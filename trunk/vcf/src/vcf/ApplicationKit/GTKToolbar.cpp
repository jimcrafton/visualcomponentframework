//GTKToolbar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/AbstractGTKControl.h"
#include "vcf/ApplicationKit/GTKToolbar.h"
#include "vcf/ApplicationKit/Toolbar.h"

using namespace VCF;

GTKToolbar::GTKToolbar( Control* control ) :
		currentlyModifyingItem_( false )
{
	control_ = ( Control* ) control;
}

void GTKToolbar::create( Control* control )
{

	control->getViewModel() ->addModelHandler(
	    new ModelEventHandler<GTKToolbar>( this, &GTKToolbar::onModelChanged, "GTKToolbar::onModelChanged" ) );

}

gboolean GTKToolbar::handleEvent( GdkEvent* gtkEvent )
{
	return AbstractGTKControl::handleEvent( gtkEvent );
}

void GTKToolbar::onModelChanged( ModelEvent* e )
{
	if ( currentlyModifyingItem_ ) {
		return ;
	}

	switch ( e->getType() ) {

		case ToolbarItem::tbCaptionChanged : {
				ToolbarModelEvent * tme = ( ToolbarModelEvent* ) e;


			}
			break;

		case ToolbarItem::tbSelected : {}
			break;

		case ToolbarItem::tbItemControlAdded : {
				ToolbarModelEvent* tme = ( ToolbarModelEvent* ) e;
			}
			break;


		case ToolbarItem::tbDimensionsChanged : {
				ToolbarModelEvent* tme = ( ToolbarModelEvent* ) e;
			}
			break;

		case ToolbarItem::tbAdded : {
				ToolbarModelEvent* tme = ( ToolbarModelEvent* ) e;
			}
			break;

		case ToolbarItem::tbRemoved : {
				ToolbarModelEvent* tme = ( ToolbarModelEvent* ) e;
			}
			break;

		case ToolbarItem::tbStateChanged : {
				ToolbarModelEvent* tme = ( ToolbarModelEvent* ) e;
			}
			break;

		case ToolbarItem::tbIndexChanged : {}
			break;

		default : {}
			break;
	}
}


void GTKToolbar::insertToolbarButton( const ulong32& index, ToolbarItem* item, bool showCaption )
{}

void GTKToolbar::showButtonCaptions( const bool& val )
{}

void GTKToolbar::setButtonCaptionPlacementHorizontal( const bool& val )
{}

void GTKToolbar::setButtonSize( const Size& buttonSize )
{}

void GTKToolbar::removeToolbarButton( ToolbarItem* item )
{}

void GTKToolbar::onImageListImageChanged( ImageListEvent* e )
{
	ImageList * imageList = ( ImageList* ) e->getSource();

	switch ( e->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED :
		case IMAGELIST_EVENT_HEIGHT_CHANGED : {
				int cx = imageList->getImageWidth();
				int cy = imageList->getImageHeight();



			}
			break;

		case IMAGELIST_EVENT_ITEM_ADDED : {}
			break;

		case IMAGELIST_EVENT_ITEM_DELETED : {}
			break;
	}
}

void GTKToolbar::setImageList( ImageList* imageList )
{}

bool GTKToolbar::isAutoResizeEnabled()
{}

void GTKToolbar::setEnableAutoResize( const bool& val )
{}

void GTKToolbar::setBorder( Border* border )
{}


/**
$Id$
*/
