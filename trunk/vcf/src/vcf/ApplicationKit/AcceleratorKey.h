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
*An AcceleratorKey represents a link between a specific
*keyboard keystroke combination and an event handler to
*be invoked when the combination takes place.
*An AcceleratorKey object may associated with a control or it
*may be associated with the current application instance for
*global behaviour. For example let's say you have a text editor
*and you want the "Ctrl" and "V" key combination to call an event
*handler whenever it is pressed to paste in some text from the
*clipboard. You can register an AcceleratorKey with the keyboard
*combination and you event handler, and <i>voila!</i> the VCF
*will take care of the rest.
*@see UIToolkit::addAcceleratorKey()
*/
class APPLICATIONKIT_API AcceleratorKey : public VCF::Object {
public:
	AcceleratorKey( Control* associatedControl, const VirtualKeyCode& keyCode,
					const ulong32& modifierMask, EventHandler* eventHandler,
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
	*@return ulong32 the keycode for this AcceleratorKey
	*/
	ulong32 getKeyCode() {
		return keyCode_;
	}

	/**
	*gets the modifier mask for the AcceleratorKey. The
	*modifier mask may be made up of any combination
	*of the Ctrl, Shift, and Alt keys.
	*/
	ulong32 getModifierMask() {
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
protected:
	VirtualKeyCode keyCode_;
	ulong32 modifierMask_;
	Control* associatedControl_;
	EventHandler* eventHandler_;
	bool isMnemonic_;
private:
};


}; //end of namespace VCF


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
*Revision 1.6.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.5.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.5  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.22.1  2003/03/12 03:09:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.3  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ACCELERATORKEY_H__


