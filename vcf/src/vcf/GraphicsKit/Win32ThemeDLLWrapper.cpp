/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2001-2002 by David Yuheng Zhao
//
// Distribute and change freely, except: don't remove my name from the source 
//
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Partly based on the _ThemeHelper struct in MFC7.0 source code (winctrl3.cpp), 
// and the difference is that this implementation wraps the full set of 
// visual style APIs from the platform SDK August 2001
//
// If you have any questions, I can be reached as follows:
//	yuheng_zhao@yahoo.com
//
/////////////////////////////////////////////////////////////////////////////

#ifdef WINTHEMES

#include "Win32ThemeDLLWrapper.h"

namespace VCF
{
	Win32ThemeDLLWrapper::Win32ThemeDLLWrapper(void)
	{
		m_hThemeDll = LoadLibrary(_T("UxTheme.dll"));
		if (m_hThemeDll==0)
		{
			DWORD err=GetLastError();

			LPVOID lpMsgBuf;
			::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				err,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0,NULL);
			::MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
			::LocalFree( lpMsgBuf );
		}
	}

	Win32ThemeDLLWrapper::~Win32ThemeDLLWrapper(void)
	{
		if (m_hThemeDll!=NULL)
			FreeLibrary(m_hThemeDll);
		m_hThemeDll = NULL;
	}

	void* Win32ThemeDLLWrapper::GetProc(LPCSTR szProc, void* pfnFail)
	{
		void* pRet = pfnFail;
		if (m_hThemeDll != NULL)
			pRet = GetProcAddress(m_hThemeDll, szProc);
		return pRet;
	}

	HTHEME Win32ThemeDLLWrapper::OpenThemeData(HWND hwnd, LPCWSTR pszClassList)
	{
		PFNOPENTHEMEDATA pfnOpenThemeData = (PFNOPENTHEMEDATA)GetProc("OpenThemeData", (void*)OpenThemeDataFail);
		return (*pfnOpenThemeData)(hwnd, pszClassList);
	}

	HRESULT Win32ThemeDLLWrapper::CloseThemeData(HTHEME hTheme)
	{
		PFNCLOSETHEMEDATA pfnCloseThemeData = (PFNCLOSETHEMEDATA)GetProc("CloseThemeData", (void*)CloseThemeDataFail);
		return (*pfnCloseThemeData)(hTheme);
	}

	HRESULT Win32ThemeDLLWrapper::DrawThemeBackground(HTHEME hTheme, HDC hdc, 
												int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect)
	{
		PFNDRAWTHEMEBACKGROUND pfnDrawThemeBackground = 
			(PFNDRAWTHEMEBACKGROUND)GetProc("DrawThemeBackground", (void*)DrawThemeBackgroundFail);
		return (*pfnDrawThemeBackground)(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
	}


	HRESULT Win32ThemeDLLWrapper::DrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, 
										int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, 
										DWORD dwTextFlags2, const RECT *pRect)
	{
		PFNDRAWTHEMETEXT pfn = (PFNDRAWTHEMETEXT)GetProc("DrawThemeText", (void*)DrawThemeTextFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwTextFlags, dwTextFlags2, pRect);
	}
	HRESULT Win32ThemeDLLWrapper::GetThemeBackgroundContentRect(HTHEME hTheme,  HDC hdc, 
														int iPartId, int iStateId,  const RECT *pBoundingRect, 
														RECT *pContentRect)
	{
		PFNGETTHEMEBACKGROUNDCONTENTRECT pfn = (PFNGETTHEMEBACKGROUNDCONTENTRECT)GetProc("GetThemeBackgroundContentRect", (void*)GetThemeBackgroundContentRectFail);
		return (*pfn)(hTheme,  hdc, iPartId, iStateId,  pBoundingRect, pContentRect);
	}
	HRESULT Win32ThemeDLLWrapper::GetThemeBackgroundExtent(HTHEME hTheme,  HDC hdc,
													int iPartId, int iStateId, const RECT *pContentRect, 
													RECT *pExtentRect)
	{
		PFNGETTHEMEBACKGROUNDEXTENT pfn = (PFNGETTHEMEBACKGROUNDEXTENT)GetProc("GetThemeBackgroundExtent", (void*)GetThemeBackgroundExtentFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, pContentRect, pExtentRect);
	}
	HRESULT Win32ThemeDLLWrapper::GetThemePartSize(HTHEME hTheme, HDC hdc, 
											int iPartId, int iStateId, RECT * pRect, enum THEMESIZE eSize, SIZE *psz)
	{
		PFNGETTHEMEPARTSIZE pfnGetThemePartSize = 
			(PFNGETTHEMEPARTSIZE)GetProc("GetThemePartSize", (void*)GetThemePartSizeFail);
		return (*pfnGetThemePartSize)(hTheme, hdc, iPartId, iStateId, pRect, eSize, psz);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeTextExtent(HTHEME hTheme, HDC hdc, 
												int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
												DWORD dwTextFlags,  const RECT *pBoundingRect, 
												RECT *pExtentRect)
	{
		PFNGETTHEMETEXTEXTENT pfn = (PFNGETTHEMETEXTEXTENT)GetProc("GetThemeTextExtent", (void*)GetThemeTextExtentFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwTextFlags,  pBoundingRect, pExtentRect);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeTextMetrics(HTHEME hTheme,  HDC hdc, 
												int iPartId, int iStateId,  TEXTMETRIC* ptm)
	{
		PFNGETTHEMETEXTMETRICS pfn = (PFNGETTHEMETEXTMETRICS)GetProc("GetThemeTextMetrics", (void*)GetThemeTextMetricsFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId,  ptm);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeBackgroundRegion(HTHEME hTheme,  HDC hdc,  
													int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion)
	{
		PFNGETTHEMEBACKGROUNDREGION pfn = (PFNGETTHEMEBACKGROUNDREGION)GetProc("GetThemeBackgroundRegion", (void*)GetThemeBackgroundRegionFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, pRect, pRegion);
	}

	HRESULT Win32ThemeDLLWrapper::HitTestThemeBackground(HTHEME hTheme,  HDC hdc, int iPartId, 
													int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
													POINT ptTest,  WORD *pwHitTestCode)
	{
		PFNHITTESTTHEMEBACKGROUND pfn = (PFNHITTESTTHEMEBACKGROUND)GetProc("HitTestThemeBackground", (void*)HitTestThemeBackgroundFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, dwOptions, pRect, hrgn, ptTest, pwHitTestCode);
	}

	HRESULT Win32ThemeDLLWrapper::DrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
										const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect)
	{
		PFNDRAWTHEMEEDGE pfn = (PFNDRAWTHEMEEDGE)GetProc("DrawThemeEdge", (void*)DrawThemeEdgeFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, pDestRect, uEdge, uFlags, pContentRect);
	}

	HRESULT Win32ThemeDLLWrapper::DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, 
										int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
	{
		PFNDRAWTHEMEICON pfn = (PFNDRAWTHEMEICON)GetProc("DrawThemeIcon", (void*)DrawThemeIconFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, pRect, himl, iImageIndex);
	}

	BOOL Win32ThemeDLLWrapper::IsThemePartDefined(HTHEME hTheme, int iPartId, 
											int iStateId)
	{
		PFNISTHEMEPARTDEFINED pfn = (PFNISTHEMEPARTDEFINED)GetProc("IsThemePartDefined", (void*)IsThemePartDefinedFail);
		return (*pfn)(hTheme, iPartId, iStateId);
	}

	BOOL Win32ThemeDLLWrapper::IsThemeBackgroundPartiallyTransparent(HTHEME hTheme, 
																int iPartId, int iStateId)
	{
		PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT pfn = (PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT)GetProc("IsThemeBackgroundPartiallyTransparent", (void*)IsThemeBackgroundPartiallyTransparentFail);
		return (*pfn)(hTheme, iPartId, iStateId);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeColor(HTHEME hTheme, int iPartId, 
										int iStateId, int iPropId,  COLORREF *pColor)
	{
		PFNGETTHEMECOLOR pfn = (PFNGETTHEMECOLOR)GetProc("GetThemeColor", (void*)GetThemeColorFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pColor);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeMetric(HTHEME hTheme,  HDC hdc, int iPartId, 
											int iStateId, int iPropId,  int *piVal)
	{
		PFNGETTHEMEMETRIC pfn = (PFNGETTHEMEMETRIC)GetProc("GetThemeMetric", (void*)GetThemeMetricFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, iPropId, piVal);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeString(HTHEME hTheme, int iPartId, 
											int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars)
	{
		PFNGETTHEMESTRING pfn = (PFNGETTHEMESTRING)GetProc("GetThemeString", (void*)GetThemeStringFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pszBuff, cchMaxBuffChars);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeBool(HTHEME hTheme, int iPartId, 
										int iStateId, int iPropId,  BOOL *pfVal)
	{
		PFNGETTHEMEBOOL pfn = (PFNGETTHEMEBOOL)GetProc("GetThemeBool", (void*)GetThemeBoolFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pfVal);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeInt(HTHEME hTheme, int iPartId, 
										int iStateId, int iPropId,  int *piVal)
	{
		PFNGETTHEMEINT pfn = (PFNGETTHEMEINT)GetProc("GetThemeInt", (void*)GetThemeIntFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, piVal);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeEnumValue(HTHEME hTheme, int iPartId, 
											int iStateId, int iPropId,  int *piVal)
	{
		PFNGETTHEMEENUMVALUE pfn = (PFNGETTHEMEENUMVALUE)GetProc("GetThemeEnumValue", (void*)GetThemeEnumValueFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, piVal);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemePosition(HTHEME hTheme, int iPartId, 
											int iStateId, int iPropId,  POINT *pPoint)
	{
		PFNGETTHEMEPOSITION pfn = (PFNGETTHEMEPOSITION)GetProc("GetThemePosition", (void*)GetThemePositionFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pPoint);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeFont(HTHEME hTheme,  HDC hdc, int iPartId, 
										int iStateId, int iPropId,  LOGFONT *pFont)
	{
		PFNGETTHEMEFONT pfn = (PFNGETTHEMEFONT)GetProc("GetThemeFont", (void*)GetThemeFontFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, iPropId, pFont);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeRect(HTHEME hTheme, int iPartId, 
										int iStateId, int iPropId,  RECT *pRect)
	{
		PFNGETTHEMERECT pfn = (PFNGETTHEMERECT)GetProc("GetThemeRect", (void*)GetThemeRectFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pRect);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeMargins(HTHEME hTheme,  HDC hdc, int iPartId, 
											int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins)
	{
		PFNGETTHEMEMARGINS pfn = (PFNGETTHEMEMARGINS)GetProc("GetThemeMargins", (void*)GetThemeMarginsFail);
		return (*pfn)(hTheme, hdc, iPartId, iStateId, iPropId, prc, pMargins);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeIntList(HTHEME hTheme, int iPartId, 
											int iStateId, int iPropId,  INTLIST *pIntList)
	{
		PFNGETTHEMEINTLIST pfn = (PFNGETTHEMEINTLIST)GetProc("GetThemeIntList", (void*)GetThemeIntListFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pIntList);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemePropertyOrigin(HTHEME hTheme, int iPartId, 
													int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin)
	{
		PFNGETTHEMEPROPERTYORIGIN pfn = (PFNGETTHEMEPROPERTYORIGIN)GetProc("GetThemePropertyOrigin", (void*)GetThemePropertyOriginFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId, pOrigin);
	}

	HRESULT Win32ThemeDLLWrapper::SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, 
											LPCWSTR pszSubIdList)
	{
		PFNSETWINDOWTHEME pfn = (PFNSETWINDOWTHEME)GetProc("SetWindowTheme", (void*)SetWindowThemeFail);
		return (*pfn)(hwnd, pszSubAppName, pszSubIdList);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeFilename(HTHEME hTheme, int iPartId, 
											int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars)
	{
		PFNGETTHEMEFILENAME pfn = (PFNGETTHEMEFILENAME)GetProc("GetThemeFilename", (void*)GetThemeFilenameFail);
		return (*pfn)(hTheme, iPartId, iStateId, iPropId,  pszThemeFileName, cchMaxBuffChars);
	}

	COLORREF Win32ThemeDLLWrapper::GetThemeSysColor(HTHEME hTheme, int iColorId)
	{
		PFNGETTHEMESYSCOLOR pfn = (PFNGETTHEMESYSCOLOR)GetProc("GetThemeSysColor", (void*)GetThemeSysColorFail);
		return (*pfn)(hTheme, iColorId);
	}

	HBRUSH Win32ThemeDLLWrapper::GetThemeSysColorBrush(HTHEME hTheme, int iColorId)
	{
		PFNGETTHEMESYSCOLORBRUSH pfn = (PFNGETTHEMESYSCOLORBRUSH)GetProc("GetThemeSysColorBrush", (void*)GetThemeSysColorBrushFail);
		return (*pfn)(hTheme, iColorId);
	}

	BOOL Win32ThemeDLLWrapper::GetThemeSysBool(HTHEME hTheme, int iBoolId)
	{
		PFNGETTHEMESYSBOOL pfn = (PFNGETTHEMESYSBOOL)GetProc("GetThemeSysBool", (void*)GetThemeSysBoolFail);
		return (*pfn)(hTheme, iBoolId);
	}

	int Win32ThemeDLLWrapper::GetThemeSysSize(HTHEME hTheme, int iSizeId)
	{
		PFNGETTHEMESYSSIZE pfn = (PFNGETTHEMESYSSIZE)GetProc("GetThemeSysSize", (void*)GetThemeSysSizeFail);
		return (*pfn)(hTheme, iSizeId);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeSysFont(HTHEME hTheme, int iFontId,  LOGFONT *plf)
	{
		PFNGETTHEMESYSFONT pfn = (PFNGETTHEMESYSFONT)GetProc("GetThemeSysFont", (void*)GetThemeSysFontFail);
		return (*pfn)(hTheme, iFontId, plf);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeSysString(HTHEME hTheme, int iStringId, 
											LPWSTR pszStringBuff, int cchMaxStringChars)
	{
		PFNGETTHEMESYSSTRING pfn = (PFNGETTHEMESYSSTRING)GetProc("GetThemeSysString", (void*)GetThemeSysStringFail);
		return (*pfn)(hTheme, iStringId, pszStringBuff, cchMaxStringChars);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue)
	{
		PFNGETTHEMESYSINT pfn = (PFNGETTHEMESYSINT)GetProc("GetThemeSysInt", (void*)GetThemeSysIntFail);
		return (*pfn)(hTheme, iIntId, piValue);
	}

	BOOL Win32ThemeDLLWrapper::IsThemeActive()
	{
		PFNISTHEMEACTIVE pfn = (PFNISTHEMEACTIVE)GetProc("IsThemeActive", (void*)IsThemeActiveFail);
		return (*pfn)();
	}

	BOOL Win32ThemeDLLWrapper::IsAppThemed()
	{
		PFNISAPPTHEMED pfnIsAppThemed = (PFNISAPPTHEMED)GetProc("IsAppThemed", (void*)IsAppThemedFail);
		return (*pfnIsAppThemed)();
	}

	HTHEME Win32ThemeDLLWrapper::GetWindowTheme(HWND hwnd)
	{
		PFNGETWINDOWTHEME pfn = (PFNGETWINDOWTHEME)GetProc("GetWindowTheme", (void*)GetWindowThemeFail);
		return (*pfn)(hwnd);
	}

	HRESULT Win32ThemeDLLWrapper::EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags)
	{
		PFNENABLETHEMEDIALOGTEXTURE pfn = (PFNENABLETHEMEDIALOGTEXTURE)GetProc("EnableThemeDialogTexture", (void*)EnableThemeDialogTextureFail);
		return (*pfn)(hwnd, dwFlags);
	}

	BOOL Win32ThemeDLLWrapper::IsThemeDialogTextureEnabled(HWND hwnd)
	{
		PFNISTHEMEDIALOGTEXTUREENABLED pfn = (PFNISTHEMEDIALOGTEXTUREENABLED)GetProc("IsThemeDialogTextureEnabled", (void*)IsThemeDialogTextureEnabledFail);
		return (*pfn)(hwnd);
	}

	DWORD Win32ThemeDLLWrapper::GetThemeAppProperties()
	{
		PFNGETTHEMEAPPPROPERTIES pfn = (PFNGETTHEMEAPPPROPERTIES)GetProc("GetThemeAppProperties", (void*)GetThemeAppPropertiesFail);
		return (*pfn)();
	}

	void Win32ThemeDLLWrapper::SetThemeAppProperties(DWORD dwFlags)
	{
		PFNSETTHEMEAPPPROPERTIES pfn = (PFNSETTHEMEAPPPROPERTIES)GetProc("SetThemeAppProperties", (void*)SetThemeAppPropertiesFail);
		(*pfn)(dwFlags);
	}

	HRESULT Win32ThemeDLLWrapper::GetCurrentThemeName(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars)
	{
		PFNGETCURRENTTHEMENAME pfn = (PFNGETCURRENTTHEMENAME)GetProc("GetCurrentThemeName", (void*)GetCurrentThemeNameFail);
		return (*pfn)(pszThemeFileName, cchMaxNameChars, pszColorBuff, cchMaxColorChars, pszSizeBuff, cchMaxSizeChars);
	}

	HRESULT Win32ThemeDLLWrapper::GetThemeDocumentationProperty(LPCWSTR pszThemeName,
														LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars)
	{
		PFNGETTHEMEDOCUMENTATIONPROPERTY pfn = (PFNGETTHEMEDOCUMENTATIONPROPERTY)GetProc("GetThemeDocumentationProperty", (void*)GetThemeDocumentationPropertyFail);
		return (*pfn)(pszThemeName, pszPropertyName, pszValueBuff, cchMaxValChars);
	}


	HRESULT Win32ThemeDLLWrapper::DrawThemeParentBackground(HWND hwnd, HDC hdc,  RECT* prc)
	{
		PFNDRAWTHEMEPARENTBACKGROUND pfn = (PFNDRAWTHEMEPARENTBACKGROUND)GetProc("DrawThemeParentBackground", (void*)DrawThemeParentBackgroundFail);
		return (*pfn)(hwnd, hdc, prc);
	}

	HRESULT Win32ThemeDLLWrapper::EnableTheming(BOOL fEnable)
	{
		PFNENABLETHEMING pfn = (PFNENABLETHEMING)GetProc("EnableTheming", (void*)EnableThemingFail);
		return (*pfn)(fEnable);
	}
}

#endif	// WINTHEMES


