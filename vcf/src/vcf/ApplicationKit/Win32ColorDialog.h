#ifndef _VCF_WIN32COLORDIALOG_H__
#define _VCF_WIN32COLORDIALOG_H__
//Win32ColorDialog.h

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

class Win32ColorDialog : public Object, public CommonColorDialogPeer {
public:
	Win32ColorDialog( Control* owner = NULL );

	virtual ~Win32ColorDialog();

	virtual Color* getSelectedColor();

	virtual void setSelectedColor( Color* selectedColor );

	virtual void setTitle( const String& title );

	virtual bool execute();

private:
	String title_;
	Color color_;
	Control* owner_;
};


};


#endif // _VCF_WIN32COLORDIALOG_H__

/**
$Id$
*/
