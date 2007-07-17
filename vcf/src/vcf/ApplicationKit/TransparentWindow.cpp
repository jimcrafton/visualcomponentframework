//TransparentWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TransparentWindowPeer.h"
#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/TransparentWindow.h"

using namespace VCF;


TransparentWindow::TransparentWindow( Frame* frame ):
	Frame(),
	transparentWndPeer_(NULL),
	windowPeer_(NULL)
{
	transparentWndPeer_ = UIToolkit::createTransparentWindowPeer( this );

	peer_ = dynamic_cast<ControlPeer*>(transparentWndPeer_);

	windowPeer_ = dynamic_cast<WindowPeer*>(transparentWndPeer_);

	peer_->create( this );
	peer_->setControl( this );

	//add a close handler to get notified of the closing window
	FrameClose.add( new ClassProcedure1<FrameEvent*,TransparentWindow>( this, &TransparentWindow::onClose, "onClose" ) );
}

TransparentWindow::~TransparentWindow()
{

}

void  TransparentWindow::setClientBounds( Rect* bounds )
{
	windowPeer_->setClientBounds( bounds );
}

void TransparentWindow::close()
{
	FrameEvent event( this, Frame::CLOSE_EVENT );
	FrameClose( &event );
	
	if ( NULL == windowPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	windowPeer_->close();
}

void TransparentWindow::setBorderPath( Path* path )
{
	windowPeer_->setBorderPath( path );
}

void TransparentWindow::setAlpha( const double& alphaValue )
{
	transparentWndPeer_->setAlpha( alphaValue );
}

double TransparentWindow::getAlpha()
{
	return transparentWndPeer_->getAlpha();
}

void TransparentWindow::setAlphaImage( Image* img )
{
	transparentWndPeer_->setAlphaImage( img );
}

void TransparentWindow::onClose( FrameEvent* e )
{
	EventHandler* ev = new ClassProcedure1<Event*,TransparentWindow>( this, &TransparentWindow::postClose );
	UIToolkit::postEvent( ev, new Event( this ) );
}

void TransparentWindow::postClose( Event* event )
{
	//check to make sure we are not parented - if we are then we don't need to do
	//delete our selves
	if ( NULL != getParent() ) {
		return;
	}
	
	free();
}