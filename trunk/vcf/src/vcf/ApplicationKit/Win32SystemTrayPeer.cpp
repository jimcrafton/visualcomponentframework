//Win32SystemTrayPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/SystemTrayPeer.h"
#include <shellapi.h>
#include "vcf/ApplicationKit/Win32SystemTrayPeer.h"

#include "vcf/ApplicationKit/Win32PopupMenu.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"

#define WM_WIN32SYTEMTRAY		WM_APP + 405

using namespace VCF;

std::map<HWND,Win32SystemTrayPeer*> Win32SystemTrayPeer::sysTrayWndMap;

Win32SystemTrayPeer::Win32SystemTrayPeer():
	trayWnd_(NULL),
	enabled_(true),
	hidden_(true),
	removed_(true),
	notifyIconData_(NULL),
	popupMenu_(NULL)
{	
	Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();

	HWND parent = toolkit->getDummyParent();

	static bool isWin32SystemTrayPeerWndClassRegistered = false;

	if ( !isWin32SystemTrayPeerWndClassRegistered ) {
		if ( System::isUnicodeEnabled() ) {
			WNDCLASSEXW wcex;

			wcex.cbSize = sizeof(wcex);

			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= (WNDPROC)Win32SystemTrayPeer::wndProc;
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= ::GetModuleHandleW( NULL );
			wcex.hIcon			= NULL;
			wcex.hCursor		= NULL;
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
			wcex.lpszMenuName	= NULL;
			wcex.lpszClassName	= L"VCF::Win32SytemTray";
			wcex.hIconSm		= NULL;

			RegisterClassExW(&wcex);
		}
		else{
			WNDCLASSEXA wcex;

			wcex.cbSize = sizeof(wcex);

			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= (WNDPROC)Win32SystemTrayPeer::wndProc;
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= ::GetModuleHandleA( NULL );
			wcex.hIcon			= NULL;
			wcex.hCursor		= NULL;
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
			wcex.lpszMenuName	= NULL;
			wcex.lpszClassName	= "VCF::Win32SytemTray";
			wcex.hIconSm		= NULL;

			RegisterClassExA(&wcex);
		}
	}

	isWin32SystemTrayPeerWndClassRegistered = true;


	if ( System::isUnicodeEnabled() ) {

		notifyIconData_ = new NOTIFYICONDATAW;
		memset( notifyIconData_, 0, sizeof(NOTIFYICONDATAW) );

		trayWnd_ = ::CreateWindowW( L"VCF::Win32SytemTray", NULL, WS_CHILD , 0, 0, 0, 0, parent, NULL, ::GetModuleHandleW( NULL ), NULL );

		Win32SystemTrayPeer::sysTrayWndMap[trayWnd_] = this;

		NOTIFYICONDATAW& notifyIconData = *notifyIconDataW();

		notifyIconData.cbSize = sizeof(NOTIFYICONDATAW);
		notifyIconData.hWnd = trayWnd_;
		notifyIconData.uID = (UINT)this;
		notifyIconData.uCallbackMessage = WM_WIN32SYTEMTRAY;
		notifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

	}
	else {
		notifyIconData_ = new NOTIFYICONDATAA;
		memset( notifyIconData_, 0, sizeof(NOTIFYICONDATAA) );

		trayWnd_ = ::CreateWindowA( "VCF::Win32SytemTray", NULL, WS_CHILD , 0, 0, 0, 0, parent, NULL, ::GetModuleHandleA( NULL ), NULL );

		Win32SystemTrayPeer::sysTrayWndMap[trayWnd_] = this;

		NOTIFYICONDATAA& notifyIconData = *notifyIconDataA();

		notifyIconData.cbSize = sizeof(NOTIFYICONDATAA);
		notifyIconData.hWnd = trayWnd_;
		notifyIconData.uID = (UINT)this;
		notifyIconData.uCallbackMessage = WM_WIN32SYTEMTRAY;
		notifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	}

}

Win32SystemTrayPeer::~Win32SystemTrayPeer()
{
	std::map<HWND,Win32SystemTrayPeer*>::iterator found =
		Win32SystemTrayPeer::sysTrayWndMap.find( trayWnd_ );

	::DestroyWindow( trayWnd_);

	if ( System::isUnicodeEnabled() ) {
		NOTIFYICONDATAW* ptr = (NOTIFYICONDATAW*)notifyIconData_;
		delete ptr;
	}
	else {
		NOTIFYICONDATAA* ptr = (NOTIFYICONDATAA*)notifyIconData_;
		delete ptr;
	}
	
	if ( found != Win32SystemTrayPeer::sysTrayWndMap.end() ) {
		Win32SystemTrayPeer::sysTrayWndMap.erase( found );
	}
}

void Win32SystemTrayPeer::setIconImage( Image* image )
{
	if ( !enabled_ ) {
        return;
	}

	HICON hIcon = NULL;
	if ( NULL != image ) {
		Win32Image* win32Img = (Win32Image*)image;

		hIcon = win32Img->convertToIcon();
		VCF_ASSERT( NULL != hIcon );
	}


	if ( System::isUnicodeEnabled() ) {
		NOTIFYICONDATAW* notifyIconData = notifyIconDataW();

		notifyIconData->uFlags = NIF_ICON;
		notifyIconData->hIcon = hIcon;

		if ( !hidden_ ) {
			Shell_NotifyIconW( NIM_MODIFY, notifyIconData );
		}
	}
	else {
		NOTIFYICONDATAA* notifyIconData = notifyIconDataA();

		notifyIconData->uFlags = NIF_ICON;
		notifyIconData->hIcon = hIcon;

		if ( !hidden_ ) {
			Shell_NotifyIconA( NIM_MODIFY, notifyIconData );
		}
	}
}

void Win32SystemTrayPeer::setPopupMenu( PopupMenu* popupMenu )
{
	popupMenu_ = popupMenu;
}

void Win32SystemTrayPeer::setTooltipText( const String& tooltipText )
{
	if ( System::isUnicodeEnabled() ) {
		NOTIFYICONDATAW* notifyIconData = notifyIconDataW();
		int len = sizeof(notifyIconData->szTip);

		tooltipText.copy( notifyIconData->szTip, len );
		notifyIconData->uFlags = NIF_TIP;

		if ( !hidden_ ) {
			Shell_NotifyIconW( NIM_MODIFY, notifyIconData );
		}
	}
	else {
		AnsiString tmp = tooltipText;
		NOTIFYICONDATAA* notifyIconData = notifyIconDataA();
		int len = sizeof(notifyIconData->szTip);

		tmp.copy( notifyIconData->szTip, len );

		notifyIconData->uFlags = NIF_TIP;

		if ( !hidden_ ) {
			Shell_NotifyIconA( NIM_MODIFY, notifyIconData );
		}
	}
}

void Win32SystemTrayPeer::addToTray()
{
	if (!removed_) {
        removeFromTray();
	}

    if (enabled_)  {

		if ( System::isUnicodeEnabled() ) {
			NOTIFYICONDATAW* notifyIconData = notifyIconDataW();
			notifyIconData->uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
			if (!Shell_NotifyIconW(NIM_ADD, notifyIconData)) {		
				//  m_bShowIconPending = TRUE;
			}
			else {
				removed_ = hidden_ = false;
			}
		}
		else{
			NOTIFYICONDATAA* notifyIconData = notifyIconDataA();
			notifyIconData->uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
			if (!Shell_NotifyIconA(NIM_ADD, notifyIconData)) {		
				//  m_bShowIconPending = TRUE;
			}
			else {
				removed_ = hidden_ = false;
			}
		}
    }
}

void Win32SystemTrayPeer::removeFromTray()
{
	if (!enabled_ || removed_) {
        return;
	}

	if ( System::isUnicodeEnabled() ) {
		NOTIFYICONDATAW* notifyIconData = notifyIconDataW();
		notifyIconData->uFlags = 0;
		if ( Shell_NotifyIconW(NIM_DELETE, notifyIconData ) ) {
			removed_ = hidden_ = true;
		}
	}
	else {
		NOTIFYICONDATAA* notifyIconData = notifyIconDataA();
		notifyIconData->uFlags = 0;
		if ( Shell_NotifyIconA(NIM_DELETE, notifyIconData ) ) {
			removed_ = hidden_ = true;
		}
	}
}

void Win32SystemTrayPeer::showInTray()
{
	if ( removed_ ) {
        addToTray();
	}

	if (!hidden_) {
        return;
	}
	
	addToTray();
}

void Win32SystemTrayPeer::hideFromTray()
{
	if ( !enabled_ || removed_ || hidden_ ) {
        return;
	}

	removeFromTray();
}

LRESULT Win32SystemTrayPeer::handleTrayMessage( WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;

	UINT uid = 0;
	if ( System::isUnicodeEnabled() ) {
		uid = notifyIconDataW()->uID;
	}
	else {
		uid = notifyIconDataA()->uID;
	}
	if ( wParam != uid ) {
		return result;
	}

	Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();

	HWND dummyWnd = toolkit->getDummyParent();

    // Clicking with right button brings up a context menu

    if ( LOWORD(lParam) == WM_RBUTTONUP ) {
		HWND wnd = dummyWnd;

		if ( NULL != this->popupMenu_ ) {
			// Display and track the popup menu
			POINT pos = {0};
			::GetCursorPos(&pos);
					
			if ( Frame::getActiveFrame() ) {
				wnd = (HWND)Frame::getActiveFrame()->getPeer()->getHandleID();
			}
			else if ( Application::getRunningInstance() ) {
				wnd = (HWND) Application::getRunningInstance()->getMainWindow()->getPeer()->getHandleID();
			}

			::SetForegroundWindow( wnd ); 

			

			MenuItem* rootItem = popupMenu_->getRootMenuItem();
			if  ( NULL != rootItem )  {
				MenuItemPeer* peer = rootItem->getPeer();
				HMENU menuHandle = (HMENU)peer->getMenuID();
				UINT flags = TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY;
				UINT retVal = ::TrackPopupMenu( menuHandle, flags, pos.x, pos.y, 0, dummyWnd, NULL );

				if ( retVal ){
					MenuItem* item = Win32MenuItem::getMenuItemFromID( retVal );
					if ( NULL != item ){
						item->click();
					}
				}
			}
		}

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
		::PostMessage( wnd, WM_NULL, 0, 0);
    } 
    else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) {
        // double click received, the default action is to execute default menu item
		   
    }
	return result;
}

LRESULT CALLBACK Win32SystemTrayPeer::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	Win32SystemTrayPeer* thisPtr = NULL;

	std::map<HWND,Win32SystemTrayPeer*>::iterator found =
		Win32SystemTrayPeer::sysTrayWndMap.find( hWnd );
	if ( found != Win32SystemTrayPeer::sysTrayWndMap.end() ) {
		thisPtr = found->second;
	}

	bool trayMessage = false;

	if ( NULL != thisPtr ) {
		if ( System::isUnicodeEnabled() ) {
			if ( thisPtr->notifyIconDataW()->uCallbackMessage == message ) {
				trayMessage = true;
			}
		}
		else{
			if ( thisPtr->notifyIconDataA()->uCallbackMessage == message ) {
				trayMessage = true;
			}
		}
	}

	if ( trayMessage ) {
		result = thisPtr->handleTrayMessage( wParam, lParam );
	}
	else {

		switch ( message ) {
			case 0: // to make the compiler happy for switch with no case label
			default : {
				if ( System::isUnicodeEnabled() ) {
					result = ::DefWindowProcW( hWnd, message, wParam, lParam );
				}
				else {
					result = ::DefWindowProcA( hWnd, message, wParam, lParam );
				}
			}
			break;
		}
	}

	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.4  2004/09/09 02:41:06  marcelloptr
*warning eliminated
*
*/
