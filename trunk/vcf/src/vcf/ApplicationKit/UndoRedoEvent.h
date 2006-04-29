#ifndef _VCF_UNDOREDOEVENT_H__
#define _VCF_UNDOREDOEVENT_H__
//UndoRedoEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define UNDOREDO_EVENT_UNDO				CUSTOM_EVENT_TYPES + 1000
#define UNDOREDO_EVENT_REDO				CUSTOM_EVENT_TYPES + 1001
#define UNDOREDO_EVENT_EXECUTE			CUSTOM_EVENT_TYPES + 1002
#define UNDOREDO_EVENT_STACK_CLEARED	CUSTOM_EVENT_TYPES + 1003
#define UNDOREDO_EVENT_STACK_CHANGED	CUSTOM_EVENT_TYPES + 1004

namespace VCF  {

class Command;

/**
\class UndoRedoEvent UndoRedoEvent.h "vcf/ApplicationKit/UndoRedoEvent.h"  
* the event for the UndoRedoStack operations.
* this event is mainly used to bypass the default behaviour
* performed by the UndoUndoStack instance involved.
* In this case the user needs to add an handler for this event
* to the UndoCommand or RedoCommand delegate of the UndoUndoStack 
* instance, and setAllowsUndo(false) or setAllowsRedo(false)
* inside this handler.
*
*/
class APPLICATIONKIT_API UndoRedoEvent : public Event {
public:
	/**
	* constructors
	*/
	UndoRedoEvent( Object* source, const unsigned long& eventType, Command* command=NULL ):
		Event(source,eventType), command_(command),allowUndo_(true),allowRedo_(true),allowExecute_(true){

	}

	UndoRedoEvent( const UndoRedoEvent& rhs ):Event(rhs),
		command_(NULL),allowUndo_(true),allowRedo_(true),allowExecute_(true)	{
		*this = rhs;
	}

	virtual ~UndoRedoEvent() {}

	/**
	* copy operator
	*/
	UndoRedoEvent& operator=( const UndoRedoEvent& rhs ) {
		Event::operator =( rhs );
		command_ = rhs.command_;
		allowUndo_ = rhs.allowUndo_;
		allowRedo_ = rhs.allowRedo_;
		allowExecute_ = rhs.allowExecute_;

		return *this;
	}

	/**
	* the command associated to the event.
	*/
	Command* getCommand(){
		return command_;
	}

	/**
	* sets the command to be associated to the event.
	*/
	void setCommand( Command* command ) {
		command_ = command;
	}

	/**
	*@return bool, false if the user managing this event
	* doens't want the UndoRedoStack instance to perform
	* hte default undo action.
	*
	*/
	bool getAllowsUndo() {
		return 	allowUndo_;
	}

	/**
	* if the user wants to bypass the undo action of the 
	* UndoRedoStack instance, he needs to assign this value
	* as false.
	*@param const bool& allowsUndo, true to let the default undo
	*action from the UndoRedoStack to be performed.
	*/
	void setAllowsUndo( const bool& allowsUndo ){
		allowUndo_ = allowsUndo;
		if ( false == allowUndo_ ) {
			this->setConsumed( true );//stop processing the events
		}
	}

	/**
	*@return bool, false if the user managing this event
	* doens't want the UndoRedoStack instance to perform
	* hte default redo action.
	*/
	bool getAllowsRedo() {
		return 	allowRedo_;
	}

	/**
	* if the user wants to bypass the redo action of the 
	* UndoRedoStack instance, he needs to assign this value
	* as false.
	*@param const bool& allowsRedo, true to let the default redo 
	*action from the UndoRedoStack to be performed.
	*/
	void setAllowsRedo( const bool& allowsRedo ){
		allowRedo_ = allowsRedo;
		if ( false == allowRedo_ ) {
			this->setConsumed( true );//stop processing the events
		}
	}

	/**
	* creates a new copy of this instance.
	*/
	virtual Object* clone( bool deep=false ) {
		return new UndoRedoEvent(*this);
	}

protected:
	/**
	* the command, potentially undoable, associated to this event.
	*/
	Command* command_;

	/**
	* flag to know if the user lets the default undo action of the 
	* UndoRedoStack instance to be performed.
	*/
	bool allowUndo_;

	/**
	* flag to know if the user lets the default redo action of the 
	* UndoRedoStack instance to be performed.
	*/
	bool allowRedo_;

	/**
	* allow for execution
	* currently unused
	*/
	bool allowExecute_;
private:
};



/**
*UndoRedoEventHandler
*handles the following:
*onUndoCommand
*onRedoCommand
*onStackCleared
*onStackChanged
*onExecuteCommand
*/
template <class SOURCE_TYPE>
class UndoRedoEventHandler : public EventHandlerInstance<SOURCE_TYPE,UndoRedoEvent> {
public:
	UndoRedoEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,UndoRedoEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,UndoRedoEvent>( source, handlerMethod, handlerName ) {

	}

};



}; //end of namespace VCF


#endif // _VCF_UNDOREDOEVENT_H__

/**
$Id$
*/
