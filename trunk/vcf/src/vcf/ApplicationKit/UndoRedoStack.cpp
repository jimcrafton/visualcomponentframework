//UndoRedoStack.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//UndoRedoStack.h
#include "vcf/ApplicationKit/ApplicationKit.h"
using namespace VCF;


UndoRedoStack::UndoRedoStack()
{

}

UndoRedoStack::~UndoRedoStack()
{
	clearCommands();
}

void UndoRedoStack::clearCommands()
{
	UndoRedoEvent event( this, UNDOREDO_EVENT_STACK_CLEARED );
	StackCleared( &event );

	std::deque<Command*>::iterator it = undoStack_.begin();
	while ( it != undoStack_.end() ) {
		Command* command = *it;
		delete command;
		command = NULL;
		it++;
	}
	
	it = redoStack_.begin();
	while ( it != redoStack_.end() ) {
		Command* command = *it;
		delete command;
		command = NULL;
		it++;
	}
	undoStack_.clear();
	redoStack_.clear();
}

void UndoRedoStack::undo()
{
	if ( undoStack_.empty() ) {
		return;
	}

	Command* firstCommand = undoStack_.back();

	UndoRedoEvent event( this, UNDOREDO_EVENT_UNDO, firstCommand );
	UndoCommand( &event );

	/* the default undo action of this class is bypassed if the user needs */
	if ( true == event.getAllowsUndo() ) {
		firstCommand->undo();
		undoStack_.pop_back();
		redoStack_.push_front( firstCommand );
	}
}

void UndoRedoStack::redo()
{
	if ( redoStack_.empty() ) {
		return;
	}

	Command* firstCommand = redoStack_.front();

	UndoRedoEvent event( this, UNDOREDO_EVENT_REDO,firstCommand );
	RedoCommand( &event );

	/* the default redo action of this class is bypassed if the user needs */
	if ( true == event.getAllowsRedo() ) {
		firstCommand->redo();
		redoStack_.pop_front();
		undoStack_.push_back( firstCommand );
	}
}

bool UndoRedoStack::hasUndoableItems()
{
	return !undoStack_.empty();
}

bool UndoRedoStack::hasRedoableItems()
{
	return !redoStack_.empty();
}

void UndoRedoStack::addCommand( Command* command, const bool& autoExecute )
{
	command->setOwningStack( this );
	undoStack_.push_back( command );

	std::deque<Command*>::iterator it = redoStack_.begin();
	while ( it != redoStack_.end() ) {
		Command* command = *it;
		delete command;
		it++;
	}
	redoStack_.clear();

	if ( true == autoExecute ) {
		command->execute();
		UndoRedoEvent event( this, UNDOREDO_EVENT_EXECUTE,command );
		ExecuteCommand( &event );
	}

	UndoRedoEvent event( this, UNDOREDO_EVENT_STACK_CHANGED, command );
	StackChanged( &event );
}

void UndoRedoStack::movetToRedoStack( Command* command )
{

}

Command* UndoRedoStack::getCurrentUndoCommand()
{
	return undoStack_.back();
}

Command* UndoRedoStack::getCurrentRedoCommand()
{
	return redoStack_.front();
}


/**
$Id$
*/
