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

    virtual void insertItem( const unsigned long& index, ListItem * item);

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
    virtual void setItemHeight( const unsigned long& itemHeight );

    /**
     * on Win32 see LB_GETCURSEL
     */
    virtual ListItem* getSelectedItem();

    /**
     * on Win32 see LB_GETITEMHEIGHT
     */
    virtual unsigned long getItemHeight();

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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
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
*Revision 1.8.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.22.1  2003/03/12 03:11:23  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32LISTBOX_H__


