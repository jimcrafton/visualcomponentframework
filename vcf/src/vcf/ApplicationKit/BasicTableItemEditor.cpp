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
			CellItemValidateChange( &event );

			event.setType( ITEMEDITOR_CHANGED );
			//if we got this far we are OK to send off a change notification !

			editingItem_->setCaption( captionOfItem );
			CellItemChanged( &event );
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
		CallBack* ev = getEventHandler("BasicTableItemEditor::onEditorTextChanged");
		if ( NULL == ev ) {
			ev = new ClassProcedure1<TextEvent*,BasicTableItemEditor>( this, &BasicTableItemEditor::onEditorTextChanged,"BasicTableItemEditor::onEditorTextChanged" );
		}

		tc->setSelectionMark( 0, editingItem_->getCaption().size() );

		tm->addTextModelChangedHandler( (EventHandler*)ev );

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
$Id$
*/
