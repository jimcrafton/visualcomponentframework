#ifndef _VCF_GTKWINDOW_H__
#define _VCF_GTKWINDOW_H__
//GTKWindow.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ABSTRACTGTKCONTROL_H__
#	include "vcf/ApplicationKit/AbstractGTKControl.h"
#endif // _VCF_ABSTRACTGTKCONTROL_H__

#ifndef _VCF_WINDOWPEER_H__
#	include "vcf/ApplicationKit/WindowPeer.h"
#endif // _VCF_WINDOWPEER_H__


namespace VCF {


/**

*/
class GTKWindow : public AbstractGTKControl, public WindowPeer {
public:
	enum WindowState{
		wsNone = 0,
		wsMaximized,
		wsMinimized,
		wsNormal
	};

	GTKWindow( Control* control, Control* owner );

	virtual ~GTKWindow();

	virtual long getHandleID();

	virtual void create( Control* owningControl );

	virtual Rect getBounds();

	virtual void setBounds( Rect* rect );

	virtual Rect getClientBounds();

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

	virtual gboolean handleEvent( GdkEvent* gdkEvent );

	virtual String getText();

	virtual void setText( const String& text );
protected:
	virtual void initGdkEventHandlers();

	static gboolean onGdkEventForContainer( GtkWidget *widget, GdkEvent *event, gpointer user_data );

	static gint deleteEvent( GtkWidget *widget, GdkEvent  *event, gpointer data );
	static void destroyEvent( GtkWidget *widget, gpointer data );

	Rect clientBounds_;
	String text_;
	WindowState sizeState_;

	GtkWidget* containerWidget_;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.2.2  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.6.2.1  2003/08/25 03:13:44  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.6  2003/08/09 02:56:44  ddiego
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
*Revision 1.5.2.4  2003/07/14 22:52:40  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.5.2.3  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.5.2.2  2003/06/01 16:43:59  ddiego
*further GTK support added
*
*Revision 1.5.2.1  2003/05/30 04:13:10  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.5  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.3  2003/04/23 03:43:37  ddiego
*further gtk dev got basic eventing code in place
*
*Revision 1.4.2.2  2003/04/19 03:31:15  ddiego
*basic code in place for gtk port for ApplicationKit - needs to be tested in
*linux
*
*Revision 1.4.2.1  2003/04/17 04:29:49  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*/


#endif // _VCF_GTKWINDOW_H__


