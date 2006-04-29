//OSXLibraryPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <dlfcn.h>


using namespace VCF;

OSXLibraryPeer::OSXLibraryPeer():
	libHandle_(NULL),
	handleIsBundle_(false)
{

}

OSXLibraryPeer::~OSXLibraryPeer()
{

}


void OSXLibraryPeer::load( const String& libraryFilename )
{
	CFTextString libName;
	libName = libraryFilename;
	CFURLRef url = CFURLCreateWithString( NULL, libName, NULL );
	
	CFBundleRef bundle = CFBundleCreate( NULL, url );
	if ( NULL != bundle ) {
		libHandle_ = bundle;
		handleIsBundle_ = true;
		if ( noErr == CFBundleLoadExecutable( bundle ) ) {			
			CFRelease( bundle );
			libHandle_ = NULL;
		}
	}
	else {
		libHandle_ = dlopen( libraryFilename.ansi_c_str(), RTLD_LAZY );	
	}
	
	CFRelease( url );
	
	if ( NULL == libHandle_ ) {		
		String errMessage = "Error opening bundle from file " + libraryFilename;
		
		if ( !handleIsBundle_ ) {
			const char* err = dlerror();
			if ( NULL != err ) {
				errMessage = err;
			}
		}
		throw RuntimeException( MAKE_ERROR_MSG_2( errMessage ) );
	}
}

void* OSXLibraryPeer::getFunction( const String& functionName )
{
	void* result = NULL;
	
	if ( handleIsBundle_ ) {
		CFBundleRef bundle = (CFBundleRef)libHandle_;
		CFTextString funcName;
		funcName = functionName;
		result = CFBundleGetFunctionPointerForName( bundle, funcName );
	}
	else {
		result = dlsym( libHandle_, functionName.ansi_c_str() );
	}
	
	return result;
}

void OSXLibraryPeer::unload()
{
	if ( NULL != libHandle_ ) {
		if ( handleIsBundle_ ) {
			CFBundleRef bundle = (CFBundleRef)libHandle_;
			CFBundleUnloadExecutable( bundle );
			CFRelease( bundle );
		}
		else {
			dlclose( libHandle_ );
		}
	}
	
	libHandle_ = NULL;
}

OSHandleID OSXLibraryPeer::getHandleID()
{
	return (OSHandleID) libHandle_;
}


/**
$Id$
*/
