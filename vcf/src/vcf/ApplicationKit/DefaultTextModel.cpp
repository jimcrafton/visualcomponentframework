//DefaultTextModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTextModel.h"


using namespace VCF;

DefaultTextModel::DefaultTextModel()
{

}

DefaultTextModel::~DefaultTextModel()
{

}

void DefaultTextModel::setText( const String& text )
{
	if ( text == text_ ) {
		//do nothing  - there's no reason to change the text 
		//as it's equivalent! This also avoids unwanted recursions.
		return;
	}

	text_ = text;

	TextEvent event( this, TextModel::tmTextSet, text, 0, text.size() );

	TextModelChanged.fireEvent( &event );
}

void DefaultTextModel::empty()
{
	DefaultTextModel::setText( "" );

	AbstractModel::empty();
}

void DefaultTextModel::insertText( const uint32& index, const String& text )
{
	text_.insert( index, text );

	TextEvent event( this, TextModel::tmTextInserted, text, index, text.size() );

	TextModelChanged.fireEvent( &event );
}

void DefaultTextModel::replaceText( const uint32& index, const uint32& count, const String& text )
{
	VCF_ASSERT( count > 0 );
	VCF_ASSERT( (index+count) <= text_.size() );


	//remove old text
	String removedText = text_.substr( index, count );

	// this relies on STL to be smart enough to delete only
	// the count character that are part of the string
	text_.erase( index, count );

	//insert new text
	text_.insert( index, text );

	TextEvent event( this, TextModel::tmTextReplaced, removedText, text, 
							index, count );
	TextModelChanged.fireEvent( &event );
}

void DefaultTextModel::deleteText( const uint32& index, const uint32& count )
{
	String changeText = text_.substr( index, count );

	// this relies on STL to be smart enough to delete only
	// the count character that are part of the string
	text_.erase( index, count );

	TextEvent event( this, TextModel::tmTextRemoved, changeText, index, count );

	TextModelChanged.fireEvent( &event );
}


String DefaultTextModel::getText()
{
	return text_;
}

String DefaultTextModel::getText( const uint32& index, const uint32& count )
{
	return text_.substr( index, count );
}

uint32 DefaultTextModel::getSize()
{
	return text_.size();
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.7  2005/07/05 14:57:11  marcelloptr
*minor change on an assertion in ReplaceText so it can replace all text
*
*Revision 1.3.2.6  2005/06/02 15:43:27  marcelloptr
*more documentation
*
*Revision 1.3.2.4  2005/05/18 16:43:55  marcelloptr
*minor comment
*
*Revision 1.3.2.2  2005/05/18 03:19:17  ddiego
*more text edit changes, fixes some subtle bugs in doc and win32 edit peer.
*
*Revision 1.3.2.1  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/05 00:35:41  ddiego
*fixed the way the DefaulttextModel is implemented. Got rid of the need for teh AbsractTextModel class, we should delete it.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.12  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11.2.2  2004/03/26 18:37:59  marcelloptr
*very minor fixes
*
*Revision 1.11.2.1  2004/03/21 19:44:58  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.11  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.1  2003/09/08 05:23:21  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.10  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:13:10  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.2.2  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8.2.1  2002/12/27 23:05:01  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.8  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.7.10.1  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.2  2002/04/27 15:52:46  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


