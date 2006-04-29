#ifndef _VCF_WIN32FONTDIALOG_H__
#define _VCF_WIN32FONTDIALOG_H__
//Win32FontDialog.h

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

class Win32FontDialog : public Object, public CommonFontDialogPeer  {
public:
	Win32FontDialog( Control* owner );

	virtual ~Win32FontDialog();

	virtual void setTitle( const String& title );

	virtual bool execute();

	virtual Font* getSelectedFont();

	virtual void setSelectedFont( Font* selectedFont );

private:
	Font font_;
	Control* owner_;
};


};


#endif // _VCF_WIN32FONTDIALOG_H__

/**
$Id$
*/
