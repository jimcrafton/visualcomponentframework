// XMLMake.cpp : Defines the entry point for the console application.
//

/**
platforms
WIN32 - windows platforms
MACOSX - Apple's MacOSX platform
LINUX - linux based systems

compilers
GCC - the GNU Compiler Collection compiler, namely g++
_MSC_VER - the Microsoft Visaul C++ compiler
*/


#ifdef GCC
#ifndef MACOSX
   //apparently OSX doesn't need this...
	#include <dirent.h> 
#endif
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <fcntl.h>
	#include <stdarg.h>
	#include <errno.h>

#endif

#include "xmake.h"
#include "XMLParser.h"
#include "CmdLine.h"
#include "FilePath.h"

// MP - moved to xmake.h
//#ifdef WIN32
//	#include <windows.h>
//    #include <io.h>
//    #include <stdio.h>
//	#include <process.h>
//#endif 

#include "DependencyNodes.h"
#include "xmakeUtils.h"


#include <exception>
#include <stdexcept>


#define MAX_TRACE_STRING 4096

using namespace xmake;


#define XMAKE_VERSION	"2.0.0"



XMLMake::XMLMake():
	makefile_("makefile.xml"),
	parsedNodes_(NULL),
	printDebug_(false),
	verbose_(false),
	action_(actNone),
	//parser_(NULL),
	returnCode_(0)	
{
	automaticVariablesMap_["target"] = "target";
	automaticVariablesMap_["dependency"] = "dependency";
	automaticVariablesMap_["output"] = "output";
	automaticVariablesMap_["name"] = "name";
	automaticVariablesMap_["dependsOn.children"] = "dependsOn.children";	
}

XMLMake::~XMLMake()
{
	DependencyNode::Iterator it = dependencyList_.begin();
	while ( it != dependencyList_.end() ) {
		delete *it;
		it ++;
	}
}



void XMLMake::debugWithArgs( String text,... )
{
	if ( printDebug_ ) {

		va_list argList;
	
		va_start( argList, text );     // Initialize variable arguments.
	
		char* buf = new char[MAX_TRACE_STRING];
		memset( buf, 0, MAX_TRACE_STRING );
#ifdef GCC	
		vsnprintf( buf, MAX_TRACE_STRING, text.c_str(), argList );
#elif WIN32
		_vsnprintf( buf, MAX_TRACE_STRING, text.c_str(), argList );
#endif	

		va_end( argList );              // Reset variable arguments.      
	
		debug( String(buf) );

		delete [] buf;
		
		
	}
}

void XMLMake::debug( const String& text )
{
	if ( printDebug_ ) {
		char* tmp = new char[text.size() + 256];
#ifdef GCC
		int pid = getpid();
#elif WIN32	
		int pid = _getpid();
#endif		
		sprintf( tmp, "<PID:0x%04X> %s", pid, text.c_str() );
		printf( tmp );
		delete [] tmp;
	}
}

const char* XMLMake::nextNonWhiteSpace( const char *s )
{
	const char* result = NULL;
	
	// Check the string.
	while( *s ) {
		
		// If this is a whitespace character than continue the loop.
		if ( (*s == ' ') || (*s == 9) || (*s == '\n') || (*s == '\r') ) {
			s++;
			continue;
		} // if
		
		// Found a none whitespace character.
		result = s;
		break;
		
	} // while
	
	return result;
}


const char* XMLMake::nextWhiteSpace( const char *s )
{
	const char* result =  NULL;
	// Check the string.
	while( *s ) {
		
		// Found a whitespace character.
		if ( (*s == ' ') || (*s == 9) || (*s == '\n') || (*s == '\r') ) {
			result = s;
			break;
		}
		
		// Else continue the loop.
		s++;
	} // while
	
	return result;
}


void XMLMake::searchIncludeFile( const String& name, long& dependencyCount, StringList& dependsList )
{
	
#ifdef WIN32
	unsigned int i;
	int j;
	char     tmp[MAXPATH];
	struct   _finddata_t  find;
	
	// Try to find in all include directory.
	for(i=0; i<includeDirectories_.size(); i++) {
		
		// Make the full name.
		strcpy(tmp, includeDirectories_[i].c_str());
		strcat(tmp, name.c_str());
		
		// Try to locate the include file.
		long hFile = _findfirst(tmp, &find);
		if ( hFile != -1 ) {

			
			// Check if it appears in the dependecy list.
			for(j=0; j<dependencyCount; j++) {
				if ( !strcmp(dependsList[j].c_str(), tmp) ) {
					return ;
				}
			}
			
			
			if ( dependencyCount == MAX_INCLUDE_DEPTH ) {				
				throw std::logic_error( "Too many dependent file." );	
			}
			
			// It is a new dependent file.
			
			dependsList[dependencyCount++] = tmp;
			_findclose( hFile );
			
			return;
		} // if
		
	} // for
#endif

#ifdef GCC

	int      i, j;
	String     tmp;
	
	// Try to find in all include directory.
	for(i=0; i<includeDirectories_.size(); i++) {
		
		// Make the full name.
		tmp = includeDirectories_[i];
		tmp += name;		

		bool fileExists;
		FILE* fileExistsHandle = fopen( tmp.c_str(), "r" );
		
		if (fileExistsHandle != NULL) {
			fileExists = true;
			fclose(fileExistsHandle);
		}
		else {
			fileExists = false;
		}
		
		if (fileExists)	{	
			StringList::iterator it = dependsList.begin();
			j = 0;
			while ( (j<dependencyCount) && (it != dependsList.end()) ) {
				if ( (*it) == tmp ) {
					return;
				}

				it ++;
				j++;
			}
			
			if ( dependencyCount == MAX_INCLUDE_DEPTH ) {			
				throw std::logic_error( "Too many dependent file." );					
			}

			dependsList[dependencyCount++] = tmp;
			return;
			
		} // if
		
	} // for
#endif
	
}

void XMLMake::makeDependFiles( String name, StringList& dependsList, long& dependencyCount )
{
	IncludeMap::iterator found = includesMap_.find( name );
	if ( found != includesMap_.end() ) {
		StringList& includes = found->second;
		
		dependencyCount += includes.size();
		dependsList.insert( dependsList.end(), includes.begin(), includes.end() );
		//printf( "found %d dependencies for %s! used shortcut!\n", dependencyCount, name.c_str() );
		return;
	}



				
	FILE  *sf;
//	char  line[LINE_SIZE];
	const char  *s; 
		//const char* e;
	int   i, first, last;	
	
	//printf( "makeDependFiles for %s\n", name.c_str() );

	// Register the first dependent file.
	first = dependencyCount;
	
	// Open source file.
	if ( (sf = fopen(name.c_str(), "rt")) == NULL ) {
		debugWithArgs("Unable to open %s file.\n", name.c_str());
		return;
		
	} 
	fseek( sf, 0, SEEK_END );

	int fileSize = ftell( sf );

	fseek( sf, 0, SEEK_SET );
	char* fileBuf = new char[fileSize];
	fread( fileBuf, 1, fileSize, sf );
	String text (fileBuf);
	delete [] fileBuf;
	// Close the source file.
	fclose(sf);
	
	int pos = text.find( "#include" );

	StringList includesList;

	// Scan source file for include statments.
	while( pos != String::npos ) {	

		s = text.c_str() + pos;
		
		s += 8; //skip past #include
			
		// Search begin of include file name.
		if ( (s = nextNonWhiteSpace(s)) == NULL )
				continue;
		s++;
			
		// Search end of include file name.
		int pos2 = text.find_first_of( ">\"", s - text.c_str() );

		if ( pos2 != String::npos ) {
			String includeFile;
		
			

			includeFile = text.substr( s - text.c_str(), pos2 - (s - text.c_str()) );
			if ( !includeFile.empty() ) {
				IncludeMap::iterator found = includesMap_.find( includeFile );
				if ( found != includesMap_.end() ) {
					StringList& includes = found->second;
					
					dependencyCount += includes.size();
					dependsList.insert( dependsList.end(), includes.begin(), includes.end() );
				}
				else {
					// Search full path of include file.
					int prevCount = dependencyCount;
					searchIncludeFile( includeFile, dependencyCount, dependsList );
					if ( prevCount < dependencyCount ) {
						includesList.push_back( includeFile );
					}
				}
			}
		}
			//*e = '\0';
				
		
		
		
		pos = text.find( "#include", pos + 1 );
		
	} // while
	
	includesMap_[name] = includesList;

	// Register the last dependent file.
	last = dependencyCount;
	
	//printf( "found %d dependencies for %s!\n", last - first, name.c_str() );
	
	// Check include files in this source file.
	if ( first < last ) {
		for(i=first; i<last; i++) {
			

			makeDependFiles( dependsList[i], dependsList, dependencyCount );
		}
	}
}



String XMLMake::getEnvironmentVariableValue( const String& variableName )
{
	String result;

#ifdef WIN32
	VCFChar envValue[1024];
	memset( envValue, 0, 1024 );
	GetEnvironmentVariable( variableName.c_str(), envValue, 1023 );

	result = envValue;
#endif

#ifdef GCC
	if ( !variableName.empty() ) {
		const char* envVar = getenv(variableName.c_str());
		if ( NULL !=  envVar ) {
    	result = envVar;	
		}
	}
#endif 


	return result;
}


int XMLMake::exec( const String& commandLine, const String& currentDirectory )
{
	int result = 0;
#ifdef WIN32
	/*
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hStdError = GetStdHandle(STD_ERROR_HANDLE);

	
	STARTUPINFO si = {0};
	si.cb = sizeof( STARTUPINFO );
	
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdInput = hStdIn;		// stdin of parent
	si.hStdOutput = hStdOut;	// write side of child-to-parent
	si.hStdError = hStdError;		// stderr of parent
	
	PROCESS_INFORMATION pi = {0};				
	
	
	
	char tmp[1024];
	commandLine.copy( tmp, commandLine.size() ); 
	tmp[commandLine.size()] = 0;
	
	if ( CreateProcess( NULL, tmp, 
						NULL, 
						NULL, 
						TRUE, 
						0, 
						NULL, 
						currentDirectory.c_str(), 
						&si, 
						&pi ) ) {
		
		
		WaitForSingleObject ( pi.hProcess, INFINITE );
		
		DWORD exitCode;
		GetExitCodeProcess(pi.hProcess,&exitCode);
		
		result = (int) exitCode;

		CloseHandle( pi.hProcess );
	}
	else {
		
		debugWithArgs( "GetLastError(): %d for cmd line %s\n", GetLastError(), commandLine.c_str() );
	}
	*/

	result = ::system(commandLine.c_str()); 
#endif

// ------------------------------ GCC --------------------------
#ifdef GCC 
       // save a copy of the current dir 
	
	if ( verbose_ ) {
		printf( "executing: \"%s\"\n", commandLine.c_str() );
	}
	
           //char currentDir[1000]; 
           //getcwd(currentDir,1000); 
    
           // changes to the dir specified as parameter 
           //chdir(commandLine.c_str()); 
    
           // runs the command line 
           result = ::system(commandLine.c_str()); 
    
           // switch back to the original dir 
           //chdir(currentDir); 
 #endif

	debugWithArgs( "\"%s\" returned: %d\n", commandLine.c_str(), result );
	return result;
}

#ifdef GCC
String getErrorString( const int& errorCode )
{
	String result;
	//error string based on linux man page docs
	//assumes
	switch ( errorCode ) {
		case EFAULT: {
			result = "EFAULT: Path points outside your accessible address space.";
		}
			break;

		case EACCES: {
			result = "EACCES: Write access to the directory containing the pathname is not allowed\n"\
			"for hte process's effective uid, or one of the directories in the pathname\n"\
			"did not allow search (execute) permission.";
		}
			break;

		case EPERM: {
			result = "EPERM: The directory that is represented by the path name has the sticky bit set\n"\
			"and the process's effective uid is neither the uid of the file to be deleted\n"\
			"nor that of the directory containing it.";

		}
			break;


		case ENAMETOOLONG: {
			result = "ENAMETOOLONG: The pathname was too long.";
		}
			break;

		case ENOENT: {
			result = "ENOENT: A directory component in the pathname does not exist or is a dangling symbolic link.";
		}
			break;

		case ENOTDIR: {
			result = "ENOTDIR: A component used as a directpy in a path is not, in fact, a directory.";
		}
			break;

		case ENOMEM: {
			result = "ENOMEM: Insufficient kernel memory.";
		}
			break;

		case EROFS: {
			result = "EROFS: Path refers to a file that is read-only.";
		}
			break;

		case EEXIST: {
			result = "EEXIST: Path refers to a file that already exists.";
		}
			break;

		case EISDIR: {
			result = "EISDIR: Path refers to a file that is a directory and write access was requested.";
		}
			break;

		case ENXIO: {
			result = "ENXIO: O_NONBLOCK or O_WRONLY is set, the named file is a FIFO and no\n"\
			"process has the file open for reading. Or, the file is a device\n"\
			"special file and no corresponding device exists.";
		}
			break;

		case ENODEV: {
			result = "ENODEV: Path refers to a device special file and no corresponding device exists.";
		}
			break;

		case ELOOP: {
			result = "ELOOP: Too many symbolic links were were encountered in resolving the pathname\n"\
			"or O_NOFOLLOW was specified but the path was a symbolic link.";
		}
			break;

		case ENFILE: {
			result = "ENFILE: The limit on the number of open file handles was reached for the OS.";
		}
			break;

		case EMFILE: {
			result = "EMFILE: The limit on the number of open file handles for the process was reached.";
		}
			break;
	}
	return result;
}
#endif

void XMLMake::error( const String& errMessage )
{
	String msg = "xmake failed: " + errMessage + "\n";
	debugWithArgs( msg.c_str() );
	if ( printDebug_ ) {
#ifdef WIN32
		printf( "GetLastError() returned %d\n", GetLastError() );
#endif
#ifdef GCC
		printf( "errno is :%d, error string: %s\n", errno, getErrorString(errno).c_str() );
#endif
	}
}

void XMLMake::setCurrentDirectory( const String& dir )
{
#ifdef WIN32
	
	if ( !SetCurrentDirectory( dir.c_str() ) ) {
		error( "Win32 SetCurrentDirectory( \"" + dir + "\") failed" );
	}
	
#endif
	
#ifdef GCC
	int result = chdir( dir.c_str() );
	if ( -1 == result ) {
		error( "chdir( \"" + dir + "\" ) failed!!\n" );	
	}
#endif	
}

String XMLMake::getCurrentDirectory()
{
	String result;
#ifdef WIN32
	char currentDir[1024];
	GetCurrentDirectory( 1023, currentDir );
	result = currentDir;
#endif

#ifdef GCC
	char currentDir[1024];
	getcwd(currentDir, 1023);
	result = currentDir;
#endif
	FilePath dir = result;
	if ( !dir.isDirectory() ) {
		dir = dir.getFileName() + FilePath::getDirectorySeparator();	
	}
	result = dir.transformToOSSpecific();

	return result;
}



class FindDependsNode{
public:

	FindDependsNode( const String& name ) :name_(name)  {

	}

	bool operator ()( DependencyNode* x ) const {
		return name_ == x->name();
	}

	const String& name_;
};

class XMLNodePred : public std::less<XMLNode*>{
public:
	typedef std::map<XMLNode*,DependencyNode*> Map;
	
	XMLNodePred(Map* map): map_(map) {
		
	}
	
	XMLNodePred( const XMLNodePred& rhs ) {
		*this = rhs;
	}
	
	XMLNodePred& operator=( const XMLNodePred& rhs ) {
		map_ = rhs.map_;
		return *this;
	}
	
	bool operator() ( XMLNode* x, XMLNode* y ) const{
		
		Map::iterator found_x =  map_->find( x );
		Map::iterator found_y =  map_->find( y );
		if ( (found_x != map_->end()) && (found_y != map_->end()) ) {
			return found_x->second->score() < found_y->second->score();
		}
		return x < y;
	}
	
	Map* map_;
};



bool XMLMake::deleteFile( const String& filename )
{
	bool result = false;
	
#ifdef WIN32
	if ( DeleteFile( filename.c_str() ) ){
		result = true;
	}
	else {
		debugWithArgs( "GetLastError() %d\n", GetLastError() );
	}
#endif

#ifdef GCC
	if ( 0 == remove(filename.c_str()) ) {
		result = true;
	}
	else {
		result = false;
	}

#endif

	return result;
}


bool XMLMake::fileNewerThan( const String& f1, const String& f2 )
{
	bool result = false;
	#ifdef WIN32
	HANDLE f1Handle = CreateFile( f1.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	HANDLE f2Handle = CreateFile( f2.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if ( (INVALID_HANDLE_VALUE != f1Handle) && (INVALID_HANDLE_VALUE != f2Handle) ) {
		
		FILETIME f1LastMod;
		GetFileTime( f1Handle, NULL, NULL, &f1LastMod );

		FILETIME f2LastMod;
		GetFileTime( f2Handle, NULL, NULL, &f2LastMod );
		
		
		int res = CompareFileTime( &f1LastMod, &f2LastMod );

		if ( res > 0 ) { //lastMod is newer than lastMod_src
			result = true;
		}		
	}	
	else {
		if ( (f2Handle == INVALID_HANDLE_VALUE) && (f1Handle != INVALID_HANDLE_VALUE) ){
			//there is no srcFile but the file does exist
			result = true;
		}
	}

	CloseHandle( f2Handle );
	CloseHandle( f1Handle );
#endif
// ------------------------- GCC ----------------------------
#ifdef GCC

	struct stat bufF1, bufF2;

	int noSuccessF1 = stat(f1.c_str(), &bufF1);
	int noSuccessF2 = stat(f2.c_str(), &bufF2);

    if (noSuccessF1 == 0 && noSuccessF2 == 0)
	{
		time_t lastMod = bufF1.st_mtime;
		time_t lastModSrc = bufF2.st_mtime;

		if (lastMod > lastModSrc)
		{
			result = true;
		}
	}
	else
	{
		if (noSuccessF1 != 0 && noSuccessF2 == 0)
		{
			result = true;
		}
	}
#endif
// ----------------------------------------------------------

	return result;
}


bool XMLMake::verifyFileName( const String& filename, const bool& autoBuildDir )
{
	bool result = false;
	
#ifdef WIN32
	FilePath fp = filename;
	String tmpFilename;
	if ( fp.isRelativePath() ) {
		tmpFilename = fp.expandRelativePathName( this->getCurrentDirectory() );
		fp = tmpFilename;
	}
	tmpFilename = fp.transformToOSSpecific();

	HANDLE fileHandle = CreateFile( tmpFilename.c_str(), 
									0,
									FILE_SHARE_READ | FILE_SHARE_WRITE, //for now
									NULL, //for now
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL );

	if ( (autoBuildDir) && (fileHandle == INVALID_HANDLE_VALUE)  ) {
		std::vector<String> dirPaths;
		String tmp = tmpFilename;
		int pos = tmp.find( "\\" );
		while ( pos != String::npos ) {
			dirPaths.push_back( tmp.substr( 0, pos ) );
			tmp.erase( 0, pos+1 );
			pos = tmp.find( "\\" );
		}

		if ( dirPaths.size() == 1 ) {
			String dir = dirPaths[0];
			if ( dir[dir.size()-1] != ':' ) {
				throw std::logic_error("invalid directory path");
			}
		}
		if ( dirPaths.size() == 0 ) {
			throw std::logic_error("invalid directory path");
		}

		std::vector<String>::iterator it = dirPaths.begin();
		String dirPath = *it;
		it++;			
		while ( it != dirPaths.end() ) {
			dirPath += "\\" + *it;
			if ( FALSE == ::CreateDirectory( dirPath.c_str(), NULL ) ) {
				int err = GetLastError();
				if ( ERROR_ALREADY_EXISTS != err ) {
					CloseHandle( fileHandle );
					throw std::logic_error( "Unable to create directory \"" + tmpFilename + "\"" );
				}
			}
			it++;
		}
	}
	else if ( fileHandle != INVALID_HANDLE_VALUE ) {
		result = true;
	}


	CloseHandle( fileHandle );
#endif

// ----------------------- GCC ---------------------------------------------------
#ifdef GCC
	// * char tmpPath[MAX_PATH+1];

	// verify if the file can be opened
	String fullName;
	fullName = filename; // this should be changed in the future to allow a different source tree

	FILE* fileHandle = fopen(fullName.c_str(),"r");

	String tmpFilename = fullName;

	if ( (autoBuildDir) && (fileHandle == NULL)  ) {
		// try to make the directories
		std::vector<String> dirPaths;
		String tmp = tmpFilename;
		unsigned int pos = tmp.find( "/" );
		while ( pos != String::npos ) {
			dirPaths.push_back( tmp.substr( 0, pos ) );
			tmp.erase( 0, pos+1 );
			pos = tmp.find( "/" );
		}

		// * if ( dirPaths.size() == 0 ) {
		// *	throw std::logic_error("invalid directory path");
		// * }	
		
		// create the dirs if necessary
		for (unsigned int i=0;i<dirPaths.size();i++)
		{
			String dirName = "";
			for (unsigned int j=0;j<=i;j++)
			{
				dirName += dirPaths[j];
				if (j != i) dirName += "/";
			}

			if (dirPaths[i] != "..")
			{				
				mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
			}
		}

	}
	else if ( fileHandle != NULL ) {
		result = true;
	}

	if (fileHandle != NULL)
	{
		fclose(fileHandle);
	}

#endif
// -----------------------------------------------------------------------

	return result;
}


bool XMLMake::moveFile( const String& src, const String& dest )
{	
	debug( "Moving file from \"" + src + "\" to \"" + dest + "\"\n" );
	FILE* srcF = fopen( src.c_str(), "r" );
	if ( NULL == srcF ) {
		error("can't open \"" + src + "\"\n" );
		return false;
	}
	fseek( srcF, 0, SEEK_END );
	unsigned long srcSize = ftell(srcF);
	fseek( srcF, 0, SEEK_SET );
	
	char* srcBuf = new char[srcSize];
	fread( srcBuf, sizeof(char), srcSize, srcF );
	fclose( srcF );
	
	
	
	FILE* destF = fopen( dest.c_str(), "wb" );
	
	
	
	//auto create the directory path if neccessary
#ifdef GCC	
	if ( (NULL == destF) /*&& (errno == ENOENT)*/ ) {
		
		FilePath dir = dest;
		if ( dir.isRelativePath() ) {
			dir = dir.expandRelativePathName( getCurrentDirectory() );
		}
		
		std::vector<String> comps = dir.getPathComponents();
		std::vector<String>::iterator it = comps.begin();
		String path = "/";
		int createDirMode = S_IRWXU | S_IRWXG | S_IRWXO;
		while ( it != comps.end() ) {
			path += *it;
			printf( "\tmkdir( \"%s\" )\n", path.c_str() );
			
			int res = mkdir( path.c_str(), createDirMode );
			
			if ( res == -1 ) {
				debugWithArgs( "errno: %d\n", errno );
				if ( errno != EEXIST ) {
					debug( "failed to create directory!\n" );
					break;
				}
			}
			it ++;
		}
		
		destF = fopen( dest.c_str(), "wb" );
	}	
	
#endif	
	
	if ( NULL == destF ) {
		debugWithArgs( "errno: %d\n", errno );
		delete [] srcBuf;
		error("can't create \"" + dest + "\"\n" );
		return false;
	}
	
	
	unsigned long destSize = fwrite( srcBuf, sizeof(char), srcSize, destF );
	if ( destSize != srcSize ) {
		delete [] srcBuf;
		debugWithArgs( "fwrite wrote: %d, asked to : %d\n",
				destSize, srcSize );	
		
		error( "source size does not match the number of bytes written to dest\n" );
		return false;
	}
	
	fclose( destF );
	
	
	delete [] srcBuf;
	
	deleteFile( src );
	return true;
}


int XMLMake::findLastStringIn( const String& src, const String& searchFor )
{
	unsigned int pos = String::npos;
	
	pos = src.find( searchFor, 0 );

	int result = pos;
	while ( String::npos != pos ) {		
	 	pos = src.find( searchFor, pos+1 );
		if ( String::npos != pos ) {
			result = pos;	
		}
	}

	return result;
}


String XMLMake::getVersion()
{
	return String(XMAKE_VERSION);
}



bool XMLMake::implicitDependenciesChanged( const String& filename, const String& outputFilename )
{
	bool result = false;

	FilePath fp = filename;
	String ext = fp.getExtension();
	
	if ( (ext != ".cpp") && (ext != ".cc")
			&& (ext != ".cxx") && (ext != ".c") ) {
		return result;
	}

	StringList depends;
	depends.resize( MAX_INCLUDE_DEPTH, "" );
	depends[0] = filename;

	long dependCount = 1;

	makeDependFiles( filename, depends, dependCount );


	//we may have an output name - if we do use this to compare against,
	//as opposed to the actual filename 
	String compareFilename = outputFilename.empty() ? filename : outputFilename;	

	for ( int i=1;i<dependCount;i++ ) {		
		if ( fileNewerThan( depends[i], compareFilename ) ) {
			result = true;
			break;
		}		
	}

	return result;
}


bool XMLMake::targetUptodate( const String name ) 
{
	bool result = true;
	TargetMap::iterator found = targets_.find( name );
	if ( found != targets_.end() ) {
		Target& target = found->second;
		String targetFilename = (target.name != target.output) ?
									target.output : target.name;

		target.uptodate = fileExists( targetFilename );

		for ( unsigned int i=0;i<target.dependencies.size();i++ ) {
			//chekc to see if the "dependency" is uptodate
			Dependency& dependency = target.dependencies[i];
			if ( dependency.buildable ) {
				String filename;

				if ( dependency.name != dependency.output ) {
					filename = dependency.output;
				}

				dependency.uptodate = targetUptodate( dependency.name );
				if ( dependency.uptodate ) {
					
					if ( fileExists( filename ) ) {					
						dependency.uptodate = !fileNewerThan( dependency.name, filename );
						
						if ( dependency.uptodate ) {
							bool res = implicitDependenciesChanged(dependency.name,filename);
							dependency.uptodate = !res;							
						}
					}
					else {
						dependency.uptodate = false;
					}
				}
				if ( !dependency.uptodate && target.uptodate ) {
					target.uptodate = false;
				}
				else if (dependency.uptodate && target.uptodate){
					target.uptodate = !fileNewerThan( filename, targetFilename );
				}
			}
		}
		result = target.uptodate;
	}

	return result;
}

void XMLMake::checkUptodateStatus( DependencyNode::Vector& sortedDependencies )
{
	DependencyNode::Iterator it = sortedDependencies.begin();
	std::vector<DependencyNode::Iterator> removalList;

	while ( it != sortedDependencies.end() ) {
		DependencyNode* dep = *it;
		
		TargetMap::iterator found = targets_.find( dep->name() );		

		if ( targetUptodate( dep->name() ) && (found != targets_.end()) ) {
			removalList.push_back( it );
		}
/*
		if ( found != targets_.end() ) {
			Target& target = found->second;
			


			String targetFilename = (target.name != target.output) ?
									target.output : target.name;

			target.uptodate = fileExists( targetFilename );
			
			for ( int i=0;i<target.dependencies.size();i++ ) {
				//chekc to see if the "dependency" is uptodate
				Dependency& dependency = target.dependencies[i];

				if ( dependency.buildable ) {
					String filename = (dependency.name != dependency.output) ?
						dependency.output : dependency.name;
					
					
					if ( fileExists( filename ) ) {					
						dependency.uptodate = !fileNewerThan( dependency.name, filename );

						if ( dependency.uptodate ) {
							bool res = implicitDependenciesChanged(dependency.name,filename);
							dependency.uptodate = !res;							
						}
					}			
					if ( !dependency.uptodate && target.uptodate ) {
						target.uptodate = false;
					}
					else if (dependency.uptodate && target.uptodate){
						target.uptodate = !fileNewerThan( filename, targetFilename );
					}
				}
			}

			if ( target.uptodate ) {
				//target.uptodate = !fileNewerThan( filename, targetFilename );
			}
			
			
		}
		*/

		it ++;
	}

	std::vector<DependencyNode::Iterator>::reverse_iterator removeIt = removalList.rbegin();
	while ( removeIt != removalList.rend() ) {
		sortedDependencies.erase( *removeIt );
		removeIt ++;
	}
}


void XMLMake::buildDependencies( Target& target )
{
	target.dependsNode = new DependencyNode();
	target.dependsNode->name( target.name );	

	dependencyList_.push_back( target.dependsNode );
	dependsGraph_.nodes().push_back( target.dependsNode );	
	
	std::vector<Dependency>::iterator it = target.dependencies.begin();
	while ( it != target.dependencies.end() ) {
		Dependency& dependency = *it;
		
		TargetMap::iterator found = targets_.find( dependency.name );
		if ( found != targets_.end() ) {
			Target& childTarget = found->second;			
			buildDependencies( childTarget );
		}
		else {
			dependency.dependsNode = new DependencyNode();
			dependency.dependsNode->name( dependency.name );
			target.dependsNode->dependsOn( dependency.dependsNode );
			dependsGraph_.nodes().push_back( dependency.dependsNode );

			
		}

		it ++;
	}
	
	
}


void XMLMake::buildDependencies( Project& project )
{

	project.dependsNode = new DependencyNode();
	project.dependsNode->name( project.name );
	dependencyList_.push_back( project.dependsNode );
	dependsGraph_.nodes().push_back( project.dependsNode );	

	

	std::vector<Dependency>::iterator it = project.dependantProjects.begin();

	while ( it != project.dependantProjects.end() ) {
		Dependency& dependency = *it;
		
		ProjectMap::iterator found = projects_.find( dependency.name );
		if ( found != projects_.end() ) {
			Project& childProject = found->second;			
			buildDependencies( childProject );
		}
		else {
			dependency.dependsNode = new DependencyNode();
			dependency.dependsNode->name( dependency.name );
			project.dependsNode->dependsOn( dependency.dependsNode );
			dependsGraph_.nodes().push_back( dependency.dependsNode );
		}

		it ++;
	}
	
	std::vector<Target>::iterator targetIt = project.targets.begin();
	while ( targetIt != project.targets.end() ) {
		Target& target = *targetIt;
		if ( firstTarget_ == target.name ) {
			buildDependencies( target );
			break;
		}
		
		targetIt ++;
	}
}


void XMLMake::buildSortedDependencyList( DependencyNode::Vector& sortedDependencies )
{
	XMLParser parser;

	parser.parse( masterContents_ );

	Enumerator<XMLNode*>* nodes = parser.getParsedNodes();
	
	targets_.clear();
	String currentProject;
	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();

		if ( node->getName() == "target" ) {
			XMLAttr* name = node->getAttrByName( "name" );
			XMLAttr* output = node->getAttrByName( "output" );
			XMLAttr* tool = node->getAttrByName( "tool" );
			XMLAttr* config = node->getAttrByName( "config" );

			if ( NULL == name ) {
				error("invalid target syntax. Target has no \"name\" attribute");
				break;
			}

			

			Target target;
			target.dependsNode = NULL;
			target.output = target.name = name->getValue();
			if ( NULL != output ) {
				target.output = output->getValue();
			}

			if ( NULL != tool ) {
				target.tool = tool->getValue();
			}

			if ( NULL != config ) {
				target.config = config->getValue();
			}

			//printf( "found target %s\n", target.name.c_str() );

			XMLNode* dependsOn = node->getNodeByName( "dependsOn" );
			if ( NULL != dependsOn ) {
				Enumerator<XMLNode*>* depends = dependsOn->getChildNodes();
				while ( depends->hasMoreElements() ) {
					XMLNode* dep = depends->nextElement();
					XMLAttr* name = dep->getAttrByName( "name" );
					XMLAttr* output = dep->getAttrByName( "output" );
					XMLAttr* tool = dep->getAttrByName( "tool" );
					XMLAttr* config = dep->getAttrByName( "config" );
					XMLAttr* buildIt = dep->getAttrByName( "build" );
					
					if ( NULL == name ) {
						error("invalid dependency syntax. Dependency has no \"name\" attribute");
						break;
					}
					
					Dependency dependency;
					dependency.dependsNode = NULL;
					dependency.name = name->getValue();
					dependency.output = dependency.name;
					if ( NULL != output ) {
						dependency.output = output->getValue();
					}
					
					if ( NULL != tool ) {
						dependency.tool = tool->getValue();
					}
					
					if ( NULL != config ) {
						dependency.config = config->getValue();
					}
					
					if ( NULL != buildIt ) {
						dependency.buildable = buildIt->getValue() == "yes" ? true : false;
					}

					Enumerator<XMLNode*>* execs = dep->getChildNodes();
					while ( execs->hasMoreElements() ) {
						XMLNode* execNode = execs->nextElement();
						if ( execNode->getName() == "exec" ) {
							XMLAttr* command = execNode->getAttrByName( "command" );
							if ( NULL != command ) {
								dependency.commands.push_back( command->getValue() );
							}
						}
					}
					
					//see if we *actually* need to add this depdendency based on
					//the current config(assuming there is one)
					if ( !defaultConfigName_.empty() ) {
						if ( (dependency.config.empty()) || 
								(dependency.partOfConfig(defaultConfigName_)) ) {
							target.dependencies.push_back(dependency);

							
						}
					}
					else {
						target.dependencies.push_back(dependency);
					}
				}
			}

			Enumerator<XMLNode*>* execs = node->getChildNodes();
			while ( execs->hasMoreElements() ) {
				XMLNode* execNode = execs->nextElement();
				if ( execNode->getName() == "exec" ) {
					XMLAttr* command = execNode->getAttrByName( "command" );
					if ( NULL != command ) {
						target.commands.push_back( command->getValue() );
					}
				}
			}

			target.project = currentProject;

			//see if we *actually* need to add this target based on
			//the current config(assuming there is one)
			if ( !defaultConfigName_.empty() ) {
				if ( (target.config.empty()) || (target.partOfConfig(defaultConfigName_)) ) {
					targets_[target.name] = target;
				}
			}
			else {
				targets_[target.name] = target;
			}
		}
		else if ( node->getName() == "project" ) {
			XMLAttr* name = node->getAttrByName( "name" );
			if ( NULL == name ) {
				error("invalid project syntax. Project has no \"name\" attribute");
				break;
			}

			Project project;
			project.name = name->getValue();

			XMLNode* dependsOn = node->getNodeByName( "dependsOn" );
			if ( NULL != dependsOn ) {
				Enumerator<XMLNode*>* depends = dependsOn->getChildNodes();
				while ( depends->hasMoreElements() ) {
					XMLNode* dep = depends->nextElement();
					XMLAttr* name = dep->getAttrByName( "name" );
					
					if ( NULL == name ) {
						error("invalid dependency syntax. Dependency has no \"name\" attribute");
						break;
					}
					
					Dependency dependency;				
					dependency.name = name->getValue();
					project.dependantProjects.push_back( dependency );
				}
			}

			currentProject = project.name;

			projects_[project.name] = project;
		}
	}

	nodes->reset();

	bool isfirst = true;

	

	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();

		if ( (node->getName() == "target") && (projects_.empty()) ) {
			XMLAttr* name = node->getAttrByName( "name" );
			XMLAttr* output = node->getAttrByName( "output" );
			

			if ( NULL == name ) {
				error("invalid Target! No name attribute specified");
				break;
			}

			//found the first target
			if ( (name->getValue() == firstTarget_) || 
					((true == isfirst) && (firstTarget_.empty())) ) {

				TargetMap::iterator found = targets_.find( name->getValue() );
				if ( found != targets_.end() ) {
					Target& target = found->second;
					
					buildDependencies( target );
					
					if ( firstTarget_.empty() ) {
						firstTarget_ = target.name;
					}
					
				}
				else {
					error("target not found");					
				}
				break;

			}

			isfirst = false;
		}
		else if ( (node->getName() == "project") && (!projects_.empty()) ) {
			XMLAttr* name = node->getAttrByName( "name" );

			if ( (name->getValue() == projectToBuild_) || 
				((true==isfirst) && (projectToBuild_.empty())) ) {
				ProjectMap::iterator found = projects_.find( name->getValue() );

				if ( found != projects_.end() ) {
					Project& project = found->second;
					
					TargetMap::iterator it = targets_.begin();
					while ( it != targets_.end() ) {
						Target& target = it->second;

						if ( target.project == project.name ) {

							project.targets.push_back( target );

							if ( (firstTarget_.empty()) && (isfirst) ) {
								firstTarget_ = target.name;
							}				
							
							isfirst = false;
						}	
						it ++;
					}

					buildDependencies( project );
					
					if ( projectToBuild_.empty() ) {
						projectToBuild_ = project.name;
					}
					
				}
				else {
					error("project not found");					
				}
				break;
			}
		}
	}

	dependsGraph_.createDependencyList( sortedDependencies );
}


void XMLMake::replaceAutomaticVariablesFor( String& s, Target& target, Dependency* dependency )
{
	int pos = 0;
	int len = 0;
	String varName;
	getVariablePos( s, varName, pos, len );
	while ( pos != String::npos ) {
		String component1;
		String component2;
		int pos1 = varName.find( "." );
		if ( pos1 != String::npos ) {
			component1 = varName.substr( 0, pos1 );
			if ( component1 == "dependsOn" ) {
				pos1 = varName.find( ".", pos1+1 );
				component1 = varName.substr( 0, pos1 );
			}
			else {
				int tmppos = pos1;
				tmppos = varName.find( ".", pos1+1 );
				if ( tmppos != String::npos ) {
					tmppos = varName.find_last_of( "." );
					component1 = varName.substr( 0, tmppos );
					pos1 = tmppos;
				}
			}
		}
		
		if ( pos1 != String::npos ) {
			component2 = varName.substr( pos1+1, varName.size() - (pos1+1) );
		}
		
		String replacement;
		if ( component1 == "target" ) {
			
			if ( component2 == "name" ) {
				replacement = target.name;									
			}
			else if ( component2 == "output" ) {
				replacement = target.output;
			}
		}
		else if ( component1 == "dependency" ) {
			if ( NULL != dependency ) {
				if ( component2 == "name" ) {
					replacement = dependency->name;
				}
				else if ( component2 == "output" ) {
					replacement = dependency->output;
				}
			}
		}
		else if ( component1 == "dependsOn.children" ) {
			for ( unsigned int i=0;i<target.dependencies.size();i++ ) {
				if ( target.dependencies[i].buildable ) {
					if ( component2 == "name" ) {
						replacement += target.dependencies[i].name;					
					}
					else if ( component2 == "output" ) {
						replacement += target.dependencies[i].output;
					}
					
					if ( (target.dependencies.size() > 1) && 
						(i < target.dependencies.size()-1) ) {
						replacement += " ";
					}
				}
			}
			
		}
		else { //it's probably a named target or dependency
			TargetMap::iterator found =  targets_.find( component1 );
			if ( found != targets_.end() ) {
				if ( component2 == "name" ) {
					replacement = found->second.name;
				}
				else if ( component2 == "output" ) {
					replacement = found->second.output;
				}
			}
			else {
				std::vector<Dependency>::iterator it = target.dependencies.begin();
				while ( it != target.dependencies.end() ) {
					if ( (*it).name == component1 ) {
						if ( component2 == "name" ) {
							replacement = (*it).name;
						}
						else if ( component2 == "output" ) {
							replacement = (*it).output;
						}
						break;
					}
					it ++;
				}
			}
		}
		if ( !replacement.empty() ) {
			s.erase( pos-2, len + 3);
			s.insert( pos-2, replacement );
			pos = (pos - 2) + replacement.size();
		}
		else {
			error( "no replacement variable found!" );
			break;
		}
		
		getVariablePos( s, varName, pos, len );
	}
}

void XMLMake::replaceAutomaticVariables( DependencyNode::Vector& sortedDependencies )
{
	DependencyNode::Iterator it = sortedDependencies.begin();
	while ( it != sortedDependencies.end() ) {
		DependencyNode* dep = *it;
		
		TargetMap::iterator found = targets_.find( dep->name() );
		if ( found != targets_.end() ) {
			Target& target = found->second;
			
			for ( unsigned int i=0;i<target.dependencies.size();i++ ) {
				found = targets_.find( target.dependencies[i].name );
				if ( found == targets_.end() ) {
					for ( unsigned int j=0;j<target.dependencies[i].commands.size();j++ ) {
						String command = target.dependencies[i].commands[j];
						replaceAutomaticVariablesFor( command, target, &target.dependencies[i] );
						target.dependencies[i].commands[j] = command;
					}
				}
			}


			for ( unsigned int j=0;j<target.commands.size();j++ ) {
				//printf( "\texec: %s\n", target.commands[j].c_str() );
				String command = target.commands[j];

				replaceAutomaticVariablesFor( command, target, NULL );

				target.commands[j] = command;
			}
		}

		it ++;
	}
}





void XMLMake::applyConfig( Dependency& dependency )
{
	String config = dependency.config;
	
	
	if ( (!config.empty() && (config == defaultConfig_.name)) || (config.empty()) ) {
		Tool tool;
		if ( dependency.tool.empty() ) {
			FilePath fp = dependency.name;
			tool = findToolForType( fp.getExtension(), defaultConfig_ );
		}
		else {
			tool = findToolByID( dependency.tool, defaultConfig_ );
		}
		
		if ( !tool.name.empty() ) {
			String command;
			if ( tool.commands.empty() ) {
				command = tool.name + " " + tool.flags + " " + dependency.name;
				dependency.commands.push_back( command );
			}
			else {
				dependency.commands.insert( dependency.commands.end(),
					tool.commands.begin(),
					tool.commands.end() );
			}
		}
		else if ( (tool.name.empty()) && (!dependency.tool.empty()) ) {
			printf( "dependency \"%s\" referenced a tool \"%s\" that doesn't exist!\n"\
					"To correct this please check the config section of \nyour makefile or the dependency/target in question.\n",
						dependency.name.c_str(), dependency.tool.c_str() );
			error( "dependency referenced a tool that doesn't exist!" );
			
			returnCode_ = -1;
			return;
		}
	}
	
}

void XMLMake::applyCurrentConfiguration( DependencyNode::Vector& sortedDependencies )
{
	DependencyNode::Iterator it = sortedDependencies.begin();
	while ( it != sortedDependencies.end() ) {
		DependencyNode* dep = *it;
		
		TargetMap::iterator found = targets_.find( dep->name() );
		if ( found != targets_.end() ) {
			Target& target = found->second;
			
			for ( unsigned int i=0;i<target.dependencies.size();i++ ) {
				//chekc to see if the "dependency" is actually a 
				//target
				Dependency& dependency = target.dependencies[i];
				applyConfig( dependency );
			}

			applyConfig( target );

			for ( unsigned int j=0;j<target.commands.size();j++ ) {
				//printf( "\texec: %s\n", target.commands[j].c_str() );
				String command = target.commands[j];

				replaceAutomaticVariablesFor( command, target, NULL );

				target.commands[j] = command;
			}
		}

		it ++;
	}
}

void XMLMake::parseMakeFile()
{
	includesMap_.clear();


	XMLParser parser;

	if ( masterContents_.empty() ) {
		return;
	}

	parser.parse( masterContents_ );
	
	Enumerator<XMLNode*>* nodes = parser.getParsedNodes();

	//step 4
	
	
	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();

		if ( node->getName() == "variable" ) {
			String realVal = node->getAttrByName("value")->getValue();
			replaceWithVariables( realVal );

			variableList_[ node->getAttrByName("name")->getValue() ] = realVal;
		}
		else if ( node->getName() == "include" ) {
			if ( NULL != node->getParentNode() ) {
				if ( node->getParentNode()->getName() != "config" ) {
					String path = node->getAttrByName("path")->getValue();
					
					replaceWithVariables( path );

					FilePath fp = path;
					if ( !fp.isDirectory() ) { //oops - forgot the trailing dir sep, add it 
						fp = fp.getFileName() + FilePath::getDirectorySeparator();
						path = fp;
					}					

					includeDirectories_.push_back( path );
				}
			}
			else {
				String path = node->getAttrByName("path")->getValue();
				FilePath fp = path;
				if ( !fp.isDirectory() ) { //oops - forgot the trailing dir sep, add it 
					fp = fp.getFileName() + FilePath::getDirectorySeparator();
					path = fp;
				}
				includeDirectories_.push_back( path );
			}
		}
	}
	
	

	//step 5
	replaceWithVariables( masterContents_ );

	parser.parse( masterContents_ );
	
	nodes = parser.getParsedNodes();

	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();

		if ( node->getName() == "config" ) {
			XMLAttr* name = node->getAttrByName( "name" );
			
			if ( NULL == name ) {
				error("invalid config found - no name specified!");
				break;
			} 
			Config config;
			config.name = name->getValue();

			configs_[config.name] = config;
			Enumerator<XMLNode*>* toolNodes = node->getChildNodes();
			while ( toolNodes->hasMoreElements() ) {				
				XMLNode* configChildNode = toolNodes->nextElement();
				if ( configChildNode->getName() == "tool" ) {
					XMLAttr* name = configChildNode->getAttrByName( "name" );
					if ( NULL == name ) {
						error("invalid tool found - no name specified!");
						break;
					} 
					
					XMLAttr* id = configChildNode->getAttrByName( "id" );
					if ( NULL == name ) {
						error("invalid tool found - no id specified!");
						break;
					} 
					
					XMLAttr* type = configChildNode->getAttrByName( "type" );
					
					Tool tool;
					if ( NULL != type ) {
						tool.type = type->getValue();
					}
					
					tool.name = name->getValue();
					tool.id = id->getValue();
					
					Enumerator<XMLNode*>* children = configChildNode->getChildNodes();
					while ( children->hasMoreElements() ) {
						XMLNode* child = children->nextElement();
						
						if ( child->getName() == "exec" ) {
							XMLAttr* command = child->getAttrByName( "command" );
							if ( NULL == command ) {
								error("invalid exec tag in tool found - no command specified!");
								break;
							}
							
							tool.commands.push_back( command->getValue() );
						}
						else if ( child->getName() == "flags" ) {
							XMLAttr* val = child->getAttrByName( "value" );
							if ( NULL == val ) {
								error("invalid flags tag in tool found - no value specified!");
								break;
							}
							
							tool.flags += val->getValue() + " ";
						}
					}
					//strip off any remaing white space
					while ( (tool.flags.size() > 1) && 
						(tool.flags[tool.flags.size()-1] == ' ') ) {
						tool.flags.erase( tool.flags.size()-1, 1 );
					}
					
					config.tools.push_back( tool );
				}
				else if ( configChildNode->getName() == "include" ) {
					if ( NULL == configChildNode->getAttrByName("path") ) {
						error("invalid include tag in tool found - no path specified!");
						break;
					}
					String path = configChildNode->getAttrByName("path")->getValue();
					FilePath fp = path;
					if ( !fp.isDirectory() ) { //oops - forgot the trailing dir sep, add it 
						fp = fp.getFileName() + FilePath::getDirectorySeparator();
						path = fp;
					}
					config.includes.push_back( path );
				}
			}
			configs_[config.name] = config;
		}
	}

	defaultConfig_ = configs_[defaultConfigName_];
	
	if ( !defaultConfig_.name.empty() ) {
		includeDirectories_.insert( includeDirectories_.end(), 
										defaultConfig_.includes.begin(),
										defaultConfig_.includes.end() );
	}

	sortedDependencies_.clear();

	buildSortedDependencyList( sortedDependencies_ );

	applyCurrentConfiguration( sortedDependencies_ );

	replaceAutomaticVariables( sortedDependencies_ );
}

bool XMLMake::fileExists( const String& filename )
{
	bool result = false;

	if ( !filename.empty() ) {
		
		FilePath fp = filename;
		FILE* f = fopen( fp.transformToOSSpecific().c_str(), "r" );
		
		if ( f ) {
			result = true;
			fclose( f );
		}
		else {
			verifyFileName( filename, true );
		}
	}
	return result;
}


String XMLMake::openFile( const String& filename )
{
	String result;

	FilePath fp = filename;
	if ( fp.isRelativePath() ) {
		fp = fp.expandRelativePathName( getCurrentDirectory() );	
	}
	FILE* f = fopen( fp.getFileName().c_str(), "rt" );
	
	if ( NULL != f ) {
		fseek( f, 0, SEEK_END );
		int size = ftell( f );
		
		fseek( f, 0, SEEK_SET );
		
		char* buf = new char[size+1];
		memset( buf, 0, size + 1 );	
		
		fread( buf, 1, size, f );
		
		fclose( f );
		buf[size] = 0;
		result = buf;
		delete [] buf;
	}
	else {
		error( "Failed to open file " + filename );
	}


	return result;
}	



//step 2
void XMLMake::readMakeFile( const String& fileName, int pos )
{
	String tmp = masterContents_;
	masterContents_ = openFile( fileName );


	if ( masterContents_.empty() ) {
		masterContents_ = tmp;
		return ;
	}

	XMLParser parser;

	parser.parse( masterContents_ );
	
	Enumerator<XMLNode*>* nodes = parser.getParsedNodes();
	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();

		if ( node->getName() == "import" ) {
			int pos1 = masterContents_.find( "<import", pos );
			if ( pos1 == String::npos ) {
				error("");
				return;
			}

			int pos2 = masterContents_.find_first_of( '>', pos1+1 );

			if ( pos2 == String::npos ) {
				error("");
				return;
			}

			masterContents_.erase( pos1, pos2-pos1+1 );
			
			if ( NULL == node->getAttrByName("file") ) {
				error( "invalid import statement - no \"file\" attribute found!" );

				return ;
			}
			readMakeFile( node->getAttrByName("file")->getValue(), pos1 );
		}
	}

	tmp.insert( pos, masterContents_ );
	masterContents_ = tmp;
}


void XMLMake::getVariablePos( const String s, String& varName, int& pos, int& length )
{
	//pos = String::npos;
	length = 0;
	varName = "";

	
	int p1 = String::npos;
	if ( pos != String::npos ) {
		p1 = s.find( "$(", pos );
	}
	else {
		p1 = s.find( "$(" );
	}

	if ( p1 == String::npos ) {
		pos = String::npos;
		return;
	}

	pos = p1 + 2;

	p1 = s.find_first_of( ")", pos );
	if ( p1 == String::npos ) {
		pos = String::npos;
		return;
	}

	length = p1-pos;
	varName = s.substr( pos, length );
}


void XMLMake::replaceWithVariables( String& s )
{
	int pos = -1;
	int length = 0;
	String varName;
	getVariablePos( s, varName, pos, length );

	while ( pos != String::npos ) {
		VariableMap::iterator found = variableList_.find( varName );
		if ( found != variableList_.end() ) {
			s.erase( pos-2, length + 3 );
			s.insert( pos-2, found->second );
		}		
		else {

			String envVarValue = getEnvironmentVariableValue( varName );
			if ( !envVarValue.empty() ) {
				s.erase( pos-2, length + 3 );
				s.insert( pos-2, envVarValue );
			}
			else {
				
				error("attempting to replace variables");
				pos += length + 1;
			}
			//break;			
		}
		
			
		getVariablePos( s, varName, pos, length );
	}
}

XMLMake::Tool XMLMake::findToolForType( const String& type, XMLMake::Config& config ) 
{
	Tool result;
	std::vector<Tool>::iterator it = config.tools.begin();
	while ( it != config.tools.end() ) {
		if ( (*it).hasType( type ) ) {
			result = *it;
			break;
		}
		it ++;
	}
	return result;
}

XMLMake::Tool XMLMake::findToolByID( const String& id, XMLMake::Config& config ) 
{
	Tool result;
	std::vector<Tool>::iterator it = config.tools.begin();
	while ( it != config.tools.end() ) {
		if ( (*it).id == id ) {
			result = *it;
			break;
		}
		it ++;
	}
	return result;
}

void XMLMake::initMakefile( const String& filename )
{
	switch ( action_ ) {
		case XMLMake::actCreateNew : case XMLMake::actNone : 
		case XMLMake::actPrintUsage: case XMLMake::actShowVersion : {
			//don't need to initialize or read anything from the
			//makefile!
			return;
		}
		break;
	}

	if ( !filename.empty() ) {		
		readMakeFile( filename );

		if ( masterContents_.empty() ) {
			printf( "no makefile was found named %s\nin directory: %s\n",
					filename.c_str(), getCurrentDirectory().c_str()	);
			returnCode_ = -1;
			return;
		}

		parseMakeFile();
	}
	else {
		returnCode_ = -1;
	}
}

void XMLMake::initMakefileFromData( const String& data )
{
	String tmp = masterContents_;

	masterContents_ = data;

	XMLParser parser;

	parser.parse( masterContents_ );
	
	int pos = 0;

	Enumerator<XMLNode*>* nodes = parser.getParsedNodes();
	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();

		if ( node->getName() == "import" ) {
			int pos1 = masterContents_.find( "<import", pos );
			if ( pos1 == String::npos ) {
				error("");
				return;
			}

			int pos2 = masterContents_.find_first_of( '>', pos1+1 );

			if ( pos2 == String::npos ) {
				error("");
				return;
			}

			masterContents_.erase( pos1, pos2-pos1+1 );

			readMakeFile( node->getAttrByName("file")->getValue(), pos1 );
		}
	}

	tmp.insert( pos, masterContents_ );
	masterContents_ = tmp;

	parseMakeFile();
}

bool XMLMake::initFromCommandLine( int argc, char** argv )
{
	defaultConfigName_ = "";	

	CommandLine cmdLine;
	includeDirectories_.clear();
	configToBuild_ = "";
	projectToBuild_ = "";
	generateFileType_ = "";
	generateOutputFileName_ = "";
	printDebug_ = false;
	verbose_ = false;
	configType_ = XMLMake::ncVC6Debug;
	action_ = XMLMake::actBuildTarget;	
	

	firstTarget_ = "";

	cmdLine.SplitLine( argc, argv );

	if ( cmdLine.HasSwitch( "-f" ) ) {		
		makefile_ = cmdLine.GetArgument( "-f", 0 );
		
		debugWithArgs( "makefile_: %s\n", makefile_.c_str() );
		
		FilePath dirPath = makefile_;
		String dirName = dirPath.expandRelativePathName( getCurrentDirectory() );
		debugWithArgs( "dirName: %s\n", dirName.c_str() );
		if ( dirName.empty() ) {
			dirName = dirPath.getPathName( true );
		}
		dirPath = dirName;
		debugWithArgs( "dirPath: %s\n", dirPath.getPathName(true).c_str() );
		
		setCurrentDirectory( dirPath.getPathName(true) );		

		dirPath = makefile_;
		//get rid of any relative pathing
		makefile_ = dirPath.getName( true );

	}
	else {
		makefile_ = "makefile.xml";
	}

	if ( cmdLine.HasSwitch( "-target" ) ) {
		firstTarget_ = cmdLine.GetArgument( "-target", 0 );
	}

	if ( cmdLine.HasSwitch( "-config" ) ) {
		defaultConfigName_ = cmdLine.GetArgument( "-config", 0 );
	}

	if ( cmdLine.HasSwitch( "-debug" ) ) {
		printDebug_ = true;
	}

	if ( cmdLine.HasSwitch( "-v" ) ) {
		verbose_ = true;
	}

	if ( cmdLine.HasSwitch( "-listtargets" ) ) {
		action_ = XMLMake::actListTargets;
	}
	else if ( cmdLine.HasSwitch( "-listconfigs" ) ) {
		action_ = XMLMake::actListConfigs;
	}
	else if ( cmdLine.HasSwitch( "-listprojs" ) ) {
		action_ = XMLMake::actListProjects;
	}
	else if ( cmdLine.HasSwitch( "-version" ) ) {
		action_ = XMLMake::actShowVersion;
	}
	else if ( cmdLine.HasSwitch( "-help" ) ) {
		action_ = XMLMake::actPrintUsage;
	}
	else if ( cmdLine.HasSwitch( "-clean" ) ) {
		action_ = XMLMake::actClean;
	}
	else if ( cmdLine.HasSwitch( "-install" ) ) {
		action_ = XMLMake::actInstall;
	}
	else if ( cmdLine.HasSwitch( "-new" ) ) {
		action_ = XMLMake::actCreateNew;
		if ( cmdLine.HasSwitch( "-configtype" ) ) {

			String type = cmdLine.GetArgument( "-configtype", 0 );
			if ( type == "VC6 Debug" ) {
				configType_ = ncVC6Debug;
			}
			else if ( type == "VC6 Release" ) {
				configType_ = ncVC6Release;
			}
			else if ( type == "GCC Debug" ) {
				configType_ = ncGCCDebug;
			}
			else if ( type == "GCC Release" ) {
				configType_ = ncGCCRelease;
			}
			
			
			if ( cmdLine.HasSwitch( "-project" ) ) {
				projectToBuild_ = cmdLine.GetArgument( "-project", 0 );
			}

			if ( cmdLine.HasSwitch( "-filelisting" ) ) {
				fileListing_ = cmdLine.GetArgument( "-filelisting", 0 );
			}
		}
	}

	if ( (XMLMake::actBuildTarget == action_) || 
			(XMLMake::actInstall == action_) ||
			(XMLMake::actClean == action_) ) {
		
		if ( argc > 1 ) {
			String firstArg = argv[1];
			int pos = firstArg.find( "-" );

			if ( (pos == String::npos) || (pos > 1) ) {
				//assume this is a project name, name cound have a - embedded 
				//in it, i.e. "MyFoo-Proj"
				projectToBuild_ = firstArg;
			}
		}
	}

	return true;
}

String XMLMake::usage()
{
	static String result = "xmake - The XML based simple make system for building C and C++ projects\n"\
						"Copyright 2002 Jim Crafton\n\n"\
						"Please use the following flags and syntax to build or \ncreate a makefile:\n\n"\
						"xmake [-list] || [projectname] -config <configuration name> [-f makefile name] || [-install] || [-clean]\n"\
						"arguments:\n"\
						"\t <projectname> is the name of the project to build in this makefile. If left blank then\n"\
						"\tthe first project found is the one that is built\n"\
						"\t-config   tells xmlmake which configuration to build\n\t as specified by the configuration name\n\n"\
						"\t-f        the makefile to use. If this is not specified then \n\txmlmake looks for a file named "\
						"\"makefile.xml\" in the \n\tcurrent directory. If this is not found then an \n\terror results.\n\n"\
						"\t-install  runs the \"install\" section of the makefile if present\n\n"\
						"\t-clean    removes all binary files produced by the makefile\n\n"\
						"\t-generate creates a class Makefile based on the contents of an\n"\
						"\texisting xmake project\n\n"\
						"\t-list     lists the configurations found in the makefile,\n"\
						"\torganized by project\n\n"\
						"\t-new      creates a new xmake makefile skeleton, with a single\n"\
						"\tempty project and a single configuration based on the configType\n"\
						"\targument. Can default to VC6 or GCC configurations\n\n"\
						"\t-project project name of the newly created xmake makefile\n\n"\
						"\t-f       file name of the actual xmake makefile that is\n"\
						"\tcreated. If not specified then the file created will be\n"\
						"\tcalled \"makefile.xml\"\n\n"\
						"\t-configtype specifies what kind of configuration to create. Must\n"\
						"\tbe either:\n"\
						"\t\t-\"VC6 Debug\" debug configuration for Microsoft's Visual C++\n"\
						"\t\tcompiler/linker\n"\
						"\t\t-\"VC6 Release\" release configuration for Microsoft's Visual C++\n"\
						"\t\tcompiler/linker\n"\
						"\t\t-\"GCC Debug\" debug configuration for GCC's C++\n"\
						"\t\tcompiler/linker\n"\
						"\t\t-\"GCC Release\" release configuration for GCC's C++\n"\
						"\t\tcompiler/linker\n\n"\
						"please report bugs to either ddiego@one.net or\n"\
						"http://sourceforge.net/tracker/?group_id=6796&atid=106796\n";

	return result;
}

void XMLMake::executeMakefile()
{
	if ( returnCode_ != 0 ) {
		return;
	}

	switch ( action_ ) {
		case XMLMake::actNone : case XMLMake::actPrintUsage: {
			printUsage();
		}
		break;

		case XMLMake::actBuildTarget : {
			buildTarget();
		}
		break;

		case XMLMake::actListTargets : {
			listTargets();
		}
		break;

		case XMLMake::actListConfigs : {
			listConfigs();
		}
		break;

		case XMLMake::actListProjects : {
			listProjects();
		}
		break;

		case XMLMake::actGenerateMakefile : {
			generateMakefile();
		}
		break;

		case XMLMake::actCreateNew : {
			createNew();
		}
		break;

		case XMLMake::actInstall : {
			install();
		}
		break;

		case XMLMake::actClean : {
			clean();
		}
		break;

		case XMLMake::actShowVersion : {
			showVersion();
		}
		break;
	}
}

void XMLMake::buildTarget()
{
	if ( returnCode_ != 0 ) {
		return;
	}

	//at the very least add the current directory to the include list
	String currentDirectory = getCurrentDirectory();

	includeDirectories_.push_back( currentDirectory );

	checkUptodateStatus( sortedDependencies_ );


	DependencyNode::Vector::reverse_iterator it = sortedDependencies_.rbegin();
	/*
	while ( it != sortedDependencies_.rend() ) {
		DependencyNode* dep = *it;
		TargetMap::iterator found = targets_.find( dep->name() );
		if ( found != targets_.end() ) {
			Target& target = found->second;
			printf( "build : %s\n", target.name.c_str() );
		}
		it ++;
	}
	*/

	bool upToDate = true;

	it = sortedDependencies_.rbegin();
	while ( it != sortedDependencies_.rend() ) {
		DependencyNode* dep = *it;
		
		TargetMap::iterator found = targets_.find( dep->name() );
		if ( found != targets_.end() ) {
			int execCount = 0;

			Target& target = found->second;
			printf( "target: %s\n", target.name.c_str() );
			fflush( NULL );

			
			execCount += target.commands.size();


			for ( unsigned int i=0;i<target.dependencies.size();i++ ) {
				Dependency& dep = target.dependencies[i];
				found = targets_.find( dep.name );

				if ( (found == targets_.end()) && (!dep.uptodate) && (dep.buildable) ) {					
					//execCount += dep.commands.size();
					printf( " dependency: %s\n", dep.name.c_str() );

					for ( unsigned int j=0;j<dep.commands.size();j++ ) {						
						upToDate = false; // uptodate is false cause we're building something...
						printf( "  %s\n", dep.commands[j].c_str() );
						fflush( NULL );
						if ( 0 != exec( dep.commands[j], currentDirectory ) ) {
							//error executing command!
							error( "Error executing \"" + dep.commands[j] + "\"" );
							returnCode_ = -1;
							return;
						}
						execCount ++;						
					}
					printf( "\n\n" );
					fflush( NULL );
				}
			}

			for ( unsigned int j=0;j<target.commands.size();j++ ) {
				printf( " %s\n", target.commands[j].c_str() );
				fflush( NULL );
				upToDate = false; // uptodate is false cause we're building something...
				
				if ( 0 != exec( target.commands[j], currentDirectory ) ) {
					//error executing command!
					error( "Error executing \"" + target.commands[j] + "\"" );
					returnCode_ = -1;
					return;
				}
			}
			printf( "\n\n" );
			fflush( NULL );

			//we have an error if we have no commands, 
			//the target is not uptodate, AND the target 
			//has an actual output filename
			if ( (0 == execCount) && (!target.uptodate) && (target.name != target.output) ) {
				//error!!!
				printf( "Target %s has no commands to execute!\n", target.name.c_str() );
				returnCode_ = -1;
				return;
			}
		}

		it ++;
	}

	if ( upToDate ) {
		printf( "Nothing to build for target %s, all dependendencies are up-to-date.\n",
					firstTarget_.c_str() );
	}
}

void XMLMake::printUsage()
{
	printf( XMLMake::usage().c_str() );
}

void XMLMake::listTargets()
{
	StringList targets = getTargets();
	StringListIterator it = targets.begin();
	printf( "targets: \n" );
	while ( it != targets.end() ) {
		printf( "\t%s\n", (*it).c_str() );
		it ++;
	}
}

void XMLMake::listConfigs()
{
	StringList configs = getConfigs();
	StringListIterator it = configs.begin();
	printf( "configurations: \n" );
	while ( it != configs.end() ) {
		printf( "\t%s\n", (*it).c_str() );
		it ++;
	}
}

void XMLMake::listProjects()
{
	StringList projects = getProjects();
	StringListIterator it = projects.begin();
	printf( "projects: \n" );
	while ( it != projects.end() ) {
		printf( "\t%s\n", (*it).c_str() );
		it ++;
	}
}

void XMLMake::generateMakefile()
{

}

void XMLMake::createNew()
{
	String makefileContents;

	String fileName;
	fileName = makefile_;
	String configName;
	
	String compiler;
	String linker;

	String cflags;
	String lflags;
	
	String rcFlags;

	String objExt;
	switch ( this->configType_ ) {
		case ncVC6Debug : {
			configName = "VC6 Debug";			
			compiler = "cl";
			linker = "link";
			cflags = "/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I .\\ /DWIN32 /D_DEBUG /D_MBCS /D_WINDOWS /Fo$(dependency.output) /FD /GZ /c";
			lflags = "/nologo /subsystem:console /incremental:yes /pdb:$(target.output).pdb /debug /machine:I386 /out:$(target.output) /pdbtype:sept";			
			rcFlags = "/v /d _DEBUG /fo " + projectToBuild_ + ".res";
			objExt = ".obj";
		}
		break;

		case ncVC6Release : {
			configName = "VC6 Release";			
			compiler = "cl";
			linker = "link";

			cflags = "/nologo /MD /W3 /Gm /GR /GX /ZI /O1 /I .\\ /DNDEBUG /DWIN32 /D_MBCS /D_WINDOWS /Fo$(dependency.output) /FD /GZ /c ";
			lflags = "/nologo /subsystem:console /incremental:yes /pdb:$(target.output).pdb /machine:I386 /out:$(target.output) /pdbtype:sept";
			
			rcFlags = "/v /d NDEBUG /fo " + projectToBuild_ + ".res";
			objExt = ".obj";
		}
		break;

		case ncGCCDebug : {
			configName = "GCC Debug";			
			compiler = "g++";
			linker = "g++";			

			cflags = "-o $(dependency.output) -g -I ./ -D _DEBUG -c ";
			lflags = "-o ";
			objExt = ".o";
		}
		break;

		case ncGCCRelease : {
			configName = "GCC Release";			
			compiler = "g++";
			linker = "g++";			
			cflags = "-o $(dependency.output) -O2 -I ./ -c ";
			lflags = "-o ";
			objExt = ".o";
		}
		break;

	}
	makefileContents = "<!--Autogenerated xmake makefile for project " + projectToBuild_ + "\n";	
	makefileContents += "-->\n\n\n";
	

	makefileContents += "<config name=\"" + configName + "\">\n";	
	makefileContents += "\t<!-- un-comment this out if you want to add\n";
	makefileContents += "\tcustom include paths for this configuration.\n";
	makefileContents += "\t\t<include path=\"\"/>\n";
	makefileContents += "\t-->\n\n";
	makefileContents += "\t<!-- compiler tool -->\n";
	makefileContents += "\t<tool id=\"cc\" name=\"" + compiler + "\" type=\".cc;.cpp;.cxx\">\n";
	makefileContents += "\t\t<flags value=\"" + cflags + "\"/>\n";
	makefileContents += "\t\t<exec command=\"" + compiler + " " + cflags + " $(dependency.name) " + "\"/>\n";
	makefileContents += "\t</tool>\n\n";

	makefileContents += "\t<!-- linker tool -->\n";
	makefileContents += "\t<tool id=\"link\" name=\"" + linker + "\" >\n";
	makefileContents += "\t\t<flags value=\"" + lflags + "\"/>\n";
	makefileContents += "\t\t<exec command=\"" + linker + " " + lflags + " $(target.output) $(dependsOn.children.output) " + "\"/>\n";
	makefileContents += "\t</tool>\n";

	if ( (configType_ == ncVC6Debug) || (configType_ == ncVC6Release) ) {
		makefileContents += "\n\t<!-- resource tool for compiling rc scripts-->\n";
		makefileContents += "\t<tool id=\"rc\" name=\"rc.exe\" type=\".rc\">\n";
		makefileContents += "\t\t<flags value=\"" + rcFlags + "\"/>\n";
		makefileContents += "\t\t<exec command=\"rc.exe " + rcFlags + " $(dependency.name) " + "\"/>\n";
		makefileContents += "\t</tool>\n\n";
	}
	
	makefileContents += "</config>\n\n\n";


	makefileContents += "<project name=\"" + projectToBuild_ + "\" >\n";
	makefileContents += "\t<dependsOn>\n";
	makefileContents += "\t\t<!-- place a dependency entry here where the\n";
	makefileContents += "\t\tdependency is another project that must be built\n";
	makefileContents += "\t\tbefore this project. The form is:\n";
	makefileContents += "\t\t\t<dependency name=\"name_of_some_project\"/>\n";
	makefileContents += "\t\t-->\n";
	makefileContents += "\t</dependsOn>\n\n\n";
	makefileContents += "\t<!--put your project's targets here.-->\n";

	String target = firstTarget_;
	if ( target.empty() ) {
		target = projectToBuild_;
	}

	makefileContents += "\t<target name=\"" + target + "\" tool=\"link\" config=\"" + configName + "\">\n";
	makefileContents += "\t\t<dependsOn>\n";
	makefileContents += "\t\t<!-- put the projects source files here -->\n";


	if ( !fileListing_.empty() ) {
		FILE* fileList = fopen( fileListing_.c_str(), "r" );
		if ( NULL != fileList ) {
			char fileName[1024];
			FilePath fp; 
			String currentDirectory = getCurrentDirectory();
			String relPath;
			String ext; 
			while( fgets(fileName, 1024, fileList) ) {
				fileName[strlen(fileName)-1] = 0;
				fp = fileName;
				makefileContents += "\t\t\t<dependency name=\"";
				if ( !fp.isRelativePath() ) {
					relPath = fp.transformToRelativePathName( currentDirectory );
				}
				else {
					relPath = fp;
				}
				makefileContents += relPath + "\"";
				
				ext = fp.getExtension();
	
				if ( (ext == ".cpp") || (ext == ".cc")
					|| (ext == ".cxx") || (ext == ".c") ) {
					makefileContents += " output=\"";
					relPath = fp.getPathName() + "Objs/" + fp.getName() + objExt;
					
					makefileContents += relPath + "\"";
				}
				if ( (ext == ".hpp") || (ext == ".hh")
					|| (ext == ".hxx") || (ext == ".h") || (ext == ".i") || (ext == ".inl") ) {
				
					makefileContents += " build=\"no\" ";
				}

				makefileContents += " />\n";
			}
			
			fclose( fileList );
		}
	}


	makefileContents += "\t\t</dependsOn>\n";
	makefileContents += "\t</target>\n";	

	makefileContents += "</project>\n";


	if ( !makefileContents.empty() ) {
		FILE* f = fopen( fileName.c_str(), "w" );
		if ( NULL != f ) {
			fwrite( makefileContents.c_str(), sizeof(char), makefileContents.size(), f );
			fclose( f );
		}
	}
	else {
		printf( "No output of type \"%s\" generated for file %s\n", fileName.c_str(),
			fileName.c_str() );
	}
}

void XMLMake::install()
{

}

void XMLMake::clean()
{
	DependencyNode::Iterator it = sortedDependencies_.begin();
	while ( it != sortedDependencies_.end() ) {
		DependencyNode* dep = *it;
		
		TargetMap::iterator found = targets_.find( dep->name() );
		if ( found != targets_.end() ) {
			Target& target = found->second;

			printf( "deleting target: %s\n", target.output.c_str() );
			deleteFile( target.output );
			for ( unsigned int i=0;i<target.dependencies.size();i++ ) {
				Dependency& dep = target.dependencies[i];
				found = targets_.find( dep.output );

				if ( (found == targets_.end()) && (dep.name != dep.output) ) {					
					printf( "\tdeleting dep: %s\n", target.dependencies[i].output.c_str() );
					deleteFile( dep.output );
				}
			}			
		}

		it ++;
	}
}

void XMLMake::showVersion()
{
	String version = getVersion() + "\n";
	printf( version.c_str() );
}

StringList XMLMake::getTargets()
{
	StringList result;
	DependencyNode::Iterator it = sortedDependencies_.begin();
	while ( it != sortedDependencies_.end() ) {
		DependencyNode* dep = *it;
		
		TargetMap::iterator found = targets_.find( dep->name() );
		if ( found != targets_.end() ) {
			Target& target = found->second;
			
			result.push_back( target.name );
		}

		it ++;
	}

	return result;
}

StringList XMLMake::getProjects()
{
	StringList result;

	return result;
}

StringList XMLMake::getConfigs()
{
	StringList result;
	ConfigMap::iterator it = configs_.begin();
	while ( it != configs_.end() ) {
		result.push_back( it->second.name );
		it ++;
	}

	return result;
}


