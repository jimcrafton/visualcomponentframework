#ifndef _VCF_GTKMENUBAR_H__
#define _VCF_GTKMENUBAR_H__
//GTKMenuBar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/MenuBarPeer.h"

namespace VCF
{

class GTKMenuBar : public MenuBarPeer {
public:
	GTKMenuBar( MenuBar* menuBar );

	virtual ~GTKMenuBar();

	virtual void setFrame( Frame* frame );

	virtual void update();

	virtual void setMenuItems( MenuItem* item );

private:
};

};

#endif // _VCF_GTKMENUBAR_H__

/**
$Id$
*/

