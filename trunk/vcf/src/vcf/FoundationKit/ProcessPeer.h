#ifndef _VCF_PROCESSPEER_H__
#define _VCF_PROCESSPEER_H__
//ProcessPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_WAITABLE_H__
#include "vcf/FoundationKit/Waitable.h"
#endif


namespace VCF {

/**
\class ProcessPeer ProcessPeer.h "vcf/FoundationKit/ProcessPeer.h"
*a peer class that wraps working with processes
*on OS's
*/
class FOUNDATIONKIT_API ProcessPeer {

public:
	ProcessPeer() {} ;

	virtual ~ProcessPeer() {};

	/**
	*returns an int that uniquely identifies the process on a given machine
	*/
	virtual int getProcessID() = 0;

	/**
	*returns the process's main thread ID
	*/
	virtual int getProcessThreadID() = 0;

	/**
	*creates a new process specified by the fully
	*qualified file name in the processName argument.
	*@param String the fully qualified file name of
	*process to start. This must represent an actual
	*executable file
	*@return bool returns true if the process was successfully started
	*otherwise false.
	*/
	virtual bool createProcess( const String& processName, const String& arguments ) = 0;

	/**
	*returns the fully qualified file name of the process the
	*object represents.
	*/
	virtual String getProcessFileName() = 0;

	virtual OSHandleID getHandleID() = 0;

	virtual uint32 terminate() = 0;

	virtual Waitable::WaitResult wait( uint32 milliseconds ) = 0;

	virtual Waitable::WaitResult wait() = 0;
};

}; //end of namespace VCF


#endif // _VCF_PROCESSPEER_H__

/**
$Id$
*/
