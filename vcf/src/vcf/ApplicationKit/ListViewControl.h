#ifndef _VCF_LISTVIEWCONTROL_H__
#define _VCF_LISTVIEWCONTROL_H__
//ListViewControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__




#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__

#ifndef _VCF_COLUMNITEM_H__
#	include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__



namespace VCF {


class ListviewPeer;

class ImageList;




enum ListViewDisplayOptions {
	lvdoDefault = 0,
	lvdoHotTracking = 1,
	lvdoFullRowSelect = 2,
	lvdoGridLines = 4
};




/**
*An enum of icon styles for list views
*/
enum IconStyleType {
	isLargeIcon=0,
	isSmallIcon,
	isList,
	isDetails
};

/**
*An enum of icon alignment types for list views
*/
enum IconAlignType {
	iaNone=0,
	iaTop,
	iaLeft,
	iaAutoArrange
};

static String IconStyleTypeNames[] = { "isLargeIcon",
                                         "isSmallIcon",
										 "isList",
										 "isDetails" };

static String IconAlignTypeNames[] = { "iaNone",
                                         "iaTop",
										 "iaLeft",
										 "iaAutoArrange" };
										 
										 


										 

#define LISTVIEWCONTROL_CLASSID			"ED88C09D-26AB-11d4-B539-00C04F0196DA"


/**
\class ListViewControl ListViewControl.h "vcf/ApplicationKit/ListViewControl.h"
*/
class APPLICATIONKIT_API ListViewControl : public VCF::Control {
public:


	DELEGATE(ItemDelegate,ItemSelectionChanged);
	DELEGATE(MouseDelegate,ColumnItemClicked);

	ListViewControl();

	virtual ~ListViewControl();

	enum {
		COLUMN_MOUSE_EVENT_CLICK = Control::CONTROL_EVENTS_LAST + 200
	};

	/* autoresizing added by Marcello */
	enum AutoSizeType {
		lcatAutoSizeNone = -1,
		lcatAutoSizeColumns = -2,
		lcatAutoSizeHeaders = -3,
		lcatAutoSizeColumnsAndHeaders = -4,
	};

	virtual void setViewModel( Model* model );

	ListModel* getListModel();

	ColumnModel* getColumnModel();

	void setListModel(ListModel * model);

	virtual void paint( GraphicsContext * context );

	virtual ColumnItem* addHeaderColumn( const String& columnName, const double& width=100.0 );

	void addHeaderColumn( ColumnItem* column );

	virtual ColumnItem* insertHeaderColumn( const uint32& index, const String& columnName, const double& width=100.0 );

	void insertHeaderColumn( const uint32& index, ColumnItem* column );

	void deleteHeaderColumn( const uint32& index );

	String getColumnName( const uint32& index );

	void setColumnName( const uint32& index, const String& columnName );

	double getColumnWidth( const uint32& index );

	void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=lcatAutoSizeNone );

	void setColumnsWidth( const double& width, ListViewControl::AutoSizeType type=lcatAutoSizeNone );

	virtual ListItem* addItem( const String& caption, const uint32 imageIndex=0 );

	virtual ListItem* insertItem( const uint32& index, const String& caption, const uint32 imageIndex=0 );	

	IconStyleType getIconStyle();

	void setIconStyle( const IconStyleType& iconStyle );

	bool getAllowsMultiSelect();

	void setAllowsMultiSelect( const bool& allowsMultiSelect );

	IconAlignType getIconAlignment();

	void setIconAlignment( const IconAlignType& iconAlignType );

	bool getAllowLabelEditing();

	void setAllowLabelEditing( const bool& allowLabelEditing );

	void setItemFocused( ListItem* item );

	void init();

	void sort( ItemSort* itemSortFunctor );

	ListItem* isPtOverItem(Point* point);

	ListItem* getFocusedItem();

	ListItem* getSelectedItem();

	/**
	*calling this repeatedly on the same item will toggle the
	*selection state of the item
	*/
	void selectItem( ListItem* item );

	Enumerator<ListItem*>* getSelectedItems();

	void rangeSelect( Rect* selectionRect );

	ImageList* getSmallImageList() {
		return stateImageList_;
	}

	ImageList* getLargeImageList() {
		return largeImageList_;
	}

	ImageList* getStateImageList() {
		return stateImageList_;
	}

	void setLargeImageList( ImageList* imageList );

	void setSmallImageList( ImageList* imageList );

	void setStateImageList( ImageList* imageList );

	Rect getItemImageRect( ListItem* item );

	int32 getDisplayOptions();

	void setDisplayOptions( const int32& displayOptions );

	Rect getItemRect( ListItem* item );

	ListItem* getListItem( const uint32& index );

	void setListItem( const uint32& index, ListItem* item );

	Enumerator<ListItem*>* getItems();

	Enumerator<ColumnItem*>* getColumnItems();

	ColumnItem* getColumnItem( const uint32& index );

	void setColumnItem( const uint32& index, ColumnItem* item );

	virtual void handleEvent( Event* event );
protected:
	//Events
	void onItemPaint( ItemEvent* event );

	void onListModelContentsChanged( ListModelEvent* event );

	void onItemAdded( ListModelEvent* event );

	void onItemDeleted( ListModelEvent* event );

	void onListModelEmptied( ModelEvent* event );

	void onColumnItemAdded( ListModelEvent* event );

	void onColumnItemDeleted( ListModelEvent* event );

	void onColumnItemChanged( ItemEvent* event );

	void onItemSelected( ItemEvent* event );

	ListviewPeer * listviewPeer_;
	ColumnModel* columnModel_;
	IconStyleType iconStyle_;
	ImageList* smallImageList_;
	ImageList* largeImageList_;
	ImageList* stateImageList_;
	ListItem* selectedItem_;

	Array<ListItem*> items_;
	Array<ColumnItem*> columnItems_;
	bool internalModelChange_;
};



};


#endif // _VCF_LISTVIEWCONTROL_H__

/**
$Id$
*/
