//Win32FilePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;



Win32FilePeer::Win32FilePeer( File* file )
{
	findData_ = NULL;
	searchHandle_ = NULL;

	file_ = file;

	// will have a value when opening the file
	fileHandle_ = NULL;
}

Win32FilePeer::~Win32FilePeer()
{
	if ( NULL != findData_ ) {
		delete findData_;
	}
}

void Win32FilePeer::setFile( File* file )
{
	// close any open handles
	close(); // %%%
	
	findData_ = NULL;
	searchHandle_ = NULL;
	
	file_ = file;
	
	// will have a value when opening the file
	fileHandle_ = NULL;
}

void Win32FilePeer::create(  uint32 openFlags  )
{
	FilePath fp = getName();
	String filename = fp.transformToOSSpecific();
	
	if ( false == filename.empty() ){
		if ( NULL != fileHandle_ ){
			::CloseHandle( fileHandle_ );
		}
		if ( FilePath::isDirectoryName( filename ) ) {
			fileHandle_ = NULL;
			std::vector<String> dirPaths;
			String tmp = filename;
			int pos = tmp.find( "\\" );
			while ( pos != String::npos ) {
				dirPaths.push_back( tmp.substr( 0, pos ) );
				tmp.erase( 0, pos+1 );
				pos = tmp.find( "\\" );
			}
			if ( dirPaths.size() == 1 ) {
				String dir = dirPaths[0];
				if ( dir[dir.size()-1] != ':' ) {
					throw BasicFileError( "Unable to create directory \"" + filename + "\", path too short or incorrect." );
				}
			}
			else if ( dirPaths.size() < 2 ) {
				throw BasicFileError( "Unable to create directory \"" + filename + "\", path too short or incorrect." );
			}
			std::vector<String>::iterator it = dirPaths.begin();
			String dirPath = *it;
			it++;
			while ( it != dirPaths.end() ) {
				dirPath += "\\" + *it;

				BOOL res = FALSE;
				if ( System::isUnicodeEnabled() ) {
					res = ::CreateDirectoryW( dirPath.c_str(), NULL );
				}
				else {
					res = ::CreateDirectoryA( dirPath.ansi_c_str(), NULL );
				}

				if ( !res ) {
					int err = GetLastError();
					if ( ERROR_ALREADY_EXISTS != err ) {
						throw BasicFileError( "Unable to create directory \"" + filename + "\"" );
					}
				}
				it++;
			}
		}
		else {
			//attach to the file
			FilePath fp = filename;
			String fileDir = fp.getPathName(true);
			if ( true == fileDir.empty() ){
				TCHAR currentDir[MAX_PATH];
				memset( currentDir, 0 , sizeof(currentDir) );
				GetCurrentDirectory( MAX_PATH, currentDir );
				filename = "\\" + filename;
				filename = currentDir +  filename;
			}

			DWORD rwFlags = 0;
			DWORD shFlags = 0;

			if ( openFlags & File::ofRead ) {
				rwFlags |= GENERIC_READ;
				shFlags |= FILE_SHARE_READ;
			}

			if ( openFlags & File::ofWrite ) {
				rwFlags |= GENERIC_WRITE;
				shFlags |= FILE_SHARE_WRITE;
			}

			if ( System::isUnicodeEnabled() ) {
				fileHandle_ = ::CreateFileW( filename.c_str(),
											rwFlags,
											shFlags,
											NULL,
											CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL,
											NULL );
			}
			else {
				fileHandle_ = ::CreateFileA( filename.ansi_c_str(),
											rwFlags,
											shFlags,
											NULL,
											CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL,
											NULL );
			}


			if ( (NULL == fileHandle_) || (INVALID_HANDLE_VALUE == fileHandle_) ){
				fileHandle_ = NULL;
				//throw exception
				throw BasicFileError("Unable to create the specified file");
			}
		}
	}
}


uint64 Win32FilePeer::getSize()
{
	uint64 result = 0;

	if ( NULL != fileHandle_ ) {
		uint32 resultLow = 0;
		uint32 resultHigh = 0;
		if ( NULL != fileHandle_ ){
			resultLow = ::GetFileSize( fileHandle_, (DWORD*)&resultHigh );
			result = makeUInt64( resultHigh, resultLow );
		}
	}
	else {
		WIN32_FILE_ATTRIBUTE_DATA fileAttribData;	
		
		int res;
		if ( System::isUnicodeEnabled() ) {
			res = ::GetFileAttributesExW( getName().c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
		} 
		else {
			res = ::GetFileAttributesExA( getName().ansi_c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
		}

		result = result = makeUInt64( fileAttribData.nFileSizeHigh, fileAttribData.nFileSizeLow );
	}

	return result;
}

DateTime Win32FilePeer::getDateModified()
{
	DateTime result ;

	WIN32_FILE_ATTRIBUTE_DATA fileAttribData;	
	
	String fileName = getName();
	VCF_ASSERT( !fileName.empty() );

	int res;
	if ( System::isUnicodeEnabled() ) {
		res = ::GetFileAttributesExW( fileName.c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
	} 
	else {
		res = ::GetFileAttributesExA( fileName.ansi_c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
	}

	if ( res ) {
		result = Win32FilePeer::convertFileTimeToDateTime( fileAttribData.ftLastWriteTime );		
	}
	else {
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to retreive file attributes for file " + fileName) );
	}
	
	return result;
}

DateTime Win32FilePeer::getDateCreated()
{
	DateTime result ;

	WIN32_FILE_ATTRIBUTE_DATA fileAttribData;	
	
	String fileName = getName();
	VCF_ASSERT( !fileName.empty() );

	int res;
	if ( System::isUnicodeEnabled() ) {
		res = ::GetFileAttributesExW( fileName.c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
	} 
	else {
		res = ::GetFileAttributesExA( fileName.ansi_c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
	}

	if ( res ) {
		result = Win32FilePeer::convertFileTimeToDateTime( fileAttribData.ftCreationTime );		
	}
	else {
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to retreive file attributes for file " + fileName) );
	}
	
	return result;
}

DateTime Win32FilePeer::getDateAccessed()
{
	DateTime result ;

	WIN32_FILE_ATTRIBUTE_DATA fileAttribData;	
	
	String fileName = getName();
	VCF_ASSERT( !fileName.empty() );

	int res;
	if ( System::isUnicodeEnabled() ) {
		res = ::GetFileAttributesExW( fileName.c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
	} 
	else {
		res = ::GetFileAttributesExA( fileName.ansi_c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData );
	}

	if ( res ) {
		result = Win32FilePeer::convertFileTimeToDateTime( fileAttribData.ftLastAccessTime );		
	}
	else {
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to retreive file attributes for file " + fileName) );
	}
	
	return result;
}


// directory search support
void Win32FilePeer::initDataSearch()
{
	if ( NULL == findData_ ) {
		if ( System::isUnicodeEnabled() ) {
			findData_ = new Win32FindDataW;
		} else {
			findData_ = new Win32FindDataA;
		}
		if ( NULL == findData_ ) {
			throw NoFreeMemException(); 
		}
	}
}

void Win32FilePeer::initFileSearch( Directory::Finder* finder )
{
	initDataSearch();

	searchHandle_ = NULL;

	// other initialize of the finder before starting the search in it

	finder->internal_updateToActiveFinder();
}

File* Win32FilePeer::findNextFileInSearch( Directory::Finder* finder )
{
	// ::FindFirstFileEx is better suited to look for subdirectories but it is unsupported by win98

	File* file = NULL;

	bool unicodeEnabled = System::isUnicodeEnabled();

	bool isDir = false;

	bool ok;
	uint32 fAttribs;

	// looping until we find the directory/file matching the filter
	while ( true )
	{
		file = NULL;
		finder->getFileInfo().internal_setStatMask( File::smStatNone );
		isDir = false;

		// are we starting a new search ?
		if ( NULL == searchHandle_ ) {
			// Remarks: 1 - do not use searchPostfix_ != L"*", like: L"*.cpp", because there is 
			//				      there is a bug that gives error when the directory is empty! :(
			//				      Is this happening only with Unicode ? or with the searchPrefix_ ?
			//
			//				  2 - Do not use '\\' and '/' at the same time, beside the prefix L"\\\\?\\",
			//              otherwise ::FindFirstFileW() could fail.
			String searchDirFilter = String( L"\\\\?\\" )+ getName() + String( L"*" );

			if ( unicodeEnabled ) {
				searchHandle_ = ::FindFirstFileW( searchDirFilter.c_str(), &((Win32FindDataW*)findData_)->findData_ );
			} else {
				searchHandle_ = ::FindFirstFileA( searchDirFilter.ansi_c_str(), &((Win32FindDataA*)findData_)->findData_ );
			}
			ok = ( INVALID_HANDLE_VALUE != searchHandle_ );

		} 
		else {
			if ( unicodeEnabled ) {
				ok = ( 0 != ::FindNextFileW( searchHandle_, &((Win32FindDataW*)findData_)->findData_ ) );
			} 
			else {
				ok = ( 0 != ::FindNextFileA( searchHandle_, &((Win32FindDataA*)findData_)->findData_ ) );
			}
		}

		if  ( ok ) {
			if ( unicodeEnabled ) {
				fAttribs = Win32FilePeer::convertAttributesFromSystemSpecific( ((Win32FindDataW*)findData_)->findData_.dwFileAttributes );
			} 
			else {
				fAttribs = Win32FilePeer::convertAttributesFromSystemSpecific( ((Win32FindDataA*)findData_)->findData_.dwFileAttributes );
			}
			
			// first filtering for attributes
			isDir = ( 0 != ( fAttribs & File::faDirectory ) );
			if ( ( isDir && finder->getCurrentDisplayOrder() == Directory::Finder::dmFiles ) ||
			     ( !isDir && ( ( finder->getCurrentDisplayOrder() == Directory::Finder::dmDirs ) ||
			                   ( ( File::faNone != finder->getMaskFilterFileAttribs() ) && 
			                     ( 0 == ( fAttribs & finder->getMaskFilterFileAttribs() ) ) ) ) ) ) {
				continue;
			}

			// to test the time: with and without
			file = updateFindDataInfos( &finder->getFileInfo(), findData_, (File::StatMask)( finder->getStatMask() & ~File::smAttributes ) );
			file->internal_setFileAttributes( fAttribs );
			file->internal_addToStatMask( File::smAttributes );

			if ( isDir && !finder->getAllowSpecialDirs() ) {
				if ( file->getName() == L"." || file->getName() == L".." ) {
					continue;
				}
			}

			// finally the full filename
			file->internal_setFileName( file_->getName() + file->getName() );
		}


		if ( NULL != file ) {
			// filtering
			FileSearchFilter* filter = finder->getSearchFilterFileObject();
			if ( NULL != filter ) {
				file = filter->passSearchFilter( file, dynamic_cast<const Directory*>(file_), finder );
			}

			// recursion management
			if ( NULL != file ) {
				// ok we found a subdirectory matching the filter
				// now recursion into this subdirectory
				if ( isDir ) {
					if ( finder->getRecurse() ) {
						if ( finder->canRecurseDown() )	{
							this->goDirDown( finder, file );
						} 
						else {
							// continue the search in the next subdirectory
							continueSearch( finder, file );
						}
					}
				}

				if ( NULL != file ) {
					// file found
					break;
				}
			}
		} 
		else {
			DWORD searchErr = ::GetLastError();
			
			// end of search or error
			if ( ERROR_NO_MORE_FILES == searchErr )  {
				if ( INVALID_HANDLE_VALUE != searchHandle_ ) {
					this->endFileSearch( finder );

					// what do we need to do next ?
					continueSearch( finder, file );
				}
				break;
			}			
			else if ( (ERROR_ACCESS_DENIED == searchErr) && (INVALID_HANDLE_VALUE == searchHandle_) )  {
				endFileSearch( finder );
				continueSearch( finder, file );
				break;
			}
			else {
				String dirInfo = "\ndirectory: " + file_->getName();
				String error = "findNextFileInSearch: " + VCFWin32::Win32Utils::getErrorString( GetLastError() ) + dirInfo ;
				throw BasicException( error );
			}
		}

	} // while ( true )

	finder->setCurrentElement( file );

	return file;
}

void Win32FilePeer::endFileSearch( Directory::Finder* finder )
{
	if ( NULL != searchHandle_ && INVALID_HANDLE_VALUE != searchHandle_ ) {
		if ( !::FindClose( searchHandle_ )) {
			String error = "endFileSearch: " + VCFWin32::Win32Utils::getErrorString( GetLastError() );
			throw BasicException( error );
		}
	}

	searchHandle_ = NULL;
}

void Win32FilePeer::continueSearch( Directory::Finder* finder, File* file )
{
	finder->continueSearch( file );
}

void Win32FilePeer::goDirDown( Directory::Finder* finder, File* file )
{
	
	finder->goDownDir( file );
}

void Win32FilePeer::goDirUp( Directory::Finder* finder, File* file )
{

	finder->goUpDir( file );
}

/*static*/ void Win32FilePeer::copyFromAttributeData( File* file, WIN32_FILE_ATTRIBUTE_DATA& fileAttribData, File::StatMask statMask/*=File::smMaskAll*/ )
{
	// throw if errors
	file->internal_removeFromStatMask( statMask );
	
	if ( statMask & File::smAttributes ) {
		file->internal_setFileAttributes( Win32FilePeer::convertAttributesFromSystemSpecific( fileAttribData.dwFileAttributes ) );
	}	

	// we are ok if here
	file->internal_addToStatMask( statMask );
}


bool Win32FilePeer::isExecutable()
{
	String ext = FilePath::getExtension( getName() );

	return ( ext == ".exe" || ext == ".com" || ext == ".dat" ) ? true : false;
}

/*static*/ File* Win32FilePeer::updateFindDataInfos( File* file, Win32FindData* findData, File::StatMask statMask/*=File::smMaskAll*/ )
{
	// throw in copyFromAttributeData if errors

	file->internal_removeFromStatMask( statMask );

	WIN32_FILE_ATTRIBUTE_DATA fileAttribData;
	if ( System::isUnicodeEnabled() ) {
			Win32FindDataW* w = ((Win32FindDataW*)findData);
			//WIN32_FIND_DATAW& dataW2 = w->findData_ ;

			WIN32_FIND_DATAW& dataW = ((Win32FindDataW*)findData)->findData_ ;

			file->internal_setFileName( dataW.cFileName );

      fileAttribData.dwFileAttributes = dataW.dwFileAttributes ;
      fileAttribData.ftCreationTime   = dataW.ftCreationTime   ;
      fileAttribData.ftLastAccessTime = dataW.ftLastAccessTime ;
      fileAttribData.ftLastWriteTime  = dataW.ftLastWriteTime  ;
      fileAttribData.nFileSizeHigh    = dataW.nFileSizeHigh    ;
      fileAttribData.nFileSizeLow     = dataW.nFileSizeLow     ;

			copyFromAttributeData( file, fileAttribData, statMask );
	} else {
			WIN32_FIND_DATAA& dataA = ((Win32FindDataA*)findData)->findData_ ;

			file->internal_setFileName( dataA.cFileName );

      fileAttribData.dwFileAttributes = dataA.dwFileAttributes ;
      fileAttribData.ftCreationTime   = dataA.ftCreationTime   ;
      fileAttribData.ftLastAccessTime = dataA.ftLastAccessTime ;
      fileAttribData.ftLastWriteTime  = dataA.ftLastWriteTime  ;
      fileAttribData.nFileSizeHigh    = dataA.nFileSizeHigh    ;
      fileAttribData.nFileSizeLow     = dataA.nFileSizeLow     ;

			copyFromAttributeData( file, fileAttribData, statMask );
	}

	//file->fileType_          = 0;
	//file->creatorType_       = 0;
	//file->finderFlags_       = 0;

	file->internal_addToStatMask( statMask );

	return file;
}

void Win32FilePeer::updateStat( File::StatMask statMask/*=File::smMaskAll*/ )
{
	// this is very similar to updateFindDataInfos but using a different data structure

	String fileName = getName();

	//VCF_ASSERT( !FilePath::getPathName( fileName, true ).empty() );	
	VCF_ASSERT( !fileName.empty() );	

	WIN32_FILE_ATTRIBUTE_DATA fileAttribData;

	file_->internal_removeFromStatMask( statMask );

	int res;
	if ( System::isUnicodeEnabled() ) {
		if ( res = ::GetFileAttributesExW( getName().c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData ) ) {
			copyFromAttributeData( file_, fileAttribData, statMask );
		}
	} 
	else {
		if ( res = ::GetFileAttributesExA( getName().ansi_c_str(), ::GetFileExInfoStandard, (void*)&fileAttribData ) ) {
			copyFromAttributeData( file_, fileAttribData, statMask );
		}
	}

	if( !res ) {
		String error = "updateStat: " + VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}
}

/*virtual*/ void Win32FilePeer::setFileAttributes( const File::FileAttributes fileAttributes )
{
	file_->internal_removeFromStatMask( File::smAttributes );

	try {
		bool unicodeEnabled = System::isUnicodeEnabled();
		if ( unicodeEnabled ) {
			uint32 dwFileAttributes = Win32FilePeer::convertAttributesToSystemSpecific( fileAttributes );
			if ( ! ::SetFileAttributesW( file_->getName().c_str(), dwFileAttributes ) ) {
				String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				throw BasicException( error );
			}
		} else {
			uint32 dwFileAttributes = Win32FilePeer::convertAttributesToSystemSpecific( fileAttributes );
			if ( ! ::SetFileAttributesA( file_->getName().ansi_c_str(), dwFileAttributes ) ) {
				String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				throw BasicException( error );
			}
		}
	}
	catch ( BasicException& /*be*/ ) {
		throw; // re-throw
	}
	catch( ... ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( MAKE_ERROR_MSG_2( error ) );
	}

	file_->internal_setFileAttributes( fileAttributes );
	file_->internal_addToStatMask( File::smAttributes );
	return;
}

void Win32FilePeer::setDateModified( const DateTime& dateModified )
{
	// see CFile::SetStatus(LPCTSTR lpszFileName, const CFileStatus& status)
	// see AfxTimeToFileTime;

	file_->internal_removeFromStatMask( File::smDateModified );

	try {
		bool unicodeEnabled = System::isUnicodeEnabled();

		// DateTime --> systemTime
		SYSTEMTIME st;
		FILETIME   ftUTC;
		HANDLE hFile = NULL;

		uint32 y, m, d, h, min, s, ms;
		dateModified.get( &y, &m, &d, &h, &min, &s, &ms );

		if ( ( y < 1601 ) || ( 30827 < y ) ) {
			throw BasicException( "The SYSTEMTIME structure doesn't allow dates outside the range [1601,30827]" );
		}

		st.wYear   = (WORD)y;
		st.wMonth  = (WORD)m;
		st.wDayOfWeek = dateModified.getWeekDay();
		st.wDay    = (WORD)d;
		st.wHour   = (WORD)h;
		st.wMinute = (WORD)min;
		st.wSecond = (WORD)s;
		st.wMilliseconds = ms;

		// convert system time to filetime
		if ( !::SystemTimeToFileTime( &st, &ftUTC ) ) { // stUTC --> ftUTC
			String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
			throw BasicException( error );
		}

		if ( unicodeEnabled ) {
			hFile = ::CreateFileW( file_->getName().c_str(), GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) {
				String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				throw BasicException( error );
			}
		} 
		else {			
			hFile = ::CreateFileA( file_->getName().ansi_c_str(), GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) {
				String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				throw BasicException( error );
			}
		}

		if (! ::SetFileTime( hFile, NULL, NULL, &ftUTC ) ) {
			String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
			throw BasicException( error );
		}

		if (! ::CloseHandle(hFile)) {
			String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
			throw BasicException( error );
		}

	}
	catch ( BasicException& /*be*/ ) {
		throw; // re-throw
	}
	catch( ... ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( MAKE_ERROR_MSG_2( error ) );
	}


	file_->internal_addToStatMask( File::smDateModified );
}

/*static*/ uint32 Win32FilePeer::convertAttributesFromSystemSpecific( const uint32& dwAttributes )
{
	uint32 fileAttributes = File::faNone;

	if ( dwAttributes & FILE_ATTRIBUTE_READONLY ) {
		fileAttributes += File::faReadOnly;
	}
	if ( dwAttributes & FILE_ATTRIBUTE_HIDDEN ) {
		fileAttributes += File::faHidden;
	}
	if ( dwAttributes & FILE_ATTRIBUTE_SYSTEM ) {
		fileAttributes += File::faSystem;
	}
	if ( dwAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
		fileAttributes += File::faDirectory;
	}
	if ( dwAttributes & FILE_ATTRIBUTE_ARCHIVE ) {
		fileAttributes += File::faArchive;
	}
#if (_MSC_VER >= 1300)
	// vc7 and above
	if ( dwAttributes & FILE_ATTRIBUTE_DEVICE ) {
		fileAttributes += File::faDevice;
	}
#endif
	if ( dwAttributes & FILE_ATTRIBUTE_NORMAL ) {
		fileAttributes += File::faNormal;
	}

	return fileAttributes;
}

/*static*/ uint32 Win32FilePeer::convertAttributesToSystemSpecific( File::FileAttributes fileAttributes )
{
	uint32 dwAttributes = 0;

	if ( fileAttributes & File::faReadOnly ) {
		dwAttributes += FILE_ATTRIBUTE_READONLY;
	}
	if ( fileAttributes & File::faHidden ) {
		dwAttributes += FILE_ATTRIBUTE_HIDDEN;
	}
	if ( fileAttributes & File::faSystem ) {
		dwAttributes += FILE_ATTRIBUTE_SYSTEM;
	}
	if ( fileAttributes & File::faDirectory ) {
		dwAttributes += FILE_ATTRIBUTE_DIRECTORY;
	}
	if ( fileAttributes & File::faArchive ) {
		dwAttributes += FILE_ATTRIBUTE_ARCHIVE;
	}
#if (_MSC_VER >= 1300)
	// vc7 and above
	if ( fileAttributes & File::faDevice ) {
		dwAttributes += FILE_ATTRIBUTE_DEVICE;
	}
#endif
	if ( fileAttributes & File::faNormal ) {
		dwAttributes += FILE_ATTRIBUTE_NORMAL;
	}

	return dwAttributes;
}


void Win32FilePeer::open( const String& fileName, uint32 openFlags, File::ShareFlags shareFlags/*=File::shMaskAny*/ )
{
	//check initial arguments
	uint32 f1 =  File::ofNone;
	VCF_ASSERT( openFlags != f1 );



	String winFileName = fileName;

	//attach to the file
	FilePath fp = winFileName;
	String fileDir = fp.getPathName(true);
	if ( true == fileDir.empty() ){
		TCHAR currentDir[MAX_PATH];
		memset( currentDir, 0 , sizeof(currentDir) );
		GetCurrentDirectory( MAX_PATH, currentDir );
		winFileName = "\\" + winFileName;
		winFileName = currentDir +  winFileName;
	}
	
	DWORD rwFlags = 0;
	DWORD shFlags = 0;
	DWORD createFlags = OPEN_EXISTING;

	if ( openFlags & File::ofRead ) {
		rwFlags |= GENERIC_READ;
	}

	if ( openFlags & File::ofWrite || openFlags & File::ofAppend ) {
		rwFlags |= GENERIC_WRITE;
	}

	if ( shareFlags & File::shRead ) {
		shFlags |= FILE_SHARE_READ;
	}

	if ( shareFlags & File::shWrite ) {
		shFlags |= FILE_SHARE_WRITE;
	}
	

	if ( System::isUnicodeEnabled() ) {
		fileHandle_ = ::CreateFileW( winFileName.c_str(),
			rwFlags,
			shFlags,
			NULL,
			createFlags,
			FILE_ATTRIBUTE_NORMAL,
			NULL );
	}
	else {
		fileHandle_ = ::CreateFileA( winFileName.ansi_c_str(),
			rwFlags,
			shFlags,
			NULL,
			createFlags,
			FILE_ATTRIBUTE_NORMAL,
			NULL );
	}
	
	
	if ( (NULL == fileHandle_) || (INVALID_HANDLE_VALUE == fileHandle_) ){
		fileHandle_ = NULL;
		//throw exception
		String errmsg = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		StringUtils::trimWhiteSpaces( errmsg );
		throw BasicFileError( MAKE_ERROR_MSG_2( errmsg + " - file: " + winFileName ) );
	}
}

void Win32FilePeer::close()
{
	::CloseHandle( fileHandle_ );
	fileHandle_ = NULL;
}

void Win32FilePeer::remove()
{
	if ( NULL != fileHandle_ ){
		::CloseHandle( fileHandle_ );
		fileHandle_ = NULL;
	}

	String filename = getName();
	if ( filename[filename.size()-1] == '\\' ) {
		BOOL res = FALSE;
		if ( System::isUnicodeEnabled() ) {
			res = ::RemoveDirectoryW( filename.c_str() );
		}
		else {
			res = ::RemoveDirectoryA( filename.ansi_c_str() );
		}

		if ( !res ) {
			throw BasicFileError( MAKE_ERROR_MSG_2("Unable to remove directory \"" + filename + "\",\nprobably because the directory still contains objects.") );
		}
	}
	else {
		BOOL res = FALSE;
		if ( System::isUnicodeEnabled() ) {
			res = ::DeleteFileW( filename.c_str() );
		}
		else {
			res = ::DeleteFileA( filename.ansi_c_str() );
		}

		if ( !res ) {
			throw BasicFileError( MAKE_ERROR_MSG_2("Unable to remove file \"" + filename + "\".") );
		}
	}
}

void Win32FilePeer::move( const String& newFileName )
{
	BOOL err = FALSE;

	String fileName = getName();

	if ( System::isUnicodeEnabled() ) {
		err = ::MoveFileW( fileName.c_str(), FilePath::transformToOSSpecific( newFileName ).c_str() );
	}
	else {
		err = ::MoveFileA( fileName.ansi_c_str(), FilePath::transformToOSSpecific( newFileName ).ansi_c_str() );
	}

	if ( !err ) {
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to move file \"" + fileName + "\" to \"" + newFileName + "\".") );
	}
}

void Win32FilePeer::copyTo( const String& copyFileName )
{
	BOOL res = FALSE;

	String src = FilePath::transformToOSSpecific( getName() );
	String dest = FilePath::transformToOSSpecific( copyFileName );

	if ( System::isUnicodeEnabled() ) {
		res = ::CopyFileW( src.c_str(), dest.c_str(), FALSE );
	}
	else {
		res = ::CopyFileA( src.ansi_c_str(), dest.ansi_c_str(), FALSE );
	}

	if ( ! res ) {
		
		throw BasicFileError( MAKE_ERROR_MSG_2("Unable to copy \"" + src + "\" to \"" + copyFileName + "\".") );
	}

}


DateTime Win32FilePeer::convertFileTimeToDateTime( const FILETIME& ft )
{
	bool ok = false;
	DateTime dt;

	SYSTEMTIME st;

	// ft --> st
	if ( ::FileTimeToSystemTime( &ft, &st ) ) {
		dt.set( st.wYear, st.wMonth, st.wDay,
							st.wHour, st.wMinute, st.wSecond, 
							st.wMilliseconds );
		ok = true;
	}

	if ( !ok ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( MAKE_ERROR_MSG_2(error) );
	}

	return dt;
}

/*static*/ DateTime Win32FilePeer::convertUtcFileTimeToLocalDateTime( const FILETIME& ftUtc )
{
	bool ok = false;
	FILETIME ftLoc;
	SYSTEMTIME stLoc;
	DateTime dt;

	// ftUTC --> ftLocal
	// see help of VisualStudio.net for "File Times", at the end, though 
	if ( ::FileTimeToLocalFileTime( &ftUtc, &ftLoc ) ) {
		// ftLocal --> stLocal
		if ( ::FileTimeToSystemTime( &ftLoc, &stLoc ) ) {
			dt.set( stLoc.wYear, stLoc.wMonth, stLoc.wDay,
								stLoc.wHour, stLoc.wMinute, stLoc.wSecond, 
								stLoc.wMilliseconds );
			ok = true;
		}
	}

	if ( !ok ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( MAKE_ERROR_MSG_2(error) );
	}

	return dt;
}

/*static*/ String Win32FilePeer::getAlternateFileName( const String& fileName )
{
	String dosName;

	try {
		bool unicodeEnabled = System::isUnicodeEnabled();
		if ( unicodeEnabled ) {
			WIN32_FIND_DATAW findData;
			HANDLE searchHandle = ::FindFirstFileW( fileName.c_str(), &findData );
			if ( INVALID_HANDLE_VALUE != searchHandle ) {
				String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				throw BasicException( MAKE_ERROR_MSG_2(error) );
			}
			dosName = findData.cAlternateFileName;
		} else {
			WIN32_FIND_DATAA findData;
			HANDLE searchHandle = ::FindFirstFileA( fileName.ansi_c_str(), &findData );
			dosName = findData.cAlternateFileName;
			if ( INVALID_HANDLE_VALUE != searchHandle ) {
				String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				throw BasicException( MAKE_ERROR_MSG_2(error) );
			}
		}
	}
	catch( ... ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( MAKE_ERROR_MSG_2( error ) );
	}

	return dosName;
}


/**
$Id$
*/
