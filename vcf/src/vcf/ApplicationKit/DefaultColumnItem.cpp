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


void DefaultColumnItem::setCaption( const String& caption )
{
	caption_ = caption;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged( &event );
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
	ItemPaint( &event );
}

void DefaultColumnItem::setCaptionAlignment( const TextAlignmentType& alignment )
{
	textAlignment_ = alignment;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged( &event );
}

void DefaultColumnItem::setWidth( const double& width )
{
	width_ = width;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged( &event );
}



/**
$Id$
*/
