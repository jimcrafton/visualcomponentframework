#ifndef _VCF_ACTIONEVENT_H__
#define _VCF_ACTIONEVENT_H__
//ActionEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
The ActionEvent is used to store and read the state about a particular action.
With the ActionEvent you can store the text, enabled, checked, or user defined
state of a particular actions. This ActionEvent is then handled (if appropriate)
by the rtegistered component target in the target's handleEvent function, where
the state is read and applied to the target however it makes the most sense.
*/
class APPLICATIONKIT_API ActionEvent : public Event {
public:

	ActionEvent( Object* source, const ulong32& eventType ):
	  Event(source,eventType),enabled_(true), state_(0),modified_(false),
	  checked_(false),exlusiveChecked_(false){}

	ActionEvent( const ActionEvent& rhs ):Event(rhs),enabled_(true), state_(0),modified_(false),
		checked_(false),exlusiveChecked_(false) {
		*this = rhs;
	}

	ActionEvent& operator=( const ActionEvent& rhs ) {
		Event::operator =( rhs );

		enabled_ = rhs.enabled_;
		state_ = rhs.state_;
		text_ = rhs.text_;
		modified_ = rhs.modified_;
		checked_ = rhs.checked_;
		exlusiveChecked_ = rhs.exlusiveChecked_;
		statusText_ = rhs.statusText_;

		return *this;
	}

	virtual Object* clone( bool deep=false ) {
		return new ActionEvent(*this);
	}

	/**
	Sets the text for a an ActionEvent
	*/
	void setText( const String& val ) {
		modified_ = true;
		text_ = val;
	}

	/**
	Sets whether or not the target should consider itself enabled or not.
	*/
	void setEnabled( const bool& val ) {
		modified_ = true;
		enabled_ = val;
	}

	/**
	Sets a user defined state, that is up to the target implementer to
	interpret. For example, a ToolbarItem looks at this value and queries
	whether the ToolbarItem::tisPressed bits are set. A MenuItem might
	look at this value entirely differently (or even ignore it).
	*/
	void setState( const long& val ) {
		modified_ = true;
		state_ = val;
	}

	/**
	Sets whether target should consider itself "checked". A MenuItem might choose to
	call it's MenuItem::setChecked() with this value.
	*/
	void setChecked( const bool& val ) {
		modified_ = true;
		checked_ = val;
	}

	/**
	Sets whether or not the checked value of this action event should
	be considered as an exclusive value. For example, if
	the action event's exclusive checked is true, then a MenuItem might
	call it's MenuItem::setRadioItem() with the value of the action
	events checked member.
	*/
	void setExclusiveChecked( const bool& val ) {
		modified_ = true;
		exlusiveChecked_ = val;
	}

	/**
	Sets the status text for this action event.
	*/
	void setStatusText( const String& val ) {
		modified_ = true;
		statusText_ = val;
	}

	/**
	Returns the text of this Action event
	*/
	String getText() {
		return text_;
	}

	/**
	returns whether or not the event is enabled
	*/
	bool isEnabled() {
		return enabled_;
	}

	/**
	returns the user defined state of the event
	*/
	long getState() {
		return state_;
	}

	/**
	returns whether the event has been modified. A new event has not yet been
	modified. Any calls to setText(), setEnabled(), setState(), setChecked(),
	or setExclusiveChecked() cause the event to be marked as modified.
	*/
	bool isModified() {
		return modified_;
	}

	/**
	Returns whether the event is checked
	*/
	bool isChecked() {
		return checked_;
	}

	/**
	Returns whether the value returned from isChecked() should be interpreted as
	an exclusive checked state. Useful for user interface items that may have
	multiple options but only allow one to be selected, such as radio
	item menus, or radio buttons.
	*/
	bool isExclusiveChecked() {
		return exlusiveChecked_;
	}

	/**
	returns a string that represents status text, such as what a status bar might use
	*/
	String getStatusText() {
		return statusText_;
	}
protected:
	String text_;
	bool enabled_;
	long state_;
	bool modified_;
	bool checked_;
	bool exlusiveChecked_;
	String statusText_;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
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
*Revision 1.2.4.1  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.2  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.1.2.1  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*/


#endif // _VCF_ACTIONEVENT_H__


