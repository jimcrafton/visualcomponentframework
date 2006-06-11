#ifndef _VCF_XCBCONTROLCONTEXTPEER_H__
#define _VCF_XCBCONTROLCONTEXTPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/XCBContextPeer.h"

namespace VCF  {

class XCBControlContextPeer : public XCBContextPeer {
public:
	XCBControlContextPeer( ControlPeer* controlPeer );

	virtual ~XCBControlContextPeer();

	virtual void setContext( GraphicsContext* context );

	Control* getOwningControl();

	virtual void checkHandle();

	virtual void releaseHandle();

protected:
	ControlGraphicsContext* owningControlCtx_;
};

}; //end of namespace VCF

#endif // _VCF_XCBCONTROLCONTEXTPEER_H__

/**
$Id$
*/

