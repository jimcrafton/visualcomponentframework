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
	VCF::uint32 position_;
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

	VCF::uint32 position_;
	VCF::uint32 line_;
	VCF::uint32 column_;
	VCF::Document* document_;
	VCF::String fileName_;	
};







/**
class TextEditDocument documentation
*/
class TextEditDocument : public VCF::Document {
public: 
	_class_rtti_( TextEditDocument, "VCF::Document", TEXTEDITDOCUMENT_CLASSID )
	_class_rtti_end_

	

	TextEditDocument();
	virtual ~TextEditDocument();

	virtual void initNew();

	virtual void empty();

	virtual bool canCutFromDocument();

	virtual bool canCopyFromDocument();

	virtual bool canPasteToDocument() {
		return false;
	}

	virtual bool saveAsType( const VCF::String& fileName, const VCF::String& fileType );

	virtual bool saveAsType( const VCF::String& fileType, VCF::OutputStream& stream );

	virtual bool openFromType( const VCF::String& fileType, VCF::InputStream& stream );

	virtual VCF::DataObject* cut();

	virtual VCF::DataObject* copy();

	virtual bool paste( VCF::DataObject* data );






	bool find( FindInfo& findInfo );

	bool findAll( FindInfo& findInfo, std::vector<FoundEntry>& foundEntries );

	bool replace( ReplaceInfo& replaceInfo );

	bool replaceAll( ReplaceInfo& replaceInfo );	

	

protected:
	class AddText;
	class RemoveText;
	class ReplaceText;


	friend class AddText;
	friend class RemoveText;
	friend class ReplaceText;


	class AddText : public VCF::AbstractCommand {
	public:
		AddText(TextEditDocument* doc, VCF::uint32 pos, 
					const VCF::String& text );

		virtual void undo();

		virtual void redo();

		virtual void execute();
		
		TextEditDocument* doc_;
		VCF::uint32 pos_;
		VCF::String text_;
		VCF::uint32 selStart_;
		VCF::uint32 selLength_;
	};

	class ReplaceText : public VCF::AbstractCommand {
	public:
		ReplaceText(TextEditDocument* doc, VCF::uint32 pos,
					VCF::uint32 length, const VCF::String& originalText,
					const VCF::String& text );

		virtual void undo();

		virtual void redo();

		virtual void execute();
		
		TextEditDocument* doc_;
		VCF::uint32 pos_;
		VCF::uint32 length_;
		VCF::String text_;
		VCF::String originalText_;
		VCF::uint32 selStart_;
		VCF::uint32 selLength_;
	};

	class RemoveText : public VCF::AbstractCommand {
	public:
		RemoveText( TextEditDocument* doc, VCF::uint32 pos, const VCF::String& text ) ;

		virtual void undo();

		virtual void redo();

		virtual void execute();

		TextEditDocument* doc_;
		VCF::uint32 pos_;
		VCF::String text_;
	};

	



	long selectionStart_;
	VCF::uint32 selectionLength_;

	void internal_insertText( const VCF::uint32& pos, const VCF::String& text );

	void internal_replaceText( const VCF::uint32& pos, const VCF::uint32& length, const VCF::String& text );

	void internal_removeText( const VCF::uint32& pos, const VCF::uint32& length );
};



#endif //_TEXTEDITDOCUMENT_H__

/**
$Id$
*/
