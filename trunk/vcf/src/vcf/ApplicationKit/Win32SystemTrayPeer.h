#ifndef _VCF_WIN32SYSTEMTRAYPEER_H__
#define _VCF_WIN32SYSTEMTRAYPEER_H__
//ControlPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {

	/**
	This is the Win32 implementation of the SystemTrayPeer class.
	Many thanks to Chris Maunder's CSystemTray code from CodeProject
	for providing a nice base to steal some ideas from in implementing
	this. You can get the CSystemTray at http://codeproject.com/shell/systemtray.asp
	*/
	class Win32SystemTrayPeer : public Object, public SystemTrayPeer {
	public:
		Win32SystemTrayPeer();

		virtual ~Win32SystemTrayPeer();

		virtual void setIconImage( Image* image );

		virtual void setPopupMenu( PopupMenu* popupMenu );

		virtual void setTooltipText( const String& tooltipText );
	
		virtual void addToTray();

		virtual void removeFromTray();

		virtual void showInTray();

		virtual void hideFromTray();

	protected:
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND trayWnd_;
		bool enabled_;
		bool hidden_;
		bool removed_;
		void* notifyIconData_;
		PopupMenu* popupMenu_;
		static std::map<HWND,Win32SystemTrayPeer*> sysTrayWndMap;

		NOTIFYICONDATAW* notifyIconDataW() {
			return (NOTIFYICONDATAW*)notifyIconData_;
		}

		NOTIFYICONDATAA* notifyIconDataA() {
			return (NOTIFYICONDATAA*)notifyIconData_;
		}

		LRESULT handleTrayMessage( WPARAM wParam, LPARAM lParam );
	};
}


#endif //_VCF_WIN32SYSTEMTRAYPEER_H__


