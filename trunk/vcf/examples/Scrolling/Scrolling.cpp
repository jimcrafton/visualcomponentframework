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
	ScrollingWindow(): currentImage_(NULL) {
		setCaption( "Scrolling" );

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

		//add our event handler to the menu item
		fileOpenImageMenu->MenuItemClicked +=
			new MenuItemEventHandler<ScrollingWindow>( this,&ScrollingWindow::openImage, "ScrollingWindow::openImage" );
		

		//set the border of the window, this will give us a nice etched border
		EtchedBorder* bdr = new EtchedBorder();
		bdr->setEdgeStyle( GraphicsContext::etSunken );
		setBorder( bdr );

		//this is what gives us the capability to easily control the
		//scrollbars for the form window
		scrollBarMgr_ = new ScrollbarManager();
		scrollBarMgr_->setTarget( this );
		addComponent( scrollBarMgr_ );

		scrollBarMgr_->setHasHorizontalScrollbar( true );
		scrollBarMgr_->setHasVerticalScrollbar( true );
		scrollBarMgr_->setKeepScrollbarsVisible( true, true );
		
		scrollBarMgr_->setHorizontalLeftScrollSpace( 200 );

		panel_ = new Panel();
		add( panel_ );

		infoLabel_ = new Label();
		panel_->add( infoLabel_, AlignClient );

		Rect r;
		Scrollable* scrollable = getScrollable();
		scrollable->getHorizontalScrollRects( NULL, &r );
		panel_->setBounds( &r );
		panel_->setIgnoreForParentScrolling( true );
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


	void openImage( MenuItemEvent* e ) {
		CommonFileOpenDialog dlg( this );

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
			infoLabel_->setCaption( Format( "Image: %s Size: %d, %d" )
									% fp.getBaseName(true).c_str()
									% currentImage_->getWidth()
									% currentImage_->getHeight() );
		}
	}



public:
	Image* currentImage_;
	Panel* panel_;

	Label* infoLabel_;
	ScrollbarManager* scrollBarMgr_;	
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
		mainWindow->show();

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
*Revision 1.7  2006/04/07 02:34:40  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.6.2.5  2006/03/19 20:50:14  ddiego
*adjusted the scrolling example to be rid of various extraneous
*code that only confused the point of the example. The extra code will
*be moved to another example.
*
*Revision 1.6.2.4  2006/03/16 18:45:23  kdmix
*setVisible(true) removed from constructor of the main window.
*
*Revision 1.6.2.3  2005/10/07 04:06:44  ddiego
*added new internet kit.
*
*Revision 1.6.2.2  2005/09/02 01:01:20  ddiego
*changed some of the common dialogs around, was using a less clear class name.
*
*Revision 1.6.2.1  2005/07/23 21:45:40  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.5.2.6  2005/06/06 02:34:04  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.5.2.5  2005/04/17 17:19:10  iamfraggle
*Small fixes
*
*Revision 1.5.2.4  2005/04/17 15:11:46  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.5.2.3  2005/03/10 17:27:37  marcelloptr
*set discrete scrolling as default behaviour for ListBoxControls
*
*Revision 1.5.2.2  2005/03/06 22:50:56  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.5.2.1  2005/01/17 18:51:15  marcelloptr
*added discrete scrolling behaviour to examples of ListBoxControl
*
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


