// Commands.cpp : Implementation of CCommands
#include "stdafx.h"
#include "VCFNewClassWiz.h"
#include "Commands.h"
#include "NewClassDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
}

/////////////////////////////////////////////////////////////////////////////
// ICommands

STDMETHODIMP CCommands::NewVCFClass()
{
	// obtain the MSDEV CWinApp object:
	// (this is the "magic")
	CWinApp* pApp = AfxGetApp();

	// IF THIS ASSERT FIRES, THEN YOU ARE LIKELY LINKING TO THE DEBUG MFC LIBRARY
	// YOU CANNOT DO THIS BECAUSE MSDEV IS LINKED TO THE RELEASE MFC LIBRARY
	// BEST THING TO DO IS DELETE YOUR DEBUG CONFIG AND MAKE A NEW ONE BASED 
	// ON YOUR EXISTING RELEASE CONFIG.  THEN, ADD DEBUG SUPPORT TO THE 
	// COMPILE AND LINK OPTIONS.  THIS WORKS BECAUSE YOU WILL STILL LINK TO
	// MFC42.DLL INSTEAD OF MFC42D.DLL
	ASSERT(pApp);

	if (NULL == pApp) return E_FAIL;

	
	
	NewClassDlg dlg;

	if ( IDOK == dlg.DoModal() ){
		CString s = dlg.GetClassDecl();
		CString filename = dlg.m_headerName;

		CFile file( filename, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
		file.Write( s.GetBuffer(0), s.GetLength() );

		filename = dlg.m_CPPName;
		s = dlg.GetClassImpl();
		CFile file2( filename, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
		file2.Write( s.GetBuffer(0), s.GetLength() );
	}


	return S_OK;
}


