//Scrolling.cpp

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


class ScrollingWindow : public Window {
public:
	ScrollingWindow(): currentImage_(NULL), listBox_(NULL) {
		setCaption( "Scrolling" );
		setVisible( true );

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
		MenuItem* fileMenu = new DefaultMenuItem( "File", menuBar->getRootMenuItem(), menuBar );
		MenuItem* fileOpenImageMenu = new DefaultMenuItem( "Open Image...", fileMenu, menuBar );
		MenuItem* fileOpenListboxMenu = new DefaultMenuItem( "Open ListBox", fileMenu, menuBar );

		//add our event handler to the menu item
		fileOpenImageMenu->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this,&ScrollingWindow::openImage, "ScrollingWindow::openImage" ) );
		fileOpenListboxMenu->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this,&ScrollingWindow::openListboxMenu, "ScrollingWindow::openListboxMenu" ) );

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
		hasHorzScrollbarMenu_->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this, &ScrollingWindow::hasHorzScrollbar, "ScrollingWindow::hasHorzScrollbar" ) );
		hasVertScrollbarMenu_->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this, &ScrollingWindow::hasVertScrollbar, "ScrollingWindow::hasVertScrollbar" ) );
		keepHorzScrollbarVisibleMenu_->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this, &ScrollingWindow::keepHorzScrollbarVisible, "ScrollingWindow::keepHorzScrollbarVisible" ) );
		keepVertScrollbarVisibleMenu_->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this, &ScrollingWindow::keepVertScrollbarVisible, "ScrollingWindow::keepVertScrollbarVisible" ) );


		//set the border of the window, this will give us a nice etched border
		EtchedBorder* bdr = new EtchedBorder();
		bdr->setStyle( GraphicsContext::etSunken );
		setBorder( bdr );

		//this is what gives us the capability to easily control the
		//scrollbars for the form window
		scrollBarMgr_ = new ScrollbarManager();
		scrollBarMgr_->setTarget( this );
		addComponent( scrollBarMgr_ );

		scrollBarMgr_->setHasHorizontalScrollbar( true );
		scrollBarMgr_->setHasVerticalScrollbar( true );
		scrollBarMgr_->setKeepScrollbarsVisible( true, true );
		updateMenuHasHorzScrollbar();
		updateMenuHasVertScrollbar();
		updateMenuKeepHorzScrollbarVisible();
		updateMenuKeepVertScrollbarVisible();

		scrollBarMgr_->setHorizontalLeftScrollSpace( 200 );

		panel_ = new Panel();
		add( panel_ );

		infoLabel_ = new Label();
		panel_->add( infoLabel_, AlignClient );

		Rect r;
		Scrollable* scrollable = getScrollable();
		scrollable->getHorizontalScrollRects( NULL, &r );
		panel_->setBounds( &r );
	}

	virtual ~ScrollingWindow(){
		if ( NULL != currentImage_ ) {
			delete currentImage_;
		}
	};

	virtual void handleEvent( Event* e ) {
		Window::handleEvent( e );
		if ( e->getType() == Control::CONTROL_SIZED ) {
			Scrollable* scrollable = getScrollable();
			if ( NULL != scrollable ) {
				Rect r;
				scrollable->getHorizontalScrollRects( NULL, &r );
				panel_->setBounds( &r );
			}
		}
	}

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint(ctx);

		if ( NULL != currentImage_ ) {

			Rect viewBounds = ctx->getViewableBounds();

			/**
			if we have an image, draw it centered within the available client
			rect
			*/
			Rect imageRect(0,0,currentImage_->getWidth(),currentImage_->getHeight());

			Point imagePos;
			imagePos = viewBounds.getTopLeft();


			//adjust the imagePos to be centered if neccessary
			if ( viewBounds.getWidth() > imageRect.getWidth() ) {
				imagePos.x_ = viewBounds.getWidth()/2.0 - imageRect.getWidth()/2.0;
			}

			if ( viewBounds.getHeight() > imageRect.getHeight() ) {
				imagePos.y_ = viewBounds.getHeight()/2.0 - imageRect.getHeight()/2.0;
			}


			//adjust the rect to the bare minimum rect needed
			imageRect.left_ = maxVal<>( 0.0,viewBounds.left_ );
			imageRect.right_ = minVal<double>( currentImage_->getWidth(), viewBounds.right_ );

			imageRect.top_ = maxVal<>( 0.0,viewBounds.top_ );
			imageRect.bottom_ = minVal<double>( currentImage_->getHeight(), viewBounds.bottom_ );

			ctx->drawPartialImage( imagePos, &imageRect , currentImage_ );
		}
	}

	void openListboxMenu( MenuItemEvent* e ) {
		if ( NULL != currentImage_ ) {
			delete currentImage_;
			currentImage_ = NULL;
		}

		/* hide the scrollbars of the main window 
		as the scrollbars of the listbox will be use */
		scrollBarMgr_->setHasHorizontalScrollbar( false );
		scrollBarMgr_->setHasVerticalScrollbar( false );
		updateMenuHasHorzScrollbar();
		updateMenuHasVertScrollbar();

		//add a ListBoxControl
		listBox_ = new ListBoxControl();		
		listBox_->setBorder( new Basic3DBorder( true ) );
		listBox_->setAllowsMultiSelect( false );
		//add scrollbar to listBox_
		ScrollbarManager* scrollbarManagerSingle = new ScrollbarManager();
		addComponent( scrollbarManagerSingle );
		scrollbarManagerSingle->setHasVerticalScrollbar( true );
		scrollbarManagerSingle->setHasHorizontalScrollbar( true );		
		scrollbarManagerSingle->setTarget( listBox_ );
		scrollbarManagerSingle->setKeepScrollbarsVisible( true, true );
		scrollbarManagerSingle->setVirtualViewVertStep( 17 );
		
		this->add( listBox_, AlignClient );
		
		//add some items to listBox_
		ListModel* listBoxModel = listBox_->getListModel();	
		for(int j=0; j<20; j++){
			String indx = StringUtils::toString(j);
			String capt = L"Very Ultra Hyper Extra Long ListItem " + indx;		
			listBoxModel->addItem( new DefaultListItem( listBoxModel, capt ) );			
		}
	}

	void openImage( MenuItemEvent* e ) {
		if ( NULL != listBox_ ) {
			 // try to comment out this !
			this->remove( listBox_ );
			listBox_->getOwner()->removeComponent( listBox_ );
			listBox_->free();
			listBox_ = NULL;
		}

		CommonFileOpen dlg( this );

		//get the available image loader extensions
		std::vector< std::pair<String,String> > contentTypes;

		/**
		this will get a list of all current available types that
		can currently be loaded by the VCF. The list is a series
		of std::pair objects. the std::pair.first element is a string
		that represents the file extension, and the std::pair.second
		represents a string that is the mime type for the extension
		*/
		GraphicsToolkit::getAvailableImageTypes( contentTypes );
		std::vector< std::pair<String,String> >::iterator it = contentTypes.begin();

		/*
		For each type, add a new filter to the dialog
		*/
		while ( it != contentTypes.end() ) {
			std::pair<String,String>& type = *it;

			dlg.addFilter( type.second + " (*." + type.first + " )", "*." + type.first );
			it ++;
		}


		if ( dlg.execute() ) {
			if ( NULL != currentImage_ ) {
				//delete our old image
				delete currentImage_;
			}

			//create a new image from the file name
			currentImage_ = GraphicsToolkit::createImage( dlg.getFileName() );
			
			scrollBarMgr_->setVirtualViewSize(  currentImage_->getWidth(), currentImage_->getHeight() ); 

			repaint(); //repaint ourselves to update the new image

			FilePath fp = dlg.getFileName();
			infoLabel_->setCaption( StringUtils::format( "Image: %s Size: %d, %d",
															fp.getBaseName(true).c_str(),
															currentImage_->getWidth(),
															currentImage_->getHeight() ) );
		}
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
	Image* currentImage_;
	Panel* panel_;

	Label* infoLabel_;
	ScrollbarManager* scrollBarMgr_;

	MenuItem* hasHorzScrollbarMenu_;
	MenuItem* hasVertScrollbarMenu_;
	MenuItem* keepHorzScrollbarVisibleMenu_;
	MenuItem* keepVertScrollbarVisibleMenu_;

	VCF::ListBoxControl* listBox_;
};




class ScrollingApplication : public Application {
public:

	ScrollingApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new ScrollingWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ScrollingApplication( argc, argv );


	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2004/12/01 04:15:12  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.4.2.11  2004/10/07 15:03:33  kiklop74
*Fixed building issues with bcb
*
*Revision 1.4.2.10  2004/09/21 22:47:50  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.4.2.9  2004/09/21 22:26:28  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.4.2.8  2004/09/21 05:55:21  dougtinkham
*replaced updateVirtualViewSize
*
*Revision 1.4.2.7  2004/09/19 22:06:12  marcelloptr
*fixed bug in listbox and image removal
*
*Revision 1.4.2.6  2004/09/19 20:01:04  marcelloptr
*scrollbars transitory changes
*
*Revision 1.4.2.4  2004/09/17 11:38:05  ddiego
*added program info support in library and process classes.
*
*Revision 1.4.2.3  2004/09/16 15:24:29  marcelloptr
*changed a name to the menu
*
*Revision 1.4.2.2  2004/09/15 22:18:37  dougtinkham
*replaced setVirtualViewWidth/Height with updateVirtualViewSize
*
*Revision 1.4.2.1  2004/09/15 14:19:13  marcelloptr
*added scrollbar menu
*
*Revision 1.4  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


