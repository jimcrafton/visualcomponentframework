#ifndef _VCF_ACCELERATORKEY_H__
#define _VCF_ACCELERATORKEY_H__
//AcceleratorKey.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class Control;

/**
\class AcceleratorKey AcceleratorKey.h "vcf/ApplicationKit/AcceleratorKey.h"
An AcceleratorKey represents a link between a specific
keyboard keystroke combination and an event handler to
be invoked when the combination takes place. There
may be more than one intance of a AcceleratorKey that 
is linked to the same keystroke combination. AcceleratorKey 
objects may associated with a control, a menu item or 
a some other generic Object instance. 

AcceleratorKey objects may also be linked to Action objects
which allows the action and accelerator to be linked together
and reused among more than one target, such as a button, and 
menu item. 

Certain classes may have multiple accelerators associated with
them, while others may have only one. A Control may 0 or more
accelerators associated with it. A MenuItem or Action may have
only one accelerator associated with it at any given moment.

The UIToolkit is used to store all the various accelerators,
as well as implemententing the exact logic for how accelerators
get called. The toolkit will release any accelerators, so once
assigned, you no longer have to worry about cleaning up the memory
for the object. 

When toolkit receives notification from the underlying window system
that a keystroke has taken place, it attempts to see if the keystroke
maps to any registered accelerators, and if it finds one, then the 
accelerator's event handler is invoked. This logic thus allows you 
to have multiple accelerators mapped to both a control and to a menu 
item. Precedence is given to the control, then the menu item, and then 
anything else.
The logic for determining the proper accelerator to use is this:
\li The toolkit attempts to find the current focused control.
\li It then attemps to match an accelerator, based on the keystroke
and the current focused control
\li If no accelerator is found that has a matching control (see 
Accelerator::getAssociatedControl() ), then a search is made to
find an accelerator with the keystroke.
\li The first accelerator found with the matching keystroke, \em and 
a non NULL menu associated with it (see Accelerator::getAssociatedMenuItem() )
is then used. 
\li If no match is found then a similar search is made for any accelerators
that match the keystroke and have a non NULL object associated with it.

An example of how you might use an accelerator is this:
Let's say you have a text editor and you want the "Ctrl" and "V" key 
combination to call an event handler whenever it is pressed to paste 
in some text from the clipboard. You can register an AcceleratorKey with 
the keyboard combination and you event handler, and <i>voila!</i> the VCF
will take care of the rest.

In addition to this, menu items also work with accelerators to enable 
the accelerator information to be displayed in the menu item caption/text.
This will work for any menu item that has an accelerator set "directly",
or a menu item that is associated with an Action that itself has an
accelerator assigned to it. This means that instead of having to manually
set the text for your menu item to hold the key combo associated with it, 
the framework will do it for you. For example:
\code
MenuItem* fileOpen = new DefaultMenuItem( "Open", file, menuBar );
fileOpen->setAcceleratorKey( vkLetterO, kmCtrl );
\endcode
That's it! The fileOpen menu item will be adjusted when it's displayed,
and instead of just displaying "Open", it will display "Open	Ctrl+O".
This works with actions as well:
\code
MenuItem* fileOpen = new DefaultMenuItem( "Open", file, menuBar );
Action* fileOpenAction = new Action();
addComponent( fileOpenAction );
fileOpenAction->addTarget( fileOpen );
fileOpenAction->setAcceleratorKey( vkLetterO, kmCtrl );
\endcode
The same thing will now happen, the menu will still display 
"Open	Ctrl+O", despite the accelerator being set on the action
instead of the menu item directly.
@see Control::addAcceleratorKey
@see MenuItem::setAcceleratorKey
@see Action::setAcceleratorKey
@see UIToolkit::addAcceleratorKey()
*/
class APPLICATIONKIT_API AcceleratorKey : public VCF::Object {
public:

	/**
	\class Value AcceleratorKey.h "vcf/ApplicationKit/AcceleratorKey.h"
	This class is used to hold the values of both the 
	keyboard modifier(s), such as Ctrl, Shift, or Alt,
	and the virtual key value, such as vkLetterV.	
	
	The actual data is stored as 2 unsigned 16 bit values,
	within one unsigned 32 bit member variable. The 
	virtual key code is stored in the upper 16 bits,
	and the keyboard modifiers are stored in the lower 
	16 bits.
	*/
	class Value {
	public:
		enum {
			ShiftBy = 16,
			MaskBy	= 0x0000FFFF
		};
		Value(): val_(0){};

		Value(const uint32& modifierMask, const VirtualKeyCode& keyCode): val_(0){
			val_ = modifierMask | (keyCode << Value::ShiftBy);
		}

		bool isEmpty() const {
			return  0 == val_;
		}

		bool hasShiftKey() const {
			return ((getModifierMask() & kmShift) != 0);
		}

		bool hasCtrlKey() const {
			return ((getModifierMask() & kmCtrl) != 0);
		}

		bool hasAltKey() const {
			return ((getModifierMask() & kmAlt) != 0);
		}

		VirtualKeyCode getKeyCode() const {
			return (VirtualKeyCode)(val_ >> Value::ShiftBy);
		}

		void setKeyCode( const VirtualKeyCode& keyCode ) {
			val_ = (keyCode << Value::ShiftBy) | (val_ & Value::MaskBy);
		}
		
		uint32 getModifierMask() const {
			return val_ & Value::MaskBy;
		}

		void setModifierMask( const uint32& modifierMask ) {
			val_ = modifierMask | (val_ & (Value::MaskBy<< Value::ShiftBy));
		}


		Value& operator= ( const uint32& val ) {
			val_ = val;
			return *this;
		}

		Value& operator= ( AcceleratorKey* val ) {
			if ( NULL == val ) {
				val_ = 0;
			}
			else {
				val_ = val->getModifierMask() | (val->getKeyCode() << Value::ShiftBy);
			}
			return *this;
		}

		operator uint32() const {
			return val_;
		}

		bool operator == ( const Value& rhs ) const {
			return val_ == rhs.val_;
		}

		bool operator != ( const Value& rhs ) const {
			return val_ != rhs.val_;
		}
	protected:
		uint32 val_;
	};

	AcceleratorKey( Control* associatedControl, const VirtualKeyCode& keyCode,
					const uint32& modifierMask, EventHandler* eventHandler,
					const bool& isMnemonic=false );

	AcceleratorKey( MenuItem* associatedMenuItem, const VirtualKeyCode& keyCode,
					const uint32& modifierMask, EventHandler* eventHandler,
					const bool& isMnemonic=false );

	AcceleratorKey( Object* associatedObject, const VirtualKeyCode& keyCode,
					const uint32& modifierMask, EventHandler* eventHandler,
					const bool& isMnemonic=false );

	virtual ~AcceleratorKey();

	/**
	*does the AcceleratorKey have the shift key in it's keyboard
	*combination.
	*@return bool returns true if it does, false if it doesn't
	*/
	bool hasShiftKey();

	/**
	*does the AcceleratorKey have the Ctrl key in it's keyboard
	*combination.
	*@return bool returns true if it does, false if it doesn't
	*/
	bool hasCtrlKey();

	/**
	*does the AcceleratorKey have the Alt key in it's keyboard
	*combination.
	*@return bool returns true if it does, false if it doesn't
	*/
	bool hasAltKey();

	/**
	*gets the virtual key code that represents the
	*specific alpha numeric key, like "V", or "1" or "F1"
	*@return uint32 the keycode for this AcceleratorKey
	*/
	uint32 getKeyCode() const {
		return keyCode_;
	}

	/**
	*gets the modifier mask for the AcceleratorKey. The
	*modifier mask may be made up of any combination
	*of the Ctrl, Shift, and Alt keys.
	*/
	uint32 getModifierMask() const {
		return modifierMask_;
	}

	/**
	*returns the associated control. An AcceleratorKey
	*can have a control instance associated with it.
	*@return Control the associated control
	*/
	Control* getAssociatedControl() {
		return associatedControl_;
	}

	/**
	*returns the associated menu item. An AcceleratorKey
	*can have a menu item instance associated with it.
	*@return MenuItem the associated menu item
	*/
	MenuItem* getAssociatedMenuItem() {
		return associatedMenuItem_;
	}

	/**
	*returns the associated object instance. An AcceleratorKey
	*can have an object instance associated with it.
	*@return Object the associated object
	*/
	Object* getAssociatedObject() {
		return associatedObject_;
	}

	/**
	*The event handler that will be invoked
	*by the AcceleratorKey when it becomes activated
	*by the framework.
	*@return EventHandler the AcceleratorKey's event handler
	*/
	EventHandler* getEventHandler() {
		return eventHandler_;
	}

	/**
	*call this method to invoke the
	*event handler for this AcceleratorKey.
	*The implementation simply passes the event
	*to the invoke()  method on the event handler.
	*@param Event* the event to pass to the event
	*handler
	*@see EventHandler::invoke()
	*/
	void invoke( Event* event );

	/**
	*returns whether or not the AcceleratorKey is triggered by a
	*keyboard mnemonic. A keyboard mnemonic is a single alpha-numeric key
	*plus the "Alt" key that trigger an action on a control. For example
	*a button might have a caption "Erase" and the mnemonic was the
	*"Alt" + "E" keys (this is usually displayed on controls as a
	*character with an underline). Pressing the "Alt" + "E" key combination
	*would cause the button's mnemonicActivate() method to be called.
	*@return bool returns true if the AcceleratorKey is a mnemonic false
	*otherwise
	*@see Control::mnemonicActivate()
	*/
	bool isMnemonic() {
		return isMnemonic_;
	}

	bool isEnabled() {
		return enabled_;
	}

	void setEnabled( const bool& val );

	virtual Object* clone( bool deep=false );
protected:
	VirtualKeyCode keyCode_;
	uint32 modifierMask_;
	Control* associatedControl_;
	MenuItem* associatedMenuItem_;
	Object* associatedObject_;
	EventHandler* eventHandler_;
	bool isMnemonic_;
	bool enabled_;

	AcceleratorKey( const AcceleratorKey& rhs );

private:
};


}; //end of namespace VCF


#endif // _VCF_ACCELERATORKEY_H__

/**
$Id$
*/
