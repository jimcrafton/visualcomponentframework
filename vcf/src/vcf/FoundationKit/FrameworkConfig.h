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

platforms:
VCF_WIN32 - running on some version of 32 bit Windows

VCF_LINUX - running under a linux

VCF_SOLARIS - running under solaris

VCF_X11 - runnning under the X11 windowing platform using the raw xlib library

VCF_GTK - running on a platform that is supported by GTK and using the GTK2 libraries. Typically
this is for linux(or *nix) platforms

VCF_OSX - running under some version of Macintosh OS X using the Cocoa Objective C libraries


compilers

_MSC_VER - compiling with Microsoft's Visual C++ compiler (at least version 6)
VCF_MSC
VCF_VC50
VCF_VC60
VCF_VC70
VCF_VC71

VCF_GCC - compiling with GCC's C++ compiler

VCF_DMC - compiling with Digital Mar's C++ compiler

VCF_BCC - compiling with Borland's C++ compiler
*/


#ifdef _MSC_VER
	#define VCF_MSC
#endif



#define VCF_COMPILER_NAME	""



#if (_MSC_VER >= 1310)
#	define VCF_VC71
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"VC71"
#elif (_MSC_VER >= 1300)
#	define VCF_VC70
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"VC70"
#elif (_MSC_VER >= 1200)
#	define VCF_VC60
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"VC60"
#elif (_MSC_VER >= 1100)
#	define VCF_VC50
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"VC60"
#endif

#ifdef __DMC__
	#define VCF_DMC
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"DMC"
#endif


#ifdef __BORLANDC__
	#define VCF_BCC

#if (__BORLANDC__ >= 0x0570)
	#define VCF_BCCKLX  //Kylix
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"BCCKLX"
#elif (__BORLANDC__ >= 0x0560) && (__BORLANDC__ < 0x0570)
	#define VCF_BCC6 //BCB 6
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"BCC6"
#elif (__BORLANDC__ >= 0x0550) && (__BORLANDC__ < 0x0560)
	#define VCF_BCC5 //BCB 5 - Free Compiler
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"BCC5"
#elif (__BORLANDC__ >= 0x0540)
	#define VCF_BCC4 //BCB 4
#	undef VCF_COMPILER_NAME
#	define VCF_COMPILER_NAME	"BCC4"
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
#ifdef VCF_BCC6
	#pragma warn -8098
#endif	
	#pragma warn -ngu
	#pragma warn -lin
#endif // __BORLANDC__



#ifdef __MWERKS__
	#define VCF_CW
	#ifdef OSX
		#define VCF_CW_OSX
	#elif defined(WIN32)
		#define VCF_CW_W32
	#endif // OS
	#if (__MWERKS__ == 0x2400)
		#define VCF_CW6
		#undef VCF_COMPILER_NAME
		#define VCF_COMPILER_NAME	"CW6"
	#endif
#endif // __MWERKS__


// This will discover the GCC compiler and it's version number (eg 3.4.2)
// __GNUC_VERSION__ contains the version number in integer form (eg 30402) - ACH
#ifdef __GNUC__
	#undef VCF_GCC
	#define VCF_GCC
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



#ifdef WIN32
	//define VCF_WIN32
	#define VCF_WIN32
#endif

#ifdef OSX
	#define VCF_OSX
#endif

#ifdef WIN32


#ifdef VCF_MSC
//disable warnings on 255 char debug symbols
	#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
	#pragma warning (disable : 4231)

//'identifier' : decorated name length exceeded, name was truncated
	#pragma warning (disable:4503)

	//disable C++ Exception Specification ignored
	#pragma warning (disable : 4290)



#	include "vcf/FoundationKit/WarningsOffVc.h"

#endif

#if ( _MSC_VER < 1300 )
//disable warning on base class not declared with the __declspec(dllexport) keyword
	#pragma warning (disable : 4251)

//disable warning on exported class derived from a class that was not exported.
	#pragma warning (disable : 4275)
#endif //_MSC_VER < 1300


#endif //WIN32



#ifdef VCF_WIN32
	#ifdef _UNICODE
		#define VCF_UNICODE_ENABLED
	#endif
#endif















namespace VCF {

	template<typename T> inline const T& minVal(const T& x, const T& y) {
		return x < y ? x : y;
	};

	template<typename T> inline const T& maxVal(const T& x, const T& y) {
		return x > y ? x : y;
	};
};


#define KEEP_NAMESPACE_IN_CLASSNAME
//#define USE_GARBAGE_COLLECTION
#ifdef _WIN32
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
#ifdef VCF_GCC
  #undef NULL

  #ifdef __GNUWIN32__
    #define NULL		0
  #endif

  //this is for handling the "implicit typename is deprecated" warning of GCC
  #define _typename_    typename


#endif //VCF_GCC

#ifndef __GNUWIN32__
#undef NULL
#define NULL		0
#endif //__GNUWIN32__





#ifdef WIN32

/**
this define is to fix:
	[ 533453 ] Disapearing menu items on WinNT 4
*/
//#ifndef _WIN32_WINNT
//note these two MUST defined this way or we get all sorts
//of happy fun problems to deal with. Notably, at the very least,
//the wrong menu structs which cause problems in WinNT4


#if !defined(__GNUWIN32__) && !defined(__BORLANDC__) 
# ifdef WINVER
#   undef WINVER
# endif
#define WINVER 0x0400
# ifdef _WIN32_WINNT
#   undef _WIN32_WINNT
# endif
#define _WIN32_WINNT 0x0400
#endif


//#endif


#define WIN32_LEAN_AND_MEAN
//include std windoze headers for peers....
#include <windows.h>
//#include "Rpcdce.h" //make sure to link with Rpcrt4.lib

#include <commctrl.h> //make sure to link with comctl32.lib
#include <shlobj.h>

#endif //WIN32


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

#if defined(VCF_ALLIN1_DLL) || defined(VCF_ALLIN1_LIB)

#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#endif


# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1310)
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
#		endif
#   ifdef __BORLANDC__
#   define _LIB_CPLVERNUM "bcc"
#   endif
# endif


/**
All of this is here so that if we use this kit in our programs, all we
have to do is pull in this one file, and we'll automatically
link to the correct library! This does mean that our app that uses this
kit needs to have either "VCF_USE_ALLIN1_DLL" defined or
"VCF_USE_ALLIN1_LIB" defined to use the DLL or static libraries.
*/
#if defined(_MSC_VER) || defined(__BORLANDC__)

	#ifdef VCF_USE_ALLIN1_DLL
	//	using dynamic link library
	#	ifdef _DEBUG
	#		pragma comment(lib, "Allin1_"_LIB_CPLVERNUM"_d.lib")
	#	else
	#		pragma comment(lib, "Allin1_"_LIB_CPLVERNUM".lib")
	#	endif
	#elif defined VCF_USE_ALLIN1_LIB
	#		pragma comment(lib, "version.lib") //link to the version lib for retreiving version info
	//	using statically linked library
	#	ifdef _DEBUG
	#		pragma comment(lib, "Allin1_"_LIB_CPLVERNUM"_sd.lib")
	#	else
	#		pragma comment(lib, "Allin1_"_LIB_CPLVERNUM"_s.lib")
	#	endif
	#else
	//	creating the static or dynamic link library
	#endif

#endif //_MSC_VER

#endif //VCF_ALLIN1_DLL/LIB

#if defined (_MSC_VER) || defined (__DMC__) || defined (__GNUWIN32__) || defined(__BORLANDC__) || defined(__MWERKS__)
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
	#			define NETKIT_DLL
	# 	endif
	# 	ifndef USE_FOUNDATIONKIT_DLL
	#			define USE_FOUNDATIONKIT_DLL
	# 	endif
  #elif defined USE_NETKIT_LIB
	# 	ifndef USE_FOUNDATIONKIT_LIB
	#			define USE_FOUNDATIONKIT_LIB
	# 	endif
	#endif

	#ifdef USE_OPENGLKIT_DLL
	# 	ifndef OPENGLKIT_DLL
	#			define OPENGLKIT_DLL
	# 	endif
	# 	ifndef USE_APPLICATIONKIT_DLL
	#			define USE_APPLICATIONKIT_DLL
	# 	endif
  #elif defined USE_OPENGLKIT_LIB
	# 	ifndef USE_APPLICATIONKIT_LIB
	#			define USE_APPLICATIONKIT_LIB
	# 	endif
	#endif
	

	#ifdef USE_APPLICATIONKIT_DLL
	# 	ifndef APPLICATIONKIT_DLL
	#			define APPLICATIONKIT_DLL
	# 	endif
	# 	ifndef USE_GRAPHICSKIT_DLL
	#			define USE_GRAPHICSKIT_DLL
	# 	endif
  #elif defined USE_APPLICATIONKIT_LIB
	# 	ifndef USE_GRAPHICSKIT_LIB
	#			define USE_GRAPHICSKIT_LIB
	# 	endif
	#endif

	#ifdef USE_GRAPHICSKIT_DLL
	# 	ifndef GRAPHICSKIT_DLL
	#			define GRAPHICSKIT_DLL
	# 	endif
	# 	ifndef USE_FOUNDATIONKIT_DLL
	#			define USE_FOUNDATIONKIT_DLL
	# 	endif
  #elif defined USE_GRAPHICSKIT_LIB
	# 	ifndef USE_FOUNDATIONKIT_LIB
	#			define USE_FOUNDATIONKIT_LIB
	# 	endif
	#endif

	#ifdef USE_FOUNDATIONKIT_DLL
	#	 ifndef FOUNDATIONKIT_DLL
	#			define FOUNDATIONKIT_DLL
	#	 endif
	#endif

#endif

// Moved here in order to avoid unnecessary repetition later on - ACH
#ifdef FOUNDATIONKIT_DLL
	#if defined(FOUNDATIONKIT_EXPORTS)
		#define FOUNDATIONKIT_API __declspec(dllexport)
		#define FOUNDATIONKIT_EXPIMP_TEMPLATE
	#else
		#define FOUNDATIONKIT_API __declspec(dllimport)
		#define FOUNDATIONKIT_EXPIMP_TEMPLATE extern
	#endif
#else
	#define FOUNDATIONKIT_API
#endif //FOUNDATIONKIT_DLL


#ifdef GRAPHICSKIT_DLL
	#if defined(GRAPHICSKIT_EXPORTS)
		#define GRAPHICSKIT_API __declspec(dllexport)
		#define GRAPHICSKIT_EXPIMP_TEMPLATE
	#else
		#define GRAPHICSKIT_API __declspec(dllimport)
		#define GRAPHICSKIT_EXPIMP_TEMPLATE extern
	#endif
#else
	#define GRAPHICSKIT_API
#endif //GRAPHICSKIT_DLL


#ifdef APPLICATIONKIT_DLL
	#if defined(APPLICATIONKIT_EXPORTS)
		#define APPLICATIONKIT_API __declspec(dllexport)
		#define APPLICATIONKIT_EXPIMP_TEMPLATE
	#else
		#define APPLICATIONKIT_API __declspec(dllimport)
		#define APPLICATIONKIT_EXPIMP_TEMPLATE extern
	#endif
#else
	#define APPLICATIONKIT_API
#endif //APPLICATIONKIT_DLL


#ifdef OPENGLKIT_DLL
	#if defined(OPENGLKIT_EXPORTS)
		#define OPENGLKIT_API __declspec(dllexport)
		#define OPENGLKIT_EXPIMP_TEMPLATE
	#else
		#define OPENGLKIT_API __declspec(dllimport)
		#define OPENGLKIT_EXPIMP_TEMPLATE extern
	#endif
#else
	#define OPENGLKIT_API
#endif //OPENGLKIT_DLL


#ifdef NETKIT_DLL
	#if defined(NETKIT_EXPORTS)
		#define NETKIT_API __declspec(dllexport)
		#define NETKIT_EXPIMP_TEMPLATE
	#else
		#define NETKIT_API __declspec(dllimport)
		#define NETKIT_EXPIMP_TEMPLATE extern
	#endif
#else
	#define NETKIT_API
#endif //NETKIT_DLL

#ifdef _MSC_VER //we are compiling with Microsoft's Visual C++ compiler

	//don't define  _typename_ as a "typename" keyword because
	//VC6 barfs on it's usage (despite it being part of the C++ standard)
	//Note the new addition is due to better vc7.1 C++ compiler compliance,
	//many thanks to Raghavendra Chandrashekara for finding this!
	#if _MSC_VER < 1310
		#define _typename_
	#else
		#define _typename_ typename
	#endif

#elif defined(__DMC__)

	#define _typename_

#elif defined(__GNUWIN32__)



#elif defined(VCF_BCC)

	#define _typename_ typename

#elif defined(VCF_CW)

	#define _typename_ typename

#endif //_MSC_VER



/**
special macro for handling multi-character constants like 'abcd' which GCC is unhappy with :(
The same is with BCC.
*/
#if defined(VCF_GCC) || defined(VCF_BCC)
	#define CHAR_CONST(x) (unsigned long) x
#else
	#define CHAR_CONST(x) x
#endif


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.6  2005/04/17 16:11:31  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.3.2.5  2005/04/11 17:07:12  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.3.2.4  2004/12/22 03:38:43  marcelloptr
*fixed VCF_COMPILER_NAME macro so less error prone.
*This also makes getExecutableNameFromBundlePath() to work right.
*
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2.2.1  2004/08/17 05:01:32  marcelloptr
*improved macros for library selection
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/30 17:28:40  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.7  2004/07/01 04:02:17  ddiego
*minor stuff
*
*Revision 1.1.2.6  2004/06/30 21:30:03  ddiego
*minor mods to copy/paste code in DocumentManager
*
*Revision 1.1.2.5  2004/06/29 03:17:41  marcelloptr
*minor fixes on import/export library macros
*
*Revision 1.1.2.4  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.26.2.3  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.26.2.2  2004/04/09 01:27:56  marcelloptr
*eliminated warning on WINVER already defined
*
*Revision 1.26.2.1  2004/04/06 17:19:15  ddiego
*minor header changes to better facilitate compiling with
*mingw. Also some minor changes to the devcpp FoundationKit project.
*
*Revision 1.26  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.25  2004/02/16 20:38:16  ddiego
*applied patch from Bobby Ward for further fixes for VC71 compiling
*
*Revision 1.24  2004/02/15 21:55:36  ddiego
*Added changes for vc7.1 compiler, many thanks to Raghavendra Chandrashekara for helping with this.
*
*Revision 1.23  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.22.4.3  2003/12/02 22:11:01  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.22.4.2  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.22.4.1  2003/08/25 15:50:50  ddiego
*added a definition of both WINVER 0x0400 and _WIN32_WINNT 0x0400
*to ensure proper structure sizes, etc
*
*Revision 1.22  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.21.2.3  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.21.2.2  2003/04/17 04:29:45  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.21.2.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.21  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.20.2.2  2002/12/27 23:04:31  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.2.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.20  2002/11/18 00:46:07  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.19.4.2  2002/11/04 04:50:17  ddiego
*bug fixes are:
*void Win32MenuItem::clearChildren(), was passing in an incorrect index into DeleteMenu()
*fixed an issue when deleting a project from a workspace. This was crashing due to open
*documents with bad pointers. Closing a project now closes all open documents that are
*associated with the project
*Verified that the new file and new class and new form, and new project and checking the validity of
*entered data.
*Fixed a bug in Win32Dialog where the Frame::allowClose() virtual method was not being
*called.
*Fixed a bug in the Delegate class which would allow multiple additions of the same event handler.
*
*Revision 1.19.4.1  2002/11/02 20:51:56  ddiego
*fixed NT4 menu bug 533453 Disapearing menu items on WinNT 4
*also added soem bug fixes for hte VCF Builder and some empty name
*error checking in the Win32FileStream class
*
*Revision 1.19  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.18.6.2  2002/08/15 01:12:58  ddiego
*changes to the xmake makefiles adding preliminary support for MinGW
*WARJNING: doesn't yet compile, or at least not on my machine
*
*Revision 1.18.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.18  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17.4.2  2002/04/27 15:42:26  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.17.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.17  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FOUNDATIONKITCONFIG_H__


