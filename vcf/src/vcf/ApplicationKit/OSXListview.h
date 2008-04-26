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

	virtual void selectItem( const uint32& index );

	virtual uint32 getSelectedItem();

	virtual void setFocusedItem( const uint32& index );

	virtual uint32 getFocusedItem();

	virtual bool isItemSelected( const uint32& index );

	virtual Rect getItemRect( const uint32& index );	

	virtual Rect getItemImageRect( const uint32& index );

	virtual uint32 hitTest( const Point& point );	

	virtual Enumerator<uint32>* getSelectedItems();

	virtual void rangeSelect( const Rect& selectionRect );	

	virtual bool allowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );	

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );


	virtual bool ensureVisible(const uint32& index, bool partialOK );
	
	virtual void setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type );

	virtual double getColumnWidth( const uint32& index );

	virtual TextAlignmentType getColumnTextAlignment( const uint32& index );

	virtual void setColumnTextAlignment( const uint32& index, const TextAlignmentType& val );

	virtual IconStyleType getIconStyle();

	virtual void setIconStyle( const IconStyleType& iconStyle );

	virtual IconAlignType getIconAlignment();

	virtual void setIconAlignment( const IconAlignType& iconAlignType );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );		

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
