//LinuxFilePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

using namespace VCF;
using namespace VCFLinux;


using namespace VCF;

LinuxFilePeer::LinuxFilePeer( File* file, const String& fileName )  :
	fileHandle_(0),
	file_(file)
{
	
}

LinuxFilePeer::~LinuxFilePeer()
{
	if ( 0 != fileHandle_ ) {
		::close(fileHandle_);
	}
}

void LinuxFilePeer::setFile( File* file )
{
	file_ = file;
}


ulong64 LinuxFilePeer::getSize()
{
	ulong64 result ;
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_size;
	}
	
	return result;
}

void LinuxFilePeer::updateStat( File::StatMask statMask )
{

}

void LinuxFilePeer::setFileAttributes( const File::FileAttributes fileAttributes )
{

}


bool LinuxFilePeer::isExecutable()
{
	bool result ;
	
	return result;
}

void LinuxFilePeer::setDateModified( const DateTime& dateModified )
{

}

DateTime LinuxFilePeer::getDateModified()
{
	DateTime result ;
	
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_mtime;
	}
	
	return result;
}

DateTime LinuxFilePeer::getDateCreated()
{   
	DateTime result ;
	
	return result;
}

DateTime LinuxFilePeer::getDateAccessed()
{
	DateTime result ;
	
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_atime;
	}
	
	return result;
}

void LinuxFilePeer::open( const String& fileName, ulong32 openFlags, File::ShareFlags shareFlags)
{
	close();
	VCF_ASSERT( !fileName.empty() );
	int oflags = 0;
	if ( File::ofRead & openFlags ) {
		oflags |= O_RDONLY;
	}
	
	if ( File::ofWrite & openFlags ) {
		oflags |= O_WRONLY;
	}
	
	if ( File::ofWrite & openFlags && File::ofRead & openFlags ) {
		oflags |= O_RDWR;
	}
	
	fileHandle_ = ::open( fileName.ansi_c_str(), oflags );
	if ( -1 == fileHandle_ ) {
		fileHandle_ = 0;
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to open the specified file " + fileName));
	}
}

void LinuxFilePeer::close()
{
	if ( 0 != fileHandle_ ) {
		::close( fileHandle_ );
	}
}

void LinuxFilePeer::create( ulong32 openFlags )
{
	close();
	String fname = file_->getName();
	VCF_ASSERT( !fname.empty() );
	
	FilePath fp = fname;
	if ( fp.isDirectoryName() ) {
		std::vector<String> dirPaths = fp.getPathComponents();
		std::vector<String>::iterator it = dirPaths.begin();
		String dirName;
		while ( it != dirPaths.end() ){
			dirName += *it;
			DIR* dir = opendir( dirName.ansi_c_str() );
			if ( NULL == dir ) {
				//try and create it?
				mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
				::mkdir( dirName.ansi_c_str(), mode );
			}
			else {
				::closedir( dir );
			}
			
			it ++;
		}
		
	}
	else {
		int oflags = O_CREAT | O_TRUNC;
		if ( File::ofRead & openFlags ) {
			oflags |= O_RDONLY;
		}
		
		if ( File::ofWrite & openFlags ) {
			oflags |= O_WRONLY;
		}
		
		if ( File::ofWrite & openFlags && File::ofRead & openFlags ) {
			oflags |= O_RDWR;
		}
		
		fileHandle_ = ::open( fname.ansi_c_str(), oflags );
		if ( -1 == fileHandle_ ) {
			fileHandle_ = 0;
			throw BasicFileError( MAKE_ERROR_MSG_2("Unable to open the specified file " + file_->getName()));
		}
		
		::lseek( fileHandle_, 0, SEEK_SET );
	}	
}

void LinuxFilePeer::remove()
{
	AnsiString fname = file_->getName();
	VCF_ASSERT( !fname.empty() );
	
	::remove( fname.c_str() );
}

void LinuxFilePeer::move( const String& newFileName )
{
	AnsiString fname = file_->getName();
	VCF_ASSERT( !fname.empty() );
	
	::rename( fname.c_str(), newFileName.ansi_c_str() );
}

void LinuxFilePeer::copyTo( const String& copyFileName )
{
	AnsiString fname = file_->getName();

	FILE* f = fopen( fname.c_str(), "rb" );
	if ( NULL != f ) {
		int size = 0;
		
		fseek( f, 0, SEEK_END );		
		size = ftell(f);
		fseek( f, 0, SEEK_SET );
		
		char* buffer = new char[size];
		
		fread( buffer, 1, size, f );
		fclose(f);
		
		f = fopen( copyFileName.ansi_c_str(), "wb" );
		if ( NULL != f ) {
			fwrite( buffer, 1, size, f );
			fclose(f);
		}
		else {
			delete [] buffer;
			throw BasicFileError( MAKE_ERROR_MSG_2("Unable to copy the specified file " + file_->getName()));	
		}
		
		
		delete [] buffer;		
	}
	else {
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to copy the specified file " + file_->getName()));	
	}
}

void LinuxFilePeer::initFileSearch( Directory::Finder* finder )
{

}

File* LinuxFilePeer::findNextFileInSearch( Directory::Finder* finder )
{
	File* result = NULL;
	
	return result;
}

void LinuxFilePeer::endFileSearch( Directory::Finder* finder )
{

}


/**
*CVS Log info
*$Log$
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
*Revision 1.5  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.14.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4.14.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2002/05/27 22:52:34  ddiego
*added two new tests for testing File and System support in the FoudnationKit
*and verified that they work in Linux. Fixed associated code in getting that to
*work.
*
*Revision 1.3  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
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
*/


