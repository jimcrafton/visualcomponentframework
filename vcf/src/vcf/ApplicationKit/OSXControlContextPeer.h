#ifndef _VCF_OSXCONTROLCONTEXTPEER_H__
#define _VCF_OSXCONTROLCONTEXTPEER_H__
//OSXControlContextPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class ControlPeer;

class ControlGraphicsContext;

class Control;

/**

*/
class OSXControlContextPeer : public OSXContext {
public:

	OSXControlContextPeer( ControlPeer* controlPeer );

	virtual ~OSXControlContextPeer();

	virtual void setContext( GraphicsContext* context );

	Control* getOwningControl();

	virtual void checkHandle();

	virtual void releaseHandle();
protected:
	ControlGraphicsContext* owningControlCtx_;
};


};


#endif // _VCF_OSXCONTROLCONTEXTPEER_H__

/**
$Id$
*/
