//Win32LibraryPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

Win32LibraryPeer::Win32LibraryPeer()
{
	libHandle_ = NULL;
}

Win32LibraryPeer::~Win32LibraryPeer()
{
	libHandle_ = NULL;
}


void Win32LibraryPeer::load( const String& libraryFilename )
{
	if ( System::isUnicodeEnabled() ) {
		libHandle_ = LoadLibraryW( libraryFilename.c_str() );
	}
	else {
		libHandle_ = LoadLibraryA( libraryFilename.ansi_c_str() );
	}


	if ( NULL == libHandle_ ){
		String error = "Win32LibraryPeer::load() exception: \nError loading \"" + libraryFilename + "\"\n" +
				VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( error );
	}
}

void* Win32LibraryPeer::getFunction( const String& functionName )
{
	void* result = NULL;

	if ( NULL == libHandle_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	}

	result = (void*)GetProcAddress( libHandle_, functionName.ansi_c_str() );


	if ( NULL == result ){
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( error );
	}

	return result;
}

void Win32LibraryPeer::unload()
{
	if ( NULL == libHandle_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	}

	BOOL freeLibResult = FreeLibrary( libHandle_ );

	if ( FALSE == freeLibResult ){
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( error );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.9.8.2  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.9.8.1  2004/04/06 17:19:16  ddiego
*minor header changes to better facilitate compiling with
*mingw. Also some minor changes to the devcpp FoundationKit project.
*
*Revision 1.9  2003/05/17 20:37:37  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.2.1  2003/03/12 03:12:38  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.2.1  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.7  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.6.10.1  2002/11/06 01:03:02  ddiego
*bug fixes, made the Win32HTMLBrowser get rid of the ATL.dll dependencies
*also made changes to the VCF Builder installer
*
*Revision 1.6  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


