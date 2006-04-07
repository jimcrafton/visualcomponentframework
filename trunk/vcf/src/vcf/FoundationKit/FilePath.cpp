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
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.1  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.5  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.2  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.1  2004/12/11 17:49:58  ddiego
*added 2 new projects that are command line tools. One is for
*creating the basic shell for app bundles, the other is for filling in, or
*updating an info.plist (or info.xml) file.
*
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/10 01:55:43  marcelloptr
*[bugfix: 1063548] FilePath crashes on relative non Native paths
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
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
*Revision 1.7  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.4  2003/09/22 01:48:05  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.6.4.3  2003/09/19 21:24:20  ddiego
*small changes
*
*Revision 1.6.4.2  2003/09/19 04:11:39  ddiego
*added fix to docmanager
*added fix to handle path components with case insensitivity on Win32
*for file path transformation to relative paths
*
*Revision 1.6.4.1  2003/08/23 12:44:35  marcelloptr
*improved comments in FilePath
*
*Revision 1.6  2003/05/17 20:37:41  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:12:47  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.2.2  2002/12/27 23:04:57  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.4.2.1  2002/11/28 05:12:05  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.4  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.3.4.2  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.3.4.1  2002/09/23 21:24:39  ddiego
*more build fixes - there is a serious error with file locks that needs to fixed
*
*Revision 1.3  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.4.10  2002/08/01 19:16:26  ddiego
*added support for create new files from the File | New... menu
*this displays a list of file templates which are read from the Object
*Repository. The FilePath had a bug with the FilePath::isRelative() function
*fixed a display bug with the CheckBoxControl and the fixed size of hte
*of the check box being too small
*
*Revision 1.2.4.9  2002/08/01 05:08:31  ddiego
*made changes to open a file from without being in a project
*started changes for add files from the "File | New..." dialog
*
*Revision 1.2.4.8  2002/07/21 05:02:50  ddiego
*added more stuff for configuration management, fixed the FilePath bug
*add a removeAllHandlers() to VCF::Delegate class
*
*Revision 1.2.4.7  2002/07/19 21:27:40  ddiego
*added tweaks to FilePath - there is still a problem with transformaing certain
*directory paths...fix this !
*
*Revision 1.2.4.6  2002/07/16 21:06:22  ddiego
*mods to the TextEditor to add advanced features for editing
*code
*
*Revision 1.2.4.5  2002/07/16 04:23:19  ddiego
*modified FilePath to get the drivename and path name in one fucntion
*will correctly ignore the drive separator in non WIN32 systems
*mods ot VCFBuilder to load external projects within a workspace
*using relative paths ! - this needs to be migrated over to xmake
*as well
*
*Revision 1.2.4.4  2002/07/15 21:03:11  ddiego
*mods to VCFBuilder, fixed some bugs in FilePath
*
*Revision 1.2.4.3  2002/07/15 04:06:14  ddiego
*fixing saving the various project file ot take advantage to relative path
*and the FilePath object
*
*Revision 1.2.4.2  2002/07/14 05:40:02  ddiego
**** empty log message ***
*
*Revision 1.2  2002/06/24 04:24:49  ddiego
*mods to VCFBuilder
*
*Revision 1.1  2002/06/18 21:18:32  ddiego
*added FilePath
*/


