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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/10/30 20:27:26  ddiego
*added osx color dialog and browse for folder dialog
**
*/


#endif // _VCF_OSXFOLDERBROWSEDIALOG_H__


