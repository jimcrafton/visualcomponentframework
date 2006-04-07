//Win32FileStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;
using namespace VCFWin32;

Win32FileStream::Win32FileStream( const String& filename, const FileStreamAccessType& accessType ):
	fileHandle_(NULL),
	file_(NULL)
{
	if ( filename.empty() ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Invalid file specified by caller to Win32FileStream::Win32FileStream() - file name is empty.") );
	}
	filename_ = filename;


	if ( System::isUnicodeEnabled() ) {
		fileHandle_ = CreateFileW( filename.c_str(),
		                       this->translateAccessType( accessType ),
                               0, //for now
							   NULL, //for now
							   translateAccessTypeToCreationType( accessType ),
							   FILE_ATTRIBUTE_NORMAL,
							   NULL );
	}
	else {
		fileHandle_ = CreateFileA( filename.ansi_c_str(),
		                       this->translateAccessType( accessType ),
                               0, //for now
							   NULL, //for now
							   translateAccessTypeToCreationType( accessType ),
							   FILE_ATTRIBUTE_NORMAL,
							   NULL );
	}

	if ( INVALID_HANDLE_VALUE == fileHandle_ ){

		throw FileIOError( CANT_ACCESS_FILE + filename + "\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}
}

Win32FileStream::Win32FileStream( File* file ):
	fileHandle_(NULL),
	file_(file)
{
	Win32FilePeer* peerImpl = (Win32FilePeer*)file->getPeer();

	if ( NULL == peerImpl->getFileHandle() ) {
		file->open();
	}

	filename_ = file->getName();
	fileHandle_ = peerImpl->getFileHandle();

	if ( INVALID_HANDLE_VALUE == fileHandle_ ){

		throw FileIOError( CANT_ACCESS_FILE + filename_ + "\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}
	
}

Win32FileStream::~Win32FileStream()
{
	if ( (NULL == file_) && (INVALID_HANDLE_VALUE != fileHandle_) ){
		CloseHandle( fileHandle_ );
	}
}

void Win32FileStream::seek(const unsigned long& offset, const SeekType& offsetFrom)
{
	DWORD err = SetFilePointer( fileHandle_, offset, NULL, translateSeekTypeToMoveType( offsetFrom ) );
	if ( 0xFFFFFFFF == err ) {
		throw FileIOError( "Error attempting to seek in stream.\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}
}

unsigned long Win32FileStream::getSize()
{
	return GetFileSize( fileHandle_, NULL );
}

unsigned long Win32FileStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	DWORD bytesRead = 0;
	BOOL result = ReadFile( fileHandle_, bytesToRead, sizeOfBytes, &bytesRead, NULL );

	if ( bytesRead != sizeOfBytes ){ //error if we are not read /writing asynchronously !
		//throw exception ?
	}

	if ( !result )  {
		throw FileIOError( "Error reading data from file stream.\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}

	return bytesRead;
}

unsigned long Win32FileStream::write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes )
{
	DWORD bytesWritten = 0;
	BOOL result = WriteFile( fileHandle_, bytesToWrite, sizeOfBytes, &bytesWritten, NULL );
	if ( bytesWritten != sizeOfBytes ){//error if we are not read /writing asynchronously !
		//throw exception ?
		//throw FileIOError( CANT_WRITE_TO_FILE + filename_ );
	}

	if ( !result )  {
		throw FileIOError( CANT_WRITE_TO_FILE + filename_ + "\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}

	return bytesWritten;
}

char* Win32FileStream::getBuffer()
{
	return NULL;
}

DWORD Win32FileStream::translateAccessType( const FileStreamAccessType& accessType )
{
	DWORD result = 0;
	switch ( accessType ){
		case fsRead : {
			result = GENERIC_READ;
		}
		break;

		case fsWrite : {
			result = GENERIC_WRITE;
		}
		break;

		case fsReadWrite : case fsDontCare : {
			result = GENERIC_WRITE | GENERIC_READ;
		}
		break;
	}
	return result;
}

DWORD Win32FileStream::translateAccessTypeToCreationType( const FileStreamAccessType& accessType )
{
	DWORD result = 0;
	switch ( accessType ){
		case fsRead : {
			result = OPEN_EXISTING;
		}
		break;

		case fsWrite : {
			result = CREATE_ALWAYS;//TRUNCATE_EXISTING | OPEN_ALWAYS;
		}
		break;

		case fsReadWrite : case fsDontCare : {
			result = OPEN_ALWAYS;
		}
		break;
	}
	return result;
}

DWORD Win32FileStream::translateSeekTypeToMoveType( const SeekType& offsetFrom )
{
	DWORD result = 0;
	switch ( offsetFrom ){
		case stSeekFromStart : {
			result = FILE_BEGIN;
		}
		break;

		case stSeekFromRelative : {
			result = FILE_CURRENT;
		}
		break;

		case stSeekFromEnd : {
			result = FILE_END;
		}
		break;
	}
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.1  2004/06/05 01:18:41  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.14.8.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.14  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:12:37  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.2.2  2002/12/28 00:53:27  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12.2.1  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.11.10.1  2002/11/02 20:51:57  ddiego
*fixed NT4 menu bug 533453 Disapearing menu items on WinNT 4
*also added soem bug fixes for hte VCF Builder and some empty name
*error checking in the Win32FileStream class
*
*Revision 1.11  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.10.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.10  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


