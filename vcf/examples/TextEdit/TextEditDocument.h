
#ifndef _TEXTEDITDOCUMENT_H__
#define _TEXTEDITDOCUMENT_H__

#include "vcf/ApplicationKit/ModelViewKit.h"

#include "vcf/ApplicationKit/TextModel.h"


#define TEXTEDITDOCUMENT_CLASSID		"e0d4c047-60f1-4397-b3af-9e467057b7c4"





class  FindInfo {
public:
	FindInfo() : atEnd_(false), position_(0),
				caseSensitive_(false), 
				matchWordOnly_(false),
				searchAllOpenDocs_(false)
				{
		
	}


	bool atEnd_;
	VCF::ulong32 position_;
	bool caseSensitive_;
	bool matchWordOnly_;
	bool searchAllOpenDocs_;
	VCF::String searchString_;
	std::vector<VCF::String> searchStrings_;
};


class  ReplaceInfo : public FindInfo {
public:
	ReplaceInfo() {
		
	}
	
	VCF::String replaceString_;
	std::vector<VCF::String> replaceStrings_;
};

class  FoundEntry {
public:
	FoundEntry() : position_(0), line_(0), column_(0),document_(NULL){

	}

	VCF::ulong32 position_;
	VCF::ulong32 line_;
	VCF::ulong32 column_;
	VCF::Document* document_;
	VCF::String fileName_;	
};







class TextEditDocumentEvent : public VCF::ModelEvent {
public:
	TextEditDocumentEvent( VCF::Object* source, const unsigned long& eventType ) 
		:VCF::ModelEvent(source,eventType),start_(0){

	};

	TextEditDocumentEvent( const TextEditDocumentEvent& rhs ):VCF::ModelEvent(rhs),start_(0) {
		*this = rhs;
	}

	TextEditDocumentEvent& operator=( const TextEditDocumentEvent& rhs ) {
		ModelEvent::operator = (rhs);

		start_ = rhs.start_;
		text_ = rhs.text_;
		return *this;
	}

	virtual VCF::Object* clone( bool deep=false ) {
		return new TextEditDocumentEvent(*this);
	}
	unsigned long start_;
	VCF::String text_;

};


/**
class TextEditDocument documentation
*/
class TextEditDocument : public VCF::Document, public VCF::TextModel {
public: 
	BEGIN_CLASSINFO( TextEditDocument, "TextEditDocument", "VCF::Document", TEXTEDITDOCUMENT_CLASSID )
	END_CLASSINFO(TextEditDocument)

	enum TextDocumentEvents {
		teTextAdded = Model::MODEL_CHANGED + 1000,
		teTextRemoved,
		teTextSelectionChanged
	};

	TextEditDocument();
	virtual ~TextEditDocument();

	virtual void initNew();

	virtual void empty();

	virtual bool canCutFromDocument();

	virtual bool canCopyFromDocument();

	virtual bool canPasteToDocument();

	virtual bool saveAsType( const VCF::String& fileName, const VCF::String& fileType );

	virtual bool saveAsType( const VCF::String& fileType, VCF::OutputStream& stream );

	virtual bool openFromType( const VCF::String& fileType, VCF::InputStream& stream );

	virtual VCF::DataObject* cut();

	virtual VCF::DataObject* copy();

	virtual bool paste( VCF::DataObject* data );


	/**
	TextModel methods
	*/

	/**
	@delegate TextModelChanged fired when the model's text data is changed
	@event TextModelEvent
	*/
	DELEGATE(TextModelChanged)

		virtual void addTextModelChangedHandler( VCF::EventHandler * handler ){
		TextModelChanged += handler;
	}

	virtual void removeTextModelChangedHandler( VCF::EventHandler * handler ) {
		TextModelChanged -= handler;
	}

	/**
	*sets the contents of the text model, completely changes what was previously
	*in the model
	*/
    virtual void setText( const VCF::String& text );

	/**
	*inserts text into the model at the given index
	*@param long the starting point to begin inserting the text. This number represents
	*a zero based index.
	*@param String the text to insert
	*/
    virtual void insertText( const unsigned long& index, const VCF::String& text );

	/**
	*replace text into the model in place of the selected text is any,
	*or at the current position otherwise
	*@param String the text to replace with
	*/
    virtual void replaceText( const unsigned long& index, const unsigned long& len, const VCF::String& text );

	/**
	*deletes text from the model, starting at index, and continuing for count characters,
	*or until the text data is empty.
	*@param long the starting point. The index is zero based.
	*@param long the number of characters to delete
	*/
    virtual void deleteText( const unsigned long& index, const unsigned long& count );

	/**
	*adds text to end of the current text data
	*/
    virtual void appendText( const VCF::String& text );

	/**
	*returns all of the TextModel's text in a string.
	*/
	virtual VCF::String getText();

	/**
	*returns the size of the TextModel
	*/
	virtual unsigned long getSize() {
		return textData_.size();
	}




	bool find( FindInfo& findInfo );

	bool findAll( FindInfo& findInfo, std::vector<FoundEntry>& foundEntries );

	bool replace( ReplaceInfo& replaceInfo );

	bool replaceAll( ReplaceInfo& replaceInfo );

	VCF::String getText( const VCF::ulong32 pos, const VCF::ulong32 length  );	

	/**
	sets the selection range 
	@param pos - if pos is -1 then everything is selected
	@param ulong32 length of the selection
	*/
	void setSelectionRange( const long pos, const VCF::ulong32 length  );

	long getSelectionStart() {
		return selectionStart_;
	}

	VCF::ulong32 getSelectionLength() {
		return selectionLength_;
	}

	/**
	returns a string that represents the selection starting 
	at the selection start and with a matching length as the 
	selection has. It is possible for this to return an empty
	string if the selection length is 0.
	@see getSelectionStart
	@see getSelectionLength
	*/
	VCF::String getSelection();

	/**
	sets the selection text. The insertion point is the current 
	selection start position. Similar to calling insertText. The
	inserted text is the length of the selectionText param.
	@see insertText
	@see getSelectionStart
	*/
	void setSelection( const VCF::String& selectionText );

	

protected:
	class AddText;
	class RemoveText;


	friend class AddText;
	friend class RemoveText;


	class AddText : public VCF::AbstractCommand {
	public:
		AddText(TextEditDocument* doc, VCF::ulong32 pos, 
					const VCF::String& text );

		virtual void undo();

		virtual void redo();

		virtual void execute();
		
		TextEditDocument* doc_;
		VCF::ulong32 pos_;
		VCF::String text_;
		VCF::ulong32 selStart_;
		VCF::ulong32 selLength_;
	};

	class RemoveText : public VCF::AbstractCommand {
	public:
		RemoveText( TextEditDocument* doc, VCF::ulong32 pos, const VCF::String& text ) ;

		virtual void undo();

		virtual void redo();

		virtual void execute();

		TextEditDocument* doc_;
		VCF::ulong32 pos_;
		VCF::String text_;
	};

	



	VCF::String textData_;

	long selectionStart_;
	VCF::ulong32 selectionLength_;

	void internal_insertText( const VCF::ulong32& pos, const VCF::String& text );

	void internal_removeText( const VCF::ulong32& pos, const VCF::ulong32& length );
};



#endif //_TEXTEDITDOCUMENT_H__



