/*
 Copyright 2000-3007 The VCF Project, Jim Crafton.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/OSXDropDown.h"

namespace VCF {

OSXDropDown::OSXDropDown( Control* control ):
		OSXControl(control)
{
	
}

OSXDropDown::~OSXDropDown()
{
	
}

void OSXDropDown::create( Control* owningControl )
{
	
}

Rect OSXDropDown::getBounds()
{
	return Rect();
}

void OSXDropDown::setBounds( Rect* rect )
{
	
}

void OSXDropDown::enableEditBox( bool val )
{
	
}

bool OSXDropDown::editBoxEnabled()
{
	return false;
}

void OSXDropDown::setEditText( const String& text )
{
	
}

String OSXDropDown::getEditText()
{
	return "";
}

void OSXDropDown::setDropDownWidth( double val )
{
	
}

double OSXDropDown::getDropDownWidth()
{
	return 0.0;
}

void OSXDropDown::setDropDownCount( const uint32& dropDownCount )
{
	
}

uint32 OSXDropDown::getDropDownCount()
{
	return 0;
}

void OSXDropDown::selectItem( const uint32& index )
{
	
}

uint32 OSXDropDown::getSelectedItem()
{
	return 0;
}

void OSXDropDown::setFocusedItem( const uint32& index )
{
	
}

uint32 OSXDropDown::getFocusedItem()
{
	return 0;
}

bool OSXDropDown::isItemSelected( const uint32& index )
{
	return false;
}

Rect OSXDropDown::getItemRect( const uint32& index )
{
	return Rect();
}

Rect OSXDropDown::getItemImageRect( const uint32& index )
{
	return Rect();
}

uint32 OSXDropDown::hitTest( const Point& point )
{
	return 0;
}

Enumerator<uint32>* OSXDropDown::getSelectedItems()
{
	return selectedItems_.getEnumerator();
}

void OSXDropDown::rangeSelect( const Rect& selectionRect )
{
	
}

bool OSXDropDown::allowsMultiSelect()
{
	return false;
}

void OSXDropDown::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	
}

void OSXDropDown::setLargeImageList( ImageList* imageList )
{
	
}

void OSXDropDown::setSmallImageList( ImageList* imageList )
{
	
}

void OSXDropDown::setFont( Font* font )
{
	
}


}
