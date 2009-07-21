#ifndef _VCF_OSCOMPATKIT_H__
#define _VCF_OSCOMPATKIT_H__
//OSCompatKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/FoundationKit.h"

#ifdef _WIN32_WCE

typedef HANDLE HTHEME;

#ifndef WS_OVERLAPPEDWINDOW
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define WS_OVERLAPPEDWINDOW (WS_SYSMENU)
#else
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
#endif
#endif

#include "WinceMenuCompat.h"

// These are not supported on Windows CE
#define WS_POPUPWINDOW              0
#define WS_EX_RIGHTSCROLLBAR        0
#define ES_SAVESEL                  0
#define CBS_OWNERDRAWVARIABLE       0
#define ODS_DEFAULT                 0
#define EM_STREAMIN                 WM_SETTEXT
#define SW_NORMAL                   SW_SHOWNORMAL
#define SM_CXFRAME                  SM_CXFIXEDFRAME
#define SM_CYFRAME                  SM_CYFIXEDFRAME
#define TPM_RIGHTBUTTON             0x0002L // Not supported - just to avoid errors
#define SPI_GETNONCLIENTMETRICS     0x0029 // Not supported - just to avoid errors
#define LR_CREATEDIBSECTION         0x00002000 // Not supported - just to avoid errors
#define RDW_FRAME                   0 // Not supported - just to avoid errors

// These are not provided on Windows CE
#ifndef GWLP_WNDPROC
#define GWLP_WNDPROC GWL_WNDPROC
#endif
#ifndef GWLP_USERDATA
#define GWLP_USERDATA GWL_USERDATA
#endif
#ifndef DWLP_MSGRESULT
#define DWLP_MSGRESULT DWL_MSGRESULT
#endif
#ifndef DWLP_DLGPROC
#define DWLP_DLGPROC DWL_DLGPROC
#endif

#ifndef SetWindowLongPtr 
#define SetWindowLongPtr SetWindowLongPtrW
#endif

#ifndef GetWindowLongPtr 
#define GetWindowLongPtr GetWindowLongPtrW
#endif

#ifndef SetWindowLongPtrW
  inline LONG_PTR tmp_SetWindowLongPtrW( HWND hWnd, int nIndex, LONG_PTR dwNewLong )
  {
	return( ::SetWindowLongW( hWnd, nIndex, LONG( dwNewLong ) ) );
  }
  #define SetWindowLongPtrW tmp_SetWindowLongPtrW
#endif

#ifndef GetWindowLongPtrW
  inline LONG_PTR tmp_GetWindowLongPtrW( HWND hWnd, int nIndex )
  {
	return( ::GetWindowLongW( hWnd, nIndex ) );
  }
  #define GetWindowLongPtrW tmp_GetWindowLongPtrW
#endif

inline 
int GetScrollPos(HWND hWnd, int nBar)
{
	SCROLLINFO lpsi = {sizeof(SCROLLINFO), SIF_POS};
	if(::GetScrollInfo(hWnd, nBar, &lpsi))
	{
		return lpsi.nPos;
	}
	return 0;
}

typedef struct tagWINDOWPLACEMENT {
    UINT  length;
    UINT  flags;
    UINT  showCmd;
    POINT ptMinPosition;
    POINT ptMaxPosition;
    RECT  rcNormalPosition;
#ifdef _MAC
    RECT  rcDevice;
#endif
} WINDOWPLACEMENT;
typedef WINDOWPLACEMENT *PWINDOWPLACEMENT, *LPWINDOWPLACEMENT;

WINUSERAPI
BOOL
WINAPI
GetWindowPlacement(
    __in HWND hWnd,
    __inout WINDOWPLACEMENT *lpwndpl);

WINUSERAPI
BOOL
WINAPI
SetWindowPlacement(
    __in HWND hWnd,
    __in CONST WINDOWPLACEMENT *lpwndpl);

typedef struct tagNONCLIENTMETRICSA
{
    UINT    cbSize;
    int     iBorderWidth;
    int     iScrollWidth;
    int     iScrollHeight;
    int     iCaptionWidth;
    int     iCaptionHeight;
    LOGFONTA lfCaptionFont;
    int     iSmCaptionWidth;
    int     iSmCaptionHeight;
    LOGFONTA lfSmCaptionFont;
    int     iMenuWidth;
    int     iMenuHeight;
    LOGFONTA lfMenuFont;
    LOGFONTA lfStatusFont;
    LOGFONTA lfMessageFont;
#if(WINVER >= 0x0600)
    int     iPaddedBorderWidth;
#endif /* WINVER >= 0x0600 */
}   NONCLIENTMETRICSA, *PNONCLIENTMETRICSA, FAR* LPNONCLIENTMETRICSA;
typedef struct tagNONCLIENTMETRICSW
{
    UINT    cbSize;
    int     iBorderWidth;
    int     iScrollWidth;
    int     iScrollHeight;
    int     iCaptionWidth;
    int     iCaptionHeight;
    LOGFONTW lfCaptionFont;
    int     iSmCaptionWidth;
    int     iSmCaptionHeight;
    LOGFONTW lfSmCaptionFont;
    int     iMenuWidth;
    int     iMenuHeight;
    LOGFONTW lfMenuFont;
    LOGFONTW lfStatusFont;
    LOGFONTW lfMessageFont;
#if(WINVER >= 0x0600)
    int     iPaddedBorderWidth;
#endif /* WINVER >= 0x0600 */
}   NONCLIENTMETRICSW, *PNONCLIENTMETRICSW, FAR* LPNONCLIENTMETRICSW;
#ifdef UNICODE
typedef NONCLIENTMETRICSW NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSW PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSW LPNONCLIENTMETRICS;
#else
typedef NONCLIENTMETRICSA NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSA PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSA LPNONCLIENTMETRICS;
#endif // UNICODE

/* PolyFill() Modes */
#define WINDING                      2

WINGDIAPI 
HRGN  
WINAPI 
CreatePolygonRgn(    __in_ecount(cPoint) CONST POINT *pptl,
                                            __in int cPoint,
                                            __in int iMode);



//http://www.codeproject.com/KB/mobile/PPCGuidGen.aspx

typedef __nullterminated unsigned char __RPC_FAR * RPC_CSTR;
#if defined(RPC_USE_NATIVE_WCHAR) && defined(_NATIVE_WCHAR_T_DEFINED)
typedef __nullterminated wchar_t __RPC_FAR * RPC_WSTR;
#else
typedef __nullterminated unsigned short __RPC_FAR * RPC_WSTR;
#endif

#if _WIN32_WCE > 0x420
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreate (
    __out UUID __RPC_FAR * Uuid
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreateNil (
    OUT UUID __RPC_FAR * NilUuid
    );

RPCRTAPI
unsigned short
RPC_ENTRY
UuidHash (
    IN UUID __RPC_FAR * Uuid,
    OUT RPC_STATUS __RPC_FAR * Status
    );
#endif

RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidFromStringW (
    __in_opt RPC_WSTR StringUuid,
    __out UUID __RPC_FAR * Uuid
    );
    
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidToStringW (
    __in const UUID __RPC_FAR * Uuid,
    __deref_out RPC_WSTR __RPC_FAR * StringUuid
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringFreeW (
    __inout RPC_WSTR __RPC_FAR * String
    );
/*---------------------------------------------------------------------*/
/*                     VARTYPE Math API                                */
/*---------------------------------------------------------------------*/

STDAPI VarAdd(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarAnd(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarCat(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarDiv(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarEqv(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarIdiv(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarImp(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarMod(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarMul(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarOr(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarPow(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarSub(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);
STDAPI VarXor(__in LPVARIANT pvarLeft, __in LPVARIANT pvarRight, __out LPVARIANT pvarResult);

STDAPI VarAbs(__in LPVARIANT pvarIn, __out LPVARIANT pvarResult);
STDAPI VarFix(__in LPVARIANT pvarIn, __out LPVARIANT pvarResult);
STDAPI VarInt(__in LPVARIANT pvarIn, __out LPVARIANT pvarResult);
STDAPI VarNeg(__in LPVARIANT pvarIn, __out LPVARIANT pvarResult);
STDAPI VarNot(__in LPVARIANT pvarIn, __out LPVARIANT pvarResult);

// Decimal math
//
STDAPI VarDecAdd(__in LPDECIMAL pdecLeft, __in LPDECIMAL pdecRight, __out LPDECIMAL pdecResult);
STDAPI VarDecDiv(__in LPDECIMAL pdecLeft, __in LPDECIMAL pdecRight, __out LPDECIMAL pdecResult);
STDAPI VarDecMul(__in LPDECIMAL pdecLeft, __in LPDECIMAL pdecRight, __out LPDECIMAL pdecResult);
STDAPI VarDecSub(__in LPDECIMAL pdecLeft, __in LPDECIMAL pdecRight, __out LPDECIMAL pdecResult);

STDAPI VarDecAbs(__in LPDECIMAL pdecIn, __out LPDECIMAL pdecResult);
STDAPI VarDecFix(__in LPDECIMAL pdecIn, __out LPDECIMAL pdecResult);
STDAPI VarDecInt(__in LPDECIMAL pdecIn, __out LPDECIMAL pdecResult);
STDAPI VarDecNeg(__in LPDECIMAL pdecIn, __out LPDECIMAL pdecResult);

STDAPI VarDecRound(__in LPDECIMAL pdecIn, int cDecimals, __out LPDECIMAL pdecResult);

STDAPI VarDecCmp(__in LPDECIMAL pdecLeft, __in LPDECIMAL pdecRight);
STDAPI VarDecCmpR8(__in LPDECIMAL pdecLeft, __in double dblRight);

/*
 * LockWindowUpdate API
 */
#define DCX_LOCKWINDOWUPDATE 0x00000400L

WINUSERAPI
BOOL
WINAPI
LockWindowUpdate(
    __in_opt HWND hWndLock);

/*
 * Shell API
 */
 #ifndef SHSTDAPI
#if defined(_SHELL32_)
#define SHSTDAPI          STDAPI
#define SHSTDAPI_(type)   STDAPI_(type)
#else
#define SHSTDAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define SHSTDAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#endif
#endif // SHSTDAPI

//SEE_MASK_FLAG_DDEWAIT is deprecated on win32 and not supported on wince
//SEE_MASK_IDLIST is not supported on wince
#define SEE_MASK_FLAG_DDEWAIT 0 
#define SEE_MASK_IDLIST       0

SHSTDAPI SHEmptyRecycleBinW(HWND hwnd, LPCWSTR pszRootPath, DWORD dwFlags);
 
#define SHELLEXECUTEINFOW     SHELLEXECUTEINFO 
#define SHGetPathFromIDListW  SHGetPathFromIDList
#define ShellExecuteExW       ShellExecuteEx
#define SHGetFileInfoW        SHGetFileInfo
#define SHGFI_EXETYPE         0x000002000 // MSDN say it's supported ????

//IShellLink is not supported - should use SHGetShortcutTarget
#define IShellLinkW           IShellLink
#define IID_IShellLinkW       IID_IShellLink

STDAPI FindMimeFromData(                                                                                                                  
    __in_opt                LPBC    pBC,                   // bind context - can be NULL                                                 
    __in_opt                LPCWSTR pwzUrl,                // url - can be null                                                          
    __in_bcount_opt(cbSize) LPVOID  pBuffer,               // buffer with data to sniff - can be null (pwzUrl must be valid)             
                            DWORD   cbSize,                // size of buffer                                                             
    __in_opt                LPCWSTR pwzMimeProposed,       // proposed mime if - can be null                                             
                            DWORD   dwMimeFlags,           // will be defined                                                            
    __deref_out             LPWSTR  *ppwzMimeOut,          // the suggested mime                                                         
    __reserved              DWORD   dwReserved);           // must be 0  


// SendMessageTimeout does not support the following param on wince
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002

WINGDIAPI 
int   
WINAPI 
GetDIBits( 
		  __in HDC hdc, 
		  __in HBITMAP hbm, 
		  __in UINT start, 
		  __in UINT cLines,  
		  __out_opt LPVOID lpvBits, 
		  __inout LPBITMAPINFO lpbmi, 
		  __in UINT usage);

WINGDIAPI 
int   
WINAPI 
SetDIBits(
        __in_opt HDC hdc, 
        __in HBITMAP hbm, 
        __in UINT start, 
        __in UINT cLines, 
        __in CONST VOID *lpBits, 
        __in CONST BITMAPINFO * lpbmi, 
        __in UINT ColorUse);

WINUSERAPI
HDESK
WINAPI
GetThreadDesktop(
    __in DWORD dwThreadId);

WINUSERAPI
BOOL
WINAPI
DestroyCursor(
    __in HCURSOR hCursor);

WINUSERAPI
HANDLE
WINAPI
CopyImage(
    __in HANDLE h,
    __in UINT type,
    __in int cx,
    __in int cy,
    __in UINT flags);
    
typedef struct tagWNDCLASSEXW {
    UINT        cbSize;
    /* Win 3.x */
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
    /* Win 4.0 */
    HICON       hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW, NEAR *NPWNDCLASSEXW, FAR *LPWNDCLASSEXW;

WINUSERAPI
ATOM
WINAPI
RegisterClassExW(
    __in CONST WNDCLASSEXW *);
    
//Event Hook

/*
 * SetWindowsHook() codes
 */
#define WH_MIN              (-1)
#define WH_MSGFILTER        (-1)
#define WH_JOURNALRECORD    0
#define WH_JOURNALPLAYBACK  1
#define WH_KEYBOARD         2
#define WH_GETMESSAGE       3
#define WH_CALLWNDPROC      4
#define WH_CBT              5
#define WH_SYSMSGFILTER     6
#define WH_MOUSE            7

typedef LRESULT (CALLBACK* HOOKPROC)(int code, WPARAM wParam, LPARAM lParam);

/*
 * Structure used by WH_MOUSE
 */
typedef struct tagMOUSEHOOKSTRUCT {
    POINT   pt;
    HWND    hwnd;
    UINT    wHitTestCode;
    ULONG_PTR dwExtraInfo;
} MOUSEHOOKSTRUCT, FAR *LPMOUSEHOOKSTRUCT, *PMOUSEHOOKSTRUCT;

WINUSERAPI
HHOOK
WINAPI
SetWindowsHookExW(
    __in int idHook,
    __in HOOKPROC lpfn,
    __in_opt HINSTANCE hmod,
    __in DWORD dwThreadId);
#ifdef UNICODE
#define SetWindowsHookEx  SetWindowsHookExW
#else
#define SetWindowsHookEx  SetWindowsHookExA
#endif // !UNICODE
    
WINUSERAPI
BOOL
WINAPI
UnhookWindowsHookEx(
    __in HHOOK hhk);
    
WINUSERAPI
LRESULT
WINAPI
CallNextHookEx(
    __in_opt HHOOK hhk,
    __in int nCode,
    __in WPARAM wParam,
    __in LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
GetKeyboardState(
    __out_ecount(256) PBYTE lpKeyState);
    
WINUSERAPI
int
WINAPI
ToAsciiEx(
    __in UINT uVirtKey,
    __in UINT uScanCode,
    __in_ecount_opt(256) CONST BYTE *lpKeyState,
    __out LPWORD lpChar,
    __in UINT uFlags,
    __in_opt HKL dwhkl);

#define CWP_ALL             0x0000
#define CWP_SKIPINVISIBLE   0x0001
#define CWP_SKIPDISABLED    0x0002
#define CWP_SKIPTRANSPARENT 0x0004

WINUSERAPI
HWND
WINAPI
ChildWindowFromPointEx(
    __in HWND hwnd,
    __in POINT pt,
    __in UINT flags);

int
WINAPI
GetCalendarInfoW(
    __in LCID     Locale,
    __in CALID    Calendar,
    __in CALTYPE  CalType,
    __out_ecount_opt(cchData) LPWSTR   lpCalData,
    __in int      cchData,
    __out_opt LPDWORD  lpValue);

//////////////////////////////////////////////////////
// POSIX FUNCTIONS
//////////////////////////////////////////////////////
#if defined(__cplusplus)
#define __BEGIN_C_DECLS extern "C" {
#define __END_C_DECLS }
#else
#define __BEGIN_C_DECLS
#define __END_C_DECLS
#endif

__BEGIN_C_DECLS

void 	__cdecl abort (void);

__END_C_DECLS

#endif //_WIN32_WCE
#endif //_VCF_OSCOMPATKIT_H__
