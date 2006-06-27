#ifndef _VCF_IMAGELISTEVENT_H__
#define _VCF_IMAGELISTEVENT_H__
//ImageListEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{


#define IMAGELIST_CONST						1100

#define IMAGELIST_EVENT_WIDTH_CHANGED		CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 1
#define IMAGELIST_EVENT_HEIGHT_CHANGED		CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 2
#define IMAGELIST_EVENT_CREATED				CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 3
#define IMAGELIST_EVENT_DESTROYED			CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 4
#define IMAGELIST_EVENT_ITEM_ADDED			CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 5
#define IMAGELIST_EVENT_ITEM_DELETED		CUSTOM_EVENT_TYPES + IMAGELIST_CONST + 6


/**
\class ImageListEvent ImageListEvent.h "vcf/ApplicationKit/ImageListEvent.h"
*/
class APPLICATIONKIT_API ImageListEvent : public Event {
public:

	ImageListEvent( Object * source): Event(source), image_(NULL), imageIndex_(0) {}

	ImageListEvent( Object* source, const uint32& eventType, Image* image=NULL )
		: Event(source,eventType), image_(image), imageIndex_(0) {}

	ImageListEvent( const ImageListEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~ImageListEvent() {}


	ImageListEvent& operator=( const ImageListEvent& rhs ) {
		Event::operator =( rhs );

		image_ = rhs.image_;
		imageIndex_ = rhs.imageIndex_;

		return *this;
	}

	Image* getImage() {
		return image_;
	}

	uint32 getIndexOfImage() {
		return imageIndex_;
	}

	void setIndexOfImage( const uint32& indexOfImage ) {
		imageIndex_ = indexOfImage;
	}

	virtual Object* clone( bool deep=false ) {
		return new ImageListEvent(*this);
	}
protected:
	Image* image_;
	uint32 imageIndex_;
};





/**
\class ImageListEventHandler ImageListEvent.h "vcf/ApplicationKit/ImageListEvent.h"
*ImageListEventHandler
*This handles the following Image List events:
*ImageListSizeChanged
*ImageAdded
*ImageDeleted
*ImageListCreated
*ImageListDestroyed
*ImageListSizeChanged
*/
template <class SOURCE_TYPE> class ImageListEventHandler : public EventHandlerInstance<SOURCE_TYPE,ImageListEvent> {
public:
	ImageListEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ImageListEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ImageListEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~ImageListEventHandler(){};
};



};


#endif // _VCF_IMAGELISTEVENT_H__

/**
$Id$
*/
