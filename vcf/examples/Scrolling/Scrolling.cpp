//Scrolling.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"

using namespace VCF;


class ScrollingWindow : public Window {
public:
	ScrollingWindow(): currentImage_(NULL) {
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

		//add our event handler to the menu item
		fileOpenImageMenu->addMenuItemClickedHandler(
			new MenuItemEventHandler<ScrollingWindow>( this,ScrollingWindow::openImage, "ScrollingWindow::openImage" ) );



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
		scrollBarMgr_->setKeepScrollbarsVisible( true );

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

	void openImage( MenuItemEvent* e ) {
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

			scrollBarMgr_->setVirtualViewWidth( currentImage_->getWidth() );
			scrollBarMgr_->setVirtualViewHeight( currentImage_->getHeight() );
			repaint(); //repaint ourselves to update the new image

			FilePath fp = dlg.getFileName();
			infoLabel_->setCaption( StringUtils::format( "Image: %s Size: %d, %d",
															fp.getBaseName(true).c_str(),
															currentImage_->getWidth(),
															currentImage_->getHeight() ) );
		}
	}

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
*Revision 1.4  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


