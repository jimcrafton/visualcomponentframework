#ifndef _VCF_WINCEMENUCOMPAT_H__
#define _VCF_WINCEMENUCOMPAT_H__
//WinceMenuCompat.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifdef _WIN32_WCE

/*
#include <atlbase.h>
#include <atlapp.h>
#include <atlosapice.h>
*/

inline BOOL IsMenu(HMENU hMenu)
{
	MENUITEMINFO mii;
	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	SetLastError(0);
	if (::GetMenuItemInfo(hMenu, 0, TRUE, &mii))
	{
		return TRUE;
	}
	else
	{
		return (::GetLastError() != ERROR_INVALID_MENU_HANDLE);
	}
}

inline int GetMenuItemCount(HMENU hMenu)
{
	if(!::IsMenu(hMenu))
	{
		::SetLastError(ERROR_INVALID_HANDLE);
		return -1;
	}
	
	MENUITEMINFO mii;
	memset((char *)&mii, 0, sizeof(mii));
	mii.cbSize = sizeof(mii);

	UINT i = 0;
	
	while(true)
	{
		if(0 == ::GetMenuItemInfo(hMenu, i, TRUE, &mii))
		{
			break;
		}
		++i;
	}

	return i;
}
inline UINT GetMenuItemID(
	HMENU hMenu,
	int nPos)
{
	MENUITEMINFO mii;
	memset((char *)&mii, 0, sizeof(mii));
	mii.cbSize = sizeof(mii); 
	mii.fMask  = MIIM_ID; 
	
	if((0 == ::GetMenuItemInfo(hMenu, nPos, TRUE, &mii)) || (mii.hSubMenu != NULL))
	{
		return 0xFFFFFFFF;
	}

	return mii.wID; 
}

BOOL
WINAPI
InsertMenuItemW(
    __in HMENU hmenu,
    __in UINT item,
    __in BOOL fByPosition,
    __in LPCMENUITEMINFOW lpmi);
    
BOOL
WINAPI
SetMenu(
    __in HWND hWnd,
    __in_opt HMENU hMenu);

#endif //_WIN32_WCE

#endif //_VCF_WINCEMENUCOMPAT_H__
