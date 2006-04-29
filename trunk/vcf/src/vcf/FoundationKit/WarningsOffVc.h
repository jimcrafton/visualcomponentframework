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


//Visual Studio .NET
// '<' : signed/unsigned mismatch
	#pragma warning ( disable : 4018 )

// unary minus operator applied to unsigned type, result still unsigned
	#pragma warning ( disable : 4146 )

// '=' : conversion from 'const double' to 'long', possible loss of data
	#pragma warning ( disable : 4244 )

// nonstandard extension used : 'i' : loop control variable declared in the for-loop is used outside the for-loop scope; it conflicts with the declaration in the outer scope
	#pragma warning ( disable : 4288 )

// C++ exception specification ignored except to indicate a function is not __declspec(nothrow) - not implemented yet in 7.0
#pragma warning ( disable : 4290 )


#endif // _VCF_WARNINGSOFFVC_H__

/**
$Id$
*/
