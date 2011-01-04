#ifndef _WIN32_DTUTILS_H__
#define _WIN32_DTUTILS_H__


#ifdef WIN32

#define MIN_DATE                (-657434L)  // about year 100
#define MAX_DATE                2958465L    // about year 9999
#define HALF_SECOND  (1.0/172800.0)

extern int monthDays[];

#endif

bool DateTimeFromOleDate(DATE dtSrc, VCF::DateTime& dtDest );
bool OleDateFromDateTime( const VCF::DateTime& srcDt, DATE& dtDest);

#endif //_WIN32_DTUTILS_H__