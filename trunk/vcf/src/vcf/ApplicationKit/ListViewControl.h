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



#ifndef _VCF_LISTCONTROL_H__
#	include "vcf/ApplicationKit/ListControl.h"
#endif // _VCF_LISTCONTROL_H__



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
class APPLICATIONKIT_API ListViewControl : public ListControl, public ColumnController {
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

	ColumnModel* getColumnModel();

	virtual void paint( GraphicsContext * context );

	ColumnItem* addHeaderColumn( const String& columnName, const double& width=100.0 );

	void addHeaderColumn( ColumnItem* column );

	ColumnItem* insertHeaderColumn( const uint32& index, const String& columnName, const double& width=100.0 );

	Enumerator<ColumnItem*>* getColumnItems();

	ColumnItem* getColumnItem( const uint32& index );

	void setColumnItem( const uint32& index, ColumnItem* item );

	void insertHeaderColumn( const uint32& index, ColumnItem* column );

	void deleteHeaderColumn( const uint32& index );

	String getColumnName( const uint32& index );

	void setColumnName( const uint32& index, const String& columnName );

	double getColumnWidth( const uint32& index );

	void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=lcatAutoSizeNone );

	void setColumnsWidth( const double& width, ListViewControl::AutoSizeType type=lcatAutoSizeNone );	


	virtual double getItemWidth( ColumnItem* item );
	virtual void setItemWidth( ColumnItem* item, const double& val );

	virtual TextAlignmentType getItemTextAlignment( ColumnItem* item );
	virtual void setItemTextAlignment( ColumnItem* item, const TextAlignmentType& val );



	IconStyleType getIconStyle();

	void setIconStyle( const IconStyleType& iconStyle );	

	IconAlignType getIconAlignment();

	void setIconAlignment( const IconAlignType& iconAlignType );

	bool getAllowLabelEditing();

	void setAllowLabelEditing( const bool& allowLabelEditing );	
	
	ImageList* getStateImageList() {
		return stateImageList_;
	}

	void setStateImageList( ImageList* imageList );	

	int32 getDisplayOptions();

	void setDisplayOptions( const int32& displayOptions );	

	ListItem* addItem( const String& caption, const uint32 imageIndex=0 );

	ListItem* insertItem( const uint32& index, const String& caption, const uint32 imageIndex=0 );	

	ListItem* getItem( const uint32& index );

	void setItem( const uint32& index, ListItem* item );

	Enumerator<ListItem*>* getItems();

	
	virtual void handleEvent( Event* event );

	
	virtual void insertItemSubItem( ListItem* item, const uint32& index, ListSubItem* subItem );
	virtual void removeItemSubItem( ListItem* item, ListSubItem* subItem );
	virtual bool getItemSubItems( ListItem* item, std::vector<ListSubItem*>& subItems );
	virtual ListSubItem* getItemSubItem( ListItem* item, const uint32& index );
	virtual uint32 getItemSubItemIndex( ListItem* item, ListSubItem* subItem );
	virtual uint32 getItemSubItemCount( ListItem* item );
	
protected:
	//Events
	//void onItemPaint( ItemEvent* event );

	//void onListModelContentsChanged( ListModelEvent* event );

	//void onItemAdded( ListModelEvent* event );

	//void onItemDeleted( ListModelEvent* event );

	//void onListModelEmptied( ModelEvent* event );

	void onColumnItemAdded( ListModelEvent* event );

	void onColumnItemDeleted( ListModelEvent* event );

	void onColumnItemChanged( ItemEvent* event );

	//void onItemSelected( ItemEvent* event );

	virtual void removeSubItemsForItem( ListItem* item );

	ListviewPeer * listviewPeer_;
	ColumnModel* columnModel_;
	IconStyleType iconStyle_;
		
	Array<ColumnItem*> columnItems_;

	typedef std::multimap<ListItem*,ListSubItem*> SubItemMap;
	typedef std::pair<SubItemMap::iterator,SubItemMap::iterator> SubItemIteratorPair;
	typedef SubItemMap::value_type SubItemPair;
	SubItemMap subItems_;
};



};


#endif // _VCF_LISTVIEWCONTROL_H__

/**
$Id$
*/
