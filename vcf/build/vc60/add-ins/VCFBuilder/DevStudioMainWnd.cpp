// DevStudioMainWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DevStudioMainWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDevStudioMainWnd * CDevStudioMainWnd::globalDevStudioMainWnd = NULL;

/////////////////////////////////////////////////////////////////////////////
// CDevStudioMainWnd

CDevStudioMainWnd::CDevStudioMainWnd(HWND hWndSubclass):
	CSubClassWnd( hWndSubclass )
{
	DoSubclass();

	TCHAR tmp[256];
	::GetWindowText( hWndSubclass, tmp, 256 );
	OutputDebugString( tmp );

}

CDevStudioMainWnd::~CDevStudioMainWnd()
{
}


BEGIN_MESSAGE_MAP(CDevStudioMainWnd, CSubClassWnd)
	//{{AFX_MSG_MAP(CDevStudioMainWnd)
	ON_WM_MDIACTIVATE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDevStudioMainWnd message handlers

void CDevStudioMainWnd::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CSubClassWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	TRACE( "CDevStudioMainWnd::OnMDIActivate\n" );	
}

void CDevStudioMainWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CSubClassWnd::OnActivate(nState, pWndOther, bMinimized);
	
	if ( WA_INACTIVE ==	nState ) {
		TRACE( "CDevStudioMainWnd::OnActivate state = WA_INACTIVE\n" );
	}
	else if ( WA_ACTIVE == nState ) {
		TRACE( "CDevStudioMainWnd::OnActivate state = WA_ACTIVE\n" );
	}
}

HWND CDevStudioMainWnd::GetMDIClientHWND()
{
	HWND result = NULL;
	char cClassName[256];
	
	result = GetTopWindow()->m_hWnd;
	::GetClassName(result, (LPTSTR)cClassName, sizeof(cClassName));
	while (strcmp(cClassName, "MDIClient") != 0)
	{
		result = ::GetNextWindow(result, GW_HWNDNEXT);
		ASSERT(result);
		GetClassName(result, (LPTSTR)cClassName, sizeof(cClassName));
	}
	
	return result;
}