#ifndef _VCF_VCFULONG64_H__
#define _VCF_VCFULONG64_H__
//VCFulong64.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\typedef ulong64 VCFulong64.h "vcf/FoundationKit/VCFulong64.h"
Unsigned 64 bit integer type
*/
#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
	typedef unsigned __int64 ulong64;
#else
	typedef unsigned long long ulong64;
#endif


/**
\typedef long64 VCFulong64.h "vcf/FoundationKit/VCFulong64.h"
Signed 64 bit integer type
*/
#if defined(VCF_MSC) || defined(VCF_BCC) || defined(VCF_ICL)
	typedef __int64 long64;
#else
	typedef long long long64;
#endif


/**
\def VCF_LIT64 VCFulong64.h "vcf/FoundationKit/VCFulong64.h"
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
inline ulong32 getHi32(ulong64 val){
	return (ulong32)(val>>32);
}


/**
This returns the top 32 bits of the number
*/
inline long32 getHi32(long64 val){
	return (long32)(val>>32);
}


/**
This returns the low 32 bits of the number
*/
inline ulong32 getLo32(ulong64 val){
	return (ulong32)val;
}


/**
This returns the low 32 bits of the number
*/
inline ulong32 getLo32(long64 val){
	return (ulong32)val;
}





/**
This sets the top 32 bits of the number to the specified
value.
*/
inline void setHi32(ulong64& val,ulong32 hi){
	val = (val & 0xffffffff) | (((ulong64)hi)<<32);
}


/**
This sets the top 32 bits of the number to the specified
value.
*/
inline void setHi32(long64& val,long32 hi){
	val = (val & 0xffffffff) | (((long64)hi)<<32);
}



/**
This sets the low 32 bits of the number to the specified
value.
*/
inline void setLo32(ulong64& val,ulong32 lo){
	val = (val & VCF_LIT64(0xffffffff00000000)) | lo;
}

/**
This sets the low 32 bits of the number to the specified
value.
*/
inline void setLo32(long64& val,ulong32 lo){
	val = (val & VCF_LIT64(0xffffffff00000000)) | lo;
}



/**
Creates an unsigned 64 bit integer from the
high and low 32 bit.*/
inline ulong64 makeULong64(ulong32 hi,ulong32 lo){
	return (((ulong64)hi)<<32) | lo;
}


/**
Creates a signed 64 bit integer from the
high and low 32 bit.*/
inline long64 makeLong64(long32 hi,ulong32 lo){
	return (((long64)hi)<<32) | lo;
}


};// end of namespace


#endif // _VCF_VCFULONG64_H__

/**
$Id$
*/
