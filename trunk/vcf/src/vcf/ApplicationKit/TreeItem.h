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


#define TREEITEM_CLASSID		"3126B223-2819-11d4-B53A-00C04F0196DA"
/**
\class TreeItem TreeItem.h "vcf/ApplicationKit/TreeItem.h" 
*/
class APPLICATIONKIT_API TreeItem : public Item {
public:

	class APPLICATIONKIT_API SubItem : public Object {
	public:
		SubItem( TreeItem* ownerItem ) : data_(NULL){
			ownerItem_ = ownerItem;
		}

		virtual ~SubItem(){};

		void* getData() {
			return data_;
		}

		void setData( void* data ) {
			data_ = data;
			ownerItem_->subItemChanged( this );
		}

		String getCaption() {
			return caption_;
		}

		void setCaption( const String& caption ) {
			caption_ = caption;
			ownerItem_->subItemChanged( this );
		}

		virtual bool canPaint() {
			return false;
		}

		virtual void paint( GraphicsContext* context, Rect* paintRect ) {

		}

	protected:
		String caption_;
		void* data_;
		TreeItem* ownerItem_;
	};


	enum TreeItemState {
		tisNone = 0,		
		tisExpanded =	0x0100,
		tisFocused =	0x0200,
	};


	enum TreeItemEvent {
		tieBase = CUSTOM_EVENT_TYPES + 81000,
		tieExpanding,
	};


	TreeItem(){}

	virtual ~TreeItem(){}

	TreeModel* getTreeModel() {
		return (TreeModel*) getModel();
	}

	TreeModel::Key getKey();

	Color* getTextColor();

	void setTextColor(Color* color);

	void setTextBold(const bool& bold);

	bool getTextBold();

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
	void expand( const bool& val ) {
		if ( val ) {
			setDisplayState( getDisplayState() | tisExpanded );
		}
		else {
			setDisplayState( getDisplayState() & ~tisExpanded );
		}

		Event e(this,tieExpanding);
		getControl()->handleEvent( &e );
	}

	/* expand this tree item.and all its children recursively.
	*@param const bool& isExpanded, true to expand, false to collapse.
	*/
	void expandAllChildren( const bool& isExpanded );

	TreeItem* getParent();

	void setParent( TreeItem* parent );

	TreeItem* getNextChildNodeItem();

	TreeItem* getPrevChildNodeItem();

	TreeItem* getChild( const TreeModel::Key& key );

	String getCaption();

	uint32 getLevel();

	void setCaption( const String& caption );

	uint32 getChildCount();	

	void addChild( TreeItem* child );

	void deleteChild( TreeItem* child );

	void clearChildren();

	int32 getSelectedImageIndex();

	void setSelectedImageIndex( const int32& selectedImageIndex );

	int32 getExpandedImageIndex();

	void setExpandedImageIndex( const int32& expandedImageIndex );

	void addSubItem( const String& caption, void* data );

	void addSubItem( SubItem* subItem );

	void removeSubItem( const uint32& index );

	virtual Enumerator<SubItem*>* getSubItems();

	virtual SubItem* getSubItem( const uint32& index );

	virtual uint32 getSubItemCount();

	virtual void subItemChanged( SubItem* item );

protected:
	Color textColor_;
	
	int32 selectedImageIndex_;
	int32 expandedImageIndex_;
	int32 stateImageIndex_;
};


}; //namespace VCF


#endif // _VCF_TREEITEM_H__

/**
$Id$
*/
