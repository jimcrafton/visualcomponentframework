#ifndef _VCF_CONTROLPEER_H__
#define _VCF_CONTROLPEER_H__
//ControlPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class Control;

class Font;

class Rect;

class Cursor;

class Border;

/** The base Peer interface.
 *   In the Visual Control Framework Peers are the equivalent of Peers in Java.
 *   Peers can be either light weight or heavyweight.
 *  Heavyweight Peers are based on native widgets are consume a certain amount of resources.
 *   On Win32 heavweight Peers have their own window handle and graphics context.
 *
 * Lightweight Peers use the window handle and graphics context of the parents.
 * Frame Peers, such as WindowPeer and DialogPeer MUST be based on heavyweight controls.
 * @interface */

class APPLICATIONKIT_API ControlPeer : public VCF::Interface {
public:

	virtual ~ControlPeer(){};

	/**
	This is called to actually create any neccessary windowing system resources specific
	to a new control (or widget/window/etc) instance for the platform.
	create() <b>must</b> be called by the containing VCF::Control subclass, typically in the
	classes constructor, after retreiving the new peer instance from the appropriate
	UIToolkit::createXXX() call.
	*/
	virtual void create( Control* owningControl ) = 0;

	/**
	Destroy the control peer's resoruces (if neccessary)
	*/
	virtual void destroyControl() = 0;

    /**
    returns a ID that identifies this control. On Win32 this corresponds to an HWND.
    */
    virtual long getHandleID() = 0;

    /**
    returns a text associated with the component. This usually gets used in the
	Control::getCaption() method.
    */
    virtual String getText() = 0;

    /**
    sets the text for the control
     */
    virtual void setText( const String& text ) = 0;

    /**
    sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent.
     */
    virtual void setBounds( Rect* rect ) = 0;

	/**
	advanced function for changing the size of multiple child windows.
	This may have no implementation on some windowing systems
	*/
	virtual bool beginSetBounds( const ulong32& numberOfChildren ) = 0;

	virtual void endSetBounds() = 0;

    /**
    returns the bounds of the component in the coordinate system of the parent.
    */
    virtual Rect getBounds() = 0;

    /**
    shows or hides the component.
    This does NOT close the component (if invoked on a frame based component ).
    */
    virtual void setVisible( const bool& visible ) = 0;

    /**
    returns wether or not the component is currently visible.
    */
    virtual bool getVisible() = 0;

    /**
     * returns the component that this Peer is attached to.
     */
    virtual Control* getControl() = 0;

    /**
     * attahces the Peer to a particular component. This should only be done once.
     */
    virtual void setControl( Control* component ) = 0;

    virtual void setCursor( Cursor* cursor ) = 0;

	virtual void setParent( Control* parent ) = 0;

	virtual Control* getParent() = 0;

	virtual bool isFocused() = 0;

	virtual void setFocused() = 0;

	virtual bool isEnabled() = 0;

	virtual void setEnabled( const bool& enabled ) = 0;

	virtual void setFont( Font* font ) = 0;

	virtual void repaint( Rect* repaintRect=NULL ) = 0;

	/**
	*this keeps the mouse events being sent to this control, even is the
	*mouse leaves the physical bounds of the control
	*/
	virtual void keepMouseEvents() = 0;

	/**
	*releases mouse events - goes back to normal event handling
	*/
	virtual void releaseMouseEvents() = 0;

	/**
	Takes the coordinates in pt, which are in the coordinate system of
	this control, and translates them into the coordinate system of the
	Screen.
	@param Point the initial point value, in the coordinate system of the
	control this method is called on.
	*/
	virtual void translateToScreenCoords( Point* pt ) = 0;

	/**
	Takes the coordinates in pt, which are in the coordinate system of
	the Screen, and translates them into the coordinate system of this
	control.
	@param Point the initial point value, in the coordinate system of the
	Screen.
	*/
	virtual void translateFromScreenCoords( Point* pt ) = 0;

	/**
	Called by the control when it's border object changes. May or may not 
	need to be implemented depending on the windowing system.
	*/
	virtual void setBorder( Border* border ) = 0;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.2.3  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.10.2.2  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.10.2.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.10  2003/08/09 02:56:44  ddiego
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
*Revision 1.9.2.1  2003/05/27 04:45:32  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.9  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.2  2003/04/17 04:29:48  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.8.2.1  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.20.1  2002/12/25 22:06:29  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CONTROLPEER_H__


