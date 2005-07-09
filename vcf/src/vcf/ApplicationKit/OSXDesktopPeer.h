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
protected:

};



}; //end of namespace VCF;


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.2.4.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/06 02:56:35  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXDESKTOPPEER_H__


