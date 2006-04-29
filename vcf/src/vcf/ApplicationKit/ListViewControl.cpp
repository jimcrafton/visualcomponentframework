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
	listModel_(NULL),
	selectedItem_(NULL)
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

	EventHandler* cmh = new ColumnModelEventHandler<ListViewControl>( this, &ListViewControl::onColumnItemAdded, "ListViewControl::onColumnItemAdded" );
	columnModel_->addItemAddedHandler( cmh );

	cmh = new ColumnModelEventHandler<ListViewControl>( this, &ListViewControl::onColumnItemDeleted, "ListViewControl::onColumnItemDeleted" );
	columnModel_->addItemDeletedHandler( cmh );


	EventHandler* paintHandler = new ItemEventHandler<ListViewControl>( this, &ListViewControl::onItemPaint, "ListViewControl::onItemPaint" );

	ItemSelectionChanged +=
		new ItemEventHandler<ListViewControl>( this, &ListViewControl::onItemSelected, "ListViewControl::onItemSelected" );

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
	smallImageList_ = NULL;

	largeImageList_ = NULL;

	stateImageList_ = NULL;

	iconStyle_ = isLargeIcon;

	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );

	setBorder( new Basic3DBorder( true ) );
}

ListModel* ListViewControl::getListModel()
{
	return listModel_;
}

ColumnModel* ListViewControl::getColumnModel()
{
	return columnModel_;
}

void ListViewControl::setListModel(ListModel * model)
{
	if ( NULL != listModel_ ) {
	//	listModel_->release();
	}

	listModel_ = model;


	if ( NULL != listModel_ ) {
		//listModel_->addRef();

		EventHandler* ev = getEventHandler( "ListBoxControl::onItemAdded" );
		if ( NULL == ev ) {
			ev = new ListModelEventHandler<ListViewControl>( this, &ListViewControl::onItemAdded, "ListBoxControl::onItemAdded" );
		}

		listModel_->addItemAddedHandler( ev );

		ev = getEventHandler( "ListBoxControl::onItemDeleted" );
		if ( NULL == ev ) {
			ev = new ListModelEventHandler<ListViewControl>( this, &ListViewControl::onItemDeleted, "ListBoxControl::onItemDeleted" );
		}

		listModel_->addItemDeletedHandler( ev );

		ev = getEventHandler( "ListBoxControl::onListModelContentsChanged" );
		if ( NULL == ev ) {
			ev = new ListModelEventHandler<ListViewControl>( this, &ListViewControl::onListModelContentsChanged, "ListBoxControl::onListModelContentsChanged" );
		}

		listModel_->addContentsChangedHandler( ev );

	}

	setViewModel( dynamic_cast<Model*>(listModel_) );
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
			Rect imgRect = *(item->getBounds());

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
			case LIST_MODEL_CONTENTS_DELETED: {
				listviewPeer_->clear();
			}
			break;

			case LIST_MODEL_ITEM_CHANGED: {
				ListItem* item = event->getListItem();
				if ( NULL != item ){
					listviewPeer_->deleteItem( item );
					listviewPeer_->insertItem( item->getIndex(), item );
				}
			}
			break;
		}
	}
}

void ListViewControl::onItemAdded( ListModelEvent* event )
{
	EventHandler* paintHandler = this->getEventHandler( "ListViewControl::onItemPaint" );
	ListItem* item = event->getListItem();
	if ( NULL != paintHandler ) {
		item->addItemPaintHandler( paintHandler );
	}

	listviewPeer_->addItem( item );
}

void ListViewControl::onItemDeleted( ListModelEvent* event )
{
	listviewPeer_->deleteItem( event->getListItem() );
}

ColumnItem* ListViewControl::addHeaderColumn( const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new DefaultColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->addItem( result );

	return result;
}

void ListViewControl::addHeaderColumn( ColumnItem* column )
{
	columnModel_->addItem( column );
}

void ListViewControl::insertHeaderColumn( const unsigned long& index, ColumnItem* column )
{
	columnModel_->insertItem( index, column );
}

ColumnItem* ListViewControl::insertHeaderColumn( const unsigned long& index, const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new DefaultColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->insertItem( index, result );

	return result;
}

void ListViewControl::deleteHeaderColumn( const unsigned long& index )
{
	columnModel_->deleteItem( index );
}

String ListViewControl::getColumnName( const unsigned long& index )
{
	ColumnItem* item = columnModel_->getItemFromIndex( index );
	return item->getCaption();
}

void ListViewControl::setColumnName( const unsigned long& index, const String& columnName )
{
	ColumnItem* item = columnModel_->getItemFromIndex( index );
	item->setCaption( columnName );
}

double ListViewControl::getColumnWidth( const unsigned long& index )
{
	return listviewPeer_->getColumnWidth( index );
}

void ListViewControl::setColumnWidth( const unsigned long& index, const double& width, ListViewControl::AutoSizeType type )
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
	ColumnItem* item = event->getColumnItem();

	listviewPeer_->insertHeaderColumn( item->getIndex(), item->getCaption(), item->getWidth() );

	EventHandler* columnItemChanged = getEventHandler( "ListViewControl::onColumnItemChanged" );
	if ( NULL == columnItemChanged ) {
		columnItemChanged = new ItemEventHandler<ListViewControl>( this,
																	&ListViewControl::onColumnItemChanged,
																	"ListViewControl::onColumnItemChanged" );
	}

	item->addItemChangedHandler( columnItemChanged );

}

void ListViewControl::onColumnItemDeleted( ColumnModelEvent* event )
{
	ColumnItem* item = event->getColumnItem();

	listviewPeer_->deleteHeaderColumn( item->getIndex() );
}

void ListViewControl::onColumnItemChanged( ItemEvent* event )
{
	ColumnItem* item = (ColumnItem*)event->getSource();

	unsigned long index = item->getIndex();
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

ListItem* ListViewControl::addItem( const String& caption, const ulong32 imageIndex )
{
	ListItem* result = NULL;

	result  = new DefaultListItem();
	result->setCaption( caption );
	result->setImageIndex( imageIndex );
	listModel_->addItem( result );

	return result;
}

void ListViewControl::addItem( ListItem* item )
{
	listModel_->addItem( item );
}

ListItem* ListViewControl::insertItem( const ulong32& index, const String& caption, const ulong32 imageIndex )
{
	ListItem* result = NULL;

	result  = new DefaultListItem();
	result->setCaption( caption );
	result->setImageIndex( imageIndex );
	listModel_->insertItem( index, result );

	return result;
}

void ListViewControl::insertItem( const ulong32& index, ListItem* item )
{
	listModel_->insertItem( index, item );
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

long ListViewControl::getDisplayOptions()
{
	if ( NULL == this->listviewPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	return listviewPeer_->getDisplayOptions();
}

void ListViewControl::setDisplayOptions( const long& displayOptions )
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
			ColumnItemClicked.fireEvent( (MouseEvent*)event );
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


/**
$Id$
*/
