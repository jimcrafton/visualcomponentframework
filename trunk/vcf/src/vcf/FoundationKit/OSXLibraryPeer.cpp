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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.1  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/10 20:42:07  ddiego
*osx updates
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


