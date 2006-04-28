#ifndef _VCF_WIN32HTMLBROWSERAPPLICATION_H__
#define _VCF_WIN32HTMLBROWSERAPPLICATION_H__
//Win32HTMLBrowserApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//this will automatilcally pull in the atl.lib
//#define _ATL_DLL

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif




void initWin32HTMLBrowserLib( HMODULE module=NULL );

void terminateWin32HTMLBrowserLib();



#endif // _VCF_WIN32HTMLBROWSERAPPLICATION_H__

/**
$Id$
*/
