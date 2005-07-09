//MainWindow.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "MainWindow.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"

#include "$$Root$$Application.h"


$$IF(STD_HELP_MNU)
#include "$$Root$$About.h"
$$ENDIF

using namespace VCF;



MainWindow::MainWindow()
{
$$IF(STD_HELP_MNU || STD_FILE_MNU || UNDO_REDO)
	//build main menu
	MenuBar* menuBar = new MenuBar( this );
	this->setMenuBar( menuBar );
	
	MenuItem* root = menuBar->getRootMenuItem();
	EventHandler* menuItemHandler = NULL;
$$IF(STD_FILE_MNU)
	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, menuBar );

	DefaultMenuItem* fileOpenProject = new DefaultMenuItem( "&Open...", file, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onFileOpenProject, "fileOpen" );
	fileOpenProject->MenuItemClicked += menuItemHandler;
	
	
	DefaultMenuItem* fileSaveProject = new DefaultMenuItem( "&Save...", file, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onFileSaveProject, "fileSave" );	
	fileSaveProject->MenuItemClicked += menuItemHandler;
	

	DefaultMenuItem* sep = new DefaultMenuItem( "", file, menuBar );
	sep->setSeparator( true );
	
	DefaultMenuItem* fileExit = new DefaultMenuItem( "E&xit", file, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onFileExit, "fileExit" );	
	fileExit->MenuItemClicked += menuItemHandler;

$$ENDIF
$$IF(UNDO_REDO)
	//edit Undo/Redo support
	DefaultMenuItem* edit = new DefaultMenuItem( "&Edit", root, menuBar );
	DefaultMenuItem* editUndo = new DefaultMenuItem( "Undo", edit, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onEditUndo, "editUndoClick" );	
	editUndo->MenuItemClicked += menuItemHandler;

	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onEditUndoUpdate, "editUndoUpdate" );	
	editUndo->MenuItemUpdate += menuItemHandler;
	
	
	DefaultMenuItem* editRedo = new DefaultMenuItem( "Redo", edit, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onEditRedo, "editRedoClick" );	
	editRedo->MenuItemClicked += menuItemHandler;

	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onEditRedoUpdate, "editRedoUpdate" );	
	editRedo->MenuItemUpdate += menuItemHandler;

$$ENDIF
$$IF(STD_HELP_MNU)

	//add Help menu
	DefaultMenuItem* help = new DefaultMenuItem( "&Help", root, menuBar );
	DefaultMenuItem* helpAbout = new DefaultMenuItem( "About...", help, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, MainWindow::onHelpAbout, "helpAbout" );	
	helpAbout->MenuItemClicked += menuItemHandler;

$$ENDIF
$$ENDIF
}

MainWindow::~MainWindow()
{
	
}
$$IF(STD_FILE_MNU)
void MainWindow::onFileOpenProject( MenuItemEvent* e )
{
	CommonFileOpen openDlg( this );	
$$BEGINLOOP(EXT_SIZE)
	openDlg.addFilter( "$$EXT_DESC$$", "$$EXT$$" );
$$ENDLOOP	
	openDlg.addFilter( "All Files", "*.*" );
	if ( true == openDlg.execute() ) {
		
	}
	
}

void MainWindow::onFileSaveProject( MenuItemEvent* e )
{
	CommonFileSave saveDlg ( this );
$$BEGINLOOP(EXT_SIZE)
	saveDlg.addFilter( "$$EXT_DESC$$", "$$EXT$$" );
$$ENDLOOP	
	if ( true == saveDlg.execute() ) {
		
	}
}

void MainWindow::onFileExit( MenuItemEvent* e )
{
	close();
}
$$ENDIF
$$IF(UNDO_REDO)

void MainWindow::onEditUndo( MenuItemEvent* e )
{
	UndoRedoStack* cmdStack = $$Root$$Application::get$$Root$$Application()->getCommandStack();
	cmdStack->undo();
}

void MainWindow::onEditUndoUpdate( VCF::MenuItemEvent* e )
{
	MenuItem* itemToUpdate = dynamic_cast<MenuItem*>(e->getSource());
	if ( NULL != itemToUpdate ) {
		UndoRedoStack* cmdStack = $$Root$$Application::get$$Root$$Application()->getCommandStack();
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
	UndoRedoStack* cmdStack = $$Root$$Application::get$$Root$$Application()->getCommandStack();
	cmdStack->redo();
}

void MainWindow::onEditRedoUpdate( VCF::MenuItemEvent* e )
{
	MenuItem* itemToUpdate = dynamic_cast<MenuItem*>(e->getSource());
	if ( NULL != itemToUpdate ) {
		UndoRedoStack* cmdStack = $$Root$$Application::get$$Root$$Application()->getCommandStack();
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
$$ENDIF
$$IF(STD_HELP_MNU)

void MainWindow::onHelpAbout( MenuItemEvent* e )
{
	$$Root$$About aboutDlg;

	aboutDlg.showModal();
	
}
$$ENDIF


