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



#define ACTION_CLASSID		"f3feab50-61f5-4b67-8a94-3b479e231a3e"

class AcceleratorKey;

/**
\class Action Action.h "vcf/ApplicationKit/Action.h"
The Action class is used to represent an "action" that gets performed because of
some event from the UI, such as clicking a menu item or button. An Action also
allows you to consolidate multiple event handlers for menu items, buttons, etc,
and their associated code to update their UI state in relation to the application's
state. An Action has one or more targets that get notified for update events. Any of
these targets can also cause the action to be executed or "performed".

An example of how this might be useful:

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
	DELEGATE(ActionDelegate,Update);

	/**
	@delegate Performed this is fired when the action's perform()
	method is called. Check the event type and confirm that it's a
	Action::ActionPerformedEvent before casting to an ActionEvent type.
	Otherwise it's whatever event the target might normally fire, 
	such as a ButtonEvent.
	@event Event
	@eventtype Action::ActionPerformedEvent
	@see perform()
	*/
	DELEGATE(EventDelegate,Performed);

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

	void perform( UIComponent* target );

	/**
	adds a target to the action
	*/
	void addTarget( UIComponent* target );

	/**
	removes a target from the action.
	*/
	void removeTarget( UIComponent* target );


	//add targets by index, basically here for 
	//support for modify targets via the VFF format
	UIComponent* getTarget( const uint32& index ) const ;

	void setTarget( const uint32& index, UIComponent* target );

	uint32 getTargetIndexes( std::vector<uint32>& indexes );

	/**
	returns an enumerator of all the targets currently attached to this
	action.
	*/
	Enumerator<UIComponent*>* getTargets();

	/**
	returns a count of the number of targets attached to this action.
	*/
	uint32 getTargetCount();

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
	void setAcceleratorKeyInfo( const VirtualKeyCode& keyCode, const uint32& modifierMask );

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
	void onAccelerator( Event* e );

protected:
	AcceleratorKey* currentAccelerator_;
	std::vector<UIComponent*> targets_;
	EnumeratorContainer<std::vector<UIComponent*>,UIComponent*> targetsContainer_;

};




};


#endif // _VCF_ACTION_H__

/**
$Id$
*/
