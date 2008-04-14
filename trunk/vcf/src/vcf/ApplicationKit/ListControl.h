#ifndef _VCF_LISTCONTROL_H__
#define _VCF_LISTCONTROL_H__
//ListControl.h

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


namespace VCF {

class ListPeer;

#define LISTCONTROL_CLASSID			"5A107182-E309-4D48-8886-F760CF778E5A"



/**
\class ListControl ListControl.h "vcf/ApplicationKit/ListControl.h"
A base class that provides a consistent interface and implementation
for any control class that deals with a list of data held in
a ListModel and a collection of ListItems.

@see ListModel
@see ListItem
@see ListController
*/	
class APPLICATIONKIT_API ListControl : public Control, public ListController {
public:
	DELEGATE(ItemDelegate,ItemSelectionChanged);


	ListControl();

	ListModel* getListModel();

	void setListModel(ListModel * model);


	ImageList* getSmallImageList() {
		return smallImageList_;
	}

	ImageList* getLargeImageList() {
		return largeImageList_;
	}

	ImageList* getStateImageList() {
		return stateImageList_;
	}

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );

	virtual void setStateImageList( ImageList* imageList );		

	ListItem* addItem( const String& caption, const uint32 imageIndex=0 );

	ListItem* insertItem( const uint32& index, const String& caption, const uint32 imageIndex=0 );	


	bool itemExists( const uint32& index );
	ListItem* getItem( const uint32& index );

	void setItem( const uint32& index, ListItem* item );	

	virtual Rect getItemImageRect( const uint32& index );


	virtual void selectItem( const uint32& index );

	virtual Enumerator<uint32>* getSelectedItemsByIndex();

	virtual void rangeSelect( const Rect& selectionRect );

	virtual uint32 getFocusedItem();

	virtual uint32 getSelectedItem();

	virtual bool allowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	void sort( ItemSort* itemSortFunctor );

	virtual uint32 hitTest( const Point& point );

	virtual Rect getItemRect( ListItem* item );

	virtual void insertItemSubItem( ListItem* item, const uint32& index, ListSubItem* subItem ) {}	

	virtual void removeItemSubItem( ListItem* item, ListSubItem* subItem ) {}
	
	virtual bool getItemSubItems( ListItem* item, std::vector<ListSubItem*>& subItems ) {
		return false;
	}

	virtual ListSubItem* getItemSubItem( ListItem* item, const uint32& index ) {
		return NULL;
	}
	virtual uint32 getItemSubItemIndex( ListItem* item, ListSubItem* subItem ) {return -1;}
	virtual uint32 getItemSubItemCount( ListItem* item ){return 0;}
	virtual void itemSelected( ListItem* item );

	virtual void modelChanged( Model* oldModel, Model* newModel );

	virtual void handleEvent( Event* event );	

	virtual void paintItem( GraphicsContext* ctx, const Rect& itemRect, const uint32& index, const DrawUIState& state ) {}
protected:	
	virtual void onItemAdded( ListModelEvent* event );
	virtual void onItemDeleted( ListModelEvent* event );

	virtual void removeSubItemsForItem( ListItem* item );

	ImageList* smallImageList_;
	ImageList* largeImageList_;
	ImageList* stateImageList_;
	ListItem* selectedItem_;

	Array<ListItem*> items_;
	
	ListPeer* listPeer_;
	

	bool internalModelChange_;
	bool inCallbackChange_;
};



};




#endif //_VCF_LISTCONTROL_H__