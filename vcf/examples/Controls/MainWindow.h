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


#endif //_MAINWINDOW_H__

/**
$Id$
*/
