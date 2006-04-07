#ifndef _VCF_RUNLOOPPEER_H__
#define _VCF_RUNLOOPPEER_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class RunLoopPeer RunLoopPeer.h "vcf/FoundationKit/RunLoopPeer.h"
*/
class FOUNDATIONKIT_API RunLoopPeer {
public:
	virtual ~RunLoopPeer(){}

	/**
	Run the run for some duration. If duration is NULL then
	run forever	until a stop() is called.
	*/
	virtual void run( const String& mode, const DateTime* duration ) = 0;

	virtual void stop() = 0;

	virtual void postEvent( Event* event, EventHandler* handler, bool deleteHandler ) = 0;

	virtual uint32 addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds ) = 0;

	virtual void removeTimer( uint32 timerID ) = 0;

	virtual OSHandleID getHandleID() = 0;
};

};

#endif //_VCF_RUNLOOPPEER_H__
