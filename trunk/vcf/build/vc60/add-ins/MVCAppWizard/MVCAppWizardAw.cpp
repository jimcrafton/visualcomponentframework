// MVCAppWizardaw.cpp : implementation file
//

#include "stdafx.h"
#include "MVCAppWizard.h"
#include "MVCAppWizardaw.h"
#include <atlbase.h>


#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString newUUID()
{
	CString result = "";

	UUID id;
	if ( RPC_S_OK == ::UuidCreate( &id ) ){
		unsigned char *tmpid = NULL;
		
		RPC_STATUS rpcresult = UuidToString(  &id, &tmpid );
		
		if ( RPC_S_OUT_OF_MEMORY != rpcresult ) {
			result = tmpid;
			
			RpcStringFree( &tmpid );
		}
	}

	return result;
}

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CMVCAppWizardAppWiz::InitCustomAppWiz()
{
	// There are no steps in this custom AppWizard.
	SetNumberOfSteps(0);

	// Add build step to .hpj if there is one
	m_Dictionary[_T("HELP")] = _T("1");

	
	CString docUUID = newUUID();
	CString windowUUID = newUUID();
	CString viewUUID = newUUID();

	m_Dictionary[_T("DOCUUID")] = docUUID;
	m_Dictionary[_T("WINDOWUUID")] = windowUUID;
	m_Dictionary[_T("VIEWUUID")] = viewUUID;

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CMVCAppWizardAppWiz::ExitCustomAppWiz()
{
	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
CAppWizStepDlg* CMVCAppWizardAppWiz::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == NULL);	// By default, this custom AppWizard has no steps

	// Set template macros based on the project name entered by the user.

	// Get value of $$root$$ (already set by AppWizard)
	CString strRoot;
	m_Dictionary.Lookup(_T("root"), strRoot);
	
	// Set value of $$Doc$$, $$DOC$$
	CString strDoc = strRoot.Left(6);
	m_Dictionary[_T("Doc")] = strDoc;
	strDoc.MakeUpper();
	m_Dictionary[_T("DOC")] = strDoc;

	// Set value of $$MAC_TYPE$$
	strRoot = strRoot.Left(4);
	int nLen = strRoot.GetLength();
	if (strRoot.GetLength() < 4)
	{
		CString strPad(_T(' '), 4 - nLen);
		strRoot += strPad;
	}
	strRoot.MakeUpper();
	m_Dictionary[_T("MAC_TYPE")] = strRoot;

	// Return NULL to indicate there are no more steps.  (In this case, there are
	//  no steps at all.)
	return NULL;
}

void CMVCAppWizardAppWiz::CustomizeProject(IBuildProject* pProject)
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
						setting = "/GR /MDd /I$(VCF_INCLUDE)";
					}
					break;

					case release: {
						setting = "/GR /MD /I$(VCF_INCLUDE)";
					}
					break;
				}

				pConfig->AddToolSettings( tool, setting, reserved );
				
				
				
				setting = "/YX";
				pConfig->RemoveToolSettings( tool, setting, reserved );

				setting = "/D_WINDOWS";
				pConfig->RemoveToolSettings( tool, setting, reserved );				
				
				
				//if ( linkType == VCF_DLL_LINK ) {//VCF_STATIC_LINK
					setting = "/DUSE_FRAMEWORK_DLL";
					pConfig->AddToolSettings( tool, setting, reserved );
					setting = "/DUSE_GRAPHICSKIT_DLL";
					pConfig->AddToolSettings( tool, setting, reserved );
					setting = "/DUSE_APPKIT_DLL";
					pConfig->AddToolSettings( tool, setting, reserved );
				//}
				tool = "link.exe";
				//if ( linkType == VCF_DLL_LINK ) {
					switch ( t ){
						case debug: {
							setting = "";
							
							setting += "rpcrt4.lib ";
							
							setting += "/libpath:$(VCF_LIB)";
						}
						break;

						case release: {
							setting = "";
							
							setting += "rpcrt4.lib ";
							
							setting += "/libpath:$(VCF_LIB)";
						}
						break;
					}

				/*
				}
				else if ( linkType == VCF_STATIC_LINK ) {
					switch ( t ){
						case debug: {
							//NetworkKit_sd, NetworkKitDLL_d, NetworkKit_s, NetworkKitDLL, RemoteObjectKit_sd, RemoteObjectKit_s, RemoteObjectKitDLL_d, RemoteObjectKitDLL
							setting = "";
							if ( m_pChooser->NeedVCFRemote() ) {
								setting += "NetworkKit_sd.lib RemoteObjectKit_sd.lib ";
							}
							else if ( m_pChooser->NeedVCFNet() ) {
								setting += "NetworkKit_sd.lib ";
							}
							setting += "comctl32.lib rpcrt4.lib /libpath:$(VCF_LIB)";
						}
						break;

						case release: {
							setting = "";
							if ( m_pChooser->NeedVCFRemote() ) {
								setting += "NetworkKit_s.lib RemoteObjectKit_s.lib ";
							}
							else if ( m_pChooser->NeedVCFNet() ) {
								setting += "NetworkKit_s.lib ";
							}
							setting += "comctl32.lib rpcrt4.lib /libpath:$(VCF_LIB)";
						}
						break;
					}
				}
				*/

				if ( ! SUCCEEDED( pConfig->AddToolSettings( tool, setting, reserved ) ) ){
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


// Here we define one instance of the CMVCAppWizardAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global MVCAppWizardaw.
CMVCAppWizardAppWiz MVCAppWizardaw;

