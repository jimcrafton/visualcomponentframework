//$$root$$.cpp


#include "ApplicationKit.h"
#include "LibraryApplication.h"
#include "Win32Peer.h"




class $$Root$$Application : public LibraryApplication {
public:

	virtual bool initRunningApplication(){
		bool result = LibraryApplication::initRunningApplication();	
		

		return result;
	}

};


static $$Root$$Application* single$$Root$$ApplicationInstance = NULL;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {
			single$$Root$$ApplicationInstance = new $$Root$$Application();

			single$$Root$$ApplicationInstance->getPeer()->setHandleID( (long)hModule );
			
			single$$Root$$ApplicationInstance->setName( "$$Root$$" );

			LibraryApplication::registerLibrary( single$$Root$$ApplicationInstance );

			if ( false == single$$Root$$ApplicationInstance->initRunningApplication() ) {
				single$$Root$$ApplicationInstance->terminateRunningApplication();

				delete single$$Root$$ApplicationInstance;

				single$$Root$$ApplicationInstance = NULL;
			}
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {
			if ( NULL != single$$Root$$ApplicationInstance ) {
				delete single$$Root$$ApplicationInstance;
				single$$Root$$ApplicationInstance = NULL;
			}
		}
		break;
    }
    return TRUE;
}

