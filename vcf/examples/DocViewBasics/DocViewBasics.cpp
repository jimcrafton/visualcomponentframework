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

	bool operator!=( const CircleShape& rhs ) const{
		return 	center_ != rhs.center_ || radius_ != rhs.radius_;
	}

	Point center_;
	double radius_;
};


/**
*/


#define CIRCLEDOCUMENT_CLASSID		"ccdeaf42-a9fd-4fb4-adf7-13077976539e"

class CircleDocument : public Document {
public:
	_class_rtti_( CircleDocument, "VCF::Document", CIRCLEDOCUMENT_CLASSID )
	_class_rtti_end_


	enum {
		CircleAdded = Model::MODEL_LAST_EVENT + 100,
		CircleRemoved
	};

	void addCircle( const CircleShape& circle ) {
		circles_.push_back( circle );

		setModified( true );

		ModelEvent e( this, CircleDocument::CircleAdded );
		ModelChanged.fireEvent( &e );
		updateAllViews();
	}

	void addCircle( const double& x, const double& y, const double& radius ) {
		addCircle( CircleShape(Point(x,y),radius) );
	}

	void addCircle( const Point& pt, const double& radius ) {
		addCircle( CircleShape(pt,radius) );
	}

	void removeCircle( const CircleShape& circle ) {
		std::vector<CircleShape>::iterator found = std::find( circles_.begin(), circles_.end(), circle );
		if ( found != circles_.end() ) {

			circles_.erase( found );

			setModified( true );

			ModelEvent e( this, CircleDocument::CircleRemoved );
			ModelChanged.fireEvent( &e );
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
		Document::empty();
	}

	


	/**
	Document class overrides
	*/

	/**
	This is how our default document will look:
	3 circles that form a triangular outline
	*/
	virtual void initNew() {
		addCircle( 100, 20, 10 );

		addCircle( 20, 120, 10 );

		addCircle( 160, 120, 10 );
	}



	virtual bool saveAsType( const VCF::String& fileType, VCF::OutputStream& stream ) {
		bool result = false;

		if ( fileType == "application/x-circledoc" ) {

			
			//save the number of circles
			int size = circles_.size();
			stream.write( size );

			std::vector<CircleShape>::const_iterator it = circles_.begin();
			while ( it != circles_.end() ) {
				const CircleShape& shape = *it;

				stream.write( shape.center_.x_ );
				stream.write( shape.center_.y_ );
				stream.write( shape.radius_ );
				it ++;
			}

			result = true;
		}

		return result;
	}

	virtual bool openFromType( const VCF::String& fileType, VCF::InputStream& stream ) {
		bool result = false;

		if ( fileType == "application/x-circledoc" ) {

			int size = 0;
			stream.read( size );
			
			double radius;
			Point pt;
			for (int i=0;i<size;i++ ) {
				stream.read( pt.x_ );
				stream.read( pt.y_ );
				stream.read( radius );

				addCircle( pt, radius );
			}

			result = true;
		}

		return result;
	}

	virtual bool canCutFromDocument() {
		return !circles_.empty();
	}

	virtual bool canCopyFromDocument() {
		return !circles_.empty();
	}

	virtual bool canPasteToDocument() {
		Clipboard* clipboard = UIToolkit::getSystemClipboard();
		return clipboard->hasDataType( "application/x-circledoc" );
	}
protected:

	std::vector<CircleShape> circles_;
};













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
		CircleDocument* circleModel = (CircleDocument*)model;

		String text = Format( "Number of circle shapes: %d" ) 
						% circleModel->getCircles().size();

		circleCount_->setCaption( text );

		CustomControl::updateView( model );
	}


	virtual void setViewModel( Model* model ) {
		EventHandler* ev = getEventHandler( "CircleInfoUI::onCircleModelChanged" );


		if ( NULL != model ) {
			if ( NULL != ev ) {
				model->removeModelHandler( ev );
			}
		}

		CustomControl::setViewModel( model );

		if ( NULL != model ) {
			if ( NULL == ev ) {
				ev = new GenericEventHandler<CircleInfoUI>( this, &CircleInfoUI::onCircleModelChanged, "CircleInfoUI::onCircleModelChanged" );
			}
			model->addModelHandler( ev );
		}
	}


	void onCircleModelChanged( Event* e ) {
		switch ( e->getType() ) {
			case CircleDocument::CircleAdded : {
				modelState_->setCaption( "New Circle Added" );
			}
			break;

			case CircleDocument::CircleRemoved : {
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


		CircleDocument* model = (CircleDocument*)getViewModel();

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




class CircleDocController : public Component {
public:

	CircleDocument* model_;
	Panel* panel_;

	CircleDocController():model_(NULL), panel_(NULL){}

	void setModel( CircleDocument* model ) {
		
		EventHandler* ev = getEventHandler( "CircleDocController::onCircleModelChanged" );


		if ( NULL != model_ ) {
			if ( NULL != ev ) {
				model_->removeModelHandler( ev );
			}
		}

		model_ = model;

		if ( NULL != model_ ) {
			if ( NULL == ev ) {
				ev = new GenericEventHandler<CircleDocController>( this, &CircleDocController::onCircleModelChanged, "CircleDocController::onCircleModelChanged" );
			}
			model_->addModelHandler( ev );
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
		docMgr->DocumentInitialized += new GenericEventHandler<DocViewBasicsWindow>( this, 
																			&DocViewBasicsWindow::onDocInitialized,
																			"DocViewBasicsWindow::onDocInitialized" );


		circlePanel_ = new Panel();
		circlePanel_->setBorder( NULL );

		add( circlePanel_, AlignClient );


		controller_ = new CircleDocController();
		controller_->setName( "CircleDocController" );
		addComponent( controller_ );
		controller_->panel_ = circlePanel_;

		circlePanel_->MouseClicked +=
			new MouseEventHandler<CircleDocController>( controller_, &CircleDocController::onMouseClicked, "CircleDocController::onMouseClicked" );

		circlePanel_->KeyUp +=
			new KeyboardEventHandler<CircleDocController>( controller_, &CircleDocController::onKeyUp, "CircleDocController::onKeyUp" );

		circlePanel_->setView( new CircleDocsView() );


		info_ = new CircleInfoUI();
		info_->setHeight( 150 );
		add( info_, AlignBottom );		
	}

	virtual ~DocViewBasicsWindow(){};


	void onDocInitialized( Event* e ) {
		CircleDocument* doc = (CircleDocument*)e->getSource();		

		controller_->setModel( doc );
		doc->addView( info_ );		
		doc->addView( circlePanel_->getView() );
	}

	Panel* circlePanel_;
	CircleInfoUI* info_;
	CircleDocController* controller_;
};




class DocViewBasicsApplication : public SDIDocumentBasedApplication {
public:

	DocViewBasicsApplication( int argc, char** argv ) : SDIDocumentBasedApplication(argc, argv) {

	}

	virtual bool initRunningApplication(){	
		
		REGISTER_CLASSINFO( CircleDocument );
		REGISTER_CLASSINFO( DocViewBasicsWindow );

		bool result = SDIDocumentBasedApplication::initRunningApplication();

		newDefaultDocument("");

		
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new DocViewBasicsApplication( argc, argv );

	Application::main();
	
	return 0;
}


