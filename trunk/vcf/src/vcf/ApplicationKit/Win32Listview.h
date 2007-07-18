#ifndef _VCF_WIN32LISTVIEW_H__
#define _VCF_WIN32LISTVIEW_H__
//Win32Listview.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/ListviewPeer.h"


namespace VCF
{

class Win32Listview : public AbstractWin32Component, public ListviewPeer {
public:
	Win32Listview( ListViewControl* listviewControl );

	virtual ~Win32Listview();

	virtual void create( Control* owningControl );

	virtual Win32Object::CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual void addItem( ListItem * item );

	virtual void insertItem( const uint32& index, ListItem * item );

	virtual void clear();

	virtual void deleteItem( ListItem* item );

	virtual bool ensureVisible(ListItem * item, bool partialOK );

	virtual void setFocusedItem(ListItem * item);

	virtual void selectItem(ListItem * item);

	virtual Rect getItemRect( ListItem* item );

	virtual bool isItemSelected(ListItem* item);

	virtual ListItem* isPtOverItem(Point* point);

	virtual ListItem* getFocusedItem();

	virtual ListItem* getSelectedItem();

	virtual Enumerator<ListItem*>* getSelectedItems();

	virtual void rangeSelect( Rect* selectionRect );

	virtual void addHeaderColumn( const String& columnName, const double& width );

	virtual void insertHeaderColumn( const uint32& index, const String& columnName, const double& width );

	virtual void deleteHeaderColumn( const uint32& index );

	virtual IconStyleType getIconStyle();

	virtual void setIconStyle( const IconStyleType& iconStyle );

	virtual bool getAllowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	virtual IconAlignType getIconAlignment();

	virtual void setIconAlignment( const IconAlignType& iconAlignType );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	void onItemPaint( ItemEvent* event );

	void onItemChanged( ItemEvent* event );

	void onItemSelected( ItemEvent* event );

	void onItemAdded( ItemEvent* event );

	void onItemDeleted( ItemEvent* event );

	virtual void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone );

	virtual double getColumnWidth( const uint32& index );

	virtual void setColumnName( const uint32& index, const String& columnName );

	virtual String getColumnName( const uint32& index );

	virtual void sort( ItemSort* itemSortFunctor );

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );

	virtual Rect getItemImageRect( ListItem* item );

	virtual int32 getDisplayOptions();

	virtual void setDisplayOptions( const int32& displayOptions );
private:
	static int CALLBACK sortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	static LRESULT CALLBACK Header_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	ListViewControl* listviewControl_;
	bool headerControlIsTracking_;
	bool internalMessage_;
	std::vector<ListItem*> selectedItems_;
	EnumeratorContainer<std::vector<ListItem*>, ListItem*> enumContainer_;
	WNDPROC oldHeaderWndProc_;
	Color backColor_;
	HIMAGELIST largeImageListCtrl_;
	HIMAGELIST smallImageListCtrl_;



	ItemHandler* itemAddedHandler_;
	ItemHandler* itemDeletedHandler_;
	ItemHandler* itemChangedHandler_;
	ItemHandler* itemSelectedHandler_;
	ItemHandler* itemPaintedHandler_;

	ItemHandler* subItemAddedHandler_;
	ItemHandler* subItemDeletedHandler_;
	ItemHandler* subItemChangedHandler_;

	void onSubItemChanged( ItemEvent* event );

	void onSubItemAdded( ItemEvent* event );

	void onSubItemDeleted( ItemEvent* event );

	void updateItemSubItems( ListItem* item );


	IconStyleType translateStyleToIconStyle( const DWORD& wsStyle );
	DWORD translateIconStyleToStyleBit( const IconStyleType& iconStyle );

	IconAlignType translateStyleToIconAlignment( const DWORD& wsStyle );
	DWORD translateIconAlignmentToStyleBit( const IconAlignType& iconAlignment );

	void onLargeImageListImageChanged( ImageListEvent* event );

	void onSmallImageListImageChanged( ImageListEvent* event );

	void registerHeaderWndProc();

	void postPaintItem( NMLVCUSTOMDRAW* drawItem );
};


};


#endif // _VCF_WIN32LISTVIEW_H__

/**
$Id$
*/
