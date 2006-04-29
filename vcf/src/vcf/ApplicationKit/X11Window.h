#ifndef _VCF_X11WINDOW_H__
#define _VCF_X11WINDOW_H__
//X11Window.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ABSTRACTX11CONTROL_H__
#	include "vcf/ApplicationKit/AbstractX11Control.h"
#endif // _VCF_ABSTRACTX11CONTROL_H__

#ifndef _VCF_WINDOWPEER_H__
#	include "vcf/ApplicationKit/WindowPeer.h"
#endif // _VCF_WINDOWPEER_H__


namespace VCF {


/**

*/
class X11Window : public Object, public AbstractX11Control, public WindowPeer {
public:

	X11Window( Control* control, Control* owner );

	virtual ~X11Window();

	virtual Rect* getClientBounds();

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

	virtual void handleEvent( XEvent* x11Event );

	virtual String getText();

	virtual void setText( const String& text );
protected:
	Rect clientBounds_;
	Atom wmProtocols_;
	String text_;
};


}; //end of namespace VCF


#endif // _VCF_X11WINDOW_H__

/**
$Id$
*/
