//CommandGroup.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//CommandGroup.h
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

CommandGroup::CommandGroup()
{

}

CommandGroup::~CommandGroup()
{
	std::vector<Command*>::iterator it = commands_.begin();
	while ( it != commands_.end() ) {
		Command* command = *it;
		delete command;
		command = NULL;
		it++;
	}
}

void CommandGroup::undo()
{
	std::vector<Command*>::reverse_iterator it = commands_.rbegin();
	while ( it != commands_.rend() ) {
		Command* command = *it;
		command->undo();
		it++;
	}
}

void CommandGroup::redo()
{
	std::vector<Command*>::iterator it = commands_.begin();
	while ( it != commands_.end() ) {
		Command* command = *it;
		command->redo();
		it++;
	}
}

void CommandGroup::execute()
{
	std::vector<Command*>::iterator it = commands_.begin();
	while ( it != commands_.end() ) {
		Command* command = *it;
		command->execute();
		it++;
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.16.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.16.1  2003/03/12 03:13:01  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.2.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.2  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


