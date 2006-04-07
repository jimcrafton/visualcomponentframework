#ifndef _VCF_VCFMATH_H__
#define _VCF_VCFMATH_H__
//VCFMath.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#ifndef M_PI
	#define M_PI	3.1415926535897932384626433832795
#endif
/**
\class Math VCFMath.h "vcf/FoundationKit/VCFMath.h"
*/
class FOUNDATIONKIT_API Math {

public:
	Math();

	virtual ~Math();

	/**
	*returns the radian value of theta, where theta is in degrees
	*/
	static double degreesToRadians( const double& theta ){
		return (M_PI * theta) / 180.0;
	}

	/**
	*returns the degee value of theta, where theta is in radians
	*/
	static double radiansToDegrees( const double& theta ){
		return (180.0 * theta) / M_PI;
	}

	static double Pi(){
		return M_PI;
	}

};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/12 22:01:41  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.26.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VCFMATH_H__


