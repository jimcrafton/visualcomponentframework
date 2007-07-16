#ifndef _VCF_IMAGEEVENT_H__
#define _VCF_IMAGEEVENT_H__
//ImageEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/Event.h"

#define IMAGE_CONST						200

#define IMAGE_EVENT_HEIGHT_CHANGED		CUSTOM_EVENT_TYPES + IMAGE_CONST + 1
#define IMAGE_EVENT_WIDTH_CHANGED		CUSTOM_EVENT_TYPES + IMAGE_CONST + 2


namespace VCF
{

class ImageEvent : public Event
{
public:
	ImageEvent( Object* source ): Event(source),newWidth_(0),newHeight_(0) {};

	virtual ~ImageEvent(){};

	ImageEvent( const ImageEvent& rhs ):Event(rhs),newWidth_(0),newHeight_(0) {
		*this = rhs;
	}

	ImageEvent& operator=( const ImageEvent& rhs ) {
		Event::operator =( rhs );
		newWidth_ = rhs.newWidth_;
		newHeight_ = rhs.newHeight_;

		return *this;
	}

	uint32 getNewWidth() {
		return newWidth_;
	}

	void setNewWidth( const uint32& newWidth ) {
		newWidth_ = newWidth;
	}

	uint32 getNewHeight() {
		return newHeight_;
	}

	void setNewHeight( const uint32& newHeight ) {
		newWidth_ = newHeight;
	}	

	virtual Object* clone( bool deep=false ) {
		return new ImageEvent(*this);
	}

private:
	uint32 newWidth_;
	uint32 newHeight_;
};

typedef Delegate1<ImageEvent*> ImageDelegate;
};


#endif // _VCF_IMAGEEVENT_H__

/**
$Id$
*/
