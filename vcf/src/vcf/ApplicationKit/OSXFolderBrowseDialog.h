#ifndef _VCF_OSXFOLDERBROWSEDIALOG_H__
#define _VCF_OSXFOLDERBROWSEDIALOG_H__
//OSXFolderBrowseDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class OSXFolderBrowseDialog : public CommonFolderBrowseDialogPeer, public Object  {
public:
	OSXFolderBrowseDialog(Control* owner);

	virtual ~OSXFolderBrowseDialog();

	virtual void setTitle( const String& title );

	virtual bool execute();

	virtual void setDirectory( const String & directory );

	virtual String getDirectory();
protected:
	static void BrowseDlgCallbackProc( NavEventCallbackMessage callBackSelector, NavCBRecPtr callBackParms, void *callBackUD );
	String title_;
	String directory_;
	NavDialogCreationOptions dlgOptions_;
	bool browseDlgResult_;
};

}; //end of namespace VCF


#endif // _VCF_OSXFOLDERBROWSEDIALOG_H__

/**
$Id$
*/
