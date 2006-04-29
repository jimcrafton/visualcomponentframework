#ifndef _VCF_OSXDESKTOPPEER_H__
#define _VCF_OSXDESKTOPPEER_H__
//OSXDesktopPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/DesktopPeer.h"


namespace VCF {

/**

*/
class OSXDesktopPeer :  public Object, public DesktopPeer {
public:

	OSXDesktopPeer( Desktop* desktop );

	virtual ~OSXDesktopPeer();

	virtual void desktopBeginPainting( Rect* clippingRect );

	virtual void desktopEndPainting();

	virtual bool desktopSupportsVirtualDirectories();

	virtual bool desktopHasFileSystemDirectory();

	virtual String desktopGetDirectory();

	virtual OSHandleID desktopGetHandleID();

	virtual OSHandleID desktopGetGraphicsContextHandleID();

	virtual void desktopSetDesktop( Desktop* desktop );

	virtual ulong32 desktopGetWidth();

	virtual ulong32 desktopGetHeight();

	virtual Rect desktopGetUsableBounds();
	
	virtual Point getCurrentMousePosition();
protected:

};



}; //end of namespace VCF;


#endif // _VCF_OSXDESKTOPPEER_H__

/**
$Id$
*/
