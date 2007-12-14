/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListItem.h"
#include "vcf/ApplicationKit/ListModel.h"


using namespace VCF;

//ListItem.cpp


String ListItem::getCaption() const
{
	//control's getUseLocaleStrings() takes precedence over ours
	Control* control = getControl();
	ListModel* lm = (ListModel*) getModel();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( lm->getAsString( index_ ) );
	}
	return lm->getAsString( index_ );
}

void ListItem::setCaption( const String& caption )
{
	ListModel* lm = (ListModel*) getModel();
	VCF_ASSERT( NULL != lm );

	lm->setAsString( index_, caption );

	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged( &event );
}

ListItem::SubItem* ListItem::addSubItem( const String& caption, void* data )
{
	return NULL;
}

void ListItem::addSubItem( ListItem::SubItem* subItem )
{

}

void ListItem::removeSubItem( const uint32& index )
{

}

Enumerator<ListItem::SubItem*>* ListItem::getSubItems()
{
	return NULL;
}

ListItem::SubItem* ListItem::getSubItem( const uint32& index )
{
	return NULL;
}

uint32 ListItem::getSubItemCount()
{
	return 0;
}

void ListItem::subItemChanged( ListItem::SubItem* item )
{

}