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


GTKToolbar::GTKToolbar(Control* control):
	currentlyModifyingItem_(false)
{
	control_ = (Control*)control;
}

void GTKToolbar::create( Control* control )
{

	control->getViewModel()->addModelHandler(
		new ModelEventHandler<GTKToolbar>( this, &GTKToolbar::onModelChanged, "GTKToolbar::onModelChanged" ) );

}

gboolean GTKToolbar::handleEvent( GdkEvent* gtkEvent )
{
	return AbstractGTKControl::handleEvent( gtkEvent );
}

void GTKToolbar::onModelChanged( ModelEvent* e )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	switch( e->getType() ) {

		case ToolbarItem::tbCaptionChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;


		}
		break;

		case ToolbarItem::tbSelected : {

		}
		break;

		case ToolbarItem::tbItemControlAdded : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
		}
		break;


		case ToolbarItem::tbDimensionsChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
		}
		break;

		case ToolbarItem::tbAdded : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
		}
		break;

		case ToolbarItem::tbRemoved : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
		}
		break;

		case ToolbarItem::tbStateChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
		}
		break;

		case ToolbarItem::tbIndexChanged  : {

		}
		break;

		default : {

		}
		break;
	}
}


void GTKToolbar::insertToolbarButton( const ulong32& index, ToolbarItem* item, bool showCaption )
{

}

void GTKToolbar::showButtonCaptions( const bool& val )
{

}

void GTKToolbar::setButtonCaptionPlacementHorizontal( const bool& val )
{

}

void GTKToolbar::setButtonSize( const Size& buttonSize )
{


}

void GTKToolbar::removeToolbarButton( ToolbarItem* item )
{

}

void GTKToolbar::onImageListImageChanged( ImageListEvent* e )
{
	ImageList* imageList = (ImageList*)e->getSource();

	switch ( e->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED : case IMAGELIST_EVENT_HEIGHT_CHANGED :{
			int cx = imageList->getImageWidth();
			int cy = imageList->getImageHeight();



		}
		break;

		case IMAGELIST_EVENT_ITEM_ADDED : {


		}
		break;

		case IMAGELIST_EVENT_ITEM_DELETED : {

		}
		break;
	}
}

void GTKToolbar::setImageList( ImageList* imageList )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.1  2003/11/01 20:35:23  ddiego
*added GTKToolbar class impl - no real functionality at this point
*
*
*/


