#ifndef _VCF_GTKMENUMANAGERPEER_H__
#define _VCF_GTKMENUMANAGERPEER_H__

//GTKMenuManagerPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/MenuManagerPeer.h"

namespace VCF {

	class GTKMenuManagerPeer : public MenuManagerPeer {
	public:

		GTKMenuManagerPeer();
		virtual ~GTKMenuManagerPeer();

		virtual MenuItemPeer* getMenuItemPeer( MenuItem* item );

		virtual void destroyMenuItemPeer( MenuItem* item );


		virtual void windowActivated( Window* window );

		virtual void windowClosed( Window* window );

		virtual void menuItemChanged( int menuItemEventType, MenuItem* item );

	protected:
	};
};

#endif //_VCF_GTKMENUMANAGERPEER_H__

/**
$Id$
*/

