#ifndef _VCF_TEXTMODEL_H__
#define _VCF_TEXTMODEL_H__
//TextModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF  {


class TextModel;
	

/**
\class TextEvent TextModel.h "vcf/ApplicationKit/TextModel.h"
*/
class APPLICATIONKIT_API TextEvent : public ModelEvent {
public:
	TextEvent( Object * source):
		ModelEvent( source,0 ),
		selectionStart(-1),
		selectionLength(0),
		changeStart(0),
		changeLength(0) {}



	TextEvent( Object * source, const String& changedText ) :
		ModelEvent( source,0 ),
		changeText(changedText),
		selectionStart(-1),
		selectionLength(0),
		changeStart(0),
		changeLength(0) {}


	TextEvent( Object * source, int selectionStart, uint32 selectionLength ):
		ModelEvent(source,0),
		selectionStart(selectionStart),
		selectionLength(selectionLength),
		changeStart(0),
		changeLength(0){}

	TextEvent( Object * source, uint32 type, const String& changedText, uint32 changeStart, uint32 changeLength ):
		ModelEvent(source, type),
		selectionStart(-1),
		selectionLength(0),
		changeStart(changeStart),
		changeLength(changeLength){

		changeText = changedText;
	}

	TextEvent( Object * source, uint32 type, const String& replacedText, 
				const String& changedText, uint32 replaceStart, uint32 replaceLength ):
		ModelEvent(source, type),
		changeText(changedText),
		originalText(replacedText),
		selectionStart(-1),
		selectionLength(0),
		changeStart(replaceStart),
		changeLength(replaceLength){}

		

	TextEvent( const TextEvent& rhs ):ModelEvent(rhs),
		selectionStart(-1),selectionLength(0),
		changeStart(0),
		changeLength(0){
		*this = rhs;
	}

	virtual ~TextEvent() {}

	TextEvent& operator= ( const TextEvent& rhs ) {
		ModelEvent::operator =( rhs );

		changeText = rhs.changeText;
		originalText = rhs.originalText;
		selectionStart = rhs.selectionStart;
		selectionLength = rhs.selectionLength;

		changeStart = rhs.changeStart;
		changeLength = rhs.changeLength;

		return *this;
	}

    

	/**
	*returns the text model associated with this event. May
	*return null if the source of the event was not a TextModel
	*/
	TextModel* getTextModel() {
		return (TextModel*)(this->getSource() );
	}

	virtual Object* clone( bool deep=false ) {
		return new TextEvent(*this);
	}

	String changeText;
	String originalText;

	/**
	The current position of the selection. A return 
	value of -1 indicates no current selection. In this case
	the getSelectionLength() will also return 0.
	*/
	int selectionStart;

	/**
	The number of characters in the selection
	*/
	uint32 selectionLength;

	/**
	The length of the change
	*/
	uint32 changeStart;

	/**
	The start of the change
	*/
	uint32 changeLength;
};





/**
TextModelEventHandler
handles the following:
\li onTextChanged
*/
typedef Delegate1<TextEvent*> TextModelDelegate; 
typedef TextModelDelegate::ProcedureType TextModelHandler;



#define TEXTMODEL_CLASSID		"412c8a0e-4dda-4270-afc0-54d2eada1b2d"


/**
\class TextModel TextModel.h "vcf/ApplicationKit/TextModel.h"
The TextModel is a model interface for working with text data.
It does not \emnot inherit from the Model class
directly. This is to allow different implementations different base classes.
For example, you might have a simple list model that inherits/implements the 
Model class, and the ListModel class. This would be suitable for most controls.
However you might want a fancier implementation, perhaps that is based 
off of the Document and ListModel classes. This would still allow you to 
use the same control with either style.

*@version 1.0
*@author Jim Crafton
*/
	class APPLICATIONKIT_API TextModel : public Model {
public:

	enum TextModelEvents {
		tmTextInserted = VCF::Model::MODEL_CHANGED + 3210,
		tmTextReplaced,
		tmTextSet,
		tmTextRemoved,
		tmTextSelectionChanged
	};	

	TextModel(){

	};

	virtual ~TextModel(){};

	/**
	*sets the contents of the text model, completely changes what was previously
	*in the model
	*/
	virtual void setText( const String& text ) = 0;

	/**
	*inserts text into the model at the given index
	*@param uint32 the starting point to begin inserting the text. This number represents
	*a zero based index.
	*@param String the text to insert
	*/
	virtual void insertText( const uint32& index, const String& text ) = 0;

	/**
	*replace text into the model in place of the selected text is any,
	*or at the current position otherwise
	*@param String the text to replace with
	*/
	virtual void replaceText( const uint32& index, const uint32& count, const String& text ) = 0;

	/**
	*deletes text from the model, starting at index, and continuing for count characters,
	*or until the text data is empty.
	*@param uint32 the starting point. The index is zero based.
	*@param uint32 the number of characters to delete
	*/
	virtual void deleteText( const uint32& index, const uint32& count ) = 0;
	
	/**
	*returns all of the TextModel's text in a string.
	*/
	virtual String getText() = 0;

	/**
	*returns a sub string of the TextModel's text in a string.
	*/
	virtual String getText( const uint32& index, const uint32& count ) = 0;

	/**
	*returns the size of the TextModel. That is the number of charecters in 
	text string that this model represents.
	*/
	virtual uint32 getSize() = 0;



	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		return getText();
	}

	virtual String getValueAsString( const VariantData& key=VariantData::null() ) {
		return getText();
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() ) { 
		setText( value );
	}

	virtual void setValueAsString( const String& value, const VariantData& key=VariantData::null() ) {
		setText( value );
	}
};



};


#endif // _VCF_TEXTMODEL_H__

/**
$Id$
*/
