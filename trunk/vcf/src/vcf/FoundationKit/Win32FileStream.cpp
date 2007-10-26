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

void Win32FileStream::seek(const uint64& offset, const SeekType& offsetFrom)
{
	// Check that offset is within the positive range of an int64
	int64 target = static_cast<int64>( offset );
	if ( target < 0 ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Offset value is too large for this system." ) );
	}
	LONG low32 = (target << 32) >> 32;
	LONG high32 = target >> 32;
	DWORD err = SetFilePointer( fileHandle_, low32, &high32, translateSeekTypeToMoveType( offsetFrom ) );
	if ( 0xFFFFFFFF == err ) {
		throw FileIOError( "Error attempting to seek in stream.\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}
}

uint64 Win32FileStream::getSize()
{
	DWORD high32 = 0;
	DWORD low32 = GetFileSize( fileHandle_, &high32 );
	uint64 size = (static_cast<uint64>(high32) << 32) + low32;
	return size;
}

uint64 Win32FileStream::read( unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	uint64 totalRead = 0;
	DWORD bytesRead = 0;
	DWORD toRead;
	if (sizeOfBytes > 0xFFFFFFFF) {
		toRead = 0xFFFFFFFF;
		sizeOfBytes -= 0xFFFFFFFF;
	}
	else {
		toRead = static_cast<DWORD>(sizeOfBytes);
		sizeOfBytes = 0;
	}
	BOOL result = ReadFile( fileHandle_, bytesToRead, toRead, &bytesRead, NULL );
	totalRead += bytesRead;

	if ( bytesRead != toRead ){ //error if we are not read /writing asynchronously !
		//throw exception ?
	}

	if ( !result )  {
		throw FileIOError( "Error reading data from file stream.\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}

	if (sizeOfBytes && (toRead == bytesRead)) {
		totalRead += read( bytesToRead + totalRead, sizeOfBytes );
	}

	return totalRead;
}

uint64 Win32FileStream::write( const unsigned char* bytesToWrite, uint64 sizeOfBytes )
{
	uint64 totalWritten = 0;
	DWORD bytesWritten = 0;
	DWORD toWrite;
	if (sizeOfBytes > 0xFFFFFFFF) {
		toWrite = 0xFFFFFFFF;
		sizeOfBytes -= 0xFFFFFFFF;
	}
	else {
		toWrite = static_cast<DWORD>(sizeOfBytes);
		sizeOfBytes = 0;
	}
	BOOL result = WriteFile( fileHandle_, bytesToWrite, toWrite, &bytesWritten, NULL );
	totalWritten += bytesWritten;

	if ( bytesWritten != sizeOfBytes ){//error if we are not read /writing asynchronously !
		//throw exception ?
		//throw FileIOError( CANT_WRITE_TO_FILE + filename_ );
	}

	if ( !result )  {
		throw FileIOError( CANT_WRITE_TO_FILE + filename_ + "\nPeer error string: " + Win32Utils::getErrorString(GetLastError()) );
	}

	if (sizeOfBytes && (toWrite == bytesWritten)) {
		totalWritten += write( bytesToWrite + totalWritten, sizeOfBytes );
	}

	return totalWritten;
}

uchar* Win32FileStream::getBuffer()
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

		case stSeekForwards : {
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
$Id$
*/
