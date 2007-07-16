#ifndef _VCF_DEFAULTTEXTMODEL_H__
#define _VCF_DEFAULTTEXTMODEL_H__
//DefaultTextModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_ABSTRACTMODEL_H__
#	include "vcf/ApplicationKit/AbstractModel.h"
#endif // _VCF_ABSTRACTMODEL_H__



#ifndef _VCF_TEXTMODEL_H__
#	include "vcf/ApplicationKit/TextModel.h"
#endif // _VCF_TEXTMODEL_H__

#ifndef _VCF_TEXTEVENT_H__
#	include "vcf/ApplicationKit/TextEvent.h"
#endif // _VCF_TEXTEVENT_H__



namespace VCF{

#define DEFAULTTEXTMODEL_CLASSID		"8B2CDC32-3CAD-11d4-B553-00C04F0196DA"
/**
\class DefaultTextModel DefaultTextModel.h "vcf/ApplicationKit/DefaultTextModel.h"
*/
class APPLICATIONKIT_API DefaultTextModel : public AbstractModel, public TextModel {
public:


    DefaultTextModel();

	virtual ~DefaultTextModel();

	/**
	@delegate TextModelChanged fired when the model's text data is changed
	@event TextModelEvent
	*/
	DELEGATE(TextModelDelegate,TextModelChanged)

	virtual void addTextModelChangedHandler( EventHandler * handler ){
		TextModelChanged += handler;
	}

	virtual void removeTextModelChangedHandler( EventHandler * handler ) {
		TextModelChanged.remove(handler);
	}

    virtual void empty();

	virtual void setText( const String& text );

    virtual void insertText( const uint32& index, const String& text );
	
    virtual void replaceText( const uint32& index, const uint32& len, const String& text );

    virtual void deleteText( const uint32& index, const uint32& count );

	virtual String getText();

	virtual String getText( const uint32& index, const uint32& count );

	virtual uint32 getSize();

protected:
	String text_;
};

};


#endif // _VCF_DEFAULTTEXTMODEL_H__

/**
$Id$
*/
