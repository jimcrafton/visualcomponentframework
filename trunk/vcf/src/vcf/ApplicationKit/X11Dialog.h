#ifndef _VCF_X11DIALOG_H__
#define _VCF_X11DIALOG_H__
//X11Dialog.h

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

#ifndef _VCF_DIALOGPEER_H__
#	include "vcf/ApplicationKit/DialogPeer.h"
#endif // _VCF_DIALOGPEER_H__



namespace VCF {

/**

*/
class X11Dialog : public Object, public AbstractX11Control, public DialogPeer{
public:
	X11Dialog( Control* owner, Dialog* component );

	X11Dialog();

	virtual ~X11Dialog();

	virtual Rect* getClientBounds();

	virtual void  setClientBounds( Rect* bounds );

	virtual void show();

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setIconImage( Image* icon );

	virtual void setCaption( const String& caption );

	virtual void showMessage( const String& message, const String& caption );

	virtual UIToolkit::ModalReturnType showMessage( const String& message, const String& caption,
	                        const long& messageButtons,	const Dialog::MessageStyle& messageStyle );

	virtual void handleEvent( XEvent* x11Event );

	virtual String getText();

	virtual void setText( const String& text );

	virtual void setBounds( Rect* rect );

protected:
	Rect clientBounds_;
	Atom wmProtocols_;
	String text_;
	Control* owner_;
	bool runningModal_;
};


}; //end of namespace VCF


#endif // _VCF_X11DIALOG_H__

/**
$Id$
*/
