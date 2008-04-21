//Window.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/MenuManager.h"



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
	FrameClose += new ClassProcedure1<FrameEvent*,Window>( this, &Window::onClose, "onClose" );

	ComponentAdded += new ClassProcedure1<Event*,Frame> ( this, &Frame::handleEvent, "Frame::handleEvent" );

	MenuManager::registerWindow( this );
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
	FrameClose += new ClassProcedure1<FrameEvent*,Window>( this, &Window::onClose, "onClose" );

	ComponentAdded += new ClassProcedure1<Event*,Frame> ( this, &Frame::handleEvent, "Frame::handleEvent" );
}

Window::~Window()
{
	StringUtils::trace( Format("In Window::~Window for instance %p\n") % this );
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
	Frame::resizeChildren(control);
}



void Window::beforeDestroy( ComponentEvent* event )
{
	//remove me from my parent control if neccessary
	Control* parent = getParent();
	if ( NULL != parent ) {
		Container* parentContainer = parent->getContainer();
		if ( NULL != parentContainer ) {
			//parentContainer->remove( this );
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
		MenuManager::registerMenuBar( menuBar_ );
	}
}

void Window::close()
{
	if ( this->allowClose() ) {
		FrameEvent event( this, Frame::CLOSE_EVENT );
		FrameClose( &event );

		if ( NULL == windowPeer_ ){
			throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
		}
		windowPeer_->close();
	}

}

void Window::onClose( FrameEvent* e )
{
	EventHandler* ev = new ClassProcedure1<Event*,Window>( this, &Window::postClose );
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

void Window::setBorderPath( Path* path )
{
	windowPeer_->setBorderPath( path );
}

/**
$Id$
*/
