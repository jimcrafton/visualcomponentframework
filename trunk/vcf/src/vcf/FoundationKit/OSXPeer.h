#ifndef _VCF_OSXPEER_H__
#define _VCF_OSXPEER_H__
//OSXPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/




namespace VCF {


class OSXStringUtils {
public:
	static String getErrorString( int errorCode ) {
		String result;

		return result;
	}
	
	static String getErrnoString( int errCode ); 

	static String extractStringValueFromCFType( CFTypeRef ref ) {
		String result;
	
		if ( NULL != ref ) {
			CFStringRef resultString = CFStringCreateWithFormat( NULL, NULL, CFSTR("%@"), ref );
			
			if ( NULL != resultString ) {
				
				CFDataRef data = CFStringCreateExternalRepresentation(NULL, 
																	  resultString, 
																	  CFStringGetSystemEncoding(), 
																	  '?');
				
				if (data != NULL) {			
					result.assign( (char*)CFDataGetBytePtr(data), CFDataGetLength(data) );
					
					CFRelease(data);
				}
				
				CFRelease( resultString );
			}	
		}
		
		return result;
	}
	
};


template < typename CFObjType>
class CFRefObject {
protected:
	CFObjType ref_;	
public:	

	CFRefObject( CFObjType ref ):ref_(ref) {
		if ( NULL != ref_ ) {
			CFRetain( ref_ );
		}
	}
	
	CFRefObject():ref_(NULL){}
	
	CFRefObject( const CFRefObject<CFObjType>& rhs ):ref_(NULL) {
		*this = rhs;
	}
	
	~CFRefObject() {
		if ( NULL != ref_ ) {			
			CFRelease( ref_ );
		}
	}
	
	CFRefObject<CFObjType>& operator=( const CFRefObject<CFObjType>& rhs ) {
		if ( NULL != ref_ ) {			
			CFRelease( ref_ );
		}
		
		ref_ = rhs.ref_;
		
		if ( NULL != ref_ ) {
			CFRetain( ref_ );
		}
			
		return *this;
	}
	
	operator CFObjType () {
		return ref_;
	}
	
	bool operator ==( CFObjType rhs ) const	{
		return 	ref_ == rhs;
	}
	
	bool operator !=( CFObjType rhs ) const	{
		return 	ref_ != rhs;
	}
	
	bool operator !() const {
		return (NULL == ref_ ) ? true: false;
	}
	
	CFObjType* operator&( ) {
		return 	&ref_;
	}

};


#define VCF_INTTOFIXED(a)	   ((Fixed)(a) << 16)
#define VCF_FIXEDTOINT(a)	   ((int)(a) >> 16)

class FixedPointNumber {
public:
	FixedPointNumber() : val_(0){
	}

	FixedPointNumber( Fixed val ) : val_(val){}

	FixedPointNumber( const double val ) {
		*this = val;
	}

	FixedPointNumber& operator=( Fixed rhs ) {
		val_ = rhs;
		return *this;
	}

	FixedPointNumber& operator=( const double& rhs ) {
		assign ( rhs );
		return *this;
	}

	FixedPointNumber& operator=( const float& rhs ) {
		assign ( rhs );
		return *this;
	}

	void assign( const double& val ) {
		int fractional = (int)((val - floor(val)) * 0xffff);

		val_ = VCF_INTTOFIXED((int)(floor(val))) | fractional;
	}

	void assign( const int& val ) {
		val_ = VCF_INTTOFIXED(val);
	}

	int asInt() const {
		return VCF_FIXEDTOINT(val_);
	}

	double asDouble() const {
		if ( 0 == val_ ) {
			return 0.0;
		}
		return (double)VCF_FIXEDTOINT(val_) + ((double)(0xFFFF)/(double)(0xFFFF0000 & val_));
	}

	operator double () const {
		return asDouble();
	}

	operator Fixed () const {
		return val_;
	}
	
	Fixed* operator&() {
		return 	&val_;
	}
protected:
	Fixed val_;
};


/**
This is a utility class for wrapping CFStringRef and allowing for
easy assignment to/from a VCF::String class.
This class also has the ability to output a CFUrlRef
*/
class CFTextString {
public:	

	CFTextString() : cfStringRef(nil), unicodeText(NULL){

	}
	
	CFTextString( ConstStr255Param str ): cfStringRef(nil), unicodeText(NULL) {
		assign( str );
	}

	CFTextString( const String& s ) : cfStringRef(nil), unicodeText(NULL){
		assign( s );
	}

    CFTextString( CFStringRef s ) : cfStringRef(nil), unicodeText(NULL){
		assign( s );
	}
	
	CFTextString( CFURLRef url ) : cfStringRef(nil), unicodeText(NULL){
		CFStringRef s = CFURLGetString(url);
		assign( s );
		CFRelease( s );
	}

	~CFTextString() {
		cleanup();
	}

	CFTextString& operator=( const String& s ) {
		assign( s );
		return *this;
	}

    CFTextString& operator=( CFStringRef s ) {
		assign( s );
		return *this;
	}

    CFTextString& operator=( const char* s ) {
        CFStringRef strRef =
            CFStringCreateWithCString( NULL, s, CFStringGetSystemEncoding() );

		assign( strRef );

        CFRelease( strRef );

		return *this;
	}
	
	CFTextString& operator=( ConstStr255Param str ) {
		assign( str );
		return *this;
	}

	int length() const {
		if ( NULL == cfStringRef ) {
			return 0;
		}
		return CFStringGetLength( cfStringRef );
	}

	void assign( const String& s ) {
		cleanup();
        cfStringRef = CFStringCreateMutable( NULL, 0 );
		CFStringAppendCharacters( cfStringRef, s.c_str(), s.size() );
		buildUnicodeBuffer();
	}
	
	void assign( ConstStr255Param str ) {
		
		char tmp[256];
		PLstrcpy( (unsigned char*)tmp, str );
		tmp[ PLstrlen(str) ] = 0;
		
		assign( tmp );        
	}

    void assign( CFStringRef s ) {
		cleanup();

		if ( NULL != s ) {
			cfStringRef = CFStringCreateMutableCopy( NULL, 0, s );

			buildUnicodeBuffer();
		}
	}



	CFStringRef ref() const {
		return cfStringRef;
	}

    CFMutableStringRef m_ref() {
		return cfStringRef;
	}

    operator CFMutableStringRef () {
		return cfStringRef;
	}

	operator CFStringRef () const {
		return cfStringRef;
	}
	
	/**
	Returns a CFURLRef - the caller is responsible for releasing the reference.
	*/
	operator CFURLRef () const {
		return CFURLCreateWithString( NULL, cfStringRef, NULL );
	}

    operator String () const {
        String result;
		if ( NULL != unicodeText ) {
			result = unicodeText;
		}
        return result;
    }

    const char* ansi_c_str() const {
        return CFStringGetCStringPtr( cfStringRef, CFStringGetSystemEncoding() );
    }

	const UniChar* c_str() const {
		return unicodeText;
	}

    void copy( UniChar* buffer, int bufferLength ) const {
        memcpy( buffer, unicodeText, sizeof(UniChar) * bufferLength );
    }

    void formatWithArgs( CFStringRef formatStr, va_list arguments ) {
        CFStringRef strRef = CFStringCreateWithFormatAndArguments( NULL, NULL, formatStr, arguments );

        assign( strRef );

        CFRelease( strRef );
    }


    void format( CFStringRef formatStr, ... ) {
        va_list argList;

        va_start( argList, formatStr );

        formatWithArgs( formatStr, argList );

        va_end( argList );
    }

    void upperCase() {
        CFStringUppercase( cfStringRef, NULL );

        if ( NULL != unicodeText ) {
			delete [] unicodeText;
            unicodeText = NULL;
		}

        buildUnicodeBuffer();
    }

    void lowerCase() {
        CFStringLowercase( cfStringRef, NULL );

        if ( NULL != unicodeText ) {
			delete [] unicodeText;
            unicodeText = NULL;
		}

        buildUnicodeBuffer();
    }
protected:
	void cleanup()	{
		if ( NULL != unicodeText ) {
			delete [] unicodeText;
		}

		if ( nil != cfStringRef ) {
			CFRelease(cfStringRef);
		}
		cfStringRef = nil;
		unicodeText = NULL;
	}

	void buildUnicodeBuffer() {
		int length = CFStringGetLength( cfStringRef );
		unicodeText = new UniChar[length+1];
		CFRange range = {0,length};
		CFStringGetCharacters(cfStringRef,range,unicodeText);
		unicodeText[length] = 0;
	}
	CFMutableStringRef cfStringRef;
	UniChar* unicodeText;

private:
		CFTextString( const CFTextString& rhs );
		CFTextString& operator=( const CFTextString& rhs );
};







};


#endif // _VCF_OSXPEER_H__

/**
$Id$
*/
