//Window.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
//#include "ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/WindowPeer.h"

using namespace VCF;

Window::Window()
{
	Application* app = Application::getRunningInstance();
	Control* owner = NULL;
	if ( NULL != app ) {
		owner = app->getMainWindow();
	}

	windowPeer_ = UIToolkit::createWindowPeer( this, owner );

	peer_ = dynamic_cast<ControlPeer*>(windowPeer_);

	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->create( this );
	peer_->setControl( this );


	menuBar_ = NULL;

	setHeight( getPreferredHeight() );

	setWidth( getPreferredWidth() );

	//add a close handler to get notified of the closing window
	FrameClose.addHandler( new WindowEventHandler<Window>( this, &Window::onClose, "onClose" ) );

	EventHandler* ev = new GenericEventHandler<Frame> ( this, &Frame::handleEvent, "Frame::handleEvent" );

	ComponentAdded += ev;
}

Window::Window( Control* control )
{

	windowPeer_ = UIToolkit::createWindowPeer( this, control );

	peer_ = dynamic_cast<ControlPeer*>(windowPeer_);

	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->create( this );
	peer_->setControl( this );


	menuBar_ = NULL;

	setHeight( getPreferredHeight() );

	setWidth( getPreferredWidth() );

	//add a close handler to get notified of the closing window
	FrameClose.addHandler( new WindowEventHandler<Window>( this, &Window::onClose, "onClose" ) );

	EventHandler* ev = new GenericEventHandler<Window> ( this, &Window::handleEvent, "Window::handleEvent" );

	ComponentAdded += ev;
}

Window::~Window()
{
	StringUtils::traceWithArgs( "In Window::~Window for instance %p\n", this );
}

void Window::destroy()
{
	Frame::destroy();
}

void Window::paint(GraphicsContext * context)
{
	Frame::paint( context );
}

void Window::setCaption( const String& caption )
{
	Frame::setCaption( caption );

	String text = caption;
	
	if ( getUseLocaleStrings() ) {
		text = System::getCurrentThreadLocale()->translate( text );
	}

	peer_->setText( text );
}

Rect Window::getClientBounds(const bool& includeBorder)
{
	if ( NULL == windowPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	return windowPeer_->getClientBounds();
}

void  Window::setClientBounds( Rect* bounds )
{
	if ( NULL == windowPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	windowPeer_->setClientBounds( bounds );
}


void Window::resizeChildren( Control* control )
{
	/*
	Rect* bounds = getClientBounds();
	Rect rect( 0.0, 0.0, bounds->getWidth(), bounds->getHeight() );
	resizeChildrenUsingBounds( &rect );
	*/
	Frame::resizeChildren(NULL);
}



void Window::beforeDestroy( ComponentEvent* event )
{
	//remove me from my parent control if neccessary
	Control* parent = getParent();
	if ( NULL != parent ) {
		Container* parentContainer = parent->getContainer();
		if ( NULL != parentContainer ) {
			parentContainer->remove( this );
		}
	}

	Frame::beforeDestroy( event );
}

MenuBar* Window::getMenuBar()
{
	return menuBar_;
}

void Window::setMenuBar( MenuBar* menuBar )
{
	menuBar_ = menuBar;
	if ( NULL != menuBar_ ){
		menuBar_->setFrame( this );
	}
}

void Window::close()
{
	if ( this->allowClose() ) {
		WindowEvent event( this, WINDOW_EVENT_CLOSE );
		FrameClose.fireEvent( &event );

		if ( NULL == windowPeer_ ){
			throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
		}
		windowPeer_->close();
	}

}

void Window::onClose( WindowEvent* e )
{
	EventHandler* ev = new GenericEventHandler<Window>( this, &Window::postClose );
	UIToolkit::postEvent( ev, new Event( this ) );
}

void Window::postClose( Event* event )
{
	//StringUtils::traceWithArgs( "Preparing to destroy window %p after a Window::close() call\n", this );

	Application* app = Application::getRunningInstance();
	if ( NULL != app ) {
		if ( app->getMainWindow() == this ) {
			return; //we're outta here - the main window will
					//get cleaned up automagically
		}
	}


	//check to nake sure we are not parented - if we are then we don't need to do
	//delete our selves
	if ( NULL != getParent() ) {
		return;
	}

	//StringUtils::traceWithArgs( "Destroying window %p\n", this );
	free();
}

void Window::setFrameStyle( const FrameStyleType& frameStyle )
{
	if ( NULL == windowPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}


	frameStyle_ = frameStyle;

	if ( !(Component::csDesigning & getComponentState()) ){
		windowPeer_->setFrameStyle( frameStyle_ );
	}
}

void Window::setFrameTopmost( const bool& isTopmost )
{
	Frame::setFrameTopmost( isTopmost );

	if ( !(Component::csDesigning & getComponentState()) ){
		if ( NULL == windowPeer_ ){
			throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
		}

		windowPeer_->setFrameTopmost( isTopmost );
	}
}

double Window::getPreferredWidth()
{
	return 500.0;
}

double Window::getPreferredHeight()
{
	return 500.0;
}

bool Window::isMaximized()
{
	return windowPeer_->isMaximized();
}

void Window::setMaximized( const bool maximized )
{
	windowPeer_->setMaximized( maximized );
}


bool Window::isMinimized()
{
	return windowPeer_->isMinimized();
}

void Window::setMinimized( const bool& minimized )
{
	windowPeer_->setMinimized( minimized );
}

void Window::restore()
{
	windowPeer_->restore();
}

void Window::setIconImage( Image* icon )
{
	windowPeer_->setIconImage( icon );
}

Image* Window::getIconImage()
{
	return NULL;
}

void Window::handleEvent( Event* event )
{
	Frame::handleEvent( event );
	switch ( event->getType() ){
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			MenuBar* menu = dynamic_cast<MenuBar*>(child);

			if ( NULL != menu ) {
				setMenuBar( menu );
			}
		}
		break;
	}
}

bool Window::isActiveFrame()
{
	return windowPeer_->isActiveWindow();
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.5  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.4.2.1  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.4  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/05/16 02:39:01  ddiego
*OSX code updates
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.36  2004/04/03 15:48:45  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.33.2.3  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.33.2.2  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.33.2.1  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.33  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.32.2.5  2003/11/04 04:19:23  ddiego
**** empty log message ***
*
*Revision 1.32.2.4  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.32.2.3  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.32.2.2  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.32.2.1  2003/08/17 21:48:22  ddiego
*fixed bug [ 788189 ] ComboBoxControl doesn't close when application loose
*focus. Also cleaned some old trace statements for debugging purposes.
*
*Revision 1.32  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.31.2.3  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.31.2.2  2003/07/21 03:08:30  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.31.2.1  2003/05/27 04:45:42  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.31  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.30.2.2  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.30.2.1  2003/03/12 03:13:27  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.30  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.29.2.5  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.29.2.4  2003/01/08 00:20:02  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.29.2.3  2002/12/27 23:05:11  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.29.2.2  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.29.2.1  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.29  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.28.4.1  2002/11/16 22:00:55  ddiego
*this fixes bug [ 633977 ] Windows not self deleteing then closed.
*Fix was simple - just needed to post an event handler after a recv
*a close event, and in the new event handler we delete the window.
*
*Revision 1.28  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.27.6.1  2002/08/13 04:28:23  ddiego
*bugs fixed:
*[ 585085 ] Can't get at multi selected filenames - this was just a matter of exposing a function that was already available in the
*peer class
*
*features:
*58839 Add a method to query closing a Frame, this required a change that included added a new event (FrameEvent and the corresponding
*FrameEventHandler) and a method, bool Frame::allowClose()
*
*Also made fixes in the VCF Builder to now take advantage of this, so the MainWindow class will now register an event
*handler to handler the FrameClosing event, and attempt to set the current workspace to NULL. If this does not happen then
*the closing event will fail and prevent the widnow from being shutdown. Woo hoo !
*
*Revision 1.27  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.26.4.2  2002/04/27 15:52:56  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.26.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.26  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


