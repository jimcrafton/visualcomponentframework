#ifndef _VCF_COMMONFILEBROWSEDIALOG_H__
#define _VCF_COMMONFILEBROWSEDIALOG_H__
//CommonFileBrowseDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF{

class CommonFolderBrowseDialogPeer;
/**
\class CommonFileBrowseDialog CommonFileBrowseDialog.h "vcf/ApplicationKit/CommonFileBrowseDialog.h"
This class displays a common dialog used to select a directory. 
*/
class APPLICATIONKIT_API CommonFileBrowseDialog : public VCF::CommonDialog {
public:
	CommonFileBrowseDialog();

	/**
	Creates a browse dialog. If the owner is NULL then the dialog is 
	non modal. If the owner is \em not NULL then the dialog is modal
	relative to the control that started it. For most cases you 
	do \em not want to pass in a NULL owner.
	*/
	CommonFileBrowseDialog( Control* owner );	

	virtual ~CommonFileBrowseDialog();

	/**
	Call this function to display the dialog.
	If the user selects a directory then it will return 
	true.
	*/
    virtual bool execute();

	/**
	Sets the initial directory for the dialog to 
	be set to. On Win32 this will cause the dialog
	tree to be navigated till it finds this directory.
	*/
	void setDirectory( const String & directory );

	/**
	Returns the directory the user chose. Only considered 
	valid to call if execute returned true.
	*/
	String getDirectory();

	/**
	Sets the title of the dialog
	*/
	void setTitle( const String& title );
private:
	CommonFolderBrowseDialogPeer* peer_;
};

};


#endif // _VCF_COMMONFILEBROWSEDIALOG_H__

/**
$Id$
*/
