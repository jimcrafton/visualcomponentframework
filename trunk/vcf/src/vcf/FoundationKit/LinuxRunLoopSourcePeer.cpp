
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopSource.h>
#include <vcf/FoundationKit/LinuxRunLoopSourcePeer.h>

#include <sys/syscall.h>

using namespace VCF;

LinuxRunLoopSourcePeer::LinuxRunLoopSourcePeer( RunLoopSource* source )
    : owner_( source )
{
	int efd = ::syscall( __NR_eventfd, 0 );
	if( efd < 0 ) {
		throw RuntimeException( strerror( errno ) ) ;
	}
	fileDesc_ = efd;
}

LinuxRunLoopSourcePeer::~LinuxRunLoopSourcePeer()
{
	int result = ::close( fileDesc_ );
	if( result != 0 ) {
			// some error occured, but how to handle it?
			perror( "Couldn't close event file descriptor." );
	}
}

void LinuxRunLoopSourcePeer::perform()
{
	uint64 count;
	int result = ::read(fileDesc_, &count, sizeof(uint64));
	if( result < 0 ) {
		throw RuntimeException( strerror( errno ) );
	}

	owner_->internal_perform();
}

void LinuxRunLoopSourcePeer::fire()
{
	uint64 count = 1;
	int result = ::write( fileDesc_, &count, sizeof(uint64) );
	if( result < 0 ) {
		throw RuntimeException( String(strerror( errno )) );
	}
}
