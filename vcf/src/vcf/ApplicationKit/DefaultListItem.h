#ifndef _VCF_DEFAULTLISTITEM_H__
#define _VCF_DEFAULTLISTITEM_H__
//DefaultListItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__


namespace VCF{

class ListModel;

#define DEFAULTLISTITEM_CLASSID		"ED88C0AC-26AB-11d4-B539-00C04F0196DA"
/**
\class DefaultListItem DefaultListItem.h "vcf/ApplicationKit/DefaultListItem.h"
*/
class APPLICATIONKIT_API DefaultListItem : public ListItem {
public:

	DefaultListItem();

	DefaultListItem( ListModel* model );

	virtual ~DefaultListItem();

	void init();

    virtual bool containsPoint( Point * pt );

    virtual uint32 getIndex();

	virtual void setIndex( const uint32& index );

    virtual void* getData();

	virtual void setData( void* data );

	virtual String getCaption();

	virtual void setCaption( const String& caption );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual bool isSelected();

	virtual void setSelected( const bool& selected );

	virtual int32 getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const int32& imageIndex );

	virtual Rect* getBounds() {
		return &bounds_;
	}

	virtual bool canPaint() {
		return true;
	}

	virtual void addSubItem( const String& caption, void* data );

	virtual void addSubItem( ListItem::SubItem* subItem );

	virtual void removeSubItem( const uint32& index );

	virtual Enumerator<ListItem::SubItem*>* getSubItems();

	virtual ListItem::SubItem* getSubItem( const uint32& index );

	virtual uint32 getSubItemCount();

	virtual void subItemChanged( ListItem::SubItem* item );

	virtual void setBounds( Rect* bounds );

	/**
	*not supported
	*/
	virtual int32 getStateImageIndex(){
		return -1;
	};

	/**
	*not supported
	*/
	virtual void setStateImageIndex( const int32& index ){}

private:	
	void* data_;
	uint32 index_;
	Rect bounds_;	
	bool selected_;
	int32 imageIndex_;
	std::vector<SubItem*> subItems_;
	EnumeratorContainer<std::vector<SubItem*>,SubItem*> subItemsContainer_;
};

};


#endif // _VCF_DEFAULTLISTITEM_H__

/**
$Id$
*/
