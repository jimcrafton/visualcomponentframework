//PopupWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/PopupWindow.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


PopupWindow::PopupWindow( Window* owningWindow ):
	Frame(),
	popupPeer_(NULL),
	windowPeer_(NULL),
	modal_(false),
	owningWindow_(owningWindow)
{

	popupPeer_ = UIToolkit::createPopupWindowPeer( this, owningWindow_ );

	peer_ = dynamic_cast<ControlPeer*>(popupPeer_);

	windowPeer_ = dynamic_cast<WindowPeer*>(popupPeer_);

	peer_->create( this );
	peer_->setControl( this );

	//add a close handler to get notified of the closing window
	FrameClose.add( new ClassProcedure1<FrameEvent*,PopupWindow>( this, &PopupWindow::onClose, "onClose" ) );
}

PopupWindow::~PopupWindow()
{
	StringUtils::trace( "PopupWindow::~PopupWindow()\n" );
}


void PopupWindow::onClose( FrameEvent* e )
{
	EventHandler* ev = new ClassProcedure1<Event*,PopupWindow>( this, &PopupWindow::postClose );
	UIToolkit::postEvent( ev, new Event( this ) );
}

void PopupWindow::postClose( Event* event )
{
	//check to make sure we are not parented - if we are then we don't need to do
	//delete our selves
	if ( NULL != getParent() ) {
		return;
	}
	
	free();
}


void PopupWindow::paint( GraphicsContext * context )
{
	if ( NULL != getView() ) {
		getView()->paintView( context );
	}
	else {	

		Rect innerBounds = getClientBounds(false);

		Border* border = getBorder();
		if ( NULL != border ){
			border->paint( this, context );
			Rect tmpBounds = border->getClientRect( &innerBounds, this );
			innerBounds = tmpBounds;
			innerBounds.inflate( -1, -1 );
		}

		
		
		if ( useColorForBackground_ ) {
			context->setColor( getColor() );
		
			context->rectangle( innerBounds.left_, innerBounds.top_, innerBounds.right_, innerBounds.bottom_ );
		
			context->fillPath();		
		}
		else {	
			BackgroundState bkg;
			bkg.setEnabled( isEnabled() );
			bkg.setActive( (this == Frame::getActiveFrame()) && isActiveFrame() );
			bkg.colorType_ = SYSCOLOR_WINDOW;	
			
			context->drawThemeBackground( &innerBounds, bkg );
		}
		


		context->setCurrentFont( getFont() );

		Scrollable* scrollable = getScrollable();
		if ( scrollable ) {
			Rect viewBounds = context->getViewableBounds();

			Point origin = context->getOrigin();

			adjustViewableBoundsAndOriginForScrollable( context, viewBounds, origin );

			context->setOrigin( origin );

			context->setViewableBounds( viewBounds );
		}
	}

	paintChildren( context );
}

void PopupWindow::mouseDown( MouseEvent* event )
{
	
}

void PopupWindow::setClientBounds( Rect* bounds )
{
	if ( NULL == windowPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	windowPeer_->setClientBounds( bounds );
}

void PopupWindow::close()
{
	FrameEvent event( this, Frame::CLOSE_EVENT );
	FrameClose( &event );
	
	if ( NULL == windowPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	windowPeer_->close();
}

void PopupWindow::showModal()
{
	if ( NULL == popupPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	modal_ = true;
	popupPeer_->showModal();
}

void PopupWindow::showAsSheet( Window* owningWindow )
{
	if ( NULL == popupPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	modal_ = true;
	popupPeer_->showAsSheet( owningWindow );
}

void PopupWindow::show()
{
	if ( NULL == popupPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	modal_ = false;
	popupPeer_->show();
}


void PopupWindow::setBorderPath( Path* path )
{

}