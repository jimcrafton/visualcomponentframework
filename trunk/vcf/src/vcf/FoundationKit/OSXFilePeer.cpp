//OSXFilePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/OSXFilePeer.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
	  
//#include "vcf/FoundationKit/regexx.h"

//#include "MoreFilesX.h"

using namespace VCF;

OSXFilePeer::OSXFilePeer( File* file, const String& fileName )  :
	fileHandle_(0),
	file_(file),
	searchStarted_(false)
{
	
}

OSXFilePeer::~OSXFilePeer()
{
	if ( 0 != fileHandle_ ) {
		//close(fileHandle_);
	}
}

void OSXFilePeer::setFile( File* file )
{
	file_ = file;
}


ulong64 OSXFilePeer::getSize()
{
	ulong64 result ;
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_size;
	}
	
	return result;
}

void OSXFilePeer::updateStat( File::StatMask statMask )
{

}

void OSXFilePeer::setFileAttributes( const File::FileAttributes fileAttributes )
{

}


bool OSXFilePeer::isExecutable()
{
	bool result ;
	
	return result;
}

void OSXFilePeer::setDateModified( const DateTime& dateModified )
{

}

DateTime OSXFilePeer::getDateModified()
{
	DateTime result ;
	
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_mtimespec.tv_sec;
	}
	
	return result;
}

DateTime OSXFilePeer::getDateCreated()
{   
	DateTime result ;
	
	return result;
}

DateTime OSXFilePeer::getDateAccessed()
{
	DateTime result ;
	
	struct stat st = {0};
	if ( -1 != fstat( fileHandle_, &st ) ) {
		result = st.st_atimespec.tv_sec;
	}
	
	return result;
}

void OSXFilePeer::open( const String& fileName, ulong32 openFlags, File::ShareFlags shareFlags)
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

void OSXFilePeer::close()
{
	if ( 0 != fileHandle_ ) {
		::close( fileHandle_ );
	}
}

void OSXFilePeer::create( ulong32 openFlags )
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

void OSXFilePeer::remove()
{
	AnsiString fname = file_->getName();
	VCF_ASSERT( !fname.empty() );
	
	::remove( fname.c_str() );
}

void OSXFilePeer::move( const String& newFileName )
{
	AnsiString fname = file_->getName();
	VCF_ASSERT( !fname.empty() );
	
	::rename( fname.c_str(), newFileName.ansi_c_str() );
}

void OSXFilePeer::copyTo( const String& copyFileName )
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

void OSXFilePeer::initFileSearch( Directory::Finder* finder )
{

}

File* OSXFilePeer::findNextFileInSearch( Directory::Finder* finder )
{
	File* result = NULL;
	
	return result;
}

void OSXFilePeer::endFileSearch( Directory::Finder* finder )
{

}
	
	
/*
bool OSXFilePeer::beginFileSearch( Directory::Finder* finder )
{
	bool result = false;
	searchFilters_.clear();
	buildSearchFilters( finder->getSearchFilter() );


	FileSearchData fsData;

	//RegExx::Regexx regex;

	return result;
}

String OSXFilePeer::findNextFileInSearch( Directory::Finder* finder )
{
	return "";
}

void OSXFilePeer::endFileSearch( Directory::Finder* finder )
{
}

void OSXFilePeer::buildSearchFilters( const String& searchFilter )
{

	String tmp = searchFilter;
	int pos = tmp.find( ";" );
	while ( String::npos != pos ) {
		searchFilters_.push_back( tmp.substr( 0, pos ) );
		tmp.erase( 0, pos+1 );
		pos = tmp.find( ";" );
	}

	if ( !tmp.empty() ) {
		searchFilters_.push_back( tmp );
	}
}

void OSXFilePeer::remove()
{

}

void OSXFilePeer::create()
{
    const char* fName = filename_.ansi_c_str();
    fileHandle_ = fopen( fName, "rb" );
    if ( NULL == fileHandle_ ) {
        //create it
        fileHandle_ = fopen( fName, "w" );
        fclose( fileHandle_ );
        fileHandle_ = fopen( fName, "rb" );
    }

    if ( NULL == fileHandle_ ) {
        throw RuntimeException( MAKE_ERROR_MSG_2("OSXFilePeer::create() failed!") );
    }
}


uint32 OSXFilePeer::getSize()
{

	uint32 result = 0;
	fseek( fileHandle_, 0, SEEK_END );
    result = ftell( fileHandle_ );
    fseek( fileHandle_, 0, SEEK_SET );
	return result;
}


void OSXFilePeer::copyTo( const String& copyFileName )
{

}
*/


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/08/02 04:11:53  ddiego
*added more examples to xcode project
*
*Revision 1.1.2.11  2004/08/01 23:40:16  ddiego
*fixed a few osx bugs
*
*Revision 1.1.2.10  2004/07/30 02:15:29  ddiego
*added some impl in OSXFilePeer
*
*Revision 1.1.2.9  2004/07/29 03:55:12  ddiego
*osx updates
*
*Revision 1.1.2.8  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.7  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


