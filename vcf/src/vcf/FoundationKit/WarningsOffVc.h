#ifndef _VCF_WARNINGSOFFVC_H__
#define _VCF_WARNINGSOFFVC_H__
//WarningsOffVc.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

//disable warnings on 255 char debug symbols
#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
#pragma warning (disable : 4231)

//'identifier' : decorated name length exceeded, name was truncated
#pragma warning (disable:4503)

//disable C++ Exception Specification ignored
#pragma warning (disable : 4290)



//Visual Studio .NET
// '<' : signed/unsigned mismatch
#pragma warning ( disable : 4018 )

// unary minus operator applied to unsigned type, result still unsigned
#pragma warning ( disable : 4146 )

// '=' : conversion from 'const double' to 'long', possible loss of data
#pragma warning ( disable : 4244 )

// nonstandard extension used : 'i' : loop control variable declared 
// in the for-loop is used outside the for-loop scope; 
// it conflicts with the declaration in the outer scope
#pragma warning ( disable : 4288 )

// C++ exception specification ignored except to indicate 
// a function is not __declspec(nothrow) - not implemented yet in 7.0
#pragma warning ( disable : 4290 )



#if defined(VCF_VC80) || defined(VCF_VC90)  || defined(VCF_VC100)
	#pragma message ( "VC8, VC9 or VC100 compiler detected - deprecation warnings turned off for now." )
	#pragma warning (disable : 4996)
    #ifndef _CRT_SECURE_NO_DEPRECATE
	    #define _CRT_SECURE_NO_DEPRECATE 1
    #endif
    #ifndef _CRT_NONSTDC_NO_DEPRECATE
        #define _CRT_NONSTDC_NO_DEPRECATE 1
    #endif
	#pragma message ( "_CRT_SECURE_NO_DEPRECATE turned on for now." )
#endif //VCF_VC80 || VCF_VC90

#if ( _MSC_VER < 1300 )
	//disable warning on base class not declared with the __declspec(dllexport) keyword
	#pragma warning (disable : 4251)

	//disable warning on exported class derived from a class that was not exported.
	#pragma warning (disable : 4275)
#endif //_MSC_VER < 1300  

#endif // _VCF_WARNINGSOFFVC_H__

/**
$Id$
*/
