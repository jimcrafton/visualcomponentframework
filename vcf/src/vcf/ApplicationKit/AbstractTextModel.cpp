//AbstractTextModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractTextModel.h"


using namespace VCF;


AbstractTextModel::AbstractTextModel()
{
}

AbstractTextModel::~AbstractTextModel()
{

}


void AbstractTextModel::setText( const String& text )
{
	text_ = text;

	TextEvent event( this, text );

	TextModelChanged.fireEvent( &event );
}

void AbstractTextModel::empty()
{
	AbstractTextModel::setText( "" );

	//this->text_ = "";
	//
	//TextModel::empty();
}

void AbstractTextModel::insertText( const unsigned long& index, const String& text )
{
	String changeText = getText();
	changeText.insert( index, text );

	AbstractTextModel::setText( changeText );
}

void AbstractTextModel::replaceText( const unsigned long& index, const unsigned long& len, const String& text )
{
	String changeText = getText();
	unsigned long length, pos;
	length = changeText.size();
	pos = VCF::minVal< unsigned long > ( index+len, length );
	length = VCF::maxVal< unsigned long > ( 0, length-pos );
	String preText = changeText.substr( 0, index );
	String postText = changeText.substr( pos, length );
	changeText = preText + text + postText;

	AbstractTextModel::setText( changeText );
}

void AbstractTextModel::deleteText( const unsigned long& index, const unsigned long& count )
{
	String changeText = this->text_.substr( index, count );

	AbstractTextModel::setText( changeText );
}

void AbstractTextModel::appendText( const String& text )
{
	String changeText = getText();
	changeText.append( text );

	AbstractTextModel::setText( changeText );
}

String AbstractTextModel::getText()
{
	return this->text_;
}

unsigned long AbstractTextModel::getSize()
{
	return this->text_.size();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.13  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.6.2  2004/03/21 19:44:58  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.12.6.1  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.12  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.3  2003/03/25 20:25:42  marcelloptr
*AbstractTextModel::appendText() fixed
*
*Revision 1.11.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:12:57  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.2.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.10.2.2  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10.2.1  2002/12/27 23:04:58  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.9.10.1  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.9  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.8  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


