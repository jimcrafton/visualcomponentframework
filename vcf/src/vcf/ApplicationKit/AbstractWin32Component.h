#ifndef _VCF_ABSTRACTWIN32COMPONENT_H__
#define _VCF_ABSTRACTWIN32COMPONENT_H__
//AbstractWin32Component.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Control;

class Font;

/**
*This is the core Win32 control class peer, does most of the handling
*of WM_XXX messages.
*/
class APPLICATIONKIT_API AbstractWin32Component : public Win32Object, public ControlPeer  {
public:
	/**
	* identifiers to specify what to paint
	*@see AbstractWin32Component::doControlPaint()
	*/
	enum {
		cpBorderOnly = 0,
		cpControlOnly,
		cpBorderAndControl
	};

	AbstractWin32Component();

	AbstractWin32Component( Control* component );

	virtual ~AbstractWin32Component();

public:
	virtual void create( Control* owningControl );

	virtual void destroyControl();

	virtual OSHandleID getHandleID();

	virtual VCF::String getText();

	virtual void setText( const VCF::String& text );

	virtual void setBounds( VCF::Rect* rect );

	virtual VCF::Rect getBounds();

	virtual void setVisible( const bool& visible );

	virtual bool getVisible();

	virtual VCF::Control* getControl();

	virtual void setControl( VCF::Control* component );

	virtual void setParent( VCF::Control* parent );

	virtual VCF::Control* getParent();

	virtual bool isFocused();

	virtual void setFocused();

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );


	virtual void repaint( Rect* repaintRect=NULL );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual String toString();

	virtual void setCursor( Cursor* cursor );

	virtual bool beginSetBounds( const ulong32& numberOfChildren );

	virtual void endSetBounds();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );

	virtual void setBorder( Border* border );

	/*
	HDWP getWindPosInfo() {
		return winPosInfo_;
	}
	*/

	/**
	* manages a paint message for a control.
	* it prepares the Graphics context for the control so the correct device context handle is used.
	* It garantees that the state of the Graphics context doesn't change during tha paint operation.
	* 
	*@param HDC paintDC, the HDC given by the system with the paint message.
	*@see GraphicsContext::saveState()
	*/
	HDC doControlPaint( HDC paintDC, RECT paintRect, RECT* exclusionRect, int whatToPaint );

	void updatePaintDC( HDC paintDC, RECT paintRect, RECT* exclusionRect );

protected:
	void init();
	HDC memDC_;
	HBITMAP originalMemBMP_;
	HBITMAP memBMP_;
	bool mouseEnteredControl_;	
	int memDCState_;

	/*
	JC I remove this cause we don't really need them
	//HDWP winPosInfo_;
	//AbstractWin32Component* parent_;
	*/
	bool destroyed_;

	/**
	*
	*
	*/
	LRESULT handleNCPaint( WPARAM wParam, LPARAM lParam );

	/**
	*
	*
	*/
	LRESULT handleNCCalcSize( WPARAM wParam, LPARAM lParam );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/07 19:32:18  marcelloptr
*more documentation
*
*Revision 1.2.2.2  2004/09/06 21:30:19  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.7  2004/07/16 04:01:45  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.6  2004/07/15 14:55:11  ddiego
*borders fixed
*
*Revision 1.1.2.5  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.4  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.18.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.18  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.17.2.2  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.17.2.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.17  2003/08/09 02:56:44  ddiego
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
*Revision 1.16.2.1  2003/05/27 04:45:32  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.16  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.16.3  2003/04/17 04:29:48  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.15.16.2  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15.16.1  2003/03/12 03:10:52  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.14  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.13  2002/02/14 05:04:52  ddiego
*documentation...
*
*Revision 1.12  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTWIN32COMPONENT_H__


