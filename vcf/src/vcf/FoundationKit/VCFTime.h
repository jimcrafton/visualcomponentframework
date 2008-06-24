#ifndef _VCF_VCFTIME_H__
#define _VCF_VCFTIME_H__
//VCFTime.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef VCF_WIN32CE
#include <time.h>
#endif

namespace VCF {

time_t vcftime( time_t *timer );

struct tm* vcflocaltime( const time_t *timer );

};


#endif //_VCF_VCFTIME_H__