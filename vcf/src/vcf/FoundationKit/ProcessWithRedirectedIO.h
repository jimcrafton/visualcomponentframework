#ifndef _VCF_PROCESSWITHREDIRECTEDIO_H__
#define _VCF_PROCESSWITHREDIRECTEDIO_H__
//ProcessWithRedirectedIO.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_OUTPUTREADYEVENT_H__
#	include "vcf/FoundationKit/OutputReadyEvent.h"
#endif // _VCF_OUTPUTREADYEVENT_H__

#ifndef _VCF_PROCESSIOREDIRECTIONPEER_H__
#	include "vcf/FoundationKit/ProcessIORedirectionPeer.h"
#endif // _VCF_PROCESSIOREDIRECTIONPEER_H__



namespace VCF {

	class ProcessIORedirectionPeer;

	/**
	\class ProcessWithRedirectedIO ProcessWithRedirectedIO.h "vcf/FoundationKit/ProcessWithRedirectedIO.h"
	This class represents a process that has it's IO redirected so that when
	there is new data available an event is fired to any registered event
	handlers. Currently only output is captured and redirected.
	You can register an event handler with the addOutputReadyHandler() method.
	To start the process either call createProcess() or construct the process
	and pass in a filename/commandline to the constructor.
	*/
	class FOUNDATIONKIT_API ProcessWithRedirectedIO : public Object {
	public:
		/**
		Constructs a ProcessWithRedirectedIO. Does NOT actually start the
		process.
		*/
		ProcessWithRedirectedIO();

		/**
		Constructs a ProcessWithRedirectedIO. It will then
		call the createProcess() with the processName passed in.
		if createProcess() returns false then an RuntimeException
		will be thrown
		*/
		ProcessWithRedirectedIO( const String& processName, const String& arguments );

		virtual ~ProcessWithRedirectedIO();


		/**
		@delegate OutputReady fires an OutputReadyEvent. This is 
		fired by the framework, specifically the ProcessIORedirectionPeer,
		whenever data has become available and read to read. The peer
		will allocate the data in the form of a string (it's assumed to
		be text format). 
		\note Please note that when data is a ready and the the new event 
		is fired, at least in the Win32 implementation, this event will
		be fired in the context of a different thread than the one in which 
		the ProcessWithRedirectedIO	was created in.
		@event OutputReadyEvent
		@eventtype 
		*/
		DELEGATE(OutputReady);

		/**
		Returns the ID of the process
		*/
		int getID();

		/**
		returns the processes's main thread ID
		*/
		int getThreadID();

		/**
		*creates/runs the process
		@param String the name of the process to run.
		createProcess() will block till the process is finished running.
		@param arguments the arguments, or command line, to pass to the process
		*@return bool indicates wether the process creation was successful. If the
		process was successful then it returns true. If not then it returns false.
		*/
		bool createProcess( const String& processName, const String& arguments );

		/**
		returns the name of the process including any commandline supplied.
		*/
		String getName();

		/**
		returns the current peer instance. Should NEVER be NULL as the constructors
		should throw exceptions if a NULL peer is returned from the SystemToolkit
		*/
		ProcessIORedirectionPeer* getPeer() {
			return processPeer_;
		}

		/**
		adds a new output ready handler. Please note (for at least Win32 implementations,
		when data is a ready and the the new event is fired, this will happen in the
		context of a different thread than the one in which the ProcessWithRedirectedIO
		was created in.
		@deprecated - use the OutputReady delegate directly.
		*/
		void addOutputReadyHandler( EventHandler* eventHandler ) {
			OutputReady += eventHandler;
		}

		/**
		@deprecated - use the OutputReady delegate directly.
		*/
		void removeOutputReadyHandler( EventHandler* eventHandler ) {
			OutputReady -= eventHandler;
		}

		uint32 terminate();
	protected:
		ProcessIORedirectionPeer* processPeer_;
	};
};


#endif // _VCF_PROCESSWITHREDIRECTEDIO_H__

/**
$Id$
*/
