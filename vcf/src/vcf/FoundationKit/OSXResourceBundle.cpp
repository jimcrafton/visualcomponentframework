
#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/OSXResourceBundle.h"


using namespace VCF;


OSXResourceBundle::OSXResourceBundle()
{
}


OSXResourceBundle::~OSXResourceBundle()
{
}

CFBundleRef OSXResourceBundle::getBundle()
{
	return CFBundleGetMainBundle();
}

OSHandleID OSXResourceBundle::getHandleID()
{
	return (OSHandleID)getBundle();
}

String OSXResourceBundle::getString( const String& resourceName )
{
	CFTextString result;
	CFRefObject<CFBundleRef> bundle = getBundle();
	
	if ( NULL != bundle ) {
		CFTextString bundleName;
		bundleName = (CFStringRef) CFBundleGetValueForInfoDictionaryKey( bundle, kCFBundleNameKey );
		CFTextString resName;
		resName = resourceName;
		result = CFCopyLocalizedStringFromTableInBundle( resName, bundleName, bundle, NULL );
	}		
		
	return result;
}

String OSXResourceBundle::getVFF( const String& resourceName )
{
	String result;
	
	CFRefObject<CFBundleRef> bundle = getBundle();
	
	if ( NULL != bundle ) {
		String tmpResName = resourceName;
		FilePath fp = resourceName;
		String ext = fp.getExtension();
		
		if ( !ext.empty() ){
			tmpResName = fp.getBaseName();
			size_t pos = ext.find(".");
			if ( pos != String::npos ) {
				ext.erase( pos, 1 );
			}
		}
		else {
			ext = "vff";
		} 
	
		CFTextString resName(tmpResName);
		CFTextString resType(ext);		
		
		
		CFURLRef resURL = CFBundleCopyResourceURL( bundle, resName, resType, NULL );
		
		fp = OSXStringUtils::extractStringValueFromCFType( resURL );
		String fName = FilePath::transformToNative( fp );
		
		FILE* f = fopen( fName.ansi_c_str(), "r" );
		if ( NULL != f ) {
			fseek( f, 0, SEEK_END );
			int sz = ftell(f);
			fseek(f, 0, SEEK_SET );
			char* buf = new char[sz];
			fread( buf, sizeof(unsigned char), sz, f );			
			
			result.assign( buf, sz );
						
			delete [] buf;
		}   
	}
	
	return result;
}

Resource* OSXResourceBundle::getResource( const String& resourceName )
{
	Resource* result = NULL;	
	
	CFRefObject<CFBundleRef> bundle = getBundle();
	
	if ( NULL != bundle ) {
		String tmpResName = resourceName;
		FilePath fp = resourceName;
		String ext = fp.getExtension();
		if ( !ext.empty() ){
			tmpResName = fp.getBaseName();
			size_t pos = ext.find(".");
			if ( pos != String::npos ) {
				ext.erase( pos, 1 );
			}
		}
	
		CFTextString resName(tmpResName);
		CFTextString resType(ext);
		
		CFURLRef resURL = CFBundleCopyResourceURL( bundle, resName, resType, NULL );
		
		fp = OSXStringUtils::extractStringValueFromCFType( resURL );
		String fName = FilePath::transformToNative( fp );
		
		FILE* f = fopen( fName.ansi_c_str(), "r" );
		if ( NULL != f ) {
			fseek( f, 0, SEEK_END );
			int sz = ftell(f);
			fseek(f, 0, SEEK_SET );
			unsigned char* buf = new unsigned char[sz];
			fread( buf, sizeof(unsigned char), sz, f );
			
			result = new Resource( buf, sz, resourceName );
			
			delete [] buf;
		}   
	}
	
	
	if ( result == NULL ) {
		//if we got this far then look for files!

		String localeName = System::getCurrentThreadLocale()->getName();
		
		String fileName = System::findResourceDirectory() +	resourceName;
		
		if ( File::exists( fileName ) ) {
			FileInputStream fs(fileName);
			ulong32 size = fs.getSize();
			char* buf = new char[size];
			fs.read( (unsigned char*)buf, size );
			
			
			result = new Resource( buf, size, resourceName );
			delete [] buf;
		}
	}
	
	return result;
}

ProgramInfo* OSXResourceBundle::getProgramInfo( const String& fileName )
{
	CFTextString bundleName(fileName);
	CFRefObject<CFURLRef> url = CFURLCreateWithString( NULL, bundleName, NULL );
	CFRefObject<CFBundleRef> bundle = CFBundleCreate( NULL, url );
	
	return OSXResourceBundle::getProgramInfo( bundle );
}

ProgramInfo* OSXResourceBundle::getProgramInfo( CFBundleRef bundle )
{
	ProgramInfo* result = NULL;
	
	CFRefObject<CFBundleRef> theBundle = bundle;
	
	if ( NULL != theBundle ) {
	
		CFRefObject<CFDictionaryRef> infoDict  = CFBundleGetLocalInfoDictionary( theBundle );
		
		if ( NULL != infoDict ) {
			String name;
			String programFileName;
			String author;
			String copyright;
			String company;
			String description;
			String programVersion;
			String fileVersion;
			String helpDirectory;
			String helpName;		
			
			name = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleName") ) );
			
			programFileName = OSXStringUtils::extractStringValueFromCFType( 
											CFBundleCopyExecutableURL( bundle ) );
											
			author = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleName") ) );
											
			copyright = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleGetInfoString") ) );
			
			company = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleName") ) );
											
			description = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleGetInfoString") ) );
			
			programVersion = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleShortVersionString") ) );
			
			fileVersion = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("CFBundleVersion") ) );
											
			
											
			if ( author.empty() ) {
				author = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("Author") ) );
			}
			
			if ( copyright.empty() ) {
				copyright = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("Copyright") ) );
			}
			
			if ( description.empty() ) {
				description = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("Description") ) );
			}
			
			if ( company.empty() ) {
				company = OSXStringUtils::extractStringValueFromCFType( 
											CFDictionaryGetValue( infoDict, CFSTR("Company") ) );
			}
																											
			result = new ProgramInfo( name, programFileName, author, copyright, company, description, programVersion, fileVersion, helpDirectory, helpName );
		}		
	}
	
	return result;
}


ProgramInfo* OSXResourceBundle::getProgramInfo()
{   
	CFRefObject<CFBundleRef> bundle = getBundle();
	
	return OSXResourceBundle::getProgramInfo( bundle );
}
		
		
		