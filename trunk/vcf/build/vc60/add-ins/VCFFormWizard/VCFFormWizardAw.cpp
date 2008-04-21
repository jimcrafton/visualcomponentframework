// VCFFormWizardaw.cpp : implementation file
//

#include "stdafx.h"
#include "VCFFormWizard.h"
#include "VCFFormWizardaw.h"
#include "chooser.h"
#include <comdef.h>
#include <atlbase.h>
#include "Page2Dlg.h"


#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CVCFFormWizardAppWiz::InitCustomAppWiz()
{
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CVCFFormWizardAppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CVCFFormWizardAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CVCFFormWizardAppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

void CVCFFormWizardAppWiz::CustomizeProject(IBuildProject* pProject)
{
	// TODO: Add code here to customize the project.  If you don't wish
	//  to customize project, you may remove this virtual override.
	
	// This is called immediately after the default Debug and Release
	//  configurations have been created for each platform.  You may customize
	//  existing configurations on this project by using the methods
	//  of IBuildProject and IConfiguration such as AddToolSettings,
	//  RemoveToolSettings, and AddCustomBuildStep. These are documented in
	//  the Developer Studio object model documentation.

	// WARNING!!  IBuildProject and all interfaces you can get from it are OLE
	//  COM interfaces.  You must be careful to release all new interfaces
	//  you acquire.  In accordance with the standard rules of COM, you must
	//  NOT release pProject, unless you explicitly AddRef it, since pProject
	//  is passed as an "in" parameter to this function.  See the documentation
	//  on CCustomAppWiz::CustomizeProject for more information.

	IConfigurations* pConfigs = NULL;

	if ( SUCCEEDED(pProject->get_Configurations( &pConfigs )) ) {
		long count = 0;
		pConfigs->get_Count( &count );
		for (long i=0;i<count;i++){
			IConfiguration* pConfig = NULL;
			long t = i+1;
			_variant_t index = t;
			CComBSTR configName;		
			const int debug = 1;
			const int release = 2;
			if ( SUCCEEDED(pConfigs->Item( index, &pConfig )) ){
				_bstr_t tool = "mfc";
				_variant_t reserved;
				pConfig->AddToolSettings( tool, 0, reserved );
				
				tool = "cl.exe";
				_bstr_t setting = "";				
				
				pConfig->get_Name( (BSTR*)&configName );

				CString s = configName;
				if ( s.Find( "Release" ) != -1 ){
					t = 2;
				}
				else if ( s.Find( "Debug" ) != -1 ){
					t = 1;
				}
				
				switch ( t ){
					case debug: {
						setting = "/GR /MDd /I$(VCF_ROOT)/src";
					}
					break;

					case release: {
						setting = "/GR /MD /I$(VCF_ROOT)/src";
					}
					break;
				}

				pConfig->AddToolSettings( tool, setting, reserved );
				
				
				
				setting = "/YX";
				pConfig->RemoveToolSettings( tool, setting, reserved );

				setting = "/D_WINDOWS";
				pConfig->RemoveToolSettings( tool, setting, reserved );				
				
				int linkType = this->m_pChooser->GetLinkType();
				if ( linkType == VCF_DLL_LINK ) {
					setting = "/DUSE_APPLICATIONKIT_DLL";
					pConfig->AddToolSettings( tool, setting, reserved );
				}
				else if ( linkType == VCF_STATIC_LINK ) {
					setting = "/DUSE_APPKIT_LIB";
					pConfig->AddToolSettings( tool, setting, reserved );
				}
				//
				tool = "link.exe";
				if ( linkType == VCF_DLL_LINK ) {
					switch ( t ){
						case debug: {
							setting = "";
							
							setting += "rpcrt4.lib ";
							
							setting += "/libpath:$(VCF_ROOT)/lib";
						}
						break;

						case release: {
							setting = "";
							setting += "rpcrt4.lib ";
							
							setting += "/libpath:$(VCF_ROOT)/lib";
						}
						break;
					}
				}
				else if ( linkType == VCF_STATIC_LINK ) {
					switch ( t ){
						case debug: {
							//NetworkKit_sd, NetworkKitDLL_d, NetworkKit_s, NetworkKitDLL, RemoteObjectKit_sd, RemoteObjectKit_s, RemoteObjectKitDLL_d, RemoteObjectKitDLL
							setting = "";
							
							setting += "comctl32.lib rpcrt4.lib /libpath:$(VCF_ROOT)/lib";
						}
						break;

						case release: {
							setting = "";
							
							setting += "comctl32.lib rpcrt4.lib /libpath:$(VCF_ROOT)/lib";
						}
						break;
					}
				}
				HRESULT hr = pConfig->AddToolSettings( tool, setting, reserved );
				if ( ! SUCCEEDED( hr ) ){
					TRACE( "failed to set linker variables\n" );
				}
				
				setting = "/subsystem:windows /entry:\"mainCRTStartup\"";
				pConfig->AddToolSettings( tool, setting, reserved );				

				pConfig->Release();
			}
		}
		pConfigs->Release();
	}
}


// Here we define one instance of the CVCFFormWizardAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global VCFFormWizardaw.
CVCFFormWizardAppWiz VCFFormWizardaw;

