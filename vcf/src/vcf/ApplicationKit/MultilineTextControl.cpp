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
	setKeepsReturnChar( true );
	setKeepsTabKey( true );
}

MultilineTextControl::~MultilineTextControl()
{

}

String MultilineTextControl::getTextForLine( const uint32& lineIndex )
{
	String result;
	result = getTextModel()->getText();

	const VCFChar* P = result.c_str();
	const VCFChar* start = P;
	const VCFChar* lineStart = P;
	int32 count = result.size();
	uint32 lineCount = 0;

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

void MultilineTextControl::scrollToLine( const uint32& lineIndex )
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
$Id$
*/
