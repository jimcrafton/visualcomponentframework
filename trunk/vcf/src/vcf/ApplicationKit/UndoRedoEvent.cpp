//UndoRedoEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//UndoRedoEvent.h
#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


UndoRedoEvent::UndoRedoEvent( Object* source, const unsigned long& eventType, Command* command ):
	Event( source, eventType )
{
	command_ = command;
	allowUndo_ = true;
	allowRedo_ = true;
	this->allowExecute_ = true;
}

UndoRedoEvent::~UndoRedoEvent()
{

}

void UndoRedoEvent::setAllowsUndo( const bool& allowsUndo ){
	allowUndo_ = allowsUndo;
	if ( false == allowUndo_ ) {
		this->setConsumed( true );//stop processing the events
	}
}

void UndoRedoEvent::setAllowsRedo( const bool& allowsRedo ){
	allowRedo_ = allowsRedo;
	if ( false == allowRedo_ ) {
		this->setConsumed( true );//stop processing the events
	}
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
*Revision 1.6  2003/05/17 20:37:19  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/12 03:11:57  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:45  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/01/08 00:19:50  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


