#ifndef _VCF_WIN32MENUMANAGERPEER_H__
#define _VCF_WIN32MENUMANAGERPEER_H__

//Win32MenuManagerPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {

	class MenuItem;
	class Win32MenuItem;

	class Win32MenuManagerPeer : public MenuManagerPeer {
	public:
		typedef std::map<MenuItem*,Win32MenuItem*> MenuItemMap;


		Win32MenuManagerPeer();
		virtual ~Win32MenuManagerPeer();

		virtual MenuItemPeer* getMenuItemPeer( MenuItem* item );

		virtual void destroyMenuItemPeer( MenuItem* item );


		virtual void windowActivated( Window* window );

		virtual void windowClosed( Window* window );

		virtual void menuItemChanged( int menuItemEventType, MenuItem* item );
	protected:
		MenuItemMap menuItemsMap_;
	};


};

#endif //_VCF_WIN32MENUMANAGERPEER_H__



