/** \file 
  * Included by all comet headers to provide compiler-specific
  * configuration.
  */
/*
 * Copyright � 2000-2002 Sofus Mortensen
 *
 * This material is provided "as is", with absolutely no warranty 
 * expressed or implied. Any use is at your own risk. Permission to 
 * use or copy this software for any purpose is hereby granted without 
 * fee, provided the above notices are retained on all copies. 
 * Permission to modify the code and to distribute modified code is 
 * granted, provided the above notices are retained, and a notice that 
 * the code was modified is included with the above copyright notice. 
 *
 * This header is part of comet.
 * http://www.lambdasoft.dk/comet
 */

#ifndef COMET_CONFIG_H
#define COMET_CONFIG_H

#define COMET_MAJOR_VER 1
#define COMET_BUILDTYPE beta
#define COMET_MINOR_VER 31
#define COMET_BUILD 20040926

#ifndef COMET_BUILD_VERSION_ONLY

#ifndef COMET_NO_DECLSPEC_PROPERTY 
#define COMET_ALLOW_DECLSPEC_PROPERTY 
#endif // COMET_NO_DECLSPEC_PROPERTY 

#pragma warning(disable : 4786)
#pragma warning(disable : 4042)
#pragma warning(disable : 4290)
#pragma warning(disable : 4710)

#ifdef _lint // PC/Lint has a few problems with comet.
# if !defined(_MSC_VER) || _MSC_VER >= 1300
#define COMET_PARTIAL_SPECIALISATION
#else

#endif
#define COMET_NESTED_TEMPLATES
#define COMET_GOOD_RECURSIVE_STRUCT
#define COMET_CONST_MEMBER_INIT
#define COMET_GUID_BASE GUID
#define COMET_STD_ITERATOR
#define COMET_NO_POINTER_CHECKING
#define COMET_STD_SWAP_NOTHROW throw()
#define COMET_TL_TRUNC
#else
//VC 7.1 support partial specialization
#ifdef _MSC_VER  
#endif

#ifdef __ICL
# define COMET_PARTIAL_SPECIALISATION
#else
# ifdef _MSC_VER 
#  if _MSC_VER < 1300
// Versions less than VC7 can't handle the rethrow & catch exception trick.
#    define COMET_DISABLE_EXCEPTION_RETHROW_CATCH
#  else // _MSC_VER >= 1300
#    define COMET_GOOD_RECURSIVE_STRUCT  
#    define COMET_CONST_MEMBER_INIT
#    if _MSC_VER >= 1310
#      define COMET_PARTIAL_SPECIALISATION
#      define COMET_NESTED_TEMPLATES
#    endif
#  endif

# endif
#if defined(_UNICODE) && !defined(UNICODE)
        #define UNICODE
#endif
#endif

#ifdef __BORLANDC__
#pragma warning(disable: 8027)
#pragma warning(disable: 8026)
#define COMET_PARTIAL_SPECIALISATION
#define COMET_NESTED_TEMPLATES
#define COMET_BROKEN_WTYPES
#define COMET_STD_ITERATOR
#define COMET_STD_SWAP_NOTHROW

#define COMET_GUID_BASE _GUID
#else
#define COMET_STD_SWAP_NOTHROW throw()
#define COMET_GUID_BASE GUID
#endif

#if defined( __CYGWIN__ ) || defined( __MINGW32__ )
#define COMET_PARTIAL_SPECIALISATION
#define COMET_NESTED_TEMPLATES
#define COMET_GCC_HEADERS
#define COMET_STD_ITERATOR
#define COMET_TL_TRUNC
#define _T(x) x

// This is not a good idea
// Routines that use _alloca has to be rewritten for __MINGW32__ targets.
// #define _alloca malloc

// WIN32 defines for GCC
#define NONAMELESSUNION
#define NOCOMATTRIBUTE

#elif defined(__MINGW32__)
#define COMET_PARTIAL_SPECIALISATION
#define COMET_NESTED_TEMPLATES
#define COMET_GCC_HEADERS
#define COMET_STD_ITERATOR
#define NONAMELESSUNION
#define NOCOMATTRIBUTE

#endif
#endif


// Use COMET_STRICT_TYPENAME only where MSVC barfs on stricter typename usage
// required by GCC.
#ifdef _MSC_VER
#if _MSC_VER <= 1300
#define COMET_STRICT_TYPENAME 
#else
#define COMET_STRICT_TYPENAME typename
#endif
#else
#define COMET_STRICT_TYPENAME typename
#endif

// PRH Feb 26 2001
// Try and determine which version of std::iterator we have.
// The ANSI/ISO compliant one seems to require a compiler
// that supports partial specialisation, as well as an
// ANSI/ISO compliant implementation of the library.

// Unfortunately, there is no __ANSI_STL #define.
// So we guess:
// If we have partial specialisation, and we're using STLPort, then
// its the ANSI/ISO std::iterator, otherwise it is the MSVC 6.0
// iterator.

// If you're using some other decent STL other than STLPort,
// then you'll need to reflect this by ensuring that COMET_STD_ITERATOR
// is defined.

#if _MSC_VER >= 1300 || defined(_CPPLIB_VER)
#define COMET_STD_ITERATOR
#else
#include <iterator>
#ifdef COMET_PARTIAL_SPECIALISATION
// this code to "detect" STLport is stolen from <boost/config.hpp>
//#if __SGI_STL_PORT >= 0x400 || __SGI_STL_PORT >= 0x321 && defined(__STL_USE_NAMESPACES)
#ifdef __SGI_STL 
#define COMET_STD_ITERATOR
#else
#ifdef __MINGW32__
//__STL_BEGIN_NAMESPACE
//template <class _Tp, class _Distance>struct iterator:  bidirectional_iterator<_Tp,_Distance>{};
//__STL_END_NAMESPACE
#endif // __MINGW32__
#endif
#else
#ifdef _CPPLIB_VER
#define COMET_STD_ITERATOR
#endif 
#endif /* COMET_PARTIAL_SPECIALISATION */
#endif

#ifndef ATL_NO_VTABLE
#if _MSC_VER >= 1200
#define ATL_NO_VTABLE __declspec(novtable)
#else
#define ATL_NO_VTABLE
#endif
#endif

#ifdef _WIN32_WCE
#define GetThreadLocale() LOCALE_USER_DEFAULT


#define CY_MULTIPLIER_F 10000.0
#define CY_MULTIPLIER 10000
#define VARCMP_LT   0
#define VARCMP_EQ   1
#define VARCMP_GT   2
#define VARCMP_NULL 3
/* Missing in Windows but useful VTBIT_* defines */
#define VTBIT_BOOL      (1 << VT_BSTR)
#define VTBIT_BSTR      (1 << VT_BSTR)
#define VTBIT_DATE      (1 << VT_DATE)
#define VTBIT_DISPATCH  (1 << VT_DISPATCH)
#define VTBIT_EMPTY     (1 << VT_EMPTY)
#define VTBIT_ERROR     (1 << VT_ERROR)
#define VTBIT_INT       (1 << VT_INT)
#define VTBIT_NULL      (1 << VT_NULL)
#define VTBIT_UINT      (1 << VT_UINT)
#define VTBIT_UNKNOWN   (1 << VT_UNKNOWN)
#define VTBIT_VARIANT   (1 << VT_VARIANT)
#define VTBIT_15        (1 << 15)        /* no variant type with this number */
#define VTBIT_I1      (1 << VT_I1)
#define VTBIT_UI1     (1 << VT_UI1)
#define VTBIT_I2      (1 << VT_I2)
#define VTBIT_UI2     (1 << VT_UI2)
#define VTBIT_I4      (1 << VT_I4)
#define VTBIT_UI4     (1 << VT_UI4)
#define VTBIT_I8      (1 << VT_I8)
#define VTBIT_UI8     (1 << VT_UI8)
#define VTBIT_R4      (1 << VT_R4)
#define VTBIT_R8      (1 << VT_R8)
#define VTBIT_CY      (1 << VT_CY)
#define VTBIT_DECIMAL (1 << VT_DECIMAL)

#endif

#if _MSC_VER <= 1200
//#define COMET_DO_NOT_SPECIALISE_SWAP_IN_STD
#endif

// Intel compiler version 500 sets _MSC_VER to 1200,
// but doesn't seem to like __forceinline
#if _MSC_VER >= 1200 && !defined(__ICL)
#define COMET_FORCEINLINE __forceinline
#else
#define COMET_FORCEINLINE inline
#endif

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE         // UNICODE is used by Windows headers
#endif
#endif

#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE        // _UNICODE is used by C-runtime/MFC headers
#endif
#endif

// Remove Microsoft's C++ profanity
#undef variant_t
#undef bstr_t
#undef com_cast

// Stop subsequent includes of <comutil.h> from #defining variant_t or bstr_t
#ifndef _USE_RAW
#define _USE_RAW
#endif

#ifndef UUID_DEFINED
#define UUID_DEFINED
#endif

#ifndef UUID
#define UUID GUID
#endif

#ifdef uuid_t
#undef uuid_t
#endif

#define COMET_DECLARE_SWAP(TYPE) template<> inline void swap(TYPE &x, TYPE &y)\
	{\
	x.swap(y);\
	}

const unsigned short COMET_VARIANT_TRUE  = (unsigned short)(0xffff);
const unsigned short COMET_VARIANT_FALSE = 0;

#define COMET_NOTUSED(x) x
#ifndef COMET_CONST_MEMBER_INIT
# define COMET_CONST_TYPE(vartype, varname,value) enum { varname = value };
# define COMET_CONST_GROUP enum {
# define COMET_CONST_ENTRY(vartype, varname,value) varname = value,
# define COMET_CONST_GROUP_END };
#else
# define COMET_CONST_TYPE(vartype, varname,value) static const vartype varname = value;
# define COMET_CONST_ENTRY(vartype, varname,value) COMET_CONST_TYPE(vartype, varname, value);
# define COMET_CONST_GROUP
# define COMET_CONST_GROUP_END
#endif
#endif // COMET_BUILD_VERSION_ONLY
#endif

