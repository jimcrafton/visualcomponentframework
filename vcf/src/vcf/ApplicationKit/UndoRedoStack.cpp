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
	StackCleared.fireEvent( &event );

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

	UndoRedoEvent event( this, UNDOREDO_EVENT_UNDO,firstCommand );
	UndoCommand.fireEvent( &event );
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
	RedoCommand.fireEvent( &event );
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
	redoStack_.clear();
	if ( true == autoExecute ) {
		command->execute();
		UndoRedoEvent event( this, UNDOREDO_EVENT_EXECUTE,command );
		ExecuteCommand.fireEvent( &event );
	}

	UndoRedoEvent event( this, UNDOREDO_EVENT_STACK_CHANGED, command );
	StackChanged.fireEvent( &event );
}

void UndoRedoStack::movetToRedoStack( Command* command )
{

}

Command* UndoRedoStack::getCurrentUndoComand()
{
	return undoStack_.back();
}

Command* UndoRedoStack::getCurrentRedoComand()
{
	return redoStack_.front();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.11  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.10.2.1  2003/08/06 21:27:49  ddiego
*minor changes
*
*Revision 1.10  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/12 03:13:27  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.8.2  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.8.8.1  2003/01/08 00:20:02  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.6.1  2002/08/03 04:26:32  ddiego
*gradual phasing back in of the UI editor features, taking into account the
*recent changes to the workspace/project graph
*
*Revision 1.7  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


