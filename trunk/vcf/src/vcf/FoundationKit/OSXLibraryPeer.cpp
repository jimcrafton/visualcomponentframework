//OSXLibraryPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
//#include <dlfcn.h>


using namespace VCF;

OSXLibraryPeer::OSXLibraryPeer():
libHandle_(NULL)
{

}

OSXLibraryPeer::~OSXLibraryPeer()
{

}


void OSXLibraryPeer::load( const String& libraryFilename )
{
	//for now, till we find a better way, we are going
	//do default to Lazy loading - the alternate is
	//have all the symbols of libary resolved at once,
	//which would mean this call would block till that was
	//done
	/*
	libHandle_ = ::dlopen( libraryFilename.c_str(), RTLD_LAZY );
StringUtils::traceWithArgs( "dlopen( %s ) returned %p\n",
							libraryFilename.c_str(),  libHandle_ );
	if ( NULL == libHandle_ ) {
		String errMessage = dlerror();
		throw RuntimeException( MAKE_ERROR_MSG_2( errMessage ) );
	}
	*/
}

void* OSXLibraryPeer::getFunction( const String& functionName )
{
	void* result = NULL;
	/*
	if ( NULL == libHandle_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "You are trying to get function adress without a valid handle to a library" ) );
	}
	result = dlsym( libHandle_, functionName.c_str() );
StringUtils::traceWithArgs( "error are: %s\n", dlerror() );
*/
	return result;
}

void OSXLibraryPeer::unload()
{
	if ( NULL != libHandle_ ) {
		//dlclose( libHandle_ );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


