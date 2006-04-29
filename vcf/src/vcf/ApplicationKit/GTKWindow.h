#ifndef _VCF_GTKWINDOW_H__
#define _VCF_GTKWINDOW_H__ 
//GTKWindow.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#ifndef _VCF_ABSTRACTGTKCONTROL_H__
#	include "vcf/ApplicationKit/AbstractGTKControl.h"
#endif // _VCF_ABSTRACTGTKCONTROL_H__

#ifndef _VCF_WINDOWPEER_H__
#	include "vcf/ApplicationKit/WindowPeer.h"
#endif // _VCF_WINDOWPEER_H__

namespace VCF
{

/**
 
*/
class GTKWindow : public AbstractGTKControl, public WindowPeer
{
public:
	enum WindowState{
	    wsNone = 0,
	    wsMaximized,
	    wsMinimized,
	    wsNormal
	};

	GTKWindow( Control* control, Control* owner );

	virtual ~GTKWindow();

	virtual OSHandleID getHandleID();

	virtual void create( Control* owningControl );

	virtual Rect getBounds();

	virtual void setBounds( Rect* rect );

	virtual Rect getClientBounds();

	virtual void setClientBounds( Rect* bounds );

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setFrameTopmost( const bool& isTopmost );

	virtual bool isMaximized();

	virtual void setMaximized( const bool maximised );

	virtual bool isMinimized();

	virtual void setMinimized( const bool& minimized );

	virtual void restore();

	virtual void setIconImage( Image* icon );

	virtual gboolean handleEvent( GdkEvent* gdkEvent );

	virtual String getText();

	virtual void setText( const String& text );

	virtual void setBorder( Border* border );

	virtual bool isActiveWindow();

protected:
	virtual void initGdkEventHandlers();

	static gboolean onGdkEventForContainer( GtkWidget *widget,
	                                        GdkEvent *event,
	                                        gpointer user_data );

	static gint deleteEvent( GtkWidget *widget, GdkEvent *event, gpointer data );
	static void destroyEvent( GtkWidget *widget, gpointer data );

	Rect clientBounds_;
	String text_;
	WindowState sizeState_;

	GtkWidget* containerWidget_;
};

} //end of namespace VCF


#endif // _VCF_GTKWINDOW_H__

/**
$Id$
*/
