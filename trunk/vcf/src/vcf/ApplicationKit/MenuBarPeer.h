#ifndef _VCF_MENUBARPEER_H__
#define _VCF_MENUBARPEER_H__
//MenuBarPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Frame;

class MenuItem;

/**
\class MenuBarPeer MenuBarPeer.h "vcf/ApplicationKit/MenuBarPeer.h"
*/
class APPLICATIONKIT_API MenuBarPeer {
public:
	virtual ~MenuBarPeer(){};

	/**
	*sets the Frame the menu bar is attached to
	*/
	virtual void setFrame( Frame* frame ) = 0;

	/**
	*updates the visual display of the menu bar area
	*/
	virtual void update() = 0;

	virtual void setMenuItems( MenuItem* item ) = 0;

};

};


#endif // _VCF_MENUBARPEER_H__

/**
$Id$
*/
