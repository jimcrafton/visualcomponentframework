// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E0F681BA_EB6C_4461_B2BD_0001F40738C6__INCLUDED_)
#define AFX_STDAFX_H__E0F681BA_EB6C_4461_B2BD_0001F40738C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <stdio.h>

#ifdef WIN32
	// tell the compiler to shut up
	#pragma warning(disable:4786)
#endif



#include <map>
#include <string>
#include <vector>

#include "CmdLine.h"

#endif // !defined(AFX_STDAFX_H__E0F681BA_EB6C_4461_B2BD_0001F40738C6__INCLUDED_)
