//System.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//#include <varargs.h>

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/Locales.h"


namespace VCF {

bool System::unicodeEnabled = false;

static std::map<String,String> cachedResourceDirMap;


System* System::getInstance()
{
	return System::systemInstance;
}

System* System::create()
{
	if ( NULL == System::systemInstance ) {
		System::systemInstance = new System();
	}

	return System::systemInstance;
}

void System::terminate()
{
	delete System::systemInstance;
	System::systemInstance = NULL;
}


System::System():
	systemPeer_(NULL),
	errorLogInstance_(NULL),
	locale_(NULL),
	resBundle_(NULL)
{
	systemPeer_ = SystemToolkit::createSystemPeer();

	if ( NULL == systemPeer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2( L"Unable to create a System peer!" ) );
	}

	System::unicodeEnabled = systemPeer_->isUnicodeEnabled();

	errorLogInstance_ = NULL;

	locale_ = new Locale( L"", L"" );

	resBundle_ = new ResourceBundle();
}

System::~System()
{
	delete resBundle_;
	delete locale_;
	delete systemPeer_;
}

String System::findResourceDirectory()
{
	String result;
	
	const CommandLine& cmdLine = FoundationKit::getCommandLine();

	return System::findResourceDirectoryForExecutable( cmdLine.getArgument(0) );
}

String System::findResourceDirectory( Locale* locale )
{
	VCF_ASSERT( NULL != locale );
	
	const CommandLine& cmdLine = FoundationKit::getCommandLine();

	return System::findResourceDirectory( cmdLine.getArgument(0), locale );
}

String System::findResourceDirectory( const String& fileName, Locale* locale )
{
	VCF_ASSERT( NULL != locale );
	VCF_ASSERT( !fileName.empty() );

	String result;	
	bool foundDir = false;

	std::map<String,String>::iterator found = cachedResourceDirMap.find( fileName );
	if ( found != cachedResourceDirMap.end() ) {
		result = found->second;
		String localeName = locale->getName();
		foundDir = result.find( localeName ) != String::npos;
	}

	if ( !foundDir ) {
		FilePath appPath = fileName;

		UnicodeString appDir = appPath.getPathName(true);

		//case A: or case B:
		String tmp = appDir + "Resources";
		if ( File::exists( tmp ) ) {
			result = tmp;
		}
		else {		
			std::vector<String> pathComponents = appPath.getPathComponents();
			std::vector<String>::reverse_iterator it = pathComponents.rbegin();
			int depth = 1;
			while ( it != pathComponents.rend() && (depth < 3) ) {
				int length = (*it).length();// + FilePath::getDirectorySeparator().length();

				//if depth == 1 then case C:
				//if depth == 2 then case D:
				appDir.erase( appDir.length()-length, length );

				tmp = appDir + "Resources";
				if ( File::exists( tmp ) ) {
					result = tmp;
					break;
				}


				depth ++;
				it ++;
			}
		}


		if ( !result.empty() ) {
			//found the top level res dir
			//now attempt to see if we can use a more locale specific dir
			//if not, fall back on the default Resources dir		
			if ( File::exists( result ) ) {
				String localeName = locale->getName();
				tmp = result + FilePath::getDirectorySeparator() + localeName;
				if ( File::exists( tmp ) ) {
					result = tmp;
				}
				//add the dir sep at the end to be proper
				result += FilePath::getDirectorySeparator();
			}
			else {
				//if we still don't have anything, then
				//assume the path where the application lives.
				//this works for app's that aren't using the 
				//bundle dir layout.
				result = appPath.getPathName(true);
			}
		}

		cachedResourceDirMap[fileName] = result;
	}

	return result;
}

String System::findResourceDirectoryForExecutable( const String& fileName )
{
	return System::findResourceDirectory( fileName, System::getCurrentThreadLocale() );
}

uint32 System::getTickCount()
{
	if ( NULL != System::getInstance()->systemPeer_ ) {
		return System::getInstance()->systemPeer_->getTickCount();
	}
	else return 0;
}

void System::sleep( const uint32& milliseconds )
{
	System::getInstance()->systemPeer_->sleep( milliseconds );
}

void System::setErrorLog( ErrorLog* errorLog )
{
	System::getInstance()->errorLogInstance_ = errorLog;
}

void System::print( const String& text )
{	
#ifdef VCF_OSX
	//JC - I got rid of CFShow as it doesn't 
	//seem to work well in a multi-threaded context, and also seems a 
	//bit slow
	printf( text.ansi_c_str() );
#elif defined(VCF_CW_W32)
	printf( text.ansi_c_str() );
#else
	wprintf( text.c_str() );
#endif

	if ( NULL != System::systemInstance ) {
		if ( NULL != System::getInstance()->errorLogInstance_ ) {			
			System::getInstance()->errorLogInstance_->toLog( text );
		}
	}
}


void System::println( const String& text )
{
	String output = text;

	if ( output.empty() ) {
		return;
	}

	output += L"\n";

#ifdef VCF_OSX
	//JC - I got rid of CFShow as it doesn't 
	//seem to work well in a multi-threaded context, and also seems a 
	//bit slow
	printf( output.ansi_c_str() );
#elif defined(VCF_CW_W32)
	printf( output.ansi_c_str() );
#else
	wprintf( output.c_str() );
#endif

	if ( NULL != System::systemInstance ) {
		if ( NULL != System::getInstance()->errorLogInstance_ ) { 
			System::getInstance()->errorLogInstance_->toLog( output );
		}
	}
}

/*
void System::println( const Format& formatter )
{
	String output = formatter;

	if ( output.empty() ) {
		return;
	}

	output += "\n";

#ifdef VCF_OSX
	CFMutableStringRef tmp = CFStringCreateMutable( NULL, 0 );

	CFStringAppendCharacters( tmp, output.c_str(), output.size() );
	CFShow( tmp );
	CFRelease( tmp );
#else
	wprintf( output.c_str() );
#endif

	if ( NULL != System::systemInstance ) {
		if ( NULL != System::getInstance()->errorLogInstance_ ) { 
			System::getInstance()->errorLogInstance_->toLog( output );
		}
	}
}
*/

void System::errorPrint( BasicException* exception )
{
	System::print( Format("Exception occured ! Error string: %s\n") % exception->getMessage() );
}

bool System::doesFileExist( const String& fileName )
{
	return System::getInstance()->systemPeer_->doesFileExist( fileName );
}

String System::getEnvironmentVariable( const String& variableName )
{
	return System::getInstance()->systemPeer_->getEnvironmentVariable( variableName );
}

void System::setEnvironmentVariable( const String& variableName, const String& newValue )
{
	System::getInstance()->systemPeer_->setEnvironmentVariable( variableName, newValue );
}

void System::addPathDirectory( const String& directory )
{
	System::getInstance()->systemPeer_->addPathDirectory( directory );
}

String System::getCurrentWorkingDirectory()
{
	return System::getInstance()->systemPeer_->getCurrentWorkingDirectory();
}

void System::setCurrentWorkingDirectory( const String& currentDirectory )
{
	System::getInstance()->systemPeer_->setCurrentWorkingDirectory( currentDirectory );
}

String System::getCommonDirectory( System::CommonDirectory directory )
{
	return System::getInstance()->systemPeer_->getCommonDirectory( directory );
}

String System::createTempFileName( System::CommonDirectory directory )
{
	return System::createTempFileName( System::getCommonDirectory( directory ) );
}

String System::createTempFileName( const String& directory )
{
	return System::getInstance()->systemPeer_->createTempFileName( directory );
}

void System::setDateToSystemTime( DateTime* date )
{
	System::getInstance()->systemPeer_->setDateToSystemTime( date );
}

void System::setDateToLocalTime( DateTime* date )
{
	System::getInstance()->systemPeer_->setDateToLocalTime( date );
}

void System::setTimeZoneToLocal( const DateTime& currentDate, TimeZone& tz )
{
	System::getInstance()->systemPeer_->setTimeZoneToLocal( currentDate, tz );
}


void System::setCurrentThreadLocale( Locale* locale )
{
	Locale* current = System::getInstance()->locale_;
	current->getPeer()->setLocale( locale->getLanguageCodeString(), locale->getCountryCodeString(), "" );
	current->setEncoding( locale->getEncoding() );

	System::getInstance()->systemPeer_->setCurrentThreadLocale( locale );
}

Locale* System::getCurrentThreadLocale()
{
	System* system = System::getInstance();
	if ( NULL != system ) {
		system->locale_->getPeer()->setToCurrentThread();
			
			//setLocale( L"", L"", L"" ); //updates it to current thread's locale info
		return System::getInstance()->locale_;
	}

	return NULL;
}

bool System::isUnicodeEnabled()
{
	return System::unicodeEnabled;
}

DateTime System::convertUTCTimeToLocalTime( const DateTime& date )
{
	return System::getInstance()->systemPeer_->convertUTCTimeToLocalTime( date );
}

DateTime System::convertLocalTimeToUTCTime( const DateTime& date )
{
	return System::getInstance()->systemPeer_->convertLocalTimeToUTCTime( date );
}

ResourceBundle* System::getResourceBundle()
{
	return System::getInstance()->resBundle_;
}

String System::getInfoFileFromFileName( const String& fileName )
{
	String result;
	

	bool isDir = false;
	{
		File file(fileName);
		if ( file.isDirectory() ) {
			isDir = true;
		}
	}
	
	bool found = false;
	
	FilePath fp = fileName;

	if ( isDir ) {
		
		if ( !fp.isDirectoryName() ) {
			fp = fp.getFileName() + FilePath::getDirectorySeparator();
		}
		
		String infoFilename = fp + "Info.plist";
		
		if ( File::exists( infoFilename ) ) {
			result = infoFilename;
		}
		else {
			infoFilename = fp + "Info.xml";
			if ( File::exists( infoFilename ) ) {
				result = infoFilename;
			}
		}
		
		if ( !found ) {
			//try Contents dir!
			infoFilename = fp + "Contents/Info.plist";
			if ( File::exists( infoFilename ) ) {
				result = infoFilename;
			}
			else {
				infoFilename = fp + "Contents/Info.xml";
				if ( File::exists( infoFilename ) ) {
					result = infoFilename;
				}
			}
		}
	}
	else {
		std::vector<String> pathComponents = fp.getPathComponents();
		std::vector<String>::reverse_iterator it = pathComponents.rbegin();
		int depth = 0;
		
		String fileDir = fp.getPathName(true);
		
		while ( it != pathComponents.rend() && (depth < 4) ) {
			const String& dirComponent = *it;
			
			int length = dirComponent.length();// + FilePath::getDirectorySeparator().length();		
						
			String infoFilename = fileDir + "Info.plist";

			if ( File::exists( infoFilename) ) {
				result = infoFilename;
				break;
			}
			else {
				infoFilename = fileDir + "Info.xml";
				if ( File::exists( infoFilename) ) {
					result = infoFilename;
					break;
				}
				infoFilename = fileDir + "Contents/Info.plist";
				if ( File::exists( infoFilename ) ) {
					result = infoFilename;					
					break;
				}
				else {
					infoFilename = fileDir + "Contents/Info.xml";
					if ( File::exists( infoFilename ) ) {
						result = infoFilename;
						break;
					}
				}
			}
			
			fileDir.erase( fileDir.length()-length, length );

			depth ++;
			it ++;
		}
	}


	

	return result;
}


ProgramInfo* System::getProgramInfoFromFileName( const String& fileName )
{
	ProgramInfo* result = 
		System::getInstance()->systemPeer_->getProgramInfoFromFileName( fileName );

	if ( NULL == result ) {
			
		String infoFilename = System::getInfoFileFromFileName( fileName );
		
		result = System::getProgramInfoFromInfoFile( infoFilename );
	}
	return result;
}

ProgramInfo* System::getProgramInfoFromInfoFile( const String& infoFileName, const String& programFileName )
{
	ProgramInfo* result = NULL;

	if ( !infoFileName.empty() ) {
		String name;
		String programFileName2 = programFileName;
		String author;
		String copyright;
		String company;
		String description;
		String programVersion;
		String fileVersion;		
		String helpDirectory;
		String helpName;

		
		XMLParser xmlParser;
		FileInputStream fs(infoFileName);
		xmlParser.parse( &fs );				
		fs.close();
		
		XMLNode* dictNode = NULL;
		Enumerator<XMLNode*>* nodes = xmlParser.getParsedNodes();
		while ( nodes->hasMoreElements() ) {
			XMLNode* node = nodes->nextElement();
			if ( node->getName() == L"plist" ) {
				dictNode = node->getNodeByName( L"dict" );
				break;
			}
		}
		
		if ( NULL != dictNode ) {
			nodes = dictNode->getChildNodes();
			while ( nodes->hasMoreElements() ) {
				XMLNode* node = nodes->nextElement();
				XMLNode* val = NULL;
				
				if ( nodes->hasMoreElements() ) {
					val = nodes->nextElement();
				}
				
				if ( (NULL != val) && (node->getName() == "key") ) {
					String cdata = node->getCDATA();
					StringUtils::trimWhiteSpaces( cdata );

					if ( cdata == "CFBundleName" ) {
						name = val->getCDATA();
						StringUtils::trimWhiteSpaces( name );
					}
					else if ( cdata == "CFBundleDisplayName" ) {
						name = val->getCDATA();
						StringUtils::trimWhiteSpaces( name );
					}
					else if ( cdata == "CFBundleVersion" ) {
						fileVersion = programVersion = val->getCDATA();
						StringUtils::trimWhiteSpaces( fileVersion );
					}
					else if ( cdata == "CFBundleGetInfoString" ) {
						copyright = programVersion = val->getCDATA();
						StringUtils::trimWhiteSpaces( copyright );
					}
					else if ( cdata == "NSHumanReadableCopyright" ) {
						copyright = programVersion = val->getCDATA();	
						StringUtils::trimWhiteSpaces( copyright );
					}
					else if ( cdata == "CFBundleExecutable" ) {
						programFileName2 = programVersion = val->getCDATA();
						StringUtils::trimWhiteSpaces( programFileName2 );
					}
					else if ( cdata == "CFBundleHelpBookName" ) {
						helpName = val->getCDATA();	
						StringUtils::trimWhiteSpaces( helpName );
					}
					else if ( cdata == "CFBundleHelpBookFolder" ) {
						helpDirectory = val->getCDATA();
						StringUtils::trimWhiteSpaces( helpDirectory );
					}
					
					//VCF cross platform keys
					else if ( cdata == "ProgramVersion" ) {
						programVersion = val->getCDATA();
						StringUtils::trimWhiteSpaces( programVersion );
					}
					else if ( cdata == "FileVersion" ) {
						programVersion = val->getCDATA();
						StringUtils::trimWhiteSpaces( programVersion );
					}
					else if ( cdata == "ProductName" ) {
						name = val->getCDATA();
						StringUtils::trimWhiteSpaces( name );
					}
					else if ( cdata == "Copyright" ) {
						copyright = val->getCDATA();
						StringUtils::trimWhiteSpaces( copyright );
					}
					else if ( cdata == "Author" ) {
						author = val->getCDATA();
						StringUtils::trimWhiteSpaces( author );
					}
					else if ( cdata == "Company" ) {
						company = val->getCDATA();
						StringUtils::trimWhiteSpaces( company );
					}
					else if ( cdata == "Description" ) {
						description = val->getCDATA();
						StringUtils::trimWhiteSpaces( description );
					}
					else if ( cdata == "Executable" ) {
						programFileName2 = val->getCDATA();
						StringUtils::trimWhiteSpaces( programFileName2 );
					}
					else if ( cdata == "HelpName" ) {
						helpName = val->getCDATA();	
						StringUtils::trimWhiteSpaces( helpName );
					}
					else if ( cdata == "HelpDirectory" ) {
						helpDirectory = val->getCDATA();
						StringUtils::trimWhiteSpaces( helpDirectory );
					}
				}
			}
			
			result = new ProgramInfo( name, programFileName2, author, copyright, company, description, programVersion, fileVersion, helpDirectory, helpName );
		}
	}

	return result;
}

ProgramInfo* System::getProgramInfoFromInfoFile( const String& infoFileName )
{
	return System::getProgramInfoFromInfoFile( infoFileName, "" );
}

void System::internal_replaceResourceBundleInstance( ResourceBundle* newInstance )
{
	if ( NULL != System::getInstance()->resBundle_ ) {
		delete System::getInstance()->resBundle_;
		System::getInstance()->resBundle_ = NULL;
	}
	System::getInstance()->resBundle_ = newInstance;
}

String System::getOSName()
{
	return System::getInstance()->systemPeer_->getOSName();
}

String System::getOSVersion()
{
	return System::getInstance()->systemPeer_->getOSVersion();
}


String System::getCompiler()
{
	String result(VCF_COMPILER_NAME);
	return result;
}

String System::getComputerName()
{
	return System::getInstance()->systemPeer_->getComputerName();
}


String System::getUserName()
{
	return System::getInstance()->systemPeer_->getUserName();
}

String System::getBundlePathFromExecutableName( const String& fileName )
{
	String result ;

	ProgramInfo* info = System::getProgramInfoFromFileName( fileName );
	if ( NULL == info ) {
		return result;
	}



	String bundleName = info->getProgramName();
	//unfortunately ::GetModuleFileNameW gives a
	// lowercase path under vc70, but not under vc6 !!
	bundleName = StringUtils::lowerCase( bundleName );

	//done with bundle !
	delete info;

	VCF_ASSERT( !bundleName.empty() );

	if ( bundleName.empty() ) {
		return result;
	}

	FilePath appPath = fileName;
	String appDir = appPath.getPathName(true);
	appPath = StringUtils::lowerCase( appPath );
	
	std::vector<String> pathComponents = appPath.getPathComponents();
	std::vector<String>::reverse_iterator it = pathComponents.rbegin();
	int depth = 0;
	
	while ( it != pathComponents.rend() && (depth < 4) ) {
		String dirComponent = *it;

		int length = dirComponent.length();// + FilePath::getDirectorySeparator().length();
		
		dirComponent.erase( dirComponent.size()-1, 1 );//trim off trailing "/"

		
		//the match is not an equals, because the bundle might be
		//called "Foo", and the current dir might be "Foo.app"
		if ( dirComponent.find(bundleName) != String::npos ) {
			result = appDir;
			break;
		}
		
		appDir.erase( appDir.length()-length, length );

		depth ++;
		it ++;
	}

	return result;
}

String System::getExecutableNameFromBundlePath( const String& fileName )
{
	String result;

	File file(fileName);
	if ( !file.isDirectory() ) {
		result = fileName;
		return result;
	}

	ProgramInfo* info = System::getProgramInfoFromFileName( fileName );
	if ( NULL == info ) {
		return result;
	}

	String executableName = info->getProgramFileName();

	delete info;

	if ( executableName.empty() ) {
		return result;
	}

	FilePath fp = FilePath::makeDirectoryName( fileName );
	//attempt 1
	result = fp + executableName;
	if ( !File::exists( result ) ) {
		//attempt 2!
		result = fp + "Contents/" + executableName;
		if ( !File::exists( result ) ) {
			//attempt 3
			result = fp + "Contents/" + System::getOSName() + FilePath::getDirectorySeparator() + executableName;
			if ( !File::exists( result ) ) {
				//attempt 4
				result = fp + "Contents/" + System::getOSName() + FilePath::getDirectorySeparator() + 
							System::getCompiler() + FilePath::getDirectorySeparator() + executableName;
			}
		}
	}

	if ( !File::exists( result ) ) {
		result = "";
	}

	return result;

}	

};


/**
$Id$
*/
