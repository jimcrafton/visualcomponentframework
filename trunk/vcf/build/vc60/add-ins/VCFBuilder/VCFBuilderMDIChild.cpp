// VCFBuilderMDIChild.cpp : implementation file
//

#include "stdafx.h"
#include "VCFBuilder.h"
#include "VCFBuilderMDIChild.h"
#include "VCFBuilderHostView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


VCFBuilderMDIChild* VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd = NULL;

HICON VCFBuilderMDIChild::globalVCFBuilderIcon = NULL;

/////////////////////////////////////////////////////////////////////////////
// VCFBuilderMDIChild

IMPLEMENT_DYNCREATE(VCFBuilderMDIChild, CMDIChildWnd)

VCFBuilderMDIChild::VCFBuilderMDIChild()
{
}

VCFBuilderMDIChild::~VCFBuilderMDIChild()
{	
	VCFBuilderMDIChild::globalVCFBuilderMDIChildWnd = NULL;
}


BEGIN_MESSAGE_MAP(VCFBuilderMDIChild, CMDIChildWnd)
	//{{AFX_MSG_MAP(VCFBuilderMDIChild)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VCFBuilderMDIChild message handlers

BOOL VCFBuilderMDIChild::PreCreateWindow(CREATESTRUCT& cs) 
{
	CMDIChildWnd::PreCreateWindow(cs);
	
	cs.dwExStyle = 0;

	cs.lpszClass = AfxRegisterWndClass( CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW, NULL, NULL, 
										VCFBuilderMDIChild::globalVCFBuilderIcon );

	return TRUE;
}

int VCFBuilderMDIChild::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetWindowText( "VCF Builder" );
	this->SetTitle( "VCF Builder" );
	VCFBuilderHostView* vcfViewHost = new VCFBuilderHostView();
	vcfViewHost->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, AFX_IDW_PANE_FIRST );
	
	return 0;
}

void VCFBuilderMDIChild::newProject()
{
	VCFBuilderHostView* vcfViewHost = (VCFBuilderHostView*)GetActiveView();
	vcfViewHost->newProject();
}
