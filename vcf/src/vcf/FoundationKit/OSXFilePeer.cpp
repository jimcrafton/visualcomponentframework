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
#include <errno.h>

#define USER_EXEC	0100
#define USER_WRITE	0200
#define USER_READ	0400
#define GRP_EXEC	010
#define GRP_WRITE	020
#define GRP_READ	040
#define OTHER_EXEC	01
#define OTHER_WRITE	02
#define OTHER_READ	04


using namespace VCF;

FSCatalogInfoBitmap defaultSearchFlags = kFSCatInfoCreateDate | kFSCatInfoContentMod | 
									kFSCatInfoAccessDate | kFSCatInfoPermissions | kFSCatInfoFinderInfo |
									kFSCatInfoDataSizes | kFSCatInfoNodeFlags ;
									

ulong32 OSX_convertAttributesFromSystemSpecific( FSCatalogInfo* catInfo )
{
	ulong32 fileAttributes = File::faNone;
	
	FSPermissionInfo* permissions = (FSPermissionInfo*)catInfo->permissions;
	
	if ( !(permissions->mode & USER_WRITE) && !(permissions->mode & GRP_WRITE) && !(permissions->mode & OTHER_WRITE) ) {
		fileAttributes |= File::faReadOnly;	
	}
	
	if ( (catInfo->nodeFlags & kFSNodeIsDirectoryMask) == kFSNodeIsDirectoryMask ) {
		fileAttributes |= File::faDirectory;
	}
	
	if ( (permissions->mode & USER_EXEC) || (permissions->mode & GRP_EXEC) || (permissions->mode & OTHER_EXEC) ) {
		fileAttributes |= File::faExecutable;	
	}
	
	
	
	fileAttributes |= File::faNormal;
		
	
	return fileAttributes;
}











OSXFilePeer::OSXFilePeer( File* file, const String& fileName )  :
	fileHandle_(0),
	file_(file),
	searchStarted_(false),
	searchIterator_(NULL),
	searchData_(NULL)
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
	const char* fileName = getName().ansi_c_str();
	VCF_ASSERT( fileName != NULL );
	
	file_->internal_removeFromStatMask( statMask );
	
	FSRef fileFS;
	if ( noErr == FSPathMakeRef( (const UInt8*)fileName, &fileFS, NULL ) ) {
		FSCatalogInfo info;
		
		if ( noErr == FSGetCatalogInfo( &fileFS, kFSCatInfoPermissions | kFSCatInfoNodeFlags, &info, NULL, NULL, NULL ) ) {
			if ( statMask & File::smAttributes ) {
				ulong32 fileAttrs = 0;
				fileAttrs = OSX_convertAttributesFromSystemSpecific( &info );
				file_->internal_setFileAttributes( fileAttrs );
			}
		}
	}
	
	file_->internal_addToStatMask( statMask );
}

void OSXFilePeer::setFileAttributes( const File::FileAttributes fileAttributes )
{

}


bool OSXFilePeer::isExecutable()
{
	bool result = false;
	
	const char* fileName = getName().ansi_c_str();
	VCF_ASSERT( fileName != NULL );
	
	FSRef fileFS;
	if ( noErr == FSPathMakeRef( (const UInt8*)fileName, &fileFS, NULL ) ) {
		FSCatalogInfo info;
		
		if ( noErr == FSGetCatalogInfo( &fileFS, kFSCatInfoPermissions, &info, NULL, NULL, NULL ) ) {
			FSPermissionInfo* permissions = (FSPermissionInfo*)info.permissions;
		
			if ( (permissions->mode & USER_EXEC) || (permissions->mode & GRP_EXEC) || (permissions->mode & OTHER_EXEC) ) {
				result = true;
			}
		}		
	}
	
	return result;
}

void OSXFilePeer::setDateModified( const DateTime& dateModified )
{

}

DateTime OSXFilePeer::getDateModified()
{
	DateTime result ;
	
	const char* fileName = getName().ansi_c_str();
	VCF_ASSERT( fileName != NULL );
	
	FSRef fileFS;
	if ( noErr == FSPathMakeRef( (const UInt8*)fileName, &fileFS, NULL ) ) {
		FSCatalogInfo info;
		
		if ( noErr == FSGetCatalogInfo( &fileFS, kFSCatInfoContentMod, &info, NULL, NULL, NULL ) ) {
			CFAbsoluteTime  absoluteTime;
			UCConvertUTCDateTimeToCFAbsoluteTime( &info.contentModDate, &absoluteTime );
			
			CFGregorianDate dt = CFAbsoluteTimeGetGregorianDate( absoluteTime, NULL );
	
			double dsecs = floor(dt.second);
			unsigned int second = (unsigned int)dsecs;	
			double milliseconds = (dt.second - dsecs) * 1000.0;
	
			result.set( dt.year, dt.month, dt.day, 
						dt.hour, dt.minute, second, (unsigned int)milliseconds );
		}		
	}
	
	return result;
}

DateTime OSXFilePeer::getDateCreated()
{   
	DateTime result ;
	
	
	const char* fileName = getName().ansi_c_str();
	VCF_ASSERT( fileName != NULL );
	
	FSRef fileFS;
	if ( noErr == FSPathMakeRef( (const UInt8*)fileName, &fileFS, NULL ) ) {
		FSCatalogInfo info;
		
		if ( noErr == FSGetCatalogInfo( &fileFS, kFSCatInfoCreateDate, &info, NULL, NULL, NULL ) ) {
			CFAbsoluteTime  absoluteTime;
			UCConvertUTCDateTimeToCFAbsoluteTime( &info.createDate, &absoluteTime );
			
			CFGregorianDate dt = CFAbsoluteTimeGetGregorianDate( absoluteTime, NULL );
	
			double dsecs = floor(dt.second);
			unsigned int second = (unsigned int)dsecs;	
			double milliseconds = (dt.second - dsecs) * 1000.0;
	
			result.set( dt.year, dt.month, dt.day, 
						dt.hour, dt.minute, second, (unsigned int)milliseconds );
		}		
	}
	return result;
}

DateTime OSXFilePeer::getDateAccessed()
{
	DateTime result ;
	
	const char* fileName = getName().ansi_c_str();
	VCF_ASSERT( fileName != NULL );
	
	FSRef fileFS;
	if ( noErr == FSPathMakeRef( (const UInt8*)fileName, &fileFS, NULL ) ) {
		FSCatalogInfo info;
		
		if ( noErr == FSGetCatalogInfo( &fileFS, kFSCatInfoAccessDate, &info, NULL, NULL, NULL ) ) {
			CFAbsoluteTime  absoluteTime;
			UCConvertUTCDateTimeToCFAbsoluteTime( &info.accessDate, &absoluteTime );
			
			CFGregorianDate dt = CFAbsoluteTimeGetGregorianDate( absoluteTime, NULL );
	
			double dsecs = floor(dt.second);
			unsigned int second = (unsigned int)dsecs;	
			double milliseconds = (dt.second - dsecs) * 1000.0;
	
			result.set( dt.year, dt.month, dt.day, 
						dt.hour, dt.minute, second, (unsigned int)milliseconds );
		}		
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
		oflags &= ~O_RDONLY;
		oflags &= ~O_WRONLY;
		
		oflags |= O_RDWR;
	}
	
	fileHandle_ = ::open( fileName.ansi_c_str(), oflags );
	if ( -1 == fileHandle_ ) {
		fileHandle_ = 0;
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to open the specified file " + fileName + ", Errno: " + OSXStringUtils::getErrnoString(errno) ));
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
	searchIterator_ = NULL;
	
	searchData_ = new FileSearchData();
	
	searchData_->searchFileRefs.resize(MaxRequestCountPerIteration);
	searchData_->searchCatalogInfos.resize(MaxRequestCountPerIteration);
	searchData_->currentSearchIndex = 0;
	searchData_->searchCount = 0;
	
	
	finder->internal_updateToActiveFinder();
}







File* OSXFilePeer::findNextFileInSearch( Directory::Finder* finder )
{
	File* result = NULL;
	
	bool isDir = false;
	bool ok = false;
	ulong32 fileAttribs;
	
	
	while ( true ) {
		OSStatus getCatInfoRes = 0;
	
		result = NULL;
		finder->getFileInfo().internal_setStatMask( File::smStatNone );
		isDir = false;
		ok = false;
		
		if ( NULL == searchIterator_ ) {
			const char* startDir = getName().ansi_c_str();			
			FSRef startFS;
			if ( noErr == FSPathMakeRef( (const UInt8*)startDir, &startFS, NULL ) ) {
				if ( noErr == FSOpenIterator( &startFS, kFSIterateFlat, &searchIterator_ ) ) {									
					
					getCatInfoRes = FSGetCatalogInfoBulk( searchIterator_, MaxRequestCountPerIteration,
														 &searchData_->searchCount, NULL, 
														 defaultSearchFlags, 
														 &searchData_->searchCatalogInfos[0], 
														 &searchData_->searchFileRefs[0], NULL, NULL );
					if ( noErr == getCatInfoRes || getCatInfoRes == errFSNoMoreItems ) {
						searchData_->currentSearchIndex = 0;
						ok = true;
					}
				}
			}			
		}	
		else if (searchData_->currentSearchIndex >= (searchData_->searchCount - 1) ) {			
			getCatInfoRes = FSGetCatalogInfoBulk( searchIterator_, MaxRequestCountPerIteration,
												 &searchData_->searchCount, NULL, 
												 defaultSearchFlags, 
												 &searchData_->searchCatalogInfos[0], 
												 &searchData_->searchFileRefs[0], NULL, NULL );
			if ( noErr == getCatInfoRes ) {
				searchData_->currentSearchIndex = 0;
				ok = true;
			}
		}	
		else {			
			searchData_->currentSearchIndex ++;
			ok = true;
		}
		
		
		if ( ok ) {
			FSRef& currentFSRef = searchData_->searchFileRefs[searchData_->currentSearchIndex];
			FSCatalogInfo& currentCatInfo = searchData_->searchCatalogInfos[searchData_->currentSearchIndex];
			
			FInfo * finderInfo = (FInfo *)&currentCatInfo.finderInfo[0];
			isDir = ((currentCatInfo.nodeFlags & kFSNodeIsDirectoryMask) == kFSNodeIsDirectoryMask) ? true : false;
			
			fileAttribs = OSX_convertAttributesFromSystemSpecific( &currentCatInfo );
			
			//check skip conditions.
			//either we are a directory and the finder is only interested in files or
			//we're NOT a directorym and the we're only interested in directories,
			//or the filter mask is set to some value other than faNone, and the current
			//file attributes don't match anything in the mask.
			if ( ( isDir && finder->getCurrentDisplayOrder() == Directory::Finder::dmFiles ) ||
			     ( !isDir && ( ( finder->getCurrentDisplayOrder() == Directory::Finder::dmDirs ) ||
			                   ( ( File::faNone != finder->getMaskFilterFileAttribs() ) && 
			                     ( 0 == ( fileAttribs & finder->getMaskFilterFileAttribs() ) ) ) ) ) ) {
				continue;
			}
			
			result = &finder->getFileInfo();
			File::StatMask statMask = (File::StatMask)(finder->getStatMask() & ~File::smAttributes);
			result->internal_removeFromStatMask( statMask );
			
			char tmp[ PATH_MAX ];
			FSRefMakePath( &currentFSRef, (UInt8*)tmp, PATH_MAX - 1 );
			
			result->internal_setFileAttributes( fileAttribs );
			result->internal_addToStatMask( File::smAttributes );
			
			result->internal_setFileName( file_->getName() + FilePath::getBaseName( tmp,true) );
			
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
						if ( finder->canRecurseDown() )	{
							finder->goDownDir( result );
						} 
						else {
							// continue the search in the next subdirectory
							finder->continueSearch( result );
						}
					}
				}

				if ( NULL != result ) {
					// file found
					break;
				}
			}
		}
		else {
			if ( getCatInfoRes == errFSNoMoreItems ) {
				if ( NULL != searchIterator_ ) {
					endFileSearch( finder );

					// what do we need to do next ?
					finder->continueSearch( result );
				}
				break;
			}
			else if ( getCatInfoRes != noErr ) {
			
				throw RuntimeException( MAKE_ERROR_MSG_2("Error searching for files.") );
			}
			else {
				endFileSearch( finder );
			}
		}		
	}
	
	finder->setCurrentElement( result );
	
	return result;
}

void OSXFilePeer::endFileSearch( Directory::Finder* finder )
{
	if ( NULL != searchIterator_ ) {
		FSCloseIterator(searchIterator_);
		searchIterator_ = NULL;
	}
	delete searchData_;
	searchData_ = NULL;
}
	


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/12/04 20:58:32  ddiego
*more osx impl work. foundationkit is mostly complete now.
*
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


