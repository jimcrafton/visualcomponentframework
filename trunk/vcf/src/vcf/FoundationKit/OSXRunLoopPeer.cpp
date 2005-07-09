//OSXRunLoopPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/OSXRunLoopPeer.h"



using namespace VCF;

OSXRunLoopPeer::OSXRunLoopPeer( RunLoop* runLoop ):
	runLoop_(runLoop)
{

}

OSXRunLoopPeer::~OSXRunLoopPeer()
{
	removeAll();
}

void OSXRunLoopPeer::run( const String& mode, const DateTime* duration )
{
	
}

uint32 OSXRunLoopPeer::addTimer( const String& mode, 
								  Object* source, 
								  EventHandler* handler, 
								  uint32 timeoutInMilliSeconds )
{
	uint32 result = 0;

	return result;
}

void OSXRunLoopPeer::removeTimer( uint32 timerID )
{
	
}

void OSXRunLoopPeer::removeAll()
{
	
}

void OSXRunLoopPeer::stop()
{	

}

OSHandleID OSXRunLoopPeer::getHandleID()
{
	return NULL;
}

void OSXRunLoopPeer::postEvent( Event* event, EventHandler* handler, bool deleteHandler )
{
	PostedEvent* pe = new PostedEvent( event, handler, deleteHandler );
	
}
