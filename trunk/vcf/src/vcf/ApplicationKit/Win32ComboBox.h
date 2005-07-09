#ifndef _VCF_WIN32COMBOBOX_H__
#define _VCF_WIN32COMBOBOX_H__
//Win32ComboBox.h

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

class ComboBoxControl;

class APPLICATIONKIT_API Win32ComboBox  : public AbstractWin32Component, public ComboBoxPeer
{
public:
	Win32ComboBox( ComboBoxControl* component );

	virtual ~Win32ComboBox();

	/**
	* returns a ID that identifies this control. On Win32 this corresponds to an HWND.
	*/
	virtual long getHandleID(){
		return AbstractWin32Component::getHandleID();
	};

	/**
	* returns a text associated with the component. This usually gets used in the Component::getCaption() method.
	*/
	virtual VCF::String getText(){
		return AbstractWin32Component::getText();
	};

	/**
	* sets the text for the widget
	*/
	virtual void setText( const VCF::String& text ){
		AbstractWin32Component::setText( text );
	};

	/**
	* sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent.
	*/
	virtual void setBounds( VCF::Rect* rect );

	/**
	* returns the bounds of the component in the coordinate system of the parent.
	*/
	virtual VCF::Rect* getBounds(){
		return AbstractWin32Component::getBounds();
	};

	/**
	* shows or hides the component.
	* This does NOT close the component (if invoked on a frame based component ).
	*/
	virtual void setVisible( const bool& visible ){
		AbstractWin32Component::setVisible( visible );
	};

	/**
	* returns wether or not the component is currently visible.
	*/
	virtual bool getVisible(){
		return AbstractWin32Component::getVisible();
	};

	/**
	* returns a bit-masked unsigned long that contains style constants.
	*  These style constants are defined in the VCF, and must
	* be translated to the particular windowing system being used.
	*/
	virtual unsigned long getStyleMask(){
		return AbstractWin32Component::getStyleMask();
	};

	/**
	* sets the current style mask.
	*  Should cause a repaint of the component, if neccessary.
	*/
	virtual void setStyleMask( const unsigned long& styleMask ){
		AbstractWin32Component::setStyleMask( styleMask );
	};

	/**
	* returns the component that this Peer is attached to.
	*/
	virtual VCF::Control* getControl(){
		return AbstractWin32Component::getControl();
	};

	/**
	* attahces the Peer to a particular component. This should only be done once.
	*/
	virtual void setControl( VCF::Control* component ){
		AbstractWin32Component::setControl( component );
	};

	virtual void setParent( VCF::Control* parent ){
		AbstractWin32Component::setParent( parent );
	};

	virtual VCF::Control* getParent(){
		return AbstractWin32Component::getParent();
	};

	virtual bool isFocused(){
		return AbstractWin32Component::isFocused();
	};

	virtual void setFocus( const bool& focused ){
		AbstractWin32Component::setFocus( focused );
	};

	virtual bool isEnabled(){
		return AbstractWin32Component::isEnabled();
	};

	virtual void setEnabled( const bool& enabled ){
		AbstractWin32Component::setEnabled( enabled );
	};

	virtual void addItem( ListItem * item );

	virtual void insertItem( const unsigned long& index, ListItem * item );

	virtual void createParams();

	virtual LRESULT handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc = NULL);

	virtual void setFont( Font* font ){
		AbstractWin32Component::setFont( font );
	};

	virtual void repaint( Rect* repaintRect=NULL ){
		AbstractWin32Component::repaint(repaintRect);
	};

	virtual void keepMouseEvents(){
		AbstractWin32Component::keepMouseEvents();
	}

	virtual void releaseMouseEvents(){
		AbstractWin32Component::releaseMouseEvents();
	};
private:

	WNDPROC oldComboBoxWndProc_;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/29 05:00:03  marcelloptr
*some white spaces
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.7.8.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.1  2003/03/12 03:11:08  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32COMBOBOX_H__


