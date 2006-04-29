#ifndef _VCF_WIN32MENUBAR_H__
#define _VCF_WIN32MENUBAR_H__
//Win32MenuBar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/MenuBarPeer.h"


namespace VCF
{

class Win32MenuBar : public MenuBarPeer
{
public:
	Win32MenuBar( MenuBar* menuBar );

	virtual ~Win32MenuBar();

	virtual void setFrame( Frame* frame );

	virtual void update();

	virtual void setMenuItems( MenuItem* item );
private:
	MenuItem* menuRoot_;
	Frame* frame_;

};

};


#endif // _VCF_WIN32MENUBAR_H__

/**
$Id$
*/
