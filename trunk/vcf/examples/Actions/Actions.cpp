//Actions.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"


using namespace VCF;


/**
This example will explain how to use the Action class in conjunction with various UI elements.
It's a good way to see how the different elements work together
*/



class ActionsWindow : public Window {
public:
	ActionsWindow() {
		setCaption( "Actions" );		


		Toolbar* tb = new Toolbar();
		tb->setName( "Toolbar1" );
		tb->setHeight( 25 );
		add( tb, AlignTop );

		ImageList* il = new ImageList();
		il->setImageHeight( 19 );
		il->setImageWidth( 19 );
		il->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
		addComponent( il );

		tb->setImageList( il );

		ResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();
		Image* img = resBundle->getImage( "new" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "open" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "save" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "saveall" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "copy" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "paste" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "undo" );
		il->addImage( img );
		delete img;


		img = resBundle->getImage( "side" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "hammer" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "wnd" );
		il->addImage( img );
		delete img;


		MenuBar* menuBar = new MenuBar();
		setMenuBar( menuBar );
		addComponent( menuBar ); 

		MenuItem* root = menuBar->getRootMenuItem();

		DefaultMenuItem* file = new DefaultMenuItem( "&File", root, menuBar );

		DefaultMenuItem* fileNew = new DefaultMenuItem( "&New", file, menuBar );
		
		DefaultMenuItem* menuSep = new DefaultMenuItem( "", file, menuBar );
		menuSep->setSeparator( true );

		DefaultMenuItem* fileOpen = new DefaultMenuItem( "&Open", file, menuBar );
		DefaultMenuItem* fileSave = new DefaultMenuItem( "&Save", file, menuBar );
		DefaultMenuItem* fileSaveAll = new DefaultMenuItem( "Save &All", file, menuBar );

		DefaultMenuItem* edit = new DefaultMenuItem( "&Edit", root, menuBar );
		
		DefaultMenuItem* editUndo = new DefaultMenuItem( "&Undo", edit, menuBar );

		menuSep = new DefaultMenuItem( "", edit, menuBar );
		menuSep->setSeparator( true );

		DefaultMenuItem* editCopy = new DefaultMenuItem( "&Copy", edit, menuBar );
		DefaultMenuItem* editPaste = new DefaultMenuItem( "&Paste", edit, menuBar );


		DefaultMenuItem* view = new DefaultMenuItem( "&View", root, menuBar );
		DefaultMenuItem* viewSidebar = new DefaultMenuItem( "&Side Bar", view, menuBar );
		DefaultMenuItem* viewHammer = new DefaultMenuItem( "&Hammer", view, menuBar );
		DefaultMenuItem* viewWindows = new DefaultMenuItem( "Show &Window List", view, menuBar );


		ToolbarItem* newTBitem = tb->addToolBarButton( "New" );
		newTBitem->setTooltip( "New Item" );

		tb->addToolBarButton( "" )->setAsSeparator();

		ToolbarItem* openTBitem = tb->addToolBarButton( "Open" );
		openTBitem->setImageIndex( 1 );
		openTBitem->setTooltip( "Open from file" );

		ToolbarItem* saveTBitem = tb->addToolBarButton( "Save" );
		saveTBitem->setImageIndex( 2 );
		saveTBitem->setTooltip( "Save to file" );

		ToolbarItem* saveAllTBitem = tb->addToolBarButton( "Save All" );
		saveAllTBitem->setImageIndex( 3 );
		saveAllTBitem->setTooltip( "Save All to file" );

		tb->addToolBarButton( "" )->setAsSeparator();

		ToolbarItem* copyTBitem = tb->addToolBarButton( "Copy" );
		copyTBitem->setImageIndex( 4 );
		copyTBitem->setTooltip( "Copy to clipboard" );

		ToolbarItem* pasteTBitem = tb->addToolBarButton( "Paste" );
		pasteTBitem->setImageIndex( 5 );
		pasteTBitem->setTooltip( "Paste from clipboard" );

		tb->addToolBarButton( "" )->setAsSeparator();

		ToolbarItem* undoTBitem = tb->addToolBarButton( "Undo" );
		undoTBitem->setImageIndex( 6 );
		undoTBitem->setTooltip( "Undo last action" );

		tb->addToolBarButton( "" )->setAsSeparator();

		ToolbarItem* sidebarTBitem = tb->addToolBarButton( "Sidebar" );
		sidebarTBitem->setImageIndex( 7 );
		sidebarTBitem->setChecked(true);
		sidebarTBitem->setTooltip( "Toggle Sidebar" );

		ToolbarItem* hammerTBitem = tb->addToolBarButton( "Hammer" );
		hammerTBitem->setImageIndex( 8 );
		hammerTBitem->setChecked(true);
		hammerTBitem->setTooltip( "Toggle Hammer" );

		ToolbarItem* windowsTBitem = tb->addToolBarButton( "Windows" );
		windowsTBitem->setImageIndex( 9 );
		windowsTBitem->setTooltip( "Show Window List" );

		sideBar_ = new Panel();
		sideBar_->setColor( Color::getColor("white") );
		sideBar_->setWidth( 100 );
		add( sideBar_, AlignLeft );


		hammerBar_ = new Panel();
		hammerBar_->setColor( Color::getColor( "gray105" ) );
		hammerBar_->setHeight( 80 );
		Label* label = new Label();
		label->getFont()->setPointSize( 20 );
		label->setCaption( "Hammer Time!" );
		hammerBar_->add( label, AlignClient );
		add( hammerBar_, AlignBottom );



		//actions

		Action* fileNewAction = new Action();
		addComponent( fileNewAction );
		fileNewAction->addTarget(fileNew);
		fileNewAction->addTarget(newTBitem);
		fileNewAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onFileNew, "ActionsWindow::onFileNew" );

		Action* fileOpenAction = new Action();
		addComponent( fileOpenAction );
		fileOpenAction->addTarget(fileOpen);
		fileOpenAction->addTarget(openTBitem);
		fileOpenAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onFileOpen, "ActionsWindow::onFileOpen" );


		Action* fileSaveAction = new Action();
		addComponent( fileSaveAction );
		fileSaveAction->addTarget(fileSave);
		fileSaveAction->addTarget(saveTBitem);
		
		fileSaveAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onFileSave, "ActionsWindow::onFileSave" );

		fileSaveAction->Update += 
			new EventHandlerInstance<ActionsWindow,ActionEvent>(this, &ActionsWindow::onUpdateFileSave, "ActionsWindow::onUpdateFileSave" );

		

		Action* fileSaveAllAction = new Action();
		addComponent( fileSaveAllAction );
		fileSaveAllAction->addTarget(fileSaveAll);
		fileSaveAllAction->addTarget(saveAllTBitem);
		fileSaveAllAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onFileSaveAll, "ActionsWindow::onFileSaveAll" );
		fileSaveAllAction->Update += 
			new EventHandlerInstance<ActionsWindow,ActionEvent>(this, &ActionsWindow::onUpdateFileSaveAll, "ActionsWindow::onUpdateFileSaveAll" );


		Action* editCopyAction = new Action();
		addComponent( editCopyAction );
		editCopyAction->addTarget(editCopy);
		editCopyAction->addTarget(copyTBitem);
		editCopyAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onEditCopy, "ActionsWindow::onEditCopy" );

		Action* editPasteAction = new Action();
		addComponent( editPasteAction );
		editPasteAction->addTarget(editPaste);
		editPasteAction->addTarget(pasteTBitem);
		
		editPasteAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onEditPaste, "ActionsWindow::onEditPaste" );
		editPasteAction->Update += 
			new EventHandlerInstance<ActionsWindow,ActionEvent>(this, &ActionsWindow::onUpdateEditPaste, "ActionsWindow::onUpdateEditPaste" );

		Action* editUndoAction = new Action();
		addComponent( editUndoAction );
		editUndoAction->addTarget(editUndo);
		editUndoAction->addTarget(undoTBitem);
		
		editUndoAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onEditUndo, "ActionsWindow::onEditUndo" );
		editUndoAction->Update += 
			new EventHandlerInstance<ActionsWindow,ActionEvent>(this, &ActionsWindow::onUpdateEditUndo, "ActionsWindow::onUpdateEditUndo" );



		Action* viewSidebarAction = new Action();
		addComponent( viewSidebarAction );

		viewSidebarAction->addTarget( viewSidebar );
		viewSidebarAction->addTarget( sidebarTBitem );

		viewSidebarAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onViewSidebar, "ActionsWindow::onViewSidebar" );

		viewSidebarAction->Update += 
			new EventHandlerInstance<ActionsWindow,ActionEvent>(this, &ActionsWindow::onUpdateViewSidebar, "ActionsWindow::onUpdateViewSidebar" );


		Action* viewHammerBarAction = new Action();
		addComponent( viewHammerBarAction );

		viewHammerBarAction->addTarget( viewHammer );
		viewHammerBarAction->addTarget( hammerTBitem );

		viewHammerBarAction->Performed += 
			new GenericEventHandler<ActionsWindow>(this, &ActionsWindow::onViewHammerBar, "ActionsWindow::onViewHammerBar" );

		viewHammerBarAction->Update += 
			new EventHandlerInstance<ActionsWindow,ActionEvent>(this, &ActionsWindow::onUpdateViewHammerBar, "ActionsWindow::onUpdateViewHammerBar" );


		canSave_ = false;
		canPaste_ = false;
	}

	virtual ~ActionsWindow(){};

	Panel* sideBar_;
	Panel* hammerBar_;

	bool canSave_;
	bool canPaste_;


	void onFileNew( Event* e ) {
		canSave_ = true;
		Dialog::showMessage( "File New!" );
	}

	void onFileOpen( Event* e ) {
		canSave_ = true;
		Dialog::showMessage( "File Open!" );
	}

	void onFileSave( Event* e ) {
		canSave_ = false;
		Dialog::showMessage( "File Save!" );
	}

	void onUpdateFileSave( ActionEvent* e ) {
		e->setEnabled( canSave_ );
	}

	void onFileSaveAll( Event* e ) {
		canSave_ = false;
		Dialog::showMessage( "File Save All!" );
	}

	void onUpdateFileSaveAll( ActionEvent* e ) {
		e->setEnabled( canSave_ );
	}

	void onEditCopy( Event* e ) {
		canPaste_ = true;
		Dialog::showMessage( "Edit Copy!" );
	}
	

	void onEditPaste( Event* e ) {
		canPaste_ = false;
		Dialog::showMessage( "Edit Paste!" );
	}

	void onUpdateEditPaste( ActionEvent* e ) {
		e->setEnabled( canPaste_ );
	}

	void onEditUndo( Event* e ) {
		Dialog::showMessage( "Edit Undo!" );
	}

	void onUpdateEditUndo( ActionEvent* e ) {
		
	}



	void onViewSidebar( Event* e ) {
		sideBar_->setVisible( !sideBar_->getVisible() );
	}

	void onUpdateViewSidebar( ActionEvent* e ) {
		if ( sideBar_->getVisible() ) {
			e->setState( e->getState() | ToolbarItem::tisPressed );
		}
		else {
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
		e->setChecked( sideBar_->getVisible() );
	}

	void onViewHammerBar( Event* e ) {
		hammerBar_->setVisible( !hammerBar_->getVisible() );
	}

	void onUpdateViewHammerBar( ActionEvent* e ) {
		if ( hammerBar_->getVisible() ) {
			e->setState( e->getState() | ToolbarItem::tisPressed );
		}
		else {
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
		e->setChecked( hammerBar_->getVisible() );
	}


	void onViewWindows( Event* e ) {

	}

};




class ActionsApplication : public Application {
public:

	ActionsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new ActionsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();
		
		return result;
	}

	virtual void idleTime() {

	}
};


int main(int argc, char *argv[])
{
	Application* app = new ActionsApplication( argc, argv );

	Application::main();
	
	return 0;
}


