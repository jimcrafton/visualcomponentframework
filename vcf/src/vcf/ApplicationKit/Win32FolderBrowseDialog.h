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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.8.2.2  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8.2.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.8  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.7.2.1  2004/03/26 00:59:47  ddiego
*fixed a C++ bug in the implementation of the
*Win32FolderBrowseDialog class. This was showing up when compiling
*for VC7.1.
*
*Revision 1.7  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.6  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/12 03:11:21  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32FOLDERBROWSEDIALOG_H__


