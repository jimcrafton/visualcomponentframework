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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.4.1  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.3  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/12 03:11:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.4  2003/01/27 05:04:02  ddiego
*more X11 work fixed up some stuff for modal event loop and added X11Dialog
*class. not ready to work yet
*
*Revision 1.1.2.3  2003/01/04 06:11:42  ddiego
*fixed a crash in X11GraphicsToolkit - an error in how colors were being freed
*added support for titles, getting the focus control, and grabbing the mouse !
*
*Revision 1.1.2.2  2003/01/03 05:43:02  ddiego
*added some tune ups to the event loop method in the X11UIToolkit
*added code for closing a window and destroying child peers
*trying to track down why a core dump happens in the ApplicationKit::terminate
*method - seems to be due to bad pointers? Very very annoying....
*
*Revision 1.1.2.1  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Auto generated header for class X11Window
*/


#endif // _VCF_X11WINDOW_H__


