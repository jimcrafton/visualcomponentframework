#ifndef _VCF_OSXTEXTPEER_H__
#define _VCF_OSXTEXTPEER_H__
//OSXTextPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/TextPeer.h"

namespace VCF {


class OSXTextPeer : public TextPeer {
public:
	OSXTextPeer( const bool& autoWordWrap, const bool& multiLined );

	OSXTextPeer();

	virtual ~OSXTextPeer();

	virtual OSHandleID getTextObjectHandle();

	//storage	
	virtual void insertText( unsigned int start, const String& text );

	virtual void deleteText( unsigned int start, unsigned int length );

	virtual unsigned int getTextLength();

	virtual String getText( unsigned int start, unsigned int length );

	
	//display
	virtual void paint( GraphicsContext* context, const Rect& paintRect );

	virtual void setRightMargin( const double & rightMargin );

	virtual void setLeftMargin( const double & leftMargin );	

	virtual void setTopMargin( const double & topMargin );

	virtual void setBottomMargin( const double & bottomMargin );	

	virtual double getLeftMargin();

	virtual double getRightMargin();

	virtual double getTopMargin();

	virtual double getBottomMargin();	

	virtual uint32 getLineCount();	

	virtual Rect getContentBoundsForWidth(const double& width);

	virtual void getStyle( unsigned int start, unsigned int length, Dictionary& styles );

	virtual void setStyle( unsigned int start, unsigned int length, Dictionary& styles );

	virtual void setDefaultStyle( Dictionary& styles );

protected:
	TXNObject txnObject_; 
	Rect margins_;
};



}; // namespace VCF


#endif //_VCF_OSXTEXTPEER_H__

/**
$Id$
*/
