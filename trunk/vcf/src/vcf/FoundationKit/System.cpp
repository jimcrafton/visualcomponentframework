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


using namespace VCF;



System* System::create()
{
	if ( NULL == System::systemInstance ) {
		System::systemInstance = new System();		
		System::systemInstance->init();
	}

	return System::systemInstance;
}

void System::terminate()
{
	System::systemInstance->free();
}


System::System():
	systemPeer_(NULL),
	errorLogInstance_(NULL),
	locale_(NULL),
	unicodeEnabled_(false),
	resBundle_(NULL)
{
	systemPeer_ = SystemToolkit::createSystemPeer();

	if ( NULL == systemPeer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2( L"Unable to create a System peer!" ) );
	}

	unicodeEnabled_ = systemPeer_->isUnicodeEnabled();

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
	
	CommandLine cmdLine = FoundationKit::getCommandLine();

	return System::findResourceDirectoryForExecutable( cmdLine.getArgument(0) );
}

String System::findResourceDirectoryForExecutable( const String& fileName )
{
	String result;	

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
		String localeName = System::getCurrentThreadLocale()->getName();
		tmp = result + FilePath::getDirectorySeparator() + localeName;
		if ( File::exists( tmp ) ) {
			result = tmp;
		}

		//add the dir sep at the end to be proper
		result += FilePath::getDirectorySeparator();
	}

	return result;
}


unsigned long System::getTickCount()
{
	if ( NULL != System::systemInstance->systemPeer_ ) {
		return System::systemInstance->systemPeer_->getTickCount();
	}
	else return 0;
}

void System::sleep( const uint32& milliseconds )
{
	System::systemInstance->systemPeer_->sleep( milliseconds );
}

void System::setErrorLog( ErrorLog* errorLog )
{
	System::systemInstance->errorLogInstance_ = errorLog;
}

void System::print( String text, ... )
{
	text = StringUtils::convertFormatString( text );

	va_list args;
	va_start( args, text );
	int charRequired = 1024;
	VCFChar* tmpChar = new VCFChar[charRequired];
	memset( tmpChar, 0, charRequired );

#ifdef VCF_GCC
  #ifdef VCF_OSX

    CFMutableStringRef fmt = CFStringCreateMutable( NULL, 0 );

	CFStringAppendCharacters( fmt, text.c_str(), text.size() );

    CFStringRef res = CFStringCreateWithFormatAndArguments( NULL, NULL, fmt, args );

    int length = minVal<uint32>( charRequired-1, CFStringGetLength( res ) );

    CFRange range = {0, length };
    CFStringGetCharacters( res, range, tmpChar );

    CFShow( res );

    CFRelease( res );
    CFRelease( fmt );

  #else
	vswprintf( tmpChar, charRequired, text.c_str(), args );
  #endif
#else
	_vsnwprintf( tmpChar, charRequired, text.c_str(), args );
#endif

	va_end( args );

  #ifndef VCF_OSX
    wprintf( tmpChar );
  #endif

	if ( NULL != System::systemInstance ) {
		if ( (NULL != System::systemInstance->errorLogInstance_) && (charRequired>0) ) {
			String tmp(tmpChar);
			System::systemInstance->errorLogInstance_->toLog( tmp );
		}
	}

	delete [] tmpChar;
}

void System::println(String text, ...)
{
	text = StringUtils::convertFormatString( text );

	va_list args;
	va_start( args, text );
	int charRequired = 1024;
	VCFChar* tmpChar = new VCFChar[charRequired];
	memset( tmpChar, 0, charRequired );

#ifdef VCF_GCC
  #ifdef VCF_OSX

    CFMutableStringRef fmt = CFStringCreateMutable( NULL, 0 );

	CFStringAppendCharacters( fmt, text.c_str(), text.size() );

    CFStringRef res = CFStringCreateWithFormatAndArguments( NULL, NULL, fmt, args );

    int length = minVal<uint32>( charRequired-1, CFStringGetLength( res ) );

    CFRange range = {0, length };
    CFStringGetCharacters( res, range, tmpChar );

    CFShow( res );
    CFShow( CFSTR( "\n" ) );

    CFRelease( res );
    CFRelease( fmt );
  #else
	vswprintf( tmpChar, charRequired, text.c_str(), args );
  #endif
#else
	_vsnwprintf( tmpChar, charRequired, text.c_str(), args );
#endif

	va_end( args );

  #ifndef VCF_OSX
    wprintf( tmpChar );
    wprintf( L"\n" );
  #endif

	if ( NULL != System::systemInstance ) {
		if ( (NULL != System::systemInstance->errorLogInstance_) && (charRequired>0) ) {
			String tmp(tmpChar);
			System::systemInstance->errorLogInstance_->toLog( tmp );
		}
	}
	delete [] tmpChar;
}

void System::errorPrint( BasicException* exception )
{
	System::print( L"Exception occured ! Error string: %s\n", exception->getMessage().c_str() );
}

bool System::doesFileExist( const String& fileName )
{
	return System::systemInstance->systemPeer_->doesFileExist( fileName );
}

String System::getEnvironmentVariable( const String& variableName )
{
	return System::systemInstance->systemPeer_->getEnvironmentVariable( variableName );
}

void System::setEnvironmentVariable( const String& variableName, const String& newValue )
{
	System::systemInstance->systemPeer_->setEnvironmentVariable( variableName, newValue );
}

void System::addPathDirectory( const String& directory )
{
	System::systemInstance->systemPeer_->addPathDirectory( directory );
}

String System::getCurrentWorkingDirectory()
{
	return System::systemInstance->systemPeer_->getCurrentWorkingDirectory();
}

void System::setCurrentWorkingDirectory( const String& currentDirectory )
{
	System::systemInstance->systemPeer_->setCurrentWorkingDirectory( currentDirectory );
}

void System::setDateToSystemTime( DateTime* date )
{
	System::systemInstance->systemPeer_->setDateToSystemTime( date );
}

void System::setDateToLocalTime( DateTime* date )
{
	System::systemInstance->systemPeer_->setDateToLocalTime( date );
}

void System::setCurrentThreadLocale( Locale* locale )
{
	System::systemInstance->locale_->getPeer()->setLocale( locale->getLanguageCodeString(), locale->getCountryCodeString(), L"" );

	System::systemInstance->systemPeer_->setCurrentThreadLocale( locale );
}

Locale* System::getCurrentThreadLocale()
{
	System::systemInstance->locale_->getPeer()->setLocale( L"", L"", L"" ); //updates it to current thread's locale info

	return System::systemInstance->locale_;
}

bool System::isUnicodeEnabled()
{
	return System::systemInstance->unicodeEnabled_;
}

DateTime System::convertUTCTimeToLocalTime( const DateTime& date )
{
	return System::systemInstance->systemPeer_->convertUTCTimeToLocalTime( date );
}

DateTime System::convertLocalTimeToUTCTime( const DateTime& date )
{
	return System::systemInstance->systemPeer_->convertLocalTimeToUTCTime( date );
}

ResourceBundle* System::getResourceBundle()
{
	return System::systemInstance->resBundle_;
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
	ProgramInfo* result = NULL;

	result = System::systemInstance->systemPeer_->getProgramInfoFromFileName( fileName );

	if ( NULL == result ) {
		bool found = false;
			
		String infoFilename = System::getInfoFileFromFileName( fileName );
		
		if ( !infoFilename.empty() ) {
			String name;
			String programFileName;
			String author;
			String copyright;
			String company;
			String description;
			String programVersion;
			String fileVersion;				
			
			XMLParser xmlParser;
			FileInputStream fs(infoFilename);
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
							programFileName = programVersion = val->getCDATA();
							StringUtils::trimWhiteSpaces( programFileName );
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
							author = val->getCDATA();
							StringUtils::trimWhiteSpaces( author );
						}
						else if ( cdata == "Description" ) {
							description = val->getCDATA();
							StringUtils::trimWhiteSpaces( description );
						}
						else if ( cdata == "Executable" ) {
							programFileName = val->getCDATA();
							StringUtils::trimWhiteSpaces( programFileName );
						}
					}
				}
				
				result = new ProgramInfo( name, programFileName, author, copyright, company, description, programVersion, fileVersion );
			}
		}		
	}
	return result;
}

void System::internal_replaceResourceBundleInstance( ResourceBundle* newInstance )
{
	if ( NULL != System::systemInstance->resBundle_ ) {
		delete System::systemInstance->resBundle_;
		System::systemInstance->resBundle_ = NULL;
	}
	System::systemInstance->resBundle_ = newInstance;
}

String System::getOSName()
{
	return System::systemInstance->systemPeer_->getOSName();
}

String System::getOSVersion()
{
	return System::systemInstance->systemPeer_->getOSVersion();
}


String System::getCompiler()
{
	String result(VCF_COMPILER_NAME);
	return result;
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
	info->free();

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

	info->free();

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

/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.4  2004/12/22 03:26:14  marcelloptr
*fixed bug in getBundlePathFromExecutableName() coming from the fact
*that GetModuleFileNameW gives a lowercase path under vc70, but not under vc6
*
*Revision 1.3.2.3  2004/12/19 07:09:20  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3.2.2  2004/12/19 04:05:01  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3.2.1  2004/12/11 17:49:59  ddiego
*added 2 new projects that are command line tools. One is for
*creating the basic shell for app bundles, the other is for filling in, or
*updating an info.plist (or info.xml) file.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.6  2004/09/17 18:40:39  ddiego
*fixed bug in system getProgramInfoFromFileName - good catch marcello.
*
*Revision 1.2.2.5  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.2.2.4  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2.2.3  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.2.2.2  2004/08/26 04:29:28  ddiego
*added support for getting the resource directory to the System class.
*
*Revision 1.2.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.11  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.10  2004/07/14 14:40:47  marcelloptr
*Unicode prefix in front of strings
*
*Revision 1.1.2.9  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.7  2004/05/18 02:07:32  ddiego
*fixed a bug in StringUtils format and trace  - from osx side
*
*Revision 1.1.2.6  2004/05/16 02:39:09  ddiego
*OSX code updates
*
*Revision 1.1.2.5  2004/05/03 03:44:53  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.4  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.3  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.17.2.1  2004/04/21 02:17:27  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.17  2004/04/03 15:48:50  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.15.4.4  2004/03/29 15:22:00  ddiego
*some minor fixes
*
*Revision 1.15.4.3  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.15.4.2  2004/02/15 20:24:02  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.15.4.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.15  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.14.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.14  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.3  2003/05/15 03:01:03  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.13.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:12:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.2.2  2003/01/05 03:23:55  cesarmello
*added method: System::println
*
*Revision 1.12.2.1  2002/12/27 23:04:57  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.11.4.1  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.11  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.10.6.1  2002/07/14 05:40:02  ddiego
**** empty log message ***
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


