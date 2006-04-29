#ifndef _VCF_VCF_H__
#define _VCF_VCF_H__
//VCF.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*Common headers
*Common defines for basic types
*/


#include "vcf/FoundationKit/FrameworkConfig.h"

namespace VCF {

	typedef char           int8;
	typedef short          int16;
	typedef int            int32;
	typedef long           long32;
	typedef unsigned char  uchar;
	typedef unsigned short ushort;
	typedef unsigned char  uint8;
	typedef unsigned short uint16;
	typedef unsigned int   uint32;
	typedef unsigned long  ulong32;

	/**
	This is used as a wrapper around some platform
	object or handle. 
	*/
	typedef void*			OSHandleID;
};


#endif // _VCF_VCF_H__

/**
$Id$
*/
