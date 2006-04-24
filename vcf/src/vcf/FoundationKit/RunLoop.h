#ifndef _VCF_RUNLOOP_H__
#define _VCF_RUNLOOP_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include <deque>

namespace VCF {

class RunLoopPeer;
class RunLoopSource;
class Thread;

/**
\class PostedEvent RunLoop.h "vcf/FoundationKit/RunLoop.h"
*/
class PostedEvent {
public:
	PostedEvent( Event* event, EventHandler* handler, bool deleteHandler ):
	  event_(event), handler_(handler), deleteHandler_(deleteHandler){}

	PostedEvent( Event* event ):
	  event_(event), handler_(NULL), deleteHandler_(false){}

	Event* event_;
	EventHandler* handler_;
	bool deleteHandler_;
};

/**
\class RunLoop RunLoop.h "vcf/FoundationKit/RunLoop.h"
*/
class FOUNDATIONKIT_API RunLoop {
public:
	enum TimerEvents {
		teTimedOut = CUSTOM_EVENT_TYPES + 5002
	};


	/**
	*/
	Delegate LoopEvents;

	Delegate TimerEvents;



	/**
	*/
	void run();

	/**
	*/
	void run( const String& mode, const DateTime& duration );

	/**
	*/
	void stop();

	/**
	*/
	RunLoopPeer* getPeer();

	/**
	*/
	void addSource( RunLoopSource* source );

	/**
	*/
	void removeSource( RunLoopSource* source );

	/**
	*/
	uint32 addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds );

	uint32 addTimer( const String& mode, uint32 timeoutInMilliSeconds );

	void removeTimer( uint32 timerID );

	/**
	*/
	void postEvent( Event* event );

	/**
	*/
	void postEvent( Event* event, EventHandler* handler, bool deleteHandler=true );


	Thread* getOwningThread() {
		return owningThread_;
	}

	bool isStopped() {
		return stopped_;
	}

	String getCurrentRunMode();

	/**
	This is called repeatedly by the run loop peer in
	it's internal loop code.
	*/
	void internal_executeOnce( const String& mode );

	void internal_cancelled( const String& mode );

	/**
	Called when the peer run loop gets a posted event
	*/
	void internal_processReceivedEvent( PostedEvent* postedEvent );

	/**
	Called by the peer run loop when a timer elapses
	*/
	void internal_processTimer( const String& mode, Object* source, EventHandler* handler );

	friend class Thread;
protected:
	RunLoopPeer* peer_;
	bool stopped_;
	Thread* owningThread_;
	std::vector<RunLoopSource*> sources_;
	std::deque<String> modes_;
	Mutex mutex_;



	/**
	called repeated for each loop iteration of the run loop.
	Each call iterates through all of the sources and calls
	RunLoopSource::perform() on the source instance
	*/
	void doSources();

	void pushCurrentMode( const String& mode );
	void popCurrentMode();

	/**
	*/
	RunLoop( Thread* thread );

	virtual ~RunLoop();
};

};

#endif //_VCF_RUNLOOP_H__
