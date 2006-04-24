//TextEditDocument.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "TextEditDocument.h"

using namespace VCF;






TextEditDocument::AddText::AddText( TextEditDocument* doc, 
												VCF::ulong32 pos, 
												const VCF::String& text ):
			doc_(doc), pos_(pos), text_(text) 
{
	isUndoable_ = true;
	commandName_ = "Added Text";
}

void TextEditDocument::AddText::undo()
{
	doc_->internal_removeText( pos_, text_.size() );
	doc_->setSelectionRange( pos_ , 0 );
}

void TextEditDocument::AddText::redo()
{
	doc_->internal_insertText( pos_, text_ );
	doc_->setSelectionRange( pos_ + text_.size(), 0 );	
}

void TextEditDocument::AddText::execute()
{
	doc_->internal_insertText( pos_, text_ );
}




TextEditDocument::ReplaceText::ReplaceText( TextEditDocument* doc, 
												VCF::ulong32 pos, 
												VCF::ulong32 length,
												const VCF::String& originalText, 
												const VCF::String& text ):
			doc_(doc), pos_(pos), length_(length), text_(text), originalText_(originalText)
{
	isUndoable_ = true;
	commandName_ = "Replaced Text";
}

void TextEditDocument::ReplaceText::undo()
{
	doc_->internal_replaceText( pos_, text_.size(), originalText_ );

	doc_->setSelectionRange( pos_ , 0 );
}

void TextEditDocument::ReplaceText::redo()
{
	doc_->internal_replaceText( pos_, length_, text_ );
	
	doc_->setSelectionRange( pos_ + text_.size(), 0 );	
}

void TextEditDocument::ReplaceText::execute()
{
	doc_->internal_replaceText( pos_, length_, text_ );
}


TextEditDocument::RemoveText::RemoveText( TextEditDocument* doc, 
												VCF::ulong32 pos, 
												const VCF::String& text ):
	doc_(doc), pos_(pos), text_(text) 
{
	isUndoable_ = true;
	commandName_ = "Deleted Text";
}

void TextEditDocument::RemoveText::undo()
{
	doc_->internal_insertText( pos_, text_ );
	doc_->setSelectionRange( pos_ + text_.size(), 0 );
}

void TextEditDocument::RemoveText::redo()
{
	doc_->internal_removeText( pos_, text_.size() );
	doc_->setSelectionRange( pos_ , 0 );
}

void TextEditDocument::RemoveText::execute()
{
	doc_->internal_removeText( pos_, text_.size() );
}






VCF::ulong32 findString( const FindInfo& findInfo, const String& inText )
{
	int start = findInfo.position_ == 0 ? 0 : findInfo.position_ + 1;

	int result = String::npos;

	
	if ( findInfo.caseSensitive_ ) {
		result = inText.find( findInfo.searchString_, start );
	}
	else {
		/**
		This is HORRIBLY inefficient, but it will have to suffice for now
		*/
		String tmpText = StringUtils::lowerCase( inText );
		String tmpFind = StringUtils::lowerCase( findInfo.searchString_ );

		result = tmpText.find( tmpFind, start );
	}

	if ( result != String::npos ) {
		if ( findInfo.matchWordOnly_ ) {
			int prevChar = 0;
			if ( result > 0 ) {
				prevChar = inText[result-1];
			}

			int lastChar = 0;
			if ( result+1+findInfo.searchString_.size() < inText.size() ) {
				lastChar = inText[result+1+findInfo.searchString_.size()];
			}

			bool wordMatch = false;

			if ( (prevChar != 0) && ( (prevChar == ' ') || (prevChar == '.') || (prevChar == '(')
				|| (prevChar == ')') ) ) {
				wordMatch = true;
			}

			if ( wordMatch ) {
				if ( lastChar != 0 ) {
					if ( (prevChar == ' ') || (prevChar == '.') || (prevChar == '(')
							|| (prevChar == ')') ) {
						wordMatch = true;
					}
					else {
						wordMatch = false;
					}
				}
			}


			if ( !wordMatch ) {
				result = String::npos;
			}
		}
	}

	return result;
}








TextEditDocument::TextEditDocument():
	Document(),
	selectionStart_(0),
	selectionLength_(0)
{
	addSupportedClipboardFormat( STRING_DATA_TYPE );
}

TextEditDocument::~TextEditDocument()
{

}

void TextEditDocument::initNew()
{
	textData_ = "";
	selectionStart_ = 0;
	selectionLength_ = 0;
}




void TextEditDocument::empty()
{
	textData_ = "";

	selectionStart_ = 0;
	selectionLength_ = 0;
	

	Document::empty();
}

bool TextEditDocument::canCutFromDocument()
{
	return (selectionLength_ != 0) ? true : false;
}

bool TextEditDocument::canCopyFromDocument()
{
	return (selectionLength_ != 0) ? true : false;
}

bool TextEditDocument::canPasteToDocument()
{
	Clipboard* clipboard = UIToolkit::getSystemClipboard();
	return clipboard->hasDataType( STRING_DATA_TYPE );
}

bool TextEditDocument::saveAsType( const VCF::String& fileName, const VCF::String& fileType )
{
	long oldSelStart = selectionStart_;
	selectionStart_ = -1;

	bool result = Document::saveAsType( fileName, fileType );

	selectionStart_ = oldSelStart;

	return result;
}

bool TextEditDocument::saveAsType( const VCF::String& fileType, VCF::OutputStream& stream )
{
	AnsiString tmp = textData_;
	stream.write( (unsigned char*)tmp.c_str(), tmp.size() );
	return true;
}

bool TextEditDocument::openFromType( const VCF::String& fileType, VCF::InputStream& stream )
{
	//textData_ = "";
	
	empty();

	String text;

	stream.read( text );

	setText( text );

	return true;
}



bool TextEditDocument::find( FindInfo& findInfo )
{
	int start = findInfo.position_ == 0 ? 0 : findInfo.position_ + 1;

	VCF::ulong32 pos = findString( findInfo, textData_ );
	
	findInfo.position_ = pos;

	if ( String::npos == findInfo.position_ ) {
		if ( start <= (textData_.size() - findInfo.searchString_.size()) ) {
			findInfo.atEnd_ = true;
		}
	}
	else {
		findInfo.atEnd_ = false;
	}
	return String::npos != findInfo.position_;
}

bool TextEditDocument::findAll( FindInfo& findInfo, std::vector<FoundEntry>& foundEntries )
{
	int start = 0;
	start = textData_.find( findInfo.searchString_, start );
	while ( start != String::npos ) {
		FoundEntry entry;
		entry.document_ = this;
		entry.position_ = start;

		foundEntries.push_back(entry);
		start = textData_.find( findInfo.searchString_, start+1 );
	}

	return !foundEntries.empty();
}

bool TextEditDocument::replace( ReplaceInfo& replaceInfo )
{
	if ( replaceInfo.position_ > textData_.size() ) {
		return false;
	}

	deleteText( replaceInfo.position_, replaceInfo.searchString_.size() );

	insertText( replaceInfo.position_, replaceInfo.replaceString_ );

	return true;
}

bool TextEditDocument::replaceAll( ReplaceInfo& replaceInfo )
{
	bool result = false;
	int start = 0;
	start = textData_.find( replaceInfo.searchString_, start );
	while ( start != String::npos ) {
		deleteText( start, replaceInfo.searchString_.size() );

		insertText( start, replaceInfo.replaceString_ );
		
		start = textData_.find( replaceInfo.searchString_, start+replaceInfo.replaceString_.size() );
		result = true;
	}

	return result;
}

VCF::String TextEditDocument::getText( const VCF::uint32& pos, const VCF::uint32& length  )
{	
	return textData_.substr( pos, length );
}

VCF::String TextEditDocument::getText()
{
	
	return textData_;
}

void TextEditDocument::setText(const VCF::String& text)
{

	CommandGroup* setTextGrp = new CommandGroup();
	setTextGrp->setName( "Change Text" );

	setTextGrp->addCommand( new RemoveText( this, 0, textData_ ) );
	setTextGrp->addCommand( new AddText( this, 0, text ) );

	DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( setTextGrp );
}

void TextEditDocument::insertText( const VCF::uint32& index, const VCF::String& text )
{
	
	DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new AddText( this, index, text ) );
}

void TextEditDocument::deleteText( const VCF::uint32& pos, const VCF::uint32& length )
{
	
	String text = textData_.substr( pos, length );

	DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new RemoveText( this, pos, text ) );
}


void TextEditDocument::replaceText( const uint32& index, const uint32& length, const String& text )
{
	String originalText = textData_.substr( index, length );

	DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new ReplaceText( this, index, length, originalText, text ) );
}

void TextEditDocument::setSelectionRange( const long pos, const VCF::ulong32 length  )
{	
	
	selectionStart_ = pos;
	selectionLength_ = length;

	
	ModelEvent e( this, TextEditDocument::teTextSelectionChanged );
	ModelChanged.fireEvent( &e );


	TextModelChanged.fireEvent( &e );

	updateAllViews();
}

VCF::String TextEditDocument::getSelection()
{
	String result = textData_.substr( selectionStart_, selectionLength_ );

	return result;
}

void TextEditDocument::setSelection( const VCF::String& selectionText )
{
	insertText( selectionStart_, selectionText );
}

DataObject* TextEditDocument::cut()
{
	DataObject* result = copy();

	if ( -1 == selectionStart_ ) {
		empty();
	}
	else {
		deleteText( selectionStart_, this->selectionLength_ );		
	}	

	setSelectionRange( selectionStart_, 0 );

	return result;
}

DataObject* TextEditDocument::copy()
{
	DataObject* result = NULL;	

	String text;
	if ( -1 == selectionStart_ ) {
		text = textData_;
	}
	else {
		text = textData_.substr( selectionStart_, selectionLength_ );
	}	

	result = new TextDataObject(text);	

	return result;
}

bool TextEditDocument::paste( DataObject* data )
{
	BasicOutputStream bos;
	
	bool result = data->saveToStream( STRING_DATA_TYPE, &bos );

	if ( !result ) {
		return result;
	}
	
	BasicInputStream bis( bos.getBuffer(), bos.getSize() );
	
	String text;
	bis >> text;

	if ( -1 == selectionStart_ ) {
		setText( text );
		//textData_ = text;
	}
	else {
		if ( selectionLength_ > 0 ) {
			replaceText( selectionStart_, selectionLength_, text );
		}
		else {
			insertText( selectionStart_, text ); 
		}
		
		setSelectionRange( selectionStart_ + text.size(), 0 );
	}

	return true;
}

void TextEditDocument::internal_insertText( const VCF::ulong32& pos, const VCF::String& text )
{
	textData_.insert( pos, text );

	setModified( true );
	

	TextEditDocumentEvent e( this, TextEditDocument::teTextAdded );
	e.text_ = text;
	e.start_ = pos;
	
	ModelChanged.fireEvent( &e );

	TextEvent event( this, TextModel::tmTextInserted, text, pos, text.size() );

	TextModelChanged.fireEvent( &event );

	updateAllViews();
}

void TextEditDocument::internal_removeText( const VCF::ulong32& pos, const VCF::ulong32& length )
{
	TextEditDocumentEvent e( this, TextEditDocument::teTextRemoved );

	e.text_ = textData_.substr( pos, length );
	e.start_ = pos;

	textData_.erase( pos, length );

	setModified( true );
	
	ModelChanged.fireEvent( &e );

	TextEvent event( this, TextModel::tmTextRemoved, e.text_, pos, length );

	TextModelChanged.fireEvent( &event );

	updateAllViews();
}

void TextEditDocument::internal_replaceText( const VCF::ulong32& pos, const VCF::ulong32& length, const VCF::String& text )
{
	TextEditDocumentEvent e( this, TextEditDocument::teTextAdded );

	e.text_ = textData_.substr( pos, length );
	e.start_ = pos;	

	//remove old text
	String removedText = textData_.substr( pos, length );

	textData_.erase( pos, length );
	//insert new text
	textData_.insert( pos, text );
	

	setModified( true );
	
	ModelChanged.fireEvent( &e );


	TextEvent event( this, TextModel::tmTextReplaced, removedText, text, 
							pos, length );
	TextModelChanged.fireEvent( &event );
}

/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:47  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2005/09/23 05:30:34  kdmix
*The first parameter of the OutputStream.write() method is const unsigned char* now.
*
*Revision 1.3.2.1  2005/07/23 21:45:43  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.2.2.5  2005/06/02 16:28:23  marcelloptr
*removed obsolete code
*
*Revision 1.2.2.4  2005/05/19 02:19:09  ddiego
*more win32 edit fixes.
*
*Revision 1.2.2.3  2005/05/18 03:19:17  ddiego
*more text edit changes, fixes some subtle bugs in doc and win32 edit peer.
*
*Revision 1.2.2.2  2005/05/15 23:17:36  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2.2.1  2005/05/04 20:47:20  marcelloptr
*standard file formatting and cvs log section added
*
*/



