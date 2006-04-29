#ifndef _VCF_COMMONFONTDIALOG_H__
#define _VCF_COMMONFONTDIALOG_H__
//CommonFont.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class CommonFontDialogPeer;

class Control;

class Font;

/**
\class CommonFontDialog CommonFontDialog.h "vcf/ApplicationKit/CommonFontDialog.h"
This class is used to display a common font dialog. 
*/
class APPLICATIONKIT_API CommonFontDialog : public CommonDialog{
public:
	/**
	Creates a font dialog. If the owner is NULL then the dialog is 
	non modal. If the owner is \em not NULL then the dialog is modal
	relative to the control that started it. For most cases you 
	do \em not want to pass in a NULL owner.
	*/
	CommonFontDialog( Control* owner );

	virtual ~CommonFontDialog();

	/**
	Displays the dialog. If the user selects a font, then it 
	returns true, otherwise false.
	*/
	virtual bool execute();

	/**
	Returns the font the user selected, or NULL.
	*/
	Font* getSelectedFont();

	/**
	Sets the initial font characteristics to show when the 
	dialog is displayed. This is generally called \em before
	the execute() function is called.
	*/
	void setSelectedFont( Font* selectedFont );
private:
	CommonFontDialogPeer* peer_;
};

}; //end of namespace VCF


#endif // _VCF_COMMONFONTDIALOG_H__

/**
$Id$
*/
