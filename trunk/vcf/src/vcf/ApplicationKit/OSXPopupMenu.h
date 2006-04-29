#ifndef _VCF_OSXPOPUPMENU_H__
#define _VCF_OSXPOPUPMENU_H__
//OSXPopupMenu.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/PopupMenuPeer.h"



namespace VCF {

class Point;

class Control;

class PopupMenu;

class OSXPopupMenu : public PopupMenuPeer, public Object {

public:
	OSXPopupMenu( PopupMenu* popupMenu );

	virtual ~OSXPopupMenu();

	virtual void setControl( Control* control );

	virtual MenuItem* popup( Point* pt );
private:
	Control* control_;
	PopupMenu* popupMenu_;
};

}; //end of namespace VCF


#endif // _VCF_OSXPOPUPMENU_H__

/**
$Id$
*/
