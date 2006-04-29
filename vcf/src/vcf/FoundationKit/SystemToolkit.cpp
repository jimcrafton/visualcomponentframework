//SystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;



SystemToolkit* SystemToolkit::create()
{

	if ( NULL == SystemToolkit::systemToolkitInstance ) {
#if defined(VCF_WIN32) && !defined(VCF_DOTNET)
		SystemToolkit::systemToolkitInstance = new Win32SystemToolkit();
#elif defined(VCF_DOTNET)
		SystemToolkit::systemToolkitInstance = new DotNetSystemToolkit();
#elif defined(VCF_POSIX)
		SystemToolkit::systemToolkitInstance = new LinuxSystemToolkit();
#elif defined(VCF_OSX)
		SystemToolkit::systemToolkitInstance = new OSXSystemToolkit();
#endif
		if ( NULL == SystemToolkit::systemToolkitInstance ) {
			throw InvalidPointerException( MAKE_ERROR_MSG_2(String("No Toolkit instantiated!")) );
		}
		SystemToolkit::systemToolkitInstance->init();
	}

	return SystemToolkit::systemToolkitInstance;
}

void SystemToolkit::terminate()
{
	SystemToolkit::systemToolkitInstance->free();
}


SystemToolkit::SystemToolkit()
{

}

SystemToolkit::~SystemToolkit()
{

}

ProcessPeer* SystemToolkit::createProcessPeer( Process* process )
{
	return SystemToolkit::getSystemToolkit()->internal_createProcessPeer( process );
}

ProcessIORedirectionPeer* SystemToolkit::createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{
	return SystemToolkit::getSystemToolkit()->internal_createProcessIORedirectionPeer(process);
}

ThreadPeer* SystemToolkit::createThreadPeer( Thread* thread, bool mainThread )
{
	return SystemToolkit::getSystemToolkit()->internal_createThreadPeer(thread,mainThread);
}

RunLoopPeer* SystemToolkit::createRunLoopPeer( RunLoop* runLoop )
{
	return SystemToolkit::getSystemToolkit()->internal_createRunLoopPeer(runLoop);
}

ThreadManagerPeer* SystemToolkit::createThreadManagerPeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createThreadManagerPeer();
}


SystemPeer* SystemToolkit::createSystemPeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createSystemPeer();
}

SemaphorePeer* SystemToolkit::createSemaphorePeer( long initialCount, long maxCount )
{
	return SystemToolkit::getSystemToolkit()->internal_createSemaphorePeer(initialCount,maxCount);
}

RegistryPeer* SystemToolkit::createRegistryPeer( Registry* registry )
{
	return SystemToolkit::getSystemToolkit()->internal_createRegistryPeer(registry);
}

MutexPeer* SystemToolkit::createMutexPeer( Mutex* mutex )
{
	return SystemToolkit::getSystemToolkit()->internal_createMutexPeer(mutex);
}

ConditionPeer* SystemToolkit::createConditionPeer( Condition* condition )
{
	return SystemToolkit::getSystemToolkit()->internal_createConditionPeer(condition);
}

LibraryPeer* SystemToolkit::createLibraryPeer( Library* library )
{
	return SystemToolkit::getSystemToolkit()->internal_createLibraryPeer(library);
}

FilePeer* SystemToolkit::createFilePeer( File* file )
{
	return SystemToolkit::getSystemToolkit()->internal_createFilePeer( file );
}

FileStreamPeer* SystemToolkit::createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType )
{
	return SystemToolkit::getSystemToolkit()->internal_createFileStreamPeer(filename,accessType);
}

FileStreamPeer* SystemToolkit::createFileStreamPeer( File* file )
{
	return SystemToolkit::getSystemToolkit()->internal_createFileStreamPeer(file);
}

LocalePeer* SystemToolkit::createLocalePeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createLocalePeer();
}

ResourceBundlePeer* SystemToolkit::createResourceBundlePeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createResourceBundlePeer();
}


/**
$Id$
*/
