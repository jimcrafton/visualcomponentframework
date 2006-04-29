//DefaultColumnItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DefaultColumnItem.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultColumnItem.h"
#include "vcf/ApplicationKit/DefaultColumnModel.h"


using namespace VCF;




DefaultColumnItem::DefaultColumnItem()
{
	index_ = 0;
	data_ = NULL;
	width_ = 100.0;
	imageIndex_ = -1;
	textAlignment_ = taTextLeft;
	tag_ = -1;
}

DefaultColumnItem::~DefaultColumnItem()
{

}

bool DefaultColumnItem::containsPoint( Point * pt )
{
	return false;
}

unsigned long DefaultColumnItem::getIndex()
{
	return index_;
}

void DefaultColumnItem::setIndex( const unsigned long& index )
{
	index_ = index;
}

void DefaultColumnItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultColumnItem::setData( void* data )
{
	data_ = data;

	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultColumnItem::setCaption( const String& caption )
{
	caption_ = caption;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged.fireEvent( &event );
}

String DefaultColumnItem::getCaption()
{
	//control's getUseLocaleStrings() takes precedence over ours
	Control* control = getControl();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( caption_ );
	}
	return caption_;
}

void DefaultColumnItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;
	ItemEvent event( this, context );
	ItemPaint.fireEvent( &event );
}

bool DefaultColumnItem::isSelected()
{
	return selected_;
}

void DefaultColumnItem::setSelected( const bool& selected )
{
	selected_ = selected;

	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemChanged.fireEvent( &event );
}

void DefaultColumnItem::setCaptionAlignment( const TextAlignmentType& alignment )
{
	textAlignment_ = alignment;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultColumnItem::setWidth( const double& width )
{
	width_ = width;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}


void DefaultColumnItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}


/**
$Id$
*/
