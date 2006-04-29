
#ifndef _WIN32PRINTDIALOG_H__
#define _WIN32PRINTDIALOG_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

class Control;

/**
class Win32PrintDialog documentation
*/
class Win32PrintDialog  : public Object, public CommonPrintDialogPeer {
public: 

	Win32PrintDialog( Control* owner );
	virtual ~Win32PrintDialog();

	virtual void setTitle( const String& title );

	virtual bool execute();

	virtual void setPrintInfo( PrintInfoHandle info );
	
	virtual PrintInfoHandle getPrintInfo();

	virtual void setNumberOfCopies( const ulong32& val );
	virtual ulong32 getNumberOfCopies();
	
	virtual void setStartPage( const ulong32& val );
	virtual ulong32 getStartPage();

	virtual void setEndPage( const ulong32& val );
	virtual ulong32 getEndPage();

	virtual void setPrintJobType( PrintSession::PrintJob val );
	virtual PrintSession::PrintJob getPrintJobType();

protected:
	String title_;
	Control* owner_;
	Win32PrintInfo printInfo_;
	static UINT CALLBACK PrintHookProc( HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );

};




};


#endif //_WIN32PRINTDIALOG_H__

/**
$Id$
*/
