//DocViewBasics.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"




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
	BEGIN_CLASSINFO( CircleDocument, "CircleDocument", "VCF::Document", CIRCLEDOCUMENT_CLASSID )
	END_CLASSINFO(CircleDocument)




	class AddCircleCommand : public AbstractCommand {
	public:

		AddCircleCommand( CircleDocument* doc, const CircleShape& shape ) : doc_(doc), shape_(shape){
			commandName_ = "Add Circle";
			isUndoable_ = true;
		}

		virtual void undo() {
			doc_->internal_removeCircle( shape_ );
		}

		virtual void redo() {
			doc_->internal_addCircle( shape_ );
		}

		virtual void execute() {
			doc_->internal_addCircle( shape_ );
		}

		CircleDocument* doc_;
		CircleShape shape_;
	};

	class RemoveCircleCommand : public AbstractCommand {
	public:

		RemoveCircleCommand( CircleDocument* doc, const CircleShape& shape ) : doc_(doc), shape_(shape){
			commandName_ = "Remove Circle";
			isUndoable_ = true;
		}

		virtual void undo() {
			doc_->internal_addCircle( shape_ );
		}

		virtual void redo() {
			doc_->internal_removeCircle( shape_ );
		}

		virtual void execute() {
			doc_->internal_removeCircle( shape_ );
		}

		CircleDocument* doc_;
		CircleShape shape_;
	};


	friend class AddCircleCommand;
	friend class RemoveCircleCommand;


	CircleDocument() {
		this->addSupportedClipboardFormat( STRING_DATA_TYPE );
	}

	enum {
		CircleAdded = Model::MODEL_LAST_EVENT + 100,
		CircleRemoved
	};

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
		else if ( fileType == STRING_DATA_TYPE ) { 
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

			stream.write( xmlString );
			result = true;
		}

		return result;
	}

	virtual bool openFromType( const VCF::String& fileType, VCF::InputStream& stream ) {
		bool result = false;
		

		if ( fileType == "application/x-circledoc" ) {

			circles_.clear();

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
		else if ( fileType == STRING_DATA_TYPE ) { 
			//read as XML format as plain text!

			circles_.clear();

			XMLParser parser;
			
			parser.parse( &stream );			
            

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

						result = true;
					}				
					break;
				}
			}			
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
		return clipboard->hasDataType( "application/x-circledoc" ) || clipboard->hasDataType( STRING_DATA_TYPE );
	}

	/*
	Add support for both our custom clipboard type, 
	"application/x-circledoc", and support plain text in
	the form of STRING_DATA_TYPE type. 
	*/
	virtual DataObject* copy() {
		DataObject* result = NULL;
		BasicOutputStream bos;
		
		if ( saveAsType( "application/x-circledoc", bos ) ) {
			if ( NULL == result ) {
				result = new DataObject();
			}
			BinaryPersistable* persistable = new BinaryPersistable( (const unsigned char*)bos.getBuffer(), bos.getSize() );
			result->addSupportedDataType( "application/x-circledoc", persistable );
		}

		BasicOutputStream bos2;
		
		if ( saveAsType( STRING_DATA_TYPE, bos2 ) ) {
			if ( NULL == result ) {
				result = new DataObject();
			}
			BinaryPersistable* persistable = new BinaryPersistable( (const unsigned char*)bos2.getBuffer(), bos2.getSize() );
			result->addSupportedDataType( STRING_DATA_TYPE, persistable );
		}
		
		return result;
	}
protected:

	std::vector<CircleShape> circles_;

	void internal_addCircle( const CircleShape& circle ) {
		circles_.push_back( circle );

		setModified( true );

		ModelEvent e( this, CircleDocument::CircleAdded );
		ModelChanged.fireEvent( &e );
		updateAllViews();
	}


	void internal_removeCircle( const CircleShape& circle ) {
		std::vector<CircleShape>::iterator found = std::find( circles_.begin(), circles_.end(), circle );
		if ( found != circles_.end() ) {

			circles_.erase( found );

			setModified( true );

			ModelEvent e( this, CircleDocument::CircleRemoved );
			ModelChanged.fireEvent( &e );
			updateAllViews();
		}
	}
};













class CircleInfoUI : public CustomControl {
public:
	CircleInfoUI() : CustomControl(true) {

		EtchedBorder* bdr = new EtchedBorder();
		bdr->setStyle( GraphicsContext::etSunken );
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

		String text = StringUtils::format( "Number of circle shapes: %d", circleModel->getCircles().size() );

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
		bdr.setStyle( GraphicsContext::etSunken );
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

		ctx->setOrigin( oldOrigin );
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
	BEGIN_CLASSINFO( DocViewAdvancedWindow, "DocViewAdvancedWindow", "VCF::Window", DOCVIEWADVANCEDWINDOW_CLASSID )
	END_CLASSINFO(DocViewAdvancedWindow)



	DocViewAdvancedWindow() {
		setCaption( "DocViewBasics" );	


		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new GenericEventHandler<DocViewAdvancedWindow>( this, 
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
			new MouseEventHandler<CircleDocController>( controller_, &CircleDocController::onMouseClicked, "CircleDocController::onMouseClicked" );

		circlePanel_->KeyUp +=
			new KeyboardEventHandler<CircleDocController>( controller_, &CircleDocController::onKeyUp, "CircleDocController::onKeyUp" );

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

	virtual ~DocViewAdvancedWindow(){};


	void onDocInitialized( Event* e ) {
		CircleDocument* doc = (CircleDocument*)e->getSource();

		//is this our document?
		if ( doc->getWindow() == this ) {
			
			controller_->setModel( doc );
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
		
		REGISTER_CLASSINFO( CircleDocument );
		REGISTER_CLASSINFO( DocViewAdvancedWindow );

		bool result = MDIDocumentBasedApplication::initRunningApplication();

		newDefaultDocument();

		
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new DocViewAdvancedApplication( argc, argv );

	Application::main();
	
	return 0;
}


