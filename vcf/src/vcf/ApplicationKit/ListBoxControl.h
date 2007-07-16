#ifndef _VCF_LISTBOXCONTROL_H__
#define _VCF_LISTBOXCONTROL_H__
//ListBoxControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */



#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__

#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__



namespace VCF{

class ImageList;



#define LISTBOXCONTROL_CLASSID		"ED88C0A5-26AB-11d4-B539-00C04F0196DA"
/**
\class ListBoxControl ListBoxControl.h "vcf/ApplicationKit/ListBoxControl.h"
*/
class APPLICATIONKIT_API ListBoxControl : public CustomControl {

public:
	enum ListBoxControlEvents {
		lbeItemStateChangeRequested = CUSTOM_EVENT_TYPES + ITEM_CONST + 100
	};

	DELEGATE(ItemDelegate,SelectionChanged);
	DELEGATE(ItemDelegate,ItemStateChangeRequested);

	ListBoxControl();

	ListBoxControl( ListModel* listModel );
	virtual ~ListBoxControl();

	void init();

	ListModel* getListModel();

	void setListModel(ListModel * model);

	virtual void rangeSelect( const bool & isSelected, ListItem * first, ListItem * last );

	void onListModelContentsChanged( ListModelEvent* event );

	void onItemAdded( ListModelEvent* event );

	void onItemDeleted( ListModelEvent* event );

	virtual void paint( GraphicsContext* ctx );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseClick( MouseEvent* event );

	virtual void mouseDblClick( MouseEvent* event );

	virtual void keyDown( KeyboardEvent* event );

	virtual void keyUp( KeyboardEvent* event );

	virtual void keyPressed( KeyboardEvent* event );

	double getDefaultItemHeight() {
		return defaultItemHeight_;
	}

	void setDefaultItemHeight( const double& defaultItemHeight );

	bool getAllowsMultiSelect() {
		return allowsMultiSelect_;
	}

	/**
	*Enables/disables the ability to have more than 1 item selected at any time.
	*Item pointers are automatically added and removed from the selectedItems_ container
	*as they are selected and deselected, respectively.
	*/
	void setAllowsMultiSelect( const bool& allowsMultiSelect );

	bool getAllowsExtendedSelect() {
		return allowsExtendedSelect_;
	}

	/**
	*Enables/disables the ability to have extended selection functionality, by
	*handling Ctrl + mouseDown and Shift + mouseDown.
	*Item pointers are automatically added and removed from the selectedItems_ container
	*as they are selected and deselected, respectively.
	*
	*If you set allowsExtendedSelect to true, allowsMultiSelect_ is automatically set to true
	*for you. Therefore, don't forget to set allowsMultiSelect to false if you want to switch 
	*from extended selection behaviour to single selection behavior. 
	*/
	void setAllowsExtendedSelect (const bool& allowsExtendedSelect);

	Enumerator<ListItem*>* getSelectedItems();

	ListItem* getSelectedItem() {
		return singleSelectedItem_;
	}

	void setSelectedItem( ListItem* selectedItem );

	/**
	*Sets the spacing between the innermost-edge of the left border and the 
	*beginning of the Item captions when scrolled all the way to the left.
	*Default value is currently 2.0	
	*/
	void setLeftGutter(const double& leftgutter);
	
	double getLeftGutter(){ 
		return leftGutter_;
	}

	/**
	*Sets the spacing between the innermost-edge of the right border and the 
	*end of the longest Item caption when scrolled all the way to the right.
	*Default value is currently 2.0
	*/
	void setRightGutter(const double& rightgutter);
	
	double getRightGutter(){ 
		return rightGutter_;
	}

	void setTextBounded( const bool& istextbounded );

	void deselectAllItems();
	
	void eraseFromSelectedItems( ListItem* item );

	/**
	*sets the scrollable for the listbox control, and sets
	*it for a discrete scrolling, item by item.
	*/
	virtual void setScrollable( Scrollable* scrollable );


	ImageList* getImageList() {
		return imageList_;
	}

	ImageList* getStateImageList() {
		return stateImageList_;
	}

	void setImageList( ImageList* imageList );

	void setStateImageList( ImageList* stateImageList );

	bool stateHitTest( Point* point, ListItem* item );
protected:
	ListModel* listModel_;
	double defaultItemHeight_;
	double currentMaxWidth_;
	double currentMaxHeight_;
	double leftGutter_;
	double rightGutter_;
	bool textBounded_;
	bool allowsMultiSelect_;
	bool allowsExtendedSelect_;
	ListItem* singleSelectedItem_;
	std::vector<ListItem*> selectedItems_;
	EnumeratorContainer<std::vector<ListItem*>,ListItem*> selectedItemsContainer_;
	ImageList* imageList_;
	ImageList* stateImageList_;
	double stateItemIndent_;

	virtual void destroy();

	void paintSelectionRect( GraphicsContext* ctx, Rect* rect, ListItem* item );

	ListItem* findSingleSelectedItem( Point* pt );

	void selectionChanged( ListItem* item );

	void paintItem( GraphicsContext* ctx, Rect& itemRect, 
					double currentTop, Color* selectedTextColor, 
					const Rect& bounds, double scrollWidth, double offsetX,
					ListItem* item );

	void paintItemState( GraphicsContext* ctx, Rect& itemRect, ListItem* item );

	void paintItemImage( GraphicsContext* ctx, Rect& itemRect, ListItem* item );

	Rect getStateRect( ListItem* item );
};


}; // namespace VCF


#endif // _VCF_LISTBOXCONTROL_H__

/**
$Id$
*/
