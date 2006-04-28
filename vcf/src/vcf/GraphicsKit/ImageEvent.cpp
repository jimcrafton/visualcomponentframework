//ImageEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"


using namespace VCF;


ImageEvent::ImageEvent( Object* source ):
	Event( source )
{

}

ImageEvent::~ImageEvent()
{

}

void ImageEvent::init()
{
	this->newWidth_ = 0;
	this->newHeight_ = 0;
}

unsigned long ImageEvent::getNewWidth()
{
	return this->newWidth_;
}

void ImageEvent::setNewWidth( const unsigned long& newWidth )
{
	this->newWidth_ = newWidth;
}

unsigned long ImageEvent::getNewHeight()
{
	return this->newHeight_;
}

void ImageEvent::setNewHeight( const unsigned long& newHeight )
{
	this->newHeight_ = newHeight;
}


/**
$Id$
*/
