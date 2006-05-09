#ifndef _VCF_GTKCOMMANDBUTTON_H__
#define _VCF_GTKCOMMANDBUTTON_H__
//GTKCommandButton.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#ifndef _VCF_DRAWUISTATE_H__
#	include "vcf/GraphicsKit/DrawUIState.h"
#endif // _VCF_DRAWUISTATE_H__

#ifndef _VCF_BUTTONPEER_H__
#	include "vcf/ApplicationKit/ButtonPeer.h"
#endif // _VCF_BUTTONPEER_H__

namespace VCF {

/**
class GTKCommandButton documentation
*/
class GTKCommandButton : public AbstractGTKControl,  public ButtonPeer {
public:
	GTKCommandButton( CommandButton* component );

	virtual ~GTKCommandButton();

	virtual void create( Control* owningControl );

	virtual Image* getImage();

    virtual void setImage( Image* image );

    virtual ButtonState getState();

    virtual void setState( const ulong32& state );

	virtual String getText();

	virtual void setText( const String& text );

	virtual gboolean handleEvent( GdkEvent* gtkEvent );

	virtual void setBorder( Border* border );

	virtual void repaint( Rect* repaintRect, const bool& immediately );

	virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );

	virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );

protected:
	ButtonState state_;
	GtkButton* gtkButton_;
	CommandButton* commandButton_;

	static void gtkButtonClicked( GtkButton* button,  gpointer data );
};

}


#endif // _VCF_GTKCOMMANDBUTTON_H__

/**
$Id$
*/
