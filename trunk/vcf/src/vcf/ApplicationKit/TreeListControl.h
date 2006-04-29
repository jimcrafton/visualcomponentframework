#ifndef _VCF_TREELISTCONTROL_H__
#define _VCF_TREELISTCONTROL_H__
//TreeListControl.h

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

#ifndef _VCF_TREEITEM_H__
#	include "vcf/ApplicationKit/TreeItem.h"
#endif // _VCF_TREEITEM_H__

#ifndef _VCF_TREEMODELEVENT_H__
#	include "vcf/ApplicationKit/TreeModelEvent.h"
#endif // _VCF_TREEMODELEVENT_H__



#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__

#ifndef _VCF_COLUMNITEM_H__
#	include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__

#ifndef _VCF_COLUMNMODELEVENT_H__
#	include "vcf/ApplicationKit/ColumnModelEvent.h"
#endif // _VCF_COLUMNMODELEVENT_H__


namespace VCF {

class ImageList;

class HeaderControl;

#define TREELISTCONTROL_CLASSID		"C7ED6506-98BD-45e9-ABCD-7704EE00A027"




class APPLICATIONKIT_API TreeListControl : public CustomControl, public DelegatedContainer<TreeListControl> {
public:

	TreeListControl();
	virtual ~TreeListControl();

	void init();

	enum TreeListControlEvents {
		ITEM_STATECHANGE_REQUESTED = CUSTOM_EVENT_TYPES + ITEM_CONST + 10
	};

	enum TreeDisplayOptions {
		tdoNone = 0,
		tdoShowHierarchyLines = 1,
		tdoShowRowLines = 2,
		tdoShowColumnLines = 4,
		tdoShowFullRowSelection = 8,
		tdoShowColumnHeader = 16
	};

	DELEGATE(ItemSelected);
	DELEGATE(ItemStateChangeRequested);
	DELEGATE(ItemExpanded);

	void setTreeModel(TreeModel * model);

	TreeModel* getTreeModel();

	ColumnModel* getColumnModel();

	double getColumnWidth( const unsigned long& index );

	void setColumnWidth( const unsigned long& index, const double& width );


	virtual void paint( GraphicsContext * context );


	void addItem( TreeItem* item, TreeItem* parent = NULL );

	TreeItem* addItem( TreeItem* parent=NULL, const String& caption="", const ulong32 imageIndex=0 );

	ulong32 getItemIndent() {
		return itemIndent_;
	}

	void setItemIndent( const ulong32& itemIndent );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseClick(  MouseEvent* event );

	virtual void mouseDblClick(  MouseEvent* event );

	virtual void keyDown( KeyboardEvent* e );

	void setImageList( ImageList* imageList );

	void setStateImageList( ImageList* imageList );

	ImageList* getImageList();

	ImageList* getStateImageList();

	long getDisplayOptions();

	void setDisplayOptions( const long& displayOptions );

	TreeItem* isPtOverItem( Point* point );

	void setSelectedItem( TreeItem* item, const bool& isSelected );

	TreeItem* getSelectedItem();

	bool getAllowLabelEditing();

	void setAllowLabelEditing( const bool& allowLabelEditing );	

	HeaderControl* getHeader() {
		return header_;
	}

	Enumerator<TreeItem*>* getSelectedItems();

	bool getAllowsMultipleSelection() {
		return allowMultipleSelection_;
	}

	void setAllowsMultipleSelection( const bool& multiSelect );

	TreeItem* hitTest( Point* pt, TreeItem* itemToTest );

	/**
	*searches all the items for a match for the point
	*/
	TreeItem* hitTest( Point* pt );

	bool stateHitTest( Point* pt, TreeItem* itemToTest );

	void setDefaultItemHeight( const double& defaultItemHeight );

	double getDefaultItemHeight();

	void showHierarchyLines( const bool& show );

	void showRowLines( const bool& show );

	void showColumnLines( const bool& show );

	void showFullRowSelection( const bool& show );

	void showColumnHeader( const bool& show );

	void clearSelectedItems();

	TreeItem* getNextItem( TreeItem* item, bool skipChildren=false );
	TreeItem* getPrevItem( TreeItem* item );

	int hitTestForEditColumn( Point* pt );

	Rect getBoundsForEdit( TreeItem* item, int column );

	void scrollToNextItem( TreeItem* item, bool scrollDown ); 
protected:
	

	HeaderControl* header_;

	ImageList* imageList_;
	ImageList* stateImageList_;

	TreeModel* treeModel_;

	double itemHeight_;
	double columnHeight_;
	ulong32 itemIndent_;

	long displayOptions_;
	bool allowLabelEditing_;
	bool allowMultipleSelection_;

	double visibleItemsHeight_;

	std::vector<TreeItem*> selectedItems_;
	EnumeratorContainer<std::vector<TreeItem*>,TreeItem*> selectedItemContainer_;

	long stateItemIndent_;

	Color rowLineColor_;
	Color columnLineColor_;
	std::map<TreeItem*,double> hierarchyHeightMap_;
	std::vector<TreeItem*> visibleDisplayItems_;
	Rect dragSelectionRect_;
	Point dragPoint_;
	bool draggingSelectionRect_;
	std::vector<TreeItem*> draggingSelectedItems_;

	int currentEditColumn_;
	Control* currentEditingControl_;

	void onModelChanged( TreeModelEvent* event );
	void onModelEmptied( Event* event );

	bool singleSelectionChange( MouseEvent* event );
	bool multiSelectionChange( MouseEvent* event );

	virtual void paintItem( TreeItem* item, GraphicsContext* context, Rect* paintRect );

	virtual void paintSubItem( TreeItem* item, GraphicsContext* context, const ulong32& subItemIndex, Rect* paintRect );

	virtual void paintExpander( TreeItem* item, GraphicsContext* context, Rect* paintRect );

	virtual void paintItemState( TreeItem* item, GraphicsContext* context, Rect* paintRect, const long& currentIndent );

	virtual void paintItemImage( TreeItem* item, GraphicsContext* context, Rect* paintRect, const long& currentIndent );

	void onColumnWidthChanged( ItemEvent* event );

	bool listVisibleItems( std::vector<TreeItem*>& items, TreeItem* itemToSearch, const double& top, const double& bottom );

	bool listSelectedItems( std::vector<TreeItem*>& items, TreeItem* firstSelectedItem, TreeItem* lastSelectedItem, TreeItem* nextItem, bool& startFound );

	void populateVisiblityList( std::vector<TreeItem*>& items, Rect* bounds=NULL );

	double getCurrentIndent( TreeItem* item );

	Rect getStateRect( TreeItem* item, const double& indent );
	Rect getExpanderRect( TreeItem* item );

	bool hitTest( Rect* rect, TreeItem* item, std::vector<TreeItem*>& hitTestList );

	void recalcScrollable();	

	void onEditingControlKeyPressed( KeyboardEvent* event );
	void onEditorFocusLost( Event* e );
	void postFinishedEditing( Event* e );

	//editing functions 
	void cancelEditing();
	void finishEditing( bool applyEdit=true );
	void editItem( TreeItem* item, Point* point );

	//virtual functions - should be overriden in derived classes

	/**
	this is a no-op - sub classes need to derive this
	*/
	virtual void finishEditingItem( TreeItem* item, Control* editControl ) {};

	/**
	this is a no-op - sub classes need to derive this
	*/
	virtual Control* createEditor( TreeItem* item, int column ) {
		return NULL;
	}

	/**
	virtual function to control whether or not to allow an edit to finish due to 
	focus loss. 
	@return bool return true to enable the edit session to finish, otherwise
	return false.
	*/
	virtual bool finishEditingFromFocusLoss( Control* lostFocusCtrl, Control* currentFocusedCtrl );
};


};


#endif // _VCF_TREELISTCONTROL_H__

/**
$Id$
*/
