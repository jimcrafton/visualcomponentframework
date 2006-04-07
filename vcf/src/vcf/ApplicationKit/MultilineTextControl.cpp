//MultilineTextControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//MultilineTextControl.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MultilineTextControl.h"
#include "vcf/ApplicationKit/TextPeer.h"


using namespace VCF;


MultilineTextControl::MultilineTextControl():
	TextControl( true )
{
	keepTabbingCharacters_ = true;
	keepReturnCharacter_ = true;
}

MultilineTextControl::~MultilineTextControl()
{

}

String MultilineTextControl::getTextForLine( const ulong32& lineIndex )
{
	String result;
	result = getTextModel()->getText();

	const VCFChar* P = result.c_str();
	const VCFChar* start = P;
	const VCFChar* lineStart = P;
	long count = result.size();
	ulong32 lineCount = 0;

	bool lineMatchFound = false;
	bool lineFound = false;
	bool trimForCRLF = false;

	while ( (P-start) < count ) {
		lineFound = false;
		trimForCRLF = false;

		if ( *P == '\n' ) {
			lineFound = true;
		}
		else if ( (*P == '\r') && (*(P+1) == '\n') ) {
			lineFound = true;
			trimForCRLF = true;
			P++;
		}
		else if ( (*P == '\r') ) {
			lineFound = true;
		}


		if ( true == lineFound ) {
			if ( lineIndex == (lineCount) ) {
				break;
			}

			lineCount ++;
			lineStart = P+1; //move past the current char
		}
		P++;
	}

	lineMatchFound = (lineIndex == lineCount);

	result = "";
	if ( (true == lineMatchFound) ) {
		if ( true == trimForCRLF ) {
			//P--;
		}

		result.append( lineStart, (P-lineStart) );
	}

	return result;
}

void MultilineTextControl::scrollToLine( const ulong32& lineIndex )
{
	textPeer_->scrollToLine( lineIndex );
}

void MultilineTextControl::scrollToSelection( const bool& _showEndSel/*=false*/ )
{
	if ( NULL == textPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	textPeer_->scrollToSelection( _showEndSel );
}

void MultilineTextControl::gotFocus( FocusEvent* event )
{
	//no-op on purpose!
}
/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/21 00:57:35  ddiego
*fixed bug in table control - problem was really with casting a
*model to a table model, and having the pointer value not be right. Needed
*to use dynamic_cast() to fix it. Curiously this problem was not flagegd in
*debug at all.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.15  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.2  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.13.2.1  2004/01/19 23:32:06  ddiego
**** empty log message ***
*
*Revision 1.13  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.1  2003/08/12 20:30:32  marcelloptr
*improvement: multiline editor - scrollToSelection
*
*Revision 1.12  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:13:15  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.9  2002/03/13 03:09:54  ddiego
*adjusted tree control drawing code when not in full row selection
*addjust buffer overrun when calculating a single line of text for a
*MultilineTextControl
*
*Revision 1.8  2002/02/07 16:11:27  ddiego
*fixed TextModel assignment for keyboard events (forgot to uncomment it from yesterday -
*dohh! )
*Added default setting for MultiLineTextControl's keepReturnCharacter_ (set to
*false to keep the enter key)
*
*Revision 1.7  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


