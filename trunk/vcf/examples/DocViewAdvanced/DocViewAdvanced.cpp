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



class CircleModel : public Model, public Persistable {
public:

	enum {
		CircleAdded = Model::MODEL_LAST_EVENT + 100,
		CircleRemoved
	};

	class AddCircleCommand : public AbstractCommand {
	public:

		AddCircleCommand( CircleModel* model, const CircleShape& shape ) : model_(model), shape_(shape){
			commandName_ = "Add Circle";
			isUndoable_ = true;
		}

		virtual void undo() {
			model_->internal_removeCircle( shape_ );
		}

		virtual void redo() {
			model_->internal_addCircle( shape_ );
		}

		virtual void execute() {
			model_->internal_addCircle( shape_ );
		}

		CircleModel* model_;
		CircleShape shape_;
	};

	class RemoveCircleCommand : public AbstractCommand {
	public:

		RemoveCircleCommand( CircleModel* model, const CircleShape& shape ) : model_(model), shape_(shape){
			commandName_ = "Remove Circle";
			isUndoable_ = true;
		}

		virtual void undo() {
			model_->internal_addCircle( shape_ );
		}

		virtual void redo() {
			model_->internal_removeCircle( shape_ );
		}

		virtual void execute() {
			model_->internal_removeCircle( shape_ );
		}

		CircleModel* model_;
		CircleShape shape_;
	};


	friend class AddCircleCommand;
	friend class RemoveCircleCommand;



	void addCircle( const CircleShape& circle ) {		
		DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new AddCircleCommand( this, circle ) );
	}

	void addCircle( const double& x, const double& y, const double& radius ) {
		addCircle( CircleShape(Point(x,y),radius) );
	}

	void addCircle( const Point& pt, const double& radius ) {
		addCircle( CircleShape(pt,radius) );
	}

	void removeCircle( const CircleShape& circle ) {
		DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new RemoveCircleCommand( this, circle ) );
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

			circles_.clear();

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
		else if ( type == STRING_DATA_TYPE ) { 
			circles_.clear();

			XMLParser parser;
			
			parser.parse( stream );			
            

			Enumerator<XMLNode*>* nodes = parser.getParsedNodes();

			while ( nodes->hasMoreElements() ) {
				XMLNode* node = nodes->nextElement();
				if ( node->getName() == getClassName() ) {

					XMLAttr* mimeTypeAttr = node->getAttrByName("mimetype");

					if ( (NULL != mimeTypeAttr) && 
							(mimeTypeAttr->getValue() == "application/x-circledoc") ) {

						Enumerator<XMLNode*>* circleNodes =  node->getChildNodes();

						while ( circleNodes->hasMoreElements() ) {
							XMLNode* circle = circleNodes->nextElement();

							XMLAttr* xAttr = circle->getAttrByName( "x" );
							XMLAttr* yAttr = circle->getAttrByName( "y" );
							XMLAttr* radiusAttr = circle->getAttrByName( "radius" );
							
							addCircle( StringUtils::fromStringAsDouble( xAttr->getValue() ),
										StringUtils::fromStringAsDouble( yAttr->getValue() ),
										StringUtils::fromStringAsDouble( radiusAttr->getValue() ) );
						}
					}				
					break;
				}
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
		else if ( type == STRING_DATA_TYPE ) { 
			//store in XML format as plain text!

			XMLNode root;
			root.setName( this->getClassName() );

			root.addAttr( "mimetype", "application/x-circledoc"  );
			root.addAttr( "document-name", getName() );

			std::vector<CircleShape>::const_iterator it = circles_.begin();
			while ( it != circles_.end() ) {

				XMLNode* circleNode = root.addChildNode( "circle" );

				const CircleShape& shape = *it;

				circleNode->addAttr( "x", StringUtils::toString( shape.center_.x_ ) );
				circleNode->addAttr( "y", StringUtils::toString( shape.center_.y_ ) );
				circleNode->addAttr( "radius", StringUtils::toString( shape.radius_ ) );

				it ++;
			}

			String xmlString = root.toString();

			stream->write( xmlString );
		}
	}
protected:
	std::vector<CircleShape> circles_;

	void internal_addCircle( const CircleShape& circle ) {
		circles_.push_back( circle );

		ModelEvent e( this, CircleModel::CircleAdded );
		ModelChanged( &e );
		updateAllViews();
	}


	void internal_removeCircle( const CircleShape& circle ) {
		std::vector<CircleShape>::iterator found = std::find( circles_.begin(), circles_.end(), circle );
		if ( found != circles_.end() ) {

			circles_.erase( found );

			ModelEvent e( this, CircleModel::CircleRemoved );
			ModelChanged( &e );
			updateAllViews();
		}
	}
};



_class_rtti_( CircleModel, "VCF::Model", "CircleModel" )
_class_rtti_end_




class CircleDocument : public Document {
public:

	CircleDocument() {}
	
	/**
	Document class overrides
	*/

	/**
	This is how our default document will look:
	3 circles that form a triangular outline
	*/
	virtual void initNew() {
		CircleModel* cm = (CircleModel*)getModel();

		cm->addCircle( 100, 20, 10 );

		cm->addCircle( 20, 120, 10 );

		cm->addCircle( 160, 120, 10 );
	}
	
};



_class_rtti_( CircleDocument, "VCF::Document", "CircleDocument" )
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

		String text = Format("Number of circle shapes: %d") % circleModel->getCircles().size();

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
				ev = new ClassProcedure1<Event*, CircleInfoUI>( this, &CircleInfoUI::onCircleModelChanged, "CircleInfoUI::onCircleModelChanged" );
			}
			newModel->ModelChanged += ev;
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


		Point oldOrigin = ctx->getOrigin();

		Scrollable* scrollable = control->getScrollable();
		if ( scrollable ) {
			Rect viewBounds = ctx->getViewableBounds();
			
			Point origin = ctx->getOrigin();
			
			control->adjustViewableBoundsAndOriginForScrollable( ctx, viewBounds, origin );
			
			ctx->setOrigin( origin );
			
			ctx->setViewableBounds( viewBounds );
		}


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

		ctx->setOrigin( oldOrigin );
	}
};




class CircleDocController : public Component {
public:

	CircleModel* model_;
	Panel* panel_;

	CircleDocController():model_(NULL), panel_(NULL){}

	void setModel( CircleModel* model ) {
		
		CallBack* ev = getCallback( "CircleDocController::onCircleModelChanged" );


		if ( NULL != model_ ) {
			if ( NULL != ev ) {
				model_->ModelChanged -= ev;
			}
		}

		model_ = model;

		if ( NULL != model_ ) {
			if ( NULL == ev ) {
				ev = new ClassProcedure1<Event*, CircleDocController>( this, &CircleDocController::onCircleModelChanged, "CircleDocController::onCircleModelChanged" );
			}
			model_->ModelChanged += ev;
		}
	}


	void onCircleModelChanged( Event* e ) {
		const std::vector<CircleShape>& circles = model_->getCircles();

		std::vector<CircleShape>::const_iterator it = circles.begin();

		Rect bounds;
		Rect r;
		while ( it != circles.end() ) {
			const CircleShape& shape = *it;
			r.left_ = shape.center_.x_ - shape.radius_;
			r.top_ = shape.center_.y_ - shape.radius_;
			r.right_ = shape.center_.x_ + shape.radius_;
			r.bottom_ = shape.center_.y_ + shape.radius_;

			r.normalize();

			if ( bounds.isEmpty() ) {
				bounds = r;
			}
			else {
				bounds.left_ = minVal<>( bounds.left_, r.left_ );
				bounds.top_ = minVal<>( bounds.top_, r.top_ );


				bounds.right_ = maxVal<>( bounds.right_, r.right_ );
				bounds.bottom_ = maxVal<>( bounds.bottom_, r.bottom_ );
			}
			
			it ++;
		}

		Scrollable* scrollable = panel_->getScrollable();

		if ( NULL != scrollable ) {
			scrollable->setVirtualViewHeight( bounds.getHeight() );
			scrollable->setVirtualViewWidth( bounds.getWidth() );
		}
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



#define DOCVIEWADVANCEDWINDOW_CLASSID		"16125cb0-731f-4fee-9d86-54b3915bb527"


class DocViewAdvancedWindow : public Window {
public:
	_class_rtti_( DocViewAdvancedWindow, "VCF::Window", DOCVIEWADVANCEDWINDOW_CLASSID )
	_class_rtti_end_



	DocViewAdvancedWindow() {
		setCaption( "DocViewBasics" );	


		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new ClassProcedure1<Event*, DocViewAdvancedWindow>( this, 
																			&DocViewAdvancedWindow::onDocInitialized,
																			"DocViewAdvancedWindow::onDocInitialized" );


		circlePanel_ = new Panel();
		circlePanel_->setBorder( NULL );

		add( circlePanel_, AlignClient );


		controller_ = new CircleDocController();
		controller_->setName( "CircleDocController" );
		addComponent( controller_ );
		controller_->panel_ = circlePanel_;

		circlePanel_->MouseClicked +=
			new ClassProcedure1<MouseEvent*,CircleDocController>( controller_, &CircleDocController::onMouseClicked, "CircleDocController::onMouseClicked" );

		circlePanel_->KeyUp +=
			new ClassProcedure1<KeyboardEvent*,CircleDocController>( controller_, &CircleDocController::onKeyUp, "CircleDocController::onKeyUp" );

		circlePanel_->setView( new CircleDocsView() );


		info_ = new CircleInfoUI();
		info_->setHeight( 75 );
		add( info_, AlignBottom );


		ScrollbarManager* sbm = new ScrollbarManager();

		sbm->setTarget( circlePanel_ );
		addComponent( sbm );

		sbm->setHasHorizontalScrollbar( true );
		sbm->setHasVerticalScrollbar( true );
		sbm->setKeepScrollbarsVisible( true ,true);


		//create our custom menus here

		MenuBar* menuBar = new MenuBar();
		setMenuBar( menuBar );
		addComponent( menuBar );


		
	}

	virtual ~DocViewAdvancedWindow(){
		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		CallBack* ev = getCallback( "DocViewAdvancedWindow::onDocInitialized" );
		if ( NULL != ev ) {
			docMgr->DocumentInitialized -= ev;
		}
		
	};


	void onDocInitialized( Event* e ) {
		Document* doc = (Document*)e->getSource();

		//is this our document?
		if ( doc->getWindow() == this ) {
			
			controller_->setModel( (CircleModel*)doc->getModel() );
			doc->addView( info_ );		
			doc->addView( circlePanel_->getView() );
		}
	}

	Panel* circlePanel_;
	CircleInfoUI* info_;
	CircleDocController* controller_;
};




class DocViewAdvancedApplication : public MDIDocumentBasedApplication {
public:

	DocViewAdvancedApplication( int argc, char** argv ) : MDIDocumentBasedApplication(argc, argv) {

	}

	virtual bool initRunningApplication(){	
		
		REGISTER_CLASSINFO_EXTERNAL( CircleModel );
		REGISTER_CLASSINFO_EXTERNAL( CircleDocument );

		REGISTER_CLASSINFO( DocViewAdvancedWindow );

		bool result = MDIDocumentBasedApplication::initRunningApplication();

		newDefaultDocument("");		
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	ApplicationKitMain<DocViewAdvancedApplication>(argc,argv);
	
	return 0;
}


