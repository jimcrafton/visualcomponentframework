#ifndef _VCF_AGGMENUMANAGERPEER_H__
#define _VCF_AGGMENUMANAGERPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/MenuManagerPeer.h"

namespace VCF {

	class AggMenuManagerPeer : public MenuManagerPeer {
	public:
		virtual MenuItemPeer* getMenuItemPeer( MenuItem* item );

		virtual void destroyMenuItemPeer( MenuItem* item );

		virtual void windowActivated( Window* frame );

		virtual void windowClosed( Window* frame );

		virtual void menuItemChanged( int menuItemEventType, MenuItem* item );
	};
};

#endif //_VCF_AGGMENUMANAGERPEER_H__

/**
$Id$
*/

