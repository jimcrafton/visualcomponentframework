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


MenuItem* Win32PopupMenu::popup( Point* pt )
{
	MenuItem* result = NULL;

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
					result = item;
				}
			}
		}
	}

	return result;
}


/**
$Id$
*/
