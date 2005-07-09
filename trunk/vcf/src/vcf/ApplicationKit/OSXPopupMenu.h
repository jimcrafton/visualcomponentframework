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

	virtual void popup( Point* pt );
private:
	Control* control_;
	PopupMenu* popupMenu_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*/


#endif // _VCF_OSXPOPUPMENU_H__


