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

protected:
	ButtonState state_;
	GtkButton* gtkButton_;
	CommandButton* commandButton_;

	static void gtkButtonClicked( GtkButton* button,  gpointer data );
};

}

/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2.6.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.3  2003/07/14 22:52:40  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.1.2.2  2003/07/13 03:45:11  ddiego
*Added further fixes for the GTK port. Now have the event handling working
*correctly, and fixed an issue with too many repaint messages being sent
*which caused 100% CPU utilization.
*
*Revision 1.1.2.1  2003/07/10 04:55:00  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*/


#endif // _VCF_GTKCOMMANDBUTTON_H__


