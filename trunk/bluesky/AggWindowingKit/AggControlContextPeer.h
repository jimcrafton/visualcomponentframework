#ifndef _VCF_XCBCONTROLCONTEXTPEER_H__
#define _VCF_XCBCONTROLCONTEXTPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "AggGraphicsPeers.h"

namespace VCF  {

class AggControlContextPeer : public AggContextPeer {
public:
	AggControlContextPeer( ControlPeer* controlPeer );

	virtual ~AggControlContextPeer();

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

