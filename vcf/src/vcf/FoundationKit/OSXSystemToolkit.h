#ifndef _VCF_OSXSYSTEMTOOLKIT_H__
#define _VCF_OSXSYSTEMTOOLKIT_H__
//OSXSystemToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class OSXSystemToolkit : public SystemToolkit{
public:

		OSXSystemToolkit();

		virtual ~OSXSystemToolkit();

		virtual ProcessPeer* internal_createProcessPeer( Process* process );

		virtual ProcessIORedirectionPeer* internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process );

		virtual ThreadPeer* internal_createThreadPeer( Thread* thread, bool mainThread );

		virtual ThreadManagerPeer* internal_createThreadManagerPeer();

        virtual RunLoopPeer* internal_createRunLoopPeer( RunLoop* runLoop );

        virtual RunLoopTimerPeer* internal_createRunLoopTimerPeer( RunLoopTimer* timer );
        
        virtual RunLoopSourcePeer* internal_createRunLoopSourcePeer( RunLoopSource* source );
        
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


#endif // _VCF_OSXSYSTEMTOOLKIT_H__

/**
$Id$
*/
