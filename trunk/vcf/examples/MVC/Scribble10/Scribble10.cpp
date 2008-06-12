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
#include "ScribbleDocument.h"


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




class Scribble10Window : public Window {
public:
	Scribble10Window() {
		controller = new ScribbleController();
		controller->setName( "controller" );
		addComponent(controller);		

		view = new ScribbleView();

		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new ClassProcedure1<Event*,Scribble10Window>( this, 
																			&Scribble10Window::onDocInitialized,
																			"Scribble10Window::onDocInitialized" );


	}

	virtual ~Scribble10Window(){};

	void onDocInitialized( Event* e ) {
		static bool firstTime = true;
		if ( firstTime ) {
			initializeSettings(true);

			DocumentManager* docMgr = DocumentManager::getDocumentManager();

			docMgr->getAction( DocumentManager::atEditCopy )->addTarget( (UIComponent*)findComponent( "copyBtn", true ) );
			docMgr->getAction( DocumentManager::atEditCut )->addTarget( (UIComponent*)findComponent( "cutBtn", true ) );
			docMgr->getAction( DocumentManager::atEditPaste )->addTarget( (UIComponent*)findComponent( "pasteBtn", true ) );
			docMgr->getAction( DocumentManager::atFileOpen )->addTarget( (UIComponent*)findComponent( "openBtn", true ) );
			docMgr->getAction( DocumentManager::atFileSave )->addTarget( (UIComponent*)findComponent( "saveBtn", true ) );
			docMgr->getAction( DocumentManager::atEditUndo )->addTarget( (UIComponent*)findComponent( "undoBtn", true ) );
			docMgr->getAction( DocumentManager::atEditRedo )->addTarget( (UIComponent*)findComponent( "redoBtn", true ) );
		}

		Document* doc = (Document*)e->getSource();

		ScribbleModel* model = (ScribbleModel*)doc->getModel();

		
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
	ScribbleView* view;
	StatusBar* status;	
	ListViewControl* scribbleListing;
	ScribbleController* controller;
};




class Scribble10App : public SDIDocumentBasedApplication {
public:

	Scribble10App( int argc, char** argv );

	virtual bool initRunningApplication(){
		contentMouseDown = false;

		bool result = SDIDocumentBasedApplication::initRunningApplication();

		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new ClassProcedure1<Event*,Scribble10App>( this, 
																			&Scribble10App::onDocInitialized,
																			"Scribble10App::onDocInitialized" );
//Scribble10App::onScribbleModelChanged

		return result;
	}


	void onDocInitialized( Event* e ) {
		Document* doc = (Document*)e->getSource();

		ScribbleModel* model = (ScribbleModel*)doc->getModel();
		model->ModelChanged += getCallback( "Scribble10App::onScribbleModelChanged" );	

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
		Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseDown( MouseEvent* e ) {
		contentMouseDown = true;
		Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseUp( MouseEvent* e ) {
		contentMouseDown = false;
	}
	

	void onListSelectionChanged( Event* e ) {
		ItemEvent* ie = (ItemEvent*)e;
		
		Document* doc = getCurrentDocument();
		ScribbleModel* model = (ScribbleModel*) doc->getModel();

		model->setActiveShape( model->getShape(ie->index) );
	}

	void onViewListing( Event* e ) {
		Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
		mainWindow->scribbleListing->setVisible( !mainWindow->scribbleListing->getVisible() );
	}

	void onViewStatusbar( Event* e ) {
		Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
		mainWindow->status->setVisible( !mainWindow->status->getVisible() );		
	}

	void onUpdateViewListing( ActionEvent* e ) {
		Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
		e->setChecked( mainWindow->scribbleListing->getVisible() );
		if ( mainWindow->scribbleListing->getVisible() ) {
			e->setState( e->getState() | ToolbarItem::tisPressed );
		}
		else {
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
	}

	void onUpdateViewStatusbar( ActionEvent* e ) {
		Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
		e->setChecked( mainWindow->status->getVisible() );
		if ( mainWindow->status->getVisible() ) {
			e->setState( e->getState() | ToolbarItem::tisPressed );
		}
		else {
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
	}

	void onEditCurrentShape( Event* e ) {		
		ScribbleController* controller = (ScribbleController*) findComponent("controller",true);

		Document* doc = getCurrentDocument();
		ScribbleModel* model = (ScribbleModel*) doc->getModel();

		controller->editShape( model->getActiveShape() );
	}

	void onUpdateEditCurrentShape( ActionEvent* e ) {
		Document* doc = getCurrentDocument();
		ScribbleModel* model = (ScribbleModel*) doc->getModel();
		e->setEnabled( NULL != model->getActiveShape() );
	}

	void onDeleteCurrentShape( Event* e ) {		
		ScribbleController* controller = (ScribbleController*) findComponent("controller",true);		
		controller->deleteCurrentShape();
	}
	
	void onListKeyDown( KeyboardEvent* e ) {	
		if ( e->getVirtualCode() == vkDelete ) {
			ScribbleController* controller = (ScribbleController*) findComponent("controller",true);		
			controller->deleteCurrentShape();

			Document* doc = getCurrentDocument();
			ScribbleModel* model = (ScribbleModel*) doc->getModel();
			if ( !model->isEmpty() ) {
				model->setActiveShape( model->getShape(0) );
			}
		}
	}
	
	

	void onScribbleModelChanged( Event* e ) {
		if ( e->getType() == ScribbleModel::ActiveShapeChanged && contentMouseDown ) {
			ScribbleModel* model = (ScribbleModel*)e->getSource();
			Scribble10Window* mainWindow = (Scribble10Window*)getMainWindow();
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

_class_rtti_(Scribble10Window, "VCF::Window", "Scribble10Window")
_field_obj_( Panel*, contentPanel )
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




_class_rtti_( ScribbleDocument, "VCF::Document", "ScribbleDocument" )
_class_rtti_end_


Scribble10App::Scribble10App( int argc, char** argv ) : 
	SDIDocumentBasedApplication(argc, argv)
{
	REGISTER_CLASSINFO_EXTERNAL(Scribble10Window);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);
	REGISTER_CLASSINFO_EXTERNAL(AboutDialog);
	REGISTER_CLASSINFO_EXTERNAL(ShapeEditDialog);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleDocument);
	
	
	
	
	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onAbout), "Scribble10App::onAbout" );
	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onListSelectionChanged), "Scribble10App::onListSelectionChanged" );
	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onViewListing), "Scribble10App::onViewListing" );
	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onViewStatusbar), "Scribble10App::onViewStatusbar" );
	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onEditCurrentShape), "Scribble10App::onEditCurrentShape" );
	
	addCallback( new ClassProcedure1<ActionEvent*,Scribble10App>(this, &Scribble10App::onUpdateEditCurrentShape), "Scribble10App::onUpdateEditCurrentShape" );
	addCallback( new ClassProcedure1<ActionEvent*,Scribble10App>(this, &Scribble10App::onUpdateViewListing), "Scribble10App::onUpdateViewListing" );
	addCallback( new ClassProcedure1<ActionEvent*,Scribble10App>(this, &Scribble10App::onUpdateViewStatusbar), "Scribble10App::onUpdateViewStatusbar" );

	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onDeleteCurrentShape), "Scribble10App::onDeleteCurrentShape" );
	
	
	addCallback( new ClassProcedure1<Event*,Scribble10App>(this, &Scribble10App::onScribbleModelChanged), "Scribble10App::onScribbleModelChanged" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble10App>(this, &Scribble10App::onContentMouseMove), "Scribble10App::onContentMouseMove" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble10App>(this, &Scribble10App::onContentMouseDown), "Scribble10App::onContentMouseDown" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble10App>(this, &Scribble10App::onContentMouseUp), "Scribble10App::onContentMouseUp" );
	
	addCallback( new ClassProcedure1<KeyboardEvent*,Scribble10App>(this, &Scribble10App::onListKeyDown), "Scribble10App::onListKeyDown" );
	
}


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble10App>(argc,argv);
}



