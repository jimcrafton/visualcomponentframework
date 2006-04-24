//Scrolling2.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"

#include "vcf/ApplicationKit/DefaultListItem.h"

using namespace VCF;





class Scrolling2Window : public Window {
public:
	Scrolling2Window(): listBox_(NULL) {
		setCaption( "Scrolling 2" );

		//lets create a menu

		//create the menu bar - this will hold the menu items
		MenuBar* menuBar = new MenuBar();

		//set the window's menu bar
		setMenuBar( menuBar );

		//add the menu to this window's components
		addComponent( menuBar );

		/**
		create menu items, first arguemtn is the menu item name,
		then the parent,
		then the owning menu bar
		*/
		
		//add our event handler to the menu item
		
		// Scrollbar menu
		MenuItem* scrollMenu = new DefaultMenuItem( "FrameScrollbars", menuBar->getRootMenuItem(), menuBar );
		hasHorzScrollbarMenu_ = new DefaultMenuItem( "Horizontal", scrollMenu, menuBar );
		hasVertScrollbarMenu_ = new DefaultMenuItem( "Vertical", scrollMenu, menuBar );
		MenuItem* separator = new DefaultMenuItem( "", scrollMenu, menuBar );
		separator->setSeparator(true);
		separator->setEnabled( true );
		keepHorzScrollbarVisibleMenu_   = new DefaultMenuItem( "Keep horizontal visible", scrollMenu, menuBar );
		keepVertScrollbarVisibleMenu_   = new DefaultMenuItem( "Keep vertical visible", scrollMenu, menuBar );

		//add our event handler to the scrollbar menu
		hasHorzScrollbarMenu_->MenuItemClicked +=
			new MenuItemEventHandler<Scrolling2Window>( this, &Scrolling2Window::hasHorzScrollbar, "Scrolling2Window::hasHorzScrollbar" );
		hasVertScrollbarMenu_->MenuItemClicked +=
			new MenuItemEventHandler<Scrolling2Window>( this, &Scrolling2Window::hasVertScrollbar, "Scrolling2Window::hasVertScrollbar" );
		keepHorzScrollbarVisibleMenu_->MenuItemClicked +=
			new MenuItemEventHandler<Scrolling2Window>( this, &Scrolling2Window::keepHorzScrollbarVisible, "Scrolling2Window::keepHorzScrollbarVisible" );
		keepVertScrollbarVisibleMenu_->MenuItemClicked +=
			new MenuItemEventHandler<Scrolling2Window>( this, &Scrolling2Window::keepVertScrollbarVisible, "Scrolling2Window::keepVertScrollbarVisible" );



		//add a ListBoxControl
		listBox_ = new ListBoxControl();		
		listBox_->setBorder( new Basic3DBorder( true ) );
		listBox_->setAllowsMultiSelect( false );
		//add scrollbar to listBox_
		scrollBarMgr_ = new ScrollbarManager(this);
		
		scrollBarMgr_->setHasVerticalScrollbar( true );
		scrollBarMgr_->setHasHorizontalScrollbar( true );		
		scrollBarMgr_->setTarget( listBox_ );
		scrollBarMgr_->setKeepScrollbarsVisible( true, true );
		
		this->add( listBox_, AlignClient );
		
		//add some items to listBox_
		ListModel* listBoxModel = listBox_->getListModel();	
		for(int j=0; j<20; j++){
			String indx = StringUtils::toString(j);
			String capt = L"Very Ultra Hyper Extra Long ListItem " + indx;		
			listBoxModel->addItem( new DefaultListItem( listBoxModel, capt ) );			
		}

		updateMenuHasHorzScrollbar();
		updateMenuHasVertScrollbar();
		updateMenuKeepHorzScrollbarVisible();
		updateMenuKeepVertScrollbarVisible();
	}

	

	void hasHorzScrollbar( MenuItemEvent* e ) {
		scrollBarMgr_->setHasHorizontalScrollbar( !scrollBarMgr_->hasHorizontalScrollBar() );
		updateMenuHasHorzScrollbar();
		repaint();
	}

	void hasVertScrollbar( MenuItemEvent* e ) {
		scrollBarMgr_->setHasVerticalScrollbar( !scrollBarMgr_->hasVerticalScrollBar() );
		updateMenuHasVertScrollbar();
		repaint();
	}

	void keepHorzScrollbarVisible( MenuItemEvent* e ) {
		scrollBarMgr_->setKeepScrollbarsVisible( !scrollBarMgr_->getKeepHorzScrollbarVisible(), scrollBarMgr_->getKeepVertScrollbarVisible() );
		updateMenuKeepHorzScrollbarVisible();
		repaint();
	}

	void keepVertScrollbarVisible( MenuItemEvent* e ) {
		scrollBarMgr_->setKeepScrollbarsVisible( scrollBarMgr_->getKeepHorzScrollbarVisible(), !scrollBarMgr_->getKeepVertScrollbarVisible() );
		updateMenuKeepVertScrollbarVisible();
		repaint();
	}

	void updateMenuHasHorzScrollbar() {
		bool has = scrollBarMgr_->hasHorizontalScrollBar();
		hasHorzScrollbarMenu_->setChecked( has );
		keepHorzScrollbarVisibleMenu_->setEnabled( has );
	}

	void updateMenuHasVertScrollbar() {
		bool has = scrollBarMgr_->hasVerticalScrollBar();
		hasVertScrollbarMenu_->setChecked( has );
		keepVertScrollbarVisibleMenu_->setEnabled( has );
	}

	void updateMenuKeepHorzScrollbarVisible() {
		bool visible = scrollBarMgr_->getKeepHorzScrollbarVisible();
		keepHorzScrollbarVisibleMenu_->setChecked( visible );
	}

	void updateMenuKeepVertScrollbarVisible() {
		bool visible = scrollBarMgr_->getKeepVertScrollbarVisible();
		keepVertScrollbarVisibleMenu_->setChecked( visible );
	}

public:	
	ScrollbarManager* scrollBarMgr_;

	MenuItem* hasHorzScrollbarMenu_;
	MenuItem* hasVertScrollbarMenu_;
	MenuItem* keepHorzScrollbarVisibleMenu_;
	MenuItem* keepVertScrollbarVisibleMenu_;

	VCF::ListBoxControl* listBox_;
};




class Scrolling2Application : public Application {
public:

	Scrolling2Application( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new Scrolling2Window();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new Scrolling2Application( argc, argv );


	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2006/04/07 02:34:40  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.1.2.1  2006/03/19 21:03:45  ddiego
*added additional scrollign example.
*
*/


