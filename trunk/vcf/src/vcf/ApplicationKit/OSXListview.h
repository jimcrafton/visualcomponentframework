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

	virtual void insertItem( const unsigned long& index, ListItem * item );

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

	virtual void insertHeaderColumn( const unsigned long& index, const String& columnName, const double& width );

	virtual void deleteHeaderColumn( const unsigned long& index );

	virtual IconStyleType getIconStyle();

	virtual void setIconStyle( const IconStyleType& iconStyle );

	virtual bool getAllowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	virtual IconAlignType getIconAlignment();

	virtual void setIconAlignment( const IconAlignType& iconAlignType );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual void setColumnWidth( const unsigned long& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone );

	virtual double getColumnWidth( const unsigned long& index );

	virtual void setColumnName( const unsigned long& index, const String& columnName );

	virtual String getColumnName( const unsigned long& index );

	virtual void sort( ItemSort* itemSortFunctor );

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );

	virtual Rect getItemImageRect( ListItem* item );

	virtual long getDisplayOptions();

	virtual void setDisplayOptions( const long& displayOptions );

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


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.2.1  2005/11/27 23:55:44  ddiego
*more osx updates.
*
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.4  2005/07/07 23:28:58  ddiego
*last osx checkins before release - not complete :(
*
*Revision 1.1.2.3  2005/06/30 02:29:12  ddiego
*more osx work on list view
*
*Revision 1.1.2.2  2005/06/29 03:46:13  ddiego
*more osx tree and list coding.
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*/


#endif // _VCF_OSXLISTVIEW_H__


