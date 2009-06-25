//StringUtils.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/DateTime.h"

#if defined(VCF_OSX) || defined(VCF_MINGW)
    #include <cxxabi.h>  //add this so we can demangle the GCC typeinfo names
#endif

#ifdef VCF_POSIX
    #include <cxxabi.h>  //add this so we can demangle the GCC typeinfo names
	#include <uuid/uuid.h>
#endif




#define TO_STRING_TXT_SIZE		50

namespace VCF {

String StringUtils::weekdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
String StringUtils::abbrevWeekdays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
String StringUtils::months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
String StringUtils::abbrevMonths[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };



void StringUtils::trace( const String& text )
{
#ifdef _DEBUG

#ifdef VCF_WIN
	VCFWin32::Win32Utils::trace( text );
#else
  #ifdef VCF_OSX
    CFTextString tmp;
    tmp = text;
    CFShow( tmp );
  #else
    wprintf( text.c_str() );
  #endif
#endif

#endif
}

String StringUtils::trimLeft( const String& text, const char& c )
{
	String result = text;

	unsigned int n=0;

	for (; n<result.length(); ++n) {
		if (result[n] != c) {
			break;
		}
	}
	result.erase(0,n);

	return result;
}

String StringUtils::trimRight( const String& text, const char& c )
{
	String result = text;

	for (int n=result.length()-1; 0<=n; --n) {
		if (result[n] != c) {
			break;
		}
		result.erase(n,1);
	}

	return result;
}

String StringUtils::trim( const String& text, const char& c )
{
	String result;
	result = trimLeft(text, c);
	result = trimRight(result, c);
	return result;
}

void StringUtils::trimWhiteSpacesLeft( String& text )
{
	for (unsigned int n=0; n<text.length(); ++n) {
		if (text[0] == ' ' || text[0] == '\t'|| text[0] == '\r'|| text[0] == '\n' ) {
			text.erase(0,1);
		} else {
			break;
		}
	}
}

void StringUtils::trimWhiteSpacesRight( String& text )
{
	for (int n=text.length()-1; 0<=n; --n) {
		if (text[n] == ' ' || text[n] == '\t' || text[n] == '\r' || text[n] == '\n' ) {
			//text[n]=0;			// error: this doesn't update text.size()
			text.erase(n,1);
		} else {
			break;
		}
	}
}

void StringUtils::trimWhiteSpaces( String& text )
{
	trimWhiteSpacesLeft(text);
	trimWhiteSpacesRight(text);
}

String StringUtils::eraseLeftOfChar( const String& s, const VCFChar& ch, const bool& included/*=false*/, const int& count/*=1*/ )
{
	String str = s;
	String::size_type pos;

	int cnt = count;
	if ( cnt < 0 ) {
		pos = s.rfind( ch );
		while ( ++cnt != 0 ) {
			pos = s.find( ch, pos );
		}
	} else {
		pos = s.find( ch );
		while ( --cnt != 0 ) {
			pos = s.find( ch, pos );
		}
	}

	if ( String::npos != pos ) {
		if ( included ) {
			str.erase( 0, pos + 1 );
		} else {
			str.erase( 0, pos );
		}
	}

	return str;
}

String StringUtils::eraseRightOfChar( const String& s, const VCFChar& ch, const bool& included/*=false*/, const int& count/*=1*/ )
{
	String str = s;
	String::size_type pos;

	int cnt = count;
	if ( cnt < 0 ) {
		pos = s.rfind( ch );
		while ( ++cnt != 0 ) {
			pos = s.find( ch, pos );
		}
	} else {
		pos = s.find( ch );
		while ( --cnt != 0 ) {
			pos = s.find( ch, pos );
		}
	}

	if ( String::npos != pos ) {
		if ( included ) {
			str.erase( pos, str.size() - pos );
		} else {
			str.erase( pos + 1, str.size() - pos - 1 );
		}
	}

	return str;
}

String StringUtils::lowerCase( const String& text )
{
	String result;

#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
	VCFChar* copyText = new VCFChar[text.size()+1];
	memset(copyText, 0, (text.size()+1)*sizeof(VCFChar) );
	text.copy( copyText, text.size() );
	_wcslwr( copyText ); // not in ANSI standard library

	result = copyText;
	delete [] copyText;

#elif defined(VCF_CW_W32) || defined(VCF_GCC)
	VCFChar* copyText = new VCFChar[text.size()+1];
	memset(copyText, 0, (text.size()+1)*sizeof(VCFChar) );
	text.copy( copyText, text.size() );
	for (int n=0; n<(int)text.size(); n++)
	{
#ifdef VCF_MINGW
		copyText[n] = towlower(copyText[n]);
#else
		copyText[n] = std::towlower(copyText[n]);
#endif
	}

	result = copyText;
	delete [] copyText;

#elif VCF_OSX
	CFTextString tmp;
	tmp = text;
	tmp.lowerCase();

	result = tmp;
#endif
	return result;
}

String StringUtils::upperCase( const VCF::String& text )
{
	String result;
#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
	VCFChar* copyText = new VCFChar[text.size()+1];
	memset(copyText, 0, (text.size()+1)*sizeof(VCFChar) );
	text.copy( copyText, text.size() );
	_wcsupr( copyText );

	result = copyText;
	delete [] copyText;

#elif defined(VCF_CW_W32) || defined(VCF_GCC)
	VCFChar* copyText = new VCFChar[text.size()+1];
	memset(copyText, 0, (text.size()+1)*sizeof(VCFChar) );
	text.copy( copyText, text.size() );
	for (int n=0; n<(int)text.size(); n++)
	{
#ifdef VCF_MINGW
		copyText[n] = towupper(copyText[n]);
#else
		copyText[n] = std::towupper(copyText[n]);
#endif
	}

	result = copyText;
	delete [] copyText;

#elif VCF_OSX
	CFTextString tmp;
	tmp = text;
	tmp.upperCase();
	result = tmp;
#endif
	return result;
}

int StringUtils::noCaseCompare( const VCF::String& str1, const VCF::String& str2 )
{
	int result = 0;
#if defined(VCF_OSX)
	CFTextString tmp1(str1);
	CFTextString tmp2(str2);
	CFComparisonResult cmpRes = CFStringCompare( tmp1, tmp2, kCFCompareCaseInsensitive );
	switch ( cmpRes ) {
		case kCFCompareLessThan : {
			result = -1;
		}
		break;

		case kCFCompareEqualTo : {
			result = 0;
		}
		break;

		case kCFCompareGreaterThan : {
			result = 1;
		}
		break;
	}

#elif defined(VCF_WIN)
	int cmpRes = CSTR_EQUAL;

	#ifndef VCF_WIN32CE
	if ( System::isUnicodeEnabled() ) {
		cmpRes = ::CompareStringW( GetThreadLocale(), NORM_IGNORECASE, str1.c_str(), str1.size(), str2.c_str(), str2.size() );

	}
	else {
		AnsiString tmp1 = str1;
		AnsiString tmp2 = str2;

		cmpRes = ::CompareStringA( GetThreadLocale(), NORM_IGNORECASE, tmp1.c_str(), tmp1.size(), tmp2.c_str(), tmp2.size() );
	}
	switch ( cmpRes ) {
		case CSTR_LESS_THAN : {
			result = -1;
		}
		break;

		case CSTR_EQUAL : {
			result = 0;
		}
		break;

		case CSTR_GREATER_THAN : {
			result = 1;
		}
		break;
	}
	#else
		cmpRes = ::CompareString( GetThreadLocale(), NORM_IGNORECASE, str1.c_str(), str1.size(), str2.c_str(), str2.size() );
	#endif

#else
	String s1 = StringUtils::upperCase(str1);
	String s2 = StringUtils::upperCase(str2);

	if ( s1 < s2 ) {
		result = -1;
	}
	else if ( s1 > s2 ) {
		result = 1;
	}
#endif
	return result;
}

VCF::String StringUtils::toStringFromHexNumber( const uchar& value )
{
	VCF::String result;
#ifdef VCF_OSX
	CFTextString cfTmp;
	cfTmp.format( CFSTR("%02X"), value );
	result = cfTmp;
#else
	VCFChar hexBytes[50];
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
	swprintf( hexBytes, sizeof(hexBytes)-1, L"%02X", value  );
#else
	swprintf( hexBytes, L"%02X", value );
	#endif
	result = hexBytes;
#endif
	return result;
}

VCF::String StringUtils::toString( const int& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_INT_CONVERSION ), value );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_INT_CONVERSION, value  );
	#else
		swprintf( tmp, W_STR_INT_CONVERSION, value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const VCF::uint32& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_UINT_CONVERSION ), value );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_UINT_CONVERSION, value  );
	#else
		swprintf( tmp, W_STR_UINT_CONVERSION, value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const long& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_LONG_CONVERSION ), value );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_LONG_CONVERSION, value  );
	#else
		swprintf( tmp, W_STR_LONG_CONVERSION, value );
	#endif
	return String( tmp );
#endif

}

VCF::String StringUtils::toString( const unsigned long& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_ULONG_CONVERSION ), value );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_ULONG_CONVERSION, value  );
	#else
		swprintf( tmp, W_STR_ULONG_CONVERSION, value );
	#endif
	return String( tmp );
#endif

}

VCF::String StringUtils::toString( const VCF::int64& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s;
	// if ( 0 != valHi )
	// s = CFStringCreateWithFormat( NULL, NULL, CFSTR( "%ld%ld" ), value.hi(), value.lo() );
	// would be a wrong implementation
	s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_ULONG_CONVERSION ), getLo32( value ) );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		// if ( 0 != valHi )
		// swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, L"%lu%lu", value.hi(), value.lo() );
		// would be a wrong implementation
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_ULONG_CONVERSION, (int)getLo32(value) );
	#else
		swprintf( tmp, L"%I64d", (int64)value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const VCF::uint64& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s;
	// if ( 0 != valHi )
	// s = CFStringCreateWithFormat( NULL, NULL, CFSTR( "%lu%lu" ), value.hi(), value.lo() );
	// would be a wrong implementation
	s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_ULONG_CONVERSION ), getLo32( value ) );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		// if ( 0 != valHi )
		// swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, L"%lu%lu", value.hi(), value.lo() );
		// would be a wrong implementation
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_ULONG_CONVERSION, (int)getLo32(value) );
	#else
		swprintf( tmp, L"%I64u", (uint64)value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const float& value )
{

#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( "%.5f" ), value );
	cfTmp = s;
	CFRelease( s );

	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );
	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, L"%.5f", value  );
	#else
		swprintf( tmp, L"%.5f", value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const double& value )
{

#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( "%.5f" ), value );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );

	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, L"%.5f", value  );
	#else
		swprintf( tmp, L"%.5f", value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const char& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_CHAR_CONVERSION ), value );
	cfTmp = s;
	CFRelease( s );
	return String( cfTmp );
#else
	VCFChar tmp[TO_STRING_TXT_SIZE];
	memset( tmp, 0, TO_STRING_TXT_SIZE * sizeof(VCFChar) );

	#if defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_CHAR_CONVERSION, value  );
	#else
		swprintf( tmp, W_STR_CHAR_CONVERSION, value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const bool& value )
{
	return ( value == true ) ? L"true" : L"false";
}

VCF::String StringUtils::newUUID()
{
	VCF::String result = "";
#if defined(VCF_WIN)
	#ifdef VCF_WIN32CE
		GUID id;
		CoCreateGuid( &id );
		char tmp[256];
		sprintf( tmp, "%08x-%04x-%04x-%x%x-%x%x%x%x%x%x",
			id.Data1, id.Data2, id.Data3, id.Data4[0], id.Data4[1],
			id.Data4[2], id.Data4[3],
			id.Data4[4], id.Data4[5],
			id.Data4[6], id.Data4[7]);
		result = tmp;
	#else
	UUID id;

	if ( RPC_S_OK == ::UuidCreate( &id ) ){




		if ( System::isUnicodeEnabled() ) {
			WideChar* tmpid = NULL;
			RPC_STATUS rpcresult = UuidToStringW(  &id, reinterpret_cast<unsigned short**>(&tmpid) );

			if ( RPC_S_OUT_OF_MEMORY != rpcresult ) {
				result = VCF::String( tmpid );

				RpcStringFreeW( reinterpret_cast<unsigned short**>(&tmpid) );
			}
		}
		else {
			char* tmpid = NULL;
			RPC_STATUS rpcresult = UuidToStringA(  &id, (unsigned char**)&tmpid );

			if ( RPC_S_OUT_OF_MEMORY != rpcresult ) {
				result = VCF::String( tmpid );

				RpcStringFreeA( (unsigned char**)&tmpid );
			}
		}
	}
	#endif
#elif defined(VCF_OSX)
	CFUUIDRef uuidRef = CFUUIDCreate( kCFAllocatorDefault );
	CFTextString tmp;
	CFStringRef s = CFUUIDCreateString( kCFAllocatorDefault, uuidRef );
	tmp = s;
	CFRelease( s );
	result = tmp;
	CFRelease( uuidRef );
#elif defined(VCF_POSIX)
	const uint32 uuidgenLength = 36;
	char buffer[uuidgenLength+1];
	memset(buffer, '\0', sizeof(buffer));

	uuid_t uuid;
	uuid_generate(uuid);
	uuid_unparse(uuid, buffer);
	uuid_clear(uuid);
	result = buffer;

//	FILE* uuidgenFile;
//	uuidgenFile = popen("uuidgen", "r");
//	if(uuidgenFile != NULL) {
// 		int charsRead = fread(buffer, sizeof(char), uuidgenLength, uuidgenFile);
// 		if(charsRead  == uuidgenLength) {
// 			result = buffer;
// 		}
// 		else {
// 		What should we do? Throw an exception!
// 		}
// 		pclose(uuidgenFile);
// 	}
#endif
	return result;
}



VCF::String StringUtils::toString( const std::type_info& typeInfo )
{
#if defined(VCF_WIN) && !defined(VCF_MINGW)
	return StringUtils::getClassNameFromTypeInfo( typeInfo );
#elif defined(VCF_GCC)
	String result;

	int status = 0;
	char* nameBuf;
	const char* c_name = 0;

	nameBuf = abi::__cxa_demangle( typeInfo.name(), 0, 0, &status );
	c_name = nameBuf;


	if ( NULL == c_name ) {
		//try typeinfo.name() without the C++ de-mangler
		c_name = typeInfo.name();

		if ( -2 == status && (strlen(c_name) == 1) ) { //built-in type
			switch (c_name[0])
			{
				case 'v': c_name = "void"; break;
				case 'w': c_name = "wchar_t"; break;
				case 'b': c_name = "bool"; break;
				case 'c': c_name = "char"; break;
				case 'a': c_name = "signed char"; break;
				case 'h': c_name = "unsigned char"; break;
				case 's': c_name = "short"; break;
				case 't': c_name = "unsigned short"; break;
				case 'i': c_name = "int"; break;
				case 'j': c_name = "unsigned int"; break;
				case 'l': c_name = "long"; break;
				case 'm': c_name = "unsigned long"; break;
				case 'x': c_name = "long long"; break;
				case 'y': c_name = "unsigned long long"; break;
				case 'n': c_name = "__int128"; break;
				case 'o': c_name = "unsigned __int128"; break;
				case 'f': c_name = "float"; break;
				case 'd': c_name = "double"; break;
				case 'e': c_name = "long double"; break;
				case 'g': c_name = "__float128"; break;
				case 'z': c_name = "..."; break;
			}
		}
	}


	if ( NULL != c_name ) {
		result = c_name;
	}

	if ( NULL != nameBuf ) {
		::free( nameBuf );
	}
	return result;
#else
	return typeInfo.name();
#endif
}

VCF::String StringUtils::getClassNameFromTypeInfo( const std::type_info& typeInfo  )
{
	VCF::String result = "";
#if defined(VCF_WIN) && !defined(VCF_MINGW) //don't know if we really need this here
		std::string tmp = typeInfo.name();  //put back in when we find typeid
		if ( tmp != "void *" ) {//void* is a special case!
			//strip out the preceding "class" or "enum" or whatever
			std::string::size_type idx = tmp.find( "class " );
			if ( idx != tmp.npos ) {
				tmp = tmp.substr( idx+std::string("class ").size() );
			}
			else {
				idx = tmp.find( "enum " );
				if ( idx != tmp.npos ) {
					tmp = tmp.substr( idx+std::string("enum ").size() );
				}
				else {
					idx = tmp.find( "struct " );
					if ( idx != tmp.npos ) {
						tmp = tmp.substr( idx+std::string("struct ").size() );
					}
				}
			}
		}

	#ifndef KEEP_NAMESPACE_IN_CLASSNAME

		std::string::size_type idx = tmp.find( "::" );
		if ( idx == tmp.npos ) {
			result = tmp;  // not part of a namespace
		} else {
			result = tmp.substr( idx + 2 );  // strip namespace off from string
		}

	#else

		result = tmp;

	#endif

#elif defined(VCF_OSX) || defined(VCF_MINGW) || defined(VCF_POSIX)
	int status = 0;
	char* nameBuf;
	const char* c_name = 0;

	nameBuf = abi::__cxa_demangle( typeInfo.name(), 0, 0, &status );
	c_name = nameBuf;


	if ( NULL == c_name ) {
		//try typeinfo.name() without the C++ de-mangler
		c_name = typeInfo.name();

		if ( -2 == status && (strlen(c_name) == 1) ) { //built-in type
			switch (c_name[0])
			{
				case 'v': c_name = "void"; break;
				case 'w': c_name = "wchar_t"; break;
				case 'b': c_name = "bool"; break;
				case 'c': c_name = "char"; break;
				case 'a': c_name = "signed char"; break;
				case 'h': c_name = "unsigned char"; break;
				case 's': c_name = "short"; break;
				case 't': c_name = "unsigned short"; break;
				case 'i': c_name = "int"; break;
				case 'j': c_name = "unsigned int"; break;
				case 'l': c_name = "long"; break;
				case 'm': c_name = "unsigned long"; break;
				case 'x': c_name = "long long"; break;
				case 'y': c_name = "unsigned long long"; break;
				case 'n': c_name = "__int128"; break;
				case 'o': c_name = "unsigned __int128"; break;
				case 'f': c_name = "float"; break;
				case 'd': c_name = "double"; break;
				case 'e': c_name = "long double"; break;
				case 'g': c_name = "__float128"; break;
				case 'z': c_name = "..."; break;
			}
		}
	}


	if ( NULL != c_name ) {
		result = c_name;
	}

	if ( NULL != nameBuf ) {
		::free( nameBuf );
	}
#else
	result = typeInfo.name();
#endif

	return result;
}

#ifdef VCF_OSX
// routine to check if it is a real error
// if your Mac code is brocken, please fix this !
// What about using sscanf ?
/*
void check_true_error( const VCF::String& value )
{
	if ( 0 == value ) {
		bool error = false;
		int len = value.size();
		if ( 0 == len ) {
			error = true;
		} else {
			VCFChar c = value[0];
			if ( CFSTR( "0" ) != c ) {
				if ( CFSTR( "+" ) == c || CFSTR( "-" ) == c ) {
					if ( CFSTR( "0" ) != value[1] ) {
						error = true;
					}
				} else {
					error = true;
				}
			}
		}
		if ( error ) {
			throw BasicException( L"Unable to convert: " + value );
		}
	}
}
*/
#endif

int StringUtils::fromStringAsHexNumber( const VCF::String& value )
{
	int result = 0;

	String::size_type size = value.size();

#ifdef VCF_OSX
		// is the string beginning with "0x" ?
		const UnicodeString::AnsiChar* p = value.ansi_c_str();
		if ( 2 < size ) {
			if ( ( '0' == p[0] ) && ( 'x' == p[1] ) ) {
				p += 2;
			}
		}
		int ret = sscanf( p, "%X", &result );
		if ( ret != 1 ) {
			throw BasicException( L"Unable to convert: " + value );
		}
	#else
		// is the string beginning with "0x" ?
		const UnicodeString::UniChar* p = value.c_str();
		if ( 2 < size ) {
			if ( ( '0' == p[0] ) && ( 'x' == p[1] ) ) {
				p += 2;
			}
		}
		int ret = swscanf( p, L"%X", &result );
		if ( ret != 1 ) {
			throw BasicException( L"Unable to convert: " + value );
		}
	#endif
	return result;
}

int StringUtils::fromStringAsInt( const VCF::String& value )
{
	int result = 0;
	#ifdef VCF_OSX

		CFTextString tmp;
		tmp = value;

		result = CFStringGetIntValue( tmp );
		if ( 0 == result ) {
			//check_true_error( tmp );
		} else if ( INT_MIN == result || INT_MAX == result ) {
			throw BasicException( L"Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			if ( value.empty() ) {
				throw BasicException( L"Unable to convert empty string" );
			}

			result = _wtoi( value.c_str() );
			if ( 0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), W_STR_INT_CONVERSION, &result ) ) ) {
				throw BasicException( L"Unable to convert: {" + value + L"}" );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_INT_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"Unable to convert: {" + value + L"}" );
			}
		#endif
	#endif
	return result;
}

VCF::uint32 StringUtils::fromStringAsUInt( const VCF::String& value )
{
	uint32 result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		if ( 0 == result ) {
			//check_true_error( tmp );
		} else if ( INT_MIN == result || INT_MAX == result ) {
			throw BasicException( L"StringUtils::fromStringAsUInt() Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			/* unfortunately there is no _wtoui function provided so we use _wtoi64 to avoid overflow */
			result = _wtoi64( value.c_str() );
			if ( 0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), W_STR_UINT_CONVERSION, &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsUInt() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_UINT_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsUInt() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

long StringUtils::fromStringAsLong( const VCF::String& value )
{
	long result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		if ( 0 == result ) {
			//check_true_error( tmp );
		} else if ( INT_MIN == result || INT_MAX == result ) {
			throw BasicException( L"StringUtils::fromStringAsLong() Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			result = _wtol( value.c_str() );
			if ( 0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), W_STR_LONG_CONVERSION, &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsLong() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_LONG_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsLong() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

unsigned long StringUtils::fromStringAsULong( const VCF::String& value )
{
	unsigned long result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		if ( 0 == result ) {
			//check_true_error( tmp );
		} else if ( INT_MIN == result || INT_MAX == result ) {
			throw BasicException( L"StringUtils::fromStringAsULong() Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			result = _wtoi64( value.c_str() );
			if ( 0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), W_STR_ULONG_CONVERSION, &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsULong() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_ULONG_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsULong() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

VCF::int64 StringUtils::fromStringAsInt64( const VCF::String& value )
{
	int64 result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		/*if ( result == 0 ) {
			//check_true_error( tmp );
		}
		else */
		if ( (INT_MIN == (int)result) || (INT_MAX == (int)result) ) {
			throw BasicException( L"StringUtils::fromStringAsInt64() Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			result = _wtoi64( value.c_str() );
			if ( (int64)0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), L"%I64d", &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsInt64() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), L"%I64d", &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsInt64() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

VCF::uint64 StringUtils::fromStringAsUInt64( const VCF::String& value )
{
	uint64 result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		if ( 0 == (int)result ) {
			//check_true_error( tmp );
		} else if ( (INT_MIN == (int)result) || (INT_MAX == (int)result) ) {
			throw BasicException( L"StringUtils::fromStringAsUInt64() Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			#if ( _MSC_VER >= 1300 )
				result = _wcstoui64( value.c_str(), NULL, 10 );
			#else
				/* we risk overflow, but that's the best we can do
				if reported problems we need to use swscanf */
				result = _wtoi64( value.c_str() );
			#endif
			if ( (uint64)0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), L"%I64u", &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsUInt64() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), L"%I64u", &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsUInt64() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

float StringUtils::fromStringAsFloat( const VCF::String& value )
{
	float result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = (float)CFStringGetDoubleValue( tmp );
		if ( 0.0 == result ) {
			//check_true_error( tmp );
		}
	#elif defined VCF_WIN32CE
		result = atof( value.ansi_c_str() );
	#else
		#if ( defined VCF_MSC ) && ( _MSC_VER >= 1300 )
			result = _wtof( value.c_str() );
			if ( 0 == result && ( value[0] != '0' && value[0] != '.' ) &&
					( -1 != swscanf( value.c_str(), W_STR_FLOAT_CONVERSION, &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsFloat() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_FLOAT_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsFloat() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

double StringUtils::fromStringAsDouble( const VCF::String& value )
{
	double result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetDoubleValue( tmp );
		if ( 0.0 == result ) {
			//check_true_error( tmp );
		}
	#elif defined VCF_WIN32CE
		result = atof( value.ansi_c_str() );
	#else
		#if ( defined VCF_MSC ) && ( _MSC_VER >= 1300 )
			result = _wtof( value.c_str() );
			if ( 0 == result && ( value[0] != '0' && value[0] != '.' ) &&
					( -1 != swscanf( value.c_str(), W_STR_DOUBLE_CONVERSION, &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsDouble() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_DOUBLE_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsDouble() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

char StringUtils::fromStringAsChar( const VCF::String& value )
{
	char result = 0;
	#ifdef VCF_OSX
		sscanf( value.ansi_c_str(), STR_CHAR_CONVERSION, &result );
	#else
		int ret = swscanf( value.c_str(), W_STR_CHAR_CONVERSION, &result );
		if ( ret != 1 ) {
			throw BasicException( L"StringUtils::fromStringAsChar() Unable to convert: " + value );
		}
	#endif

	return result;
}

short StringUtils::fromStringAsShort( const VCF::String& value )
{
	int result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
	#else
		#ifdef VCF_MSC
			result = _wtoi( value.c_str() );
			if ( 0 == result && ( value[0] != '0' && value[0] != '.' ) &&
					( -1 != swscanf( value.c_str(), W_STR_SHORT_CONVERSION, &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsShort() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_SHORT_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsShort() Unable to convert: " + value );
			}
		#endif
	#endif
	return (short)result;
}

bool StringUtils::fromStringAsBool( const VCF::String& value )
{
	bool result = false;
	if ( value == W_STR_BOOL_CONVERSION_TRUE ){
		result = true;
	}
	else if ( value == W_STR_BOOL_CONVERSION_FALSE ){
		result = false;
	}
	else {
		throw BasicException( L"StringUtils::fromStringAsBool() Unable to convert: " + value );
	}

	return result;
}


VCF::String StringUtils::format( const DateTime& date, const String& formatting, Locale* locale )
{
	String result;

	const VCFChar* p = formatting.c_str();
	const VCFChar* start = p;
	const VCFChar* current = p;
	int size = formatting.size();
	uint32 y = date.getYear();
	uint32 m = date.getMonth();
	uint32 d = date.getDay();

#ifdef VCF_OSX
    int tmpLen = 256;
#endif

	VCFChar tmp[256];
	memset( tmp, 0, sizeof(tmp) );

	bool hashCharFound = false;
	int formatArgCount = 1;

	while ( (p-start) < size ) {
		if ( ('%' == *p) || (hashCharFound) ) {

			p++;

			switch ( *p ) {
				case '#' : {
					hashCharFound = true;
					formatArgCount = 2;
					p --;
				}
				break;

				//	%% - Percent sign
				case '%' : {
					result.append( current, (p-current) -formatArgCount );
					result += "%";

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%a - Abbreviated weekday name
				case 'a' : {
					result.append( current, (p-current) -formatArgCount );

					result += StringUtils::abbrevWeekdays[date.getWeekDay()];

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%A - Full weekday name
				case 'A' : {
					result.append( current, (p-current) -formatArgCount );

					result += StringUtils::weekdays[date.getWeekDay()];

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%b - Abbreviated month name
				case 'b' : {
					result.append( current, (p-current) -formatArgCount );

					result += StringUtils::abbrevMonths[m-1];

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%B - Full month name
				case 'B' : {
					result.append( current, (p-current) -formatArgCount );

					result += StringUtils::months[m-1];

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%c - Date and time representation appropriate for locale
				case 'c' : {
					result.append( current, (p-current) -formatArgCount );

					//result += L"{insert Locale date/time here}";

					if ( NULL != locale ) {
						result += locale->toStringFromDate( date ) + " " + locale->toStringFromTime( date );
					}

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%d - Day of month as decimal number (01  31)
				case 'd' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), d );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[ minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, sizeof(tmp)-1, L"%d", d );
						#else
							swprintf( tmp, L"%d", d );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), d );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[ minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", d );
						#else
							swprintf( tmp, L"%02d", d );
						#endif

					}

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%D or %j - Day of year as decimal number (001  366)
				case 'D' : case 'j' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), date.getDayOfYear() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[ minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", date.getDayOfYear() );
						#else
							swprintf( tmp, L"%d", date.getDayOfYear() );
						#endif
							result += tmp;

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%03d"), date.getDayOfYear() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%03d", date.getDayOfYear()  );
						#else
							swprintf( tmp, L"%03d", date.getDayOfYear()  );
						#endif
						result += tmp;

					}

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;

				}
				break;

				//	%H - Hour in 24-hour format (00  23)
				case 'H' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), date.getHour() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", date.getHour() );
						#else
							swprintf( tmp, L"%d", date.getHour() );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), date.getHour() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", date.getHour() );
						#else
							swprintf( tmp, L"%02d", date.getHour() );
						#endif

					}

					result += tmp;
					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%I - Hour in 12-hour format (01  12)
				case 'I' : {
					result.append( current, (p-current) -formatArgCount );

					int h = date.getHour() % 12;
					if ( h == 0 ) {
						h = 12;
					}
					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), h );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[ minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", h );
						#else
							swprintf( tmp, L"%d", h );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), h );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", h );
						#else
							swprintf( tmp, L"%02d", h );
						#endif

					}

						result += tmp;

						current = p + 1;
						hashCharFound = false;
						formatArgCount = 1;
					}
				break;

				//	%m - Month as decimal number (01  12)
				case 'm' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), m );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", m  );
						#else
							swprintf( tmp, L"%d", m  );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), m );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", m  );
						#else
							swprintf( tmp, L"%02d", m  );
						#endif

					}

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%M - Minute as decimal number (00  59)
				case 'M' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), date.getMinute() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", date.getMinute()  );
						#else
							swprintf( tmp, L"%d", date.getMinute()  );
						#endif

						}
						else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), date.getMinute() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", date.getMinute()  );
						#else
							swprintf( tmp, L"%02d", date.getMinute()  );
						#endif

					}

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%P - Current locale's A.M./P.M. indicator for 12-hour clock
				case 'P' : {
					result.append( current, (p-current) -formatArgCount );

					if ( NULL != locale ) {

						if ( date.getHour() > 11 ) {
							result += locale->getPMSymbol();
						}
						else {
							result += locale->getAMSymbol();
						}
					}

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				// %s - millisecond part
				case 's' : {
					result.append( current, (p-current) -formatArgCount );

					#ifdef VCF_OSX
						CFTextString cfStr;
						cfStr.format( CFSTR("%03d"), date.getMillisecond() );
						cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
						tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
					#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
						swprintf( tmp, tmpLen-1, L"%03d", date.getMillisecond()  );
					#else
						swprintf( tmp, L"%03d", date.getMillisecond()  );
					#endif

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%S - Second as decimal number (00  59)
				case 'S' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), date.getSecond() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", date.getSecond()  );
						#else
							swprintf( tmp, L"%d", date.getSecond()  );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), date.getSecond() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", date.getSecond()  );
						#else
							swprintf( tmp, L"%02d", date.getSecond()  );
						#endif

					}


					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%U - Week of year as decimal number, with Sunday as first day of week (00  53)
				case 'U' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), date.getWeekOfYearStartingSun() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", date.getWeekOfYearStartingSun()  );
						#else
							swprintf( tmp, L"%d", date.getWeekOfYearStartingSun()  );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), date.getWeekOfYearStartingSun() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", date.getWeekOfYearStartingSun()  );
						#else
							swprintf( tmp, L"%02d", date.getWeekOfYearStartingSun()  );
						#endif

					}

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%w - Weekday as decimal number (0  6; Sunday is 0)
				case 'w' : {
					result.append( current, (p-current) -formatArgCount );

					#ifdef VCF_OSX
						CFTextString cfStr;
						cfStr.format( CFSTR("%d"), date.getWeekDay() );
						cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
						tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
					#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
						swprintf( tmp, tmpLen-1, L"%d", (int)date.getWeekDay()  );
					#else
						swprintf( tmp, L"%d", (int)date.getWeekDay()  );
					#endif

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%W - Week of year as decimal number, with Monday as first day of week (00  53)
				case 'W' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), date.getWeekOfYearStartingMon() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", date.getWeekOfYearStartingMon()  );
						#else
							swprintf( tmp, L"%d", date.getWeekOfYearStartingMon()  );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), date.getWeekOfYearStartingMon() );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", date.getWeekOfYearStartingMon()  );
						#else
							swprintf( tmp, L"%02d", date.getWeekOfYearStartingMon()  );
						#endif

					}

					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%x - Date representation for current locale
				case 'x' : {
					result.append( current, (p-current) -formatArgCount );

					if ( NULL != locale ) {
						result += locale->toStringFromDate( date );
					}

					//result += L"{Locale's Date}";

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%X - Time representation for current locale
				case 'X' : {
					result.append( current, (p-current) -formatArgCount );

					if ( NULL != locale ) {
						result += locale->toStringFromTime( date );
					}

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%y - Year without century, as decimal number (00  99)
				case 'y' : {
					result.append( current, (p-current) -formatArgCount );

					if ( hashCharFound ) {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%d"), y % 100 );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%d", y % 100  );
						#else
							swprintf( tmp, L"%d", y % 100  );
						#endif

					}
					else {

						#ifdef VCF_OSX
							CFTextString cfStr;
							cfStr.format( CFSTR("%02d"), y % 100 );
							cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
							tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
						#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
							swprintf( tmp, tmpLen-1, L"%02d", y % 100  );
						#else
							swprintf( tmp, L"%02d", y % 100  );
						#endif

					}


					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%Y - Year with century, as decimal number
				case 'Y' : {
					result.append( current, (p-current) -formatArgCount );

					#ifdef VCF_OSX
						CFTextString cfStr;
						cfStr.format( CFSTR("%04d"), y );
						cfStr.copy( tmp, minVal<uint32>(cfStr.length(),tmpLen-1) );
						tmp[minVal<uint32>(cfStr.length(),tmpLen-1) ] = 0;
					#elif defined(VCF_POSIX) || defined(VCF_CW_W32) || defined(VCF_DMC)
						swprintf( tmp, tmpLen-1, L"%04d", y  );
					#else
						swprintf( tmp, L"%04d", y  );
					#endif


					result += tmp;

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				default : {
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;
			}
		}
		p++;
	}

	if ( current < p ) {
		result.append( current, (p-current) );
	}

	return result;
}

String StringUtils::convertFormatString( const String& formattedString )
{
	#ifdef VCF_OSX
		String result = formattedString;
		String lsDirective = "%ls";

		size_t pos = result.find( lsDirective );
		while ( pos != String::npos ) {
			result.erase( pos, lsDirective.length() );
			result.insert( pos, "%s" );
			pos = result.find( lsDirective, pos + 1 );
		}

		return result;
	#else
		return formattedString;
	#endif
}

VCF::String StringUtils::toString( const VariantData& value )
{
	return value.toString();
}

VCF::String StringUtils::translateVKCodeToString( VirtualKeyCode code )
{
	VCF::String result;

	switch ( code ) {
		case vkF1: {
			result = "F1";
		}
		break;

		case vkF2: {
			result = "F2";
		}
		break;

		case vkF3: {
			result = "F3";
		}
		break;

		case vkF4: {
			result = "F4";
		}
		break;

		case vkF5: {
			result = "F5";
		}
		break;

		case vkF6: {
			result = "F6";
		}
		break;

		case vkF7: {
			result = "F7";
		}
		break;

		case vkF8: {
			result = "F8";
		}
		break;

		case vkF9: {
			result = "F9";
		}
		break;

		case vkF10: {
			result = "F10";
		}
		break;

		case vkF11: {
			result = "F11";
		}
		break;

		case vkF12: {
			result = "F12";
		}
		break;

		case vkUpArrow: {
			result = "Up";
		}
		break;

		case vkDownArrow: {
			result = "Down";
		}
		break;

		case vkLeftArrow: {
			result = "Left";
		}
		break;

		case vkRightArrow: {
			result = "Right";
		}
		break;

		case vkPgUp: {
			result = "Page Up";
		}
		break;

		case vkPgDown: {
			result = "Page Down";
		}
		break;

		case vkHome: {
			result = "Home";
		}
		break;

		case vkEnd: {
			result = "End";
		}
		break;

		case vkInsert: {
			result = "Ins";
		}
		break;

		case vkDelete: {
			result = "Del";
		}
		break;

		case vkBackSpace: {
			result = "Back";
		}
		break;

		case vkNumber0: {
			result = "0";
		}
		break;

		case vkNumber1: {
			result = "1";
		}
		break;

		case vkNumber2: {
			result = "2";
		}
		break;

		case vkNumber3: {
			result = "3";
		}
		break;

		case vkNumber4: {
			result = "4";
		}
		break;

		case vkNumber5: {
			result = "5";
		}
		break;

		case vkNumber6: {
			result = "6";
		}
		break;

		case vkNumber7: {
			result = "7";
		}
		break;

		case vkNumber8: {
			result = "8";
		}
		break;

		case vkNumber9: {
			result = "9";
		}
		break;

		case vkLetterA: {
			result = "A";
		}
		break;

		case vkLetterB: {
			result = "B";
		}
		break;

		case vkLetterC: {
			result = "C";
		}
		break;

		case vkLetterD: {
			result = "D";
		}
		break;

		case vkLetterE: {
			result = "E";
		}
		break;

		case vkLetterF: {
			result = "F";
		}
		break;

		case vkLetterG: {
			result = "G";
		}
		break;

		case vkLetterH: {
			result = "H";
		}
		break;

		case vkLetterI: {
			result = "I";
		}
		break;

		case vkLetterJ: {
			result = "J";
		}
		break;

		case vkLetterK: {
			result = "K";
		}
		break;

		case vkLetterL: {
			result = "L";
		}
		break;

		case vkLetterM: {
			result = "M";
		}
		break;

		case vkLetterN: {
			result = "N";
		}
		break;

		case vkLetterO: {
			result = "O";
		}
		break;

		case vkLetterP: {
			result = "P";
		}
		break;

		case vkLetterQ: {
			result = "Q";
		}
		break;

		case vkLetterR: {
			result = "R";
		}
		break;

		case vkLetterS: {
			result = "S";
		}
		break;

		case vkLetterT: {
			result = "T";
		}
		break;

		case vkLetterU: {
			result = "U";
		}
		break;

		case vkLetterV: {
			result = "V";
		}
		break;

		case vkLetterW: {
			result = "W";
		}
		break;

		case vkLetterX: {
			result = "X";
		}
		break;

		case vkLetterY: {
			result = "Y";
		}
		break;

		case vkLetterZ: {
			result = "Z";
		}
		break;

		case vkSpaceBar: {
			result = "Space";
		}
		break;

		case vkReturn: {
			result = "Enter";
		}
		break;

		case vkAlt: {
			result = "Alt";
		}
		break;

		case vkShift: {
			result = "Shift";
		}
		break;

		case vkCtrl: {
			result = "Ctrl";
		}
		break;

		case vkTab: {
			result = "Tab";
		}
		break;

		case vkEscape: {
			result = "Esc";
		}
		break;

		case vkLeftApostrophe: {
			result = "`";
		}
		break;
			//`
		case vkTilde: {
			result = "~";
		}
		break;
					//~
		case vkExclamation: {
			result = "!";
		}
		break;
				//!
		case vkCommercialAt: {
			result = "@";
		}
		break;
				//@
		case vkNumberSign: {
			result = "#";
		}
		break;
				//#
		case vkDollarSign: {
			result = "$";
		}
		break;
				//$
		case vkPercent: {
			result = "%";
		}
		break;
					//%
		case vkCircumflex: {
			result = "^";
		}
		break;
				//^
		case vkAmpersand: {
			result = "&";
		}
		break;
				//&
		case vkAsterix: {
			result = "*";
		}
		break;
					//*
		case vkOpenParen: {
			result = "(";
		}
		break;
				//(
		case vkCloseParen: {
			result = ")";
		}
		break;
				//)
		case vkHyphen: {
			result = "-";
		}
		break;
					//-
		case vkUnderbar: {
			result = "_";
		}
		break;
					//_
		case vkEqualsSign: {
			result = "=";
		}
		break;
				//=
		case vkPlusSign: {
			result = "+";
		}
		break;
					//+
		case vkUprightBar: {
			result = "|";
		}
		break;
				//|
		case vkBackSlash: {
			result = "\\";
		}
		break;
				/* \   */
		case vkOpenBracket: {
			result = "[";
		}
		break;
				//[
		case vkOpenBrace: {
			result = "{";
		}
		break;
				//{
		case vkCloseBracket: {
			result = "]";
		}
		break;
				//]
		case vkCloseBrace: {
			result = "}";
		}
		break;
				//}
		case vkSemiColon: {
			result = ";";
		}
		break;

		case vkColon: {
			result = ":";
		}
		break;

		case vkSingleQuote: {
			result = "'";
		}
		break;

		case vkDoubleQuote: {
			result = "\"";
		}
		break;

		case vkComma: {
			result = ",";
		}
		break;

		case vkLessThan: {
			result = "<";
		}
		break;

		case vkPeriod: {
			result = ".";
		}
		break;

		case vkGreaterThan: {
			result = ">";
		}
		break;

		case vkForwardSlash: {
			result = "/";
		}
		break;

		case vkQuestionMark: {
			result = "?";
		}
		break;

		//miscellaneous
		case vkPrintScreen: {
			result = "Print Screen";
		}
		break;

		case vkScrollLock: {
			result = "Scroll Lock";
		}
		break;

		case vkPause: {
			result = "Pause";
		}
		break;

		case vkCapsLock: {
			result = "Caps Lock";
		}
		break;

		case vkUndefined: {
			result = "Undefined";
		}
		break;
	}

	return result;
}


};

/**
$Id$
*/
