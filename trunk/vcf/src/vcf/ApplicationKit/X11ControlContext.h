#ifndef _VCF_X11CONTROLCONTEXT_H__
#define _VCF_X11CONTROLCONTEXT_H__
//X11ControlContext.h

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
class X11ControlContext : public X11Context{
public:

	X11ControlContext( ControlPeer* controlPeer );

	virtual ~X11ControlContext();

	virtual void setContext( GraphicsContext* context );

	Control* getOwningControl();

	virtual void checkHandle();

	virtual void releaseHandle();
protected:
	ControlGraphicsContext* owningControlCtx_;
};


};


#endif // _VCF_X11CONTROLCONTEXT_H__

/**
$Id$
*/
