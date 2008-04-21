// VCFFormWizard.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "VCFFormWizard.h"
#include "VCFFormWizardaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE VCFFormWizardDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("VCFFORMWIZARD.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(VCFFormWizardDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(VCFFormWizardDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&VCFFormWizardaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("VCFFORMWIZARD.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(VCFFormWizardDLL);
	}
	return 1;   // ok
}
