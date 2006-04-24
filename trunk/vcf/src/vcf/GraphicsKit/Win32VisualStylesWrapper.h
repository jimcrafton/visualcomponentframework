#ifndef _VCF_WIN32VISUALSTYLESWRAPPER_H__
#define _VCF_WIN32VISUALSTYLESWRAPPER_H__

//Win32VisualStylesWrapper.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#if _MSC_VER > 1000
#   pragma once
#endif


#include "thirdparty/win32/Microsoft/uxtheme.h"
#include "thirdparty/win32/Microsoft/tmschema.h"

/**
Based on the class CVisualStylesXP by David Yuheng Zhao.
His original copyright notice:

Copyright (C) 2001-2002 by David Yuheng Zhao

Distribute and change freely, except: don't remove my name from the source

No warrantee of any kind, express or implied, is included with this
software; use at your own risk, responsibility for damages (if any) to
anyone resulting from the use of this software rests entirely with the
user.

Partly based on the _ThemeHelper struct in MFC7.0 source code (winctrl3.cpp),
and the difference is that this implementation wraps the full set of
visual style APIs from the platform SDK August 2001

If you have any questions, I can be reached as follows:
	yuheng_zhao@yahoo.com

Changes made by Jim Crafton to make things fit in better with VCF existing code
and to make it easier to read/understand what's going on.
*/

class GRAPHICSKIT_API Win32VisualStylesWrapper {
private:
	typedef HTHEME(__stdcall *PFNOPENTHEMEDATA)(HWND hwnd, LPCWSTR pszClassList);
	typedef HRESULT(__stdcall *PFNCLOSETHEMEDATA)(HTHEME hTheme);
	typedef HRESULT(__stdcall *PFNDRAWTHEMEBACKGROUND)(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, const RECT *pRect,  const RECT *pClipRect);
	typedef HRESULT (__stdcall *PFNDRAWTHEMETEXT)(HTHEME hTheme, HDC hdc, int iPartId,
		int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags,
		DWORD dwTextFlags2, const RECT *pRect);
	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDCONTENTRECT)(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId,  const RECT *pBoundingRect,
		RECT *pContentRect);
	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDEXTENT)(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect,
		RECT *pExtentRect);
	typedef HRESULT(__stdcall *PFNGETTHEMEPARTSIZE)(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, RECT * pRect, THEMESIZE eSize,  SIZE *psz);
	typedef HRESULT (__stdcall *PFNGETTHEMETEXTEXTENT)(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount,
		DWORD dwTextFlags,  const RECT *pBoundingRect,
		RECT *pExtentRect);
	typedef HRESULT (__stdcall *PFNGETTHEMETEXTMETRICS)(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId,  TEXTMETRIC* ptm);
	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDREGION)(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion);
	typedef HRESULT (__stdcall *PFNHITTESTTHEMEBACKGROUND)(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn,
		POINT ptTest,  WORD *pwHitTestCode);
	typedef HRESULT (__stdcall *PFNDRAWTHEMEEDGE)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	typedef HRESULT (__stdcall *PFNDRAWTHEMEICON)(HTHEME hTheme, HDC hdc, int iPartId,
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
	typedef BOOL (__stdcall *PFNISTHEMEPARTDEFINED)(HTHEME hTheme, int iPartId,
		int iStateId);
	typedef BOOL (__stdcall *PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT)(HTHEME hTheme,
		int iPartId, int iStateId);
	typedef HRESULT (__stdcall *PFNGETTHEMECOLOR)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  COLORREF *pColor);
	typedef HRESULT (__stdcall *PFNGETTHEMEMETRIC)(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  int *piVal);
	typedef HRESULT (__stdcall *PFNGETTHEMESTRING)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars);
	typedef HRESULT (__stdcall *PFNGETTHEMEBOOL)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  BOOL *pfVal);
	typedef HRESULT (__stdcall *PFNGETTHEMEINT)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  int *piVal);
	typedef HRESULT (__stdcall *PFNGETTHEMEENUMVALUE)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  int *piVal);
	typedef HRESULT (__stdcall *PFNGETTHEMEPOSITION)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  POINT *pPoint);
	typedef HRESULT (__stdcall *PFNGETTHEMEFONT)(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  LOGFONT *pFont);
	typedef HRESULT (__stdcall *PFNGETTHEMERECT)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  RECT *pRect);
	typedef HRESULT (__stdcall *PFNGETTHEMEMARGINS)(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins);
	typedef HRESULT (__stdcall *PFNGETTHEMEINTLIST)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  INTLIST *pIntList);
	typedef HRESULT (__stdcall *PFNGETTHEMEPROPERTYORIGIN)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId, PROPERTYORIGIN *pOrigin);
	typedef HRESULT (__stdcall *PFNSETWINDOWTHEME)(HWND hwnd, LPCWSTR pszSubAppName,
		LPCWSTR pszSubIdList);
	typedef HRESULT (__stdcall *PFNGETTHEMEFILENAME)(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars);
	typedef COLORREF (__stdcall *PFNGETTHEMESYSCOLOR)(HTHEME hTheme, int iColorId);
	typedef HBRUSH (__stdcall *PFNGETTHEMESYSCOLORBRUSH)(HTHEME hTheme, int iColorId);
	typedef BOOL (__stdcall *PFNGETTHEMESYSBOOL)(HTHEME hTheme, int iBoolId);
	typedef int (__stdcall *PFNGETTHEMESYSSIZE)(HTHEME hTheme, int iSizeId);
	typedef HRESULT (__stdcall *PFNGETTHEMESYSFONT)(HTHEME hTheme, int iFontId,  LOGFONT *plf);
	typedef HRESULT (__stdcall *PFNGETTHEMESYSSTRING)(HTHEME hTheme, int iStringId,
		LPWSTR pszStringBuff, int cchMaxStringChars);
	typedef HRESULT (__stdcall *PFNGETTHEMESYSINT)(HTHEME hTheme, int iIntId, int *piValue);
	typedef BOOL (__stdcall *PFNISTHEMEACTIVE)();
	typedef BOOL(__stdcall *PFNISAPPTHEMED)();
	typedef HTHEME (__stdcall *PFNGETWINDOWTHEME)(HWND hwnd);
	typedef HRESULT (__stdcall *PFNENABLETHEMEDIALOGTEXTURE)(HWND hwnd, DWORD dwFlags);
	typedef BOOL (__stdcall *PFNISTHEMEDIALOGTEXTUREENABLED)(HWND hwnd);
	typedef DWORD (__stdcall *PFNGETTHEMEAPPPROPERTIES)();
	typedef void (__stdcall *PFNSETTHEMEAPPPROPERTIES)(DWORD dwFlags);
	typedef HRESULT (__stdcall *PFNGETCURRENTTHEMENAME)(
		LPWSTR pszThemeFileName, int cchMaxNameChars,
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars);
	typedef HRESULT (__stdcall *PFNGETTHEMEDOCUMENTATIONPROPERTY)(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars);
	typedef HRESULT (__stdcall *PFNDRAWTHEMEPARENTBACKGROUND)(HWND hwnd, HDC hdc,  RECT* prc);
	typedef HRESULT (__stdcall *PFNENABLETHEMING)(BOOL fEnable);

private:
	struct ThemeFuncs {
		PFNOPENTHEMEDATA openThemeDataFunc;
		PFNCLOSETHEMEDATA closeThemeDataFunc;
		PFNDRAWTHEMEBACKGROUND drawThemeBackgroundFunc;
		PFNDRAWTHEMETEXT drawThemeTextFunc;
		PFNGETTHEMEBACKGROUNDCONTENTRECT getThemeBackgroundContentRectFunc;
		PFNGETTHEMEBACKGROUNDEXTENT getThemeBackgroundExtentFunc;
		PFNGETTHEMEPARTSIZE getThemePartSizeFunc;
		PFNGETTHEMETEXTEXTENT getThemeTextExtentFunc;
		PFNGETTHEMETEXTMETRICS getThemeTextMetricsFunc;
		PFNGETTHEMEBACKGROUNDREGION getThemeBackgroundRegionFunc;
		PFNHITTESTTHEMEBACKGROUND hitTestThemeBackgroundFunc;
		PFNDRAWTHEMEEDGE drawThemeEdgeFunc;
		PFNDRAWTHEMEICON drawThemeIconFunc;
		PFNISTHEMEPARTDEFINED isThemePartDefinedFunc;
		PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT isThemeBackgroundPartiallyTransparentFunc;
		PFNGETTHEMECOLOR getThemeColorFunc;
		PFNGETTHEMEMETRIC getThemeMetricFunc;
		PFNGETTHEMESTRING getThemeStringFunc;
		PFNGETTHEMEBOOL getThemeBoolFunc;
		PFNGETTHEMEINT getThemeIntFunc;
		PFNGETTHEMEENUMVALUE getThemeEnumValueFunc;
		PFNGETTHEMEPOSITION getThemePositionFunc;
		PFNGETTHEMEFONT getThemeFontFunc;
		PFNGETTHEMERECT getThemeRectFunc;
		PFNGETTHEMEMARGINS getThemeMarginsFunc;
		PFNGETTHEMEINTLIST getThemeIntListFunc;
		PFNGETTHEMEPROPERTYORIGIN getThemePropertyOriginFunc;
		PFNSETWINDOWTHEME setWindowThemeFunc;
		PFNGETTHEMEFILENAME getThemeFilenameFunc;
		PFNGETTHEMESYSCOLOR getThemeSysColorFunc;
		PFNGETTHEMESYSCOLORBRUSH getThemeSysColorBrushFunc;
		PFNGETTHEMESYSBOOL getThemeSysBoolFunc;
		PFNGETTHEMESYSSIZE getThemeSysSizeFunc;
		PFNGETTHEMESYSFONT getThemeSysFontFunc;
		PFNGETTHEMESYSSTRING getThemeSysStringFunc;
		PFNGETTHEMESYSINT getThemeSysIntFunc;
		PFNISTHEMEACTIVE isThemeActiveFunc;
		PFNISAPPTHEMED isAppThemedFunc;
		PFNGETWINDOWTHEME getWindowThemeFunc;
		PFNENABLETHEMEDIALOGTEXTURE enableThemeDialogTextureFunc;
		PFNISTHEMEDIALOGTEXTUREENABLED isThemeDialogTextureEnabledFunc;
		PFNGETTHEMEAPPPROPERTIES getThemeAppPropertiesFunc;
		PFNSETTHEMEAPPPROPERTIES setThemeAppPropertiesFunc;
		PFNGETCURRENTTHEMENAME getCurrentThemeNameFunc;
		PFNGETTHEMEDOCUMENTATIONPROPERTY getThemeDocumentationPropertyFunc;
		PFNDRAWTHEMEPARENTBACKGROUND drawThemeParentBackgroundFunc;
		PFNENABLETHEMING enableThemingFunc;
	};




	static HTHEME OpenThemeDataFail(HWND , LPCWSTR )
	{return NULL;}


	static HRESULT CloseThemeDataFail(HTHEME)
	{return E_FAIL;}


	static HRESULT DrawThemeBackgroundFail(HTHEME, HDC, int, int, const RECT *, const RECT *)
	{return E_FAIL;}


	static HRESULT DrawThemeTextFail(HTHEME, HDC, int, int, LPCWSTR, int, DWORD, DWORD, const RECT*)
	{return E_FAIL;}


	static HRESULT GetThemeBackgroundContentRectFail(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId,  const RECT *pBoundingRect,
		RECT *pContentRect)
	{return E_FAIL;}

	static HRESULT GetThemeBackgroundExtentFail(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect,
		RECT *pExtentRect)
	{return E_FAIL;}


	static HRESULT GetThemePartSizeFail(HTHEME, HDC, int, int, RECT *, THEMESIZE, SIZE *)
	{return E_FAIL;}


	static HRESULT GetThemeTextExtentFail(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount,
		DWORD dwTextFlags,  const RECT *pBoundingRect,
		RECT *pExtentRect)
	{return E_FAIL;}


	static HRESULT GetThemeTextMetricsFail(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId,  TEXTMETRIC* ptm)
	{return E_FAIL;}


	static HRESULT GetThemeBackgroundRegionFail(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion)
	{return E_FAIL;}


	static HRESULT HitTestThemeBackgroundFail(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn,
		POINT ptTest,  WORD *pwHitTestCode)
	{return E_FAIL;}


	static HRESULT DrawThemeEdgeFail(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect)
	{return E_FAIL;}


	static HRESULT DrawThemeIconFail(HTHEME hTheme, HDC hdc, int iPartId,
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
	{return E_FAIL;}


	static BOOL IsThemePartDefinedFail(HTHEME hTheme, int iPartId,
		int iStateId)
	{return FALSE;}


	static BOOL IsThemeBackgroundPartiallyTransparentFail(HTHEME hTheme,
		int iPartId, int iStateId)
	{return FALSE;}


	static HRESULT GetThemeColorFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  COLORREF *pColor)
	{return E_FAIL;}


	static HRESULT GetThemeMetricFail(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}


	static HRESULT GetThemeStringFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars)
	{return E_FAIL;}


	static HRESULT GetThemeBoolFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  BOOL *pfVal)
	{return E_FAIL;}


	static HRESULT GetThemeIntFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}


	static HRESULT GetThemeEnumValueFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}


	static HRESULT GetThemePositionFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  POINT *pPoint)
	{return E_FAIL;}


	static HRESULT GetThemeFontFail(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  LOGFONT *pFont)
	{return E_FAIL;}


	static HRESULT GetThemeRectFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  RECT *pRect)
	{return E_FAIL;}


	static HRESULT GetThemeMarginsFail(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins)
	{return E_FAIL;}


	static HRESULT GetThemeIntListFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  INTLIST *pIntList)
	{return E_FAIL;}


	static HRESULT GetThemePropertyOriginFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId, PROPERTYORIGIN *pOrigin)
	{return E_FAIL;}


	static HRESULT SetWindowThemeFail(HWND hwnd, LPCWSTR pszSubAppName,
		LPCWSTR pszSubIdList)
	{return E_FAIL;}


	static HRESULT GetThemeFilenameFail(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars)
	{return E_FAIL;}


	static COLORREF GetThemeSysColorFail(HTHEME hTheme, int iColorId)
	{return RGB(255,255,255);}


	static HBRUSH GetThemeSysColorBrushFail(HTHEME hTheme, int iColorId)
	{return NULL;}


	static BOOL GetThemeSysBoolFail(HTHEME hTheme, int iBoolId)
	{return FALSE;}


	static int GetThemeSysSizeFail(HTHEME hTheme, int iSizeId)
	{return 0;}


	static HRESULT GetThemeSysFontFail(HTHEME hTheme, int iFontId,  LOGFONT *plf)
	{return E_FAIL;}


	static HRESULT GetThemeSysStringFail(HTHEME hTheme, int iStringId,
		LPWSTR pszStringBuff, int cchMaxStringChars)
	{return E_FAIL;}


	static HRESULT GetThemeSysIntFail(HTHEME hTheme, int iIntId, int *piValue)
	{return E_FAIL;}


	static BOOL IsThemeActiveFail()
	{return FALSE;}


	static BOOL IsAppThemedFail()
	{return FALSE;}


	static HTHEME GetWindowThemeFail(HWND hwnd)
	{return NULL;}


	static HRESULT EnableThemeDialogTextureFail(HWND hwnd, DWORD dwFlags)
	{return E_FAIL;}


	static BOOL IsThemeDialogTextureEnabledFail(HWND hwnd)
	{return FALSE;}


	static DWORD GetThemeAppPropertiesFail()
	{return 0;}


	static void SetThemeAppPropertiesFail(DWORD dwFlags)
	{return;}


	static HRESULT GetCurrentThemeNameFail(
		LPWSTR pszThemeFileName, int cchMaxNameChars,
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars)
	{return E_FAIL;}


	static HRESULT GetThemeDocumentationPropertyFail(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars)
	{return E_FAIL;}


	static HRESULT DrawThemeParentBackgroundFail(HWND hwnd, HDC hdc,  RECT* prc)
	{return E_FAIL;}


	static HRESULT EnableThemingFail(BOOL fEnable)
	{return E_FAIL;}


	HMODULE themeDllHandle_;
	FARPROC getProc( LPCSTR szProcName, FARPROC failFunction) {
		FARPROC result = failFunction;
		if (themeDllHandle_ != NULL)
			result = ::GetProcAddress(themeDllHandle_, szProcName);
		return result;
	}

	ThemeFuncs funcs_;
protected:
	static Win32VisualStylesWrapper Instance;
public:
	Win32VisualStylesWrapper(): themeDllHandle_(NULL) {
		themeDllHandle_ = ::LoadLibrary( "UxTheme.dll" );

		memset( &funcs_, 0, sizeof(funcs_) );
	}

	~Win32VisualStylesWrapper() {

		if (themeDllHandle_!=NULL) {
			::FreeLibrary(themeDllHandle_);
		}
		themeDllHandle_ = NULL;
	}



	static HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList)
	{
		if ( NULL == Instance.funcs_.openThemeDataFunc ) {
			Instance.funcs_.openThemeDataFunc = (PFNOPENTHEMEDATA)Instance.getProc("OpenThemeData", (FARPROC)OpenThemeDataFail);
		}
		return (*Instance.funcs_.openThemeDataFunc)(hwnd, pszClassList);
	}

	static HRESULT CloseThemeData(HTHEME hTheme)
	{
		if ( NULL == Instance.funcs_.closeThemeDataFunc ) {
			Instance.funcs_.closeThemeDataFunc = (PFNCLOSETHEMEDATA)Instance.getProc("CloseThemeData", (FARPROC)CloseThemeDataFail);
		}
		return (*Instance.funcs_.closeThemeDataFunc)(hTheme);
	}

	static HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect)
	{
		if ( NULL == Instance.funcs_.drawThemeBackgroundFunc ) {
			Instance.funcs_.drawThemeBackgroundFunc =
			(PFNDRAWTHEMEBACKGROUND)Instance.getProc("DrawThemeBackground", (FARPROC)DrawThemeBackgroundFail);
		}


		return (*Instance.funcs_.drawThemeBackgroundFunc)(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
	}


	static HRESULT DrawThemeText(HTHEME hTheme, HDC hdc, int iPartId,
		int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags,
		DWORD dwTextFlags2, const RECT *pRect)
	{
		if ( NULL == Instance.funcs_.drawThemeTextFunc ) {
			Instance.funcs_.drawThemeTextFunc = (PFNDRAWTHEMETEXT)Instance.getProc("DrawThemeText", (FARPROC)DrawThemeTextFail);
		}

		return (*Instance.funcs_.drawThemeTextFunc)(hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwTextFlags, dwTextFlags2, pRect);
	}

	static HRESULT GetThemeBackgroundContentRect(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId,  const RECT *pBoundingRect,
		RECT *pContentRect)
	{
		if ( NULL == Instance.funcs_.getThemeBackgroundContentRectFunc ) {
			Instance.funcs_.getThemeBackgroundContentRectFunc = (PFNGETTHEMEBACKGROUNDCONTENTRECT)Instance.getProc("GetThemeBackgroundContentRect", (FARPROC)GetThemeBackgroundContentRectFail);
		}
		return (*Instance.funcs_.getThemeBackgroundContentRectFunc)(hTheme,  hdc, iPartId, iStateId,  pBoundingRect, pContentRect);
	}

	static HRESULT GetThemeBackgroundExtent(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect,
		RECT *pExtentRect)
	{
		if ( NULL == Instance.funcs_.getThemeBackgroundExtentFunc ) {
			Instance.funcs_.getThemeBackgroundExtentFunc = (PFNGETTHEMEBACKGROUNDEXTENT)Instance.getProc("GetThemeBackgroundExtent", (FARPROC)GetThemeBackgroundExtentFail);
		}
		return (*Instance.funcs_.getThemeBackgroundExtentFunc)(hTheme, hdc, iPartId, iStateId, pContentRect, pExtentRect);
	}

	static HRESULT GetThemePartSize(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, RECT * pRect, THEMESIZE eSize, SIZE *psz)
	{
		if ( NULL == Instance.funcs_.getThemePartSizeFunc ) {
			Instance.funcs_.getThemePartSizeFunc =
				(PFNGETTHEMEPARTSIZE)Instance.getProc("GetThemePartSize", (FARPROC)GetThemePartSizeFail);
		}
		return (*Instance.funcs_.getThemePartSizeFunc)(hTheme, hdc, iPartId, iStateId, pRect, eSize, psz);
	}

	static HRESULT GetThemeTextExtent(HTHEME hTheme, HDC hdc,
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount,
		DWORD dwTextFlags,  const RECT *pBoundingRect,
		RECT *pExtentRect)
	{
		if ( NULL == Instance.funcs_.getThemeTextExtentFunc ) {
			Instance.funcs_.getThemeTextExtentFunc = (PFNGETTHEMETEXTEXTENT)Instance.getProc("GetThemeTextExtent", (FARPROC)GetThemeTextExtentFail);
		}
		return (*Instance.funcs_.getThemeTextExtentFunc)(hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwTextFlags,  pBoundingRect, pExtentRect);
	}

	static HRESULT GetThemeTextMetrics(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId,  TEXTMETRIC* ptm)
	{
		if ( NULL == Instance.funcs_.getThemeTextMetricsFunc ) {
			Instance.funcs_.getThemeTextMetricsFunc = (PFNGETTHEMETEXTMETRICS)Instance.getProc("GetThemeTextMetrics", (FARPROC)GetThemeTextMetricsFail);
		}
		return (*Instance.funcs_.getThemeTextMetricsFunc)(hTheme, hdc, iPartId, iStateId,  ptm);
	}

	static HRESULT GetThemeBackgroundRegion(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion)
	{
		if ( NULL == Instance.funcs_.getThemeBackgroundRegionFunc ) {
			Instance.funcs_.getThemeBackgroundRegionFunc = (PFNGETTHEMEBACKGROUNDREGION)Instance.getProc("GetThemeBackgroundRegion", (FARPROC)GetThemeBackgroundRegionFail);
		}
		return (*Instance.funcs_.getThemeBackgroundRegionFunc)(hTheme, hdc, iPartId, iStateId, pRect, pRegion);
	}

	static HRESULT HitTestThemeBackground(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn,
		POINT ptTest,  WORD *pwHitTestCode)
	{
		if ( NULL == Instance.funcs_.hitTestThemeBackgroundFunc ) {
			Instance.funcs_.hitTestThemeBackgroundFunc = (PFNHITTESTTHEMEBACKGROUND)Instance.getProc("HitTestThemeBackground", (FARPROC)HitTestThemeBackgroundFail);
		}
		return (*Instance.funcs_.hitTestThemeBackgroundFunc)(hTheme, hdc, iPartId, iStateId, dwOptions, pRect, hrgn, ptTest, pwHitTestCode);
	}

	static HRESULT DrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect)
	{
		if ( NULL == Instance.funcs_.drawThemeEdgeFunc ) {
			Instance.funcs_.drawThemeEdgeFunc = (PFNDRAWTHEMEEDGE)Instance.getProc("DrawThemeEdge", (FARPROC)DrawThemeEdgeFail);
		}
		return (*Instance.funcs_.drawThemeEdgeFunc)(hTheme, hdc, iPartId, iStateId, pDestRect, uEdge, uFlags, pContentRect);
	}

	static HRESULT DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId,
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
	{
		if ( NULL == Instance.funcs_.drawThemeIconFunc ) {
			Instance.funcs_.drawThemeIconFunc = (PFNDRAWTHEMEICON)Instance.getProc("DrawThemeIcon", (FARPROC)DrawThemeIconFail);
		}
		return (*Instance.funcs_.drawThemeIconFunc)(hTheme, hdc, iPartId, iStateId, pRect, himl, iImageIndex);
	}

	static BOOL IsThemePartDefined(HTHEME hTheme, int iPartId,
		int iStateId)
	{
		if ( NULL == Instance.funcs_.isThemePartDefinedFunc ) {
			Instance.funcs_.isThemePartDefinedFunc = (PFNISTHEMEPARTDEFINED)Instance.getProc("IsThemePartDefined", (FARPROC)IsThemePartDefinedFail);
		}
		return (*Instance.funcs_.isThemePartDefinedFunc)(hTheme, iPartId, iStateId);
	}

	static BOOL IsThemeBackgroundPartiallyTransparent(HTHEME hTheme,
		int iPartId, int iStateId)
	{
		if ( NULL == Instance.funcs_.isThemeBackgroundPartiallyTransparentFunc ) {
			Instance.funcs_.isThemeBackgroundPartiallyTransparentFunc = (PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT)Instance.getProc("IsThemeBackgroundPartiallyTransparent", (FARPROC)IsThemeBackgroundPartiallyTransparentFail);
		}
		return (*Instance.funcs_.isThemeBackgroundPartiallyTransparentFunc)(hTheme, iPartId, iStateId);
	}

	static HRESULT GetThemeColor(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  COLORREF *pColor)
	{
		if ( NULL == Instance.funcs_.getThemeColorFunc ) {
			Instance.funcs_.getThemeColorFunc = (PFNGETTHEMECOLOR)Instance.getProc("GetThemeColor", (FARPROC)GetThemeColorFail);
		}
		return (*Instance.funcs_.getThemeColorFunc)(hTheme, iPartId, iStateId, iPropId, pColor);
	}

	static HRESULT GetThemeMetric(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  int *piVal)
	{
		if ( NULL == Instance.funcs_.getThemeMetricFunc ) {
			Instance.funcs_.getThemeMetricFunc = (PFNGETTHEMEMETRIC)Instance.getProc("GetThemeMetric", (FARPROC)GetThemeMetricFail);
		}
		return (*Instance.funcs_.getThemeMetricFunc)(hTheme, hdc, iPartId, iStateId, iPropId, piVal);
	}

	static HRESULT GetThemeString(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars)
	{
		if ( NULL == Instance.funcs_.getThemeStringFunc ) {
			Instance.funcs_.getThemeStringFunc = (PFNGETTHEMESTRING)Instance.getProc("GetThemeString", (FARPROC)GetThemeStringFail);
		}
		return (*Instance.funcs_.getThemeStringFunc)(hTheme, iPartId, iStateId, iPropId, pszBuff, cchMaxBuffChars);
	}

	static HRESULT GetThemeBool(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  BOOL *pfVal)
	{
		if ( NULL == Instance.funcs_.getThemeBoolFunc ) {
			Instance.funcs_.getThemeBoolFunc = (PFNGETTHEMEBOOL)Instance.getProc("GetThemeBool", (FARPROC)GetThemeBoolFail);
		}
		return (*Instance.funcs_.getThemeBoolFunc)(hTheme, iPartId, iStateId, iPropId, pfVal);
	}

	static HRESULT GetThemeInt(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  int *piVal)
	{
		if ( NULL == Instance.funcs_.getThemeIntFunc ) {
			Instance.funcs_.getThemeIntFunc = (PFNGETTHEMEINT)Instance.getProc("GetThemeInt", (FARPROC)GetThemeIntFail);
		}
		return (*Instance.funcs_.getThemeIntFunc)(hTheme, iPartId, iStateId, iPropId, piVal);
	}

	static HRESULT GetThemeEnumValue(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  int *piVal)
	{
		if ( NULL == Instance.funcs_.getThemeEnumValueFunc ) {
			Instance.funcs_.getThemeEnumValueFunc = (PFNGETTHEMEENUMVALUE)Instance.getProc("GetThemeEnumValue", (FARPROC)GetThemeEnumValueFail);
		}
		return (*Instance.funcs_.getThemeEnumValueFunc)(hTheme, iPartId, iStateId, iPropId, piVal);
	}

	static HRESULT GetThemePosition(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  POINT *pPoint)
	{
		if ( NULL == Instance.funcs_.getThemePositionFunc ) {
			Instance.funcs_.getThemePositionFunc = (PFNGETTHEMEPOSITION)Instance.getProc("GetThemePosition", (FARPROC)GetThemePositionFail);
		}
		return (*Instance.funcs_.getThemePositionFunc)(hTheme, iPartId, iStateId, iPropId, pPoint);
	}

	static HRESULT GetThemeFont(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  LOGFONT *pFont)
	{
		if ( NULL == Instance.funcs_.getThemeFontFunc ) {
			Instance.funcs_.getThemeFontFunc = (PFNGETTHEMEFONT)Instance.getProc("GetThemeFont", (FARPROC)GetThemeFontFail);
		}
		return (*Instance.funcs_.getThemeFontFunc)(hTheme, hdc, iPartId, iStateId, iPropId, pFont);
	}

	static HRESULT GetThemeRect(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  RECT *pRect)
	{
		if ( NULL == Instance.funcs_.getThemeRectFunc ) {
			Instance.funcs_.getThemeRectFunc = (PFNGETTHEMERECT)Instance.getProc("GetThemeRect", (FARPROC)GetThemeRectFail);
		}
		return (*Instance.funcs_.getThemeRectFunc)(hTheme, iPartId, iStateId, iPropId, pRect);
	}

	static HRESULT GetThemeMargins(HTHEME hTheme,  HDC hdc, int iPartId,
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins)
	{
		if ( NULL == Instance.funcs_.getThemeMarginsFunc ) {
			Instance.funcs_.getThemeMarginsFunc = (PFNGETTHEMEMARGINS)Instance.getProc("GetThemeMargins", (FARPROC)GetThemeMarginsFail);
		}
		return (*Instance.funcs_.getThemeMarginsFunc)(hTheme, hdc, iPartId, iStateId, iPropId, prc, pMargins);
	}

	static HRESULT GetThemeIntList(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  INTLIST *pIntList)
	{
		if ( NULL == Instance.funcs_.getThemeIntListFunc ) {
			Instance.funcs_.getThemeIntListFunc = (PFNGETTHEMEINTLIST)Instance.getProc("GetThemeIntList", (FARPROC)GetThemeIntListFail);
		}
		return (*Instance.funcs_.getThemeIntListFunc)(hTheme, iPartId, iStateId, iPropId, pIntList);
	}

	static HRESULT GetThemePropertyOrigin(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId, PROPERTYORIGIN *pOrigin)
	{
		if ( NULL == Instance.funcs_.getThemePropertyOriginFunc ) {
			Instance.funcs_.getThemePropertyOriginFunc = (PFNGETTHEMEPROPERTYORIGIN)Instance.getProc("GetThemePropertyOrigin", (FARPROC)GetThemePropertyOriginFail);
		}
		return (*Instance.funcs_.getThemePropertyOriginFunc)(hTheme, iPartId, iStateId, iPropId, pOrigin);
	}

	static HRESULT SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName,
		LPCWSTR pszSubIdList)
	{
		if ( NULL == Instance.funcs_.setWindowThemeFunc ) {
			Instance.funcs_.setWindowThemeFunc = (PFNSETWINDOWTHEME)Instance.getProc("SetWindowTheme", (FARPROC)SetWindowThemeFail);
		}
		return (*Instance.funcs_.setWindowThemeFunc)(hwnd, pszSubAppName, pszSubIdList);
	}

	static HRESULT GetThemeFilename(HTHEME hTheme, int iPartId,
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars)
	{
		if ( NULL == Instance.funcs_.getThemeFilenameFunc ) {
			Instance.funcs_.getThemeFilenameFunc = (PFNGETTHEMEFILENAME)Instance.getProc("GetThemeFilename", (FARPROC)GetThemeFilenameFail);
		}
		return (*Instance.funcs_.getThemeFilenameFunc)(hTheme, iPartId, iStateId, iPropId,  pszThemeFileName, cchMaxBuffChars);
	}

	static COLORREF GetThemeSysColor(HTHEME hTheme, int iColorId)
	{
		if ( NULL == Instance.funcs_.getThemeSysColorFunc ) {
			Instance.funcs_.getThemeSysColorFunc = (PFNGETTHEMESYSCOLOR)Instance.getProc("GetThemeSysColor", (FARPROC)GetThemeSysColorFail);
		}
		return (*Instance.funcs_.getThemeSysColorFunc)(hTheme, iColorId);
	}

	static HBRUSH GetThemeSysColorBrush(HTHEME hTheme, int iColorId)
	{
		if ( NULL == Instance.funcs_.getThemeSysColorBrushFunc ) {
			Instance.funcs_.getThemeSysColorBrushFunc = (PFNGETTHEMESYSCOLORBRUSH)Instance.getProc("GetThemeSysColorBrush", (FARPROC)GetThemeSysColorBrushFail);
		}
		return (*Instance.funcs_.getThemeSysColorBrushFunc)(hTheme, iColorId);
	}

	static BOOL GetThemeSysBool(HTHEME hTheme, int iBoolId)
	{
		if ( NULL == Instance.funcs_.getThemeSysBoolFunc ) {
			 Instance.funcs_.getThemeSysBoolFunc = (PFNGETTHEMESYSBOOL)Instance.getProc("GetThemeSysBool", (FARPROC)GetThemeSysBoolFail);
		}
		return (* Instance.funcs_.getThemeSysBoolFunc)(hTheme, iBoolId);
	}

	static int GetThemeSysSize(HTHEME hTheme, int iSizeId)
	{
		if ( NULL == Instance.funcs_.getThemeSysSizeFunc ) {
			Instance.funcs_.getThemeSysSizeFunc = (PFNGETTHEMESYSSIZE)Instance.getProc("GetThemeSysSize", (FARPROC)GetThemeSysSizeFail);
		}
		return (*Instance.funcs_.getThemeSysSizeFunc)(hTheme, iSizeId);
	}

	static HRESULT GetThemeSysFont(HTHEME hTheme, int iFontId,  LOGFONT *plf)
	{
		if ( NULL == Instance.funcs_.getThemeSysFontFunc ) {
			Instance.funcs_.getThemeSysFontFunc = (PFNGETTHEMESYSFONT)Instance.getProc("GetThemeSysFont", (FARPROC)GetThemeSysFontFail);
		}
		return (*Instance.funcs_.getThemeSysFontFunc)(hTheme, iFontId, plf);
	}

	static HRESULT GetThemeSysString(HTHEME hTheme, int iStringId,
		LPWSTR pszStringBuff, int cchMaxStringChars)
	{
		if ( NULL == Instance.funcs_.getThemeSysStringFunc ) {
			Instance.funcs_.getThemeSysStringFunc = (PFNGETTHEMESYSSTRING)Instance.getProc("GetThemeSysString", (FARPROC)GetThemeSysStringFail);
		}
		return (*Instance.funcs_.getThemeSysStringFunc)(hTheme, iStringId, pszStringBuff, cchMaxStringChars);
	}

	static HRESULT GetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue)
	{
		if ( NULL == Instance.funcs_.getThemeSysIntFunc ) {
			 Instance.funcs_.getThemeSysIntFunc = (PFNGETTHEMESYSINT)Instance.getProc("GetThemeSysInt", (FARPROC)GetThemeSysIntFail);
		}
		return (*Instance.funcs_.getThemeSysIntFunc)(hTheme, iIntId, piValue);
	}

	static BOOL IsThemeActive()
	{
		if ( NULL == Instance.funcs_.isThemeActiveFunc ) {
			Instance.funcs_.isThemeActiveFunc = (PFNISTHEMEACTIVE)Instance.getProc("IsThemeActive", (FARPROC)IsThemeActiveFail);
		}
		return (*Instance.funcs_.isThemeActiveFunc)();
	}

	static BOOL IsAppThemed()
	{
		if ( NULL == Instance.funcs_.isAppThemedFunc ) {
			Instance.funcs_.isAppThemedFunc = (PFNISAPPTHEMED)Instance.getProc("IsAppThemed", (FARPROC)IsAppThemedFail);
		}
		return (*Instance.funcs_.isAppThemedFunc)();
	}

	static HTHEME GetWindowTheme(HWND hwnd)
	{
		if ( NULL == Instance.funcs_.getWindowThemeFunc ) {
			 Instance.funcs_.getWindowThemeFunc = (PFNGETWINDOWTHEME)Instance.getProc("GetWindowTheme", (FARPROC)GetWindowThemeFail);
		}
		return (* Instance.funcs_.getWindowThemeFunc)(hwnd);
	}

	static HRESULT EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags)
	{
		if ( NULL == Instance.funcs_.enableThemeDialogTextureFunc ) {
			Instance.funcs_.enableThemeDialogTextureFunc = (PFNENABLETHEMEDIALOGTEXTURE)Instance.getProc("EnableThemeDialogTexture", (FARPROC)EnableThemeDialogTextureFail);
		}
		return (*Instance.funcs_.enableThemeDialogTextureFunc)(hwnd, dwFlags);
	}

	static BOOL IsThemeDialogTextureEnabled(HWND hwnd)
	{
		if ( NULL == Instance.funcs_.isThemeDialogTextureEnabledFunc ) {
			Instance.funcs_.isThemeDialogTextureEnabledFunc = (PFNISTHEMEDIALOGTEXTUREENABLED)Instance.getProc("IsThemeDialogTextureEnabled", (FARPROC)IsThemeDialogTextureEnabledFail);
		}
		return (*Instance.funcs_.isThemeDialogTextureEnabledFunc)(hwnd);
	}

	static DWORD GetThemeAppProperties()
	{
		if ( NULL == Instance.funcs_.getThemeAppPropertiesFunc ) {
			Instance.funcs_.getThemeAppPropertiesFunc = (PFNGETTHEMEAPPPROPERTIES)Instance.getProc("GetThemeAppProperties", (FARPROC)GetThemeAppPropertiesFail);
		}
		return (*Instance.funcs_.getThemeAppPropertiesFunc)();
	}

	static void SetThemeAppProperties(DWORD dwFlags)
	{
		if ( NULL == Instance.funcs_.setThemeAppPropertiesFunc ) {
			Instance.funcs_.setThemeAppPropertiesFunc = (PFNSETTHEMEAPPPROPERTIES)Instance.getProc("SetThemeAppProperties", (FARPROC)SetThemeAppPropertiesFail);
		}
		(*Instance.funcs_.setThemeAppPropertiesFunc)(dwFlags);
	}

	static HRESULT GetCurrentThemeName(
		LPWSTR pszThemeFileName, int cchMaxNameChars,
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars)
	{
		if ( NULL == Instance.funcs_.getCurrentThemeNameFunc ) {
			Instance.funcs_.getCurrentThemeNameFunc = (PFNGETCURRENTTHEMENAME)Instance.getProc("GetCurrentThemeName", (FARPROC)GetCurrentThemeNameFail);
		}
		return (*Instance.funcs_.getCurrentThemeNameFunc)(pszThemeFileName, cchMaxNameChars, pszColorBuff, cchMaxColorChars, pszSizeBuff, cchMaxSizeChars);
	}

	static HRESULT GetThemeDocumentationProperty(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars)
	{
		if ( NULL == Instance.funcs_.getThemeDocumentationPropertyFunc ) {
			Instance.funcs_.getThemeDocumentationPropertyFunc = (PFNGETTHEMEDOCUMENTATIONPROPERTY)Instance.getProc("GetThemeDocumentationProperty", (FARPROC)GetThemeDocumentationPropertyFail);
		}
		return (*Instance.funcs_.getThemeDocumentationPropertyFunc)(pszThemeName, pszPropertyName, pszValueBuff, cchMaxValChars);
	}


	static HRESULT DrawThemeParentBackground(HWND hwnd, HDC hdc,  RECT* prc)
	{
		if ( NULL == Instance.funcs_.drawThemeParentBackgroundFunc ) {
			Instance.funcs_.drawThemeParentBackgroundFunc = (PFNDRAWTHEMEPARENTBACKGROUND)Instance.getProc("DrawThemeParentBackground", (FARPROC)DrawThemeParentBackgroundFail);
		}
		return (*Instance.funcs_.drawThemeParentBackgroundFunc)(hwnd, hdc, prc);
	}

	static HRESULT EnableTheming(BOOL fEnable)
	{
		if ( NULL == Instance.funcs_.enableThemingFunc ) {
			Instance.funcs_.enableThemingFunc = (PFNENABLETHEMING)Instance.getProc("EnableTheming", (FARPROC)EnableThemingFail);
		}
		return (*Instance.funcs_.enableThemingFunc)(fEnable);
	}
};



#endif // _VCF_WIN32VISUALSTYLESWRAPPER_H__

