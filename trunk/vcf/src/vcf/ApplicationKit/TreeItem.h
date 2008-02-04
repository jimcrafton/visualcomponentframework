#ifndef _VCF_TREEITEM_H__
#define _VCF_TREEITEM_H__
//TreeItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__




namespace VCF {

class Color;
class TreeItem;

class APPLICATIONKIT_API TreeSubItem : public Object {
public:
	TreeSubItem( TreeItem* ownerItem ) : data_(NULL){
		ownerItem_ = ownerItem;
	}

	virtual ~TreeSubItem(){};

	void* getData() {
		return data_;
	}

	void setData( void* data );

	String getCaption();

	void setCaption( const String& caption );

	virtual bool canPaint() {
		return false;
	}

	virtual void paint( GraphicsContext* context, Rect* paintRect ) {}

protected:		
	void* data_;
	TreeItem* ownerItem_;
};



class TreeController {
public:
	virtual ~TreeController(){}


	virtual TreeItem* getItemParent( TreeItem* item ) = 0;
	virtual void setItemParent( TreeItem* item, TreeItem* parent ) = 0;

	virtual Rect getItemRect( TreeItem* item ) = 0;

	virtual void addChildItem( TreeItem* item, TreeItem* child ) = 0;
	virtual void removeChildItem( TreeItem* item, TreeItem* child ) = 0;

	virtual TreeItem* getItemFromKey( const TreeModel::Key& key ) = 0;
	virtual void setItemKey( TreeItem* item, const TreeModel::Key& key ) = 0;

	virtual bool getItemChildren( TreeItem* item, std::vector<TreeItem*>& children ) = 0;

	virtual void insertItemSubItem( TreeItem* item, const uint32& index, TreeSubItem* subItem ) = 0;
	virtual void removeItemSubItem( TreeItem* item, TreeSubItem* subItem ) = 0;
	virtual bool getItemSubItems( TreeItem* item, std::vector<TreeSubItem*>& subItems ) = 0;
	virtual TreeSubItem* getItemSubItem( TreeItem* item, const uint32& index ) = 0;
	virtual uint32 getItemSubItemCount( TreeItem* item ) = 0;

	virtual void itemExpanded( TreeItem* item ) = 0;
	virtual void itemSelected( TreeItem* item ) = 0;
};





#define TREEITEM_CLASSID		"3126B223-2819-11d4-B53A-00C04F0196DA"
/**
\class TreeItem TreeItem.h "vcf/ApplicationKit/TreeItem.h" 
*/
class APPLICATIONKIT_API TreeItem : public Item {
public:


	enum TreeItemState {
		tisNone = 0,		
		tisExpanded =	0x0100,
		tisFocused =	0x0200,
	};


	enum TreeItemEvent {
		tieBase = CUSTOM_EVENT_TYPES + 81000,
		tieExpanding,
	};


	TreeItem();

	virtual ~TreeItem();

	virtual void setSelected( const bool& selected );

	TreeModel* getTreeModel() {
		return (TreeModel*) getModel();
	}

	TreeController* getController() {
		return dynamic_cast<TreeController*>( getControl() );
	}

	void setKey( TreeModel::Key val );

	TreeModel::Key getKey() {
		return key_;
	}

	Font* getFont();

	/**
	Indicates that the default font for this item should be used. It's 
	also an indicator that the font is NULL and no attempts at modifications
	have been attempted.
	*/
	bool isFontDefault();

	void setFont( Font* val );

	bool isLeaf() {
		return getTreeModel()->isLeaf( getKey() );
	}

	bool isRoot() {
		return getKey() == TreeModel::RootKey;
	}

	bool isExpanded() {
		return getDisplayState() & tisExpanded ? true : false;
	}

	/* expand this tree item.
	*@param const bool& isExpanded, true if it expands, false to collapse it.
	*/
	void expand( const bool& val );

	/* expand this tree item.and all its children recursively.
	*@param const bool& isExpanded, true to expand, false to collapse.
	*/
	void expandAllChildren( const bool& isExpanded );

	TreeItem* getParent();

	void setParent( TreeItem* parent );

	TreeItem* getNextChildNodeItem();

	TreeItem* getPrevChildNodeItem();
	
	bool getChildren( std::vector<TreeItem*>& children );

	String getCaption();

	uint32 getLevel();

	void setCaption( const String& caption );

	uint32 getChildCount();	

	void addChild( TreeItem* child );

	void removeChild( TreeItem* child );

	void clearChildren();

	int32 getSelectedImageIndex() {
		return selectedImageIndex_;
	}

	void setSelectedImageIndex( const int32& selectedImageIndex );

	int32 getExpandedImageIndex() {
		return expandedImageIndex_;
	}

	void setExpandedImageIndex( const int32& expandedImageIndex );

	virtual int32 getStateImageIndex() const {
		return stateImageIndex_;
	}

	virtual void setStateImageIndex( const int32& index ) {
		stateImageIndex_ = index;
	}



	TreeSubItem* addSubItem( const String& caption, void* data );

	void addSubItem( TreeSubItem* subItem );

	void removeSubItem( const uint32& index );

	bool getSubItems( std::vector<TreeSubItem*>& subItems );

	TreeSubItem* getSubItem( const uint32& index );

	uint32 getSubItemCount();

	virtual void subItemChanged( TreeSubItem* item );

	virtual uint64 sizeOf() const;
protected:
	Font* font_;
	TreeModel::Key key_;
	
	int32 selectedImageIndex_;
	int32 expandedImageIndex_;
	int32 stateImageIndex_;
};




inline void TreeSubItem::setData( void* data )
{
	data_ = data;
	ownerItem_->subItemChanged( this );
}

}; //namespace VCF


#endif // _VCF_TREEITEM_H__

/**
$Id$
*/

