// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "VCFBuilder.h"
#include "Commands.h"
#include "VCFBuilderMDIChild.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;

	// Create Application event handlers
	XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
	m_pApplicationEventsObj->AddRef();
	m_pApplicationEventsObj->Connect(m_pApplication);
	m_pApplicationEventsObj->m_pCommands = this;

	// Create Debugger event handler
	CComPtr<IDispatch> pDebugger;
	if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
		&& pDebugger != NULL)
	{
		XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
		m_pDebuggerEventsObj->AddRef();
		m_pDebuggerEventsObj->Connect(pDebugger);
		m_pDebuggerEventsObj->m_pCommands = this;
	}
}

void CCommands::UnadviseFromEvents()
{
	ASSERT (m_pApplicationEventsObj != NULL);
	m_pApplicationEventsObj->Disconnect(m_pApplication);
	m_pApplicationEventsObj->Release();
	m_pApplicationEventsObj = NULL;

	if (m_pDebuggerEventsObj != NULL)
	{
		// Since we were able to connect to the Debugger events, we
		//  should be able to access the Debugger object again to
		//  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
		CComPtr<IDispatch> pDebugger;
		VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
		ASSERT (pDebugger != NULL);
		m_pDebuggerEventsObj->Disconnect(pDebugger);
		m_pDebuggerEventsObj->Release();
		m_pDebuggerEventsObj = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Event handlers

// TODO: Fill out the implementation for those events you wish handle
//  Use m_pCommands->GetApplicationObject() to access the Developer
//  Studio Application object

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

STDMETHODIMP CCommands::ActivateVCFBuilderEnvironment() 
{
	//

	// TODO: Replace this with the actual code to execute this command
	//  Use m_pApplication to access the Developer Studio Application object,
	//  and VERIFY_OK to see error strings in DEBUG builds of your add-in
	//  (see stdafx.h)

	//VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	//::MessageBox(NULL, "VCFBuilder Command invoked.", "VCFBuilder", MB_OK | MB_ICONINFORMATION);
	//VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));

	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CMDIFrameWnd* frame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	if ( NULL != frame ) {
		if ( NULL != frame->GetSafeHwnd() )	{			
			if ( NULL == VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd ) 	{
				VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd = (VCFBuilderMDIChild*)frame->CreateNewChild( RUNTIME_CLASS(VCFBuilderMDIChild), IDR_VCF_MDICHILD, NULL, NULL );
				VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->MDIMaximize();
				VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->ActivateFrame();
				VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->SetTitle( "VCF Builder" );
				VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->SetWindowText( "VCF Builder" );
				frame->DrawMenuBar();
			}
			else {
				if ( NULL != VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->GetSafeHwnd() )	{	
					VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->MDIMaximize();
					VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->ActivateFrame();
					frame->DrawMenuBar();
				}
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CCommands::OpenProject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	

	return S_OK;
}

STDMETHODIMP CCommands::NewProject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if ( NULL != VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd ) 	{
		VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd->newProject();
	}

	return S_OK;
}

STDMETHODIMP CCommands::SaveProject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	

	return S_OK;
}

STDMETHODIMP CCommands::SaveProjectAs()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	

	return S_OK;
}

STDMETHODIMP CCommands::NewForm()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	

	return S_OK;
}

STDMETHODIMP CCommands::ActivateVCFBuilderEnvStandalone()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	AfxMessageBox( "ActivateVCFBuilderEnvStandalone" );

	return S_OK;
}
