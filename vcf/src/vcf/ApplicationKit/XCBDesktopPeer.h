#ifndef _VCF_XCBDESKTOPPEER_H__
#define _VCF_XCBDESKTOPPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/DesktopPeer.h"

namespace VCF {

	class XCBDesktopPeer : public DesktopPeer {
	public:
		XCBDesktopPeer( Desktop* desktop );

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

	};
};

#endif //_VCF_XCBDESKTOPPEER_H__

/**
$Id$
*/

