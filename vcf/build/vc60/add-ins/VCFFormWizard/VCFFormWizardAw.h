#if !defined(AFX_VCFFORMWIZARDAW_H__CD90ED26_5FC4_44B8_A717_DF18DA621B7A__INCLUDED_)
#define AFX_VCFFORMWIZARDAW_H__CD90ED26_5FC4_44B8_A717_DF18DA621B7A__INCLUDED_

// VCFFormWizardaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see VCFFormWizard.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CVCFFormWizardAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CVCFFormWizardAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global VCFFormWizardaw.  (Its definition is in VCFFormWizardaw.cpp.)
extern CVCFFormWizardAppWiz VCFFormWizardaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCFFORMWIZARDAW_H__CD90ED26_5FC4_44B8_A717_DF18DA621B7A__INCLUDED_)
