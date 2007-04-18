#ifndef _VCF_XCBUISHELLPEER_H__
#define _VCF_XCBUISHELLPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/UIShellPeer.h"

namespace VCF {

	class XCBUIShellPeer : public UIShellPeer {
	public:
		XCBUIShellPeer( UIShell* shell );

		virtual ~XCBUIShellPeer();

		virtual void shellBeginPainting( Rect* clippingRect );

		virtual void shellEndPainting();

		virtual bool shellSupportsVirtualDirectories();

		virtual bool shellHasFileSystemDirectory();

		virtual String shellGetDirectory();

		virtual OSHandleID shellGetHandleID();

		virtual OSHandleID shellGetGraphicsContextHandleID();

		virtual void shellSetUIShell( UIShell* shell );

		virtual uint32 shellGetWidth();

		virtual uint32 shellGetHeight();

		virtual Rect shellGetUsableBounds();

		virtual Point getCurrentMousePosition();

	};
};

#endif //_VCF_XCBUISHELLPEER_H__

/**
$Id$
*/

