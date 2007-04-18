#ifndef _VCF_OSXUISHELLPEER_H__
#define _VCF_OSXUISHELLPEER_H__

/*
 Copyright 2000-2007 The VCF Project, Orhun Birsoy.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */

#include "vcf/ApplicationKit/UIShellPeer.h"

namespace VCF {
    
class OSXUIShellPeer : public UIShellPeer {
public:
		OSXUIShellPeer( UIShell* shell );
        
		virtual ~OSXUIShellPeer();
        
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

#endif //_VCF_OSXUISHELLPEER_H__

/**
$Id$
 */
