//OSXFileStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace VCF;

OSXFileStream::OSXFileStream( const String& filename, const FileStreamAccessType& accessType ):
fileHandle_(0),
file_(NULL)
{
	filename_ = filename;
	
	int oflags = 0;
	
	bool fileExists = true;
	FILE* f = fopen( filename_.ansi_c_str(), "rb" );
	if ( NULL == f ) {
		fileExists = false;
	}
	else {
		fclose(f);
	}
	
	switch ( accessType ){
		case fsRead : {
			oflags = O_RDONLY;
		}
		break;

		case fsWrite : {
			oflags = O_CREAT | O_WRONLY | O_TRUNC;
		}
		break;

		case fsReadWrite : case fsDontCare : {
			oflags = O_CREAT | O_TRUNC | O_RDWR;
		}
		break;
	}
	
	fileHandle_ = ::open( filename_.ansi_c_str(), oflags );
	
	if (fileHandle_ < 0)	{
		fileHandle_ = NULL;
		throw FileIOError( CANT_ACCESS_FILE + filename  );
	}
	else {
		if ( !fileExists ) {
			mode_t mode = S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH;
			fchmod( fileHandle_, mode );
		}
		::lseek( fileHandle_, 0, SEEK_SET );
	}
}

OSXFileStream::OSXFileStream( File* file ):
	fileHandle_(0),
	file_(file)
{
	filename_ = file_->getName();	
	
	OSXFilePeer* filePeer = (OSXFilePeer*)file_->getPeer();
	fileHandle_ = filePeer->getFileHandle();
	
	if (fileHandle_ < 0)	{
		fileHandle_ = NULL;
		throw FileIOError( CANT_ACCESS_FILE + filename_  );
	}
	else {
		::lseek( fileHandle_, 0, SEEK_SET );
	}
	
}

OSXFileStream::~OSXFileStream()
{

	if ((file_ == NULL) && (fileHandle_ != NULL)) {
		::close( fileHandle_ );
	}
}

void OSXFileStream::seek(const uint64& offset, const SeekType& offsetFrom)
{
	// Check that offset is representable in this system's off_t type
	off_t target = static_cast<off_t>( offset );
	if ( ( target < 0 ) || ( offset != static_cast<uint64>( target ) ) ){
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Read byte count is too large for this system." ) );
	}
	int seekType = translateSeekTypeToMoveType( offsetFrom );

	int err = ::lseek( fileHandle_, target, seekType );

	if (err < 0 ) {
		int errorCode = errno;
		String errMsg = "Error attempting to seek in stream.\n" + OSXStringUtils::getErrorString( errorCode );
		throw FileIOError( MAKE_ERROR_MSG_2(errMsg) );
	}
}

uint64 OSXFileStream::getSize()
{
	uint64 result = 0;
	
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_size;
	}	
	
	return result;
}

uint64 OSXFileStream::read( unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	// Check that offset is representable in this system's off_t type
	off_t length = static_cast<off_t>( sizeOfBytes );
	if ( ( length < 0 ) || ( sizeOfBytes != static_cast<uint64>( length ) ) ){
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Read byte count is too large for this system." ) );
	}
	size_t bytesRead = 0;
	size_t err = ::read( fileHandle_, bytesToRead, length );

	if (err < 0)	{
		// TODO: peer error string
		int errorCode = errno;
		String errMsg = "Error reading data from file stream.\n" + OSXStringUtils::getErrorString( errorCode );
		throw FileIOError( MAKE_ERROR_MSG_2(errMsg) );
	}
	else
	{
		bytesRead = err;
	}

	if ( bytesRead != length ){ //error if we are not read /writing asynchronously !
								  //throw exception ?
	}
	
	return bytesRead;
}

uint64 OSXFileStream::write( const unsigned char* bytesToWrite, uint64 sizeOfBytes )
{
	// Check that offset is representable in this system's off_t type
	off_t length = static_cast<off_t>( sizeOfBytes );
	if ( ( length < 0 ) || ( sizeOfBytes != static_cast<uint64>( length ) ) ){
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Write byte count is too large for this system." ) );
	}
	int bytesWritten = 0;
	size_t err = ::write( fileHandle_, bytesToWrite, length );

	if (err < 0)
	{
		int errorCode = errno;
		String errMsg = CANT_WRITE_TO_FILE + filename_ + "\n" + OSXStringUtils::getErrorString( errorCode );

		throw FileIOError( MAKE_ERROR_MSG_2(errMsg) );
	}
	else
	{
		bytesWritten = err;
	}

	if ( bytesWritten != length ){//error if we are not read /writing asynchronously !
									//throw exception ?
		 //throw FileIOError( CANT_WRITE_TO_FILE + filename_ );
	}
	
	return bytesWritten;
}

uchar* OSXFileStream::getBuffer()
{
	// ???
	return NULL;
}


int OSXFileStream::translateSeekTypeToMoveType( const SeekType& offsetFrom )
{
	int result = 0;

	switch ( offsetFrom ){
		case stSeekFromStart : {
			result = SEEK_SET;
		}
			break;

		case stSeekForwards : {
			result = SEEK_CUR;
		}
			break;

		case stSeekFromEnd : {
			result = SEEK_END;
		}
			break;
	}
	return result;
}


/**
$Id$
*/
