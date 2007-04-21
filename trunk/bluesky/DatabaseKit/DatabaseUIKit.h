#ifndef _VCF_DATABASEUIKIT_H__
#define _VCF_DATABASEUIKIT_H__

/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

// We don't need any of this if we've disabled pragma linking
#ifndef VCF_DISABLE_PRAGMA_LINKING

/**
Handle the extension based on the compiler
*/
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
#		endif
#  ifdef __BORLANDC__
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif


#ifdef _DEBUG
	#define DBUIKIT_LIBDLL	"DatabaseUIKit_"_LIB_CPLVERNUM"_d.lib"
	#define DBUIKIT_LIBS	"DatabaseUIKit_"_LIB_CPLVERNUM"_sd.lib"
#else
	#define DBUIKIT_LIBDLL	"DatabaseUIKit_"_LIB_CPLVERNUM".lib"
	#define DBUIKIT_LIBS	"DatabaseUIKit_"_LIB_CPLVERNUM"_s.lib"
#endif



//auto link stuff
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_DATABASEUIKIT_DLL
		#pragma message( "linking to " DBUIKIT_LIBDLL )
		#define DATABASEUIKIT_DLL
		// using dynamic link library		
		#pragma comment(lib, DBUIKIT_LIBDLL)
	#elif defined USE_DATABASEUIKIT_LIB
		#pragma message( "linking to " DBUIKIT_LIBS )
		// using statically linked library
		#pragma comment(lib, DBUIKIT_LIBS)
	#endif

#endif //VCF_MSC





//this sets up a "dependencies" set of defines
//if you are using the regex kit, then it only makes 
//sense that you are ALSO using the FoundationKit.
//the following takes care of defining these for you.

#ifdef USE_DATABASEUIKIT_DLL
# 	ifndef DATABASEUIKIT_DLL
#		define DATABASEUIKIT_DLL
# 	endif
#elif defined (USE_DATABASEUIKIT_LIB)
# 	ifndef DATABASEUIKIT_LIB
#		define DATABASEUIKIT_LIB
# 	endif
#endif

#ifdef DATABASEUIKIT_DLL
# 	ifndef USE_APPLICATIONKIT_DLL
#		define USE_APPLICATIONKIT_DLL
# 	endif
# 	ifndef USE_GRAPHICSKIT_DLL
#		define USE_GRAPHICSKIT_DLL
# 	endif
# 	ifndef USE_FOUNDATIONKIT_DLL
#		define USE_FOUNDATIONKIT_DLL
# 	endif
# 	ifndef USE_DATABASEKIT_DLL
#		define USE_DATABASEKIT_DLL
# 	endif
#elif defined (DATABASEUIKIT_LIB)
# 	ifndef USE_APPLICATIONKIT_LIB
#		define USE_APPLICATIONKIT_LIB
# 	endif
# 	ifndef USE_GRAPHICSKIT_LIB
#		define USE_GRAPHICSKIT_LIB
# 	endif
# 	ifndef USE_FOUNDATIONKIT_LIB
#		define USE_FOUNDATIONKIT_LIB
# 	endif
# 	ifndef USE_DATABASEKIT_LIB
#		define USE_DATABASEKIT_LIB
# 	endif
#endif


#ifndef USE_FOUNDATIONKIT_DLL
#pragma message ("USE_FOUNDATIONKIT_DLL not defined!!!")
#endif

#endif // VCF_DISABLE_PRAGMA_LINKING

//export crap
#ifdef DATABASEUIKIT_DLL
	#if defined(DATABASEUIKIT_EXPORTS)
		#define DATABASEUIKIT_API __declspec(dllexport)
	#else
		#define DATABASEUIKIT_API __declspec(dllimport)
	#endif
#else
	#define DATABASEUIKIT_API
#endif //DATABASEUIKIT_DLL



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "DatabaseKit.h"


namespace VCF {

    class DATABASEUIKIT_API DatabaseUIKit {
    public:
        static void init( int argc, char **argv );

        static void terminate();
    };

};

#endif
