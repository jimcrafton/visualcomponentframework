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

void LinuxFileStream::seek( const unsigned long& offset,
                            const SeekType& offsetFrom )
{
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

unsigned long LinuxFileStream::getSize()
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

unsigned long LinuxFileStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	if ( fileHandle_ < 0 ) {
		return 0;
	}
	int bytesRead =::read( fileHandle_, bytesToRead, sizeOfBytes );
	if ( bytesRead < 0 ) {
		throw FileIOError( MAKE_ERROR_MSG_2(
		                       "Error reading data from file stream.\n"
		                       + LinuxUtils::getErrorString( errno ) ) );
	}
	//error if we are not reading/writing asynchronously !
	if ( bytesRead != static_cast<int>(sizeOfBytes) ) {
		//throw exception ?
	}

    return bytesRead;
}

unsigned long LinuxFileStream::write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes )
{
	if ( fileHandle_ < 0 ) {
		return 0;
	}	
	int bytesWritten = ::write( fileHandle_, bytesToWrite, sizeOfBytes );
	if ( bytesWritten < 0 ) {
        wprintf(L"%i\n", errno);
		throw FileIOError( MAKE_ERROR_MSG_2(
		                       CANT_WRITE_TO_FILE + filename_ + "\n"
		                       + LinuxUtils::getErrorString( errno ) ) );
	}
	//error if we are not reading/writing asynchronously !
	if ( bytesWritten != static_cast<int>(sizeOfBytes) ) {
		//throw exception ?
		//throw FileIOError( CANT_WRITE_TO_FILE + filename_ );
	}

    return bytesWritten;
}

char* LinuxFileStream::getBuffer()
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

		case stSeekFromRelative : {
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
