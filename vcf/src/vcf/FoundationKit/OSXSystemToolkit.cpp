//OSXSystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/OSXLocalePeer.h"

using namespace VCF;


OSXSystemToolkit::OSXSystemToolkit()
{

}

OSXSystemToolkit::~OSXSystemToolkit()
{

}

ProcessPeer* OSXSystemToolkit::internal_createProcessPeer( Process* process )
{
	ProcessPeer* result = NULL;

	result = new OSXProcessPeer();

	return result;
}

ThreadPeer* OSXSystemToolkit::internal_createThreadPeer( Thread* thread )
{
	return new OSXThread( thread );
}

SystemPeer* OSXSystemToolkit::internal_createSystemPeer()
{
	return new OSXSystemPeer();
}

SemaphorePeer* OSXSystemToolkit::internal_createSemaphorePeer( long initialCount, long maxCount )
{
	return new OSXSemaphore( initialCount, maxCount );
}

RegistryPeer* OSXSystemToolkit::internal_createRegistryPeer( Registry* registry )
{
	return NULL;//new LinuxRegistry();
}

MutexPeer* OSXSystemToolkit::internal_createMutexPeer( Mutex* mutex )
{
	return new OSXMutex(  );
}

ConditionPeer* OSXSystemToolkit::internal_createConditionPeer( Condition* condition )
{
	return new OSXConditionPeer(condition);
}

LibraryPeer* OSXSystemToolkit::internal_createLibraryPeer( Library* library )
{
	return NULL;//new LinuxLibraryPeer();
}

FilePeer* OSXSystemToolkit::internal_createFilePeer( File* file )
{
	return new OSXFilePeer( file );
}

FileStreamPeer* OSXSystemToolkit::internal_createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType )
{
	return new OSXFileStream( filename, accessType );
}

FileStreamPeer* OSXSystemToolkit::internal_createFileStreamPeer( File* file )
{
	return new OSXFileStream( file );
}

ProcessIORedirectionPeer* OSXSystemToolkit::internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{

	//result->setProcess( process );
	return 	NULL;//result;
}

LocalePeer* OSXSystemToolkit::internal_createLocalePeer()
{
    return new OSXLocalePeer();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/29 03:55:21  ddiego
*osx updates
*
*Revision 1.1.2.7  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


