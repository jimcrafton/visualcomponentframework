//Win32HTMLBrowserApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//#include "Win32HTMLBrowserInterface.h"
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"



#include "vcf/ApplicationKit/Win32HTMLBrowserApplication.h"

#include "vcf/ApplicationKit/Win32HTMLBrowser.h"


CComModule _Module;


using namespace VCF;


BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


class Win32HTMLBrowserApplication : public LibraryApplication {
public:

	virtual bool initRunningApplication(){

		bool result = LibraryApplication::initRunningApplication();

		return result;
	}

};


static Win32HTMLBrowserApplication* singleWin32HTMLBrowserApplicationInstance = NULL;




void initWin32HTMLBrowserLib( HMODULE module )
{
	if ( module == NULL ) {
		module = GetModuleHandle(NULL);
	}
	_Module.Init(ObjectMap, (HINSTANCE)module );

	//singleWin32HTMLBrowserApplicationInstance = new Win32HTMLBrowserApplication();

	//singleWin32HTMLBrowserApplicationInstance->getPeer()->setHandleID( (long)module );

	//singleWin32HTMLBrowserApplicationInstance->setName( "Win32HTMLBrowser" );

	//LibraryApplication::registerLibrary( singleWin32HTMLBrowserApplicationInstance );

	REGISTER_CLASSINFO( Win32HTMLBrowser );
	/*
	if ( false == singleWin32HTMLBrowserApplicationInstance->initRunningApplication() ) {
		singleWin32HTMLBrowserApplicationInstance->terminateRunningApplication();

		delete singleWin32HTMLBrowserApplicationInstance;

		singleWin32HTMLBrowserApplicationInstance = NULL;
	}
	*/
}

void terminateWin32HTMLBrowserLib()
{
	_Module.Term();

	if ( NULL != singleWin32HTMLBrowserApplicationInstance ) {
	//	delete singleWin32HTMLBrowserApplicationInstance;
	//	singleWin32HTMLBrowserApplicationInstance = NULL;
	}
}



#ifdef _USRDLL

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {
			initWin32HTMLBrowserLib((HINSTANCE) hModule);
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {
			terminateWin32HTMLBrowserLib();
		}
		break;
    }
    return TRUE;
}

#endif


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
*Revision 1.11  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.14.1  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10  2002/06/19 21:48:46  ddiego
**** empty log message ***
*
*Revision 1.9  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


