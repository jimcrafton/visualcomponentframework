#ifndef _TEXTEDITDOCUMENT_H__
#define _TEXTEDITDOCUMENT_H__
//TextEditDocument.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ModelViewKit.h"

#include "vcf/ApplicationKit/TextModel.h"

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"



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
	TextEditDocumentEvent( VCF::Object* source, const VCF::uint32& eventType ) 
		:VCF::ModelEvent(source,eventType),start_(0){

	};

	TextEditDocumentEvent( const TextEditDocumentEvent& rhs ):VCF::ModelEvent(rhs),start_(0) {
		*this = rhs;
	}

#ifndef _MSC_VER
	TextEditDocumentEvent& operator=( const TextEditDocumentEvent& rhs ) {
		VCF::ModelEvent::operator = (rhs);

		start_ = rhs.start_;
		text_ = rhs.text_;
		return *this;
	}
#endif

	virtual VCF::Object* clone( bool deep=false ) {
		return new TextEditDocumentEvent(*this);
	}
	VCF::uint32 start_;
	VCF::String text_;

};


/**
class TextEditDocument documentation
*/
class TextEditDocument : public VCF::Document, public VCF::TextModel {
public: 
	_class_rtti_( TextEditDocument, "VCF::Document", TEXTEDITDOCUMENT_CLASSID )
	_class_rtti_end_

	enum TextDocumentEvents {
		teTextAdded = VCF::Model::MODEL_CHANGED + 1000,
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
    virtual void insertText( const VCF::uint32& index, const VCF::String& text );

	/**
	*replace text into the model in place of the selected text is any,
	*or at the current position otherwise
	*@param String the text to replace with
	*/
    virtual void replaceText( const VCF::uint32& index, const VCF::uint32& len, const VCF::String& text );

	/**
	*deletes text from the model, starting at index, and continuing for count characters,
	*or until the text data is empty.
	*@param long the starting point. The index is zero based.
	*@param long the number of characters to delete
	*/
    virtual void deleteText( const VCF::uint32& index, const VCF::uint32& count );

	/**
	*returns all of the TextModel's text in a string.
	*/
	virtual VCF::String getText();

	virtual VCF::String getText( const VCF::uint32& index, const VCF::uint32& count );

	/**
	*returns the size of the TextModel
	*/
	virtual VCF::uint32 getSize() {
		return textData_.size();
	}




	bool find( FindInfo& findInfo );

	bool findAll( FindInfo& findInfo, std::vector<FoundEntry>& foundEntries );

	bool replace( ReplaceInfo& replaceInfo );

	bool replaceAll( ReplaceInfo& replaceInfo );	

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
	class ReplaceText;


	friend class AddText;
	friend class RemoveText;
	friend class ReplaceText;


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

	class ReplaceText : public VCF::AbstractCommand {
	public:
		ReplaceText(TextEditDocument* doc, VCF::ulong32 pos,
					VCF::ulong32 length, const VCF::String& originalText,
					const VCF::String& text );

		virtual void undo();

		virtual void redo();

		virtual void execute();
		
		TextEditDocument* doc_;
		VCF::ulong32 pos_;
		VCF::ulong32 length_;
		VCF::String text_;
		VCF::String originalText_;
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

	void internal_replaceText( const VCF::ulong32& pos, const VCF::ulong32& length, const VCF::String& text );

	void internal_removeText( const VCF::ulong32& pos, const VCF::ulong32& length );
};



/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:47  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/07/23 21:45:43  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.2.2.4  2005/05/18 03:19:17  ddiego
*more text edit changes, fixes some subtle bugs in doc and win32 edit peer.
*
*Revision 1.2.2.3  2005/05/04 20:47:20  marcelloptr
*standard file formatting and cvs log section added
*
*/


#endif //_TEXTEDITDOCUMENT_H__



