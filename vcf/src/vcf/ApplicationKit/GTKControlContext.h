#ifndef _VCF_GTKCONTROLCONTEXT_H__
#define _VCF_GTKCONTROLCONTEXT_H__
//GTKControlContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class ControlPeer;

class ControlGraphicsContext;

class Control;

/**

*/
class GTKControlContext : public GTKContext {
public:

	GTKControlContext( ControlPeer* controlPeer );

	virtual ~GTKControlContext();

	virtual void setContext( GraphicsContext* context );

	Control* getOwningControl();

	virtual void checkHandle();

	virtual void releaseHandle();
protected:
	ControlGraphicsContext* owningControlCtx_;
};


};


#endif // _VCF_GTKCONTROLCONTEXT_H__

/**
$Id$
*/
