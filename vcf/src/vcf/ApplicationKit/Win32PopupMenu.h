#ifndef _VCF_WIN32POPUPMENU_H__
#define _VCF_WIN32POPUPMENU_H__
//Win32PopupMenu.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/PopupMenuPeer.h"



namespace VCF {

class Point;

class Control;

class PopupMenu;

class Win32PopupMenu : public PopupMenuPeer, public Object {

public:
	Win32PopupMenu( PopupMenu* popupMenu );

	virtual ~Win32PopupMenu();

	virtual void setControl( Control* control );

	virtual MenuItem* popup( Point* pt );
private:
	Control* control_;
	PopupMenu* popupMenu_;
};

}; //end of namespace VCF


#endif // _VCF_WIN32POPUPMENU_H__

/**
$Id$
*/
