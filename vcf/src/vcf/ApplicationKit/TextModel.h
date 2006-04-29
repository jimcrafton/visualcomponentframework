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



namespace VCF{


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
class APPLICATIONKIT_API TextModel  {
public:

	enum TextModelEvents {
		tmTextInserted = VCF::Model::MODEL_CHANGED + 3210,
		tmTextReplaced,
		tmTextSet,
		tmTextRemoved
	};


	TextModel(){

	};

	virtual ~TextModel(){};

	/**
	*adds a new TextModelEvent handler
	*/
	virtual void addTextModelChangedHandler( EventHandler * handler ) = 0;

	/**
	*removes a TextModelEvent handler
	*/
	virtual void removeTextModelChangedHandler( EventHandler * handler ) = 0;

	/**
	*sets the contents of the text model, completely changes what was previously
	*in the model
	*/
	virtual void setText( const String& text ) = 0;

	/**
	*inserts text into the model at the given index
	*@param long the starting point to begin inserting the text. This number represents
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
	*@param long the starting point. The index is zero based.
	*@param long the number of characters to delete
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

};



};


#endif // _VCF_TEXTMODEL_H__

/**
$Id$
*/
