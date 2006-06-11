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

	#ifdef VCF_WIN
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

#ifdef VCF_WIN
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

#ifdef VCF_WIN
	
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


#ifdef VCF_WIN
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
$Id$
*/
