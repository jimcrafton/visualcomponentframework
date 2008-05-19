//OSXListview.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/ListViewControl.h"

#include "vcf/ApplicationKit/OSXControl.h"

#include "vcf/ApplicationKit/OSXListview.h"

#define OSX_LISTVIEW_CTRL_PRIMARY_COL		'PRIM'



/*


struct ForEachData {
	OSXListview* listview;
};


struct FindPtForItemData : public ForEachData {
	VCF::Rect rect;
	VCF::Point* pt;
};

*/


/*
void OSXListview::create( Control* owningControl )
{
	::Rect r;
	r.left = 0;
	r.top = 0;
	r.right = 0;
	r.bottom = 0;
	
	OSStatus err;
	if ( noErr == CreateDataBrowserControl( NULL, &r, kDataBrowserListView, &hiView_ ) ) {
		DataBrowserCallbacks callbacks;
		callbacks.version = kDataBrowserLatestCallbacks;
		err = InitDataBrowserCallbacks( &callbacks ); 	
		callbacks.u.v1.itemDataCallback = OSXListview::DBItemDataCallback;
		callbacks.u.v1.itemNotificationCallback = OSXListview::DBItemNotificationCallback;
		
		err = SetDataBrowserCallbacks( hiView_, &callbacks );
		
		
		//create initial column (DataBrowser doesn't work without at least one column
		DataBrowserListViewColumnDesc col;
		col.propertyDesc.propertyID = OSX_LISTVIEW_CTRL_PRIMARY_COL;
		col.propertyDesc.propertyType =  kDataBrowserTextType;
		col.propertyDesc.propertyFlags =  kDataBrowserListViewSelectionColumn;
		
		col.headerBtnDesc.version = kDataBrowserListViewLatestHeaderDesc;
		col.headerBtnDesc.minimumWidth = 10;
		col.headerBtnDesc.maximumWidth = 200;
		col.headerBtnDesc.titleOffset = 0;
		col.headerBtnDesc.titleString = NULL;
		col.headerBtnDesc.initialOrder = kDataBrowserOrderIncreasing;
		col.headerBtnDesc.btnFontStyle.flags = 0;
		col.headerBtnDesc.btnFontStyle.font = 0;
		col.headerBtnDesc.btnFontStyle.size = 0;
		col.headerBtnDesc.btnFontStyle.style = 0;
		col.headerBtnDesc.btnFontStyle.mode = 0;
		col.headerBtnDesc.btnFontStyle.just = 0;
		
		col.headerBtnDesc.btnContentInfo.contentType = kControlContentTextOnly;
		
		AddDataBrowserListViewColumn( hiView_, &col, 0 );
		
		SetDataBrowserSelectionFlags( hiView_, kDataBrowserSelectOnlyOne | kDataBrowserResetSelection );
		
		SetDataBrowserTableViewHiliteStyle( hiView_, kDataBrowserTableViewFillHilite );
		
		OSXControl* thisPtr = this;
		SetControlProperty( hiView_, 
							VCF_PROPERTY_CREATOR, 
							VCF_PROPERTY_CONTROL_VAL, 
							sizeof(thisPtr), 
							&thisPtr );
							
		err = OSXControl::installStdControlHandler();
							
		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("InstallEventHandler failed for OSXTree!") );
		}
		EventHandler* ev = 
			new ClassProcedure1<Event*,OSXListview>( this, &OSXListview::onControlModelChanged, "OSXListview::onControlModelChanged" );					
		
		owningControl->ControlModelChanged += ev;
				
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("CreateDataBrowserControl failed to create view!") );
	}
}


OSStatus OSXListview::DBItemDataCallback( ControlRef browser, DataBrowserItemID item, 
										DataBrowserPropertyID property, DataBrowserItemDataRef itemData,
										Boolean setValue )
{
	OSStatus err = noErr;
	
	if ( !setValue ) {
		switch ( property ) {

			case OSX_LISTVIEW_CTRL_PRIMARY_COL : {
				ListItem* listItem	 = (ListItem*)item;
				CFTextString tmp;
				tmp = listItem->getCaption();
				SetDataBrowserItemDataText( itemData, tmp );
			}
			break;
			
			case kDataBrowserItemIsSelectableProperty : {
				err = SetDataBrowserItemDataBooleanValue( itemData, true );
			}
			break;
			
			case kDataBrowserItemIsContainerProperty : {
				SetDataBrowserItemDataBooleanValue( itemData, false );				
			}
			break;
			
			default: {
				err = errDataBrowserPropertyNotSupported;				
			}
			break;
		}		
	}
	else {
		err = errDataBrowserPropertyNotSupported;
	}
	
	return err;
}


void OSXListview::DBItemNotificationCallback( ControlRef browser, DataBrowserItemID itemID, 
															DataBrowserItemNotification message)
{
	
    switch (message)
    {
        case kDataBrowserContainerOpened:  {		
              
        }
		break;
		   
		case kDataBrowserItemSelected : {
			SetDataBrowserSelectedItems( browser, 1, &itemID, kDataBrowserItemsAdd );
		}
		break;
		
		case kDataBrowserItemDeselected : {
			SetDataBrowserSelectedItems( browser, 1, &itemID, kDataBrowserItemsRemove );		
		}
		break;
		
    }

}


void OSXListview::addItem( ListItem * item )
{
	//unsigned int index = item->getIndex();
	
	DataBrowserItemID dbItem = (DataBrowserItemID)item;
	AddDataBrowserItems( hiView_, kDataBrowserNoItem, 1, &dbItem, kDataBrowserItemNoProperty );
}

void OSXListview::insertItem( const uint32& index, ListItem * item )
{

}

void OSXListview::clear()
{
	RemoveDataBrowserItems( hiView_, kDataBrowserNoItem, 0, NULL, kDataBrowserItemNoProperty );
}

void OSXListview::deleteItem( ListItem* item )
{
	//unsigned int index = item->getIndex();
	DataBrowserItemID dbItem = (DataBrowserItemID)item;
	
	RemoveDataBrowserItems( hiView_, kDataBrowserNoItem, 1, &dbItem, kDataBrowserItemNoProperty );
}

bool OSXListview::ensureVisible(ListItem * item, bool partialOK )
{
	bool result = false;
	
	return result;
}

void OSXListview::setFocusedItem(ListItem * item)
{
	
}

void OSXListview::selectItem(ListItem * item)
{
	
}

VCF::Rect OSXListview::getItemRect( ListItem* item )
{	
	VCF::Rect result;
	UInt32 columns = 0;
	GetDataBrowserTableViewColumnCount( hiView_, &columns );
	DataBrowserTableViewColumnID colID = 0;
	DataBrowserItemID itemID = (DataBrowserItemID)item;
	::Rect itemBounds;
	for (UInt32 col=0;col<columns;col++ ) {
		GetDataBrowserTableViewColumnProperty( hiView_, col, &colID );
		GetDataBrowserItemPartBounds( hiView_, itemID, colID, kDataBrowserPropertyEnclosingPart, &itemBounds );
		if ( col == 0 ) {
			result.left_ = itemBounds.left;
			result.top_ = itemBounds.top;
			result.right_ = itemBounds.right;
			result.bottom_ = itemBounds.bottom;
		}
		else {
			result.right_ = itemBounds.right;
			result.bottom_ = itemBounds.bottom;		
		}
	}	
		
	return result;
}

bool OSXListview::isItemSelected(ListItem* item)
{
	bool result = false;
	
	return result;
}

void OSXListview::findPtForEachItem ( DataBrowserItemID item, DataBrowserItemState state, void *clientData )
{
	//FindPtForItemData* data = (FindPtForItemData*)clientData;
	
	::Rect itemBounds;
	//DataBrowserTableViewColumnID colID = 0;
	//GetDataBrowserItemPartBounds( data->listview->hiView_, item, colID, kDataBrowserPropertyEnclosingPart, &itemBounds );
}

ListItem* OSXListview::isPtOverItem( Point* point )
{
	ListItem* result = NULL;
		
	FindPtForItemData data;
	data.listview = this;
	data.pt = point;	
	if ( noErr == ForEachDataBrowserItem( hiView_, kDataBrowserNoItem, false, 0, OSXListview::findPtForEachItem, &data ) ) {
		//result = data.rect;
	}	
	
	return result;
}

ListItem* OSXListview::getFocusedItem()
{
	ListItem* result = NULL;

	
	return result;
}

ListItem* OSXListview::getSelectedItem()
{
	ListItem* result = NULL;
	Handle items = NewHandle(0);
	
	if ( noErr == GetDataBrowserItems( hiView_, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, items ) ) {
 		int count = GetHandleSize(items)/sizeof(DataBrowserItemID);
		
		if ( count > 0 ) {
			HLock( items );
			DataBrowserItemID* item = *((DataBrowserItemID**)items);
		
			result = (ListItem*)(*item);
		
			HUnlock( items );
		}
	}
	DisposeHandle( items );
	return result;
}

Enumerator<ListItem*>* OSXListview::getSelectedItems()
{
	ListItem* item = NULL;
	
	return NULL;
}

void OSXListview::rangeSelect( Rect* selectionRect )
{

}

void OSXListview::addHeaderColumn( const String& columnName, const double& width )
{
	UInt32 columnCount = 0;
	GetDataBrowserTableViewColumnCount( hiView_, &columnCount );
	
	insertHeaderColumn( columnCount, columnName, width );
}

void OSXListview::insertHeaderColumn( const uint32& index, const String& columnName, const double& width )
{
	if ( index == 0 ) {
	
	}
	else {
		DataBrowserListViewColumnDesc col;
		col.propertyDesc.propertyID = OSX_LISTVIEW_CTRL_PRIMARY_COL + 1;
		col.propertyDesc.propertyType =  kDataBrowserTextType;
		col.propertyDesc.propertyFlags =  kDataBrowserListViewSelectionColumn;
		
		col.headerBtnDesc.version = kDataBrowserListViewLatestHeaderDesc;
		col.headerBtnDesc.minimumWidth = 10;
		col.headerBtnDesc.maximumWidth = (UInt16)width;
		col.headerBtnDesc.titleOffset = 0;
		
		CFTextString tmp(columnName);
		
		col.headerBtnDesc.titleString = tmp;
		col.headerBtnDesc.initialOrder = kDataBrowserOrderIncreasing;
		col.headerBtnDesc.btnFontStyle.flags = 0;
		col.headerBtnDesc.btnFontStyle.font = 0;
		col.headerBtnDesc.btnFontStyle.size = 0;
		col.headerBtnDesc.btnFontStyle.style = 0;
		col.headerBtnDesc.btnFontStyle.mode = 0;
		col.headerBtnDesc.btnFontStyle.just = 0;
		
		col.headerBtnDesc.btnContentInfo.contentType = kControlContentTextOnly;
		
		AddDataBrowserListViewColumn( hiView_, &col, index );
	}
}

void OSXListview::deleteHeaderColumn( const uint32& index )
{
	//ListModel* listModel = listviewControl_->getListModel();
	//ListItem* item = listModel->getItemFromIndex( index );
	DataBrowserTableViewColumnID columnId = OSX_LISTVIEW_CTRL_PRIMARY_COL + index;
	RemoveDataBrowserTableViewColumn( hiView_, columnId );
}

IconStyleType OSXListview::getIconStyle()
{
	return IconStyleType(0);
}

void OSXListview::setIconStyle( const IconStyleType& iconStyle )
{
	
}

bool OSXListview::getAllowsMultiSelect()
{
	DataBrowserSelectionFlags flags = 0;
	if ( noErr == GetDataBrowserSelectionFlags( hiView_, &flags ) ) {
		return (flags & kDataBrowserSelectOnlyOne) ? false : true;
	}
	return false;
}

void OSXListview::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	DataBrowserSelectionFlags flags = 0;
	if ( noErr == GetDataBrowserSelectionFlags( hiView_, &flags ) ) {	
		if ( allowsMultiSelect ) {
			flags |= kDataBrowserDragSelect;
			flags &= ~kDataBrowserSelectOnlyOne;
		}
		else {
			flags |= kDataBrowserDragSelect | kDataBrowserSelectOnlyOne;
		}
		SetDataBrowserSelectionFlags( hiView_, flags );
	}
}

IconAlignType OSXListview::getIconAlignment()
{
	return IconAlignType(0);
}

void OSXListview::setIconAlignment( const IconAlignType& iconAlignType )
{
	
}

bool OSXListview::getAllowLabelEditing()
{
	return false;
}

void OSXListview::setAllowLabelEditing( const bool& allowLabelEditing )
{
	
}





void OSXListview::setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type )
{
	DataBrowserTableViewColumnID columnId = OSX_LISTVIEW_CTRL_PRIMARY_COL + index;
	SetDataBrowserTableViewNamedColumnWidth( hiView_, columnId, (UInt16)width );
}

double OSXListview::getColumnWidth( const uint32& index )
{
	double result = 0.0;
	
	DataBrowserTableViewColumnID columnId = OSX_LISTVIEW_CTRL_PRIMARY_COL + index;
	UInt16 width = 0;
	
	if ( noErr == GetDataBrowserTableViewNamedColumnWidth( hiView_, columnId, &width ) ) {
		result = width;
	}
	return result;
}

void OSXListview::setColumnName( const uint32& index, const String& columnName )
{
	DataBrowserTableViewColumnID columnId = OSX_LISTVIEW_CTRL_PRIMARY_COL + index;
	DataBrowserListViewHeaderDesc col;	
	memset( &col, 0, sizeof(col) );
	col.version = kDataBrowserListViewLatestHeaderDesc;	
	
	if ( noErr == GetDataBrowserListViewHeaderDesc( hiView_, columnId, &col ) ) {
		CFTextString tmp(columnName);
		col.titleString = tmp;
		SetDataBrowserListViewHeaderDesc( hiView_, columnId, &col );
	}	
}

String OSXListview::getColumnName( const uint32& index )
{
	String result;	

	DataBrowserTableViewColumnID columnId = OSX_LISTVIEW_CTRL_PRIMARY_COL + index;
	DataBrowserListViewHeaderDesc col;	
	memset( &col, 0, sizeof(col) );
	col.version = kDataBrowserListViewLatestHeaderDesc;	
	
	if ( noErr == GetDataBrowserListViewHeaderDesc( hiView_, columnId, &col ) ) {
		CFTextString tmp;
		tmp = col.titleString;
		result = tmp;
	}
	
	return result;
}


void OSXListview::sort( ItemSort* itemSortFunctor )
{
	
}


void OSXListview::setLargeImageList( ImageList* imageList )
{
	
}

void OSXListview::setSmallImageList( ImageList* imageList )
{
	
}

VCF::Rect OSXListview::getItemImageRect( ListItem* item )
{
	VCF::Rect result;
	
	UInt32 columns = 0;
	GetDataBrowserTableViewColumnCount( hiView_, &columns );
	DataBrowserTableViewColumnID colID = 0;
	DataBrowserItemID itemID = (DataBrowserItemID)item;
	::Rect itemBounds;
	
	GetDataBrowserTableViewColumnProperty( hiView_, 0, &colID );
	GetDataBrowserItemPartBounds( hiView_, itemID, colID, kDataBrowserPropertyIconPart, &itemBounds );
	
	result.left_ = itemBounds.left;
	result.top_ = itemBounds.top;
	result.right_ = itemBounds.right;
	result.bottom_ = itemBounds.bottom;
	
	return result;
}

int32 OSXListview::getDisplayOptions()
{
	int32 result = lvdoDefault;
	

	return result;
}

void OSXListview::setDisplayOptions( const int32& displayOptions )
{
	
}

void OSXListview::addListItems()
{
	ListModel* listModel = listviewControl_->getListModel();
	
	uint32 count = listModel->getCount();
	int i = 0;
	DataBrowserItemID* dbItems = new DataBrowserItemID[count];
	
	Enumerator<ListItem*>* items = listModel->getItems();
	while ( items->hasMoreElements() ) {
		ListItem* item = items->nextElement();
		dbItems[i] = (DataBrowserItemID)item;
		
		i++;
	}
	
	AddDataBrowserItems( hiView_, kDataBrowserNoItem, count, dbItems, kDataBrowserItemNoProperty );
	
	delete [] dbItems;
}

OSStatus OSXListview::handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	OSStatus result = eventNotHandledErr;
	
    UInt32 whatHappened = GetEventKind (theEvent);
	TCarbonEvent event( theEvent );
	
	switch ( GetEventClass( theEvent ) )  {				 
		case kEventClassControl : {
			switch( whatHappened ) {
				case kEventControlDraw : {
					result = CallNextEventHandler( nextHandler, theEvent );
				}
				break;
				
				default : {
					result = OSXControl::handleOSXEvent( nextHandler, theEvent );
				}	
				break;
			}
		}
		break;
		
		default : {
			result = OSXControl::handleOSXEvent( nextHandler, theEvent );
		}	
		break;
	}
	
	return result;			
}

void OSXListview::onControlModelChanged( Event* e )
{
	addListItems();
	
	EventHandler* ev = (EventHandler*) getCallback( "OSXListview::onListModelItemAdded" );
	if ( NULL == ev ) {
		ev = new ClassProcedure1<Event*,OSXListview>( this, &OSXListview::onListModelItemAdded, "OSXListview::onListModelItemAdded" );
	}	
	
	ListModel* listModel = listviewControl_->getListModel();
	listModel->addItemAddedHandler( ev );
	
	ev = (EventHandler*)getCallback( "OSXListview::onListModelItemDeleted" );
	if ( NULL == ev ) {
		ev = new ClassProcedure1<Event*,OSXListview>( this, &OSXListview::onListModelItemDeleted, "OSXListview::onListModelItemDeleted" );
	}
	
	listModel->addItemDeletedHandler( ev );
}

void OSXListview::onListModelItemAdded( Event* e )
{
	ListModelEvent* ev = (ListModelEvent*)e;
	ListItem* item = ev->getListItem();

	unsigned int index = item->getIndex();
	
	DataBrowserItemID dbItem = (DataBrowserItemID)item;
	AddDataBrowserItems( hiView_, kDataBrowserNoItem, 1, &dbItem, kDataBrowserItemNoProperty );	
}

void OSXListview::onListModelItemDeleted( Event* e )
{
	ListModelEvent* ev = (ListModelEvent*)e;
	ListItem* item = ev->getListItem();

	unsigned int index = item->getIndex();
	DataBrowserItemID dbItem = (DataBrowserItemID)item;
	
	RemoveDataBrowserItems( hiView_, kDataBrowserNoItem, 1, &dbItem, kDataBrowserItemNoProperty );
}

*/

namespace VCF {

OSXListview::OSXListview( ListViewControl* listviewControl ):
	OSXControl( listviewControl ),
	listviewControl_( listviewControl )
{

}

OSXListview::~OSXListview()
{
	
}



void OSXListview::create( Control* owningControl )
{

}

void OSXListview::selectItem( const uint32& index )
{

}

uint32 OSXListview::getSelectedItem()
{
	return 0;
}

void OSXListview::setFocusedItem( const uint32& index )
{

}

uint32 OSXListview::getFocusedItem()
{
	return 0;
}

bool OSXListview::isItemSelected( const uint32& index )
{
	return false;
}

Rect OSXListview::getItemRect( const uint32& index )
{
	return Rect();
}

Rect OSXListview::getItemImageRect( const uint32& index )
{
	return Rect();
}

uint32 OSXListview::hitTest( const Point& point )
{
	return 0;
}

Enumerator<uint32>* OSXListview::getSelectedItems()
{
	return selectedItems_.getEnumerator();
}

void OSXListview::rangeSelect( const Rect& selectionRect )
{

}

bool OSXListview::allowsMultiSelect()
{
	return false;
}

void OSXListview::setAllowsMultiSelect( const bool& allowsMultiSelect )
{

}

void OSXListview::setLargeImageList( ImageList* imageList )
{

}

void OSXListview::setSmallImageList( ImageList* imageList )
{

}


bool OSXListview::ensureVisible(const uint32& index, bool partialOK )
{
	return false;
}
	
void OSXListview::setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type )
{

}

double OSXListview::getColumnWidth( const uint32& index )
{
	return 0.0;
}

TextAlignmentType OSXListview::getColumnTextAlignment( const uint32& index )
{
	return TextAlignmentType();
}

void OSXListview::setColumnTextAlignment( const uint32& index, const TextAlignmentType& val )
{

}

IconStyleType OSXListview::getIconStyle()
{
	return IconStyleType();
}

void OSXListview::setIconStyle( const IconStyleType& iconStyle )
{

}

IconAlignType OSXListview::getIconAlignment()
{
	return IconAlignType();
}

void OSXListview::setIconAlignment( const IconAlignType& iconAlignType )
{

}

bool OSXListview::getAllowLabelEditing()
{
	return false;
}

void OSXListview::setAllowLabelEditing( const bool& allowLabelEditing )
{

}

int32 OSXListview::getDisplayOptions()
{
	return 0;
}	

void OSXListview::setDisplayOptions( const int32& displayOptions )
{

}

};


/**
$Id$
*/
