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



#ifndef _VCF_TEXTMODEL_H__
#	include "vcf/ApplicationKit/TextModel.h"
#endif // _VCF_TEXTMODEL_H__



namespace VCF{

#define DEFAULTTEXTMODEL_CLASSID		"8B2CDC32-3CAD-11d4-B553-00C04F0196DA"
/**
\class DefaultTextModel DefaultTextModel.h "vcf/ApplicationKit/DefaultTextModel.h"
*/
class APPLICATIONKIT_API DefaultTextModel : public TextModel {
public:


    DefaultTextModel();

	virtual ~DefaultTextModel();


	virtual bool isEmpty();

    virtual void empty();	

	virtual String getText();

	virtual String getText( const uint32& index, const uint32& count );

	virtual uint32 getSize();

protected:
	String text_;

	virtual void doSetText( const String& text );

    virtual void doInsertText( const uint32& index, const String& text );
	
    virtual void doReplaceText( const uint32& index, const uint32& len, const String& text );

    virtual void doRemoveText( const uint32& index, const uint32& count );
};

};


#endif // _VCF_DEFAULTTEXTMODEL_H__

/**
$Id$
*/
