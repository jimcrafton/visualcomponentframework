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

bool DefaultTextModel::isEmpty()
{
	return text_.empty();
}

void DefaultTextModel::doSetText( const String& text )
{
	if ( text == text_ ) {
		//do nothing  - there's no reason to change the text 
		//as it's equivalent! This also avoids unwanted recursions.
		return;
	}

	text_ = text;
}

void DefaultTextModel::empty()
{
	DefaultTextModel::setText( "" );

	Model::empty();
}

void DefaultTextModel::doInsertText( const uint32& index, const String& text )
{
	text_ = text_.insert( index, text );	
}

void DefaultTextModel::doReplaceText( const uint32& index, const uint32& count, const String& text )
{
	VCF_ASSERT( count > 0 );
	


	//remove old text

	//String removedText = text_.substr( index, count );

	// this relies on STL to be smart enough to delete only
	// the count character that are part of the string
	if ( !text_.empty() ) {
		text_ = text_.erase( index, count );
	}

	//insert new text
	text_ = text_.insert( index, text );	
}

void DefaultTextModel::doRemoveText( const uint32& index, const uint32& count )
{
	//String changeText = text_.substr( index, count );

	// this relies on STL to be smart enough to delete only
	// the count character that are part of the string
	text_ = text_.erase( index, count );	
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
