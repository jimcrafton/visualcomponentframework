//[!output PROJECT_NAME].cpp
#include "vcf/ApplicationKit/ApplicationKit.h"

#include "[!output PROJECT_NAME].h"

using namespace VCF;

#define [!output UPPER_CASE_PROJECT_NAME]PACKAGEUUID "[!output VPL_UUID]"


class [!output PROJECT_NAME]Package : public PackageInfo {
public:
	[!output PROJECT_NAME]Package() : PackageInfo(
								"[!output PROJECT_NAME]",
								[!output UPPER_CASE_PROJECT_NAME]PACKAGEUUID,
								"",
								"[!output PROJECT_NAME].vpl",
								PackageInfo::lfSharedLibLinkage,
								"[!output AUTHOR]",
								"[!output COMPANY]",
								"[!output COPYRIGHT]",
								""){

	}
};



extern "C" [!output UPPER_CASE_PROJECT_NAME]_API void initPackage()
{

}


