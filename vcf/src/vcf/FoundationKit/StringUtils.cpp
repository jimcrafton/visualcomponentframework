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

using namespace VCF;

String StringUtils::weekdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
String StringUtils::abbrevWeekdays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
String StringUtils::months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
String StringUtils::abbrevMonths[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };



/*
void StringUtils::traceWithArgs( String text, ... )
{
	text = StringUtils::convertFormatString( text );

//#ifdef _DEBUG
	va_list argList;

	va_start( argList, text );     // Initialize variable arguments.

	VCFChar* buf = new VCFChar[MAX_TRACE_STRING];
	memset( buf, 0, MAX_TRACE_STRING*sizeof(VCFChar) );

#if defined(VCF_GCC) || defined(VCF_CW)
    #ifdef VCF_OSX
    CFMutableStringRef fmt = CFStringCreateMutable( NULL, 0 );

	CFStringAppendCharacters( fmt, text.c_str(), text.size() );

    CFStringRef res = CFStringCreateWithFormatAndArguments( NULL, NULL, fmt, argList );

    int length = minVal<uint32>( MAX_TRACE_STRING-1, CFStringGetLength( res ) );

    CFRange range = {0, length };
    CFStringGetCharacters( res, range, buf );
    CFRelease( res );
    CFRelease( fmt );

    #else
      vswprintf( buf, MAX_TRACE_STRING, text.c_str(), argList );
    #endif
#else
	_vsnwprintf( buf, MAX_TRACE_STRING, text.c_str(), argList );
#endif

	va_end( argList );              // Reset variable arguments.

	//StringUtils::trace( String("WARNING: Using deprecated function!!! - StringUtils::traceWithArgs(...)\n") ); // MP-
	StringUtils::trace( String(buf) );

	delete [] buf;
//#endif
}
*/
void StringUtils::traceWithArgs( const Format& formatter )
{
	StringUtils::trace( formatter );
}

void StringUtils::trace( const String& text )
{
#ifdef _DEBUG

#ifdef WIN32
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

#if defined(VCF_MSC) || defined(VCF_BCC)
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
	for (int n=0; n<text.size(); n++)
	{
		copyText[n] = std::towlower(copyText[n]);
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
#if defined(VCF_MSC) || defined(VCF_BCC)
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
	for (int n=0; n<text.size(); n++)
	{
		copyText[n] = std::towupper(copyText[n]);
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

#elif defined(WIN32)
	int cmpRes = CSTR_EQUAL;
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

VCF::String StringUtils::toString( const VCF::ulong32& value )
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

VCF::String StringUtils::toString( const VCF::long64& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s;
	// if ( 0 != valHi )
	// s = CFStringCreateWithFormat( NULL, NULL, CFSTR( "%ld%ld" ), value.hi(), value.lo() );
	// would be a wrong implementation
	s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_ULONG_CONVERSION ), value.lo() );
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
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_ULONG_CONVERSION, (int)value.lo() );
	#else
		swprintf( tmp, L"%I64d", (__int64)value );
	#endif
	return String( tmp );
#endif
}

VCF::String StringUtils::toString( const VCF::ulong64& value )
{
#ifdef VCF_OSX
	CFTextString cfTmp;
	CFStringRef s;
	// if ( 0 != valHi )
	// s = CFStringCreateWithFormat( NULL, NULL, CFSTR( "%lu%lu" ), value.hi(), value.lo() );
	// would be a wrong implementation
	s = CFStringCreateWithFormat( NULL, NULL, CFSTR( STR_ULONG_CONVERSION ), value.lo() );
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
		swprintf( tmp, sizeof(tmp)/sizeof(VCFChar)-1, W_STR_ULONG_CONVERSION, (int)value.lo() );
	#else
		swprintf( tmp, L"%I64u", (unsigned __int64)value );
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
#ifdef WIN32
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


VCF::String StringUtils::format( const Format& formatter )
{
	return formatter;
}
/*
VCF::String StringUtils::format( VCF::String formatText, ... )
{
	//StringUtils::trace( String("WARNING: Using deprecated function!!! - StringUtils::format(...)\n") ); // MP-

	VCF::String result = "";


	formatText = StringUtils::convertFormatString( formatText );

	va_list argList;

	va_start( argList, formatText );     // Initialize variable arguments.

	VCFChar* buf = new VCFChar[MAX_TRACE_STRING];
	memset( buf, 0, MAX_TRACE_STRING*sizeof(VCFChar) );

#ifdef VCF_OSX
	CFMutableStringRef fmt = CFStringCreateMutable( NULL, 0 );

	CFStringAppendCharacters( fmt, formatText.c_str(), formatText.size() );

	CFStringRef res = CFStringCreateWithFormatAndArguments( NULL, NULL, fmt, argList );

	int length = minVal<uint32>( MAX_TRACE_STRING-1, CFStringGetLength( res ) );

	CFRange range = {0, length };
	CFStringGetCharacters( res, range, buf );
	CFRelease( res );
	CFRelease( fmt );

#elif defined(VCF_POSIX) || defined(VCF_CW_W32)
	vswprintf( buf, MAX_TRACE_STRING, formatText.c_str(), argList );
#else
	_vsnwprintf( buf, MAX_TRACE_STRING, formatText.c_str(), argList );
#endif

	va_end( argList );              // Reset variable arguments.

	result = buf;

	delete [] buf;

	return result;
}
*/

VCF::String StringUtils::toString( const std::type_info& typeInfo )
{
#if defined(WIN32) && !defined(VCF_MINGW)
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
#if defined(VCF_WIN32) && !defined(VCF_MINGW) //don't know if we really need this here
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
			result = _wtoi( value.c_str() );
			if ( 0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), W_STR_INT_CONVERSION, &result ) ) ) {
				throw BasicException( L"Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), W_STR_INT_CONVERSION, &result );
			if ( ret != 1 ) {
				throw BasicException( L"Unable to convert: " + value );
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
	uint32 result = 0;
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
		#ifdef _MSC_VER
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

VCF::ulong32 StringUtils::fromStringAsULong( const VCF::String& value )
{
	uint32 result = 0;
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

VCF::long64 StringUtils::fromStringAsLong64( const VCF::String& value )
{
	long64 result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		/*if ( result == 0 ) {
			//check_true_error( tmp );
		} 
		else */
		if ( (INT_MIN == (int)result) || (INT_MAX == (int)result) ) {
			throw BasicException( L"StringUtils::fromStringAsLong64() Overflow - Unable to convert: " + value );
		}
	#else
		#ifdef VCF_MSC
			result = _wtoi64( value.c_str() );
			if ( (long64)0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), L"%I64d", &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsLong64() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), L"%I64d", &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsLong64() Unable to convert: " + value );
			}
		#endif
	#endif
	return result;
}

VCF::ulong64 StringUtils::fromStringAsULong64( const VCF::String& value )
{
	ulong64 result = 0;
	#ifdef VCF_OSX
		CFTextString tmp;
		tmp = value;
		result = CFStringGetIntValue( tmp );
		if ( 0 == (int)result ) {
			//check_true_error( tmp );
		} else if ( (INT_MIN == (int)result) || (INT_MAX == (int)result) ) {
			throw BasicException( L"StringUtils::fromStringAsULong64() Overflow - Unable to convert: " + value );
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
			if ( (ulong64)0 == result && ( value[0] != '0' ) &&
					( -1 != swscanf( value.c_str(), L"%I64u", &result ) ) ) {
				throw BasicException( L"StringUtils::fromStringAsULong64() Unable to convert: " + value );
			}
		#else
			int ret = swscanf( value.c_str(), L"%I64u", &result );
			if ( ret != 1 ) {
				throw BasicException( L"StringUtils::fromStringAsULong64() Unable to convert: " + value );
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

	return result;
}


VCF::String StringUtils::format( const DateTime& date, const String& formatting )
{
	String result;

	const VCFChar* p = formatting.c_str();
	const VCFChar* start = p;
	const VCFChar* current = p;
	int size = formatting.size();
	int pos = 0;
	unsigned long  y = date.getYear();
	unsigned long m = date.getMonth();
	unsigned long d = date.getDay();

	VCFChar tmp[256];
	int tmpLen = sizeof(tmp)/sizeof(VCFChar);
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

					result += L"{insert Locale date/time here}";

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

					result += L"{Locale's AM/PM indicator}";

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

					result += L"{Locale's Date}";

					current = p + 1;
					hashCharFound = false;
					formatArgCount = 1;
				}
				break;

				//	%X - Time representation for current locale
				case 'X' : {
					result.append( current, (p-current) -formatArgCount );

					result += L"{Locale's Time}";

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

	}

	return result;
}





/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.16  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.4.2.15  2006/01/22 17:19:37  ddiego
*fixed some bugs in type_info handling for gcc.
*
*Revision 1.4.2.14  2006/01/22 14:24:12  ddiego
*updated to add case insens str compare.
*
*Revision 1.4.2.13  2006/01/22 05:50:09  ddiego
*added case insensitive string compare to string utils class.
*
*Revision 1.4.2.12  2006/01/20 20:04:26  dougtinkham
*demangle typeinfo names for MinGW
*
*Revision 1.4.2.11  2005/12/04 20:58:32  ddiego
*more osx impl work. foundationkit is mostly complete now.
*
*Revision 1.4.2.10  2005/12/01 01:33:14  obirsoy
*add back the borland fixes.
*
*Revision 1.4.2.9  2005/12/01 01:13:00  obirsoy
*More linux improvements.
*
*Revision 1.4.2.7  2005/11/10 04:43:27  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.4.2.6  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.4.2.5  2005/11/04 17:56:17  ddiego
*fixed bugs in some win32 code to better handle unicode - ansi functionality.
*
*Revision 1.4.2.4  2005/08/01 19:57:01  marcelloptr
*minor fixes or additions
*
*Revision 1.4.2.2  2005/07/30 16:52:57  iamfraggle
*Provide (temporary) CW implementations of lowerCase and upperCase and made trimLeft use standard variable declaration
*
*Revision 1.4.2.1  2005/07/24 02:30:26  ddiego
*fixed bug in retreiving program info.
*
*Revision 1.4  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.10  2005/06/25 21:49:06  marcelloptr
*fixes on trimLeft and fromStringAsHexNumber
*
*Revision 1.3.2.9  2005/04/18 12:41:29  dougtinkham
*changes for DMC
*
*Revision 1.3.2.8  2005/04/18 04:26:25  dougtinkham
*change for DMC, on swprintf calls
*
*Revision 1.3.2.7  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.3.2.6  2005/04/13 02:50:45  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.3.2.5  2005/04/11 17:07:12  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.3.2.4  2005/03/15 01:51:51  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.3  2005/03/14 05:44:51  ddiego
*added the Formatter class as part of the process of getting rid of the var arg methods in System and StringUtils.
*
*Revision 1.3.2.2  2005/03/14 04:17:24  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3.2.1  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.7  2004/11/17 04:52:49  ddiego
*added some minor fixes to win32 resource loading, and added 2 new examples that demonstrate basic resource loading and basic usage of dialogs.
*
*Revision 1.2.2.6  2004/10/23 12:20:00  marcelloptr
*bugfix [1048400] menus are now merged regardless of their shortcut key
*
*Revision 1.2.2.5  2004/09/18 16:37:10  marcelloptr
*changed implementation of fromStringAsDouble as it was crashing on vc6. Thanks Jim for pointing it out. Improved fromStringAsULong64
*
*Revision 1.2.2.4  2004/09/17 21:03:02  marcelloptr
*fromStringAs... function made 5-10 times faster in debug mode with Win32 MS VC CRT while checking for validity
*
*Revision 1.2.2.2  2004/08/31 08:50:52  marcelloptr
*minor fix string <--> signed long64 conversion
*
*Revision 1.2.2.1  2004/08/26 04:05:47  marcelloptr
*minor change on name of getMillisecond
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.19  2004/08/03 20:57:22  marcelloptr
*minor change on name DateTime:getSecond DateTime:getMillisecond
*
*Revision 1.1.2.18  2004/08/02 14:27:05  kiklop74
*Minor fix in functions lowercase and uppercase that prevented them to
*work under Borland C++
*
*Revision 1.1.2.17  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.16  2004/07/26 03:40:31  ddiego
*minor changes
*
*Revision 1.1.2.15  2004/07/26 03:30:39  marcelloptr
*minor fix string to double conversion
*
*Revision 1.1.2.14  2004/07/26 00:47:38  marcelloptr
*added conversions String <-> long64
*
*Revision 1.1.2.13  2004/07/21 02:06:53  marcelloptr
*BugFix 985136 cast to (int) and ulong64 and other conversion issues
*The fromStringAs... functions now throw an exception in case of some errors
*
*Revision 1.1.2.12  2004/07/05 01:01:51  marcelloptr
*added ulong64 ctor, operators and toString conversion
*
*Revision 1.1.2.11  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.9  2004/05/31 19:42:52  ddiego
*more osx updates
*
*Revision 1.1.2.8  2004/05/31 13:20:57  ddiego
*more osx updates
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
*Revision 1.19.2.1  2004/04/21 02:17:27  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.19  2004/04/03 15:48:49  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.17.2.5  2004/03/29 15:22:00  ddiego
*some minor fixes
*
*Revision 1.17.2.4  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.17.2.3  2004/02/21 03:27:10  ddiego
*updates for OSX porting
*
*Revision 1.17.2.2  2004/01/17 18:47:31  ddiego
*added a new example for DateTime calss and some other minor fixes to it
*
*Revision 1.17.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.17  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.4.3  2003/11/10 01:57:43  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.16.4.2  2003/08/20 22:55:20  ddiego
*got rid of some older methods for StringUtils, should be using the FilePath
*class instead
*
*Revision 1.16.4.1  2003/08/11 19:58:54  marcelloptr
*improvement: StringUtils::trimWhiteSpaces functions added
*
*Revision 1.16  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.2  2003/03/23 04:06:34  marcelloptr
*minor fixes
*
*Revision 1.15.2.1  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.12.2  2003/01/08 03:49:21  ddiego
*fixes to ensure that move and size events get sent properly. Not sure
*I am happy with how it is currently working. Fix to X11Cursor so that the cursorID
*has a valid initial value.
*
*Revision 1.14.12.1  2002/12/28 21:51:20  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.14  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.13  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.12.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.12  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


