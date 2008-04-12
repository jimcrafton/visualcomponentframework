//ListControl.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/ListModel.h"
#include "vcf/ApplicationKit/ListPeer.h"
#include "vcf/ApplicationKit/ListControl.h"
#include "vcf/ApplicationKit/ListItem.h"


using namespace VCF;




ListControl::ListControl():
	Control(),
	smallImageList_(NULL),
	largeImageList_(NULL),
	stateImageList_(NULL),
	selectedItem_(NULL),
	listPeer_(NULL),
	internalModelChange_(false),
	inCallbackChange_(false)
		
{
	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );
}

ListModel* ListControl::getListModel()
{
	return (ListModel*) getViewModel();
}

void ListControl::setListModel(ListModel * model)
{
	setViewModel( model );
}

void ListControl::onListModelContentsChanged( ListModelEvent* event )
{

}

void ListControl::onItemAdded( ListModelEvent* event )
{
	if ( internalModelChange_ ) {
		return;
	}

	inCallbackChange_ = true;

	ListItem* item = new ListItem();
	addComponent( item );
	items_.push_back( item );
	item->setModel( getViewModel() );
	item->setControl( this );
	item->setIndex( event->index );	


	repaint();

	inCallbackChange_ = false;
}

void ListControl::removeSubItemsForItem( ListItem* item )
{

}

void ListControl::onItemDeleted( ListModelEvent* event )
{
	inCallbackChange_ = true;
	Array<ListItem*>::iterator found = items_.begin();

	while ( found != items_.end() ) {
		ListItem* item = *found;
		if ( item->getIndex() == event->index ) {
			break;
		}
		++found;
	}

	if ( found != items_.end() ) {				
		Array<ListItem*>::iterator it = items_.begin();		
		while ( it != items_.end() ) {
			ListItem* item = *it;
			if ( item->getIndex() > event->index ) {
				item->setIndex( item->getIndex() - 1 );
			}
			
			++it;
		}
		
		ListItem* item = *found;
		
		removeSubItemsForItem( item );

		items_.erase( found );
		
		removeComponent( item );
		item->free();
	}
	inCallbackChange_ = false;
}

void ListControl::modelChanged( Model* oldModel, Model* newModel )
{
	ListModel* lm = (ListModel*)oldModel;

	if ( NULL != lm ) {
		CallBack* ev = getCallback( "ListControl::onItemAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemAdded, "ListControl::onItemAdded" );
		}
		
		lm->ItemAdded -= ev;

		ev = getCallback( "ListControl::onItemDeleted" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemDeleted, "ListControl::onItemDeleted" );
		}

		lm->ItemRemoved -= ev;

		ev = getCallback( "ListControl::onListModelContentsChanged" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onListModelContentsChanged, "ListControl::onListModelContentsChanged" );
		}

		lm->ModelChanged -= ev;
	}

	if ( NULL != newModel ) {
		lm = dynamic_cast<ListModel*>( newModel );
		VCF_ASSERT( lm != NULL );
		
		
		if ( NULL != lm ) {
			CallBack* ev = getCallback( "ListControl::onItemAdded" );
			if ( NULL == ev ) {
				ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemAdded, "ListControl::onItemAdded" );
			}
			
			lm->ItemAdded += ev;
			
			ev = getCallback( "ListControl::onItemDeleted" );
			if ( NULL == ev ) {
				ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemDeleted, "ListControl::onItemDeleted" );
			}
			
			lm->ItemRemoved += ev;
			
			ev = getCallback( "ListControl::onListModelContentsChanged" );
			if ( NULL == ev ) {
				ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onListModelContentsChanged, "ListControl::onListModelContentsChanged" );
			}
			
			lm->ModelChanged += ev;
		}
	}
}

void ListControl::handleEvent( Event* event )
{
	Control::handleEvent( event );
	switch ( event->getType() ) {
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			ListItem* item = dynamic_cast<ListItem*>(child);
			if ( NULL != item ) {
				
				if ( !inCallbackChange_ ) {				
					internalModelChange_ = true;
					ListModel* lm = getListModel();
					lm->add( "" );
					
					items_.push_back( item );
					item->setModel( getViewModel() );
					item->setControl( this );
					item->setIndex( lm->getCount()-1 );	
					
					internalModelChange_ = false;
				}
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
		}
		break;

		case ITEM_EVENT_SELECTED : {
			ItemSelectionChanged( (ItemEvent*)event );
		}
		break;
	}
}

Rect ListControl::getItemRect( ListItem* item )
{
	return listPeer_->getItemRect( item->getIndex() ) ;
}

void ListControl::itemSelected( ListItem* item )
{
	if ( item->isSelected() ) {
		listPeer_->selectItem( item->getIndex() );
	}
	else {
		listPeer_->selectItem( ListModel::InvalidIndex );
	}
}

void ListControl::setLargeImageList( ImageList* imageList )
{
	this->largeImageList_ = imageList;
	listPeer_->setLargeImageList( imageList );
}

void ListControl::setSmallImageList( ImageList* imageList )
{
	this->smallImageList_ = imageList;
	listPeer_->setSmallImageList( imageList );
}

void ListControl::setStateImageList( ImageList* imageList )
{
	stateImageList_ = imageList;	
}

ListItem* ListControl::addItem( const String& caption, const uint32 imageIndex )
{
	ListModel* lm = getListModel();

	return insertItem( lm->getCount(), caption, imageIndex );
}

ListItem* ListControl::insertItem( const uint32& index, const String& caption, const uint32 imageIndex )
{
	ListItem* result = NULL;
	ListModel* lm = getListModel();
	lm->insert( index, caption );

	result = getItem(index);

	return result;
}

bool ListControl::itemExists( const uint32& index )
{
	if ( index < items_.size() ) {		
		return true;
	}
	return false;
}

ListItem* ListControl::getItem( const uint32& index )
{
	ListItem* result = NULL;

	if ( index < items_.size() ) {
		result = items_[index];
	}

	return result;
}

void ListControl::setItem( const uint32& index, ListItem* item )
{
	if ( index < items_.size() ) {
		inCallbackChange_ = true;
		ListItem* oldItem = items_[index];
		
		items_[index] = item;
		
		if ( NULL == item->getOwner() ) {
			addComponent( item );
		}

		item->setControl( this );
		item->setModel( getViewModel() );
		item->setIndex( oldItem->getIndex() );



		//free up sub items
		removeSubItemsForItem( oldItem );

		removeComponent( oldItem );
		oldItem->free();

		repaint();
		inCallbackChange_ = false;
	}
}

Rect ListControl::getItemImageRect( const uint32& index )
{
	return listPeer_->getItemImageRect( index );
}

void ListControl::selectItem( const uint32& index )
{
	listPeer_->selectItem( index );
}

Enumerator<uint32>* ListControl::getSelectedItems()
{
	return listPeer_->getSelectedItems();
}

void ListControl::rangeSelect( const Rect& selectionRect )
{
	listPeer_->rangeSelect( selectionRect );
}

uint32 ListControl::getFocusedItem()
{
	return listPeer_->getFocusedItem();
}

uint32 ListControl::getSelectedItem()
{
	return listPeer_->getSelectedItem();
}

bool ListControl::allowsMultiSelect()
{
	return listPeer_->allowsMultiSelect();
}

void ListControl::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	listPeer_->setAllowsMultiSelect( allowsMultiSelect );
}

void ListControl::sort( ItemSort* itemSortFunctor )
{
	
}

uint32 ListControl::hitTest( const Point& point )
{
	return listPeer_->hitTest( point );
}
