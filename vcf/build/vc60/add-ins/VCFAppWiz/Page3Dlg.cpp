// Page3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "vcfwizard.h"
#include "Page3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page3Dlg dialog


Page3Dlg::Page3Dlg(CWnd* pParent /*=NULL*/)
	: CAppWizStepDlg(Page3Dlg::IDD)
{
	//{{AFX_DATA_INIT(Page3Dlg)
	m_useVCFNet = FALSE;
	m_useVCFRemote = FALSE;
	m_useOpenGL = FALSE;
	//}}AFX_DATA_INIT
}


void Page3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page3Dlg)
	DDX_Check(pDX, IDC_VCFNET, m_useVCFNet);
	DDX_Check(pDX, IDC_VCFREMOTE, m_useVCFRemote);
	DDX_Check(pDX, IDC_OPENGL, m_useOpenGL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page3Dlg, CDialog)
	//{{AFX_MSG_MAP(Page3Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_VCFNET, OnVcfnet)
	ON_BN_CLICKED(IDC_VCFREMOTE, OnVcfremote)
	ON_BN_CLICKED(IDC_OPENGL, OnOpengl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page3Dlg message handlers

void Page3Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CWnd* wnd = this->GetDlgItem( IDC_IMAGE3 );
	CDC* pDC = wnd->GetDC();
	CDC tmpDC;
	tmpDC.CreateCompatibleDC( NULL );
	CBitmap bmp;
	bmp.LoadBitmap( IDB_SPLASH );
	CBitmap* oldBMP = tmpDC.SelectObject( &bmp );
	BITMAP bmpInfo = {0};
	GetObject(bmp, sizeof(BITMAP), &bmpInfo );
	
	pDC->BitBlt( 1, 1, bmpInfo.bmWidth, bmpInfo.bmHeight, &tmpDC, 0, 0, SRCCOPY );	

	bmp.DeleteObject();
	tmpDC.SelectObject( oldBMP );
	tmpDC.DeleteDC();
	wnd->ReleaseDC( pDC );
	// Do not call CDialog::OnPaint() for painting messages
}

void Page3Dlg::OnVcfnet() 
{
	// TODO: Add your control notification handler code here
	m_useVCFNet = !m_useVCFNet;
	UpdateData( FALSE );
}

void Page3Dlg::OnVcfremote() 
{
	// TODO: Add your control notification handler code here
	m_useVCFRemote = !m_useVCFRemote;
	if ( TRUE == m_useVCFRemote ) {
		m_useVCFNet = TRUE;
	}
	UpdateData( FALSE );
}

void Page3Dlg::OnOpengl() 
{
	m_useOpenGL = !m_useOpenGL;
	UpdateData( FALSE );
}
