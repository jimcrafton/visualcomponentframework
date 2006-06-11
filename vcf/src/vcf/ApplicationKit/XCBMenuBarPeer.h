#ifndef _VCF_XCBMENUBAR_H__
#define _VCF_XCBMENUBAR_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/MenuBarPeer.h"

namespace VCF
{

class XCBMenuBarPeer : public MenuBarPeer {
public:
	XCBMenuBarPeer( MenuBar* menuBar);

	virtual void setFrame( Frame* frame );

	virtual void update();

	virtual void setMenuItems( MenuItem* item );

private:
};

};

#endif // _VCF_XCBMENUBAR_H__

/**
$Id$
*/

