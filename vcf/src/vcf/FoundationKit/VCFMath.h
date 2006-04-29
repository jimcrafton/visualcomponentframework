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


#endif // _VCF_VCFMATH_H__

/**
$Id$
*/
