//[!output PROJECT_NAME].cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/LibraryApplication.h"
#include "vcf/FoundationKit/Win32Peer.h"

using namespace VCF;


class [!output PROJECT_NAME]Application : public LibraryApplication {
public:

	virtual bool initRunningApplication(){
		bool result = LibraryApplication::initRunningApplication();


		return result;
	}

};


static [!output PROJECT_NAME]Application* single[!output PROJECT_NAME]ApplicationInstance = NULL;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {

			single[!output PROJECT_NAME]ApplicationInstance = new [!output PROJECT_NAME]Application();

			single[!output PROJECT_NAME]ApplicationInstance->getPeer()->setHandleID( (long)hModule );

			single[!output PROJECT_NAME]ApplicationInstance->setName( "[!output PROJECT_NAME]" );

			LibraryApplication::registerLibrary( single[!output PROJECT_NAME]ApplicationInstance );
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {
			if ( NULL != single[!output PROJECT_NAME]ApplicationInstance ) {
				delete single[!output PROJECT_NAME]ApplicationInstance;
				single[!output PROJECT_NAME]ApplicationInstance = NULL;
			}
		}
		break;
    }
    return TRUE;
}


