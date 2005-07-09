//OSXToolbar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/ApplicationKit/OSXControl.h"

#include "vcf/ApplicationKit/OSXToolbar.h"
#include "vcf/ApplicationKit/Toolbar.h"


using namespace VCF;


OSXToolbar::OSXToolbar(Control* control):
	OSXControl(control),
	currentlyModifyingItem_(false)
{

}


void OSXToolbar::create( Control* control )
{
	
	control->getViewModel()->addModelHandler(
		new ModelEventHandler<OSXToolbar>( this, &OSXToolbar::onModelChanged, "OSXToolbar::onModelChanged" ) );

}

void OSXToolbar::setEnableAutoResize( const bool& val )
{
	
}

bool OSXToolbar::isAutoResizeEnabled()
{
	

	return true;
}

void OSXToolbar::onModelChanged( ModelEvent* e )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	int index = 0;

	switch( e->getType() ) {

		case ToolbarItem::tbCaptionChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			
		}
		break;


		case ToolbarItem::tbImageIndexChanged : {
			
		}
		break;


		case ToolbarItem::tbSelected : {

		}
		break;

		case ToolbarItem::tbGroupChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

						
		}
		break;

		case ToolbarItem::tbCheckChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

						
		}
		break;
		
		case ToolbarItem::tbItemControlAdded : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
			Control* addedControl = NULL;

			

			currentlyModifyingItem_ = false;
		}
		break;


		case ToolbarItem::tbDimensionsChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			
		}
		break;

		case ToolbarItem::tbAdded : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			bool val = ((Toolbar*)control_)->getShowButtonCaptions();			
		}
		break;

		case ToolbarItem::tbRemoved : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
			
		}
		break;

		case ToolbarItem::tbStateChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
			long state = tme->getItem()->getState();

			if ( state == ToolbarItem::tisSeparator ) {
				
			}
			else {
				if ( state & ToolbarItem::tisPressed ) {
					if ( state & ToolbarItem::tisChecked ) {
						
					}
				}
				
				if ( state & ToolbarItem::tisGrouped ) {
					
				}
				
				if ( state & ToolbarItem::tisChecked ) {
					
				}
				
				if ( state & ToolbarItem::tisEnabled ) {
					
				}
				else {
					
				}
			}			
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



void OSXToolbar::showButtonCaptions( const bool& val )
{
	control_->setVisible( false );

	

	control_->setVisible( true );
}

void OSXToolbar::setButtonCaptionPlacementHorizontal( const bool& val )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	currentlyModifyingItem_ = true;

	control_->setVisible( false );

	

	control_->setVisible( true );

	currentlyModifyingItem_ = false;
}

void OSXToolbar::setButtonSize( const Size& buttonSize )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	currentlyModifyingItem_ = true;

	control_->setVisible( false );

	

	control_->setVisible( true );
	currentlyModifyingItem_ = false;
}


void OSXToolbar::onImageListImageChanged( ImageListEvent* e )
{
	ImageList* imageList = (ImageList*)e->getSource();

	switch ( e->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED : case IMAGELIST_EVENT_HEIGHT_CHANGED :{
			
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

void OSXToolbar::setImageList( ImageList* imageList )
{
	if ( NULL != imageList ) {

		control_->setVisible( false );
		
		EventHandler* imgListHandler = getEventHandler( "OSXToolbar::onImageListImageChanged" );

		
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<OSXToolbar>(this, &OSXToolbar::onImageListImageChanged, "OSXToolbar::onImageListImageChanged" );
		}

		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );


		bool val = ((Toolbar*)control_)->getShowButtonCaptions();

		
		control_->setVisible( true );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.2  2005/06/23 01:26:55  ddiego
*build updates
*
*Revision 1.1.2.1  2005/06/23 00:35:36  ddiego
*added osx classes
*
*/


