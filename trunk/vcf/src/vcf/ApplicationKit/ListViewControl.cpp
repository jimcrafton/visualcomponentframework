//ListViewControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/ListviewPeer.h"
#include "vcf/ApplicationKit/DefaultListModel.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/DefaultColumnModel.h"
#include "vcf/ApplicationKit/DefaultColumnItem.h"

using namespace VCF;


ListViewControl::ListViewControl():
	selectedItem_(NULL),
		internalModelChange_(false),
		smallImageList_(NULL),
	largeImageList_(NULL),
	stateImageList_(NULL),
	iconStyle_(isLargeIcon)
{
	listviewPeer_ = UIToolkit::createListViewPeer( this );

	peer_ = dynamic_cast<ControlPeer*>(listviewPeer_ );

	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->create( this );

	setListModel( new DefaultListModel() );

	addComponent( getViewModel() );


	columnModel_ = new DefaultColumnModel();

	addComponent( columnModel_ );

	EventHandler* cmh = (EventHandler*)
		new ClassProcedure1<ColumnModelEvent*,ListViewControl>( this, &ListViewControl::onColumnItemAdded, "ListViewControl::onColumnItemAdded" );
	columnModel_->ItemAdded += cmh;

	cmh = (EventHandler*)
		new ClassProcedure1<ColumnModelEvent*,ListViewControl>( this, &ListViewControl::onColumnItemDeleted, "ListViewControl::onColumnItemDeleted" );
	columnModel_->ItemRemoved += cmh;


	EventHandler* paintHandler = (EventHandler*)
		new ClassProcedure1<ItemEvent*,ListViewControl>( this, &ListViewControl::onItemPaint, "ListViewControl::onItemPaint" );

	ItemSelectionChanged += new ClassProcedure1<ItemEvent*,ListViewControl>( this, &ListViewControl::onItemSelected, "ListViewControl::onItemSelected" );

	init();

	setVisible( true );
}


ListViewControl::~ListViewControl()
{
	if ( NULL != columnModel_ ) {
		//columnModel_->release();
	}



}

void ListViewControl::init()
{
	

	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );

	setBorder( new Basic3DBorder( true ) );
}

ListModel* ListViewControl::getListModel()
{
	return (ListModel*) getViewModel();
}

ColumnModel* ListViewControl::getColumnModel()
{
	return columnModel_;
}

void ListViewControl::setViewModel( Model* model )
{
	ListModel* lm = getListModel();

	if ( NULL != lm ) {
		CallBack* ev = getCallback( "ListBoxControl::onItemAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListViewControl>( this, &ListViewControl::onItemAdded, "ListBoxControl::onItemAdded" );
		}
		
		lm->ItemAdded -= ev;

		ev = getCallback( "ListBoxControl::onItemDeleted" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListViewControl>( this, &ListViewControl::onItemDeleted, "ListBoxControl::onItemDeleted" );
		}

		lm->ItemRemoved -= ev;

		ev = getCallback( "ListBoxControl::onListModelContentsChanged" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListViewControl>( this, &ListViewControl::onListModelContentsChanged, "ListBoxControl::onListModelContentsChanged" );
		}

		lm->ModelChanged -= ev;
	}

	Control::setViewModel( model );

	lm = dynamic_cast<ListModel*>( model );
	VCF_ASSERT( lm != NULL );


	if ( NULL != lm ) {
		//listModel_->addRef();

		CallBack* ev = getCallback( "ListBoxControl::onItemAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListViewControl>( this, &ListViewControl::onItemAdded, "ListBoxControl::onItemAdded" );
		}
		
		lm->ItemAdded += ev;

		ev = getCallback( "ListBoxControl::onItemDeleted" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListViewControl>( this, &ListViewControl::onItemDeleted, "ListBoxControl::onItemDeleted" );
		}

		lm->ItemRemoved += ev;

		ev = getCallback( "ListBoxControl::onListModelContentsChanged" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListViewControl>( this, &ListViewControl::onListModelContentsChanged, "ListBoxControl::onListModelContentsChanged" );
		}

		lm->ModelChanged += ev;
	}
}

void ListViewControl::setListModel(ListModel * model)
{
	setViewModel( model );	
}

void ListViewControl::onItemPaint( ItemEvent* event )
{
	return;

	ListItem* item = (ListItem*)event->getSource();
	GraphicsContext* context = event->getContext();
	if ( NULL != context ) {
		ImageList* il = NULL;

		if (  isLargeIcon == iconStyle_ ) {
			il = getLargeImageList();
		}
		else {
			il = getSmallImageList();
		}
		if ( NULL != il ) {
			Rect imgRect = item->getBounds();

			imgRect.left_ = imgRect.left_ + (imgRect.getWidth()/2.0 - il->getImageWidth()/2.0);
			imgRect.right_ = imgRect.left_ + il->getImageWidth();
			imgRect.bottom_ = imgRect.top_ + il->getImageHeight();

			context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );
			context->rectangle( &imgRect );
			context->fillPath();

			if ( true == item->isSelected() ) {
				if ( NULL != stateImageList_ ) {
					//stateImageList_->draw( context, item->getSelectedImageIndex(), &imgRect );
				}
				else {
					il->draw( context, item->getImageIndex(), &imgRect );
				}
			}
			else {
				il->draw( context, item->getImageIndex(), &imgRect );
			}
		}
	}
}

void ListViewControl::onListModelContentsChanged( ListModelEvent* event )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	if ( NULL != event ){
		switch ( event->getType() ){
/*			case LIST_MODEL_CONTENTS_DELETED: {
				listviewPeer_->clear();
			}
			break;

			case LIST_MODEL_ITEM_CHANGED: {
				ListItem* item = event->getListItem();
				if ( NULL != item ){
					listviewPeer_->deleteItem( item );
					listviewPeer_->insert( item->getIndex(), item );
				}
			}
			break;
			*/
		}
	}
}

void ListViewControl::onItemAdded( ListModelEvent* event )
{
	CallBack* paintHandler = this->getCallback( "ListViewControl::onItemPaint" );
/*
	ListItem* item = event->getListItem();
	if ( NULL != paintHandler ) {
		item->ItemPaint += paintHandler;
	}

	listviewPeer_->add( item );
	*/

	if ( internalModelChange_ ) {
		return;
	}

	ListItem* item = new ListItem();
	addComponent( item );
	items_.push_back( item );
	item->setModel( getViewModel() );
	item->setControl( this );
	item->setIndex( event->index );	


	repaint();

}

void ListViewControl::onItemDeleted( ListModelEvent* event )
{
//	listviewPeer_->deleteItem( event->getListItem() );
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
		items_.erase( found );		
		
		removeComponent( item );
		item->free();
	}
}

ColumnItem* ListViewControl::addHeaderColumn( const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new DefaultColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->add( result );

	return result;
}

void ListViewControl::addHeaderColumn( ColumnItem* column )
{
	columnModel_->add( column );
}

void ListViewControl::insertHeaderColumn( const uint32& index, ColumnItem* column )
{
	columnModel_->insert( index, column );
}

ColumnItem* ListViewControl::insertHeaderColumn( const uint32& index, const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new DefaultColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->insert( index, result );

	return result;
}

void ListViewControl::deleteHeaderColumn( const uint32& index )
{
	columnModel_->remove( index );
}

String ListViewControl::getColumnName( const uint32& index )
{	
	return columnModel_->getAsString( index );
}

void ListViewControl::setColumnName( const uint32& index, const String& columnName )
{
//	ColumnItem* item = columnModel_->getItemFromIndex( index );
//	item->setCaption( columnName );
	columnModel_->setAsString( index, columnName );
}

double ListViewControl::getColumnWidth( const uint32& index )
{
	return listviewPeer_->getColumnWidth( index );
}

void ListViewControl::setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type )
{
	listviewPeer_->setColumnWidth( index, width, type );
}

void ListViewControl::setColumnsWidth( const double& width, ListViewControl::AutoSizeType type )
{
	for ( int i = 0; i < columnModel_->getCount(); ++i ) {
		listviewPeer_->setColumnWidth( i, width, type );
	}
}

IconStyleType ListViewControl::getIconStyle()
{
	return iconStyle_;// listviewPeer_->getIconStyle();
}

void ListViewControl::setIconStyle( const IconStyleType& iconStyle )
{
	iconStyle_ = iconStyle;
	listviewPeer_->setIconStyle( iconStyle_ );
}

bool ListViewControl::getAllowsMultiSelect()
{
	return listviewPeer_->getAllowsMultiSelect();
}

void ListViewControl::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	listviewPeer_->setAllowsMultiSelect( allowsMultiSelect );
}

IconAlignType ListViewControl::getIconAlignment()
{
	return listviewPeer_->getIconAlignment();
}

void ListViewControl::setIconAlignment( const IconAlignType& iconAlignType )
{
	listviewPeer_->setIconAlignment( iconAlignType );
}

bool ListViewControl::getAllowLabelEditing()
{
	return listviewPeer_->getAllowLabelEditing();
}

void ListViewControl::setAllowLabelEditing( const bool& allowLabelEditing )
{
	listviewPeer_->setAllowLabelEditing( allowLabelEditing );
}

void ListViewControl::setItemFocused( ListItem* item )
{
	listviewPeer_->setFocusedItem( item );
}

void ListViewControl::onListModelEmptied( ModelEvent* event )
{
	listviewPeer_->clear();
}

void ListViewControl::onColumnItemAdded( ColumnModelEvent* event )
{
	ColumnItem* item = new DefaultColumnItem();
	item->setControl( this );
	item->setModel( getColumnModel() );
	item->setIndex( event->index );
	addComponent( item );
	columnItems_.insert( columnItems_.begin() + event->index, item );	

	listviewPeer_->insertHeaderColumn( item->getIndex(), item->getCaption(), item->getWidth() );

	CallBack* columnItemChanged = getCallback( "ListViewControl::onColumnItemChanged" );
	if ( NULL == columnItemChanged ) {
		columnItemChanged = new ClassProcedure1<ItemEvent*,ListViewControl>( this,
																	&ListViewControl::onColumnItemChanged,
																	"ListViewControl::onColumnItemChanged" );
	}

	item->ItemChanged += columnItemChanged;
}

void ListViewControl::onColumnItemDeleted( ColumnModelEvent* event )
{
	//ColumnItem* item = event->getColumnItem();

	//listviewPeer_->deleteHeaderColumn( item->getIndex() );
}

void ListViewControl::onColumnItemChanged( ItemEvent* event )
{
	ColumnItem* item = (ColumnItem*)event->getSource();

	uint32 index = item->getIndex();
	listviewPeer_->setColumnName( index, item->getCaption() );
	listviewPeer_->setColumnWidth( index, item->getWidth() );
}

void ListViewControl::sort( ItemSort* itemSortFunctor )
{
	listviewPeer_->sort( itemSortFunctor );
}

ListItem* ListViewControl::isPtOverItem(Point* point)
{
	return listviewPeer_->isPtOverItem( point );
}

ListItem* ListViewControl::getFocusedItem()
{
	return listviewPeer_->getFocusedItem();
}

ListItem* ListViewControl::getSelectedItem()
{
	return listviewPeer_->getSelectedItem();//
}

Enumerator<ListItem*>* ListViewControl::getSelectedItems()
{
	return listviewPeer_->getSelectedItems();
}

void ListViewControl::rangeSelect( Rect* selectionRect )
{
	listviewPeer_->rangeSelect( selectionRect );
}

ListItem* ListViewControl::addItem( const String& caption, const uint32 imageIndex )
{
	ListModel* lm = getListModel();

	return insertItem( lm->getCount(), caption, imageIndex );
}


ListItem* ListViewControl::insertItem( const uint32& index, const String& caption, const uint32 imageIndex )
{
	ListItem* result = NULL;
	
	ListModel* lm = getListModel();
	lm->insert( index, caption );

	return result;
}


void ListViewControl::setSmallImageList( ImageList* imageList )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	smallImageList_ = imageList;

	listviewPeer_->setSmallImageList( smallImageList_ );
}

void ListViewControl::setLargeImageList( ImageList* imageList )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	largeImageList_ = imageList;

	listviewPeer_->setLargeImageList( largeImageList_ );
}

void ListViewControl::setStateImageList( ImageList* imageList )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	stateImageList_ = imageList;
}

Rect ListViewControl::getItemImageRect( ListItem* item )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	return listviewPeer_->getItemImageRect( item );
}

int32 ListViewControl::getDisplayOptions()
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	return listviewPeer_->getDisplayOptions();
}

void ListViewControl::setDisplayOptions( const int32& displayOptions )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	listviewPeer_->setDisplayOptions( displayOptions );
}

void ListViewControl::selectItem( ListItem* item )
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	listviewPeer_->selectItem( item );
}

void ListViewControl::handleEvent( Event* event )
{
	Control::handleEvent( event );
	switch ( event->getType() ) {
		case ListViewControl::COLUMN_MOUSE_EVENT_CLICK : {
			ColumnItemClicked( (MouseEvent*)event );
		}
		break;
	}
}

void ListViewControl::onItemSelected( ItemEvent* event )
{
	selectedItem_ = listviewPeer_->getSelectedItem();
}

void ListViewControl::paint( GraphicsContext * context )
{
	Rect innerBounds = getClientBounds( false );	

	context->setColor( getColor() );
			
	context->rectangle( &innerBounds );
			
	context->fillPath();
}

Rect ListViewControl::getItemRect( ListItem* item )
{
	return listviewPeer_->getItemRect( item );
}

ListItem* ListViewControl::getListItem( const uint32& index )
{
	ListItem* result = NULL;

	if ( index < items_.size() ) {
		result = items_[index];
	}

	return result;
}

void ListViewControl::setListItem( const uint32& index, ListItem* item )
{
	if ( index < items_.size() ) {
		ListItem* oldItem = items_[index];
		
		items_[index] = item;
		
		if ( NULL == item->getOwner() ) {
			addComponent( item );
		}

		item->setControl( this );
		item->setModel( getViewModel() );
		item->setIndex( oldItem->getIndex() );

		removeComponent( oldItem );
		oldItem->free();

		repaint();
	}
}

Enumerator<ListItem*>* ListViewControl::getItems()
{
	return items_.getEnumerator();
}

Enumerator<ColumnItem*>* ListViewControl::getColumnItems()
{
	return columnItems_.getEnumerator();
}	

/**
$Id$
*/
