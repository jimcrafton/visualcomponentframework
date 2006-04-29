//FilePath.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


FilePath::FilePath()
{

}



FilePath::FilePath( const String& filename )
{
	filename_ = transformToNative( filename );
}



FilePath::FilePath( const FilePath& filePath )
//: Object(filePath)
{
	filename_ = transformToNative( filePath.filename_ );
}



FilePath::~FilePath()
{

}

String FilePath::getDriveSeparator()
{
#ifdef WIN32
	return L":";
#else
	return L"";
#endif
}

bool FilePath::isRelativePath( const String& filename )
{
	bool result = false;
	String drive = getDriveName( filename );

	VCFChar c = filename[0];
	if ( ( c != '/' && c != '\\' ) && ( drive.empty() ) ) {
		result = true;
	}
	else if ( c == '.' ) {
		// is relative if ( "./" or "../" at the beginning )
		int pos = filename.find_first_of( L"/\\" );
		result = ( ( pos == 1 ) ||
		           ( ( pos == 2 ) && ( filename[0] == L'.' ) ) );
	}
	return result;
}

bool FilePath::isDirectoryName( const String& path )
{
	VCFChar c = path[ path.size() - 1 ];
	bool result = ( c == '/' || c == '\\' );
	return result;
}

void FilePath::splitDrive( const String& fullname, String& drive, String& pathname )
{
	// DriveSeparator is included in drive

	size_t lastDrivePos = fullname.find_last_of( FilePath::getDriveSeparator() );

	if ( String::npos != lastDrivePos ) {
		drive = fullname.substr( 0, lastDrivePos + 1 );
		pathname  = fullname.substr( lastDrivePos + 1, fullname.size() - lastDrivePos - 1 );
	} else {
		drive.erase();
		pathname = fullname;
	}

	VCF_ASSERT( fullname == drive + pathname ); 
}

String FilePath::getDriveName( const String& fullname )
{
	// DriveSeparator is included in drive

	size_t lastDrivePos = fullname.find_last_of( FilePath::getDriveSeparator() );

	if ( String::npos != lastDrivePos ) {
		return fullname.substr( 0, lastDrivePos + 1 );
	} else {
		return String( L"" );
	}
}

void FilePath::splitPath( const String& fullname, String& path, String& name )
{
	// DirectorySeparator is included in path

	/**
	* Remarks:
	*
	*   The main reason why FilePath, looks for both '/' and '\\' under Windows in the 
	*   implementation of some of its member function, is that under Windows they are both used.
	*   By not doing this we can have the surprising effect of having a different behaviour 
	*   of the code under a Window and a 'nix platform.
	*
	*   A second reason is that this version works with both an OSSpecific and a Native formats,
	*   with a negligible performance penalty.
	*/

	size_t lastDirsepPos = fullname.find_last_of( L"/\\" );

	if ( lastDirsepPos != String::npos ) {
		path = fullname.substr( 0, lastDirsepPos + 1 );
		name  = fullname.substr( lastDirsepPos + 1, fullname.size() - lastDirsepPos - 1 );
	} else {
		path.erase();
		name = fullname;
	}

	VCF_ASSERT( fullname == path + name ); 
}

String FilePath::getPathName( const String& fullname, const bool& includeDriveName )
{
	// DirectorySeparator is included in path

	size_t lastDrivePos = String::npos;
	if ( !includeDriveName ) {
		lastDrivePos = fullname.find_last_of( FilePath::getDriveSeparator() );
	}

	size_t lastDirsepPos = fullname.find_last_of( L"/\\" );

	String path;
	if ( lastDrivePos != String::npos ) {
		if ( lastDirsepPos != String::npos ) {
			path = fullname.substr( lastDrivePos + 1, lastDirsepPos - lastDrivePos );
		} 
		else {
			path = fullname.substr( lastDrivePos + 1, fullname.size() - lastDrivePos );
		}
	} 
	else {
		if ( lastDirsepPos != String::npos ) {
			path = fullname.substr( 0, lastDirsepPos + 1 );
		} 
		else {
			path.erase();
		}
	}
	return path;
}

void FilePath::splitExtension( const String& fullname, String& root, String& ext )
{
	// ExtensionSeparator is included in ext

	size_t lastExtPos   = fullname.find_last_of( FilePath::getExtensionSeparator() );
	if ( lastExtPos != String::npos ) {
		root = fullname.substr( 0, lastExtPos );
		ext  = fullname.substr( lastExtPos, fullname.size() - lastExtPos );
	} else {
		root = fullname;
		ext.erase();
	}

	VCF_ASSERT( fullname == root + ext ); 
}

String FilePath::getBaseName( const String& fullname, const bool& includeExtension )
{
	size_t lastDirsepPos = fullname.find_last_of( L"/\\" );

	size_t lastExtPos = String::npos;
	if ( !includeExtension ) {
		lastExtPos = fullname.find_last_of( FilePath::getExtensionSeparator() );
	}

	String path;
	if ( lastDirsepPos != String::npos ) {
		if ( lastExtPos != String::npos ) {
			path = fullname.substr( lastDirsepPos + 1, lastExtPos - lastDirsepPos - 1 );
		} else {
			path = fullname.substr( lastDirsepPos + 1, fullname.size() - lastDirsepPos - 1 );
		}
	} else {
		if ( lastExtPos != String::npos ) {
			path = fullname.substr( 0, lastExtPos );
		} else {
			path = fullname;
		}
	}
	return path;
}

String FilePath::getExtension( const String& fullname )
{
	String path;
	size_t lastExtPos = fullname.find_last_of( FilePath::getExtensionSeparator() );
	if ( lastExtPos != String::npos ) {
		path = fullname.substr( lastExtPos, fullname.size() - 1 );
	}
	return path;
}



bool compareDirectoryComponent( const String& s1, const String& s2 )
{
	//returns true if s1 == s2 taking in consideration if the filesystem is case sensitive

	bool result = false;

#ifdef WIN32
	result = (StringUtils::lowerCase(s1) == StringUtils::lowerCase(s2));
#else
	result = (s1 == s2);
#endif

	return result;
}

String FilePath::getTransformedToRelativePathName( const String& fullPath, const String& workingPath )
{
	String result;

	String fullPathCopy, workDir;

	if ( workingPath.empty() ) {
		workDir = System::getCurrentWorkingDirectory();
	}
	else {
		//make sure it's a dir name
		workDir = FilePath::getPathName( workingPath, true );
	}

	if ( workDir.empty() ) {
		//ok we're screwed - throw an exception
		return L"";
	}

	workDir = FilePath::transformToNative( workDir );
	fullPathCopy = FilePath::transformToNative( fullPath );

	std::vector<String> workPathComponents = getPathComponents( workDir );
	std::vector<String> currentPathComponents = getPathComponents( fullPathCopy );

	String workingDrive = FilePath::getDriveName( workDir );
	String currentDrive = FilePath::getDriveName( fullPathCopy );

	if ( StringUtils::lowerCase(currentDrive) == StringUtils::lowerCase(workingDrive) ) {
		String sep = String( 1, (VCFChar)DirectorySeparator );
		String tmp;
		std::vector<String>::iterator workIt = workPathComponents.begin();
		size_t workingIndex = 0;
		size_t currentIndex = 0;
		while ( workIt != workPathComponents.end() ) {
			if ( (!compareDirectoryComponent( *workIt, currentPathComponents[currentIndex] )) || (workingIndex != currentIndex) ) {
				tmp += L".." + sep;
			}
			else {
				currentIndex ++;
				if ( currentIndex >= currentPathComponents.size() ) {
					currentIndex = currentPathComponents.size()-1;
				}
			}
			workingIndex ++;
			workIt ++;
		}

		if ( currentIndex > 0 ) { //this is because we are at the root / dir, don't
			//need the duplicate '/' character

			//test to see if we need to add a local dir
			if ( tmp.empty() ) {
				tmp += L"." + sep;
			}
			//only go on if we are NOT on the last element
			if ( currentIndex <= currentPathComponents.size()-1 ) {
				for ( size_t j=currentIndex; j<currentPathComponents.size(); j++ ) {
					if ( j < workPathComponents.size() ) {
						if ( !compareDirectoryComponent( workPathComponents[j], currentPathComponents[j]) ) {
							tmp += currentPathComponents[j];
						}
					}
					else {
						tmp += currentPathComponents[j];
					}
				}
			}
		}

		result = tmp + FilePath::getBaseName( fullPathCopy, true );
	}
	else {
		result = fullPathCopy;
	}


	return result;
}

String FilePath::getExpandedRelativePathName( const String& fullPath, const String& workingPath )
{
	if ( !FilePath::isRelativePath( fullPath ) ) {
		return FilePath::transformToNative( fullPath );
	}

	String result, workDir;

	String fullPathCopy = fullPath;

	if ( workingPath.empty() ) {
		workDir = System::getCurrentWorkingDirectory();
	}
	else {
		//make sure it's a dir name
		workDir = FilePath::getPathName( workingPath, true );
	}

	if ( workDir.empty() ) {
		//ok we're screwed - throw an exception
		return L"";
	}

	String sep = String( 1, (VCFChar)DirectorySeparator );
	workDir = FilePath::transformToNative( workDir );
	fullPathCopy = FilePath::transformToNative( fullPath );

	//store drive if present because getPathComponents() will remove it
	String drive = FilePath::getDriveName( workDir );

	std::vector<String> workPathComponents = getPathComponents( workDir );
	size_t pos = fullPathCopy.find( L".." + sep );
	if ( pos != String::npos ) {

		while ( pos != String::npos ) {
			if ( 0 != pos ) {
				//OOOOHHH error condition this is
				//is a malformed string ! - in other
				//words we have a relative path like foo/../bar - incorrect!!!
				//throw exception

				return L"";
			}

			//remove the last dir component
			//equivalent of "going back a dir", or "cd .."
			workPathComponents.pop_back();
			fullPathCopy.erase( 0, pos+3 );
			pos = fullPathCopy.find( L".." + sep, 0 );
		}
		std::vector<String>::iterator it = workPathComponents.begin();
		result = L"";
		while ( it != workPathComponents.end() ) {
			result += *it;
			it ++;
		}
		result += fullPathCopy;
		result = drive + result;
	}
	else {
		//ok look for ../ series
		pos = fullPathCopy.find( L"." + sep, 0 );
		//ok simply local working dir
		//remove the ./ notation and prepend the
		//working dir to file name
		if ( pos != String::npos ) {
			fullPathCopy.erase( pos, 2 );
			result = workDir + fullPathCopy;
		}
		else if ( fullPathCopy[0] != FilePath::DirectorySeparator ) {
			result = workDir + fullPathCopy;
		}
	}

	return result;
}

std::vector<String> FilePath::getPathComponents( const String& path )
{
	std::vector<String> pathComponents;

	//gets rid of drive
	String pathCopy = FilePath::getPathName( path, false );

	pathCopy = FilePath::transformToNative( pathCopy );

	String sep = String( 1, (VCFChar)DirectorySeparator );

	size_t pos = pathCopy.find( sep, 0 );
	size_t lastPos = 0;
	while ( pos != String::npos ) {
		pathComponents.push_back( pathCopy.substr( lastPos, (pos - lastPos)+1 ) );
		lastPos = pos+1;
		pos = pathCopy.find( sep, pos + 1 );
	}

	if ( ( !pathCopy.empty() ) && ( pathComponents.size() == 0 ) ) {
		throw BasicException( MAKE_ERROR_MSG_2( "FilePath::getPathComponents: bad parsing" ) );
	}

	return pathComponents;
}

/**
*this will convert the filename to a standard format:
[<drive_letter>:]/[dir1/][dir2/][dir_n/]
*/
String FilePath::transformToNative( const String& filename )
{
	String result = filename;
	std::replace_if( result.begin(), result.end(),
					std::bind2nd(std::equal_to<VCFChar>(),'\\') , '/' );
	return result;
}

String FilePath::transformToOSSpecific( const String& filename )
{
	VCFChar convertChar = '/';
#ifdef WIN32
	convertChar = '\\';
#endif

	String result = filename;

	std::replace_if( result.begin(), result.end(),
					std::bind2nd(std::equal_to<VCFChar>(),'/') , convertChar );

	return result;
}

String FilePath::makeDirectoryName(  const String& fullname, const bool& remove )
{
	String fn = FilePath::transformToNative( fullname );

	int size = fn.size();
	if ( 0 < size ) {
		String sep = String( 1, (VCFChar)DirectorySeparator );
		VCFChar c = fn[size-1];
		bool hasSep = ( c == '/' ) || ( c == '\\' );
		/* check against both separators under windows */
		if ( hasSep ) {
			if ( remove ) {
				fn.erase( size-1, 1 );
			}
		} else {
			if ( !remove ) {
				fn += sep;
			}
		}
	}

	return fn;
}

bool FilePath::wildCharsMatchName( const String& filename, const String& wildChars )
{
	String fname, fext;
	FilePath::splitExtension( filename, fname, fext );

	String wname, wext;
	FilePath::splitExtension( wildChars, wname, wext );

	bool match = ( ( wname == L"*" || wname == fname ) &&
	               ( wext == L"*" || wext == fext || ( 0 == fext.size() && wext == L"." ) ) );

	return match;
}


/**
$Id$
*/
