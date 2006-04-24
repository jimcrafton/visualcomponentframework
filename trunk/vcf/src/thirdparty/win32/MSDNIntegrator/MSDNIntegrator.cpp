// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegrator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MSDNIntegrator.h"
#include "SplitPath.h"
#include "MSDNIntegration.h"

//#include "MSDNIntegratorDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp

BEGIN_MESSAGE_MAP(CMSDNIntegratorApp, CWinApp)
	//{{AFX_MSG_MAP(CMSDNIntegratorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp construction

CMSDNIntegratorApp::CMSDNIntegratorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMSDNIntegratorApp object

CMSDNIntegratorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp initialization


class CmdLine : public CCommandLineInfo {
public:
	CmdLine() :add(false), remove(false), action(-1) {

	}

	virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast ) {
		CCommandLineInfo::ParseParam( lpszParam, bFlag, bLast );

		if ( bFlag ) {
			if ( CString(lpszParam) == "guid" ) {
				action = guidFlag;
			}
			else if ( CString(lpszParam) == "chm" ) {
				action = chmFileNameFlag;
			}
			else if ( CString(lpszParam) == "chi" ) {
				action = chiFileNameFlag;
			}
			else if ( CString(lpszParam) == "add" ) {
				add = true;
				remove = false;
			}
			else if ( CString(lpszParam) == "remove" ) {
				add = false;
				remove = true;
			}
			else if ( CString(lpszParam) == "title" ) {
				action = titleFlag;
			}
			
			else {
				action = -1;
			}
		}
		else {
			switch ( action ) {
				case guidFlag : {
					guid = lpszParam;
				}
				break;

				case chiFileNameFlag : {
					chiFileName = lpszParam;
				}
				break;

				case chmFileNameFlag : {
					chmFileName = lpszParam;
				}
				break;

				case titleFlag : {
					title = lpszParam;
				}
				break;
				
			}
		}
	}

	enum {
		guidFlag = 0,
		chiFileNameFlag,
		chmFileNameFlag,
		titleFlag
	};

	CString guid;
	CString chiFileName;
	CString chmFileName;
	CString title;
	bool add;

	bool remove;

	int action;
};

//"{858cf701-5e04-48ba-968e-46569c787d5f}"

BOOL CMSDNIntegratorApp::InitInstance()
{	
	//SetRegistryKey(_T("Codejock Software Demos"));

	returnCode = 0;

	CmdLine cmdline;
	ParseCommandLine( cmdline );

	CMSDNIntegration::Get().SetTitleString(cmdline.title);
	CMSDNIntegration::Get().SetUniqueID(cmdline.guid);
	CMSDNIntegration::Get().SetHelpVer("1");
	CMSDNIntegration::Get().SetChmFile(cmdline.chmFileName);
	CMSDNIntegration::Get().SetChiFile(cmdline.chiFileName);


	if ( CMSDNIntegration::Get( ).IsInitialized( ) ) {
		if ( cmdline.add ) { 
			
			if (  CMSDNIntegration::Get( ).CanIntegrate( false, true ) )	{
				if ( CMSDNIntegration::Get( ).IntegrateMSDNCol( ) )  {
					if ( CMSDNIntegration::Get( ).IntegrateMSDNDat( ) ) {
						
					}
					else {
						//error
						returnCode = 1;
					}
				}
				else {
					//error
					returnCode = 1;
				}
			}
			else {
				returnCode = 1;
			}
		}
		else if ( cmdline.remove )  {
			if ( CMSDNIntegration::Get( ).RestoreMSDNDat( ) ) {

				if ( !CMSDNIntegration::Get( ).RestoreMSDNCol( ) ) 	{
					returnCode = 1;
				}
			}
			else {
				returnCode = 1;
			}
		}
	}	
	else {
		returnCode = 1;
	}

	return FALSE;
}

int CMSDNIntegratorApp::ExitInstance() 
{
	int res = CWinApp::ExitInstance();
	if ( res == 0 ) {
		res = returnCode;
	}
	return res;
}
