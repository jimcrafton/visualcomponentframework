//LinuxFilePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>

using namespace VCF;
using namespace VCFLinux;

LinuxFilePeer::LinuxFilePeer( File* file )
		: fileHandle_( -1 )
		, file_( file )
		, searchStarted_( false )
        , fileSearchData_( NULL )
{}

LinuxFilePeer::~LinuxFilePeer()
{
	this->close();
}

void LinuxFilePeer::setFile( File* file )
{
	this->close();
	file_ = file;
}

ulong64 LinuxFilePeer::getSize()
{
	if ( -1 == fileHandle_ ) {
		return 0;
	}
	struct stat st;
	::memset( &st, '\0', sizeof( struct stat ) );
	if ( -1 != ::fstat( fileHandle_, &st ) ) {
		return st.st_size;
	}
	return 0;
}

void LinuxFilePeer::updateStat( File::StatMask statMask )
{}

void LinuxFilePeer::setFileAttributes( const File::FileAttributes fileAttributes )
{}

bool LinuxFilePeer::isExecutable()
{
	if ( -1 == fileHandle_ ) {
		return false;
	}
	struct stat st;
	::memset( &st, '\0', sizeof( struct stat ) );
	if ( -1 != ::fstat( fileHandle_, &st ) ) {
		return ( st.st_mode == S_IXUSR
		         or st.st_mode == S_IXGRP
		         or st.st_mode == S_IXOTH );
	}
	return false;
}

void LinuxFilePeer::setDateModified( const DateTime& dateModified )
{}

DateTime LinuxFilePeer::getDateModified()
{
	DateTime result ;
	if ( -1 != fileHandle_ ) {
		struct stat st;
		::memset( &st, '\0', sizeof( struct stat ) );
		if ( -1 != fstat( fileHandle_, &st ) ) {
			result = st.st_mtime;
		}
	}
    else
    {
        struct stat st;
        lstat(getName().ansi_c_str(), &st);
        result = st.st_mtime;
    }
	return result;
}

DateTime LinuxFilePeer::getDateCreated()
{
	return this->getDateModified();
}

DateTime LinuxFilePeer::getDateAccessed()
{
	DateTime result ;
	if ( -1 != fileHandle_ ) {
		struct stat st;
		::memset( &st, '\0', sizeof( struct stat ) );
		if ( -1 != fstat( fileHandle_, &st ) ) {
			result = st.st_atime;
		}
	}
	return result;
}

void LinuxFilePeer::open( const String& fileName, ulong32 openFlags, File::ShareFlags shareFlags )
{
	this->close();

	VCF_ASSERT( !fileName.empty() );

	int oflags = 0;

    if ( File::ofWrite & openFlags && File::ofRead & openFlags ) {
		oflags |= O_RDWR;
	}
    else if ( File::ofWrite & openFlags ) {
        oflags |= O_WRONLY;
    }
    else if ( File::ofRead & openFlags ) {
		oflags |= O_RDONLY;
	}

    fileHandle_ = ::open( fileName.ansi_c_str(), oflags );

    if ( -1 == fileHandle_ ) {
		throw BasicFileError( MAKE_ERROR_MSG_2(
		                          "Unable to open the specified file "
		                          + fileName ) );
	}
}

void LinuxFilePeer::close()
{
	if ( -1 != fileHandle_ ) {
		::close( fileHandle_ );
	}
}

void LinuxFilePeer::create( ulong32 openFlags )
{
	this->close();
	String fileName = file_->getName();
	VCF_ASSERT( !fileName.empty() );
	FilePath filePath = fileName;
	if ( filePath.isDirectoryName() ) {
		std::vector<String> dirPaths = filePath.getPathComponents();
		String dirName;
		for ( std::vector<String>::iterator it = dirPaths.begin();
		        it != dirPaths.end();
		        ++it ) {
			dirName += *it;
			DIR* dir = opendir( dirName.ansi_c_str() );
			if ( ! dir ) {
				//try and create it?
				mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
				::mkdir( dirName.ansi_c_str(), mode );
			} else {
				::closedir( dir );
			}
		}
	} else {
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
		fileHandle_ = ::open( fileName.ansi_c_str(), oflags );
		if ( -1 == fileHandle_ ) {
			throw BasicFileError( MAKE_ERROR_MSG_2(
			                          "Unable to open the specified file "
			                          + file_->getName() ) );
		}
		::lseek( fileHandle_, 0, SEEK_SET );
	}
}

void LinuxFilePeer::remove
	()
{
	AnsiString fileName = file_->getName();
	VCF_ASSERT( !fileName.empty() );
	::remove
		( fileName.c_str() );
}

void LinuxFilePeer::move( const String& newFileName )
{
	AnsiString fileName = file_->getName();
	VCF_ASSERT( !fileName.empty() );
	::rename( fileName.c_str(), newFileName.ansi_c_str() );
}

void LinuxFilePeer::copyTo( const String& copyFileName )
{
	AnsiString fileName = file_->getName();
	FILE* f = ::fopen( fileName.c_str(), "rb" );
	if ( f ) {
		::fseek( f, 0, SEEK_END );
		int size = ftell( f );
		std::vector<char> buffer( size, '\0' );
		::fseek( f, 0, SEEK_SET );
		::fread( &buffer[ 0 ], 1, buffer.size(), f );
		::fclose( f );
		f = ::fopen( copyFileName.ansi_c_str(), "wb" );
		if ( f ) {
			::fwrite( &buffer[ 0 ], 1, buffer.size(), f );
			::fclose( f );
		} else {
			throw BasicFileError( MAKE_ERROR_MSG_2(
			                          "Unable to copy the specified file "
			                          + file_->getName() ) );
		}
	} else {
		throw BasicFileError( MAKE_ERROR_MSG_2(
		                          "Unable to copy the specified file "
		                          + file_->getName() ) );
	}
}


class LinuxFilePeer::FileSearchData
{
public:
    FileSearchData()
    : searchDir_(NULL)
    , location_(0)
	{
	}

    DIR *searchDir_;
    long int location_;
    String   currentDir_;
};

ulong32 LinuxFilePeer::convertAttributesFromSystemSpecific( const struct stat& st, const String& fileName )
{
    ulong32 fileAttributes = File::faNone;

    if( !(st.st_mode & (S_IWUSR | S_IWGRP | S_IWOTH)) ) {
        fileAttributes += File::faReadOnly;
    }
    //                               make sure it is not "." or ".."
    if(fileName[0] == '.' && (fileName[1] != '\0' || fileName[2] != '.') ) {
        // if(fileName[0] == '.' && (fileName != "." || fileName != "..") ) {  
        fileAttributes += File::faHidden;
    }

    //File::faSystem ?  Should I check whether the file is in a specific directory ie /bin, /lib etc ?

    if(!(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
        fileAttributes += File::faExecutable;
    }

    if( S_ISDIR( st.st_mode) ) {
        fileAttributes += File::faDirectory;
    }

    //File::faArchive ?
    if(S_ISBLK(st.st_mode) || S_ISCHR(st.st_mode)) {
        fileAttributes += File::faDevice;
    }

    if( !S_ISREG(st.st_mode) ) {
        fileAttributes += File::faNormal;
    }

    return fileAttributes;
}

void LinuxFilePeer::initFileSearch( Directory::Finder* finder )
{
    if(fileSearchData_ == NULL) {
        fileSearchData_ = new FileSearchData;
    }
    char buf[PATH_MAX];
    fileSearchData_->currentDir_ = getcwd(buf, sizeof(buf));
    searchStarted_ = true;
    // other initialize of the finder before starting the search in it
    finder->internal_updateToActiveFinder();
}

File* LinuxFilePeer::findNextFileInSearch( Directory::Finder* finder )
{
	File* result = NULL;
    bool isDir = false;
    bool ok = false;
    ulong32 fileAttribs;

    while ( true ) {
        result = NULL;
        finder->getFileInfo().internal_setStatMask( File::smStatNone );
        isDir = false;
        ok = fileSearchData_->searchDir_ != NULL;

        dirent* entry = NULL;
        if (fileSearchData_->searchDir_ == NULL) {
            fileSearchData_->searchDir_ = opendir(getName().ansi_c_str());
            ok = fileSearchData_->searchDir_ != NULL;
            chdir(getName().ansi_c_str());
            fileSearchData_->location_ = telldir(fileSearchData_->searchDir_);
        }

        if(ok)
        {
            seekdir(fileSearchData_->searchDir_, fileSearchData_->location_);
            entry = readdir(fileSearchData_->searchDir_);
            ok = entry != NULL;
            fileSearchData_->location_ = telldir(fileSearchData_->searchDir_);
        }

        if ( ok ) {
            struct stat statbuf;
            lstat(entry->d_name, &statbuf);
            fileAttribs = LinuxFilePeer::convertAttributesFromSystemSpecific(statbuf, entry->d_name);
            isDir = S_ISDIR(statbuf.st_mode);
            
            //check skip conditions.
            //either we are a directory and the finder is only interested in files or
            //we're NOT a directorym and the we're only interested in directories,
            //or the filter mask is set to some value other than faNone, and the current
            //file attributes don't match anything in the mask.
            if ( ( strcmp(".", entry->d_name) == 0 ) || 
                 ( strcmp("..", entry->d_name) == 0 ) ||
                 ( isDir && finder->getCurrentDisplayOrder() == Directory::Finder::dmFiles ) ||
                 ( !isDir && ( ( finder->getCurrentDisplayOrder() == Directory::Finder::dmDirs ) ||
                 ( ( File::faNone != finder->getMaskFilterFileAttribs() ) && 
                 ( 0 == ( fileAttribs & finder->getMaskFilterFileAttribs() ) ) ) ) ) ) {
                continue;
            }
            result = &finder->getFileInfo();
            File::StatMask statMask = (File::StatMask)(finder->getStatMask() & ~File::smAttributes);
            result->internal_removeFromStatMask( statMask );
            result->internal_setFileAttributes( fileAttribs );
            result->internal_addToStatMask( File::smAttributes );
      
            //???? get the file name of the current entry/file/whatever ????
            result->internal_setFileName( file_->getName() + entry->d_name);
        }
     
        if ( result != NULL ) {
            FileSearchFilter* filter = finder->getSearchFilterFileObject();
            if ( NULL != filter ) {
                result = filter->passSearchFilter( result, dynamic_cast<const Directory*>(file_), finder );
            }
            // recursion management
            if ( NULL != result ) {
                // ok we found a subdirectory matching the filter
                // now recursion into this subdirectory
                if ( isDir ) {
                    if ( finder->getRecurse() ) {
                        if ( finder->canRecurseDown() ) {
                            finder->goDownDir( result );
                        } 
                        else {
                            // continue the search in the next subdirectory
                            chdir("..");
                            finder->continueSearch( result );
                        }
                    }
                }
    
                if ( NULL != result ) {
                    break;
                }
            }
        }
        else {
            chdir("..");
            endFileSearch( finder );
            finder->continueSearch( result );
            break;
        }  
    }
    finder->setCurrentElement( result );
    return result;
}

void LinuxFilePeer::endFileSearch( Directory::Finder* finder )
{
    if(fileSearchData_ != NULL)
    {
        if(fileSearchData_->searchDir_ != NULL)
        {
            closedir(fileSearchData_->searchDir_);
            fileSearchData_->searchDir_ = NULL;
        }
        if(!fileSearchData_->currentDir_.empty())
        {
            chdir(fileSearchData_->currentDir_.ansi_c_str());
        }
        delete fileSearchData_;
        fileSearchData_ = NULL;
        searchStarted_ = false;
    }
}


/**
$Id$
*/
