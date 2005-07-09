// MFCIntegration2.h : main header file for the MFCINTEGRATION2 application
//

#if !defined(AFX_MFCINTEGRATION2_H__260D08A0_04E0_4423_85A5_A6DB15F9652C__INCLUDED_)
#define AFX_MFCINTEGRATION2_H__260D08A0_04E0_4423_85A5_A6DB15F9652C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCIntegration2App:
// See MFCIntegration2.cpp for the implementation of this class
//

class CMFCIntegration2App : public CWinApp
{
public:
	CMFCIntegration2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCIntegration2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	virtual int ExitInstance( );
public:
	//{{AFX_MSG(CMFCIntegration2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCINTEGRATION2_H__260D08A0_04E0_4423_85A5_A6DB15F9652C__INCLUDED_)
