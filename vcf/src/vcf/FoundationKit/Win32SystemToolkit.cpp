//Win32SystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ProcessIORedirectionPeer.h"
#include "vcf/FoundationKit/Win32ProcessIORedirector.h"

#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/Win32LocalePeer.h"
#include "vcf/FoundationKit/Win32Condition.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#include "vcf/FoundationKit/Win32RunLoopPeer.h"
#include "vcf/FoundationKit/Win32ThreadManagerPeer.h"


using namespace VCF;


Win32SystemToolkit::Win32SystemToolkit()
{

}

Win32SystemToolkit::~Win32SystemToolkit()
{

}

ProcessPeer* Win32SystemToolkit::internal_createProcessPeer( Process* process )
{
	ProcessPeer* result = NULL;

	result = new Win32ProcessPeer();

	return result;
}

ProcessIORedirectionPeer* Win32SystemToolkit::internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{
	ProcessIORedirectionPeer * result = new Win32ProcessIORedirector();
	result->setProcess( process );

	return result;
}

ThreadPeer* Win32SystemToolkit::internal_createThreadPeer( Thread* thread, bool mainThread )
{
	ThreadPeer* result = NULL;

	return new Win32Thread( thread, mainThread );
}

RunLoopPeer* Win32SystemToolkit::internal_createRunLoopPeer( RunLoop* runLoop )
{
	return new Win32RunLoopPeer( runLoop );
}

ThreadManagerPeer* Win32SystemToolkit::internal_createThreadManagerPeer()
{
	return new Win32ThreadManagerPeer();
}

SystemPeer* Win32SystemToolkit::internal_createSystemPeer()
{
	return new Win32SystemPeer();
}

SemaphorePeer* Win32SystemToolkit::internal_createSemaphorePeer( long initialCount, long maxCount )
{
	return new Win32SemaphorePeer( initialCount, maxCount );
}

RegistryPeer* Win32SystemToolkit::internal_createRegistryPeer( Registry* registry )
{
	return new Win32Registry();
}

MutexPeer* Win32SystemToolkit::internal_createMutexPeer( Mutex* mutex )
{
	return new Win32Mutex();
}

ConditionPeer* Win32SystemToolkit::internal_createConditionPeer( Condition* condition )
{
	return new Win32Condition(condition);
}

LibraryPeer* Win32SystemToolkit::internal_createLibraryPeer( Library* library )
{
	return new Win32LibraryPeer();
}

FilePeer* Win32SystemToolkit::internal_createFilePeer( File* file )
{
	return new Win32FilePeer( file );
}

FileStreamPeer* Win32SystemToolkit::internal_createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType )
{
	return new Win32FileStream( filename, accessType );
}

FileStreamPeer* Win32SystemToolkit::internal_createFileStreamPeer( File* file )
{
	return new Win32FileStream( file );
}

LocalePeer* Win32SystemToolkit::internal_createLocalePeer()
{
	return new Win32LocalePeer();
}

ResourceBundlePeer* Win32SystemToolkit::internal_createResourceBundlePeer()
{
	return new Win32ResourceBundle();
}


/**
$Id$
*/
