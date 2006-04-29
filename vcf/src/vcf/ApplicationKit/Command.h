#ifndef _VCF_COMMAND_H__
#define _VCF_COMMAND_H__
//Command.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class UndoRedoStack;


/**
\class Command Command.h "vcf/ApplicationKit/Command.h"
*A Command represents an interface describing a single
*action, that is potentially undoable.
*Commands are placed on the application wide UndoRedoStack object
*during the course of the application. Each command should represent
*a single user action like, typing text, or removing an item from
*a tree. The actual implementation will vary widely and will need
*whatever state variables are neccessary to both execute/redo the
*command, and undo the command.
*/
class APPLICATIONKIT_API Command {
public:
	virtual ~Command(){};

	/**
	*Undo the command
	*/
	virtual void undo() = 0;

	/**
	*redo the command. Generally the same, or similar, code
	*as performed in the execute() method
	*/
	virtual void redo() = 0;

	/**
	*execute the command. Usually called by the UndoRedoStack after
	*the command has been added to it.
	*/
	virtual void execute() = 0;

	/**
	*returns the UndoRedoStack that owns this command.
	*@return UndoRedoStack a pointer to the current UndoRedoStack
	*instance for this command object.
	*/
	virtual UndoRedoStack* getOwningStack() = 0;

	/**
	*sets the owning UndoRedoStack for this command
	*@param UndoRedoStack the UndoRedoStack that will
	*own this command
	*/
	virtual void setOwningStack( UndoRedoStack* stack ) = 0;

	/**
	*The name of this command. Frequently the name is the basis for the
	*display text that is shown in the "Edit | Undo" or "Edit | Redo" menu
	*items.
	*@return String the name of this command
	*/
	virtual String getName() = 0;

	/**
	*sets the name of this command
	*/
	virtual void setName( const String& name ) = 0;

	/**
	*Is this command undoable ?
	*@return bool true if the command's undo()/redo() methods
	*can be safely called, otherwise false. Commands that return
	*false for this method are usually not added to the UndoRedoStack
	*though they will be executed.
	*/
	virtual bool isUndoable() = 0;
protected:

private:
};


}; //end of namespace VCF


#endif // _VCF_COMMAND_H__

/**
$Id$
*/
