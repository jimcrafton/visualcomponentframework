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


#include <comdef.h>
#include <atlbase.h>

extern CComModule _Module;

#include <atlcom.h>
#include <atlwin.h>

void initWin32HTMLBrowserLib( HMODULE module=NULL );

void terminateWin32HTMLBrowserLib();


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.7.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.2.2  2002/12/28 01:56:21  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.5.2.1  2002/12/27 23:04:41  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.5  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.4.10.1  2002/11/06 01:03:01  ddiego
*bug fixes, made the Win32HTMLBrowser get rid of the ATL.dll dependencies
*also made changes to the VCF Builder installer
*
*Revision 1.4  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32HTMLBROWSERAPPLICATION_H__


