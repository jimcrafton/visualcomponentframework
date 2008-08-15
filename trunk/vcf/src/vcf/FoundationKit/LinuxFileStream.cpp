//LinuxFileStream.cpp

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
using namespace VCFLinux;

LinuxFileStream::LinuxFileStream( const String& filename,
                                  const FileStreamAccessType& accessType )
		: fileHandle_( -1 )
		, file_( 0 )
		, filename_( filename )
{
	int oflags = 0;
	int mode = 0; 
	switch ( accessType ) {
		case fsRead : {
				oflags = O_RDONLY;
			}
			break;

		case fsWrite : {
				oflags = O_WRONLY | O_CREAT;
				mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 0644
			}
			break;

		case fsReadWrite :
		case fsDontCare : {
				oflags = O_CREAT | O_TRUNC | O_RDWR;
				mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 0644
			}
			break;
	}
	
	fileHandle_ = ::open( filename_.ansi_c_str(), oflags, mode );
	if ( fileHandle_ > 0 ) {
		::lseek( fileHandle_, 0, SEEK_SET );
	} else {
		throw FileIOError( CANT_ACCESS_FILE + filename_ );
	}
}

LinuxFileStream::LinuxFileStream( File* file )
		: fileHandle_( -1 )
		, file_( file )
		, filename_( file_->getName() )
{
	LinuxFilePeer * filePeer = static_cast<LinuxFilePeer*>( file_->getPeer() );
	fileHandle_ = filePeer->getFileHandle();
	if ( fileHandle_ > 0 ) {
		::lseek( fileHandle_, 0, SEEK_SET );
	} else {
		throw FileIOError( CANT_ACCESS_FILE + filename_ );
	}
}

LinuxFileStream::~LinuxFileStream()
{
	if ( ( ! file_ ) and ( fileHandle_ > 0 ) ) {
		::close( fileHandle_ );
	}
}

void LinuxFileStream::seek( const uint64& offset,
                            const SeekType& offsetFrom )
{
	// Check that offset is representable in this system's off_t type
	off_t target = static_cast<off_t>( offset );
	if ( ( target < 0 ) || ( offset != static_cast<uint64>( target ) ) ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Offset value is too large for this system." ));
	}
	if ( fileHandle_ < 0 ) {
		return;
	}
	int seekType = translateSeekTypeToMoveType( offsetFrom );
	if ( ::lseek( fileHandle_, offset, seekType ) < 0 ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
		                       "Error attempting to seek in stream.\n"
		                       + LinuxUtils::getErrorString( errno ) ) );
	}
}

uint64 LinuxFileStream::getSize()
{
	if ( fileHandle_ < 0 ) {
		return 0;
	}
	struct stat st;
	::memset( &st, '\0', sizeof( struct stat ) );
	if ( -1 != fstat( fileHandle_, &st ) ) {
		return st.st_size;
	}
	return 0;
}

uint64 LinuxFileStream::read( unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	// Check that offset is representable in this system's off_t type
	off_t length = static_cast<off_t>( sizeOfBytes );
	if ( ( length < 0 ) || ( sizeOfBytes != static_cast<uint64>( length ) ) ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Read byte count is too large for this system." ));
	}
	if ( fileHandle_ < 0 ) {
		return 0;
	}
	int64 bytesRead =::read( fileHandle_, bytesToRead, length );
	if ( bytesRead < 0 ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
		                       "Error reading data from file stream.\n"
		                       + LinuxUtils::getErrorString( errno ) ) );
	}
	//error if we are not reading/writing asynchronously !
	if ( bytesRead != static_cast<int64>(length) ) {
		//throw exception ?
	}

    return bytesRead;
}

uint64 LinuxFileStream::write( const unsigned char* bytesToWrite, uint64 sizeOfBytes )
{
	// Check that offset is representable in this system's off_t type
	off_t length = static_cast<off_t>( sizeOfBytes );
	if ( ( length < 0 ) || ( sizeOfBytes != static_cast<uint64>( length ) ) ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
								"Write byte count is too large for this system." ));
	}
	if ( fileHandle_ < 0 ) {
		return 0;
	}	
	int64 bytesWritten = ::write( fileHandle_, bytesToWrite, length );
	if ( bytesWritten < 0 ) {
        wprintf(L"%i\n", errno);
		throw FileIOError( MAKE_ERROR_MSG_2(
		                       CANT_WRITE_TO_FILE + filename_ + "\n"
		                       + LinuxUtils::getErrorString( errno ) ) );
	}
	//error if we are not reading/writing asynchronously !
	if ( bytesWritten != static_cast<int64>(length) ) {
		//throw exception ?
		//throw FileIOError( CANT_WRITE_TO_FILE + filename_ );
	}

    return bytesWritten;
}

uchar* LinuxFileStream::getBuffer()
{
	// ???
	return 0;
}


int LinuxFileStream::translateSeekTypeToMoveType( const SeekType& offsetFrom )
{
	int result = 0;
	switch ( offsetFrom ) {
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
