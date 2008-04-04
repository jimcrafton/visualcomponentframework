//DocViewBasics.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"


using namespace VCF;








class CircleShape {
public:

	CircleShape( const Point& pt, const double& radius ) :  center_(pt), radius_(radius) {}

	CircleShape():radius_(0.0){}

	//gotta be a good C++ citizen and provide an operator== overload so
	//we can use this in STL Algorithms

	bool operator==( const CircleShape& rhs ) const{
		return 	center_ == rhs.center_ && radius_ == rhs.radius_;
	}

	/**
    * implementation of operator != is needed for BCB 5 because of the
    * ackward implementation of the find algorithm in RW STL
	*/
	bool operator!=( const CircleShape& rhs ) const{
		return ( !operator==( rhs ) );
	}

	Point center_;
	double radius_;
};


/**
First lets create a model - this will store a collection of circles.
Each circle will have a point defining it's center and a radius.
This model allows us to add, remove and get individual circles, as
well as access to the vector that stores the circles.
*/

class CircleModel : public Model, public Persistable {
public:

	enum {
		CircleAdded = Model::MODEL_LAST_EVENT + 100,
		CircleRemoved
	};

	void addCircle( const CircleShape& circle ) {
		circles_.push_back( circle );

		ModelEvent e( this, CircleModel::CircleAdded );
		ModelChanged( &e );
		updateAllViews();
	}

	void addCircle( const Point& pt, const double& radius ) {
		addCircle( CircleShape(pt,radius) );
	}

	void removeCircle( const CircleShape& circle ) {
		std::vector<CircleShape>::iterator found = std::find( circles_.begin(), circles_.end(), circle );
		if ( found != circles_.end() ) {

			circles_.erase( found );

			ModelEvent e( this, CircleModel::CircleRemoved );
			ModelChanged( &e );
			updateAllViews();
		}
	}

	CircleShape& getCircle( int index ) {
		return circles_.at(index);
	}

	const CircleShape& getCircle( int index ) const {
		return circles_.at(index);
	}

	std::vector<CircleShape>& getCircles() {
		return circles_;
	}

	const std::vector<CircleShape>& getCircles() const {
		return circles_;
	}

	int size() const {
		return circles_.size();
	}


	/**
	We need to override the Model::empty() method so we can support
	clearing out our model.
	*/
	virtual void empty() {
		//remove all the circles!
		circles_.clear();

		//make sure to call the super class's implementation
		Model::empty();
	}

	virtual bool isEmpty() {
		return circles_.empty();
	}


	virtual void loadFromStream( InputStream* stream, const MIMEType& type ) {
		if ( type == "application/x-circledoc" ) {

			int size = 0;
			stream->read( size );
			
			double radius;
			Point pt;
			for (int i=0;i<size;i++ ) {
				stream->read( pt.x_ );
				stream->read( pt.y_ );
				stream->read( radius );

				addCircle( pt, radius );
			}
		}
	}

	virtual void saveToStream( OutputStream* stream, const MIMEType& type ) {
		if ( type == "application/x-circledoc" ) {
			//save the number of circles
			int size = circles_.size();
			stream->write( size );

			std::vector<CircleShape>::const_iterator it = circles_.begin();
			while ( it != circles_.end() ) {
				const CircleShape& shape = *it;

				stream->write( shape.center_.x_ );
				stream->write( shape.center_.y_ );
				stream->write( shape.radius_ );
				it ++;
			}
		}
	}

	std::vector<CircleShape> circles_;
};



_class_rtti_( CircleModel, "VCF::Model", "CircleModel" )
_class_rtti_end_





class CircleInfoUI : public CustomControl {
public:
	CircleInfoUI() : CustomControl(true) {

		EtchedBorder* bdr = new EtchedBorder();
		bdr->setEdgeStyle( GraphicsContext::etSunken );
		setBorder( bdr );


		setContainer( new StandardContainer() );

		circleCount_ = new Label();
		circleCount_->setCaption( "" );

		circleCount_->setHeight( 50 );
		getContainer()->add( circleCount_, AlignTop );

		modelState_ = new Label();
		modelState_->setCaption( "" );

		modelState_->setHeight( 50 );
		getContainer()->add( modelState_, AlignClient );
	}

	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );
		getContainer()->paintChildren( ctx );
	}

	virtual void updateView( Model* model ) {
		CircleModel* circleModel = (CircleModel*)model;

		String text = Format( "Number of circle shapes: %d" ) 
						% circleModel->getCircles().size();

		circleCount_->setCaption( text );

		CustomControl::updateView( model );
	}


	virtual void modelChanged( Model* oldModel, Model* newModel ) {
		CallBack* ev = getCallback( "CircleInfoUI::onCircleModelChanged" );


		if ( NULL != oldModel ) {
			if ( NULL != ev ) {
				oldModel->ModelChanged -= ev;
			}
		}

		

		if ( NULL != newModel ) {
			if ( NULL == ev ) {
				ev = new ClassProcedure1<Event*,CircleInfoUI>( this, &CircleInfoUI::onCircleModelChanged, "CircleInfoUI::onCircleModelChanged" );
			}
			newModel->ModelChanged +=ev;
		}
	}



	void onCircleModelChanged( Event* e ) {
		switch ( e->getType() ) {
			case CircleModel::CircleAdded : {
				modelState_->setCaption( "New Circle Added" );
			}
			break;

			case CircleModel::CircleRemoved : {
				modelState_->setCaption( "Circle removed" );
			}
			break;

			case Model::MODEL_EMPTIED : {
				modelState_->setCaption( "Model emptied." );
			}
			break;
		}
	}

protected:
	Label* circleCount_;
	Label* modelState_;
};






class CircleDocsView : public AbstractView {
public:


	virtual void paintView( GraphicsContext* ctx ) {


		Control* control = AbstractView::getViewControl();

		Rect r = control->getClientBounds();


		ctx->rectangle( &r );
		ctx->setColor( Color::getColor("white") );
		ctx->fillPath();


		EtchedBorder bdr;
		bdr.setEdgeStyle( GraphicsContext::etSunken );
		bdr.paint( &r, ctx );


		CircleModel* model = (CircleModel*)getViewModel();

		const std::vector<CircleShape>& circles = model->getCircles();
		for ( std::vector<CircleShape>::const_iterator it = circles.begin(); it!=circles.end(); it++ ) {
			const CircleShape& circle = *it;

			ctx->setColor( Color::getColor("blue") );
			ctx->circle( circle.center_, circle.radius_ );
			ctx->fillPath();

			ctx->setColor( Color::getColor("black") );
			ctx->circle( circle.center_, circle.radius_ );
			ctx->strokePath();

		}
	}
};




class CircleViewController : public Component {
public:

	CircleModel* model_;
	Panel* panel_;

	CircleViewController():model_(NULL), panel_(NULL){}

	void setModel( Model* model ) {
		
		CallBack* ev = getCallback( "CircleViewController::onCircleModelChanged" );


		if ( NULL != model_ ) {
			if ( NULL != ev ) {
				model_->ModelChanged -= ev;
			}
		}

		model_ = (CircleModel*)model;

		if ( NULL != model_ ) {
			if ( NULL == ev ) {
				ev = new ClassProcedure1<Event*,CircleViewController>( this, &CircleViewController::onCircleModelChanged, "CircleViewController::onCircleModelChanged" );
			}
			model_->ModelChanged += ev;
		}
	}


	void onCircleModelChanged( Event* e ) {
		//no-op for now
	}

	void onMouseClicked( MouseEvent* e ) {

		if ( e->hasLeftButton() ) {
			model_->addCircle( *e->getPoint(), 50 );
		}
		else if ( e->hasRightButton() ) {

			const std::vector<CircleShape>& circles = model_->getCircles();

			std::vector<CircleShape>::const_iterator it = circles.begin();
			Rect r;
			while ( it != circles.end() ) {
				const CircleShape& shape = *it;
				r.left_ = shape.center_.x_ - shape.radius_;
				r.top_ = shape.center_.y_ - shape.radius_;
				r.right_ = shape.center_.x_ + shape.radius_;
				r.bottom_ = shape.center_.y_ + shape.radius_;

				if ( r.containsPt( e->getPoint() ) ) {
					model_->removeCircle( shape );
					break;
				}
				it ++;
			}

		}
	}

	void onKeyUp( KeyboardEvent* e ) {

		if ( e->getVirtualCode() == vkDelete ) {
			model_->empty();
		}
	}
};



#define DOCVIEWBASICSWINDOW_CLASSID		"16125cb0-731f-4fee-9d86-54b3915bb527"


class DocViewBasicsWindow : public Window {
public:
	_class_rtti_( DocViewBasicsWindow, "VCF::Window", DOCVIEWBASICSWINDOW_CLASSID )
	_class_rtti_end_



	DocViewBasicsWindow() {
		setCaption( "DocViewBasics" );	


		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new ClassProcedure1<Event*,DocViewBasicsWindow>( this, 
																			&DocViewBasicsWindow::onDocInitialized,
																			"DocViewBasicsWindow::onDocInitialized" );


		circlePanel_ = new Panel();
		circlePanel_->setBorder( NULL );

		add( circlePanel_, AlignClient );


		controller_ = new CircleViewController();
		controller_->setName( "CircleViewController" );
		addComponent( controller_ );
		controller_->panel_ = circlePanel_;

		circlePanel_->MouseClicked +=
			new ClassProcedure1<MouseEvent*,CircleViewController>( controller_, &CircleViewController::onMouseClicked, "CircleViewController::onMouseClicked" );

		circlePanel_->KeyUp +=
			new ClassProcedure1<KeyboardEvent*,CircleViewController>( controller_, &CircleViewController::onKeyUp, "CircleViewController::onKeyUp" );

		circlePanel_->setView( new CircleDocsView() );


		info_ = new CircleInfoUI();
		info_->setHeight( 150 );
		add( info_, AlignBottom );		
	}

	virtual ~DocViewBasicsWindow(){};


	void onDocInitialized( Event* e ) {
		Document* doc = (Document*)e->getSource();		

		controller_->setModel( doc->getModel() );
		doc->addView( info_ );		
		doc->addView( circlePanel_->getView() );
	}

	Panel* circlePanel_;
	CircleInfoUI* info_;
	CircleViewController* controller_;
};




class DocViewBasicsApplication : public SDIDocumentBasedApplication {
public:

	DocViewBasicsApplication( int argc, char** argv ) : SDIDocumentBasedApplication(argc, argv) {
		this->setSingleInstance(true);
	}

	virtual bool initRunningApplication(){	
		
		REGISTER_CLASSINFO_EXTERNAL( CircleModel );
		REGISTER_CLASSINFO( DocViewBasicsWindow );

		bool result = SDIDocumentBasedApplication::initRunningApplication();

		processCommandLine();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<DocViewBasicsApplication>(argc, argv);
}


