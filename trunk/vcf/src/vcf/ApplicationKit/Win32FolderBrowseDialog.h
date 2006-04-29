#ifndef _VCF_WIN32FOLDERBROWSEDIALOG_H__
#define _VCF_WIN32FOLDERBROWSEDIALOG_H__
//Win32FolderBrowseDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Win32FolderBrowseDialog : public CommonFolderBrowseDialogPeer, public Object  {

public:
	enum {
		TreeControlID = 0x3741
	};

	Win32FolderBrowseDialog();

	virtual ~Win32FolderBrowseDialog();

	virtual void setTitle( const String& title );

	virtual bool execute();

	virtual void setDirectory( const String & directory );

	virtual String getDirectory();
protected:
	static int CALLBACK BrowseDlgCallbackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData );
	static HTREEITEM getDriveRoot( HWND treeCtrl, HTREEITEM desktop, const String& driveName, std::vector<String>& pathComponents );
	static HTREEITEM getFinalItem( HWND treeCtrl, HTREEITEM driveRoot, std::vector<String>& pathComponents );
	String title_;
	String directory_;
};

}; //end of namespace VCF


#endif // _VCF_WIN32FOLDERBROWSEDIALOG_H__

/**
$Id$
*/
