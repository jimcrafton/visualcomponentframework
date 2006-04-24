#ifndef _VCF_COMMONPRINTDIALOG_H__
#define _VCF_COMMONPRINTDIALOG_H__
//CommonPrintDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF{
class CommonPrintDialogPeer;

/**
\class CommonPrintDialog CommonPrintDialog.h "vcf/ApplicationKit/CommonPrintDialog.h"
A class for displaying a common print dialog. 
*/
class APPLICATIONKIT_API CommonPrintDialog : public VCF::CommonDialog {
public:
	CommonPrintDialog( Control* owner );
	virtual ~CommonPrintDialog();


	/**
	Displays the print dialog. If the user
	hit's OK, the function will return true
	and you can start a print session, otherwise
	it will return false.
	*/
	virtual bool execute();
	
	
	String getTitle();

	/**
	Sets the title of the dialog
	*/
	void setTitle( const String& title );

	/**
	Sets the number of copies of the document you'd like 
	to make. This value may be changed by the user.
	*/
	void setNumberOfCopies( const ulong32& val );
	ulong32 getNumberOfCopies();
	
	/**
	Sets the start page for the print dialog
	*/
	void setStartPage( const ulong32& val );
	ulong32 getStartPage();

	/**
	Sets the end page for the print dialog. If you
	have a document with 200 pages, and the start is
	set to 1, and the end to 10, then only pages
	1 through 10 will be printed.
	*/
	void setEndPage( const ulong32& val );
	ulong32 getEndPage();
	
	
	void setPrintJobType( PrintSession::PrintJob val );
	/**
	This is the type of print job the user selected/
	This is an enum which can be either Selected Page, Page Range, or All Pages.
	*/
	PrintSession::PrintJob getPrintJobType();

	

	PrintInfoHandle getPrintInfo();
	void setPrintInfo( PrintInfoHandle info );

protected:
	String title_;
	CommonPrintDialogPeer* peer_;
};

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.1.2.2  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.1.2.1  2005/09/02 01:01:20  ddiego
*changed some of the common dialogs around, was using a less clear class name.
*
*Revision 1.3  2004/12/01 04:31:20  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.7.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7  2003/05/17 20:37:01  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2002/12/25 22:06:16  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.5  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMMONPRINT_H__


