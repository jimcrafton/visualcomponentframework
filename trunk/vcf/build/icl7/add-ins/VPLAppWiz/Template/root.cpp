//$$root$$.cpp
#include "ApplicationKit.h"


#include $$ROOT_INCLUDE$$

using namespace VCF;


#define $$ROOT$$PACKAGEUUID		"$$PKG_UUID$$"


class $$Root$$Package : public PackageInfo {
public:
	$$Root$$Package() : PackageInfo(
								"$$Root$$", 
								$$ROOT$$PACKAGEUUID,
								"",
								"$$Root$$.vpl",
								PackageInfo::lfSharedLibLinkage,
								"$$AUTHOR$$",
								"$$COMPANY$$",
								"$$COPYRIGHT$$",
								"$$ADDTL$$"){

	}
};



extern "C" $$ROOT_$$_API void initPackage()
{
	
}


