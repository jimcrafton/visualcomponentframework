#ifndef _VCF_DESKTOPPEER_H__
#define _VCF_DESKTOPPEER_H__
//DesktopPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class Desktop;


/**
\class DesktopPeer DesktopPeer.h "vcf/ApplicationKit/DesktopPeer.h"
*Class DesktopPeer interface documentation
*/
class APPLICATIONKIT_API DesktopPeer : public Interface {
public:
	virtual ~DesktopPeer(){};

	/**
	*Prepares the desktop for painting.
	*MUST be called before calling getContext(), or errors
	*may occur
	*@param Rect* specifies a rectangular region to clip
	*the drawing to. The rectangles coords are screen coords.
	*/
	virtual void desktopBeginPainting( Rect* clippingRect ) = 0;

	/**
	*called after finished painting on the desktop
	*allows for native Windowing system cleanup to happen
	*/
	virtual void desktopEndPainting() = 0;

	virtual bool desktopSupportsVirtualDirectories() = 0;

	virtual bool desktopHasFileSystemDirectory() = 0;

	virtual String desktopGetDirectory() = 0;


	virtual OSHandleID desktopGetHandleID() = 0;

	virtual OSHandleID desktopGetGraphicsContextHandleID() = 0;

	virtual void desktopSetDesktop( Desktop* desktop ) = 0;

	virtual ulong32 desktopGetWidth() = 0;

	virtual ulong32 desktopGetHeight() = 0;

	virtual Rect desktopGetUsableBounds() = 0;

	virtual Point getCurrentMousePosition() = 0;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.3.2.1  2006/02/15 05:14:33  ddiego
*more browser code.
*
*Revision 1.3  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.9.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/04/17 04:29:48  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.8  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.20.1  2002/12/26 04:32:11  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DESKTOPPEER_H__


