//VCFString.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/TextCodec.h"

#include <errno.h>

using namespace VCF;



int UnicodeString::adjustForBOMMarker( UnicodeString::AnsiChar*& stringPtr, uint32& len )
{
	//for now only handle UTF16 Little endian - bail on anything else!
	int result = 0;

	ulong32 bom = 0;
	if ( len > UnicodeString::UTF16BOMSize ) {
		bom  = ((stringPtr[0] << 8) | stringPtr[1]) & 0x0000FFFF;
		if ( UnicodeString::UTF16LittleEndianBOM == bom ) {
			stringPtr += UnicodeString::UTF16BOMSize; //skip over the BOM
			len -= UnicodeString::UTF16BOMSize;
			result = UnicodeString::UTF16LittleEndianBOM;
		}
		else {
			if ( UnicodeString::UTF16BigEndianBOM == bom ) {
				result = UnicodeString::UTF16BigEndianBOM;
				StringUtils::trace( "Unable to translate UTF16BigEndianBOM string\n" );
			}
			else {
				if ( len > UnicodeString::UTF8BOMSize ) {
					bom = 0;
					bom  = ((stringPtr[0] << 16) | (stringPtr[1] << 8) | stringPtr[0]) & 0x00FFFFFF;
					if ( UnicodeString::UTF8BOM == bom ) {
						result = UnicodeString::UTF8BOM;
						stringPtr += UnicodeString::UTF8BOMSize; //skip over the BOM
						len -= UnicodeString::UTF8BOMSize;
					}
					else {
						if ( len > UnicodeString::UTF8BOMSize ) {
							bom = 0;
							bom  = (stringPtr[0] << 24) | (stringPtr[1] << 16) | (stringPtr[2] << 8) | stringPtr[3];

							if ( (UnicodeString::UTF32LittleEndianBOM == bom) || 
									(UnicodeString::UTF32BigEndianBOM == bom) ) {
								StringUtils::trace( "Unable to translate UTF32 BOM string\n" );

								if ( UnicodeString::UTF32LittleEndianBOM == bom ) {
									result = UnicodeString::UTF32LittleEndianBOM;
								}
								else if ( UnicodeString::UTF32BigEndianBOM == bom ) {
									result = UnicodeString::UTF32BigEndianBOM;
								}
							}
						}
					}
				}
			}
		}
	}

	return result;
}

UnicodeString::UnicodeString(const std::string& rhs):
	ansiDataBuffer_(NULL)
{
	UnicodeString::transformAnsiToUnicode( rhs.c_str(), rhs.size(), data_ );
}

UnicodeString::UnicodeString(const UnicodeString::AnsiChar* string ):
	ansiDataBuffer_(NULL)
{
	UnicodeString::transformAnsiToUnicode( string, strlen(string), data_ );
}

UnicodeString::UnicodeString(const UnicodeString::UniChar* string ):
	data_(string),
	ansiDataBuffer_(NULL)
{

}


UnicodeString::UnicodeString(const UnicodeString::AnsiChar* string, UnicodeString::size_type stringLength ):
	ansiDataBuffer_(NULL)
{
	UnicodeString::transformAnsiToUnicode( string, stringLength, data_ );
}

UnicodeString::UnicodeString(const UnicodeString::UniChar* string, UnicodeString::size_type stringLength ):
	data_(string,stringLength),
	ansiDataBuffer_(NULL)
{
}

UnicodeString::UnicodeString( size_type n, UnicodeString::AnsiChar c ):
	data_( n, UnicodeString::transformAnsiCharToUnicodeChar(c) ),
	ansiDataBuffer_(NULL)
{

}

UnicodeString::UnicodeString( size_type n, UnicodeString::UniChar c ):
	data_(n, c),
	ansiDataBuffer_(NULL)
{

}


#ifdef VCF_OSX
UnicodeString::UnicodeString(const wchar_t* string ):
	ansiDataBuffer_(NULL)
{
	//!!!!!!!!!!!!!!!!!!MAJOR HACK ALERT!!!!!!!!!!!!!!!
	//Because *&^$%'n Apple doesn't provide wcslen we have to do this here - completely
	//*&^#$%% LAME!!!!!! :(
	int strLength = 0;
	const wchar_t* P = string;
	while ( *P != 0 ) {
		strLength ++;
		P++;

		if ( strLength >= 10000 ) { //arbitrarily stop after 10,000 characters? Lame as HELLL
			break;
		}
	}

	if ( *P == 0 ) {
		strLength ++;
	}


	int size = strLength;

	if ( !(size > 0) ) {
		throw RuntimeException( "size < 0 wcstombs() failed" );
	}

	UnicodeString::AnsiChar* tmp = new UnicodeString::AnsiChar[size+1];

	if ( wcstombs( tmp, string, strLength ) > 0 ) {
		tmp[size] = 0;
		UnicodeString::transformAnsiToUnicode( tmp, size, data_ );
	}

	delete [] tmp;
	tmp = NULL;
}
#endif


UnicodeString::~UnicodeString()
{
	if ( NULL != ansiDataBuffer_ ) {
		delete [] ansiDataBuffer_;
		ansiDataBuffer_ = NULL;
	}
}

void UnicodeString::transformAnsiToUnicode( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength, UnicodeString::StringData& newStr )
{
	if ( stringLength == 0 ) {
		newStr.erase(0,newStr.size());
	}
	else {

	#ifdef VCF_WIN32
		int size = MultiByteToWideChar( CP_ACP, 0, str, stringLength, NULL, 0 );

		if ( !(size > 0) ) {
			throw RuntimeException( L"size > 0 MultiByteToWideChar() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* tmp = new UniChar[size];


		int err = MultiByteToWideChar( CP_ACP, 0, str, stringLength, (LPWSTR)tmp, size );
		if ( 0 == err ) {
			err = GetLastError();
		}

		newStr.assign( tmp, size );

		delete [] tmp;

	#elif defined(VCF_OSX)
		CFStringRef cfStr =
		CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );

		int size = CFStringGetLength( cfStr );
		if ( !(size > 0) ) {
			throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* unicodeText = new UniChar[size+1];
		CFRange range = {0,size};
		CFStringGetCharacters(cfStr,range,unicodeText);
		unicodeText[size] = 0;
		newStr.assign( unicodeText, size );
		delete [] unicodeText;
		CFRelease( cfStr );

	#elif defined(VCF_POSIX)
		int size = mbstowcs (NULL, str, 0 );
		if ( size < 0) {
			throw RuntimeException( L"size < 0 mbstowcs() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* tmp = new UniChar[size+1];

		int err = mbstowcs( tmp, str, size );
		if ( err > 0 ) {
			newStr.assign( tmp, size );
		}

		delete [] tmp;

	#endif
	}
}

UnicodeString::UniChar UnicodeString::transformAnsiCharToUnicodeChar( UnicodeString::AnsiChar c )
{
	UnicodeString::UniChar result = 0;

#ifdef VCF_WIN32
	int err = MultiByteToWideChar( CP_ACP, 0, &c, 1, (LPWSTR)&result, 1 );

	if ( !(err > 0) ) {
		throw RuntimeException( L"size > 0 MultiByteToWideChar() failed" );
	}

#elif defined(VCF_OSX)
	char str[2] = {c,0};
	CFStringRef cfStr =
			CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );

	int size = CFStringGetLength( cfStr );
	if ( !(size > 0) ) {
		throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
	}

	UniChar unicodeText[2];
	CFRange range = {0,2};
	CFStringGetCharacters(cfStr,range,unicodeText);
	result = unicodeText[0];
	CFRelease( cfStr );

#elif defined(VCF_POSIX)
	UnicodeString::UniChar tmp[2] = {0,0};
	mbstowcs( tmp, &c, 1 );
	result = tmp[0];
#endif

	return result;
}

UnicodeString::AnsiChar UnicodeString::transformUnicodeCharToAnsiChar( UnicodeString::UniChar c )
{
	AnsiChar result;

#ifdef VCF_WIN32
	
	if (  0 == ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)&c, 1,
									&result, 1, NULL, NULL ) ) {
		result = 0;
		throw RuntimeException( L"WideCharToMultiByte() failed" );
	}


#elif defined(VCF_OSX)
	String str;
	str +=c;


	CFTextString tmp;
	tmp = str;
	CFRange r = {0,tmp.length()};
	CFIndex size2 = 0;
	CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, NULL, 0, &size2 );
	
	if ( !(size2 > 0) ) {
		throw RuntimeException( L"size <= 0 CFStringGetBytes() failed" );
	}
	
	size2 = minVal<CFIndex>( 1, size2 );
	
	
	if (  0 == ::CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false,
									(UInt8*)&result, size2, &size2 ) ) {
		//CFStringGetBytes failed
		throw RuntimeException( L"CFStringGetBytes failed" );
		result = 0;
	}
	
#elif defined(VCF_POSIX)
	int size = wctomb(NULL, c);


	if ( size < 0 ) {
		throw RuntimeException( L"size < 0 wctomb() failed" );
	}

	UnicodeString::AnsiChar* tmp = new UnicodeString::AnsiChar[size+1];

	if ( wctomb( tmp, c ) < 0 ) {
		throw RuntimeException( L"wctomb() failed" );
		result = 0;
	}
	else {
		result = tmp[0];
	}

	delete [] tmp;

#endif
	return result;
}

UnicodeString::AnsiChar* UnicodeString::transformUnicodeToAnsi( const UnicodeString& str )
{
	UnicodeString::AnsiChar* result= NULL;
	int size = 0;


#ifdef VCF_WIN32
    int strLength = str.data_.size();
	if ( str.empty() ) {
		strLength = 1;
	}

	size = ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)str.data_.c_str(), strLength,
							NULL, 0, NULL, NULL );

	if ( !(size > 0) ) {
		throw RuntimeException( L"size > 0 WideCharToMultiByte() failed" );
	}

	result = new UnicodeString::AnsiChar[size+1];

	if (  0 == ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)str.data_.c_str(), strLength,
									result, size, NULL, NULL ) ) {
		//WideCharToMultiByte failed
		delete [] result;
		result = NULL;
	}
	else {
		result[size] = 0;
	}

#elif defined(VCF_OSX)
	if ( str.length() > 0 ) {
		CFTextString tmp;
		tmp = str;
		CFRange r = {0,tmp.length()};
		CFIndex size2 = 0;
		CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, NULL, 0, &size2 );

		if ( !(size2 > 0) ) {
			throw RuntimeException( L"size <= 0 CFStringGetBytes() failed" );
		}

		result = new UnicodeString::AnsiChar[size2+1];

		if (  0 == ::CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false,
										(UInt8*)result, size2, &size2 ) ) {
			//CFStringGetBytes failed
			delete [] result;
			result = NULL;
		}
		else {
			result[size2] = 0;
		}
	}

#elif defined(VCF_POSIX)
	size = wcstombs( NULL, str.data_.c_str(), 0 );

	if ( size < 0 ) {
        // It is not possible to convert the string at once.
        mbstate_t mbs;
        memset(&mbs, 0, sizeof(mbs));
        char mbstr[64];
        size_t mbslen;
        const wchar_t *wcsPtr = str.data_.c_str();
        std::string strRes;
        while(wcsPtr != NULL) {
            memset(mbstr, 0, sizeof(mbstr));
            mbslen = wcsrtombs(mbstr, &wcsPtr, sizeof(mbstr)-1, &mbs);
            if(mbslen == (size_t)-1) {
                if(errno == EILSEQ) {
                    // Conversion failed. Convert to ? instead.
                    strRes += mbstr;
                    strRes += "?";
                    wcsPtr++;
                }
            }
            else
            {
                strRes += mbstr;
            }
        }
        result = new UnicodeString::AnsiChar[strRes.length()+1];
        memset(result, 0, strRes.length()+1);
        strncpy(result, strRes.c_str(), strRes.length());
        return result;
	}

	result = new UnicodeString::AnsiChar[size+1];

	if ( wcstombs( result, str.data_.c_str(), size ) < 0 ) {
		delete [] result;
		result = NULL;
	}
	else {
		result[size] = 0;
	}

#endif

	return result;
}

void UnicodeString::decode_ansi( TextCodec* codec, UnicodeString::AnsiChar* str, UnicodeString::size_type& strSize ) const 
{
	VCF_ASSERT ( str != NULL );

	ulong32 size = codec->convertToAnsiString( *this, str, strSize );	
	
	if ( size < strSize ) {
		str[size] = 0;
	}
	
	strSize = size;
}

UnicodeString UnicodeString::decode( TextCodec* codec ) const
{
	return codec->convertToUnicodeString( *this );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString::AnsiChar* str, UnicodeString::size_type n )
{
	VCF_ASSERT ( str != NULL );
	*this = codec->convertToUnicodeString( str, n );
	modified();
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString& str )
{
	*this = codec->convertToUnicodeString( str );
	modified();
}


bool UnicodeString::operator ==( const UnicodeString::AnsiChar* rhs ) const
{
	VCF_ASSERT ( rhs != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ == tmp.data_;
}

bool UnicodeString::operator !=( const UnicodeString::AnsiChar* rhs ) const
{
	VCF_ASSERT ( rhs != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ != tmp.data_;
}

bool UnicodeString::operator >( const UnicodeString::AnsiChar* rhs ) const
{
	VCF_ASSERT ( rhs != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ > tmp.data_;
}

bool UnicodeString::operator >=( const UnicodeString::AnsiChar* rhs ) const
{
	VCF_ASSERT ( rhs != NULL );
	
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ >= tmp.data_;
}

bool UnicodeString::operator <( const UnicodeString::AnsiChar* rhs ) const
{
	VCF_ASSERT ( rhs != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ < tmp.data_;
}

bool UnicodeString::operator <=( const UnicodeString::AnsiChar* rhs ) const
{
	VCF_ASSERT ( rhs != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	return data_ <= tmp.data_;
}


UnicodeString& UnicodeString::operator=(const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString::transformAnsiToUnicode( s, strlen(s), data_ );
	modified();
	

	return *this;
}

UnicodeString& UnicodeString::operator=(UnicodeString::AnsiChar c)
{
	data_ = UnicodeString::transformAnsiCharToUnicodeChar( c  );
	modified();
	return *this;
}

const UnicodeString::AnsiChar* UnicodeString::ansi_c_str() const
{	
	if ( NULL == ansiDataBuffer_  ) {
		ansiDataBuffer_ = UnicodeString::transformUnicodeToAnsi( *this );
	}

	return ansiDataBuffer_;
}

UnicodeString& UnicodeString::operator+=(UnicodeString::AnsiChar c)
{
	data_ += UnicodeString::transformAnsiCharToUnicodeChar( c  );
	modified();
	return *this;
}

UnicodeString& UnicodeString::operator+=(const AnsiChar* rhs )
{
	VCF_ASSERT ( rhs != NULL );
	
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	data_ += tmp.data_;
	modified();

	return *this;
}

/*
UnicodeString UnicodeString::operator+( const AnsiChar& rhs )
{
	UnicodeString result;
	result = data_ + UnicodeString::transformAnsiCharToUnicodeChar( c  );
	return result;
}

UnicodeString UnicodeString::operator+( const AnsiChar* rhs )
{
	UnicodeString result;
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );

	result = data_ + tmp;
	return result;
}
*/

UnicodeString& UnicodeString::append(const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.append( tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::append(const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	data_.append( tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::append( size_type n, UnicodeString::AnsiChar c)
{
	data_.append( n, UnicodeString::transformAnsiCharToUnicodeChar( c  ) );
	modified();

	return *this;
}

UnicodeString& UnicodeString::assign(const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.assign( tmp.data_ );
	modified();
	return *this;
}

UnicodeString& UnicodeString::assign(const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	data_.assign( tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::assign( size_type n, UnicodeString::AnsiChar c)
{
	data_.assign( n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.insert( p0, tmp.data_ );
	modified();
	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	data_.insert( p0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.insert( p0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString::iterator UnicodeString::insert(UnicodeString::iterator it, UnicodeString::AnsiChar c)
{
	data_.insert( it, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return begin();
}

void UnicodeString::insert(UnicodeString::iterator it, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.insert( it, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	data_.replace( p0, n0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	data_.replace( p0, n0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.replace( p0, n0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	data_.replace( first0, last0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	data_.replace( first0, last0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.replace( first0, last0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString::size_type UnicodeString::copy(UnicodeString::AnsiChar *s, UnicodeString::size_type n, UnicodeString::size_type pos) const
{
	VCF_ASSERT ( s != NULL );
/*
JC this is commented out to make the copy code simpler here.
We translate to a AnsiString, adn then call the copy() method on that
and return the result
	UnicodeString::AnsiChar* copyStr = UnicodeString::transformUnicodeToAnsi( *this );

	UnicodeString::size_type result = minVal<UnicodeString::size_type>( strlen(copyStr+pos), n );

	memcpy( s, copyStr+pos, result );


	delete [] copyStr;

	return result;
*/

	AnsiString copyStr = *this;


	return copyStr.copy( s, n, pos );
	
}

UnicodeString::size_type UnicodeString::find(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.rfind( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.rfind( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.rfind( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_first_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_first_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_first_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_last_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_last_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_last_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_first_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_first_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_first_not_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_last_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_last_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_last_not_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

int UnicodeString::compare(const UnicodeString::AnsiChar *s) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.compare( tmp.data_ ) ;
}

int UnicodeString::compare(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.compare( p0, n0, tmp.data_ ) ;
}

int UnicodeString::compare(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s, UnicodeString::size_type pos) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s+pos, strlen(s+pos), tmp.data_ );

	return data_.compare( p0, n0, tmp.data_ ) ;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.6  2006/03/19 00:14:47  obirsoy
*. Fixed a problem introduced during last commit.
*
*Revision 1.5.2.5  2006/03/19 00:04:17  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.5.2.4  2005/11/30 05:31:36  ddiego
*further osx drag-drop updates.
*
*Revision 1.5.2.3  2005/11/27 23:55:45  ddiego
*more osx updates.
*
*Revision 1.5.2.2  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.5.2.1  2005/09/08 03:16:58  ddiego
*fix for BOM marker in input stream handling and xml parser.
*
*Revision 1.5  2005/07/09 23:15:06  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.3.2.3  2005/05/15 23:17:39  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.2  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.3.2.1  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/10/10 20:42:08  ddiego
*osx updates
*
*Revision 1.2.2.3  2004/09/18 16:54:55  ddiego
*added a new function to the UnicodeString class to convert from a
*unicode char to a ansi char.
*
*Revision 1.2.2.2  2004/09/11 22:55:45  ddiego
*changed the way ansi_c_str() works and got rid of global static map of allocated char* strings. This was causing problems on SMP machines.
*
*Revision 1.2.2.1  2004/09/11 19:16:37  ddiego
*changed the way ansi_c_str() works and got rid of global static map of allocated char* strings. This was causing problems on SMP machines.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.10  2004/06/09 21:12:17  thrysoee
*Fix VCF::String (Unicode) related segfaults on Linux
*
*Revision 1.1.2.9  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.7  2004/05/30 01:36:01  marcelloptr
*tabs reformatting
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
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/21 02:17:27  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.2  2004/04/03 15:48:50  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.6  2004/03/29 15:22:00  ddiego
*some minor fixes
*
*Revision 1.1.2.5  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.1.2.4  2004/03/21 16:03:10  ddiego
*minor change to VCFString to properly allocate a buffer
*unicode xfrm
*
*Revision 1.1.2.3  2004/03/02 03:46:26  ddiego
*some minor fixes for GCC. Still having a problem with GCC on linux, linking, and wide strings. I don't know which I hate more, GCC or MSVC6. Sigh... :(
*
*Revision 1.1.2.2  2004/02/16 05:34:05  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:00:49  ddiego
*added some missing files for locales
*
*/


