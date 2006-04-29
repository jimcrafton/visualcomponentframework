//LinuxLibraryPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <dlfcn.h>

using namespace VCF;

LinuxLibraryPeer::LinuxLibraryPeer()
		: libHandle_( 0 )
{}

LinuxLibraryPeer::~LinuxLibraryPeer()
{}

void LinuxLibraryPeer::load( const String& libraryFilename )
{
	System::println("Opening "+libraryFilename);
	//for now, till we find a better way, we are going
	//do default to Lazy loading - the alternate is
	//have all the symbols of libary resolved at once,
	//which would mean this call would block till that was
	//done
	libHandle_ = ::dlopen( libraryFilename.ansi_c_str(), RTLD_LAZY );

	StringUtils::traceWithArgs( Format("dlopen( %s ) returned %p\n") %
								 libraryFilename %  libHandle_ );

	if ( ! libHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( dlerror() ) );
	}
}

void* LinuxLibraryPeer::getFunction( const String& functionName )
{
	void* result = NULL;

	if ( ! libHandle_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2(
		                                   "You are trying to get function adress "
		                                   "without a valid handle to a library" ) );
	}
	result = dlsym( libHandle_, functionName.ansi_c_str() );
	if(result == NULL) {
		StringUtils::traceWithArgs( Format( "error are: %s\n" ) % String(dlerror()) );
	}
	return result;
}

OSHandleID LinuxLibraryPeer::getHandleID()
{
    return libHandle_;
}

void LinuxLibraryPeer::unload()
{
	if ( libHandle_ ) {
		dlclose( libHandle_ );
	}
}


/**
$Id$
*/
