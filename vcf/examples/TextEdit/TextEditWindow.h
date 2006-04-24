#ifndef _TEXTEDITWINDOW_H__
#define _TEXTEDITWINDOW_H__
//TextEditWindow.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#define TEXTEDITWINDOW_CLASSID		"60614ad0-b9bb-40d4-94f3-34ceb0683c85"


/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"


/**
* The TextEditWindow class.
* 
* The TextEditWindow acts as a sort of "Controller" between the document
*   and the edit control, so that when the document's selection changes the text
*   control's selection is updated, and when the text control changes it's selection
*   the document is correspondingly updated.
@see TextEditWindow::onDocInitialized()
*/
class TextEditWindow  : public VCF::Window{
public: 
	_class_rtti_( TextEditWindow, "VCF::Window", TEXTEDITWINDOW_CLASSID )
	_class_rtti_end_

	TextEditWindow();
	virtual ~TextEditWindow();


protected:
	void onDocInitialized( VCF::Event* e ) ;	
	void onSelectionChanged( VCF::Event* e );
	void onModelChanged( VCF::Event* e );
	void initMenus();
	void initToolbar();

	void viewToolbarClicked( VCF::MenuItemEvent* e );
	void updateViewToolbar( VCF::MenuItemEvent* e );

	bool docSelectionChanging_;
};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:47  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/07/23 21:45:43  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.2.2.4  2005/05/04 20:58:54  marcelloptr
*standard file formatting and cvs log section added. More documentation.
*
*/


#endif //_TEXTEDITWINDOW_H__



