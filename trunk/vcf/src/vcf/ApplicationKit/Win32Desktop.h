#ifndef _VCF_WIN32DESKTOP_H__
#define _VCF_WIN32DESKTOP_H__
//Win32Desktop.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/DesktopPeer.h"



namespace VCF  {

/**
*Class Win32Desktop documentation
*/
class Win32Desktop : public Object, public DesktopPeer {
public:
	Win32Desktop( Desktop* desktop );

	virtual ~Win32Desktop();

	/**
	*Prepares the desktop for painting.
	*MUST be called before calling getContext(), or errors
	*may occur
	*@param Rect* specifies a rectangular region to clip
	*the drawing to. The rectangles coords are screen coords.
	*/
	virtual void desktopBeginPainting( Rect* clippingRect );

	/**
	*called after finished painting on the desktop
	*allows for native Windowing system cleanup to happen
	*/
	virtual void desktopEndPainting();

	virtual bool desktopSupportsVirtualDirectories();

	virtual bool desktopHasFileSystemDirectory();

	virtual String desktopGetDirectory();

	virtual OSHandleID desktopGetGraphicsContextHandleID();

	virtual OSHandleID desktopGetHandleID();

	virtual void desktopSetDesktop( Desktop* desktop );

	virtual void desktopTranslateToScreenCoords( Control* control, Point* pt );

	virtual void desktopTranslateFromScreenCoords( Control* control, Point* pt );

	virtual ulong32 desktopGetWidth();

	virtual ulong32 desktopGetHeight();

	virtual Rect desktopGetUsableBounds();
protected:
	Desktop* desktop_;
	HRGN hClipRgn_;
private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:11:15  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.14.3  2003/01/08 00:19:46  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7.14.2  2002/12/30 00:24:12  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.7.14.1  2002/12/29 00:59:23  marcelloptr
*Minor fixes
*
*Revision 1.7  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/27 15:52:19  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32DESKTOP_H__


