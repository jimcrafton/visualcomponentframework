//MenuManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MenuManager.h"
#include "vcf/ApplicationKit/MenuManagerPeer.h"


using namespace VCF;

MenuManager* MenuManager::menuManager = NULL;


MenuManager::MenuManager():
	peer_(NULL),
	mainMenu_(NULL)
{
	peer_ = UIToolkit::createMenuManagerPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create MenuManager peer") );
	}

	mainMenu_ = new MenuBar(); 
}

MenuManager::~MenuManager()
{
	if ( NULL != mainMenu_ ) {
		mainMenu_->free();
	}
	delete peer_;
}

void MenuManager::create()
{
	MenuManager::menuManager = new MenuManager();
}

void MenuManager::terminate()
{
	delete MenuManager::menuManager;
}

MenuItemPeer* MenuManager::getMenuItemPeer( MenuItem* item )
{
	return MenuManager::menuManager->peer_->getMenuItemPeer( item );
}

void MenuManager::registerWindow( Window* window )
{
	VCF_ASSERT( NULL != window );

	EventHandler* ev = MenuManager::menuManager->getEventHandler( "MenuManager::onWindowActivated" );
	if ( NULL == ev ) {
		ev = new GenericEventHandler<MenuManager>( MenuManager::menuManager, &MenuManager::onWindowActivated, "MenuManager::onWindowActivated" );
	}

	window->FrameActivation += ev;

	ev = MenuManager::menuManager->getEventHandler( "MenuManager::onWindowClosed" );
	if ( NULL == ev ) {
		ev = new GenericEventHandler<MenuManager>( MenuManager::menuManager, &MenuManager::onWindowClosed, "MenuManager::onWindowClosed" );
	}
	
	window->FrameClose += ev;

}

void MenuManager::registerMenuBar( MenuBar* menuBar )
{
	VCF_ASSERT( NULL != menuBar );

	EventHandler* ev = MenuManager::menuManager->getEventHandler( "MenuManager::onMenuItemChange" );
	if ( NULL == ev ) {
		ev = new GenericEventHandler<MenuManager>( MenuManager::menuManager, &MenuManager::onMenuItemChange, "MenuManager::onMenuItemChange" );
	}

	menuBar->MenuItemChanged += ev;
}

void MenuManager::registerPopupMenu( PopupMenu* popupMenu )
{
	VCF_ASSERT( NULL != popupMenu );

	EventHandler* ev = MenuManager::menuManager->getEventHandler( "MenuManager::onMenuItemChange" );
	if ( NULL == ev ) {
		ev = new GenericEventHandler<MenuManager>( MenuManager::menuManager, &MenuManager::onMenuItemChange, "MenuManager::onMenuItemChange" );
	}

	popupMenu->MenuItemChanged += ev;
}

void MenuManager::onWindowActivated( Event* event )
{
	Window* window = (Window*)event->getSource();

	peer_->windowActivated( window );
}


void MenuManager::onWindowClosed( Event* event )
{
	Window* window = (Window*)event->getSource();

	peer_->windowClosed( window );
}

void MenuManager::onMenuItemChange( Event* event )
{
	MenuItem* item = (MenuItem*)event->getSource();
	peer_->menuItemChanged( event->getType(), item );
}

Menu* MenuManager::getMainMenu()
{
	return menuManager->mainMenu_;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.5  2005/06/08 13:51:29  marcelloptr
*added CVS log section
*
*/


