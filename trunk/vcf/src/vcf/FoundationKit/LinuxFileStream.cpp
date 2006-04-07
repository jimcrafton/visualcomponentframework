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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.3  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.3.2.2  2005/12/01 01:13:00  obirsoy
*More linux improvements.
*
*Revision 1.3.2.1  2005/11/10 00:04:08  obirsoy
*changes required for gcc under Linux.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/08/02 00:48:23  ddiego
*fixed build errors in linux for FoundationKit
*
*Revision 1.1.2.3  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.14.3  2003/04/19 22:22:56  ddiego
*tested the code developed in windows using gtk in linux. Seems to work ok except for a
*few minor compiler glitches. Had to comment out the partial specialization for
*floating point image bits in include/graphics/ImageBits.h. Also made some
*adjustments in the makefiles for building the GraphicsKit and ApplicationKit
*from the build/make/Makefile.
*
*Revision 1.3.14.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.14.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2002/05/28 03:03:15  ddiego
*added another test: FileStreaming to test out the FileStream class in
*linux. Added some changes to the LinuxFileStream class. Also added the
*LinuxLibraryPeer so the Library class now works in linux.
*
*Revision 1.2  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.4.1  2002/03/26 04:46:34  cesarmello
*Linux headers
*
*Revision 1.1  2002/01/28 02:07:59  cesarmello
*Linux file peer
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


