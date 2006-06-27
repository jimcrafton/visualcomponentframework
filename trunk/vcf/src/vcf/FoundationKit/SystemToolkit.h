#ifndef _VCF_SYSTEMTOOLKIT_H__
#define _VCF_SYSTEMTOOLKIT_H__
//SystemToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class ProcessPeer;
class ProcessIORedirectionPeer;
class ProcessWithRedirectedIO;
class ThreadPeer;
class Process;
class Thread;
class Mutex;
class Condition;
class System;
class SystemPeer;
class LocalePeer;
class ResourceBundlePeer;
class RunLoop;
class RunLoopPeer;
class ThreadManagerPeer;

/**
\class SystemToolkit SystemToolkit.h "vcf/FoundationKit/SystemToolkit.h"
The SystemToolkit is and abstract class used to create or 
get access to basic system peer instances, like threads, processes, etc. 
It is a singleton factory for the various platform specific 
peers that are required for the FoundationKit. 

The SystemToolkit is a singleton and is not intended to be created
or deleted directly. It is created as part of the FoundationKit::init()
and deleted as part of the FoundationKit::terminate() call. 

If you are porting to a new platform you will need to derive a new 
class from this one and provide implementations of the various
internal_createXXXPeer methods. 
*/
class FOUNDATIONKIT_API SystemToolkit : public Object{

public:

	static SystemToolkit* create();

	static void terminate();

	

	/**
	*creates a new ProcessPeer instance
	*/
	static ProcessPeer* createProcessPeer( Process* process );

	static ProcessIORedirectionPeer* createProcessIORedirectionPeer( ProcessWithRedirectedIO* process );

	/**
	*creates a new ThreadPeer instance
	*/
	static ThreadPeer* createThreadPeer( Thread* thread, bool mainThread );

	static RunLoopPeer* createRunLoopPeer( RunLoop* runLoop );

	static ThreadManagerPeer* createThreadManagerPeer();

	

	/**
	*creates a new system peer
	*/
	static SystemPeer* createSystemPeer();

	static SemaphorePeer* createSemaphorePeer( int32 initialCount = 1, int32 maxCount = 1 );

	static RegistryPeer* createRegistryPeer( Registry* registry );

	static MutexPeer* createMutexPeer( Mutex* mutex );

    static ConditionPeer* createConditionPeer( Condition* condition );

	static LibraryPeer* createLibraryPeer( Library* library );

	static FilePeer* createFilePeer( File* file );

	static FileStreamPeer* createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType );

	static FileStreamPeer* createFileStreamPeer( File* file );

	static LocalePeer* createLocalePeer();

	static ResourceBundlePeer* createResourceBundlePeer();
protected:
	SystemToolkit();

	virtual ~SystemToolkit();

	/**
	creates a new ProcessPeer instance. 
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.
	*/
	virtual ProcessPeer* internal_createProcessPeer( Process* process ) = 0;

	/**	
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.
	*/
	virtual ProcessIORedirectionPeer* internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process ) = 0;

	/**
	creates a new ThreadPeer instance.
	
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual ThreadPeer* internal_createThreadPeer( Thread* thread, bool mainThread ) = 0;

	virtual RunLoopPeer* internal_createRunLoopPeer( RunLoop* runLoop ) = 0;

	virtual ThreadManagerPeer* internal_createThreadManagerPeer() = 0;

	
	/**
	*creates a new system peer
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual SystemPeer* internal_createSystemPeer() = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual SemaphorePeer* internal_createSemaphorePeer( int32 initialCount = 1, int32 maxCount = 1 ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual RegistryPeer* internal_createRegistryPeer( Registry* registry ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual MutexPeer* internal_createMutexPeer( Mutex* mutex ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
    virtual ConditionPeer* internal_createConditionPeer( Condition* condition ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual LibraryPeer* internal_createLibraryPeer( Library* library ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual FilePeer* internal_createFilePeer( File* file ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual FileStreamPeer* internal_createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual FileStreamPeer* internal_createFileStreamPeer( File* file ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual LocalePeer* internal_createLocalePeer() = 0;

	virtual ResourceBundlePeer* internal_createResourceBundlePeer() = 0;

	/**
	*returns the one and only instance of the system toolkit
	*/
	static SystemToolkit* getSystemToolkit() {
		return systemToolkitInstance;
	}
	static SystemToolkit* systemToolkitInstance;
};

}; //end of namespace VCF


#endif // _VCF_SYSTEMTOOLKIT_H__

/**
$Id$
*/
