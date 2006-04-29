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

	virtual Point getCurrentMousePosition();
protected:
	Desktop* desktop_;
	HRGN hClipRgn_;
private:
};


}; //end of namespace VCF


#endif // _VCF_WIN32DESKTOP_H__

/**
$Id$
*/
