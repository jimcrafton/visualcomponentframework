//Library.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


Library::Library( const String& libraryName, const bool& autoUnloadLib )
{
	currentLibName_ = libraryName;	

	autoUnloadLib_ = autoUnloadLib;
	init();
}

Library::~Library()
{
	if ( NULL != libPeer_ ){
		if ( true == autoUnloadLib_ ){
			try {
				unload();
			}
			catch (...){
				StringUtils::trace( "failed to unload the libary - probably alread unloaded" );
			}
		}
		delete libPeer_;
		libPeer_ = NULL;
	}
}


void Library::init()
{
	libPeer_ = NULL;


	libPeer_ = SystemToolkit::createLibraryPeer( this );
	if ( NULL == libPeer_ ) {
		throw NoPeerFoundException();
	}

	if ( !currentLibName_.empty() ){
		try {
			load( currentLibName_ );
		}
		catch (...) {
			unload();
		}
	}
}

void Library::load( const String& libraryFilename )
{
	String fullLibraryName = libraryFilename;

	{
		try {
			//does this file exist?
			//probably won't if we have passed in 
			//just the .dll name (i.e. "foo.dll") and 
			//are relying on the path to fill in teh rest
			//if that's the case don't assume it's a bundle
			if ( File::exists( libraryFilename ) ) {
				File libFile(libraryFilename);			
				if ( libFile.isDirectory() ) {
					
					fullLibraryName = System::getExecutableNameFromBundlePath( libraryFilename );			
					
					if ( fullLibraryName.empty() ) {
						throw RuntimeException( MAKE_ERROR_MSG_2("Invalid file name. Points to a directory with no program/library information available.") );
					}
				}
			}
		}
		catch ( ... ) {
			//assume it's not a directory :)
			//move on...
		}
	}	


	libPeer_->load( fullLibraryName );
	
	currentLibName_ = fullLibraryName;

	typedef void (*initFunc)(OSHandleID);

	initFunc _init = NULL;
	try {
		_init = (initFunc) getFunction( L"_vpl_init" );
	}
	catch ( BasicException& e ) {
		System::errorPrint( &e );
	}
	if ( NULL != _init ) {
		_init( libPeer_->getHandleID() );
	}
	else {
		//don't throw the exception - this is *not* a fatal error
		RuntimeException re( MAKE_ERROR_MSG_2("VCF Package Library does not have a valid _vpl_init function!") );

		System::errorPrint( &re );
	}

}

void Library::unload()
{
	typedef void (*terminateFunc)(OSHandleID);

	terminateFunc _terminate = NULL;

	try {
		_terminate = (terminateFunc) getFunction("_vpl_terminate");
	}
	catch  ( BasicException& e ) {
		System::errorPrint( &e );
	}

	if ( NULL != _terminate ) {

		_terminate( libPeer_->getHandleID() );
	}
	else {
		//don't throw the exception - this is *not* a fatal error
		RuntimeException re( MAKE_ERROR_MSG_2("VCF Package Library does not have a valid _vpl_terminate function!") );

		System::errorPrint( &re );
	}

	libPeer_->unload();
}

void* Library::getFunction( const String& functionName )
{
	return libPeer_->getFunction( functionName );
}


/**
$Id$
*/
