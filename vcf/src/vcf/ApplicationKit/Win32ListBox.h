#ifndef _VCF_WIN32LISTBOX_H__
#define _VCF_WIN32LISTBOX_H__
//Win32ListBox.h

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

class APPLICATIONKIT_API Win32ListBox : public AbstractWin32Component, public ListBoxPeer {

public:
	Win32ListBox( ListBoxControl* listboxControl );

	virtual ~Win32ListBox();

	/**
	* returns a ID that identifies this control. On Win32 this corresponds to an HWND.
	*/
	virtual OSHandleID getHandleID(){
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
	virtual void setBounds( VCF::Rect* rect ){
		AbstractWin32Component::setBounds( rect );
	};

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
	* returns a bit-masked uint32 that contains style constants.
	*  These style constants are defined in the VCF, and must
	* be translated to the particular windowing system being used.
	*/
	virtual uint32 getStyleMask(){
		return AbstractWin32Component::getStyleMask();
	};

	/**
	* sets the current style mask.
	*  Should cause a repaint of the component, if neccessary.
	*/
	virtual void setStyleMask( const uint32& styleMask ){
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

	virtual void createParams();

	virtual LRESULT handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc = NULL );

	/**
	* on Win32 see LB_SETCARETINDEX
	*/
	virtual void setFocusedItem(ListItem * item);

	/**
	* on Win32 see LB_RESETCONTENT
	*/
	virtual void clear();

	/**
	* on Win32 see LB_SELITEMRANGEEX
	*/
	virtual void rangeSelect(const bool & isSelected, ListItem * first, ListItem * last);

	/**
	* on Win32 see LB_SETCURSEL
	*/
	virtual void selectItem(ListItem * item);

	/**
	* on Win32 see LB_GETITEMRECT
	*/
	virtual Rect* getItemRect();

	/**
	* on Win32 see LB_ADDSTRING
	*/
	virtual void addItem(ListItem * item);

	virtual void insertItem( const uint32& index, ListItem * item);

	virtual void removeItem( ListItem* item );

	/**
	* on Win32 see LB_GETCURSEL
	*/
	virtual bool isItemSelected(ListItem* item);

	/**
	* returns NULL if the point passed in is not over a list item
	*/
	virtual ListItem* isPtOverItem(Point* point);

	/**
	* returns a the item that has the focus in a multiple selection range.
	* On Win32 see LB_GETCARETINDEX
	*/
	virtual ListItem* getFocusedItem();

	/**
	* on  Win32 see LB_SETITEMHEIGHT
	*/
	virtual void setItemHeight( const uint32& itemHeight );

	/**
	* on Win32 see LB_GETCURSEL
	*/
	virtual ListItem* getSelectedItem();

	/**
	* on Win32 see LB_GETITEMHEIGHT
	*/
	virtual uint32 getItemHeight();

	virtual void setFont( Font* font ){
		AbstractWin32Component::setFont( font );
	};

	virtual void repaint( Rect* repaintRect=NULL ){
		AbstractWin32Component::repaint(repaintRect);
	};

	virtual void keepMouseEvents(){
		AbstractWin32Component::keepMouseEvents();
	};

	virtual void releaseMouseEvents(){
		AbstractWin32Component::releaseMouseEvents();
	};

	virtual void setCursor( Cursor* cursor ) {
		AbstractWin32Component::setCursor( cursor );
	}
private:
	ListBoxControl* listboxControl_;
	WNDPROC oldListboxWndProc_;
	Rect itemRect_;
	HBRUSH backgroundBrush_;
};

};


#endif // _VCF_WIN32LISTBOX_H__

/**
$Id$
*/
