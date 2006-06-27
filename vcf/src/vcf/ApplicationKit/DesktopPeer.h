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

	virtual uint32 desktopGetWidth() = 0;

	virtual uint32 desktopGetHeight() = 0;

	virtual Rect desktopGetUsableBounds() = 0;

	virtual Point getCurrentMousePosition() = 0;
};


}; //end of namespace VCF


#endif // _VCF_DESKTOPPEER_H__

/**
$Id$
*/
