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

class ShapeEditDialog : public Dialog {
public:

	Color strokeColor;
	Color fillColor;
	bool filled;
	double width;

	ShapeEditDialog(){
		addCallback( new ClassProcedure1<Event*,ShapeEditDialog>(this, &ShapeEditDialog::onDoColor), "ShapeEditDialog::onDoColor" );

		FrameClose += new ClassProcedure1<Event*,ShapeEditDialog>(this, &ShapeEditDialog::onClose,"onClose");
	}


	void initFromShape( ScribbleShape* shape ) {
		Control* c = (Control*)findComponent("fillColor",true);
		c->setColor( shape->getFill() );

		c = (Control*)findComponent("strokeColor",true);
		c->setColor( shape->getStroke() );

		CheckBoxControl* cb = (CheckBoxControl*)findComponent("filled",true);
		cb->setChecked( shape->getFilled() );
		
		TextControl* tc = (TextControl*)findComponent("strokeWidth",true);
		tc->setText( StringUtils::toString(shape->getStrokeWidth()) );
	}
	

	void onClose( Event* ) {
		Control* c = (Control*)findComponent("fillColor",true);
		fillColor = *c->getColor();

		c = (Control*)findComponent("strokeColor",true);
		strokeColor = *c->getColor();

		CheckBoxControl* cb = (CheckBoxControl*)findComponent("filled",true);
		filled = cb->isChecked();

		TextControl* tc = (TextControl*)findComponent("strokeWidth",true);
		width = StringUtils::fromStringAsDouble(tc->getText());

	}

	void onDoColor(Event* e) {
		Control* ctrl = (Control*)e->getSource();
		CommonColorDialog colorDlg;
		colorDlg.setSelectedColor( ctrl->getColor() );
		if ( colorDlg.execute() ) {
			
			ctrl->setColor( colorDlg.getSelectedColor() );
		}
	}
};



class Scribble5Window : public Window {
public:
	Scribble5Window() {
		
	}
	virtual ~Scribble5Window(){};

	Panel* contentPanel;
	ScribbleModel* scribble;	
	StatusBar* status;	
	ListViewControl* scribbleListing;
};




class Scribble5App : public Application {
public:

	Scribble5App( int argc, char** argv );

	virtual bool initRunningApplication(){
		contentMouseDown = false;

		bool result = Application::initRunningApplication();
		
		ScribbleController* controller = new ScribbleController();
		controller->setName( "controller" );
		addComponent(controller);


		Scribble5Window* mainWindow = (Scribble5Window*) Frame::createWindow( classid(Scribble5Window) );
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
		Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseDown( MouseEvent* e ) {
		contentMouseDown = true;
		Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
		mainWindow->status->setStatusPaneText( 2, Format("Coords: %0.1f, %0.1f") % e->getPoint()->x_ % e->getPoint()->y_ );
	}

	void onContentMouseUp( MouseEvent* e ) {
		contentMouseDown = false;
	}

	

	void onListSelectionChanged( Event* e ) {
		ItemEvent* ie = (ItemEvent*)e;
		Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
		mainWindow->scribble->setActiveShape( mainWindow->scribble->getShape(ie->index) );
	}

	void onViewListing( Event* e ) {
		Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
		mainWindow->scribbleListing->setVisible( !mainWindow->scribbleListing->getVisible() );
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( mainWindow->scribbleListing->getVisible() );
	}

	void onViewStatusbar( Event* e ) {
		Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
		mainWindow->status->setVisible( !mainWindow->status->getVisible() );
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( mainWindow->status->getVisible() );
	}

	void onEditCurrentShape( Event* e ) {
		Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
		ScribbleShape* s = mainWindow->scribble->getActiveShape();
		if ( NULL != s ) { 			
			typedef SmartPtr<ShapeEditDialog> ShapeEditDialogPtr;
			
			ShapeEditDialogPtr::Shared editDlg = ShapeEditDialogPtr::New( (ShapeEditDialog*)Frame::createDialog( classid(ShapeEditDialog) ) );
			editDlg->initFromShape(s);

			if ( editDlg->showModal() == UIToolkit::mrOK ) {
				s->setFill( &editDlg->fillColor );
				s->setStroke( &editDlg->strokeColor );

				s->setFilled( editDlg->filled );

				s->setStrokeWidth( editDlg->width );
			}
		}
	}
	
	

	void onScribbleModelChanged( Event* e ) {
		if ( e->getType() == ScribbleModel::ActiveShapeChanged && contentMouseDown ) {
			ScribbleModel* model = (ScribbleModel*)e->getSource();
			Scribble5Window* mainWindow = (Scribble5Window*)getMainWindow();
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

_class_rtti_(Scribble5Window, "VCF::Window", "Scribble5Window")
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

Scribble5App::Scribble5App( int argc, char** argv ) : 
	Application(argc, argv)
{
	REGISTER_CLASSINFO_EXTERNAL(Scribble5Window);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);
	REGISTER_CLASSINFO_EXTERNAL(AboutDialog);
	REGISTER_CLASSINFO_EXTERNAL(ShapeEditDialog);
	
	
	
	addCallback( new ClassProcedure1<Event*,Scribble5App>(this, &Scribble5App::onAbout), "Scribble5App::onAbout" );
	addCallback( new ClassProcedure1<Event*,Scribble5App>(this, &Scribble5App::onListSelectionChanged), "Scribble5App::onListSelectionChanged" );
	addCallback( new ClassProcedure1<Event*,Scribble5App>(this, &Scribble5App::onViewListing), "Scribble5App::onViewListing" );
	addCallback( new ClassProcedure1<Event*,Scribble5App>(this, &Scribble5App::onViewStatusbar), "Scribble5App::onViewStatusbar" );
	addCallback( new ClassProcedure1<Event*,Scribble5App>(this, &Scribble5App::onEditCurrentShape), "Scribble5App::onEditCurrentShape" );
	
	addCallback( new ClassProcedure1<Event*,Scribble5App>(this, &Scribble5App::onScribbleModelChanged), "Scribble5App::onScribbleModelChanged" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble5App>(this, &Scribble5App::onContentMouseMove), "Scribble5App::onContentMouseMove" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble5App>(this, &Scribble5App::onContentMouseDown), "Scribble5App::onContentMouseDown" );
	addCallback( new ClassProcedure1<MouseEvent*,Scribble5App>(this, &Scribble5App::onContentMouseUp), "Scribble5App::onContentMouseUp" );
	
	
}


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble5App>(argc,argv);
}



