//VCFTime.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VCFTime.h"

#ifdef VCF_WIN32CE
#undef	time
#define time		_time64
struct tm _tmbuf;
#endif

namespace VCF {

time_t vcftime( time_t *timer )
{
	time_t result = 0;
	result = ::time( timer );

	return result;
}

struct tm* vcflocaltime( const time_t *timer )
{
#ifndef VCF_WIN32CE
	return ::localtime( timer );
#else
	 int err = _localtime64_s(&_tmbuf, timer);
	 return &_tmbuf;
#endif
}

};
