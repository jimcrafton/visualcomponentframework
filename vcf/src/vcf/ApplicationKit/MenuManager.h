#ifndef _VCF_MENUMANAGER_H__
#define _VCF_MENUMANAGER_H__

//MenuManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#if _MSC_VER > 1000
#   pragma once
#endif





namespace VCF {

	class MenuManagerPeer;


	/**
	\par
	The MenuManager class is used by the internals of the framework
	to make sure that menu are handled in a platform neutral way.
	When run on a specific platform work the menu manager peer
	ensures that the menu implementation conforms to the particular 
	platform's standard UI. This is a rather long winded way of saying 
	that on Win32 each window can have a menu (or not), and on Mac OS X
	you just have the main system menu. The MenuManager insulates you
	from having to care one way or the other. 
	\par
	The menu manager is a singleton and cannot be created directly. 
	Developers should never call the MenuManager::create() or 
	MenuManager::terminate() functions - they will be called for you
	by the framework.
	*/
	class APPLICATIONKIT_API MenuManager : public ObjectWithEvents{
	public:
		/**
		Used by the UIToolkit to create the singleton instance of the 
		MenuManager
		*/
		static void create();

		/**
		Used by the UIToolkit to destroy the singleton instance of the 
		MenuManager
		*/
		static void terminate();

		/**
		This is used by internal framework classes to retreive a menu item
		peer for a given menu item. It's entirely possible, depending
		on the platform, that more than one menu item instance may share 
		a single menu item peer.
		*/
		static MenuItemPeer* getMenuItemPeer( MenuItem* item );

		/**
		Register this window with the menu manager
		so that it can take note of change to the
		window's menu bar and adjust accordingly. Note that
		\emphasis only windows may have a menu associated with
		them.
		*/
		static void registerWindow( Window* window );

		/**
		This registers a menu bar with the menu manager. The
		framework takes care of calling this for you, developers
		should not have to call this directly.
		*/
		static void registerMenuBar( MenuBar* menuBar );

		/**
		This registers a popup menu (or context menu) with the menu 
		manager. The framework takes care of calling this for you, 
		developers should not have to call this directly.
		*/
		static void registerPopupMenu( PopupMenu* popupMenu );

		/**
		This returns the main menu instance. 
		*/
		static Menu* getMainMenu();
	protected:
		MenuManager();
		~MenuManager();

		static MenuManager* menuManager;

		Menu* mainMenu_;
		MenuManagerPeer* peer_;
		
		void onWindowActivated( Event* event );
		void onWindowClosed( Event* event );
		void onMenuItemChange( Event* event );
	};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.4  2005/06/08 13:50:29  marcelloptr
*added CVS log section
*
*/


#endif //_VCF_MENUMANAGER_H__


