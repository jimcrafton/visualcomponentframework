#ifndef _VCF_WIN32WINDOW_H__
#define _VCF_WIN32WINDOW_H__
//Win32Window.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/WindowPeer.h"


namespace VCF
{

class Win32Window : public AbstractWin32Component, public WindowPeer
{
public:
	Win32Window();

	Win32Window( Control* component, Control* owner );

	virtual ~Win32Window();

	virtual void create( Control* owningControl );

	virtual void setText( const String& text );

	virtual void setBounds( VCF::Rect* rect );

	virtual void setVisible( const bool& visible );

	virtual void setParent( VCF::Control* parent );

	virtual Rect getClientBounds();

	virtual void  setClientBounds( Rect* bounds );

	virtual Win32Object::CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

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
protected:
	bool activatesPending_;
	bool internalClose_;
	Control* owner_;

	void handleActivate();

	virtual LONG_PTR generateStyleForSetParent(VCF::Control* parent);
};


};


#endif // _VCF_WIN32WINDOW_H__

/**
$Id$
*/
