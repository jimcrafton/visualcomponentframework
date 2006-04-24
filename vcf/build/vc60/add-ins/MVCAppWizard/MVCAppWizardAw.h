#if !defined(AFX_MVCAPPWIZARDAW_H__EAD00860_6256_4B86_9D0F_017D9F2E66AF__INCLUDED_)
#define AFX_MVCAPPWIZARDAW_H__EAD00860_6256_4B86_9D0F_017D9F2E66AF__INCLUDED_

// MVCAppWizardaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see MVCAppWizard.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CMVCAppWizardAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);
};

// This declares the one instance of the CMVCAppWizardAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global MVCAppWizardaw.  (Its definition is in MVCAppWizardaw.cpp.)
extern CMVCAppWizardAppWiz MVCAppWizardaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVCAPPWIZARDAW_H__EAD00860_6256_4B86_9D0F_017D9F2E66AF__INCLUDED_)
