// Page1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VPLAppWiz.h"
#include "Page1Dlg.h"
#include "VPLAppWizAw.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page1Dlg dialog


Page1Dlg::Page1Dlg()
	: CAppWizStepDlg(Page1Dlg::IDD)
{
	//{{AFX_DATA_INIT(Page1Dlg)
	m_additional = _T("");
	m_author = _T("");
	m_company = _T("");
	m_copyright = _T("");
	//}}AFX_DATA_INIT
}


void Page1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page1Dlg)
	DDX_Control(pDX, IDC_IMAGE, m_image);
	DDX_Text(pDX, IDC_ADDITIONAL, m_additional);
	DDX_Text(pDX, IDC_AUTHOR, m_author);
	DDX_Text(pDX, IDC_COMPANY, m_company);
	DDX_Text(pDX, IDC_COPYRIGHT, m_copyright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(Page1Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page1Dlg message handlers

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

BOOL Page1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	// TODO: Set template variables based on the dialog's data.

	VPLAppWizaw.m_Dictionary[_T("AUTHOR")] = m_author;
	VPLAppWizaw.m_Dictionary[_T("COMPANY")] = m_company;
	VPLAppWizaw.m_Dictionary[_T("COPYRIGHT")] = m_copyright;
	VPLAppWizaw.m_Dictionary[_T("ADDTL")] = m_additional;

	VPLAppWizaw.m_Dictionary[_T("PKG_UUID")] = newUUID();



	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}

BOOL Page1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
	CBitmap bmp;
	bmp.LoadBitmap( IDB_SPLASH );
	m_image.SetBitmap( bmp );
	bmp.Detach();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


