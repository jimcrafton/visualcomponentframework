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


	virtual uint32 desktopGetHandleID();

	virtual uint32 desktopGetGraphicsContextHandleID();

	virtual void desktopSetDesktop( Desktop* desktop );

	virtual void desktopTranslateToScreenCoords( Control* control, Point* pt );

	virtual void desktopTranslateFromScreenCoords( Control* control, Point* pt );

	virtual uint32 desktopGetWidth();

	virtual uint32 desktopGetHeight();

	virtual Rect desktopGetUsableBounds();
protected:

};



}; //end of namespace VCF;


#endif // _VCF_X11DESKTOP_H__

/**
$Id$
*/
