//BasicTableItemEditor.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/BasicTableItemEditor.h"


using namespace VCF;

BasicTableItemEditor::BasicTableItemEditor( TableCellItem* editingItem ):
	editingItem_(editingItem),
		editingControl_(NULL)
{
	editingItem_ = editingItem;
}

BasicTableItemEditor::~BasicTableItemEditor()
{
	
}


void BasicTableItemEditor::updateItem()
{
	VCF_ASSERT( NULL != editingControl_ );
	VCF_ASSERT( NULL != editingItem_ );
	
	TextControl* editingControl = dynamic_cast<TextControl*>( editingControl_ );
	if ( NULL != editingControl ){
		TextModel* tm = editingControl->getTextModel();

		String captionOfItem = tm->getText();

		void* itemCaptionPtr = (void*)&captionOfItem;
		ItemEditorEvent event( this, itemCaptionPtr );
		event.setItemBeingEdited( editingItem_ );

		try {
			CellItemValidateChange.fireEvent( &event );

			event.setType( ITEMEDITOR_CHANGED );
			//if we got this far we are OK to send off a change notification !

			editingItem_->setCaption( captionOfItem );
			CellItemChanged.fireEvent( &event );
		}
		catch ( InvalidStateException& ){

		}
		catch (...){
			throw;//pass it on to someone else !!
		}
	}	
}

Control* BasicTableItemEditor::getEditingControl()
{
	if ( NULL == editingControl_ ){
		TextControl* tc = new TextControl();
		tc->setBorder( NULL );
		TextModel* tm = tc->getTextModel();
		tm->setText( editingItem_->getCaption() );
		EventHandler* ev = getEventHandler("BasicTableItemEditor::onEditorTextChanged");
		if ( NULL == ev ) {
			ev = new TextModelEventHandler<BasicTableItemEditor>( this, &BasicTableItemEditor::onEditorTextChanged,"BasicTableItemEditor::onEditorTextChanged" );
		}

		tc->setSelectionMark( 0, editingItem_->getCaption().size() );

		tm->addTextModelChangedHandler( ev );

		editingControl_ = tc;
	}

	VCF_ASSERT( NULL != editingControl_ );

	return editingControl_;
}

void BasicTableItemEditor::onEditorTextChanged( TextEvent* event )
{
	String editorText = event->getTextModel()->getText();

}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2005/01/26 20:59:28  ddiego
*some fixes to table control and to teh table item editor interface
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.18  2004/04/03 16:09:31  ddiego
*Found some more merge issues that needing resolving.
*
*Revision 1.17  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.16.6.1  2004/03/18 04:19:26  ddiego
*some minor stuff for tables
*
*Revision 1.16  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15.2.1  2003/03/12 03:12:59  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.8.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.14.8.2  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14.8.1  2002/12/25 22:06:34  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.14  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.13.6.1  2002/08/31 05:44:52  ddiego
**** empty log message ***
*
*Revision 1.13  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12  2002/03/19 01:39:56  ddiego
*minor changes to ComboBoxControl to fix tabbing error with arrow keys
*fixes bug 531678 Bad behaviour of arrow keys in Combobox
*
*Revision 1.11.4.3  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.11.4.2  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.11.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.11  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


