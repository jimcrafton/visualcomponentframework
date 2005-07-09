//Win32PopupMenu.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32PopupMenu.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"



using namespace VCF;

Win32PopupMenu::Win32PopupMenu( PopupMenu* popupMenu )
{
	control_ = NULL;
	popupMenu_ = popupMenu;
}

Win32PopupMenu::~Win32PopupMenu()
{

}

void Win32PopupMenu::setControl( Control* control )
{
	control_ = control;
}

void initPopupMenu( HWND hwnd, HMENU menu )
{
	int count = ::GetMenuItemCount( menu );
	DWORD lParam = MAKELONG( 0, FALSE );
	SendMessage( hwnd, WM_INITMENUPOPUP, (WPARAM)menu, lParam );
	for ( int i=0;i<count;i++ ){
		MENUITEMINFO itemInfo = {0};
		itemInfo.cbSize = sizeof(MENUITEMINFO);
		itemInfo.fMask = MIIM_SUBMENU;
		if ( ::GetMenuItemInfo( menu, i, TRUE, &itemInfo ) ) {
			if ( NULL != itemInfo.hSubMenu ) {
				int subMenuCount = ::GetMenuItemCount( itemInfo.hSubMenu );
				if ( subMenuCount > 0 ) {
					initPopupMenu( hwnd, itemInfo.hSubMenu );
				}
			}
		}
	}
}


void Win32PopupMenu::popup( Point* pt )
{
	if ( (NULL != control_) && (NULL != pt) ){
		MenuItem* rooItem = popupMenu_->getRootMenuItem();
		if  ( NULL != rooItem )  {
			MenuItemPeer* peer = rooItem->getPeer();
			ControlPeer* controlPeer = control_->getPeer();
			if ( (NULL == peer) || (NULL == controlPeer) ){
				//throw exception
			}
			

			HMENU menuHandle = (HMENU)peer->getMenuID();
			UINT flags = TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY;
			HWND wnd = (HWND)controlPeer->getHandleID();
			
			POINT tmpPt = {0};
			tmpPt.x = (long)pt->x_;
			tmpPt.y = (long)pt->y_;
			ClientToScreen( wnd, &tmpPt );

			initPopupMenu( wnd, menuHandle );			

			UINT retVal = ::TrackPopupMenu( menuHandle, flags, tmpPt.x, tmpPt.y, 0, wnd, NULL );

			if ( retVal ){
				MenuItem* item = Win32MenuItem::getMenuItemFromID( retVal );
				if ( NULL != item ){
					item->click();
				}
			}
			else {
				StringUtils::traceWithArgs( Format("TrackPopupMenu failed, err: %d\n") % GetLastError() );
			}	

		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/03/15 01:51:50  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/12 02:05:45  ddiego
*fixed a subtle bug (that only showed up when using a lightweight
*control) that happened with MouseClick events being handled twice.
*
*Revision 1.1.2.3  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.14  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:12:40  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.12  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.11.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.11  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.10  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


