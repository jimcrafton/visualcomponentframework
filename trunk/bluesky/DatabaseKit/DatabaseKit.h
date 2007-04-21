#ifndef _VCF_DATABASEKIT_H__
#define _VCF_DATABASEKIT_H__

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
	#define DBKIT_LIBDLL	"DatabaseKit_"_LIB_CPLVERNUM"_d.lib"
	#define DBKIT_LIBS	"DatabaseKit_"_LIB_CPLVERNUM"_sd.lib"
#else
	#define DBKIT_LIBDLL	"DatabaseKit_"_LIB_CPLVERNUM".lib"
	#define DBKIT_LIBS	"DatabaseKit_"_LIB_CPLVERNUM"_s.lib"
#endif



//auto link stuff
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_DATABASEKIT_DLL
		#pragma message( "linking to " DBKIT_LIBDLL )
		#define DATABASEKIT_DLL
		// using dynamic link library		
		#pragma comment(lib, DBKIT_LIBDLL)
	#elif defined USE_DATABASEKIT_LIB
		#pragma message( "linking to " DBKIT_LIBS )
		// using statically linked library
		#pragma comment(lib, DBKIT_LIBS)
	#endif

#endif //VCF_MSC





//this sets up a "dependencies" set of defines

#ifdef USE_DATABASEKIT_DLL
# 	ifndef DATABASEKIT_DLL
#		define DATABASEKIT_DLL
# 	endif
#elif defined (USE_DATABASEKIT_LIB)
# 	ifndef DATABASEKIT_LIB
#		define DATABASEKIT_LIB
# 	endif
#endif

#ifdef DATABASEKIT_DLL
# 	ifndef USE_FOUNDATIONKIT_DLL
#		define USE_FOUNDATIONKIT_DLL
# 	endif
#elif defined (DATABASEKIT_LIB)
# 	ifndef USE_FOUNDATIONKIT_LIB
#		define USE_FOUNDATIONKIT_LIB
# 	endif
#endif


#endif // VCF_DISABLE_PRAGMA_LINKING

//export crap
#ifdef DATABASEKIT_DLL
	#if defined(DATABASEKIT_EXPORTS)
		#define DATABASEKIT_API __declspec(dllexport)
	#else
		#define DATABASEKIT_API __declspec(dllimport)
	#endif
#else
	#define DATABASEKIT_API
#endif //DATABASEKIT_DLL



#include "vcf/FoundationKit/FoundationKit.h"


namespace VCF {

	template <typename ContainerT, typename ValueT>
	class EnumImpl : public EnumeratorContainer< ContainerT,ValueT > {
	public:
		typedef ContainerT Container;
		
		inline EnumImpl(){
			initContainer( container );
		}
		
		inline operator Container& () {
			return container;
		}

		inline operator const Container& () const {
			return container;
		}

		inline Container& operator () () {
			return container;
		}

		inline const Container& operator () () const {
			return container;
		}

		Container* operator->() {
			return &container;
		}

		Container container;
	};

	template <typename ValueT>
	class VectorEnum : public EnumImpl< std::vector<ValueT>,ValueT > {
	public:
		typedef Container Vector;		
	};

};



#include "DatabaseToolkit.h"
#include "Database.h"
#include "DatabaseError.h"
#include "DataSet.h"
#include "Transaction.h"
#include "StringList.h"
#include "FieldDefinitions.h"
#include "DataField.h"
#include "DataSource.h"


//DB providers...
/*
#include "FBTransaction.h"
#include "FBDataSet.h"
#include "SQLiteDatabase.h"
#include "FBDatabase.h"
*/




/**
\dir
The Database Kit is the VCF's library for accessing data, be it
a formal database like MS Sql Server, MySQL, or SQLite, or 
some other record based format. 

Most of the core ideas and design
for the Database Kit were inspired by studying the Delphi VCL's 
database classes.

The Database Kit uses some terms that may throw people off. The 
reason for this is that the Database Kit wraps any kind of record 
based data, not \em just SQL databases. For example, a file that
consists of an array of structs might have a wrapper that allows
access to it though the Database Kit. Let's quickly define the
terms we use here:

||Term || Definition
|Field | equivalent to a column in a table. 
|Record | equivalent to a row. A record is made of 1 
or more fields

*/


namespace VCF {

	/**
	\class DatabaseKit DatabaseKit.h "vcf/DatabaseKit/DatabaseKit.h"
	This is the toolkit for the DatabaseKit library. You'll need to 
	initialize it \em before using any classes from the DatabaseKit
	library, and terminate it when you're done. For example:
	\code
	int main( int argc, char** argv )
	{
		DatabaseKit::init( argc, argv );
		
		//rest of your code goes here....
	
		DatabaseKit::terminate();
		return 0;
	}
	\endcode
	*/
    class DATABASEKIT_API DatabaseKit {
    public:
		/**
		Called to initialize the DatabaseKit library.
		*/
        static void init( int argc, char **argv );

		/**
		Called to terminate the DatabaseKit library and 
		destroy/release any global resources used by the kit.
		*/
        static void terminate();
    };

};

#endif
