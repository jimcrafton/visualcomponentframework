// PreHeaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vcfnewclasswiz.h"
#include "PreHeaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString GPLText = 	
	"This program is free software; you can redistribute it and/or\r"\
	"modify it under the terms of the GNU General Public License\r"\
	"as published by the Free Software Foundation; either version 2\r"\
	"of the License, or (at your option) any later version.\r"\
	"\r"\
	"This program is distributed in the hope that it will be useful,\r"\
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\r"\
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\r"\
	"GNU General Public License for more details.\r"\
	"\r"\
	"You should have received a copy of the GNU General Public License\r"\
	"along with this program; if not, write to the Free Software\r"\
	"Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\r";
	


CString VCFLicenseText = 
	"This program is free software; you can redistribute it and/or\r"\
	"modify it as you choose. In fact, you can do anything you would like\r"\
	"with it, so long as credit is given if used in commercial applications.\r"\
	"This program is distributed in the hope that it will be useful,\r"\
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\r"\
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\r"\
	"\rNB: This software will not save the world.\r";

/////////////////////////////////////////////////////////////////////////////
// PreHeaderDlg dialog


PreHeaderDlg::PreHeaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PreHeaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PreHeaderDlg)
	m_preDefinedHdrsSel = 0;
	m_preHdrText = _T("");
	//}}AFX_DATA_INIT
}


void PreHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PreHeaderDlg)
	DDX_CBIndex(pDX, IDC_PREDEFINED_HDRS, m_preDefinedHdrsSel);
	DDX_Text(pDX, IDC_PRE_HDR_TEXT, m_preHdrText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PreHeaderDlg, CDialog)
	//{{AFX_MSG_MAP(PreHeaderDlg)
	ON_CBN_SELCHANGE(IDC_PREDEFINED_HDRS, OnSelchangePredefinedHdrs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PreHeaderDlg message handlers

void PreHeaderDlg::OnSelchangePredefinedHdrs() 
{
	this->UpdateData();
	switch ( this->m_preDefinedHdrsSel ) 
	{
		case 0 :{
			this->m_preHdrText = "";
		}
		break;

		case 1 :{
			this->m_preHdrText = GPLText;
		}
		break;

		case 2 :{
			this->m_preHdrText = VCFLicenseText;
		}
		break;
	}
	this->UpdateData( FALSE );
}



BOOL PreHeaderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CFont font;
	font.CreatePointFont( 80, "Courier New" );
	CWnd* wnd = this->GetDlgItem( IDC_PRE_HDR_TEXT );
	wnd->SetFont( &font );
	font.Detach();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
