#ifndef _VCF_ACTION_H__
#define _VCF_ACTION_H__
//Action.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class AcceleratorKey;

/**
<p>
The Action class is used to represent an "action" that gets performed because of
some event from the UI, such as clicking a menu item or button. An Action also
allows you to consolidate multiple event handlers for menu items, buttons, etc,
and their associated code to update their UI state in relation to the application's
state. An Action has one or more targets that get notified for update events. Any of
these targets can also cause the action to be executed or "performed".
<p>An example
of how this might be useful:
Consider an application that has three UI elements, a button, a toolbar item,
and a menu item. Clicking the menu item, toolbar item, or button all cause
some change of state in the application. Without using actions, you would have to
write 3 individual event handlers for the "click" events of the menu item,
button, and toolbar item, as well as separate ui updating code. If you use an
action, you simply add all three items as targets to the action, and then write
a single handler that's attached to the action's Performed delegate, and another
event handler that is attached to the action's Update delegate. The framework then takes
care of the rest, and clicking the button, menu item, or toolbar item will all cause
event handler attached to the action's Performed delegate to get called, and each
UI element will in turn be updated as specified by event handler attached to the
action's Update delegate.

@delegates
	@del Update
	@del Performed
*/
class APPLICATIONKIT_API Action : public Component {
public:
	Action();

	Action( Component* owner );

	Action( const String& name, Component* owner );

	Action( const String& name );

	virtual ~Action();

	enum {
		/**
		This event type is used when the update method is invoked.
		*/
		UpdateEvent = 40521,

		/**
		This is used when an action event is fired.
		*/
		ActionPerformedEvent = 40511,

		/**
		This is used when the action's accelerator is changed, specifically
		by the method setAcceleratorKey().
		*/
		AcceleratorChanged = 40541
	};

	/**
	@delegate Update this is fired when the action's update() method is called.
	@event	ActionEvent
	@eventtype Action::UpdateEvent
	@see update()
	*/
	DELEGATE(Update);

	/**
	@delegate Performed this is fired when the action's perform()
	method is called.
	@event ActionEvent
	@eventtype Action::ActionPerformedEvent
	@see perform()
	*/
	DELEGATE(Performed);

	/**
	This is called by a target (or the framework itself) to tell the action to fire off an
	update event to all the actions targets.
	First an Update event is fired in order to let the application to set, in the event(s) 
	handler(s) of this action, the desired state for the ActionEvent ( e.g. enabled
	or not, checked or not.
	Then the update ActionEvent is fired off to all the actions targets.
	The enabled state of the accelerator associated to this action, if any, is also updated
	accordingly.
	@see ActionEvent
	*/
	void update();

	/**
	This is called to execute the action. An action performed event will be fired off
	to all the event handlers attached to the Performed delegate.
	*/
	void perform( Event* event=NULL );

	/**
	adds a target to the action
	*/
	void addTarget( Component* target );

	/**
	removes a target from the action.
	*/
	void removeTarget( Component* target );

	/**
	returns an enumerator of all the targets currently attached to this
	action.
	*/
	Enumerator<Component*>* getTargets();

	/**
	returns a count of the number of targets attached to this action.
	*/
	unsigned long getTargetCount();

	/**
	\p
	This sets the accelerator key object for the action item. If one already exists
	it is removed for this action item. The accelerator is assigned the 
	key code and modifier mask passed in, and is given a default event handler which
	calls the action item's perform method.
	\p
	An action may have only one accelerator associated with it at any given time.
	\p
	Internally this method creates a new AcceleratorKey isntance and then calls the 
	setAcceleratorKey( AcceleratorKey* ) method. See this method's documentation for
	more details.
	@see setAcceleratorKey
	*/
	void setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	/**
	\p
	Sets the acclerator object for this action item. If one already exists then it 
	is removed.
	\p
	To ensure that any targets of this action are properly updated, the action 
	creates a Event instance, sets it's event type to Action::AcceleratorChanged, 
	loops through all it's targets, and then calls each target's handleEvent() method
	passing in the event instance. Targets should respond accordingly to this event
	if it makes sense.
	*/
	void setAcceleratorKey( AcceleratorKey* accelerator );

	/**
	Returns the accelerator for the action item.
	*/
	AcceleratorKey* getAccelerator();

	/**
	Returns the event handler used to trigger the action's 
	perform() method when the appropriate key combination
	is pressed. If no event handler exists at the time of this
	call, a new instance will be created.
	*/
	EventHandler* getAcceleratorEventHandler();
protected:
	/**
	* the default event handler for the accelerator associated to this action.
	*/
	void onAccelerator( KeyboardEvent* e );

protected:
	AcceleratorKey* currentAccelerator_;
	std::vector<Component*> targets_;
	EnumeratorContainer<std::vector<Component*>,Component*> targetsContainer_;

};




};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.5  2005/06/02 15:26:54  marcelloptr
*more documentation
*
*Revision 1.2.4.4  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2.4.3  2005/03/14 19:02:02  marcelloptr
*comments and added an error message to avoid an infinite loop
*
*Revision 1.2.4.1  2005/03/14 04:17:22  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
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
*Revision 1.2.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.3  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.1.2.2  2003/12/08 05:05:27  ddiego
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


#endif // _VCF_ACTION_H__


