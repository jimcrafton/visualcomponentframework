// AddInMod.cpp : implementation file
//

#include "stdafx.h"
#include "VCFBuilder.h"
#include "DSAddIn.h"
#include "Commands.h"
#include "DevStudioMainWnd.h"
#include "VCFBuilderMDIChild.h"
#include "VCFBuilderHostView.h"
#include "DevStudioMDIClientWnd.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called when the user first loads the add-in, and on start-up
//  of each subsequent Developer Studio session
STDMETHODIMP CDSAddIn::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// Store info passed to us
	IApplication* pApplication = NULL;
	if (FAILED(pApp->QueryInterface(IID_IApplication, (void**) &pApplication))
		|| pApplication == NULL)
	{
		*OnConnection = VARIANT_FALSE;
		return S_OK;
	}

	m_dwCookie = dwCookie;

	// Create command dispatch, send info back to DevStudio
	CCommandsObj::CreateInstance(&m_pCommands);
	m_pCommands->AddRef();

	// The QueryInterface above AddRef'd the Application object.  It will
	//  be Release'd in CCommand's destructor.
	m_pCommands->SetApplicationObject(pApplication);

	// (see stdafx.h for the definition of VERIFY_OK)

	VERIFY_OK(pApplication->SetAddInInfo((long) AfxGetInstanceHandle(),
		(LPDISPATCH) m_pCommands, IDR_TOOLBAR_MEDIUM, IDR_TOOLBAR_LARGE, m_dwCookie));

	// Inform DevStudio of the commands we implement

	VCFBuilderMDIChild::globalVCFBuilderIcon = AfxGetApp()->LoadIcon(IDI_VCFBUILDER);

	//Initialize the DevStdio global subclass window 
	HWND hWnd = ::GetActiveWindow();
	HWND hDesktopWnd = ::GetDesktopWindow();
	HWND hDevStudioWnd = NULL;
    while (hWnd  &&  hWnd != hDesktopWnd)
    {
        hDevStudioWnd = hWnd;
        hWnd = ::GetParent(hWnd);
    }

	CDevStudioMainWnd::globalDevStudioMainWnd = new CDevStudioMainWnd(hDevStudioWnd);	

	// find the MDI client area window
	HWND hMDIWnd = CDevStudioMainWnd::globalDevStudioMainWnd->GetMDIClientHWND();    
	

	if ( (NULL != hMDIWnd) && (NULL != hDevStudioWnd) ) {
		//CDevStudioMDIClientWnd::globalDevStudioMDIChildMgr = new CDevStudioMDIClientWnd(hMDIWnd, pApplication);
		char tmp[256];
		memset(tmp,0,256);
		sprintf( tmp, "Found %x MDIClient hWnd\n", hMDIWnd );
		
		OutputDebugString( tmp );

		VCFBuilderMDIChildWnd::RegisterClass( AfxGetApp()->m_hInstance );

		RECT r = {0};
		GetWindowRect( hMDIWnd, &r );
		POINT* pt = (POINT*)&r;

		ScreenToClient( hDevStudioWnd, pt );
		pt ++;
		ScreenToClient( hDevStudioWnd, pt );


		HWND mdiChildWnd = CreateWindowEx( 0,//WS_EX_MDICHILD | WS_EX_WINDOWEDGE, 
											VCFBuilderMDIChildWnd::WndClassName,
											"VCFBuilderMDIChildWnd",
											WS_BORDER | WS_CHILD,
											r.left, r.top,
											r.right-r.left, r.bottom-r.top,
											hDevStudioWnd,
											NULL, AfxGetApp()->m_hInstance,
											0 );



	}	

	/*
	CRuntimeClass* pRTDocClass = NULL;
	bool addDocTemplate = false;
	{
		AFX_MANAGE_STATE( AfxGetAppModuleState() );
		POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
		while ( (NULL != pos) && (!addDocTemplate) ) {
			CDocTemplate* docTemplate = AfxGetApp()->GetNextDocTemplate( pos );
			CString docTemplateClassName = docTemplate->GetRuntimeClass()->m_lpszClassName;
			//if ( docTemplateClassName == "CTextDocTemplate" ) {
				char tmp[256];
				sprintf( tmp,"docTemplate class name: \"%s\"\n", docTemplate->GetRuntimeClass()->m_lpszClassName );
				
				OutputDebugString( tmp );
				POSITION pos2 = docTemplate->GetFirstDocPosition();
				while ( NULL != pos2 ) {
					CDocument* doc = docTemplate->GetNextDoc( pos2 );
					CString docClassName = doc->GetRuntimeClass()->m_lpszClassName;
					if ( docClassName == "CWorkspaceDoc" ) {
						pRTDocClass = doc->GetRuntimeClass();
						addDocTemplate = true;
					}
					
					sprintf( tmp,"doc class name: \"%s\"\n", doc->GetRuntimeClass()->m_lpszClassName );
					OutputDebugString( tmp );
				}
			//}
			
		}
	}
	*/

	//finished initializing.....
	
	if ( false == initVCFBuilderAddInCommands( (bFirstTime == VARIANT_TRUE), pApplication ) )	{
		*OnConnection = VARIANT_FALSE;
		return S_OK;
	}
	

	*OnConnection = VARIANT_TRUE;
	return S_OK;
}

// This is called on shut-down, and also when the user unloads the add-in
STDMETHODIMP CDSAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	delete CDevStudioMainWnd::globalDevStudioMainWnd;
	CDevStudioMainWnd::globalDevStudioMainWnd = NULL;

	//delete CDevStudioMDIClientWnd::globalDevStudioMDIChildMgr;
	//CDevStudioMDIClientWnd::globalDevStudioMDIChildMgr = NULL;

	m_pCommands->UnadviseFromEvents();
	m_pCommands->Release();
	m_pCommands = NULL;

	// TODO: Perform any cleanup work here

	return S_OK;
}

bool CDSAddIn::initVCFBuilderAddInCommands( const bool& bFirstTime, IApplication* pApplication )
{
	bool result = true;
	std::vector<CComBSTR> m_cmdNames;

	// The command name should not be localized to other languages.  The 
	//  tooltip, command description, and other strings related to this
	//  command are stored in the string table (IDS_CMD_STRING) and should
	//  be localized.
	LPCTSTR szCommand = _T("ActivateDevStdioEnvironmentCommand");
	VARIANT_BOOL bRet;
	CString strCmdString;
	strCmdString.LoadString(IDS_CMD_ACTIVATE_DEV_STDIO_ENV);
	strCmdString = szCommand + strCmdString;
	CComBSTR bszCmdString(strCmdString);
	CComBSTR bszMethod(_T("ActivateDevStdioEnvironment"));
	CComBSTR bszCmdName(szCommand);
	m_cmdNames.push_back( bszCmdName );
	VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, 0, m_dwCookie, &bRet));
	if (bRet == VARIANT_FALSE)
	{
		// AddCommand failed because a command with this name already
		//  exists.  You may try adding your command under a different name.
		//  Or, you can fail to load as we will do here.
		result = false;
	}


	szCommand = _T("ActivateVCFBuilderEnvironmentCommand");
	strCmdString.LoadString(IDS_CMD_ACTIVATE_VCF_BUILDER_ENV);
	strCmdString = szCommand + strCmdString;
	bszCmdString = strCmdString;
	bszMethod = _T("ActivateVCFBuilderEnvironment");
	bszCmdName = szCommand;
	m_cmdNames.push_back( bszCmdName );
	VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, 1, m_dwCookie, &bRet));
	if ( VARIANT_FALSE == bRet ) {
		result = false;
	}

	szCommand = _T("ActivateVCFBuilderEnvStandaloneCommand");
	strCmdString.LoadString(IDS_CMD_ACTIVATE_VCF_BUILDER_ENV_STANDALONE);
	strCmdString = szCommand + strCmdString;
	bszCmdString = strCmdString;
	bszMethod = _T("ActivateVCFBuilderEnvStandalone");
	bszCmdName = szCommand;
	m_cmdNames.push_back( bszCmdName );
	VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, 2, m_dwCookie, &bRet));
	if ( VARIANT_FALSE == bRet ) {
		result = false;
	}

	szCommand = _T("NewProjectCommand");
	strCmdString.LoadString(IDS_CMD_NEW_PROJECT);
	strCmdString = szCommand + strCmdString;
	bszCmdString = strCmdString;
	bszMethod = _T("NewProject");
	bszCmdName = szCommand;
	m_cmdNames.push_back( bszCmdName );
	VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, 3, m_dwCookie, &bRet));
	if ( VARIANT_FALSE == bRet ) {
		result = false;
	}

	if ( result ) {

		if (bFirstTime)
		{
			std::vector<CComBSTR>::iterator it = m_cmdNames.begin();
			while ( it != m_cmdNames.end() ) {
				VERIFY_OK( pApplication->AddCommandBarButton(dsGlyph, *it, m_dwCookie) );	
				it++;
			}
		}
	}

	return result;
}
