#ifndef _VCF_LISTVIEWPEER_H__
#define _VCF_LISTVIEWPEER_H__
//ListviewPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class ListItem;




/**
\class ListviewPeer ListviewPeer.h "vcf/ApplicationKit/ListviewPeer.h"
*/

class APPLICATIONKIT_API ListviewPeer : public VCF::Interface {
public:
	virtual ~ListviewPeer(){};	

	virtual bool ensureVisible(ListItem * item, bool partialOK ) = 0;

	virtual void setFocusedItem(ListItem * item) = 0;

	virtual void selectItem(ListItem * item) = 0;

	virtual Rect getItemRect( ListItem* item ) = 0;

	virtual bool isItemSelected(ListItem* item) = 0;

	virtual ListItem* isPtOverItem(Point* point) = 0;

	virtual ListItem* getFocusedItem() = 0;

	virtual ListItem* getSelectedItem() = 0;

	virtual Enumerator<ListItem*>* getSelectedItems() = 0;

	virtual void rangeSelect( Rect* selectionRect ) = 0;
	
	virtual void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone ) = 0;

	virtual double getColumnWidth( const uint32& index ) = 0;

	virtual void sort( ItemSort* itemSortFunctor ) = 0;

	virtual IconStyleType getIconStyle() = 0;

	virtual void setIconStyle( const IconStyleType& iconStyle ) = 0;

	virtual bool getAllowsMultiSelect() = 0;

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect ) = 0;

	virtual IconAlignType getIconAlignment() = 0;

	virtual void setIconAlignment( const IconAlignType& iconAlignType ) = 0;

	virtual bool getAllowLabelEditing() = 0;

	virtual void setAllowLabelEditing( const bool& allowLabelEditing ) = 0;

	virtual void setLargeImageList( ImageList* imageList ) = 0;

	virtual void setSmallImageList( ImageList* imageList ) = 0;

	virtual Rect getItemImageRect( ListItem* item ) = 0;

	virtual int32 getDisplayOptions() = 0;

	virtual void setDisplayOptions( const int32& displayOptions ) = 0;
};

}


#endif // _VCF_LISTVIEWPEER_H__

/**
$Id$
*/
