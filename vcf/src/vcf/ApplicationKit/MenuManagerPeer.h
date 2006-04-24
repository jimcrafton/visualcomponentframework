#ifndef _VCF_MENUMANAGERPEER_H__
#define _VCF_MENUMANAGERPEER_H__

//MenuManagerPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
/**
\class MenuManagerPeer MenuManagerPeer.h "vcf/ApplicationKit/MenuManagerPeer.h"
*/
	class APPLICATIONKIT_API MenuManagerPeer {
	public:
		virtual ~MenuManagerPeer(){}

		virtual MenuItemPeer* getMenuItemPeer( MenuItem* item ) = 0;

		virtual void destroyMenuItemPeer( MenuItem* item ) = 0;

		virtual void windowActivated( Window* frame ) = 0;

		virtual void windowClosed( Window* frame ) = 0;

		virtual void menuItemChanged( int menuItemEventType, MenuItem* item ) = 0;
	};


};



#endif //_VCF_MENUMANAGERPEER_H__