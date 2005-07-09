#ifndef _VCF_OSXMENUMANAGERPEER_H__
#define _VCF_OSXMENUMANAGERPEER_H__

//OSXMenuManagerPeer.h

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
	class OSXMenuItem;

	class OSXMenuManagerPeer : public MenuManagerPeer {
	public:
		typedef std::map<MenuItem*,OSXMenuItem*> MenuItemMap;


		OSXMenuManagerPeer();
		virtual ~OSXMenuManagerPeer();

		virtual MenuItemPeer* getMenuItemPeer( MenuItem* item );


		virtual void windowActivated( Window* window );

		virtual void windowClosed( Window* window );

		virtual void menuItemChanged( int menuItemEventType, MenuItem* item );
	protected:
	};


};

#endif //_VCF_OSXMENUMANAGERPEER_H__
