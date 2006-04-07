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
		load( currentLibName_ );
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
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.1  2005/09/03 17:13:23  ddiego
*added a new argument to _vpl_init and _vpl_terminate functions.
*
*Revision 1.5  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.2  2005/02/27 01:46:10  ddiego
*fixed bug in testing whether a path should be loaded as a bundle.
*added some additional rtti info for certain classes in app kit.
*
*Revision 1.3.2.1  2004/12/19 07:09:19  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.2.2.2  2004/09/15 04:41:23  ddiego
*made some minor changes to the SharedLibraries example, and the init and term code of the Library class.
*
*Revision 1.2.2.1  2004/08/27 19:55:44  marcelloptr
*Color changes
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.11.6.2  2004/04/10 04:37:19  ddiego
*added a MIMType class that parses mime types.
*
*Revision 1.11.6.1  2004/04/09 06:09:06  ddiego
*nybbles and bytes
*
*Revision 1.11  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.10.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10  2003/05/17 20:37:41  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.16.3  2003/04/07 03:39:33  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.9.16.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.16.1  2003/03/12 03:12:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.8  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


