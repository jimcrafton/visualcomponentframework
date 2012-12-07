//MainWindow.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "MainWindow.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"

#include "[!output PROJECT_NAME]Application.h"


[!if HELP_MENU]
#include "[!output PROJECT_NAME]About.h"
[!endif]

using namespace VCF;



MainWindow::MainWindow()
{
	//build main menu
	MenuBar* menuBar = new MenuBar();
	this->setMenuBar( menuBar );
	MenuItem* root = menuBar->getRootMenuItem();
	ClassProcedure1<MenuItemEvent*,MainWindow>* menuItemHandler = NULL;

	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, menuBar );

[!if FILE_MENU]
	DefaultMenuItem* fileOpenProject = new DefaultMenuItem( "&Open...", file, menuBar );
	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onFileOpenProject, "fileOpen" );
	fileOpenProject->MenuItemClicked += menuItemHandler;
	
	
	DefaultMenuItem* fileSaveProject = new DefaultMenuItem( "&Save...", file, menuBar );
	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onFileSaveProject, "fileSave" );	
	fileSaveProject->MenuItemClicked += menuItemHandler;
	

	DefaultMenuItem* sep = new DefaultMenuItem( "", file, menuBar );
	sep->setSeparator( true );
[!endif]	
	DefaultMenuItem* fileExit = new DefaultMenuItem( "E&xit", file, menuBar );
	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onFileExit, "fileExit" );	
	fileExit->MenuItemClicked += menuItemHandler;

[!if UNDO_REDO]
	//edit Undo/Redo support
	DefaultMenuItem* edit = new DefaultMenuItem( "&Edit", root, menuBar );
	DefaultMenuItem* editUndo = new DefaultMenuItem( "Undo", edit, menuBar );
	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onEditUndo, "editUndoClick" );	
	editUndo->MenuItemClicked += menuItemHandler;

	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onEditUndoUpdate, "editUndoUpdate" );	
	editUndo->MenuItemUpdate += menuItemHandler;
	
	
	DefaultMenuItem* editRedo = new DefaultMenuItem( "Redo", edit, menuBar );
	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onEditRedo, "editRedoClick" );	
	editRedo->MenuItemClicked += menuItemHandler;

	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onEditRedoUpdate, "editRedoUpdate" );	
	editRedo->MenuItemUpdate += menuItemHandler;

[!endif]
[!if HELP_MENU]

	//add Help menu
	DefaultMenuItem* help = new DefaultMenuItem( "&Help", root, menuBar );
	DefaultMenuItem* helpAbout = new DefaultMenuItem( "About...", help, menuBar );
	menuItemHandler = new ClassProcedure1<MenuItemEvent*,MainWindow>(this, &MainWindow::onHelpAbout, "helpAbout" );	
	helpAbout->MenuItemClicked += menuItemHandler;

[!endif]
}

MainWindow::~MainWindow()
{
	
}
[!if FILE_MENU]
void MainWindow::onFileOpenProject( MenuItemEvent* e )
{
	CommonFileOpenDialog openDlg;	

	openDlg.addFilter( "All Files", "*.*" );
	
	if ( true == openDlg.execute() ) {
		
	}
	
}

void MainWindow::onFileSaveProject( MenuItemEvent* e )
{
	CommonFileSaveDialog saveDlg;

	if ( true == saveDlg.execute() ) {
		
	}
}

[!endif]
void MainWindow::onFileExit( MenuItemEvent* e )
{
	close();
}

[!if UNDO_REDO]

void MainWindow::onEditUndo( MenuItemEvent* e )
{
	UndoRedoStack* cmdStack = [!output PROJECT_NAME]Application::get[!output PROJECT_NAME]Application()->getCommandStack();
	cmdStack->undo();
}

void MainWindow::onEditUndoUpdate( VCF::MenuItemEvent* e )
{
	MenuItem* itemToUpdate = dynamic_cast<MenuItem*>(e->getSource());
	if ( NULL != itemToUpdate ) {
		UndoRedoStack* cmdStack = [!output PROJECT_NAME]Application::get[!output PROJECT_NAME]Application()->getCommandStack();
		bool hasUndoableCmds = cmdStack->hasUndoableItems();
		if ( true == hasUndoableCmds ) {
			itemToUpdate->setCaption( "Undo \"" + cmdStack->getCurrentUndoCommand()->getName() + "\"" );
		}
		else {
			itemToUpdate->setCaption( "Nothing to Undo" );
		}
		itemToUpdate->setEnabled( hasUndoableCmds );
	}
}

void MainWindow::onEditRedo( MenuItemEvent* e )
{
	UndoRedoStack* cmdStack = [!output PROJECT_NAME]Application::get[!output PROJECT_NAME]Application()->getCommandStack();
	cmdStack->redo();
}

void MainWindow::onEditRedoUpdate( VCF::MenuItemEvent* e )
{
	MenuItem* itemToUpdate = dynamic_cast<MenuItem*>(e->getSource());
	if ( NULL != itemToUpdate ) {
		UndoRedoStack* cmdStack = [!output PROJECT_NAME]Application::get[!output PROJECT_NAME]Application()->getCommandStack();
		bool hasRedoableCmds = cmdStack->hasRedoableItems();
		if ( true == hasRedoableCmds ) {
			itemToUpdate->setCaption( "Redo \"" + cmdStack->getCurrentRedoCommand()->getName() + "\"" );
		}
		else {
			itemToUpdate->setCaption( "Nothing to Redo" );
		}
		itemToUpdate->setEnabled( hasRedoableCmds );
	}
}
[!endif]
[!if HELP_MENU]

void MainWindow::onHelpAbout( MenuItemEvent* e )
{
	[!output PROJECT_NAME]About aboutDlg;

	aboutDlg.showModal();
	
}
[!endif]


