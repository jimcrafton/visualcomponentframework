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
$Id$
*/
