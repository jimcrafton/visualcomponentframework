//UIShell.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//UIShell.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/UIShellPeer.h"



using namespace VCF;

UIShell* UIShell::create()
{
	if ( NULL == UIShell::shellInstance ) {
		UIShell::shellInstance = new UIShell();
		UIShell::shellInstance->init();
	}

	return UIShell::shellInstance;
}

UIShell::UIShell()
{
	context_ = NULL;
	peer_ = NULL;
}

UIShell::~UIShell()
{
	/**may be NULL if the init function was never called,
	*which is theoretically possible if no one uses the UIShell object
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

void UIShell::init()
{
	if ( context_ == NULL ) {
		peer_ = UIToolkit::createUIShellPeer( this );
		if ( NULL == peer_ ) {
			throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL UIShellPeer, UIToolkit::createUIShellPeer() is probably not implemented correctly") );
		}
		context_ = new GraphicsContext( peer_->shellGetGraphicsContextHandleID() );
	}
}

void UIShell::beginPainting( Rect* clippingRect )
{
	peer_->shellBeginPainting( clippingRect );
}

void UIShell::endPainting()
{
	peer_->shellEndPainting();
}

bool UIShell::supportsVirtualDirectories()
{
	return peer_->shellSupportsVirtualDirectories();
}


bool UIShell::hasFileSystemDirectory()
{
	return peer_->shellHasFileSystemDirectory();
}

String UIShell::getDirectory()
{
	return peer_->shellGetDirectory();
}

uint32 UIShell::getWidth()
{
	return peer_->shellGetWidth();
}

uint32 UIShell::getHeight()
{
	return peer_->shellGetHeight();
}

Rect UIShell::getUsableBounds()
{
	return peer_->shellGetUsableBounds();
}

Point UIShell::getCurrentMousePosition()
{
	return peer_->getCurrentMousePosition();
}


/**
$Id: UIShell.cpp 2807 2006-06-27 20:25:49Z kdmix $
*/
