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

	virtual void createParams();

	virtual LRESULT handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc = NULL );

	virtual void addItem( ListItem * item );

	virtual void insertItem( const unsigned long& index, ListItem * item );

	virtual void clear();

	virtual void deleteItem( ListItem* item );

	virtual bool ensureVisible(ListItem * item, bool partialOK );

	virtual void setFocusedItem(ListItem * item);

	virtual void selectItem(ListItem * item);

	virtual Rect* getItemRect( ListItem* item );

	virtual bool isItemSelected(ListItem* item);

	virtual ListItem* isPtOverItem(Point* point);

	virtual ListItem* getFocusedItem();

	virtual ListItem* getSelectedItem();

	virtual Enumerator<ListItem*>* getSelectedItems();

	virtual void rangeSelect( Rect* selectionRect );

	virtual void addHeaderColumn( const String& columnName, const double& width );

	virtual void insertHeaderColumn( const unsigned long& index, const String& columnName, const double& width );

	virtual void deleteHeaderColumn( const unsigned long& index );

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

	virtual void setColumnWidth( const unsigned long& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone );

	virtual double getColumnWidth( const unsigned long& index );

	virtual void setColumnName( const unsigned long& index, const String& columnName );

	virtual String getColumnName( const unsigned long& index );

	virtual void sort( ItemSort* itemSortFunctor );

	virtual void setLargeImageList( ImageList* imageList );

	virtual void setSmallImageList( ImageList* imageList );

	virtual Rect getItemImageRect( ListItem* item );

	virtual long getDisplayOptions();

	virtual void setDisplayOptions( const long& displayOptions );
private:
	static int CALLBACK sortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	static LRESULT CALLBACK Header_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	ListViewControl* listviewControl_;
	bool headerControlIsTracking_;
	std::vector<ListItem*> selectedItems_;
	EnumeratorContainer<std::vector<ListItem*>, ListItem*> enumContainer_;
	Rect itemRect_;	
	WNDPROC oldHeaderWndProc_;
	Color backColor_;
	HIMAGELIST largeImageListCtrl_;
	HIMAGELIST smallImageListCtrl_;



	ItemEventHandler<Win32Listview>* itemAddedHandler_;
	ItemEventHandler<Win32Listview>* itemDeletedHandler_;
	ItemEventHandler<Win32Listview>* itemChangedHandler_;
	ItemEventHandler<Win32Listview>* itemSelectedHandler_;
	ItemEventHandler<Win32Listview>* itemPaintedHandler_;

	ItemEventHandler<Win32Listview>* subItemAddedHandler_;
	ItemEventHandler<Win32Listview>* subItemDeletedHandler_;
	ItemEventHandler<Win32Listview>* subItemChangedHandler_;

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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/15 18:53:00  ddiego
*more updates
*
*Revision 1.1.2.3  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.20.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.20  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.19.2.4  2003/10/20 03:40:25  ddiego
* made some minor changes fixed a bug in color where we forget to actually
*assign hls/hsv values.
*
*Revision 1.19.2.3  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.19.2.2  2003/09/09 19:32:02  marcelloptr
*minor changes and autoresizing of listbox columns
*
*Revision 1.19.2.1  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.19  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.18.2.1  2003/05/27 04:45:32  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.18  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.17.2.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.17.2.1  2003/03/12 03:11:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.17  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.16.8.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.16  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.15.6.1  2002/07/03 07:13:01  marcelloptr
*minor fixes
*
*Revision 1.15  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.1  2002/04/27 15:52:19  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.14  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32LISTVIEW_H__


