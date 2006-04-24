// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCIntegration1.h"
#include "ChildView.h"

#include "vcf/FoundationKit/StringTokenizer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace VCF;


/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CEdit )
	//{{AFX_MSG_MAP(CChildView)
	
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_INFO, OnFileInfo)
	
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CEdit::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= ES_MULTILINE | WS_VSCROLL| WS_HSCROLL;

	return TRUE;
}

void CChildView::OnFileOpen()
{
	CFileDialog dlg( TRUE );

	if ( dlg.DoModal() == IDOK ) {
		String fileName = dlg.GetPathName();
	
		FilePath path = fileName;

		FilePath win32Path = path;
		win32Path.transformToOSSpecific();

		CString msg;
		msg.Format( "Full path: %s\n Base name: %s\nExtension: %s\nDirectory: %s\nWin32 Path: %s", 
						path.getFileName().ansi_c_str(),
						path.getBaseName().ansi_c_str(), 
						path.getExtension().ansi_c_str(),
						path.getPathName( true ).ansi_c_str(),
						win32Path.getFileName().ansi_c_str());

		AfxMessageBox( msg );

		m_fileName = path;

		String fileContents;
		FileInputStream fs(path);
		fs >> fileContents;

		SetWindowText( fileContents.ansi_c_str() );
	}
}

void CChildView::OnFileInfo()
{
	String resString = System::getResourceBundle()->getString( StringUtils::toString(IDS_FILENAME_INFO) );

	FilePath path = m_fileName;

	FilePath win32Path = path;
	win32Path.transformToOSSpecific();

	CString text;
	GetWindowText( text );


	StringTokenizer tokens( (const char*) text );

	int lineCount = 0;
	while ( tokens.hasMoreElements() ) {
		tokens.nextElement();
		lineCount ++;
	}

	String msg = StringUtils::format( Format( "%s\nFull path: %s\nBase name: %s\nExtension: %s\nDirectory: %s\nWin32 Path: %s\nNumber of lines: %d") % 
					resString %
					path.getFileName() %
					path.getBaseName() %
					path.getExtension() %
					path.getPathName( true ) %
					win32Path.getFileName() %
					lineCount );


	AfxMessageBox( msg.ansi_c_str() );
}