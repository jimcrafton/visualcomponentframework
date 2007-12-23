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

	ModelChanged( &event );
}

void DefaultTextModel::empty()
{
	DefaultTextModel::setText( "" );

	Model::empty();
}

void DefaultTextModel::insertText( const uint32& index, const String& text )
{
	text_.insert( index, text );

	TextEvent event( this, TextModel::tmTextInserted, text, index, text.size() );

	ModelChanged( &event );
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
	ModelChanged( &event );
}

void DefaultTextModel::deleteText( const uint32& index, const uint32& count )
{
	String changeText = text_.substr( index, count );

	// this relies on STL to be smart enough to delete only
	// the count character that are part of the string
	text_.erase( index, count );

	TextEvent event( this, TextModel::tmTextRemoved, changeText, index, count );

	ModelChanged( &event );
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
$Id$
*/
