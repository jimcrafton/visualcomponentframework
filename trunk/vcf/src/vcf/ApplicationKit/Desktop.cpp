//Desktop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Desktop.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DesktopPeer.h"



using namespace VCF;

Desktop* Desktop::create()
{
	if ( NULL == Desktop::desktopInstance ) {
		Desktop::desktopInstance = new Desktop();
		Desktop::desktopInstance->init();
	}

	return Desktop::desktopInstance;
}

Desktop::Desktop()
{
	context_ = NULL;
	peer_ = NULL;
}

Desktop::~Desktop()
{
	/**may be NULL if the init function was never called,
	*which is theoretically possible if no one uses the Desktop object
	*Maybe the Toolkit should init the deskotp ?
	*/
	if ( NULL != context_ ) {
		context_->getPeer()->setContextID( 0 );
		delete context_;
	}
	context_ = NULL;

	delete peer_;
	peer_ = NULL;
}

void Desktop::init()
{
	if ( context_ == NULL ) {
		peer_ = UIToolkit::createDesktopPeer( this );
		if ( NULL == peer_ ) {
			throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL DesktopPeer, UIToolkit::createDesktopPeer() is probably not implemented correctly") );
		}
		context_ = new GraphicsContext( peer_->desktopGetGraphicsContextHandleID() );
	}
}

void Desktop::beginPainting( Rect* clippingRect )
{
	peer_->desktopBeginPainting( clippingRect );
}

void Desktop::endPainting()
{
	peer_->desktopEndPainting();
}

bool Desktop::supportsVirtualDirectories()
{
	return peer_->desktopSupportsVirtualDirectories();
}


bool Desktop::hasFileSystemDirectory()
{
	return peer_->desktopHasFileSystemDirectory();
}

String Desktop::getDirectory()
{
	return peer_->desktopGetDirectory();
}

ulong32 Desktop::getWidth()
{
	return peer_->desktopGetWidth();
}

ulong32 Desktop::getHeight()
{
	return peer_->desktopGetHeight();
}

Rect Desktop::getUsableBounds()
{
	return peer_->desktopGetUsableBounds();
}

Point Desktop::getCurrentMousePosition()
{
	return peer_->getCurrentMousePosition();
}


/**
$Id$
*/
