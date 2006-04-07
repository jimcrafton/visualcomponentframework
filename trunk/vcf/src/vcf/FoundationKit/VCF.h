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


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2006/02/19 06:50:31  ddiego
*minor updates.
*
*Revision 1.4  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.2  2005/06/11 00:50:50  marcelloptr
*moved uint8/uint16 to VCF namespace
*
*Revision 1.2.4.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.20.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.10  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VCF_H__


