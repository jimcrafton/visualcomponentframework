//Win32MenuBar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32MenuBar.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"


using namespace VCF;


Win32MenuBar::Win32MenuBar(  MenuBar* menuBar  )
{
	frame_ = NULL;
	this->menuRoot_ = menuBar->getRootMenuItem();
}

Win32MenuBar::~Win32MenuBar()
{

}

void Win32MenuBar::setFrame( Frame* frame )
{	
	Frame* oldFrame = frame_;
	frame_ = frame;

	if ( (NULL != frame_) && (NULL != menuRoot_) ){		

		ControlPeer* Peer = frame_->getPeer();
		HWND wnd = (HWND)Peer->getHandleID();

		MenuItemPeer* itemImpl = menuRoot_->getPeer();

		HMENU menu = (HMENU) itemImpl->getMenuID();
		SetMenu( wnd, menu );
	}
	else if ( NULL == frame_ && NULL != oldFrame ) {
		SetMenu( (HWND)oldFrame->getPeer()->getHandleID(), NULL );		
	}
}

void Win32MenuBar::update()
{
	if ( (NULL != frame_) && (NULL != menuRoot_) ){
		ControlPeer* Peer = frame_->getPeer();
		HWND wnd = (HWND)Peer->getHandleID();

		DrawMenuBar( wnd );
	}
}

void Win32MenuBar::setMenuItems( MenuItem* item )
{
	menuRoot_ = item;
}


/**
$Id$
*/
