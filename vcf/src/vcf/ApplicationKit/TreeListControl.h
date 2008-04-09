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


#ifndef _VCF_TREECONTROL_H__
#	include "vcf/ApplicationKit/TreeControl.h"
#endif // _VCF_TREECONTROL_H__



namespace VCF {

class ImageList;



#define TREELISTCONTROL_CLASSID		"C7ED6506-98BD-45e9-ABCD-7704EE00A027"




class APPLICATIONKIT_API TreeListControl : public TreeControl, public ColumnController {
public:

	TreeListControl();
	virtual ~TreeListControl();
	
	double getColumnWidth( const uint32& index );

	void setColumnWidth( const uint32& index, const double& width );

	virtual ColumnItem* getColumnItem( const uint32& index );

	virtual void insertItemSubItem( TreeItem* item, const uint32& index, TreeSubItem* subItem );
	virtual void removeItemSubItem( TreeItem* item, TreeSubItem* subItem );
	virtual bool getItemSubItems( TreeItem* item, std::vector<TreeSubItem*>& subItems );
	virtual TreeSubItem* getItemSubItem( TreeItem* item, const uint32& index );
	virtual uint32 getItemSubItemCount( TreeItem* item );
	virtual bool subItemExists( const TreeModel::Key& key, const uint32& subItemIndex );


	virtual double getItemWidth( ColumnItem* item );
	virtual void setItemWidth( ColumnItem* item, const double& val );
	virtual TextAlignmentType getItemTextAlignment( ColumnItem* item );
	virtual void setItemTextAlignment( ColumnItem* item, const TextAlignmentType& val );


	virtual void mouseDown( MouseEvent* event );

	virtual void keyDown( KeyboardEvent* e );

	
/*
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

	DELEGATE(ItemDelegate,ItemSelected);
	DELEGATE(ItemDelegate,ItemStateChangeRequested);
	DELEGATE(ItemDelegate,ItemExpanded);

	virtual void modelChanged( Model* oldModel, Model* newModel );

	TreeModel* getTreeModel();

	void setTreeModel( TreeModel* tm );

	

	


	virtual void paint( GraphicsContext * context );


	void insertItem( TreeItem* parent, TreeItem* item );
	TreeItem* insertItem( TreeItem* parent, const String& caption, const uint32 imageIndex=-1 );
	void removeItem( TreeItem* item );

	virtual TreeItem* getItemParent( TreeItem* item );
	virtual void setItemParent( TreeItem* item, TreeItem* parent );

	virtual Rect getItemRect( const TreeModel::Key& item );

	virtual void addChildItem( TreeItem* item, TreeItem* child );
	virtual void removeChildItem( TreeItem* item, TreeItem* child );

	virtual TreeItem* getItemFromKey( const TreeModel::Key& key );
	virtual void setItemKey( TreeItem* item, const TreeModel::Key& key );

	virtual bool getItemChildren( TreeItem* item, std::vector<TreeItem*>& children );

	virtual void insertItemSubItem( TreeItem* item, const uint32& index, TreeSubItem* subItem );
	virtual void removeItemSubItem( TreeItem* item, TreeSubItem* subItem );
	virtual bool getItemSubItems( TreeItem* item, std::vector<TreeSubItem*>& subItems );
	virtual TreeSubItem* getItemSubItem( TreeItem* item, const uint32& index );
	virtual uint32 getItemSubItemCount( TreeItem* item );

	virtual void itemExpanded( TreeItem* item );
	virtual void itemSelected( TreeItem* item );



	uint32 getItemIndent() {
		return itemIndent_;
	}

	void setItemIndent( const uint32& itemIndent );

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

	int32 getDisplayOptions();

	void setDisplayOptions( const int32& displayOptions );

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

	

	

	void scrollToNextItem( TreeItem* item, bool scrollDown ); 

	bool itemExists( const TreeModel::Key& key );

	
	*/

	virtual void handleEvent( Event* event );

	int hitTestForEditColumn( const Point& pt );

	Rect getBoundsForEdit( TreeItem* item, int column );
protected:
	bool allowLabelEditing_;
	int currentEditColumn_;
	Control* currentEditingControl_;

	typedef std::multimap<TreeItem*,TreeSubItem*> SubItemMap;
	typedef std::pair<SubItemMap::iterator,SubItemMap::iterator> SubItemIteratorPair;
	typedef SubItemMap::value_type SubItemPair;
	SubItemMap subItems_;

	Array<ColumnItem*> columnItems_;

	void onColumnItemAdded( ListModelEvent* event );
	void onColumnItemDeleted( ListModelEvent* event );



	/*

	HeaderControl* header_;

	ImageList* imageList_;
	ImageList* stateImageList_;

	double itemHeight_;
	double columnHeight_;
	uint32 itemIndent_;

	int32 displayOptions_;
	bool allowLabelEditing_;
	bool allowMultipleSelection_;

	double visibleItemsHeight_;

	Array<TreeItem*> selectedItems_;
	bool controlChangeToModel_;
	std::map<TreeModel::Key,TreeItem*> itemMap_;


	int32 stateItemIndent_;

	Color rowLineColor_;
	Color columnLineColor_;
	std::map<TreeItem*,double> hierarchyHeightMap_;
	std::vector<TreeItem*> visibleDisplayItems_;
	Rect dragSelectionRect_;
	Point dragPoint_;
	bool draggingSelectionRect_;
	std::vector<TreeItem*> draggingSelectedItems_;

	

	void onModelChanged( TreeModelEvent* event );
	void onModelEmptied( Event* event );

	bool singleSelectionChange( MouseEvent* event );
	bool multiSelectionChange( MouseEvent* event );

	virtual void paintItem( TreeItem* item, GraphicsContext* context, Rect* paintRect );

	virtual void paintSubItem( TreeItem* item, GraphicsContext* context, const uint32& subItemIndex, Rect* paintRect );

	virtual void paintExpander( TreeItem* item, GraphicsContext* context, Rect* paintRect );

	virtual void paintItemState( TreeItem* item, GraphicsContext* context, Rect* paintRect, const int32& currentIndent );

	virtual void paintItemImage( TreeItem* item, GraphicsContext* context, Rect* paintRect, const int32& currentIndent );

	void onColumnWidthChanged( ItemEvent* event );

	bool listVisibleItems( std::vector<TreeItem*>& items, TreeItem* itemToSearch, const double& top, const double& bottom );

	bool listSelectedItems( std::vector<TreeItem*>& items, TreeItem* firstSelectedItem, TreeItem* lastSelectedItem, TreeItem* nextItem, bool& startFound );

	void populateVisiblityList( std::vector<TreeItem*>& items, Rect* bounds=NULL );

	double getCurrentIndent( TreeItem* item );

	Rect getStateRect( TreeItem* item, const double& indent );
	Rect getExpanderRect( TreeItem* item );

	bool hitTest( Rect* rect, TreeItem* item, std::vector<TreeItem*>& hitTestList );

	void recalcScrollable();	

	TreeItem* getNextItem( TreeItem* item, bool skipChildren=false );
	TreeItem* getPrevItem( TreeItem* item );
*/

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
