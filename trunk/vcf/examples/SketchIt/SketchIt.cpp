//SketchIt.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "../examples/SketchIt/SketchDocument.h"
#include "../examples/SketchIt/SketchWindow.h"
#include "../examples/SketchIt/SketchView.h"
#include "../examples/SketchIt/SketchTools.h"


using namespace VCF;




class SketchIt : public SDIDocumentBasedApplication {
public:
	SketchIt( int argc, char** argv ) : SDIDocumentBasedApplication(argc, argv ) {

	}

	virtual void terminateRunningApplication() {
		SDIDocumentBasedApplication::terminateRunningApplication();

		ToolManager::terminate();
	}

	virtual bool initRunningApplication(){
		REGISTER_CLASSINFO( SketchDocument );
		REGISTER_CLASSINFO( SketchWindow );
		REGISTER_CLASSINFO( SketchView );

		bool result = SDIDocumentBasedApplication::initRunningApplication();

		ToolManager::init();

		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new GenericEventHandler<SketchIt>( this,
																			&SketchIt::onDocInitialized,
																			"SketchIt::onDocInitialized" );

		newDefaultDocument();

		return result;
	}

	void onDocInitialized( Event* e ) {
		Document* doc = (Document*)e->getSource();



		static bool firstTime = true;

		if ( firstTime || (doc->getWindow() != getMainWindow()) )  {
			MenuBar* menuBar = doc->getWindow()->getMenuBar();

			MenuItem* root = menuBar->getRootMenuItem();
			MenuItem* view = new DefaultMenuItem( "&View", root, menuBar );
			MenuItem* viewAA = new DefaultMenuItem( "&Anti-Aliased", view, menuBar );

			viewAA->addMenuItemClickedHandler(
				new MenuItemEventHandler<SketchIt>( this,
													&SketchIt::onToggleAntiAliasing,
													"SketchIt::onToggleAntiAliasing" ) );

			viewAA->addMenuItemUpdateHandler(
				new MenuItemEventHandler<SketchIt>( this,
													&SketchIt::onUpdateToggleAntiAliasing,
													"SketchIt::onUpdateToggleAntiAliasing" ) );


			MenuItem* tools = new DefaultMenuItem( "&Tools", root, menuBar );

			MenuItem* toolsSelect = new DefaultMenuItem( "&Select", tools, menuBar );

			MenuItem* toolsLine = new DefaultMenuItem( "&Line", tools, menuBar );
			MenuItem* toolsRect = new DefaultMenuItem( "&Rectangle", tools, menuBar );
			MenuItem* toolsBezCurve = new DefaultMenuItem( "&Bezier Curve", tools, menuBar );

			MenuItem* toolsImage = new DefaultMenuItem( "&Image", tools, menuBar );

			ToolManager::getToolManager()->setCurrentControl( doc->getWindow() );

			Tool* tool = new SelectTool();

			ToolManager::getToolManager()->registerTool( tool, toolsSelect );

			tool = new LineTool();
			ToolManager::getToolManager()->registerTool( tool, toolsLine );

			ToolManager::getToolManager()->registerTool( new RectangleTool(), toolsRect );
			ToolManager::getToolManager()->registerTool( new CurveTool(), toolsBezCurve );

			ToolManager::getToolManager()->registerTool( new ImageTool(), toolsImage );


			MenuItem* toolsXForm = new DefaultMenuItem( "&Transform", tools, menuBar );
			MenuItem* toolsXFormRotate = new DefaultMenuItem( "&Rotate", toolsXForm, menuBar );
			MenuItem* toolsXFormScale = new DefaultMenuItem( "&Scale", toolsXForm, menuBar );
			MenuItem* toolsXFormSkew = new DefaultMenuItem( "S&kew", toolsXForm, menuBar );

			tool = new RotateTool();
			ToolManager::getToolManager()->registerTool( tool, toolsXFormRotate );

			ToolManager::getToolManager()->registerTool( new ScaleTool(), toolsXFormScale );

			ToolManager::getToolManager()->registerTool( new SkewTool(), toolsXFormSkew );





			//Add menu items to the "Edit" menu
			MenuItem* edit = root->getChildAt( 1 );

			MenuItem* sep = new DefaultMenuItem( "", NULL, NULL );
			edit->insertChild( 6, sep );
			sep->setSeparator( true );

			MenuItem* editDelete = new DefaultMenuItem( "Delete\tDel", NULL, NULL );
			edit->insertChild( 7, editDelete );
			editDelete->addMenuItemClickedHandler(
				new MenuItemEventHandler<SketchIt>( this,
													&SketchIt::onDeleteShape,
													"SketchIt::onDeleteShape" ) );

			editDelete->addMenuItemUpdateHandler(
				new MenuItemEventHandler<SketchIt>( this,
													&SketchIt::onUpdateDeleteShape,
													"SketchIt::onUpdateDeleteShape" ) );

			//add a hotkey to the menuitem
			editDelete->setAcceleratorKey( vkDelete, 0 );



			MenuItem* editFill = new DefaultMenuItem( "Fill Shape", NULL, NULL );
			edit->insertChild( 8, editFill );

			editFill->addMenuItemClickedHandler(
				new MenuItemEventHandler<SketchIt>( this,
													&SketchIt::onSetFillShape,
													"SketchIt::onSetFillShape" ) );

			editFill->addMenuItemUpdateHandler(
				new MenuItemEventHandler<SketchIt>( this,
													&SketchIt::onUpdateSetFillShape,
													"SketchIt::onUpdateSetFillShape" ) );


		}

		firstTime = false;
	}

	void onDeleteShape( MenuItemEvent* e ) {
		Document*  doc = DocumentManager::getDocumentManager()->getCurrentDocument();

		if ( NULL != doc ) {
			SketchDocument* skDoc = (SketchDocument*)doc;
			Shape* shape = skDoc->getSelectedShape();

			skDoc->removeShape( shape );
		}
	}

	void onUpdateDeleteShape( MenuItemEvent* e ) {
		bool enabled = false;
		Document*  doc = DocumentManager::getDocumentManager()->getCurrentDocument();

		if ( NULL != doc ) {
			SketchDocument* skDoc = (SketchDocument*)doc;
			Shape* shape = skDoc->getSelectedShape();
			enabled = (NULL != shape) ? true : false;
		}

		MenuItem* item = (MenuItem*)e->getSource();
		item->setEnabled( enabled );
	}


	void onSetFillShape( MenuItemEvent* e ) {
		Document*  doc = DocumentManager::getDocumentManager()->getCurrentDocument();

		if ( NULL != doc ) {
			SketchDocument* skDoc = (SketchDocument*)doc;
			Shape* shape = skDoc->getSelectedShape();

			shape->fill_ = !shape->fill_;
		}
	}

	void onUpdateSetFillShape( MenuItemEvent* e ) {
		bool enabled = false;
		bool checked = false;
		Document*  doc = DocumentManager::getDocumentManager()->getCurrentDocument();

		if ( NULL != doc ) {
			SketchDocument* skDoc = (SketchDocument*)doc;
			Shape* shape = skDoc->getSelectedShape();
			enabled = (NULL != shape) ? true : false;

			if ( NULL != shape ) {
				checked = shape->fill_;
				enabled = true;
			}
		}

		MenuItem* item = (MenuItem*)e->getSource();
		item->setEnabled( enabled );
		item->setChecked( checked );
	}


	void onToggleAntiAliasing( MenuItemEvent* e ) {
		Document*  doc = DocumentManager::getDocumentManager()->getCurrentDocument();

		doc->getWindow()->setUsingRenderBuffer( !doc->getWindow()->isUsingRenderBuffer() );
		GraphicsContext* ctx = doc->getWindow()->getContext();
		if ( doc->getWindow()->isUsingRenderBuffer() ) {
			ctx->setDrawingArea( doc->getWindow()->getClientBounds() );
		}

		doc->getWindow()->repaint();
	}

	void onUpdateToggleAntiAliasing( MenuItemEvent* e ) {
		Document*  doc = DocumentManager::getDocumentManager()->getCurrentDocument();
		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( doc->getWindow()->isUsingRenderBuffer() );
	}
};


int main(int argc, char *argv[])
{
	Application* app = new SketchIt( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.4.2.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


