#ifndef _VCF_FOUNDATIONKITCONFIG_H__
#define _VCF_FOUNDATIONKITCONFIG_H__
//FrameworkConfig.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*Basic setup defines for Foundationkit Classes
*/



/**
Common #defines for various compilers and platforms. Note that some of these are defined by the
current compiler (i.e. _MSC_VER), but others must be defined in your build script.

Platforms:

	VCF_WIN - running on some version of Windows
	VCF_WIN32 - running on some version of 32 bit Windows
	VCF_WIN64 - running on some version of 64 bit Windows

	VCF_CYGWIN - running under a Cygwin

	VCF_OSX - running under some version of Macintosh OS X using the Cocoa Objective C libraries

	VCF_POSIX - running under a linux


Toolkits:

	VCF_X11 - runnning under the X11 windowing platform using the raw xlib library

	VCF_GTK - running on a platform that is supported by GTK and using 
		the GTK2 libraries. Typically this is for linux(or *nix) platforms


Compilers:

	VCF_ICL - compiling with Intel's C++ compiler

	VCF_MSC - compiling with Microsoft's Visual C++ compiler (at least version 6)
	VCF_VC50
	VCF_VC60
	VCF_VC70
	VCF_VC71
	VCF_VC80

	VCF_DMC - compiling with Digital Mar's C++ compiler

	VCF_BCC - compiling with Borland's C++ compiler
	VCF_BCC4
	VCF_BCC5
	VCF_BCC6
	VCF_BCCKLX
	VCF_BCC8

	VCF_CW - compiling with CodeWarrior MetroWerks' C++ compiler
	VCF_CW6
	VCF_CW_OSX
	VCF_CW_W32

	VCF_GCC - compiling with GCC's C++ compiler

	VCF_MINGW - compiling with MinGW version of GCC's C++ compiler


Miscellaneous:

	VCF_UNICODE - Unicode is default

*/


/**
Setup VCF_ operating system
*/
#if defined(WIN32) || defined(_WIN32)
	#define VCF_WIN32

	// Define both to be sure that the thirdpatry code will find appropriate one.
	#ifndef _WIN32
		#define _WIN32
	#endif
	#ifndef WIN32
		#define WIN32
	#endif
#endif

#if defined(WIN64) || defined(_WIN64)
	#define VCF_WIN64

	// Define both to be sure that the thirdpatry code will find appropriate one.
	#ifndef _WIN64
		#define _WIN64
	#endif
	#ifndef WIN64
		#define WIN64
	#endif
#endif

#if defined(VCF_WIN32) || defined(VCF_WIN64)
	#define VCF_WIN
#endif


#ifdef __CYGWIN__
	#define VCF_CYGWIN
#endif


#ifdef OSX
	#define VCF_OSX
#endif


#ifdef __linux__
    #define VCF_POSIX
#endif


/**
Setup compiler names, and some compiler-specific warnings
*/
#define VCF_COMPILER_NAME	""


#ifdef __INTEL_COMPILER
	#define VCF_ICL

    // Intel compiler defines _MSC_VER either as it consider to be compatible.
    // We undef it to keep separate their issues.
	#undef _MSC_VER

	#undef VCF_COMPILER_NAME
	#define VCF_COMPILER_NAME	"ICL"
#endif // __INTEL_COMPILER


#ifdef _MSC_VER
	#define VCF_MSC

	#if (_MSC_VER >= 1400)
		#define VCF_VC80
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"VC80"
	#elif (_MSC_VER >= 1310)
		#define VCF_VC71
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"VC71"
	#elif (_MSC_VER >= 1300)
		#define VCF_VC70
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"VC70"
	#elif (_MSC_VER >= 1200)
		#define VCF_VC60
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"VC60"
	#elif (_MSC_VER >= 1100)
		#define VCF_VC50
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"VC50"
	#endif

    // Disable some warnings
	#include "vcf/FoundationKit/WarningsOffVc.h"

#endif


#ifdef __DMC__
	#define VCF_DMC

	#undef VCF_COMPILER_NAME
	#define VCF_COMPILER_NAME	"DMC"
#endif


#ifdef __BORLANDC__
	#define VCF_BCC

	#if (__BORLANDC__ >= 0x0580 )
		#define VCF_BCC8  //BDS 2006
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"BCC8"
	#elif (__BORLANDC__ == 0x0570)
		#define VCF_BCCKLX  //Kylix
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"BCCKLX"
	#elif (__BORLANDC__ >= 0x0560) && (__BORLANDC__ < 0x0570)
		#define VCF_BCC6 //BCB 6
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"BCC6"
	#elif (__BORLANDC__ >= 0x0550) && (__BORLANDC__ < 0x0560)
		#define VCF_BCC5 //BCB 5 - Free Compiler
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"BCC5"
	#elif (__BORLANDC__ >= 0x0540)
		#define VCF_BCC4 //BCB 4
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"BCC4"
	#endif //bcc version

	#if defined(VCF_BCC6) && !defined(_USE_OLD_RW_STL)
		#define __MINMAX_DEFINED
		#define NOMINMAX    
		using std::min;
		using std::max;
		#define __max max
		#define __min min
	#endif //minmax defined

	//Some pragmas now
	#pragma warn -8026
	#pragma warn -inl
	#pragma warn -aus
	#pragma warn -ccc
	#pragma warn -csu
	#pragma warn -osh
	#pragma warn -par
	#pragma warn -pia
	#pragma warn -rch
	#pragma warn -rng
	#pragma warn -hid
	#if (__BORLANDC__ > 0x0551)
		#pragma warn -8098
	#endif	
	#pragma warn -ngu
	#pragma warn -lin
#endif // __BORLANDC__


#ifdef __MWERKS__
	#define VCF_CW

	#ifdef OSX
		#define VCF_CW_OSX
	#elif defined(VCF_WIN32)
		#define VCF_CW_W32
	#endif // OSX
	#if (__MWERKS__ == 0x2400)
		#define VCF_CW6
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"CW6"
	#endif
#endif // __MWERKS__


#ifdef __GNUC__
	#define VCF_GCC

	// This will discover the GCC compiler and it's version number (eg 3.4.2)
	// __GNUC_VERSION__ contains the version number in integer form (eg 30402) - ACH
	#if defined(__GNU_PATCHLEVEL__)
		#define __GNUC_VERSION__ (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100 \
                            + __GNUC_PATCHLEVEL__)
	#else
		#define __GNUC_VERSION__ (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100)
	#endif
	#undef VCF_COMPILER_NAME
	
	//The below does NOT compile under GCC 3.3.3. Does anyone know why not???
	//#define VCF_COMPILER_NAME "GCC"__GNUC__"."__GNUC_MINOR__"."__GNUC_PATCHLEVEL__
	#define VCF_COMPILER_NAME String("GCC") + __GNUC__ + "."
#endif // __GNUC__


#ifdef __MINGW32__
	#define VCF_MINGW

	#undef VCF_COMPILER_NAME
	#define VCF_COMPILER_NAME	"MINGW"
#endif // __MINGW32__


/**
Setup VCF_ miscellaneous macros
*/
#if defined(_UNICODE) || defined(UNICODE)
	#define VCF_UNICODE

	// Define both to be sure that the thirdpatry code will find appropriate one.
	#ifndef _UNICODE
		#define _UNICODE
	#endif
	#ifndef UNICODE
		#define UNICODE
	#endif
#endif



namespace VCF {

	typedef unsigned char  uchar;
	typedef unsigned short ushort;
	typedef unsigned int   uint;
	typedef unsigned long  ulong;

	typedef signed char    int8;
	typedef unsigned char  uint8;
	
	typedef short          int16;
	typedef unsigned short uint16;

	typedef int            int32;
	typedef unsigned int   uint32;

	/**
	This is used as a wrapper around some platform
	object or handle. 
	*/
	typedef void*			OSHandleID;

	
	template<typename T> inline const T& minVal(const T& x, const T& y) {
		return x < y ? x : y;
	};

	template<typename T> inline const T& maxVal(const T& x, const T& y) {
		return x > y ? x : y;
	};


	/**
	\typedef ulong64 FrameworkConfig.h "vcf/FoundationKit/FrameworkConfig.h"
	Unsigned 64 bit integer type
	*/
	#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
		typedef unsigned __int64 ulong64;
	#else
		typedef unsigned long long ulong64;
	#endif


	/**
	\typedef long64 FrameworkConfig.h "vcf/FoundationKit/FrameworkConfig.h"
	Signed 64 bit integer type
	*/
	#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
		typedef __int64 long64;
	#else
		typedef long long long64;
	#endif


	/**
	\def VCF_LIT64 FrameworkConfig.h "vcf/FoundationKit/FrameworkConfig.h"
	Macro to include a 64 bit integer literal in the code.
	The macro will append the correct suffix that the compiler
	may need for 64 bit integer literals (for example LL for gcc).
	Usage example:
	\code
	ulong64 x = VCF_LIT64(0xffffffffffffffff);
	\endcode
	*/
	#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
		#define VCF_LIT64(x) (x)	// not suffix needed
	#else
		#define VCF_LIT64(x) (x##LL)
	#endif


	/**
	This returns the top 32 bits of the number
	*/
	inline uint32 getHi32(ulong64 val){
		return (uint32)(val>>32);
	}


	/**
	This returns the top 32 bits of the number
	*/
	inline int32 getHi32(long64 val){
		return (int32)(val>>32);
	}


	/**
	This returns the low 32 bits of the number
	*/
	inline uint32 getLo32(ulong64 val){
		return (uint32)val;
	}


	/**
	This returns the low 32 bits of the number
	*/
	inline uint32 getLo32(long64 val){
		return (uint32)val;
	}


	/**
	This sets the top 32 bits of the number to the specified
	value.
	*/
	inline void setHi32(ulong64& val,uint32 hi){
		val = (val & 0xffffffff) | (((ulong64)hi)<<32);
	}


	/**
	This sets the top 32 bits of the number to the specified
	value.
	*/
	inline void setHi32(long64& val,int32 hi){
		val = (val & 0xffffffff) | (((long64)hi)<<32);
	}


	/**
	This sets the low 32 bits of the number to the specified
	value.
	*/
	inline void setLo32(ulong64& val,uint32 lo){
		val = (val & VCF_LIT64(0xffffffff00000000)) | lo;
	}

	/**
	This sets the low 32 bits of the number to the specified
	value.
	*/
	inline void setLo32(long64& val,uint32 lo){
		val = (val & VCF_LIT64(0xffffffff00000000)) | lo;
	}



	/**
	Creates an unsigned 64 bit integer from the
	high and low 32 bit.*/
	inline ulong64 makeULong64(uint32 hi,uint32 lo){
		return (((ulong64)hi)<<32) | lo;
	}


	/**
	Creates a signed 64 bit integer from the
	high and low 32 bit.*/
	inline long64 makeLong64(int32 hi,uint32 lo){
		return (((long64)hi)<<32) | lo;
	}
	

};



#define KEEP_NAMESPACE_IN_CLASSNAME

#ifdef VCF_WIN
	#ifdef _DEBUG
	//	#define USE_VCF_NEW
	#endif
#endif


//this section will turn the advanced RTTI features on or off. By default they are on
//Note: Turning them off means that code that depends on the RTTI API's will fail.
#ifndef VCF_NO_RTTI
	#define VCF_RTTI
#endif

//comment this out to prevent the framework from using it's debug operator new() functions
#ifdef _DEBUG
	#define _VCF_DEBUG_NEW
#endif

//apparently NULL may not always be 0 - this makes it so...
#ifndef VCF_CYGWIN
	#undef NULL
	#define NULL		0
#endif //VCF_CYGWIN



#ifdef VCF_WIN

/**
this define is to fix:
	[ 533453 ] Disapearing menu items on WinNT 4
*/
//#ifndef _WIN32_WINNT
//note these two MUST defined this way or we get all sorts
//of happy fun problems to deal with. Notably, at the very least,
//the wrong menu structs which cause problems in WinNT4


	#if !defined(VCF_CYGWIN) && !defined(VCF_BCC)  
		#ifdef WINVER
			#undef WINVER
		#endif
		#define WINVER 0x0400
		#ifdef _WIN32_WINNT
			#undef _WIN32_WINNT
		#endif
		#define _WIN32_WINNT 0x0400
	#endif

	#if defined(VCF_MINGW)  
		#define _WIN32_IE 0x0500
		#if defined(_WIN32_WINNT)
			#undef _WIN32_WINNT
		#endif
		#define _WIN32_WINNT 0x0500
	#endif

	#define WIN32_LEAN_AND_MEAN

#endif //VCF_WIN



/**
VCF code should use _typename_, and it gets set appropriately here
*/
#ifdef VCF_MSC

	//don't define  _typename_ as a "typename" keyword because
	//VC6 barfs on it's usage (despite it being part of the C++ standard)
	//Note the new addition is due to better vc7.1 C++ compiler compliance,
	//many thanks to Raghavendra Chandrashekara for finding this!
	#if _MSC_VER < 1310
		#define _typename_
	#else
		#define _typename_ typename
	#endif

#elif defined(VCF_DMC)

	#define _typename_

#else

	#define _typename_ typename

#endif //VCF_MSC



/**
special macro for handling multi-character constants like 'abcd' which GCC is unhappy with :(
The same is with BCC.
*/
#if defined(VCF_GCC) || defined(VCF_BCC)
	#define CHAR_CONST(x) (uint32) x
#else
	#define CHAR_CONST(x) x
#endif



//Macros to handle the All-in-1 library option
//Note that you are able to create an All-in-1 with chosen kits excluded.
//If you exclude a kit that supports an included kit (eg FoundationKit),
//then you are responsible for providing the excluded kit separately.
#ifdef VCF_USE_ALLIN1_DLL
#	ifndef VCF_ALLIN1_NO_OPENGLKIT
#		define USE_OPENGLKIT_DLL
#	elif !defined(VCF_ALLIN1_NO_APPLICATIONKIT)
#		define USE_APPLICATIONKIT_DLL
#	elif !define(VCF_ALLIN1_NO_GRAPHICSKIT)
#		define USE_GRAPHICS_KIT	/*
#	elif !define(VCF_ALLIN1_NO_NETKIT)
#		define USE_NETKIT_DLL	*/
#	elif !define(VCF_ALLIN1_NO_FOUNDATIONKIT)
#		pragma error("You're trying to use an All-in-1 dll with nothing in it!")
#	endif
#elif defined(VCF_USE_ALLIN1_LIB)
#	ifndef VCF_ALLIN1_NO_OPENGLKIT
#		define USE_OPENGLKIT_LIB
#	elif !defined(VCF_ALLIN1_NO_APPLICATIONKIT)
#		define USE_APPLICATIONKIT_LIB
#	elif !define(VCF_ALLIN1_NO_GRAPHICSKIT)
#		define USE_GRAPHICS_KIT	/*
#	elif !define(VCF_ALLIN1_NO_NETKIT)
#		define USE_NETKIT_LIB	*/
#	elif !define(VCF_ALLIN1_NO_FOUNDATIONKIT)
#		pragma error("You're trying to use an All-in-1 lib with nothing in it!")
#	endif
#endif

#ifdef VCF_ALLIN1_DLL
#	ifndef VCF_ALLIN1_NO_FOUNDATIONKIT
#		define FOUNDATIONKIT_DLL
#	endif
#	ifndef VCF_ALLIN1_NO_GRAPHICSKIT
#		define GRAPHICSKIT_DLL
#	endif
#	ifndef VCF_ALLIN1_NO_APPLICATIONKIT
#		define APPLICATIONKIT_DLL
#	endif
#	ifndef VCF_ALLIN1_NO_OPENGLKIT
#		define OPENGLKIT_DLL
#	endif	/*
#	ifndef VCF_ALLIN1_NO_NETKIT
#		define NETKIT_DLL
#	endif
#	ifndef VCF_ALLIN1_NO_REMOTEKIT
#		define REMOTEKIT_DLL
#	endif	*/
#endif

#ifdef VCF_ALLIN1_EXPORTS
#	ifndef VCF_ALLIN1_NO_FOUNDATIONKIT
#		define FOUNDATIONKIT_EXPORTS
#	endif
#	ifndef VCF_ALLIN1_NO_GRAPHICSKIT
#		define GRAPHICSKIT_EXPORTS
#	endif
#	ifndef VCF_ALLIN1_NO_APPLICATIONKIT
#		define APPLICATIONKIT_EXPORTS
#	endif
#	ifndef VCF_ALLIN1_NO_OPENGLKIT
#		define OPENGLKIT_EXPORTS
#	endif	/*
#	ifndef VCF_ALLIN1_NO_NETKIT
#		define NETKIT_EXPORTS
#	endif
#	ifndef VCF_ALLIN1_NO_REMOTEKIT
#		define REMOTEKIT_EXPORTS
#	endif	*/
#endif

#if defined(VCF_ALLIN1_DLL) || defined(VCF_ALLIN1_LIB) || defined(VCF_USE_ALLIN1_DLL) || defined(VCF_USE_ALLIN1_LIB)

#  ifdef _LIB_CPLVERNUM
#    undef _LIB_CPLVERNUM
#  endif


# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#	endif
#   ifdef VCF_BCC
#     define _LIB_CPLVERNUM "bcc"
#   endif
# endif

#endif //VCF_ALLIN1_DLL/LIB

/**
All of this is here so that if we use this kit in our programs, all we
have to do is pull in this one file, and we'll automatically
link to the correct library! This does mean that our app that uses this
kit needs to have either "VCF_USE_ALLIN1_DLL" defined or
"VCF_USE_ALLIN1_LIB" defined to use the DLL or static libraries.
*/
#if defined(VCF_MSC) || defined(VCF_BCC)

	#ifdef VCF_USE_ALLIN1_DLL
	//	using dynamic link library
	#	ifdef _DEBUG
	#		pragma comment(lib, "VCF_"_LIB_CPLVERNUM"_d.lib")
	#	else
	#		pragma comment(lib, "VCF_"_LIB_CPLVERNUM".lib")
	#	endif
	#elif defined (VCF_USE_ALLIN1_LIB)
	#		pragma comment(lib, "version.lib") //link to the version lib for retreiving version info
	#		pragma comment(lib, "comctl32.lib") //link to the version lib for retreiving version info
	#		pragma comment(lib, "rpcrt4.lib") //link to the version lib for retreiving version info
	//	using statically linked library
	#	ifdef _DEBUG
	#		pragma comment(lib, "VCF_"_LIB_CPLVERNUM"_sd.lib")
	#	else
	#		pragma comment(lib, "VCF_"_LIB_CPLVERNUM"_s.lib")
	#	endif
	#else
	//	creating the static or dynamic link library
	#endif

#endif //VCF_MSC



#if defined (VCF_MSC) || defined (VCF_DMC) || defined (VCF_CYGWIN) ||defined(VCF_MINGW) || defined(VCF_BCC) || defined(VCF_CW)
  // when we use USE_FOUNDATIONKIT_DLL we always want FOUNDATIONKIT_DLL
	// and we save a MACRO defines at the same time.
	// Nevertheless USE_FOUNDATIONKIT_DLL cannot replace FOUNDATIONKIT_DLL

	// USE_APPLICATIONKIT_DLL implies USE_GRAPHICSKIT_DLL
	// USE_GRAPHICSKIT_DLL    implies USE_FOUNDATIONKIT_DLL
	// USE_NETKIT_DLL         implies USE_FOUNDATIONKIT_DLL
	// USE_OPENGLKIT_DLL	  implies USE_APPLICATIONKIT_DLL
	// and 
	// USE_APPLICATIONKIT_LIB implies USE_GRAPHICSKIT_LIB
	// USE_GRAPHICSKIT_LIB    implies USE_FOUNDATIONKIT_LIB
	// USE_NETKIT_LIB         implies USE_FOUNDATIONKIT_LIB
	// USE_OPENGLKIT_LIB	  implies USE_OPENGLKIT_LIB

	#ifdef USE_NETKIT_DLL
	# 	ifndef NETKIT_DLL
	#		define NETKIT_DLL
	# 	endif
	# 	ifndef USE_FOUNDATIONKIT_DLL
	#		define USE_FOUNDATIONKIT_DLL
	# 	endif
	#elif defined (USE_NETKIT_LIB)
	# 	ifndef USE_FOUNDATIONKIT_LIB
	#		define USE_FOUNDATIONKIT_LIB
	# 	endif
	#endif

	#ifdef USE_OPENGLKIT_DLL
	# 	ifndef OPENGLKIT_DLL
	#		define OPENGLKIT_DLL
	# 	endif
	# 	ifndef USE_APPLICATIONKIT_DLL
	#		define USE_APPLICATIONKIT_DLL
	# 	endif
	#elif defined (USE_OPENGLKIT_LIB)
	# 	ifndef USE_APPLICATIONKIT_LIB
	#		define USE_APPLICATIONKIT_LIB
	# 	endif
	#endif	

	#ifdef USE_APPLICATIONKIT_DLL
	# 	ifndef APPLICATIONKIT_DLL
	#		define APPLICATIONKIT_DLL
	# 	endif
	# 	ifndef USE_GRAPHICSKIT_DLL
	#		define USE_GRAPHICSKIT_DLL
	# 	endif
	#elif defined (USE_APPLICATIONKIT_LIB)
	# 	ifndef USE_GRAPHICSKIT_LIB
	#		define USE_GRAPHICSKIT_LIB
	# 	endif
	#endif

	#ifdef USE_GRAPHICSKIT_DLL
	# 	ifndef GRAPHICSKIT_DLL
	#		define GRAPHICSKIT_DLL
	# 	endif
	# 	ifndef USE_FOUNDATIONKIT_DLL
	#		define USE_FOUNDATIONKIT_DLL
	# 	endif
	#elif defined (USE_GRAPHICSKIT_LIB)
	# 	ifndef USE_FOUNDATIONKIT_LIB
	#		define USE_FOUNDATIONKIT_LIB
	# 	endif
	#endif

	#ifdef USE_FOUNDATIONKIT_DLL
	#	 ifndef FOUNDATIONKIT_DLL
	#		define FOUNDATIONKIT_DLL
	#	 endif
	#endif

#endif



/**
* Setup attributes for importing/exporting
*/

// MinGW chokes on inline and __declspec(dllimport) together.
// this is lesser of 2 evils hopefully
#if defined(VCF_MINGW)
	#ifdef FOUNDATIONKIT_DLL
	#	if defined(FOUNDATIONKIT_EXPORTS)
	#		define FOUNDATIONKIT_API __declspec(dllexport)
	#	else
	#		define FOUNDATIONKIT_API
	#	endif
	#else
	#	define FOUNDATIONKIT_API
	#endif

	#ifdef GRAPHICSKIT_DLL
	#	if defined(GRAPHICSKIT_EXPORTS)
	#		define GRAPHICSKIT_API __declspec(dllexport)
	#	else
	#		define GRAPHICSKIT_API
	#	endif
	#else
	#	define GRAPHICSKIT_API
	#endif

	#ifdef APPLICATIONKIT_DLL
	#	if defined(APPLICATIONKIT_EXPORTS)
	#		define APPLICATIONKIT_API __declspec(dllexport)
	#	else
	#		define APPLICATIONKIT_API
	#	endif
	#else
	#	define APPLICATIONKIT_API
	#endif

	#ifdef OPENGLKIT_DLL
	#	if defined(OPENGLKIT_EXPORTS)
	#		define OPENGLKIT_API __declspec(dllexport)
	#	else
	#		define OPENGLKIT_API
	#	endif
	#else
	#	define OPENGLKIT_API
	#endif

	#ifdef NETKIT_DLL
	#	if defined(NETKIT_EXPORTS)
	#		define NETKIT_API __declspec(dllexport)
	#	else
	#		define NETKIT_API
	#	endif
	#else
	#	define NETKIT_API
	#endif	
#else

	// Moved here in order to avoid unnecessary repetition later on - ACH
	#if defined(FOUNDATIONKIT_DLL) && !defined(VCF_GCC)
		#if defined(FOUNDATIONKIT_EXPORTS)
			#define FOUNDATIONKIT_API __declspec(dllexport)
		#else
			#define FOUNDATIONKIT_API __declspec(dllimport)
		#endif
	#else
		#define FOUNDATIONKIT_API
	#endif //FOUNDATIONKIT_DLL

	#ifdef GRAPHICSKIT_DLL
		#if defined(GRAPHICSKIT_EXPORTS)
			#define GRAPHICSKIT_API __declspec(dllexport)
		#else
			#define GRAPHICSKIT_API __declspec(dllimport)
		#endif
	#else
		#define GRAPHICSKIT_API
	#endif //GRAPHICSKIT_DLL

	#ifdef APPLICATIONKIT_DLL
		#if defined(APPLICATIONKIT_EXPORTS)
			#define APPLICATIONKIT_API __declspec(dllexport)
		#else
			#define APPLICATIONKIT_API __declspec(dllimport)
		#endif
	#else
		#define APPLICATIONKIT_API
	#endif //APPLICATIONKIT_DLL

	#ifdef OPENGLKIT_DLL
		#if defined(OPENGLKIT_EXPORTS)
			#define OPENGLKIT_API __declspec(dllexport)
		#else
			#define OPENGLKIT_API __declspec(dllimport)
		#endif
	#else
		#define OPENGLKIT_API
	#endif //OPENGLKIT_DLL

	#ifdef NETKIT_DLL
		#if defined(NETKIT_EXPORTS)
			#define NETKIT_API __declspec(dllexport)
		#else
			#define NETKIT_API __declspec(dllimport)
		#endif
	#else
		#define NETKIT_API
	#endif //NETKIT_DLL
	
#endif



#endif // _VCF_FOUNDATIONKITCONFIG_H__

/**
$Id$
*/
