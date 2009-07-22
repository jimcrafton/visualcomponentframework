#include "vcf/OSCompatKit/OSCompatKit.h"

#include <stdlib.h>

UINT
WINAPI
RegisterWindowMessageA(
    LPCSTR lpString)
{
	int nRet = 0;
	LPWSTR lpWideCharStr = NULL;

	if (!lpString)
		return 0;

	// We allocate on stack
	lpWideCharStr = (LPWSTR)_alloca(MAX_PATH * sizeof(WCHAR));
	if (lpWideCharStr) 
	{
		lpWideCharStr[0] = 0;
		nRet = MultiByteToWideChar(CP_ACP, 0, lpString, -1, lpWideCharStr, MAX_PATH);
		if (nRet > 0)
			nRet = RegisterWindowMessageW(lpWideCharStr);
	}
	return nRet;
}


HANDLE
WINAPI
CopyImage(
    __in HANDLE hbm,
    __in UINT type,
    __in int cx,
    __in int cy,
    __in UINT flags)
{
	if ((!hbm) || (type != IMAGE_BITMAP))
		return NULL;

	 // Get dimensions of bitmap
    BITMAP bm;
    if(!GetObject(hbm, sizeof(bm), &bm))
        return NULL;
	
	if (cx == 0)
		cx = bm.bmWidth;
	if (cy == 0)
		cy = bm.bmHeight;

	HDC hdcSrc = CreateCompatibleDC(NULL);
	HDC hdcDst = CreateCompatibleDC(NULL);
	HBITMAP hbmOld, hbmOld2, hbmNew;
	hbmOld = (HBITMAP)SelectObject(hdcSrc, hbm);
	hbmNew = CreateBitmap( cx, cy, bm.bmPlanes,
		bm.bmBitsPixel, NULL);
	hbmOld2 = (HBITMAP)SelectObject(hdcDst, hbmNew);
	StretchBlt(hdcDst, 0, 0, cx, cy, hdcSrc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	SelectObject(hdcSrc, hbmOld);
	DeleteDC(hdcSrc);
	DeleteDC(hdcDst);
	return hbmNew;
}

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