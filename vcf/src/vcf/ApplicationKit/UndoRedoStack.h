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
* stack class managing any undo redo operation.
* It is possible to bypass the default undo redo
* behaviour of this class, without deriving
* form this class, through the use of its UndoCommand 
* and RedoCommand delegates.
*/

class APPLICATIONKIT_API UndoRedoStack : public ObjectWithEvents {
public:
	/**
	* Used if the user desires to bypass the default behaviour of 
	* this UndoRedoStack instance. In this case the user needs 
	* to add an event handler to this delegate, and setAllowsUndo(false)
	* inside this handler.
	*/
	DELEGATE(UndoCommand);

	/**
	* Used if the user desires to bypass the default action of 
	* this UndoRedoStack instance. In this case the user needs 
	* to add an event handler to this delegate, and setAllowsRedo(false)
	* inside this handler.
	*/
	DELEGATE(RedoCommand);

	/**
	* to be notified that the stack is going to be be cleared.
	* This is called foreward.
	*/
	DELEGATE(StackCleared);

	/**
	* to be notified that the stack has been changed.
	* This is called afterward.
	*/
	DELEGATE(StackChanged);

	/**
	* to be notified that a command has been executed.
	* This is called after the command has been added to the undo stack,
	* and after the command has been executed
	*/
	DELEGATE(ExecuteCommand);

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


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/01/17 17:55:41  marcelloptr
*documentation
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/13 22:30:42  marcelloptr
*more documentation
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.7.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7  2003/05/17 20:37:05  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:09:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.5  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_UNDOREDOSTACK_H__


