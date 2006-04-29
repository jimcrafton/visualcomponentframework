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


#endif // _VCF_COMMONPRINT_H__

/**
$Id$
*/
