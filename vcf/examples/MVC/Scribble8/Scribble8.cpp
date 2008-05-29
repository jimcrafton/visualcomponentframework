//Scribble1.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/GraphicsKit/Ellipse.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/CheckBoxControl.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/Toolbar.h"

#include "ScribbleModel.h"
#include "ScribbleView.h"
#include "ScribbleController.h"


using namespace VCF;

class AboutDialog : public Dialog {
public:
	Label* program;
	Label* author;
	Label* company;
	Label* copyright;
	AboutDialog(){}

	virtual ~AboutDialog()
	{

	}
};




class Scribble8Window : public Window {
public:
	Scribble8Window() {
		controller = new ScribbleController();
		controller->setName( "controller" );
		addComponent(controller);		

		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new ClassProcedure1<Event*,Scribble8Window>( this, 
																			&Scribble8Window::onDocInitialized,
																			"Scribble8Window::onDocInitialized" );


	}

	virtual ~Scribble8Window(){};

	void onDocInitialized( Event* e ) {
		static bool firstTime = true;
		if ( firstTime ) {
			initializeSettings(true);
		}

		Document* doc = (Document*)e->getSource();

		ScribbleModel* model = (ScribbleModel*)doc->getModel();

		ScribbleView* view = new ScribbleView();
		contentPanel->setView( view );
		model->addView( view );


		scribbleListing->setModel( model );

		controller->setControl( contentPanel );
		controller->setModel( model );

		Rect r = model->getMaxBounds();
		status->setStatusPaneText( 1, Format("Dimensions: %0.1f x %0.1f") % r.getWidth() % r.getHeight() );		
		firstTime = false;
	}


	Panel* contentPanel;
	ScribbleModel* scribble;	
	StatusBar* status;	
	ListViewControl* scribbleListing;
	ScribbleController* controller;
};




class Scribble8App : public SDIDocumentBasedApplication {
public:

	Scribble8App( int argc, char** argv );

	virtual bool initRunningApplication(){
		contentMouseDown = false;

		bool result = SDIDocumentBasedApplication::initRunningApplication();

		return result;
	}

	void onAbout(Event*) {
		typedef SmartPtr<AboutDialog> AboutDialogPtr;

		AboutDialogPtr::Shared aboutDlg = AboutDialogPtr::New( (AboutDialog*)Frame::createDialog( classid(AboutDialog) ) );
		ProgramInfo* info = this->getResourceBundle()->getProgramInfo();
		if ( NULL != info ) {
			aboutDlg->program->setCaption( info->getProgramName() );
			aboutDlg->author->setCaption( info->getAuthor() );
			aboutDlg->company->setCaption( info->getCompany() );
			aboutDlg->copyright->setCaption( info->getCopyright() );
			delete info;
		}
		aboutDlg->showModal();
		
	}

	void onContentMouseMove( MouseEvent* e ) {
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseDown( MouseEvent* e ) {
		contentMouseDown = true;
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseUp( MouseEvent* e ) {
		contentMouseDown = false;
	}
	

	void onListSelectionChanged( Event* e ) {
		ItemEvent* ie = (ItemEvent*)e;
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		mainWindow->scribble->setActiveShape( mainWindow->scribble->getShape(ie->index) );
	}

	void onViewListing( Event* e ) {
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		mainWindow->scribbleListing->setVisible( !mainWindow->scribbleListing->getVisible() );
	}

	void onViewStatusbar( Event* e ) {
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		mainWindow->status->setVisible( !mainWindow->status->getVisible() );		
	}

	void onUpdateViewListing( ActionEvent* e ) {
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		e->setChecked( mainWindow->scribbleListing->getVisible() );
		if ( mainWindow->scribbleListing->getVisible() ) {
			e->setState( e->getState() | ToolbarItem::tisPressed );
		}
		else {
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
	}

	void onUpdateViewStatusbar( ActionEvent* e ) {
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		e->setChecked( mainWindow->status->getVisible() );
		if ( mainWindow->status->getVisible() ) {
			e->setState( e->getState() | ToolbarItem::tisPressed );
		}
		else {
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
	}

	void onEditCurrentShape( Event* e ) {		
		ScribbleController* controller = (ScribbleController*) findComponent("controller");

		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		controller->editShape( mainWindow->scribble->getActiveShape() );
	}

	void onUpdateEditCurrentShape( ActionEvent* e ) {
		Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
		e->setEnabled( NULL != mainWindow->scribble->getActiveShape() );
	}

	void onDeleteCurrentShape( Event* e ) {		
		ScribbleController* controller = (ScribbleController*) findComponent("controller");		
		controller->deleteCurrentShape();
	}
	
	void onListKeyDown( KeyboardEvent* e ) {	
		if ( e->getVirtualCode() == vkDelete ) {
			ScribbleController* controller = (ScribbleController*) findComponent("controller");		
			controller->deleteCurrentShape();

			Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
			if ( !mainWindow->scribble->isEmpty() ) {
				mainWindow->scribble->setActiveShape( mainWindow->scribble->getShape(0) );
			}
		}
	}
	
	

	void onScribbleModelChanged( Event* e ) {
		if ( e->getType() == ScribbleModel::ActiveShapeChanged && contentMouseDown ) {
			ScribbleModel* model = (ScribbleModel*)e->getSource();
			Scribble8Window* mainWindow = (Scribble8Window*)getMainWindow();
			if ( NULL != model->getActiveShape() ) {
				VariantData v = (ScribbleShape*) model->getActiveShape();
				mainWindow->scribbleListing->selectItem( model->getIndexOf( v ) );
			}
			else {
				mainWindow->scribbleListing->selectItem( ListModel::InvalidIndex );
			}
		}
	}

	bool contentMouseDown;
};











_class_rtti_(ScribbleController, "VCF::Component", "ScribbleController")
_class_rtti_end_

_class_rtti_(Scribble8Window, "VCF::Window", "Scribble8Window")
_field_obj_( Panel*, contentPanel )
_field_obj_( ScribbleModel*, scribble )
_field_obj_( StatusBar*, status )
_field_obj_( ListViewControl*, scribbleListing )

_class_rtti_end_

_class_rtti_(AboutDialog, "VCF::Dialog", "AboutDialog")
_field_obj_( Label*, program )
_field_obj_( Label*, copyright )
_field_obj_( Label*, author )
_field_obj_( Label*, company )
_class_rtti_end_

_class_rtti_(ShapeEditDialog, "VCF::Dialog", "ShapeEditDialog")
_class_rtti_end_


_class_rtti_(ScribbleShape, "VCF::Object", "ScribbleShape")
_property_object_( Color, "fill", getFill, setFill, "" );
_property_object_( Color, "stroke", getStroke, setStroke, "" );
_property_( double, "strokeWidth", getStrokeWidth, setStrokeWidth, "" );
_property_( bool, "filled", getFilled, setFilled, "" );
_property_( String, "data", getData, setData, "" );
_property_( double, "rotation", getRotation, setRotation, "" );
_property_( double, "transX", getTranslateX, setTranslateX, "" );
_property_( double, "transY", getTranslateY, setTranslateY, "" );
_property_( double, "scaleX", getScaleX, setScaleX, "" );
_property_( double, "scaleY", getScaleY, setScaleY, "" );
_property_( double, "shearX", getShearX, setShearX, "" );
_property_( double, "shearY", getShearY, setShearY, "" );
_class_rtti_end_

_class_rtti_(ScribbleModel, "VCF::SimpleListModel", "ScribbleModel")
_property_array_( VariantData, "shapes", get,set,insert,remove,getCount, "" )
_property_object_( Color, "backColor", getBackColor, setBackColor, "" );
_property_object_( Color, "defaultFill", getDefaultFillColor, setDefaultFillColor, "" );
_property_object_( Color, "defaultStroke", getDefaultStrokeColor, setDefaultStrokeColor, "" );
_property_( double, "defaultStrokeWidth", getDefaultWidth, setDefaultWidth, "" );
_property_( bool, "defaultFilled", getDefaultFilled, setDefaultFilled, "" );
_class_rtti_end_

Scribble8App::Scribble8App( int argc, char** argv ) : 
	SDIDocumentBasedApplication(argc, argv)
{
	REGISTER_CLASSINFO_EXTERNAL(Scribble8Window);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);
	REGISTER_CLASSINFO_EXTERNAL(AboutDialog);
	REGISTER_CLASSINFO_EXTERNAL(ShapeEditDialog);
	
	
	
	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onAbout), "Scribble8App::onAbout" );
	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onListSelectionChanged), "Scribble8App::onListSelectionChanged" );
	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onViewListing), "Scribble8App::onViewListing" );
	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onViewStatusbar), "Scribble8App::onViewStatusbar" );
	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onEditCurrentShape), "Scribble8App::onEditCurrentShape" );
	
	addCallback( new ClassProcedure1<ActionEvent*,Scribble8App>(this, &Scribble8App::onUpdateEditCurrentShape), "Scribble8App::onUpdateEditCurrentShape" );
	addCallback( new ClassProcedure1<ActionEvent*,Scribble8App>(this, &Scribble8App::onUpdateViewListing), "Scribble8App::onUpdateViewListing" );
	addCallback( new ClassProcedure1<ActionEvent*,Scribble8App>(this, &Scribble8App::onUpdateViewStatusbar), "Scribble8App::onUpdateViewStatusbar" );

	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onDeleteCurrentShape), "Scribble8App::onDeleteCurrentShape" );
	
	
	addCallback( new ClassProcedure1<Event*,Scribble8App>(this, &Scribble8App::onScribbleModelChanged), "Scribble8App::onScribbleModelChanged" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble8App>(this, &Scribble8App::onContentMouseMove), "Scribble8App::onContentMouseMove" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble8App>(this, &Scribble8App::onContentMouseDown), "Scribble8App::onContentMouseDown" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble8App>(this, &Scribble8App::onContentMouseUp), "Scribble8App::onContentMouseUp" );
	
	addCallback( new ClassProcedure1<KeyboardEvent*,Scribble8App>(this, &Scribble8App::onListKeyDown), "Scribble8App::onListKeyDown" );
	
}


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble8App>(argc,argv);
}



