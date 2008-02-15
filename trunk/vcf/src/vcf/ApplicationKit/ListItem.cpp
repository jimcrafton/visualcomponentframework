//ListItem.cpp
/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListItem.h"
#include "vcf/ApplicationKit/ListModel.h"


using namespace VCF;


String ListSubItem::getCaption()
{
	String result;

	return result;
}

void ListSubItem::setCaption( const String& caption )
{

}


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

	lm->setAsString( index_, caption, false );

	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged( &event );
}

ListSubItem* ListItem::addSubItem( const String& caption, void* data )
{
	return NULL;
}

void ListItem::addSubItem( ListSubItem* subItem )
{
	getController()->insertItemSubItem( this, getController()->getItemSubItemCount(this), subItem );
}

void ListItem::removeSubItem( const uint32& index )
{
	getController()->removeItemSubItem( this, getController()->getItemSubItem(this,index) );
}

bool ListItem::getSubItems( std::vector<ListSubItem*>& subItems )
{
	return getController()->getItemSubItems( this, subItems );
}

ListSubItem* ListItem::getSubItem( const uint32& index )
{
	return getController()->getItemSubItem(this,index);
}

uint32 ListItem::getSubItemCount()
{
	return getController()->getItemSubItemCount(this);
}

void ListItem::subItemChanged( ListSubItem* item )
{
	ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_CHANGED );
	
	SubItemChanged( &event );
}