
/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/
//FilePath.cpp

#include "xmake.h"
#include "FilePath.h"
#include <algorithm>
#include <vector>
#include <map>

#ifdef WIN32
	#include <windows.h>    
#endif 

#ifdef GCC
  #include <dirent.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <sys/stat.h>
#endif

using namespace xmake;


FilePath::FilePath()
{

}



FilePath::FilePath( const String& filename ):filename_(filename)
{	
	convertToNative(filename_);
}



FilePath::FilePath( const FilePath& filePath ):filename_(filePath.filename_)
{
	convertToNative(filename_);
}



FilePath::~FilePath()
{

}

String FilePath::getDriveSeparator()
{
#ifdef WIN32
	return ":";
#else
	return "";
#endif
}

String FilePath::getExtension() const
{
	String result;

	result = filename_;		
	
	unsigned int lastSlashPos = result.find_last_of( FilePath::getDirectorySeparator() );
	
	if ( lastSlashPos != String::npos ) {			
		result = result.substr( lastSlashPos+1, result.size() - (lastSlashPos) );
	}

	int pos = result.find_last_of( FilePath::getExtensionSeparator() );
	
	if ( pos != String::npos ) {
		result.erase( 0, pos );
	}
	else {
		result = "";
	}

	return result;
}



String FilePath::getName( const bool& includeExtension ) const
{
	String result;
	
	result = filename_;		
	
	int lastSlashPos = result.find_last_of( FilePath::getDirectorySeparator() );
	
	if ( lastSlashPos != String::npos ) {			
		result = result.substr( lastSlashPos+1, result.size() - (lastSlashPos) );
	}
	
	if ( !includeExtension ) {
		int pos = result.find_last_of( FilePath::getExtensionSeparator() );
		
		if ( pos != String::npos ) {
			result.erase( pos, result.size() - pos );
		}
	}
	
	return result;
}


String FilePath::getDriveName() const
{
	String result;
	
	result = filename_;
	
	int drivePos = result.find_last_of( FilePath::getDriveSeparator() );
	if ( String::npos == drivePos ) {
		result = "";
	}
	else {
		result = result.substr( 0, drivePos );
	}
	return result;
}


String FilePath::getPathName( const bool& includeDriveName ) const
{
	String result;
	
	result = filename_;
	
	unsigned int drivePos = result.find_last_of( FilePath::getDriveSeparator() );
	if ( String::npos != drivePos ) {
		result.erase( 0, drivePos+1 );
	}
	
	int lastSlashPos = result.find_last_of( FilePath::getDirectorySeparator() );
	
	if ( lastSlashPos != String::npos ) {
		result = result.substr( 0, lastSlashPos+1 );
	}
	else {
		result = "";
	}

	if ( includeDriveName ) {
		String tmp = getDriveName();
		if ( false ==  tmp.empty() ) {
			tmp += FilePath::getDriveSeparator();
		}
		result = tmp + result;
	}
	
	return result;
}



bool FilePath::doesFileExist() const
{	
	bool result = true;
#ifdef WIN32

	HANDLE hfile = ::CreateFile( filename_.c_str(), 0, 
		0/*FILE_SHARE_READ | FILE_SHARE_WRITE*/, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM, NULL );
	
	if ( INVALID_HANDLE_VALUE == hfile ) {
		int err = ::GetLastError();
		if ( (err == ERROR_FILE_NOT_FOUND) || (err == ERROR_PATH_NOT_FOUND) ){
			result = false;
		}
	}
	else {
		CloseHandle( hfile );
	}
#endif
	return result;
}

bool FilePath::isRelativePath() const
{
	bool result = false;
	String drive = getDriveName();

	if ( (filename_[0] != FilePath::DirectorySeparator) && (drive.empty())  ) {
		result = true;
	}
	else {
		int pos = filename_.find( "../" );
		if ( pos == 0 ) {
			result = true;
		}
		else {
			result = (filename_.find( "./" ) == 0);
		}
	}
	return result;
}

bool FilePath::isDirectory() const
{
	bool result = filename_[filename_.size()-1] == FilePath::DirectorySeparator;
	return result;
}

String FilePath::transformToRelativePathName( const String& workingPath ) const
{
	String result;
	String tmp = filename_;
	String workDir = workingPath;
	if ( workDir.empty() ) {
#ifdef WIN32
		char currentDir[1024];
		GetCurrentDirectory( 1023, currentDir );
		workDir = currentDir;
#endif
#ifdef GCC
		char currentDir[1024];
		getcwd(currentDir, 1023);
		workDir = currentDir;
#endif		
	}
	else {
		//make sure it's a dir name
		FilePath dirPath(workingPath);
		workDir = dirPath.getDriveName() + FilePath::getDriveSeparator() + dirPath.getPathName();
	}
	
	if ( workDir.empty() ) {
		//ok we're screwed - throw an exception
		return "";
	}
	
	if ( workDir[workDir.size()-1] != FilePath::DirectorySeparator ) {
		workDir += FilePath::getDirectorySeparator();
	}
	
	FilePath workingDirPath = workDir;		
	
	std::vector<String> workPathComponents = separatePathComponents(workingDirPath);
	
	std::vector<String> currentPathComponents = separatePathComponents(filename_);
	
	String workingDrive = workingDirPath.getDriveName();
	String currentDrive	= getDriveName();
	
	if ( currentDrive == workingDrive ) {
		String tmp;
		std::vector<String>::iterator workIt = workPathComponents.begin();
		unsigned int workingIndex = 0;
		unsigned int currentIndex = 0;
		while ( workIt != workPathComponents.end() ) {
			if ( (*workIt != currentPathComponents[currentIndex]) || (workingIndex != currentIndex) ) {
				tmp += "../";					
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
				tmp += "./";
			}
			//only go on if we are NOT on the last element
			if ( currentIndex <= currentPathComponents.size()-1 ) {
				for ( int j=currentIndex; j<(int)currentPathComponents.size(); j++ ) {
					if ( j < (int)workPathComponents.size() ) {
						if ( workPathComponents[j] != currentPathComponents[j] ) {
							tmp += currentPathComponents[j];
						}
					}
					else {
						tmp += currentPathComponents[j];
					}
				}
			}
		}
		
		result = tmp + getName(true);
	}
	
	
	return result;
}

String FilePath::expandRelativePathName( const String& workingPath ) const
{
	String result;
	String tmp = filename_;
	String workDir = workingPath;
	if ( workDir.empty() ) {
#ifdef WIN32
		char currentDir[1024];
		GetCurrentDirectory( 1023, currentDir );
		workDir = currentDir;
#endif
#ifdef GCC
		char currentDir[1024];
		getcwd(currentDir, 1023);
		workDir = currentDir;
#endif
	}
	else {
		//make sure it's a dir name
		FilePath dirPath(workingPath);

		workDir = dirPath.getDriveName() + FilePath::getDriveSeparator() + dirPath.getPathName();
	}
	
	if ( workDir.empty() ) {
		//ok we're screwed - throw an exception
		return "";
	}
	
	if ( workDir[workDir.size()-1] != FilePath::DirectorySeparator ) {
		workDir += FilePath::getDirectorySeparator();
	}
	
	convertToNative(workDir);
	
	//strip drive if present
	String drive;
	unsigned int drivePos = workDir.find_last_of( FilePath::getDriveSeparator() );
	if ( String::npos == drivePos ) {
		drive = "";
	}
	else {
		drive = workDir.substr( 0, drivePos );
		//workDir.erase( 0, drivePos );
	}
	
	std::vector<String> workPathComponents = separatePathComponents(workDir);
	int pos = tmp.find( "../" );
	if ( pos != String::npos ) {			
		
		while ( pos != String::npos ) {
			if ( 0 != pos ) {
				//OOOOHHH error condition this is 
				//is a malformed strign ! - in other 
				//words we have a relative path like foo/../bar - incorrect!!!
				//throw exception
				
				return "";
			}
			
			//remove the last dir component
			//equivalent of "going back a dir", or "cd .."
			workPathComponents.pop_back(); 
			tmp.erase( 0, pos+3 );
			pos = tmp.find( "../", 0 );
			
		}
		std::vector<String>::iterator it = workPathComponents.begin();
		result = "";
		while ( it != workPathComponents.end() ) {
			result += *it;
			it ++;
		}
		result += tmp;
		result = drive + FilePath::getDriveSeparator() + result;
	}
	else {		
		//ok look for ./ series
		pos = tmp.find( "./", 0 );
		//ok simply local working dir
		//remove the ./ notation and prepend the 
		//working dir to file name
		if ( pos != String::npos ) {
			tmp.erase( pos, 2 );
			result = workDir + tmp;
		}
		else if ( tmp[0] != FilePath::DirectorySeparator ) {
			result = workDir + tmp;
		}
	}
	
	return result;
}

std::vector<String> FilePath::separatePathComponents( const String& path ) const
{
	std::vector<String> pathComponents;
	String tmp = path;
	
	//get rid of drive
	String driveSep = FilePath::getDriveSeparator();
	
	int pos = String::npos;
	if ( !driveSep.empty() ) {
		pos = tmp.find( driveSep );
	}
	
	
	if ( pos != String::npos ) {
		tmp.erase( 0, pos + 1 );
	}

	pos = tmp.find( FilePath::getDirectorySeparator(), 0 );

	int lastPos = 0;
	while ( pos != String::npos ) {		
		String s = tmp.substr( lastPos, (pos - lastPos)+1 );
		
		pathComponents.push_back( s );
		lastPos = pos+1;
		pos = tmp.find( FilePath::getDirectorySeparator(), pos + 1 );		
	}
	
	return pathComponents;
}

/**
*this will convert the filename to a standard format:
[<drive_letter>:]/[dir1/][dir2/][dir_n/]
*/
void FilePath::convertToNative( String& filename ) const
{
	std::replace_if( filename.begin(), filename.end(), 
					std::bind2nd(std::equal_to<char>(),'\\') , '/' );


}

String FilePath::transformToOSSpecific() const
{
	char convertChar = '/';
#ifdef WIN32
	convertChar = '\\';
#endif
	String result = filename_;

	std::replace_if( result.begin(), result.end(), 
					std::bind2nd(std::equal_to<char>(),'/') , convertChar );

	return result;
}


