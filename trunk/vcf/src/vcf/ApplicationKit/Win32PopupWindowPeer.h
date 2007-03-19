#ifndef _VCF_WIN32POPUPWINDOWPEER_H__
#define _VCF_WIN32POPUPWINDOWPEER_H__
//PopupWindowPeer.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {


class APPLICATIONKIT_API Win32PopupWindowPeer : public Win32Window, public PopupWindowPeer {
public:
	Win32PopupWindowPeer( Frame* frame, Window* owner );

	virtual ~Win32PopupWindowPeer();

	virtual void create( Control* owningControl );

	virtual Win32Object::CreateParams createParams();

	virtual void setBorder( Border* border );

	virtual void setText( const String& text );

	virtual void setBounds( VCF::Rect* rect );

	virtual void setVisible( const bool& visible );

	virtual void  setClientBounds( Rect* bounds );

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setFrameTopmost( const bool& isTopmost );

	virtual bool isMaximized();

	virtual void setMaximized( const bool maximised );

	virtual bool isMinimized();

	virtual void setMinimized( const bool& minimized );

	virtual void restore();

	virtual void setIconImage( Image* icon );

	virtual bool isActiveWindow();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual void showModal();

	virtual void showAsSheet( Window* owningWindow );

	virtual void show();	
};


};



#endif //_VCF_WIN32POPUPWINDOWPEER_H__