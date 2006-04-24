// MFCIntegration1.h : main header file for the MFCINTEGRATION1 application
//

#if !defined(AFX_MFCINTEGRATION1_H__374259AE_0F41_4B92_B599_CE41359D8208__INCLUDED_)
#define AFX_MFCINTEGRATION1_H__374259AE_0F41_4B92_B599_CE41359D8208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCIntegration1App:
// See MFCIntegration1.cpp for the implementation of this class
//

class CMFCIntegration1App : public CWinApp
{
public:
	CMFCIntegration1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCIntegration1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	virtual int ExitInstance( );
// Implementation

public:
	//{{AFX_MSG(CMFCIntegration1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCINTEGRATION1_H__374259AE_0F41_4B92_B599_CE41359D8208__INCLUDED_)
