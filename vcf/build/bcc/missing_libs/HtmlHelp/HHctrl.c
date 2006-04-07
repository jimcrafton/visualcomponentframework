/*******************************************************************
#  Borland compatible HtmlHelp library                             # 
# (c) 2005 Darko Miletic                                           #
#  kiklop@fibertel.com.ar                                          #
*******************************************************************/

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <htmlhelp.h>


typedef HWND (WINAPI *dHtmlHelpA)(HWND, LPCSTR, UINT, DWORD_PTR);
typedef HWND (WINAPI *dHtmlHelpW)(HWND, LPCWSTR, UINT, DWORD_PTR);

static HMODULE libHandle__ = NULL;
static dHtmlHelpA HHA__    = NULL;
static dHtmlHelpW HHW__    = NULL;
static char lPath[MAX_PATH] = {0};

void __cdecl hhctrl_cleanup (void) {
  if (libHandle__ != NULL) {
    Sleep(50);
    FreeLibrary(libHandle__);
    libHandle__ = NULL;
  }
  HHA__ = NULL;
  HHW__ = NULL;
}
#pragma exit hhctrl_cleanup 88

const char* __cdecl GetLocation_(void) {
  char* location = "CLSID\\{ADB880A6-D8FF-11CF-9377-00AA003B7A11}\\InprocServer32";
  HKEY key = NULL;
  LONG ret , csize = 0;
  ret = RegOpenKeyExA(HKEY_CLASSES_ROOT, location, 0, KEY_READ, &key);
  if (ret == ERROR_SUCCESS) {
    ret = RegQueryValueA(key, NULL, NULL, &csize);
    if (ret == ERROR_SUCCESS) {
      RegQueryValueA(key, NULL, lPath, &csize);
    }
    RegCloseKey(key);
  }
  return lPath;
}

BOOL __cdecl InitF__(void) {
  if (libHandle__ == NULL) {
    libHandle__ = LoadLibraryA(GetLocation_());
    if (libHandle__ == NULL) {
      libHandle__ = LoadLibraryA("hhctrl.ocx");
    }
    if (libHandle__ != NULL) {
      HHA__ = (dHtmlHelpA)GetProcAddress(libHandle__, ATOM_HTMLHELP_API_ANSI   );
      HHW__ = (dHtmlHelpW)GetProcAddress(libHandle__, ATOM_HTMLHELP_API_UNICODE);
      if ((HHA__ == NULL) || (HHW__ == NULL)) {
        hhctrl_cleanup();
      }
    }
  }
  return (libHandle__ != NULL);
}

HWND WINAPI HtmlHelpA(HWND hwndCaller, LPCSTR pszFile, UINT uCommand, DWORD_PTR dwData) {
  return InitF__() ? HHA__(hwndCaller, pszFile, uCommand, dwData) : (HWND)NULL;
}

HWND WINAPI HtmlHelpW(HWND hwndCaller, LPCWSTR pszFile, UINT uCommand, DWORD_PTR dwData) {
  return InitF__() ? HHW__(hwndCaller, pszFile, uCommand, dwData) : (HWND)NULL;
}


