#ifndef _VCF_WIN32SYSTEMTOOLKIT_H__
#define _VCF_WIN32SYSTEMTOOLKIT_H__
//Win32SystemToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Win32SystemToolkit : public SystemToolkit{
public:

	Win32SystemToolkit();

	virtual ~Win32SystemToolkit();

	/**
	*creates a new ProcessPeer instance
	*/
	virtual ProcessPeer* internal_createProcessPeer( Process* process );

	virtual ProcessIORedirectionPeer* internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process );

	/**
	*creates a new ThreadPeer instance
	*/
	virtual ThreadPeer* internal_createThreadPeer( Thread* thread, bool mainThread );

	virtual RunLoopPeer* internal_createRunLoopPeer( RunLoop* runLoop );

	virtual ThreadManagerPeer* internal_createThreadManagerPeer();

	/**
	*creates a new system peer
	*/
	virtual SystemPeer* internal_createSystemPeer();

	virtual SemaphorePeer* internal_createSemaphorePeer( int32 initialCount, int32 maxCount );

	virtual RegistryPeer* internal_createRegistryPeer( Registry* registry );

	virtual MutexPeer* internal_createMutexPeer( Mutex* mutex );

	virtual ConditionPeer* internal_createConditionPeer( Condition* condition );

	virtual LibraryPeer* internal_createLibraryPeer( Library* library );

	virtual FilePeer* internal_createFilePeer( File* file );

	virtual FileStreamPeer* internal_createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType );

	virtual FileStreamPeer* internal_createFileStreamPeer( File* file );

	virtual LocalePeer* internal_createLocalePeer();

	virtual ResourceBundlePeer* internal_createResourceBundlePeer();
};


};


#endif // _VCF_WIN32SYSTEMTOOLKIT_H__

/**
$Id$
*/
