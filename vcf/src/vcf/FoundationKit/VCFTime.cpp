//VCFTime.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VCFTime.h"

namespace VCF {

time_t vcftime( time_t *timer )
{
	time_t result = 0;
#ifndef VCF_WIN32CE
	result = ::time( timer );
#else
				
#endif
	return result;
}

struct tm* vcflocaltime( const time_t *timer )
{
#ifndef VCF_WIN32CE
	return ::localtime( timer );
#else
	static struct tm result;

	return &result;
#endif
}

};
