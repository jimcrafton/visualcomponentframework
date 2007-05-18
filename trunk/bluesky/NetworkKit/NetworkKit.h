#ifndef _VCF_NETWORKKIT_H__
#define _VCF_NETWORKKIT_H__

//NetworkKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



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
	#define NETWORKKIT_LIBDLL	"NetworkKit_"_LIB_CPLVERNUM"_d.lib"
	#define NETWORKKIT_LIBS	"NetworkKit_"_LIB_CPLVERNUM"_sd.lib"
#else
	#define NETWORKKIT_LIBDLL	"NetworkKit_"_LIB_CPLVERNUM".lib"
	#define NETWORKKIT_LIBS	"NetworkKit_"_LIB_CPLVERNUM"_s.lib"
#endif



//auto link stuff
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_NETWORKKIT_DLL
		#pragma message( "linking to " NETWORKKIT_LIBDLL )
		#define DATABASEKIT_DLL
		// using dynamic link library		
		#pragma comment(lib, NETWORKKIT_LIBDLL)
	#elif defined USE_NETWORKKIT_LIB
		#pragma message( "linking to " NETWORKKIT_LIBS )
		// using statically linked library
		#pragma comment(lib, NETWORKKIT_LIBS)
	#endif

#endif //VCF_MSC





//this sets up a "dependencies" set of defines
//if you are using the regex kit, then it only makes 
//sense that you are ALSO using the FoundationKit.
//the following takes care of defining these for you.

#ifdef USE_NETWORKKIT_DLL
# 	ifndef NETWORKKIT_DLL
#		define NETWORKKIT_DLL
# 	endif
# 	ifndef USE_FOUNDATIONKIT_DLL
#		define USE_FOUNDATIONKIT_DLL
# 	endif
#elif defined (USE_NETWORKKIT_LIB)
//#		define ONIG_EXTERN extern
# 	ifndef USE_FOUNDATIONKIT_LIB
#		define USE_FOUNDATIONKIT_LIB
# 	endif
#endif



//export crap
#ifdef NETWORKKIT_DLL
	#if defined(NETWORKKIT_EXPORTS)
		#define NETWORKKIT_API __declspec(dllexport)
	#else
		#define NETWORKKIT_API __declspec(dllimport)
	#endif
#else
	#define NETWORKKIT_API
#endif //DATABASEKIT_DLL



#include <winsock2.h>
#pragma comment( lib, "ws2_32" )

#include "vcf/FoundationKit/FoundationKit.h"







namespace VCF {
	class NETWORKKIT_API NetworkKit {
	public:
		static void init( int argc, char **argv );

        static void terminate();
	};




	class NETWORKKIT_API NetworkException : public BasicException {
	public:		
		NetworkException( const String & message ):
			BasicException( message ){};

		NetworkException():
			BasicException( "Unknown Network Exception occurred." ){};
			
		NetworkException( const String & message, int lineNumber ):
			BasicException(message, lineNumber){};
			
		virtual ~NetworkException() throw() {};
	};
};



#endif //_VCF_NETWORKKIT_H__