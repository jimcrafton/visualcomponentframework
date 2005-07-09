//Directory.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;




///////////////////////////////////////////////////////////////////////////////
// Directory::Finder

Directory::Finder::Finder( Directory* directoryToSearch, FileSearchFilter* filterFileObject/*=NULL*/, const bool& ownFilterFileObject/*=false*/ )
	: fileInfos_( L"" )	
{
	reset();

	owningDirectory_				= directoryToSearch;

	searchFilterFileObject_ = filterFileObject;
	ownFilterFileObject_		= ownFilterFileObject;
}

Directory::Finder::~Finder()
{
	FilePeer* dirPeer = owningDirectory_->getPeer();
	if ( NULL != dirPeer ) {
		dirPeer->endFileSearch( this );
	}

	if ( NULL != subfinders_ ) {

		std::vector<Directory::Finder*>::iterator it = subfinders_->begin();
		while ( it != subfinders_->end() ) {
			Directory::Finder* finder = *it;
			finder->free();
			it ++;
		}
		subfinders_->clear();
		delete subfinders_;
		subfinders_ = NULL;
	}

	if ( NULL != subdirs_ ) {
		std::vector<Directory*>::iterator it = subdirs_->begin();
		while ( it != subdirs_->end() ) {
			Directory* subDir = *it;
			subDir->free();
			it ++;
		}
		subdirs_->clear();
		delete subdirs_;
		subdirs_ = NULL;
	}

	if ( ownFilterFileObject_ && NULL != searchFilterFileObject_ ) {
		delete searchFilterFileObject_;
	}

	
}

void Directory::Finder::reset()
{
	fileInfos_.setName( L"" );

	subfinders_ = NULL;
	subdirs_ = NULL;
	owningDirectory_ = NULL;
	recursionLevel_ = 0;
	recursionLevelMax_ = -1;
	subdirs_ = NULL;

	goSearchAgain_ = false;
	currentElement_	= NULL;
	searchHasMoreElements_ = ( NULL != currentElement_ );

	searchFilterFileObject_ = NULL;
	ownFilterFileObject_ = false;
	maskFilterFileAttribs_ = File::faMaskAll;
	statMask_ = File::smMaskAll;

	displayMode_ = Directory::Finder::dmAny; // no limitations normally
	displayOrder_ = Directory::Finder::dmAny; // unsorted by default ( search in only one step )
	displayOrderCurrent_ = displayOrder_;

	allowSpecialDirs_ = false; // normally the dot dirs are useless ( "." and ".." )
	keepOSSpecificFormat_ = false; // by default we keep the native format

	recurse_ = false;

	rootSearchFinder_ = this;	// initialized for normal non-recursive use
	activeFinder_ = this;	// initialized for normal non-recursive use
	childFinder_ = NULL;
	parentFinder_ = NULL;
}

void Directory::Finder::setDisplayMode( DisplayMode displayMode )
{
	displayMode_ = displayMode;
	if ( ( dmFiles == displayMode_ && !recurse_ ) || dmDirs == displayMode_ ) {
		displayOrderCurrent_ = displayMode_;
	}
}

void Directory::Finder::setDisplayOrder( DisplayMode displayOrder )
{
	displayOrder_ = displayOrder;
	displayOrderCurrent_ = displayOrder;
	if ( ( dmFiles == displayMode_ && !recurse_ ) || dmDirs == displayMode_ ) {
		displayOrderCurrent_ = displayMode_;
	}
}

void Directory::Finder::setParentFinder( Finder* finder, const String& relPath, const int& previousRecursionLevel )
{
	rootSearchFinder_ = finder->rootSearchFinder_;
	recursionLevel_ = previousRecursionLevel + 1;
	
	setRecursion( finder->recurse_, finder->recursionLevelMax_ ); // finder->recurse_ always true here
	setDisplayMode( finder->displayMode_ );
	setDisplayOrder( finder->displayOrder_ );
	
	// relative path for files in this subdir
	relativePathToRootSearch_  = finder->relativePathToRootSearch_ + relPath;
	
	//finderSubdir->displayOrderCurrent_ = Directory::Finder::dmDirs;
	
	// inherits information from the parent finder
	rootSearchFinder_	= finder->rootSearchFinder_;
	maskFilterFileAttribs_	= finder->maskFilterFileAttribs_;
	statMask_	= finder->statMask_;
	setAllowSpecialDirs( finder->getAllowSpecialDirs() );
	
	// set the newly created subdir-finder as the active one
	rootSearchFinder_->activeFinder_ = this;
	
	// this will force the initialization of this new finder
	rootSearchFinder_->activeFinder_->currentElement_ = NULL;
	
	parentFinder_ = finder;
	finder->childFinder_ = this;
	
	// one level down
	// set the current subdirectory level for the active finder
	// attention: at this precise point the active finder is *not* exactly the current finder
	finder->rootSearchFinder_->activeFinder_->recursionLevel_ = previousRecursionLevel + 1;
	
	// do not adjust this here, it is too soon ( do it inside initFileSearch instead )
	// finder->rootSearchFinder_->relativePathToRootSearch_= finderSubdir->relativePathToRootSearch_;
	
	VCF_ASSERT( finder->childFinder_->parentFinder_ == finder );
}

void Directory::Finder::continueSearch( File* file )
{
	Directory::Finder::DisplayMode displayOrder1 = Directory::Finder::dmAny;
	Directory::Finder::DisplayMode displayOrder2 = Directory::Finder::dmAny;
	

	if ( Directory::Finder::dmFiles == displayOrder_ ) {
		displayOrder1 = Directory::Finder::dmFiles;
		displayOrder2 = Directory::Finder::dmDirs;
	} 
	else if ( Directory::Finder::dmDirs == displayOrder_ ) {
		displayOrder1 = Directory::Finder::dmDirs;
		displayOrder2 = Directory::Finder::dmFiles;
	}

	if ( Directory::Finder::dmAny != displayOrderCurrent_ && 
		   displayOrder1 == displayOrderCurrent_ ) {
		// 1st step done: we were searching for dir, now we search for files
		
		VCF_ASSERT( rootSearchFinder_->activeFinder_ == this );

		displayOrderCurrent_ = displayOrder2;

		// the 'dirs' search was completed. We need to state that it is not
		searchHasMoreElements_ = true;
		goSearchAgain_ = true;
	} 
	else { // if ( finder->displayOrderCurrent_ == displayOrder2 ) {
		if ( recurse_ ) {
			goUpDir( file );
		} 
		else {
			rootSearchFinder_->activeFinder_->goSearchAgain_ = false;
		}
	}
}

void Directory::Finder::goDownDir( File* file )
{
	// Remark:
	// 1) it doesn't change file
	// 2) it doesn't change the finder
	// 3) it changes the rootSearchFinder_->activeFinder_ which is the created finder for this subdir

	// - please remove or comment the VCF_ASSERT in the future

	// if we are here we have found at least this element, so,
	// we need to store this information before is forgotten
	Directory::Finder* activeFinder = rootSearchFinder_->activeFinder_;
	VCF_ASSERT( activeFinder == this );
	currentElement_ = file;	
	searchHasMoreElements_ = ( NULL != currentElement_ );
	searchHasMoreElements_ = true;

	// store the current subdirectory level before switching subdir
	int previousRecursionLevel = activeFinder->recursionLevel_;

	// will return this dir, but next childFinder_ will be used
	String directorySeparator;
	if ( rootSearchFinder_->keepOSSpecificFormat_ ) {
		directorySeparator = FilePath::getDirectorySeparatorOSSpecific();
	} 
	else {
		directorySeparator = FilePath::getDirectorySeparator();
	}
	String relPath = FilePath::getBaseName( file->getName(), true ) + directorySeparator; // this subdirectory name just found
	file->internal_setFileName( file->getName() + directorySeparator );

	// simple memory management
	// so it doesn't need to keep in memory any subdirectory found
	Directory* dir = NULL;
	const bool manageMemory = true; // it works fine
	if ( ( manageMemory ) &&
		   ( previousRecursionLevel + 1 < rootSearchFinder_->subdirs_->size() ) ) {
		// we cannot use previousRecursionLevel+0 because 
		// we usually have ( &dir->finder_->fileInfos_ == file ) when we are here
		// and that would reset dir->finder_ when calling dir->findFiles
		dir = (*rootSearchFinder_->subdirs_)[ previousRecursionLevel + 1 ];
		dir->setName( file->getName() );	

	} 
	else {
		dir = new Directory( file->getName() );
		rootSearchFinder_->subdirs_->push_back( dir );
	}

	// only the rootSearchFinder_ is the possible owner of the searchFilterFileObject_
	Directory::Finder* finderSubdir = dir->findFiles( searchFilterFileObject_, false );

	finderSubdir->setParentFinder( this, relPath, previousRecursionLevel );

	if ( NULL == subfinders_ ) {
		subfinders_ = new std::vector<Directory::Finder*>();
	}
	rootSearchFinder_->subfinders_->push_back( finderSubdir );
}

void Directory::Finder::goUpDir( File* file )
{
	// Remark:
	// 1) it doesn't change file
	// 2) it doesn't change the finder
	// 3) it changes the rootSearchFinder_->activeFinder_ which is the first up-dir with more elements to search

	// - please remove or comment the VCF_ASSERT in the future

	//VCF_ASSERT( NULL != finder->parentFinder_ ); // should be false only when finder->rootSearchFinder_

	if ( NULL != parentFinder_ ) {
		VCF_ASSERT( rootSearchFinder_->activeFinder_ == this );

		// we need to state right away here, that the search in this subdirectory was completed
		currentElement_ = file;
		searchHasMoreElements_ = ( NULL != currentElement_ ); // i.e. false. 

		// store the current subdirectory level before switching subdir
		int previousRecursionLevel = rootSearchFinder_->activeFinder_->recursionLevel_;

		// we go up one or more levels until we find one with the search not completed yet
		while( rootSearchFinder_->activeFinder_ != rootSearchFinder_ &&
						!rootSearchFinder_->activeFinder_->searchHasMoreElements_ ) {
				// detach this child from parent
				parentFinder_->childFinder_ = NULL;

				// set the parent as the active one
				rootSearchFinder_->activeFinder_ = rootSearchFinder_->activeFinder_->parentFinder_;

				// we just finished a search in the child, but we need to continue 
				// the search in the parent dir if it had more elements to search
				VCF_ASSERT( parentFinder_->searchHasMoreElements_ == true );
				rootSearchFinder_->activeFinder_->goSearchAgain_ = parentFinder_->searchHasMoreElements_;

				// one level up
				previousRecursionLevel--;
		}
		// set the current subdirectory level for the active finder ( not exactly the current one )
		rootSearchFinder_->activeFinder_->recursionLevel_ = previousRecursionLevel;

		rootSearchFinder_->relativePathToRootSearch_= rootSearchFinder_->activeFinder_->relativePathToRootSearch_;
		if ( NULL == rootSearchFinder_->activeFinder_->parentFinder_ ) {
			rootSearchFinder_->relativePathToRootSearch_.erase();
			rootSearchFinder_->activeFinder_->relativePathToRootSearch_.erase();
		}
	} else {
		// in the root directory for this recursive search we don't want to go forever
		rootSearchFinder_->activeFinder_->goSearchAgain_ = false;

		rootSearchFinder_->relativePathToRootSearch_.erase();
		rootSearchFinder_->activeFinder_->relativePathToRootSearch_.erase();
	}
}


void Directory::Finder::setRecursion( const bool& recurse, const int& recursionLevelMax/*=-1*/ )
{
	// Remark: displayOrder = true by default because that's the 
	//					setting that a user usually needs when doing recursion.

	recurse_ = recurse;
	recursionLevelMax_ = recursionLevelMax;

	if ( recurse_ ) {
		if ( 0 == recursionLevel_ && this  == rootSearchFinder_ ) {

			subdirs_ = new std::vector<Directory*>;
			if ( NULL == subdirs_ ) {
				throw NoFreeMemException();
			}
			subdirs_->reserve( ( -1 < recursionLevelMax_ ) ? recursionLevelMax_ : 100 );

			this->rootSearchFinder_ = this;
			activeFinder_ = this;
		//} else {
			//throw BasicException( "Only the finder at the root of the search can be initialized for recursion !" );
		}

		// updates displayOrderCurrent_
		setDisplayOrder( displayOrder_ );
	}
}

Directory::Finder* Directory::findFiles( const String& basenameFilterList/*=L""*/, const String& pathnameFilterList/*=L""*/ )
{
	FileSearchFilter* filterFileObject = NULL;

	Directory::Finder* result = NULL;

	//if ( NULL == finder_ ) {
		// creating a new finder
		filterFileObject = NULL;
		bool basenameEmpty = ( basenameFilterList.empty() || basenameFilterList == L"*" || basenameFilterList == L"*.*" );
		bool pathnameEmpty = ( pathnameFilterList.empty() || pathnameFilterList == L"*" || pathnameFilterList == L"*.*" );
		if ( !basenameEmpty || !pathnameEmpty ) {
			filterFileObject = new FileSearchFilterStandard( basenameFilterList, pathnameFilterList );
		}

		/*
	} 
	else {
		// resetting the existing finder
		finder_->reset();
		finder_->owningDirectory_				= this;

		filterFileObject = finder_->getSearchFilterFileObject();
		FileSearchFilterStandard* filterFileObjectStandard = dynamic_cast<FileSearchFilterStandard*>( filterFileObject );
		if ( NULL != filterFileObjectStandard ) {
			if ( filterFileObjectStandard->basenameFilterList_ != basenameFilterList || 
				   filterFileObjectStandard->pathnameFilterList_ != pathnameFilterList ) {
				filterFileObjectStandard->buildSearchFilters( basenameFilterList, pathnameFilterList );
			}
		} else {
			delete filterFileObject;
			filterFileObject = new FileSearchFilterStandard( basenameFilterList, pathnameFilterList );
		}
	}
	*/

	result = findFiles( filterFileObject, true );

	return result;
}

Directory::Finder* Directory::findFiles( FileSearchFilter* filterFileObject/*=NULL*/, const bool& ownFilterFileObject/*=false*/ )
{
	Directory::Finder* result = NULL;


	if ( FilePath::isRelativePath( fileName_ ) ) {
		String msg = Format("Please provide a full path name to the directory when performing a file search.\nPath: %s") % fileName_;
		throw BasicException( MAKE_ERROR_MSG_2( msg ) );
	}

	//if ( NULL == finder_ ) {

		result = new Directory::Finder( this, filterFileObject, ownFilterFileObject );
		if ( NULL == result ) {
			throw NoFreeMemException();
		}
		/*
	} else {
		finder_->reset();
		finder_->owningDirectory_				= this;
		finder_->setSearchFilterFileObject( filterFileObject, ownFilterFileObject );
	}
*/
	

	return result;
}

File* Directory::Finder::getCurrentElement() const
{
	return currentElement_;
}


bool Directory::Finder::nextElement()
{
	// continues the search until a valid element is found 
	// or the search is completed along all the allowed subdirectories
	while( true )
	{
		FilePeer* dirPeer = rootSearchFinder_->activeFinder_->owningDirectory_->getPeer();

		if ( !rootSearchFinder_->activeFinder_->searchHasMoreElements_ ) {
			dirPeer->initFileSearch( this );
		}

		// attention: this will change the activeFinder_ if it changes subdirectory level
		currentElement_ = dirPeer->findNextFileInSearch( rootSearchFinder_->activeFinder_ );

		// normally breaks and return the file/dir found to the user
		if ( currentElement_ ) {
			// if we want to display only files or directories names
			if ( ( currentElement_->isDirectory() && Directory::Finder::dmFiles == rootSearchFinder_->displayMode_ ) ||
				   ( !currentElement_->isDirectory() && Directory::Finder::dmDirs == rootSearchFinder_->displayMode_ ) ) {
				searchHasMoreElements_ = true;
				continue;
			} 
			else {
				break;
			}
		} 
		else {
			// otherwise it continues ...
			// ... only when we are switching subdirectory during the recursion, 
			// or changing search mode between dmDirs and dmFiles
			if ( !rootSearchFinder_->activeFinder_->goSearchAgain_ ) {
				break;
			}
		}
	}

	searchHasMoreElements_ = ( NULL != currentElement_ );

	return searchHasMoreElements_;
}



///////////////////////////////////////////////////////////////////////////////
// Directory

Directory::Directory( const String& fileName )
: File( FilePath::makeDirectoryName( fileName ) )
{
	
}

Directory::Directory( const FilePath& filePath )
: File( FilePath::makeDirectoryName( filePath.getFileName() ) )
{
	
}

Directory::~Directory()
{
}



///////////////////////////////////////////////////////////////////////////////
// FileSearchFilterStandard

FileSearchFilterStandard::FileSearchFilterStandard( const String& basenameFilterList, const String& pathnameFilterList/*=L""*/, const String& separator/*=L";"*/ )
{	
	buildSearchFilters( basenameFilterList, pathnameFilterList, separator );
}

void FileSearchFilterStandard::buildSearchFilters( const String& basenameFilterList, const String& pathnameFilterList/*=L""*/, const String& separator/*=L";"*/ )
{
	basenameFilterList_ = basenameFilterList;
	pathnameFilterList_ = pathnameFilterList;
	separator_          = separator;

	searchFiltersBasename_.clear();

	if ( !basenameFilterList.empty() ) {
		int pos = 0, lastpos = 0;
		while ( String::npos != pos ) {
			pos = basenameFilterList.find( separator_, lastpos );
			if ( String::npos != pos ) {
				searchFiltersBasename_.push_back( basenameFilterList.substr( lastpos, pos ) );
				lastpos = pos + 1;
			}
		};
		searchFiltersBasename_.push_back( basenameFilterList.substr( lastpos, basenameFilterList.size() ) );
	}


	searchFiltersPathname_.clear();

	if ( !pathnameFilterList.empty() ) {
		String sdir;
		int pos = 0, lastpos = 0;
		while ( String::npos != pos ) {
			pos = pathnameFilterList.find( separator_, lastpos );
			if ( String::npos != pos ) {
				sdir = pathnameFilterList.substr( lastpos, pos );
				sdir = FilePath::transformToOSSpecific( sdir );
				searchFiltersPathname_.push_back( sdir );
				lastpos = pos + 1;
			}
		};
		sdir = pathnameFilterList.substr( lastpos, pathnameFilterList.size() );
		sdir = FilePath::transformToOSSpecific( sdir );
		searchFiltersPathname_.push_back( sdir );
	}
}

File* FileSearchFilterStandard::passSearchFilter( const File* file, const Directory* subdir, const Directory::Finder* finder )
{
	/*
	* The user is allowed to assume that all these arguments are never NULL.
	* this function must return NULL if it does not pass the filter !
	* All arguments are const to make sure the user knows what is doing.
	*/

	if ( 0 == searchFiltersBasename_.size() && 0 == searchFiltersPathname_.size() ) {
		return const_cast<File*>( file );
	}

	// Do not perform any fitering on directories 
	// otherwise we cannot recurse into any subdirectories
	// Use Finder::dmFiles instead if you want to find only files.
	bool isDir = const_cast<File*>(file)->isDirectory();
	if ( isDir ) {
		return const_cast<File*>( file );
	}


	String sf;

	bool pass = false;
	if ( 0 == searchFiltersBasename_.size() ) {
		pass = true;
	} else {
		searchFilterIterator_ = searchFiltersBasename_.begin();
		while ( searchFilterIterator_ != searchFiltersBasename_.end() ) {
			sf = *searchFilterIterator_ ++;

			if ( FilePath::wildCharsMatchName( file->getName(), sf ) ) {
				pass = true;
				break;
			}
		}
	}

	if ( pass ) {
		// no filter on path when no recursing
		if ( finder->getRecurse() ) {
			pass = false;
			if ( 0 == searchFiltersPathname_.size() ) {
				pass = true;
			} else {
				String path = subdir->getName();
				if ( finder->getKeepOSSpecificFormat() ) {
					path = FilePath::transformToOSSpecific( path );
				} else {
					path = FilePath::transformToNative( path );
				}
				searchFilterIterator_ = searchFiltersPathname_.begin();
				while ( searchFilterIterator_ != searchFiltersPathname_.end() ) {
					sf = *searchFilterIterator_ ++;
					
					int pos = subdir->getName().find( sf );
					if ( String::npos != pos ) {
						pass = true;
						break;
					}
				}
			}
		}
	}

	if ( pass ) {
		return const_cast<File*>( file );
	} else {
		return NULL;
	}

	return const_cast<File*>( file );
}



/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.5  2005/06/02 15:21:23  marcelloptr
*minor fix
*
*Revision 1.2.4.4  2005/03/15 01:51:51  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.2.4.3  2005/02/16 17:08:40  marcelloptr
*improved an error message
*
*Revision 1.2.4.1  2004/12/10 22:32:42  ddiego
*fixed bug in the Win32 file peer class that was not properly
*creating directories.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/23 00:56:37  ddiego
*added the latest changes to the File and Directory finder classes.
*
*Revision 1.1.2.5  2004/07/20 02:03:13  ddiego
*fixed some miscellaneous bugs in directory search code. Many
*thanks to Marcello for helping out on this.
*
*Revision 1.1.2.4  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.3  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.7  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.6.2.1  2004/03/19 21:25:57  ddiego
*just some minor noodlin
*
*Revision 1.6  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.4.3  2003/09/27 14:57:24  marcelloptr
*bugfix [813573] Directory ctor adds one separator too much
*
*Revision 1.5.4.2  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.5.4.1  2003/08/22 04:39:18  ddiego
*minor improvemtn to Diretory constructor, fixed bug in DefaultTableCellItem
*
*Revision 1.5  2003/05/17 20:37:24  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.16.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4.16.1  2003/03/12 03:12:09  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


