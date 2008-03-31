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

	virtual IconStyleType getIconStyle();

	virtual void setIconStyle( const IconStyleType& iconStyle );

	virtual bool getAllowsMultiSelect();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	virtual IconAlignType getIconAlignment();

	virtual void setIconAlignment( const IconAlignType& iconAlignType );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone );

	virtual double getColumnWidth( const uint32& index );

	virtual TextAlignmentType getColumnTextAlignment( const uint32& index );

	virtual void setColumnTextAlignment( const uint32& index, const TextAlignmentType& val );

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
	Array<ListItem*> selectedItems_;
	WNDPROC oldHeaderWndProc_;
	Color backColor_;
	HIMAGELIST largeImageListCtrl_;
	HIMAGELIST smallImageListCtrl_;
	HFONT oldHeaderFont_;
	GraphicsContext* currentCtx_;

	void onCtrlModelChanged( Event* e );
	void onListModelChanged( Event* e );
	void onColumnModelChanged( Event* e );
	void onColumnModelAdded( Event* e );
	void onColumnModelRemoved( Event* e );
	
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
