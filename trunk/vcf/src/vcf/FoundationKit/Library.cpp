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
	libPeer_->load( libraryFilename );
	currentLibName_ = libraryFilename;

	typedef void (*initFunc)(void);

	initFunc _init = (initFunc) getFunction("_vpl_init");
	if ( NULL != _init ) {
		_init();
	}
	else {
		//don't throw the exception - this is *not* a fatal error
		RuntimeException re( MAKE_ERROR_MSG_2("VCF Package Library does not have a valid _vpl_init function!") );

		System::errorPrint( &re );
	}

}

void Library::unload()
{
	typedef void (*terminateFunc)(void);

	terminateFunc _terminate = (terminateFunc) getFunction("_vpl_terminate");
	if ( NULL != _terminate ) {

		_terminate();
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


