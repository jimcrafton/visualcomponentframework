#include "vcf/OSCompatKit/OSCompatKit.h"


int
WINAPI
GetCalendarInfoW(
    __in LCID     Locale,
    __in CALID    Calendar,
    __in CALTYPE  CalType,
    __out_ecount_opt(cchData) LPWSTR   lpCalData,
    __in int      cchData,
    __out_opt LPDWORD  lpValue)
{

	return 0;
}

BOOL
WINAPI
DestroyCursor(
    __in HCURSOR hCursor)
{
	// Doesn't exist on wince
	return TRUE;
}

void abort(void)
{
	/* No return */
    TerminateProcess(GetCurrentProcess(), 0);
}