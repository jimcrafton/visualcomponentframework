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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/01 04:02:17  ddiego
*minor stuff
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.10  2003/05/17 20:37:37  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/12 03:12:39  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


