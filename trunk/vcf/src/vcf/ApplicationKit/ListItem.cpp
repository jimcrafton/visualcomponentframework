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

	ListModel* lm = ownerItem_->getListModel();
	result = lm->getSubItemAsString( ownerItem_->getIndex(), 
							ownerItem_->getController()->getItemSubItemIndex( ownerItem_, this ) );

	if ( getUseLocaleStrings() && (NULL != ownerItem_->getControl()) && (ownerItem_->getControl()->getUseLocaleStrings()) ) {
		result = System::getCurrentThreadLocale()->translate( result );
	}
	return result;
}

void ListSubItem::setCaption( const String& caption )
{
	ListModel* lm = ownerItem_->getListModel();

	lm->setSubItemAsString( ownerItem_->getIndex(), 
							ownerItem_->getController()->getItemSubItemIndex( ownerItem_, this ),
							caption );
}

ListSubItem::ListSubItem( ListItem* ownerItem, const String& caption, void* data ):
	data_(data)
{
	ownerItem_ = ownerItem;
	setCaption(caption);

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

	lm->setAsString( index_, caption );
}

ListSubItem* ListItem::addSubItem( const String& caption, void* data )
{
	ListSubItem* result = new ListSubItem(this, caption, data);

	addSubItem( result );

	return result;
}

void ListItem::addSubItem( ListSubItem* subItem )
{
	internalChange_ = true;

	if ( subItem->getListItem() != this ) {
		subItem->setListItem(this);
	}

	addComponent( subItem );
	getController()->insertItemSubItem( this, getController()->getItemSubItemCount(this), subItem );
	internalChange_ = false;
}

void ListItem::removeSubItem( const uint32& index )
{
	ListSubItem* item = getController()->getItemSubItem(this,index);
	getController()->removeItemSubItem( this, item );

	removeComponent( item );
	item->free();
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

void ListItem::handleEvent( Event* event )
{
	Item::handleEvent( event );

	switch ( event->getType() ) {
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			ListSubItem* item = dynamic_cast<ListSubItem*>(child);
			if ( NULL != item ) {
				if ( !internalChange_ ) {
					if ( item->getListItem() != this ) {
						item->setListItem(this);
					}			
					
					getController()->insertItemSubItem( this, getController()->getItemSubItemCount(this), item );
				}
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
		}
		break;
	}
}