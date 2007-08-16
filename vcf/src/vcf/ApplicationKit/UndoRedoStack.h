#ifndef _VCF_UNDOREDOSTACK_H__
#define _VCF_UNDOREDOSTACK_H__
//UndoRedoStack.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include <deque>



namespace VCF  {

/**
\class UndoRedoStack UndoRedoStack.h "vcf/ApplicationKit/UndoRedoStack.h"  
* stack class managing any undo redo operation.
* It is possible to bypass the default undo redo
* behaviour of this class, without deriving
* form this class, through the use of its UndoCommand 
* and RedoCommand delegates.
*/

class APPLICATIONKIT_API UndoRedoStack : public ObjectWithCallbacks {
public:
	/**
	* Used if the user desires to bypass the default behaviour of 
	* this UndoRedoStack instance. In this case the user needs 
	* to add an event handler to this delegate, and setAllowsUndo(false)
	* inside this handler.
	*/
	DELEGATE(UndoRedoDelegate,UndoCommand);

	/**
	* Used if the user desires to bypass the default action of 
	* this UndoRedoStack instance. In this case the user needs 
	* to add an event handler to this delegate, and setAllowsRedo(false)
	* inside this handler.
	*/
	DELEGATE(UndoRedoDelegate,RedoCommand);

	/**
	* to be notified that the stack is going to be be cleared.
	* This is called foreward.
	*/
	DELEGATE(UndoRedoDelegate,StackCleared);

	/**
	* to be notified that the stack has been changed.
	* This is called afterward.
	*/
	DELEGATE(UndoRedoDelegate,StackChanged);

	/**
	* to be notified that a command has been executed.
	* This is called after the command has been added to the undo stack,
	* and after the command has been executed
	*/
	DELEGATE(UndoRedoDelegate,ExecuteCommand);

public:
	UndoRedoStack();

	virtual ~UndoRedoStack();

	/**
	* undoes the last command.
	* this default behaviour can be bypassed.
	*@fire UndoCommand, before the default undo action is performed.
	*@event UndoRedoEvent
	*@eventtype UNDOREDO_EVENT_UNDO
	*/
	virtual void undo();

	/**
	* redoes the last command ( undoes the previous undo ).
	* this default behaviour can be bypassed.
	*@fire UndoCommand, before the default redo action is performed.
	*@event UndoRedoEvent
	*@eventtype UNDOREDO_EVENT_REDO
	*/
	virtual void redo();

	/**
	* tells if there is any undo item in the stack.
	*/
	virtual bool hasUndoableItems();

	/**
	* tells if there is any redo item in the stack.
	*/
	virtual bool hasRedoableItems();

	/**
	* adds a command to the undo stack and clears the redo stack.
	* By default this also executes the command.
	*@param Command* command, the instance representing
	*the action which is potentially undoable.
	*@const bool& autoExecute, true if the operation needs also 
	*to be executed. This is the default.
	*@fire ExecuteCommand, only if autoExecute==true, after the command has been executed.
	*@event UndoRedoEvent
	*@eventtype UNDOREDO_EVENT_EXECUTE.
	*@fire StackChanged, after the command has been added.
	*@event UndoRedoEvent
	*@eventtype UNDOREDO_EVENT_STACK_CHANGED.
	*/
	virtual void addCommand( Command* command, const bool& autoExecute=true );

	/**
	* gets the first command to undo.
	*/
	virtual Command* getCurrentUndoCommand();

	/**
	* gets the first command to redo.
	*/
	virtual Command* getCurrentRedoCommand();

	/**
	* clears both the undo/redo stacks.
	*@fire StackChanged, event before the stack is cleared.
	*@event UndoRedoEvent
	*@eventtype UNDOREDO_EVENT_STACK_CHANGED.
	*/
	void clearCommands();

protected:
	/**
	* Unused.
	* MP ?
	*/
	void movetToRedoStack( Command* command );

	/**
	* the undo and redo internal stacks.
	*/
	std::deque<Command*> undoStack_;
	std::deque<Command*> redoStack_;
private:
};


}; // namespace VCF


#endif // _VCF_UNDOREDOSTACK_H__

/**
$Id$
*/
