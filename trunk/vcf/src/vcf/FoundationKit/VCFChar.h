#ifndef _VCF_VCFCHAR_H__
#define _VCF_VCFCHAR_H__
//VCFChar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF{

	/*
#ifdef VCF_UNICODE
	typedef wchar_t VCFChar;
#else
	typedef char VCFChar;
#endif
	*/

/**
JC - I added this to make it simple to build on
linux platforms - gcc doesn't like
std::basic_string<unsigned short> on linux, but
doesn't like std::basic_string<wchar_t> on OSX, go figure :(
*/
#if defined( VCF_POSIX )
	typedef wchar_t WideChar;
#elif defined( VCF_CYGWIN )
    typedef wchar_t WideChar;
#elif defined( VCF_MINGW )
    typedef wchar_t WideChar;	
#elif defined( VCF_BCC )
    typedef wchar_t WideChar;
#elif defined( VCF_CW_W32 )
	typedef wchar_t WideChar;
#elif defined( VCF_DMC )
	typedef wchar_t WideChar;
#elif defined( VCF_VC80 )
    typedef wchar_t WideChar;
#elif defined( VCF_VC90 )
    typedef wchar_t WideChar;
#elif defined( VCF_VC100 )
    typedef wchar_t WideChar;
#elif defined( VCF_ICL )
    typedef wchar_t WideChar;
#else
	typedef unsigned short WideChar;
#endif



	typedef WideChar VCFChar;
};


#ifdef VCF_OSX


namespace std {

template<>
struct char_traits<VCF::WideChar> {
	typedef VCF::WideChar	char_type;
	typedef wint_t		int_type;
	typedef streamoff 	off_type;
	typedef wstreampos 	pos_type;
	typedef mbstate_t 	state_type;

	static void assign( char_type &c1, const char_type &c2 )
	{
		c1 = c2;
	}

	static bool eq( const char_type &c1, const char_type &c2 )
	{
		return c1 == c2;
	}

	static bool lt( const char_type &c1, const char_type &c2 )
	{
		return c1 < c2;
	}

	static int compare( const char_type *s1, const char_type *s2, size_t n )
	{
		size_t i = 0;
		while ( i < n and *s1 == *s2 )
		{
			++i;
			++s1;
			++s2;
		}
		return i >= n ? 0 : *s1 - *s2;
	}

	static size_t length( const char_type *s )
	{
		const char_type		*p = s;
		while ( *p != 0 )
			++p;
		return p - s;
	}

	static const char_type *find( const char_type *s, size_t n, const char_type &a )
	{
		size_t  i = 0;
		while ( i < n and a != *s )
		{
			++i;
			++s;
		}
		return i >= n ? 0 : s;
	}

	static char_type *move( char_type *s1, const char_type *s2, int_type n )
	{
		return (char_type *)memmove( s1, s2, n * sizeof( char_type ) );
	}

	static char_type *copy( char_type *s1, const char_type *s2, size_t n )
	{
		return (char_type *)memcpy( s1, s2, n * sizeof( char_type ) );
	}

	static char_type *assign( char_type *s, size_t n, char_type a )
	{
		size_t  i = 0;
		char_type *p = s;
		while ( i < n )
		{
			*p = a;
			++i;
			++p;
		}
		return s;
	}

	static char_type to_char_type( const int_type &c )
	{
		return char_type( c );
	}

	static int_type to_int_type( const char_type &c )
	{
		return int_type( c );
	}

	static bool eq_int_type( const int_type &c1, const int_type &c2 )
	{
		return c1 == c2;
	}

	static int_type  eof()
	{
		return static_cast<int_type>(EOF);
	}

	static int_type not_eof( const int_type &c )
	{
		return eq_int_type( c, eof() ) ? 0 : c;
	}
};

}; //end of namespace std

#endif


#endif // _VCF_VCFCHAR_H__

/**
$Id$
*/
