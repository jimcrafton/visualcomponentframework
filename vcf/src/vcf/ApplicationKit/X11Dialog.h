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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
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
*Revision 1.3  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/12 03:11:38  ddiego
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
*Revision 1.1.2.3  2003/02/03 05:22:47  ddiego
*added support for command types to the PuchButton class
*added support for clicks in the PuchButton class to auto close a dialog
*if it is parented to one, similar to the CommandButton. This is part of the
*gradual phase out of the CommandButton class
*Add supprt for drawing a focus rect in the PushButton class
*plugged in tabbing bahaviour to the X11UIToolkit. It seems as though
*"Shift" + "Tab" is not being picked up properly
*Finished implementing the X11Dialog::showMessage(String,String) method
*and also add some finishing touches to teh X11Dialog so it displays correctly
*Add some finishing touches to the X11UIToolkit::runModalEventLoop() as well
*
*Revision 1.1.2.2  2003/02/02 04:56:02  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.1.2.1  2003/01/27 05:04:02  ddiego
*more X11 work fixed up some stuff for modal event loop and added X11Dialog
*class. not ready to work yet
*
*Auto generated header for class X11Dialog
*/


#endif // _VCF_X11DIALOG_H__


