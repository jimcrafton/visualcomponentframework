//Win32ResourceBundle.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/Win32ResourceBundle.h"


using namespace VCF;





#define RT_RCDATA_W           MAKEINTRESOURCEW(10)
#define RT_RCDATA_A           MAKEINTRESOURCEA(10)



Win32ResourceBundle::Win32ResourceBundle():
	foundResName_(false)
{
	
}

Win32ResourceBundle::~Win32ResourceBundle()
{
	
}

String Win32ResourceBundle::getString( const String& resourceName )
{
	/**
	Assume an exe resource by default?
	*/

	bool failedToFindRes = true;
	HINSTANCE hinst = getResourceInstance();
	String result;
	HRSRC resHandle = NULL;
	if ( System::isUnicodeEnabled() ) {
		resHandle = ::FindResourceW( hinst, resourceName.c_str(), RT_RCDATA_W );
	}
	else {
		resHandle = ::FindResourceA( hinst, resourceName.ansi_c_str(), RT_RCDATA_A );
	}

	if ( NULL != resHandle ){
		HGLOBAL	data = ::LoadResource( hinst, resHandle );
		if ( NULL != data ){
			TCHAR* strData = (TCHAR*)::LockResource( data );
			result = strData;
			failedToFindRes = false;
			::FreeResource( data );
		}
	}
	else {		
		//try and see if the resourceName is an int id and find it via 
		//throw exception- resource not found !!!!
		uint32 stringID = 0;
		try {
			stringID = StringUtils::fromStringAsUInt(resourceName);
		}
		catch( ... ) {
			result = L"";
		}


		if ( stringID > 0 ) {
			if ( System::isUnicodeEnabled() ) {
				wchar_t tmp[256];
				int ret = ::LoadStringW( hinst, stringID, tmp, 255 );
				if ( ret ) {
					tmp[ret] = 0;
					result = tmp;
					failedToFindRes = false;
				}				
			}
			else {
				char tmp[256];
				int ret = ::LoadStringA( hinst, stringID, tmp, 255 );
				if ( ret ) {
					tmp[ret] = 0;
					result = tmp;
					failedToFindRes = false;
				}
			}			
		}
		else {
			failedToFindRes = true;
		}

	}


	if ( failedToFindRes ) {
		//look in the resource .strings file 
		
		result = System::getCurrentThreadLocale()->translate( resourceName );		
	}

	return result;
}

String Win32ResourceBundle::getVFF( const String& resourceName )
{
	String result;
	bool failedToFindRes = true;

	HRSRC resHandle = NULL;
	if ( System::isUnicodeEnabled() ) {
		resHandle = ::FindResourceW( getResourceInstance(), resourceName.c_str(), L"VFF" );
	}
	else {
		resHandle = ::FindResourceA( getResourceInstance(), resourceName.ansi_c_str(), "VFF" );
	}

	if ( NULL != resHandle ){
		HGLOBAL	data = ::LoadResource( NULL, resHandle );
		if ( NULL != data ){
			void* dataPtr = ::LockResource( data );
			TCHAR* strData = (TCHAR*)dataPtr;
			int size = SizeofResource( getResourceInstance(), resHandle );
			result = strData;
			int resSize = result.size();
			void *tmp = dataPtr;
			/**
			*this is here to properly skip over '\0' characters in the stream
			*/
			while ( resSize < size ){
				tmp = (void*)((char*)dataPtr + resSize + 1);
				strData = (TCHAR*)tmp;
				result += "\n";
				result += strData;
				resSize = result.size();
				failedToFindRes = false;
			}
			::FreeResource( data );
		}
	}
	else {
		//throw exception- resource not found !!!!
	}


	if ( failedToFindRes ) {
		//try res directory

		String localeName = System::getCurrentThreadLocale()->getName();

		bool fileExists = false;
		String vffFile = System::findResourceDirectory() + resourceName;

		if ( File::exists( vffFile ) ) {
			fileExists = true;
		}
		else {
			vffFile += ".vff";
			if ( File::exists( vffFile ) ) {
				fileExists = true;
			}
		}

		if ( fileExists ) {
			FileInputStream fs(vffFile);

			fs >> result;
		}
	}

	return result;
}


Resource* Win32ResourceBundle::getResource( const String& resourceName )
{
	Resource* result = NULL;

	bool failedToFindRes = true;

	foundResName_ = false;
	foundResType_ = "\0";

	searchResName_ = resourceName;
	/**
	JC
	we are using the ansi version as there isn't 
	a wide string verion of the ENUMRESTYPEPROC
	in the base version of the SDK headers that 
	come with vc6.
	The problem is that both the EnumResourceTypesA and 
	EnumResourceTypeW functions are defined to take the 
	same ENUMRESTYPEPROC, where in later version's of the 
	SDK header the EnumResourceTypesA uses a ENUMRESTYPEPROCA
	function pointer, and the EnumResourceTypesW uses a 
	ENUMRESTYPEPROCW argument.
	*/
	::EnumResourceTypesA( getResourceInstance(),
							 Win32ResourceBundle::EnumResTypeProcA,
							 (LPARAM)this );
	
	if ( true == foundResName_ ){
		HRSRC resHandle = NULL;

		
		resHandle = ::FindResourceA( getResourceInstance(),
			                              resourceName.ansi_c_str(),
										  foundResType_ );
		

		if ( NULL != resHandle ){
			HGLOBAL	dataHandle = ::LoadResource( NULL, resHandle );
			if ( NULL != dataHandle ){
				void* data = ::LockResource( dataHandle );
				int size = ::SizeofResource( getResourceInstance(), resHandle );				
				return new Resource( data, size, resourceName );
			}
		}
		else {
			//throw exception- resource not found !!!!
		}
	}

	//if we got this far then look for files!

	String localeName = System::getCurrentThreadLocale()->getName();
	
	bool fileExists = false;
	String fileName = System::findResourceDirectory() +	resourceName;
	
	if ( File::exists( fileName ) ) {
		FileInputStream fs(fileName);
		ulong32 size = fs.getSize();
		char* buf = new char[size];
		fs.read( buf, size );
		

		result = new Resource( buf, size, resourceName );
		delete [] buf;
	}

	return result;
}



BOOL CALLBACK Win32ResourceBundle::EnumResTypeProcA( HMODULE hModule, char* lpszType, LPARAM lParam )
{
	if ( (RT_CURSOR == lpszType) || (RT_ICON == lpszType) || (RT_BITMAP == lpszType) || (RT_STRING == lpszType) || (RT_VERSION == lpszType) || (RT_VXD == lpszType) ) {
		return TRUE;
	}
	return ::EnumResourceNamesA( hModule,
		                        lpszType,
								Win32ResourceBundle::EnumResNameProcA,
								lParam );
}



BOOL CALLBACK Win32ResourceBundle::EnumResNameProcA( HMODULE hModule, const char* lpszType, char* lpszName, LPARAM lParam )
{
	BOOL result = TRUE;
	Win32ResourceBundle* thisPtr = (Win32ResourceBundle*)lParam;

	
	
	if ( StringUtils::lowerCase(thisPtr->searchResName_) == StringUtils::lowerCase(lpszName) ) {
		thisPtr->foundResName_ = true;
		thisPtr->foundResType_ = lpszType;
		result = FALSE;
	}
	return result;
}

HINSTANCE Win32ResourceBundle::getResourceInstance()
{
	HINSTANCE result = ::GetModuleHandle(NULL);
	
	
	return result;
}




/*

 * Copyright (c) 2002 by Ted Peck <tpeck@roundwave.com>
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * THIS CODE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED. IN PARTICULAR, NO WARRANTY IS MADE
 * THAT THE CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGING. IN NO EVENT WILL THE AUTHOR BE LIABLE FOR ANY COSTS OR DAMAGES 
 * ARISING FROM ANY USE OF THIS CODE. NO USE OF THIS CODE IS AUTHORIZED EXCEPT UNDER
 * THIS DISCLAIMER.
 *
 * Use at your own risk!

 JC - Modified this for use in the VCF.
*/

template <typename CharType >
struct VCF_VS_VERSIONINFO { 
  WORD  wLength; 
  WORD  wValueLength; 
  WORD  wType; 
  CharType szKey[1]; 
  WORD  Padding1[1]; 
  VS_FIXEDFILEINFO Value; 
  WORD  Padding2[1]; 
  WORD  Children[1]; 
};
typedef VCF_VS_VERSIONINFO<VCF::WideChar> VS_VERSIONINFO_W;
typedef VCF_VS_VERSIONINFO<char> VS_VERSIONINFO_A;

template <typename CharType >
struct VCF_String { 
  WORD   wLength; 
  WORD   wValueLength; 
  WORD   wType; 
  CharType  szKey[1]; 
  WORD   Padding[1]; 
  WORD   Value[1]; 
}; 

typedef VCF_String<VCF::WideChar> String_W;
typedef VCF_String<char> String_A;

template <typename CharType >
struct VCF_StringTable { 
  WORD   wLength; 
  WORD   wValueLength; 
  WORD   wType; 
  CharType  szKey[1]; 
  WORD   Padding[1]; 
  VCF_String<CharType> Children[1]; 
};
typedef VCF_StringTable<VCF::WideChar> StringTable_W;
typedef VCF_StringTable<char> StringTable_A;

template <typename CharType >
struct VCF_StringFileInfo { 
  WORD        wLength; 
  WORD        wValueLength; 
  WORD        wType; 
  CharType       szKey[1]; 
  WORD        Padding[1]; 
  VCF_StringTable<CharType> Children[1]; 
};
typedef VCF_StringFileInfo<VCF::WideChar> StringFileInfo_W;
typedef VCF_StringFileInfo<char> StringFileInfo_A;

template <typename CharType >
struct VCF_Var { 
  WORD  wLength; 
  WORD  wValueLength; 
  WORD  wType; 
  CharType szKey[1]; 
  WORD  Padding[1]; 
  DWORD Value[1]; 
}; 
typedef VCF_Var<VCF::WideChar> Var_W;
typedef VCF_Var<char> Var_A;

template <typename CharType >
struct VCF_VarFileInfo { 
  WORD  wLength; 
  WORD  wValueLength; 
  WORD  wType; 
  CharType szKey[1]; 
  WORD  Padding[1]; 
  VCF_Var<CharType>  Children[1]; 
}; 
typedef VCF_VarFileInfo<VCF::WideChar> VarFileInfo_W;
typedef VCF_VarFileInfo<char> VarFileInfo_A;


typedef std::multimap<String,String> VersionMap;





#define VS_ROUNDOFFS(a,b,r)	(((byte*)(b) - (byte*)(a) + ((r)-1)) & ~((r)-1))
#define VS_ROUNDPOS(b, a, r)	(((byte*)(a))+VS_ROUNDOFFS(a,b,r))

void getVersionInfoW( VersionMap& map, const String& fileName )
{
	VCF::WideChar fileNameW[MAX_PATH];
	int sz = minVal<int>( MAX_PATH,fileName.size() );

	fileName.copy( fileNameW,sz );
	fileNameW[sz] = 0;

	DWORD dummy;
	DWORD size = GetFileVersionInfoSizeW( fileNameW, &dummy);

	if ( 0 == size ) {
		return;
	}

	unsigned char* buf = new unsigned char[size];
	memset(buf, 0, size);

	

	if ( !GetFileVersionInfoW(fileNameW, 0, size, buf) ) {
		delete [] buf;
		return;
	}

	VS_VERSIONINFO_W* versionInfo = (VS_VERSIONINFO_W*)buf;

	String key = versionInfo->szKey;

	
	VCF_ASSERT( key == L"VS_VERSION_INFO");


	BYTE* node = (BYTE*) &versionInfo->szKey[wcslen(versionInfo->szKey)+1];
	VS_FIXEDFILEINFO* fixedFileInfo = (VS_FIXEDFILEINFO*) VS_ROUNDPOS(node, versionInfo, 4);

	if (versionInfo->wValueLength) {
		//showFIXEDFILEINFO(fixedFileInfo);	// Show the 'Value' element
	}

	std::pair<String,String> entry;

	
	// Iterate over the 'Children' elements of VS_VERSIONINFO (either StringFileInfo or VarFileInfo)
	StringFileInfo_W* strFileInfo = (StringFileInfo_W*) VS_ROUNDPOS(((byte*)fixedFileInfo) + versionInfo->wValueLength, fixedFileInfo, 4);
	for ( ; ((byte*) strFileInfo) < (((byte*) versionInfo) + versionInfo->wLength); strFileInfo = (StringFileInfo_W*)VS_ROUNDPOS((((byte*) strFileInfo) + strFileInfo->wLength), strFileInfo, 4)) { // StringFileInfo_W / VarFileInfo
		if (!wcscmp(strFileInfo->szKey, L"StringFileInfo")) {
			// The current child is a StringFileInfo element
			VCF_ASSERT(1 == strFileInfo->wType);
			VCF_ASSERT(!strFileInfo->wValueLength);
			// Iterate through the StringTable elements of StringFileInfo
			StringTable_W* strTable = (StringTable_W*) VS_ROUNDPOS(&strFileInfo->szKey[wcslen(strFileInfo->szKey)+1], strFileInfo, 4);
			for ( ; ((byte*) strTable) < (((byte*) strFileInfo) + strFileInfo->wLength); strTable = (StringTable_W*)VS_ROUNDPOS((((byte*) strTable) + strTable->wLength), strTable, 4)) {
				
				entry.first = String(L"LangID");
				entry.second = strTable->szKey;
				map.insert( entry );



				VCF_ASSERT(!strTable->wValueLength);
				// Iterate through the String elements of StringTable_W
				String_W* strElement = (String_W*) VS_ROUNDPOS(&strTable->szKey[wcslen(strTable->szKey)+1], strTable, 4);
				for ( ; ((byte*) strElement) < (((byte*) strTable) + strTable->wLength); strElement = (String_W*) VS_ROUNDPOS((((byte*) strElement) + strElement->wLength), strElement, 4)) {
					wchar_t* strValue = (wchar_t*) VS_ROUNDPOS(&strElement->szKey[wcslen(strElement->szKey)+1], strElement, 4);
					//printf("  %-18S: %.*S\n", strElement->szKey, strElement->wValueLength, strValue); // print <sKey> : <sValue>

					entry.first = strElement->szKey;
					entry.second.assign( strValue, strElement->wValueLength );
					map.insert( entry );
				}
			}
		}
		else {
			// The current child is a VarFileInfo element
			VCF_ASSERT(1 == strFileInfo->wType); // ?? it just seems to be this way...
			VarFileInfo_W* varFileInfo = (VarFileInfo_W*) strFileInfo;
			VCF_ASSERT(!wcscmp(varFileInfo->szKey, L"VarFileInfo"));
			VCF_ASSERT(!varFileInfo->wValueLength);
			// Iterate through the Var elements of VarFileInfo (there should be only one, but just in case...)
			Var_W* element = (Var_W*) VS_ROUNDPOS(&varFileInfo->szKey[wcslen(varFileInfo->szKey)+1], varFileInfo, 4);
			for ( ; ((byte*) element) < (((byte*) varFileInfo) + varFileInfo->wLength); element = (Var_W*)VS_ROUNDPOS((((byte*) element) + element->wLength), element, 4)) {
				
				entry.first = element->szKey;				

				// Iterate through the array of pairs of 16-bit language ID values that make up the standard 'Translation' VarFileInfo element.
				WORD* wordElement = (WORD*) VS_ROUNDPOS(&element->szKey[wcslen(element->szKey)+1], element, 4);
				for (WORD* wpos = wordElement ; ((byte*) wpos) < (((byte*) wordElement) + element->wValueLength); wpos+=2) {
					entry.second += StringUtils::format( L"%04x%04x ", (int)*wpos++, (int)(*(wpos+1)) );
				}

				map.insert( entry );
			}
		}
	}

	delete [] buf;

}



void getVersionInfoA( VersionMap& map, const String& fileName )
{
	char fileNameA[MAX_PATH];
	int sz = minVal<int>( MAX_PATH,fileName.size() );

	fileName.copy( fileNameA,sz );
	fileNameA[sz] = 0;

	DWORD dummy;
	DWORD size = GetFileVersionInfoSizeA( fileNameA, &dummy);

	if ( 0 == size ) {
		return;
	}

	unsigned char* buf = new unsigned char[size];
	memset(buf, 0, size);

	

	if ( !GetFileVersionInfoA(fileNameA, 0, size, buf) ) {
		delete [] buf;
		return;
	}

	VS_VERSIONINFO_A* versionInfo = (VS_VERSIONINFO_A*)buf;

	String key = versionInfo->szKey;

	
	VCF_ASSERT( key == L"VS_VERSION_INFO");


	BYTE* node = (BYTE*) &versionInfo->szKey[strlen(versionInfo->szKey)+1];
	VS_FIXEDFILEINFO* fixedFileInfo = (VS_FIXEDFILEINFO*) VS_ROUNDPOS(node, versionInfo, 4);

	if (versionInfo->wValueLength) {
		//showFIXEDFILEINFO(fixedFileInfo);	// Show the 'Value' element
	}

	std::pair<String,String> entry;

	
	// Iterate over the 'Children' elements of VS_VERSIONINFO (either StringFileInfo or VarFileInfo)
	StringFileInfo_A* strFileInfo = (StringFileInfo_A*) VS_ROUNDPOS(((byte*)fixedFileInfo) + versionInfo->wValueLength, fixedFileInfo, 4);
	for ( ; ((byte*) strFileInfo) < (((byte*) versionInfo) + versionInfo->wLength); strFileInfo = (StringFileInfo_A*)VS_ROUNDPOS((((byte*) strFileInfo) + strFileInfo->wLength), strFileInfo, 4)) { // StringFileInfo_A / VarFileInfo
		if (!strcmp(strFileInfo->szKey, "StringFileInfo")) {
			// The current child is a StringFileInfo element
			VCF_ASSERT(1 == strFileInfo->wType);
			VCF_ASSERT(!strFileInfo->wValueLength);
			// Iterate through the StringTable elements of StringFileInfo
			StringTable_A* strTable = (StringTable_A*) VS_ROUNDPOS(&strFileInfo->szKey[strlen(strFileInfo->szKey)+1], strFileInfo, 4);
			for ( ; ((byte*) strTable) < (((byte*) strFileInfo) + strFileInfo->wLength); strTable = (StringTable_A*)VS_ROUNDPOS((((byte*) strTable) + strTable->wLength), strTable, 4)) {
				
				entry.first = String(L"LangID");
				entry.second = strTable->szKey;
				map.insert( entry );



				VCF_ASSERT(!strTable->wValueLength);
				// Iterate through the String elements of StringTable_W
				String_A* strElement = (String_A*) VS_ROUNDPOS(&strTable->szKey[strlen(strTable->szKey)+1], strTable, 4);
				for ( ; ((byte*) strElement) < (((byte*) strTable) + strTable->wLength); strElement = (String_A*) VS_ROUNDPOS((((byte*) strElement) + strElement->wLength), strElement, 4)) {
					char* strValue = (char*) VS_ROUNDPOS(&strElement->szKey[strlen(strElement->szKey)+1], strElement, 4);
					
					entry.first = strElement->szKey;
					entry.second.assign( strValue, strElement->wValueLength );
					map.insert( entry );
				}
			}
		}
		else {
			// The current child is a VarFileInfo element
			VCF_ASSERT(1 == strFileInfo->wType); // ?? it just seems to be this way...
			VarFileInfo_A* varFileInfo = (VarFileInfo_A*) strFileInfo;
			VCF_ASSERT(!strcmp(varFileInfo->szKey, "VarFileInfo"));
			VCF_ASSERT(!varFileInfo->wValueLength);
			// Iterate through the Var elements of VarFileInfo (there should be only one, but just in case...)
			Var_A* element = (Var_A*) VS_ROUNDPOS(&varFileInfo->szKey[strlen(varFileInfo->szKey)+1], varFileInfo, 4);
			for ( ; ((byte*) element) < (((byte*) varFileInfo) + varFileInfo->wLength); element = (Var_A*)VS_ROUNDPOS((((byte*) element) + element->wLength), element, 4)) {
				
				entry.first = element->szKey;				

				// Iterate through the array of pairs of 16-bit language ID values that make up the standard 'Translation' VarFileInfo element.
				WORD* wordElement = (WORD*) VS_ROUNDPOS(&element->szKey[strlen(element->szKey)+1], element, 4);
				for (WORD* wpos = wordElement ; ((byte*) wpos) < (((byte*) wordElement) + element->wValueLength); wpos+=2) {
					entry.second += StringUtils::format( L"%04x%04x ", (int)*wpos++, (int)(*(wpos+1)) );
				}

				map.insert( entry );
			}
		}
	}

	delete [] buf;

}


class FindVersionInfoVal {
public:
	FindVersionInfoVal( const String& value ): value_(StringUtils::lowerCase( value )){};

	bool operator() ( const std::pair<String,String>& x ) const {
		String x1 = StringUtils::lowerCase( x.first );
		int pos = x1.find( value_ );
		return pos != String::npos;
	}

	String value_;
};

ProgramInfo* Win32ResourceBundle::getProgramInfoFromFileName( const String& fileName )
{
	ProgramInfo* result = NULL;

	VersionMap map;

	if ( System::isUnicodeEnabled() ) {
		getVersionInfoW( map, fileName );
	}		
	else {
		getVersionInfoA( map, fileName );
	}

	if ( !map.empty() ) {
		String name;
		String programFileName;
		String author;
		String copyright;
		String company;
		String description;
		String programVersion;
		String fileVersion;
	
		VersionMap::iterator found =  std::find_if( map.begin(), map.end(), FindVersionInfoVal("Author") );
		if ( found != map.end() ) {
			author = found->second;
		}

		found = std::find_if( map.begin(), map.end(), FindVersionInfoVal("ProductName") );
		if ( found != map.end() ) {
			name = found->second;
		}

		found = std::find_if( map.begin(), map.end(), FindVersionInfoVal("copyright") );
		if ( found != map.end() ) {
			copyright = found->second;
		}

		found = std::find_if( map.begin(), map.end(), FindVersionInfoVal("ProductVersion") );
		if ( found != map.end() ) {
			fileVersion = found->second;
		}

		found = std::find_if( map.begin(), map.end(), FindVersionInfoVal("Company") );
		if ( found != map.end() ) {
			company = found->second;
		}

		found = std::find_if( map.begin(), map.end(), FindVersionInfoVal("Comments") );
		if ( found != map.end() ) {
			description = found->second;
		}

		found = std::find_if( map.begin(), map.end(), FindVersionInfoVal("FileVersion") );
		if ( found != map.end() ) {
			programVersion = found->second;
		}
		
		programFileName = fileName;


		result = new ProgramInfo( name, programFileName, author, copyright, company, description, programVersion, fileVersion );
	}

	return result;
}


ProgramInfo* Win32ResourceBundle::getProgramInfo()
{
	String fileName;

	if ( System::isUnicodeEnabled() ) {
		VCF::WideChar tmp[MAX_PATH];		
		::GetModuleFileNameW( getResourceInstance(), tmp, MAX_PATH );
		fileName = tmp;		
	}		
	else {
		char tmp[MAX_PATH];
		::GetModuleFileNameA( getResourceInstance(), tmp, MAX_PATH );
		fileName = tmp;		
	}

	return Win32ResourceBundle::getProgramInfoFromFileName(fileName);
}



/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.9  2004/11/21 00:19:11  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.1.2.8  2004/11/17 19:02:55  ddiego
*fixed compiler error in Win32ResourceBundle::getResource() method.
*
*Revision 1.1.2.7  2004/11/17 04:52:49  ddiego
*added some minor fixes to win32 resource loading, and added 2 new examples that demonstrate basic resource loading and basic usage of dialogs.
*
*Revision 1.1.2.6  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.1.2.5  2004/09/16 03:26:26  ddiego
*fixed it so we can now get program information from a resource bundle. This can be embedded in the exe like in windows, or read from an external file a la OS X info.plist xml files.
*
*Revision 1.1.2.4  2004/09/15 21:14:28  ddiego
*added support for getting program info from resource bundle.
*
*Revision 1.1.2.3  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.1.2.2  2004/08/26 04:29:28  ddiego
*added support for getting the resource directory to the System class.
*
*Revision 1.1.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.16.8.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.16  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.1  2003/03/12 03:12:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.13.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.13  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


