#ifndef _VCF_OSXCOLORDIALOG_H__
#define _VCF_OSXCOLORDIALOG_H__
//OSXColorDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



namespace VCF {

class Control;

class OSXColorDialog : public Object, public CommonColorDialogPeer {
public:
	OSXColorDialog( Control* owner = NULL );

	virtual ~OSXColorDialog();

	virtual Color* getSelectedColor();

	virtual void setSelectedColor( Color* selectedColor );

	virtual void setTitle( const String& title );

	virtual bool execute();

protected:
	String title_;
	Color color_;
	Control* owner_;
};


};


#endif // _VCF_OSXCOLORDIALOG_H__

/**
$Id$
*/
