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

void OSXFileStream::seek(const unsigned long& offset, const SeekType& offsetFrom)
{
	int seekType = translateSeekTypeToMoveType( offsetFrom );

	int err = ::lseek( fileHandle_, offset, seekType );

	if (err < 0 ) {
		int errorCode = errno;
		String errMsg = "Error attempting to seek in stream.\n" + OSXStringUtils::getErrorString( errorCode );
		throw FileIOError( MAKE_ERROR_MSG_2(errMsg) );
	}
}

unsigned long OSXFileStream::getSize()
{
	unsigned long result = 0;
	
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_size;
	}	
	
	return result;
}

unsigned long OSXFileStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	size_t bytesRead = 0;
	size_t err = ::read( fileHandle_, bytesToRead, sizeOfBytes );

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

	if ( bytesRead != sizeOfBytes ){ //error if we are not read /writing asynchronously !
								  //throw exception ?
	}
	
	return bytesRead;
}

unsigned long OSXFileStream::write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes )
{
	int bytesWritten = 0;
	size_t err = ::write( fileHandle_, bytesToWrite, sizeOfBytes );

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

	if ( bytesWritten != sizeOfBytes ){//error if we are not read /writing asynchronously !
									//throw exception ?
		 //throw FileIOError( CANT_WRITE_TO_FILE + filename_ );
	}
	
	return bytesWritten;
}

char* OSXFileStream::getBuffer()
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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2005/11/21 04:00:51  ddiego
*more osx updates.
*
*Revision 1.2.6.1  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.9  2004/08/02 04:11:53  ddiego
*added more examples to xcode project
*
*Revision 1.1.2.8  2004/08/01 23:40:16  ddiego
*fixed a few osx bugs
*
*Revision 1.1.2.7  2004/07/29 03:55:21  ddiego
*osx updates
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


