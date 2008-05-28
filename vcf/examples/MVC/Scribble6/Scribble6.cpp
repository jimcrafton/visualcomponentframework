//Scribble1.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/GraphicsKit/Ellipse.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/CheckBoxControl.h"
#include "vcf/ApplicationKit/TextControl.h"

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




class Scribble6Window : public Window {
public:
	Scribble6Window() {
		
	}
	virtual ~Scribble6Window(){};

	Panel* contentPanel;
	ScribbleModel* scribble;	
	StatusBar* status;	
	ListViewControl* scribbleListing;
};




class Scribble6App : public Application {
public:

	Scribble6App( int argc, char** argv );

	virtual bool initRunningApplication(){
		contentMouseDown = false;

		bool result = Application::initRunningApplication();
		
		ScribbleController* controller = new ScribbleController();
		controller->setName( "controller" );
		addComponent(controller);


		Scribble6Window* mainWindow = (Scribble6Window*) Frame::createWindow( classid(Scribble6Window) );
		setMainWindow(mainWindow);
		
		ScribbleView* view = new ScribbleView();
		mainWindow->contentPanel->setView( view );
		mainWindow->scribble->addView( view );
		
		
		controller->setControl( mainWindow->contentPanel );
		controller->setModel( mainWindow->scribble );

		Rect r = mainWindow->scribble->getMaxBounds();
		mainWindow->status->setStatusPaneText( 1, Format("Dimensions: %0.1f x %0.1f") % r.getWidth() % r.getHeight() );

		mainWindow->show();
		
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
		Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseDown( MouseEvent* e ) {
		contentMouseDown = true;
		Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseUp( MouseEvent* e ) {
		contentMouseDown = false;
	}
	

	void onListSelectionChanged( Event* e ) {
		ItemEvent* ie = (ItemEvent*)e;
		Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
		mainWindow->scribble->setActiveShape( mainWindow->scribble->getShape(ie->index) );
	}

	void onViewListing( Event* e ) {
		Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
		mainWindow->scribbleListing->setVisible( !mainWindow->scribbleListing->getVisible() );
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( mainWindow->scribbleListing->getVisible() );
	}

	void onViewStatusbar( Event* e ) {
		Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
		mainWindow->status->setVisible( !mainWindow->status->getVisible() );
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( mainWindow->status->getVisible() );
	}

	void onEditCurrentShape( Event* e ) {		
		ScribbleController* controller = (ScribbleController*) findComponent("controller");

		Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
		controller->editShape( mainWindow->scribble->getActiveShape() );
	}

	void onDeleteCurrentShape( Event* e ) {		
		ScribbleController* controller = (ScribbleController*) findComponent("controller");		
		controller->deleteCurrentShape();
	}
	
	void onListKeyDown( KeyboardEvent* e ) {	
		if ( e->getVirtualCode() == vkDelete ) {
			ScribbleController* controller = (ScribbleController*) findComponent("controller");		
			controller->deleteCurrentShape();

			Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
			if ( !mainWindow->scribble->isEmpty() ) {
				mainWindow->scribble->setActiveShape( mainWindow->scribble->getShape(0) );
			}
		}
	}
	
	

	void onScribbleModelChanged( Event* e ) {
		if ( e->getType() == ScribbleModel::ActiveShapeChanged && contentMouseDown ) {
			ScribbleModel* model = (ScribbleModel*)e->getSource();
			Scribble6Window* mainWindow = (Scribble6Window*)getMainWindow();
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

_class_rtti_(Scribble6Window, "VCF::Window", "Scribble6Window")
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

Scribble6App::Scribble6App( int argc, char** argv ) : 
	Application(argc, argv)
{
	REGISTER_CLASSINFO_EXTERNAL(Scribble6Window);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);
	REGISTER_CLASSINFO_EXTERNAL(AboutDialog);
	REGISTER_CLASSINFO_EXTERNAL(ShapeEditDialog);
	
	
	
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onAbout), "Scribble6App::onAbout" );
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onListSelectionChanged), "Scribble6App::onListSelectionChanged" );
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onViewListing), "Scribble6App::onViewListing" );
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onViewStatusbar), "Scribble6App::onViewStatusbar" );
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onEditCurrentShape), "Scribble6App::onEditCurrentShape" );
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onDeleteCurrentShape), "Scribble6App::onDeleteCurrentShape" );
	
	addCallback( new ClassProcedure1<Event*,Scribble6App>(this, &Scribble6App::onScribbleModelChanged), "Scribble6App::onScribbleModelChanged" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble6App>(this, &Scribble6App::onContentMouseMove), "Scribble6App::onContentMouseMove" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble6App>(this, &Scribble6App::onContentMouseDown), "Scribble6App::onContentMouseDown" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble6App>(this, &Scribble6App::onContentMouseUp), "Scribble6App::onContentMouseUp" );
	
	addCallback( new ClassProcedure1<KeyboardEvent*,Scribble6App>(this, &Scribble6App::onListKeyDown), "Scribble6App::onListKeyDown" );
	
}


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble6App>(argc,argv);
}



