#ifndef _VCF_OSXMENUBAR_H__
#define _VCF_OSXMENUBAR_H__
//OSXMenuBar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/MenuBarPeer.h"


namespace VCF  {

class OSXMenuBar : public MenuBarPeer {
public:
	OSXMenuBar( MenuBar* menuBar );

	virtual ~OSXMenuBar();

	virtual void setFrame( Frame* frame );

	virtual void update();

	virtual void setMenuItems( MenuItem* item );
private:
	MenuItem* menuRoot_;
	Frame* frame_;

};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*/

#endif //_VCF_OSXMENUBAR_H__

