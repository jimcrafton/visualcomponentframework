//ListBox.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/DefaultListItem.h"


using namespace VCF;


/**
*This example demonstrates how the different selection styles of a 
*ListBoxControl function. The three styles include single selection,
*when only 1 item can be selected at a time, multiselection, when 
*more than 1 item can be selected at a time, and extended selection.
*Extended selection is similar to multiselection, but can handle Ctrl+MouseDown
*and Shift+MouseDown selection. Experiment. 
*/

class ListBoxWindow : public Window {
public:
	ListBoxWindow() {
		setCaption( "ListBox" );
		setVisible( true );

		this->setUseColorForBackground( true );
	
		this->setWidth(600);
		this->setHeight(600);
		
		double labelHeight = 40.0;
		double listboxWidth = 160.0;
		double listboxHeight = 300.0;
		double horizSpace = 20.0;
		double vertSpace = 10.0;
	
		// construct labels
		Label* label1 = new Label();
		label1->setBounds(horizSpace, 10, listboxWidth, labelHeight);
		label1->setWordWrap( true );
		label1->setCaption( L"allowsMultiSelect_ = false" );
		label1->getFont()->setBold(false);	
	
		Label* label2 = new Label();
		label2->setBounds(listboxWidth + 2*horizSpace, 10, listboxWidth, labelHeight);
		label2->setWordWrap( true );
		label2->setCaption( L"allowsMultiSelect_ = true\nallowsExtendedSelect_ = false" );	
		label2->getFont()->setBold(false);	
	
		Label* label3 = new Label();
		label3->setBounds(2*listboxWidth + 3*horizSpace, 10, listboxWidth, labelHeight);
		label3->setWordWrap( true );
		label3->setCaption( L"allowsMultiSelect_ = true\nallowsExtendedSelect_ = true" );
		label3->getFont()->setBold(false);	

	
		//build ListBoxes with a border
		ListBoxControl* listBoxSingle = new ListBoxControl();
		listBoxSingle->setName( L"listBoxSingle" );
		listBoxSingle->setUseColorForBackground( true );

		/**
		This sets the selection style to single selection (allowsMultiSelect_ = false).
		*/
		listBoxSingle->setAllowsMultiSelect( false );

		/**
		This sets the selection style to single selection. We really
		don't need to set this now, because if allowsMultiSelect_ is false,
		the setting for allowsExtendedSelect_ has no effect.
		*/
		listBoxSingle->setAllowsExtendedSelect( false );


		ListBoxControl* listBoxMulti = new ListBoxControl();
		listBoxMulti->setName( L"listBoxMulti" );
		listBoxMulti->setUseColorForBackground( true );

		/**
		This sets the selection style to multi selection (allowsMultiSelect_ = true).
		*/
		listBoxMulti->setAllowsMultiSelect( true );

		/**
		This sets the selection style to not allow extended selection. It is 
		important to make this call if you DO NOT want extended selection AND
		allowsMultiSelect_ = true, because the default setting for allowsExtendedSelect_ is true.
		This may change in the future.
		*/
		listBoxMulti->setAllowsExtendedSelect( false );


		ListBoxControl* listBoxExtended = new ListBoxControl();
		listBoxExtended->setName( L"listBoxExtended" );
		listBoxExtended->setUseColorForBackground( true );
		listBoxExtended->setAllowsMultiSelect( true );

		/**
		This sets the selection style to allow extended selection.
		Technically we do not have to set this here if 
		allowsMultiSelect_ is true, because the default setting for
		allowsExtendedSelect_ is true (this might change in the future, as
		it is a little counter-intuitive).
		*/
		listBoxExtended->setAllowsExtendedSelect( true );

		listBoxSingle->setBounds(horizSpace, labelHeight + vertSpace, listboxWidth, listboxHeight);
		listBoxMulti->setBounds(listboxWidth + 2*horizSpace, labelHeight + vertSpace, listboxWidth, listboxHeight);
		listBoxExtended->setBounds(2*listboxWidth + 3*horizSpace, labelHeight + vertSpace, listboxWidth, listboxHeight);
	
		//add borders to list boxes
		Basic3DBorder* listBoxSingleBrdr = new Basic3DBorder();
		listBoxSingleBrdr->setInverted( true );
		listBoxSingle->setBorder(listBoxSingleBrdr);

		Basic3DBorder* listBoxMultiBrdr = new Basic3DBorder();
		listBoxMultiBrdr->setInverted( true );
		listBoxMulti->setBorder(listBoxMultiBrdr);

		Basic3DBorder* listBoxExtendedBrdr = new Basic3DBorder();
		listBoxExtendedBrdr->setInverted( true );
		listBoxExtended->setBorder(listBoxExtendedBrdr);

		//add scrollbars to list boxes
		ScrollbarManager* scrollbarManagerSingle = new ScrollbarManager();
		addComponent( scrollbarManagerSingle );
		scrollbarManagerSingle->setHasVerticalScrollbar( true );
		scrollbarManagerSingle->setHasHorizontalScrollbar( true );		
		scrollbarManagerSingle->setTarget( listBoxSingle );

		ScrollbarManager* scrollbarManagerMulti = new ScrollbarManager();
		addComponent( scrollbarManagerMulti );
		scrollbarManagerMulti->setHasVerticalScrollbar( true );
		scrollbarManagerMulti->setHasHorizontalScrollbar( true );
		scrollbarManagerMulti->setTarget( listBoxMulti );

		ScrollbarManager* scrollbarManagerExtended = new ScrollbarManager();
		addComponent( scrollbarManagerExtended );
		scrollbarManagerExtended->setHasVerticalScrollbar( true );
		scrollbarManagerExtended->setHasHorizontalScrollbar( true );
		scrollbarManagerExtended->setTarget( listBoxExtended );

		//add TextControl to display # of selected items
		TextControl* textCtrlSingle = new TextControl();
		textCtrlSingle->setName( L"textCtrlSingle" );
		TextControl* textCtrlMulti = new TextControl();
		textCtrlMulti->setName( L"textCtrlMulti" );
		TextControl* textCtrlExtended = new TextControl();
		textCtrlExtended->setName( L"textCtrlExtended" );

		textCtrlSingle->setBounds(horizSpace, labelHeight + 2*vertSpace + listboxHeight, listboxWidth, 20.0);
		textCtrlMulti->setBounds(2*horizSpace + listboxWidth, labelHeight + 2*vertSpace + listboxHeight, listboxWidth, 20.0);
		textCtrlExtended->setBounds(3*horizSpace + 2*listboxWidth, labelHeight + 2*vertSpace + listboxHeight, listboxWidth, 20.0);

		// Populate list boxes with some dummy list items.
		ListModel* singleModel = listBoxSingle->getListModel();
		ListModel* multiModel = listBoxMulti->getListModel();
		ListModel* extendedModel = listBoxExtended->getListModel();

		for(int j=0; j<60; j++){
			String indx = StringUtils::toString(j);
			String capt = L"DefaultListItem " + indx;
		
			singleModel->addItem( new DefaultListItem( singleModel, capt ) );
			multiModel->addItem( new DefaultListItem( multiModel, capt ) );
			extendedModel->addItem( new DefaultListItem( extendedModel, capt ) );
		}

		//add buttons for deselecting all selected items
		CommandButton* btnSingle = new CommandButton();
		CommandButton* btnMulti = new CommandButton();
		CommandButton* btnExtended = new CommandButton();
	
		btnSingle->setBounds( horizSpace, labelHeight + 3*vertSpace + listboxHeight + 20, listboxWidth, 25.0 );
		btnMulti->setBounds( 2*horizSpace + listboxWidth, labelHeight + 3*vertSpace + listboxHeight + 20, listboxWidth, 25.0 );
		btnExtended->setBounds( 3*horizSpace + 2*listboxWidth, labelHeight + 3*vertSpace + listboxHeight + 20, listboxWidth, 25.0 );		
	
		btnSingle->setCaption( "Deselect All" );
		btnMulti->setCaption( "Deselect All" );
		btnExtended->setCaption( "Deselect All" );
	

		//add Controls to MainWindow
		this->setWidth(3*listboxWidth+4*horizSpace + 8);
		
		this->add(label1);
		this->add(label2);
		this->add(label3);

		this->add(listBoxSingle);
		this->add(listBoxMulti);
		listBoxExtended->setAnchor( AnchorLeft | AnchorRight );
		this->add(listBoxExtended);

		this->add(textCtrlSingle);
		this->add(textCtrlMulti);
		textCtrlExtended->setAnchor( AnchorLeft | AnchorRight );
		this->add(textCtrlExtended);

		this->add(btnSingle);
		this->add(btnMulti);
		btnExtended->setAnchor( AnchorLeft | AnchorRight );
		this->add(btnExtended);
	
		//add SelectionChanged handlers for each listbox.
		listBoxSingle->SelectionChanged.addHandler( new ItemEventHandler<ListBoxWindow>(this, &ListBoxWindow::getListBoxSingleInfo, "ListBoxWindow::getListBoxSingleInfo"));
		listBoxMulti->SelectionChanged.addHandler( new ItemEventHandler<ListBoxWindow>(this, &ListBoxWindow::getListBoxMultiInfo, "ListBoxWindow::getListBoxMultiInfo"));
		listBoxExtended->SelectionChanged.addHandler( new ItemEventHandler<ListBoxWindow>(this, &ListBoxWindow::getListBoxExtendedInfo, "ListBoxWindow::getListBoxExtendedInfo"));
	
		//add ButtonClicked handlers for each command button.	
		btnSingle->ButtonClicked.addHandler( new ButtonEventHandler<ListBoxWindow>( this, &ListBoxWindow::onbtnSingleClicked, "ListBoxWindow::onbtnSingleClicked" ) );
		btnMulti->ButtonClicked.addHandler( new ButtonEventHandler<ListBoxWindow>( this, &ListBoxWindow::onbtnMultiClicked, "ListBoxWindow::onbtnMultiClicked" ) );
		btnExtended->ButtonClicked.addHandler( new ButtonEventHandler<ListBoxWindow>( this, &ListBoxWindow::onbtnExtendedClicked, "ListBoxWindow::onbtnExtendedClicked" ) );

	}

	virtual ~ListBoxWindow(){};


	void getListBoxSingleInfo( VCF::ItemEvent* );
	void getListBoxMultiInfo( VCF::ItemEvent* );
	void getListBoxExtendedInfo( VCF::ItemEvent* );

	void getListBoxInfo(VCF::ListBoxControl* LBC, VCF::TextControl* txtCtrl);

	void onbtnSingleClicked( VCF::ButtonEvent* );
	void onbtnMultiClicked( VCF::ButtonEvent* );
	void onbtnExtendedClicked( VCF::ButtonEvent* );


};

/** This is our main function that calculates the # of selected items in 
a list box and displays the # in a corresponding text control. This is called
by each of the list box control and button handlers that we added. Those handlers
find the correct MyListBox and CommandButton instances and pass pointers to them to
this function.
*/
void ListBoxWindow::getListBoxInfo(ListBoxControl* LBC, TextControl* txtCtrl){
	Enumerator<ListItem*>* myvec = LBC->getSelectedItems();	
	
	int sz = 0;    
	while( myvec->hasMoreElements() ){
		sz += 1;
		ListItem* li = myvec->nextElement();
	}
	String text = StringUtils::toString( sz ) + " items selected";	
	txtCtrl->getTextModel()->setText( text );

}

void ListBoxWindow::onbtnSingleClicked( ButtonEvent*  ){	
	ListBoxControl* LBC = (ListBoxControl*)this->findComponent( "listBoxSingle" );
	TextControl* txtCtrl = (TextControl*)this->findComponent( "textCtrlSingle" );
	LBC->deselectAllItems();	
	getListBoxInfo(LBC, txtCtrl);
}

void ListBoxWindow::onbtnMultiClicked( ButtonEvent*  ){	
	ListBoxControl* LBC = (ListBoxControl*)this->findComponent( "listBoxMulti" );
	TextControl* txtCtrl = (TextControl*)this->findComponent( "textCtrlMulti" );
	LBC->deselectAllItems();	
	getListBoxInfo(LBC, txtCtrl);	
}

void ListBoxWindow::onbtnExtendedClicked( ButtonEvent*  ){	
	ListBoxControl* LBC = (ListBoxControl*)this->findComponent( "listBoxExtended" );
	TextControl* txtCtrl = (TextControl*)this->findComponent( "textCtrlExtended" );
	LBC->deselectAllItems();	
	getListBoxInfo(LBC, txtCtrl);
}

void ListBoxWindow::getListBoxSingleInfo( ItemEvent* )
{
	ListBoxControl* LBC = (ListBoxControl*)this->findComponent( "listBoxSingle" );	
	TextControl* txtCtrl = (TextControl*)this->findComponent( "textCtrlSingle" );
	getListBoxInfo(LBC, txtCtrl);	
}

void ListBoxWindow::getListBoxMultiInfo( ItemEvent* )
{
	ListBoxControl* LBC = (ListBoxControl*)this->findComponent( "listBoxMulti" );	
	TextControl* txtCtrl = (TextControl*)this->findComponent( "textCtrlMulti" );
	getListBoxInfo(LBC, txtCtrl);	
}

void ListBoxWindow::getListBoxExtendedInfo( ItemEvent* )
{
	ListBoxControl* LBC = (ListBoxControl*)this->findComponent( "listBoxExtended" );	
	TextControl* txtCtrl = (TextControl*)this->findComponent( "textCtrlExtended" );
	getListBoxInfo(LBC, txtCtrl);
}





class ListBoxApplication : public Application {
public:

	ListBoxApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new ListBoxWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 50.0, 50.0, 650.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ListBoxApplication( argc, argv );

	Application::main();
	
	return 0;
}


