#ifndef _VCF_X11DESKTOP_H__
#define _VCF_X11DESKTOP_H__
//X11Desktop.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/DesktopPeer.h"


namespace VCF {

/**

*/
class X11Desktop :  public Object, public DesktopPeer {
public:

	X11Desktop( Desktop* desktop );

	virtual ~X11Desktop();

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


	virtual ulong32 desktopGetHandleID();

	virtual ulong32 desktopGetGraphicsContextHandleID();

	virtual void desktopSetDesktop( Desktop* desktop );

	virtual void desktopTranslateToScreenCoords( Control* control, Point* pt );

	virtual void desktopTranslateFromScreenCoords( Control* control, Point* pt );

	virtual ulong32 desktopGetWidth();

	virtual ulong32 desktopGetHeight();

	virtual Rect desktopGetUsableBounds();
protected:

};



}; //end of namespace VCF;


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.2.10.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2002/12/26 04:32:11  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
*Auto generated header for class X11Desktop
*/


#endif // _VCF_X11DESKTOP_H__


