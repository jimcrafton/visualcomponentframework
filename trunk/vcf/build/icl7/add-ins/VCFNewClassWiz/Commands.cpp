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

	CComPtr<IBuildProject> proj;
	
	if ( SUCCEEDED( this->m_piApplication->get_ActiveProject( (IDispatch**)&proj ) ) ){
		
		NewClassDlg dlg;
		
		CComBSTR projPath;
		proj->get_FullName( &projPath );


		if ( IDOK == dlg.DoModal() ){
					
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			
			CString headerFilename = dlg.m_headerName;

			_splitpath( dlg.m_headerName, drive, dir, fname, ext );

			if ( strlen(dir) <= 0 ) {
				headerFilename = projPath;
					
				_splitpath( headerFilename, drive, dir, fname, ext );

				headerFilename = drive;
				headerFilename += dir;

				_splitpath( dlg.m_headerName, drive, dir, fname, ext );

				headerFilename += fname;
				headerFilename += ext;
			}
			
			
			CString s = dlg.GetClassDecl();

			CFile file( headerFilename, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
			file.Write( s.GetBuffer(0), s.GetLength() );
			
			CString CPPFilename = dlg.m_CPPName;

			_splitpath( dlg.m_CPPName, drive, dir, fname, ext );

			if ( strlen(dir) <= 0 ) {
				CPPFilename = projPath;
					
				_splitpath( CPPFilename, drive, dir, fname, ext );

				CPPFilename = drive;
				CPPFilename += dir;

				_splitpath( dlg.m_CPPName, drive, dir, fname, ext );

				CPPFilename += fname;
				CPPFilename += ext;
			}
			

			if ( FALSE == dlg.m_isClassAnInterface ) {
				
				s = dlg.GetClassImpl();
				CFile file2( CPPFilename, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
				file2.Write( s.GetBuffer(0), s.GetLength() );
			}
			
			CComBSTR cppFile;
			cppFile = CPPFilename;
			_variant_t reserved;
			if ( FALSE == dlg.m_isClassAnInterface ) {
				proj->AddFile( cppFile, reserved );
			}


			CComBSTR headerFile = headerFilename;
			
			proj->AddFile( headerFile, reserved );			
			
		}
		
	}
	else {
		AfxMessageBox( "You don't have an active project - please create one before using this Class Wizard." );
	}



	return S_OK;
}


