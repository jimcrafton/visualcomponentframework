//LinuxSystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ProcessIORedirectionPeer.h"
#include "vcf/FoundationKit/LinuxProcessIORedirector.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/LinuxLocalePeer.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/LinuxResourceBundle.h"
#include "vcf/FoundationKit/PosixThreadManagerPeer.h"
#include "vcf/FoundationKit/LinuxRunLoopPeer.h"


using namespace VCF;

LinuxSystemToolkit::LinuxSystemToolkit()
{}

LinuxSystemToolkit::~LinuxSystemToolkit()
{}

ProcessPeer* LinuxSystemToolkit::internal_createProcessPeer( Process* process )
{
	return new LinuxProcessPeer();
}

ThreadPeer* LinuxSystemToolkit::internal_createThreadPeer( Thread* thread, bool mainThread )
{
	return new PosixThread( thread, mainThread );
}

RunLoopPeer* LinuxSystemToolkit::internal_createRunLoopPeer( RunLoop* runLoop )
{
    return new LinuxRunLoopPeer( runLoop );
}

ThreadManagerPeer* LinuxSystemToolkit::internal_createThreadManagerPeer()
{
    return new PosixThreadManagerPeer();
}

SystemPeer* LinuxSystemToolkit::internal_createSystemPeer()
{
	return new LinuxSystemPeer();
}

SemaphorePeer* LinuxSystemToolkit::internal_createSemaphorePeer( int32 initialCount,
                                                                 int32 maxCount )
{
	return new LinuxSemaphorePeer( initialCount, maxCount );
}

RegistryPeer* LinuxSystemToolkit::internal_createRegistryPeer( Registry* registry )
{
	return new LinuxRegistry();
}

MutexPeer* LinuxSystemToolkit::internal_createMutexPeer( Mutex* mutex )
{
	return new PosixMutex();
}

ConditionPeer*
LinuxSystemToolkit::internal_createConditionPeer( Condition* condition )
{
	return new PosixCondition( condition );
}

LibraryPeer* LinuxSystemToolkit::internal_createLibraryPeer( Library* library )
{
	return new LinuxLibraryPeer();
}

FilePeer* LinuxSystemToolkit::internal_createFilePeer( File* file )
{
	return new LinuxFilePeer( file );
}

FileStreamPeer*
LinuxSystemToolkit::internal_createFileStreamPeer( const String& filename,
                                                   const FileStreamAccessType& accessType )
{
	return new LinuxFileStream( filename, accessType );
}

FileStreamPeer* LinuxSystemToolkit::internal_createFileStreamPeer( File* file )
{
	return new LinuxFileStream( file );
}

ProcessIORedirectionPeer* LinuxSystemToolkit::internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{
	ProcessIORedirectionPeer * result = new LinuxProcessIORedirector();
	result->setProcess( process );
	return result;
}

LocalePeer* LinuxSystemToolkit::internal_createLocalePeer()
{
	return new LinuxLocalePeer();
}

ResourceBundlePeer* LinuxSystemToolkit::internal_createResourceBundlePeer()
{
	return new LinuxResourceBundle();
}


/**
$Id$
*/
