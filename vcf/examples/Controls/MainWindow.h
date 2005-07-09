#ifndef _MAINWINDOW_H__
#define _MAINWINDOW_H__

//MainWindow.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ControlsKit.h"

/**
*Class MainWindow documentation
*/
class MainWindow : public VCF::Window {
public:
	MainWindow();

	virtual ~MainWindow();
	void onHelpAbout( VCF::MenuItemEvent* e );
protected:

private:
	//Our primary TabbedPages control
	VCF::TabbedPages* mainPages_;
	VCF::TabModel* mainPagesModel_;

	//individual TabPage

	VCF::TabPage* listBoxPage_;
	VCF::TabPage* bordersPage_;
	VCF::TabPage* buttonsPage_;
	VCF::TabPage* textPage_;
	VCF::TabPage* treePage_;

public:
	//related to ListBoxTabPage
	void makeListBoxPage();
	void listBox1Change( VCF::ItemEvent* );
	void onbtnRemove( VCF::ButtonEvent* );
	void onbtnDeselect( VCF::ButtonEvent* );
	void onbtnAddItemClicked( VCF::ButtonEvent* );
	void onrbSingleSelClicked( VCF::ButtonEvent* );
	void onrbMultiSelClicked( VCF::ButtonEvent* );
	void onrbExtendedSelClicked( VCF::ButtonEvent* );

public:
	VCF::ListBoxControl* listBox1_;
	VCF::TextControl* txtCtrlAddToListBox_;


	//fills the pages with controls
public:
	void makeButtonsPage();

	void makeTextPage();

	void makeTreePage();


	//related to buttonsTabPage
public:
	void makeBordersPage();
	void onButtonClicked( ButtonEvent* e );

	VCF::Panel* basic3DBorderPanel_;
	VCF::Panel* light3DBorderPanel_;
	VCF::Panel* etchedBorderPanel_;
	VCF::Panel* colorEtchedBorderPanel_;

	void onSingletextCtrlSelectionChanged( VCF::Event* e );
};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:34  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.2.7  2005/06/26 01:40:25  marcelloptr
*added images to a PushButton
*
*Revision 1.2.2.6  2005/05/22 04:04:29  ddiego
*more text edit fixes.
*
*Revision 1.2.2.5  2005/05/05 14:18:42  marcelloptr
*standard VCF formatting
*
*Revision 1.2.2.4  2005/05/05 12:42:25  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2.2.3  2005/05/04 01:20:38  marcelloptr
*member variables following VCF standard
*
*Revision 1.2.2.2  2005/04/25 00:11:55  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.2.2.1  2005/03/06 22:50:53  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/12/01 04:15:00  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.5  2004/10/01 17:06:00  dougtinkham
*updated Borders tab page
*
*Revision 1.1.2.4  2004/09/19 20:10:31  marcelloptr
*minor changes
*
*Revision 1.1.2.2  2004/08/30 03:50:47  dougtinkham
*added copyright
*
*/

#endif //_MAINWINDOW_H__


