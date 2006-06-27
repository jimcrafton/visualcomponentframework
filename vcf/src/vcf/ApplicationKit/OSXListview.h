#ifndef _VCF_OSXLISTVIEW_H__
#define _VCF_OSXLISTVIEW_H__
//OSXListview.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ListviewPeer.h"


namespace VCF
{

class OSXListview : public OSXControl, public ListviewPeer {
public:
	OSXListview( ListViewControl* listviewControl );

	virtual ~OSXListview();

	virtual void create( Control* owningControl );

	virtual void addItem( ListItem * item );

	virtual void insertItem( const uint32& index, ListItem * item );

	virtual void clear();

	virtual void deleteItem( ListItem* item );

	virtual bool ensureVisible(ListItem * item, bool partialOK );

	virtual void setFocusedItem(ListItem * item);

	virtual void selectItem(ListItem * item);

	virtual Rect getItemRect( ListItem* item );

	virtual bool isItemSelected(ListItem* item);

	virtual ListItem* isPtOverItem(Point* point);

	virtual ListItem* getFocusedItem();

	virtual ListItem* getSelectedItem();

	virtual Enumerator<ListItem*>* getSelectedItems();

	virtual void rangeSelect( Rect* selectionRect );

	virtual void addHeaderColumn( const String& columnName, const double& width );

	virtual void insertHeaderColumn( const uint32& index, const String& columnName, const double& width );

	virtual void deleteHeaderColumn( const uint32& index );

	virtual IconStyleType getIconStyle();

	virtual void setIconStyle( const IconStyleType& iconStyle );

	virtual bool getAllowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	virtual IconAlignType getIconAlignment();

	virtual void setIconAlignment( const IconAlignType& iconAlignType );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone );

	virtual double getColumnWidth( const uint32& index );

	virtual void setColumnName( const uint32& index, const String& columnName );

	virtual String getColumnName( const uint32& index );

	virtual void sort( ItemSort* itemSortFunctor );

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );

	virtual Rect getItemImageRect( ListItem* item );

	virtual int32 getDisplayOptions();

	virtual void setDisplayOptions( const int32& displayOptions );

	virtual OSStatus handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent );
protected:	
	ListViewControl* listviewControl_;
	std::vector<ListItem*> selectedItems_;
	EnumeratorContainer<std::vector<ListItem*>, ListItem*> enumContainer_;	
	
	void onControlModelChanged( Event* e );
	void onListModelItemAdded( Event* e );
	void onListModelItemDeleted( Event* e );
	
	static OSStatus DBItemDataCallback( ControlRef browser, DataBrowserItemID item, 
										DataBrowserPropertyID property, DataBrowserItemDataRef itemData,
										Boolean setValue );
										
	static void DBItemNotificationCallback( ControlRef browser, DataBrowserItemID itemID, 
															DataBrowserItemNotification message);
															
	static void findPtForEachItem ( DataBrowserItemID item, DataBrowserItemState state, void *clientData );
	void addListItems();
};


};


#endif // _VCF_OSXLISTVIEW_H__

/**
$Id$
*/
