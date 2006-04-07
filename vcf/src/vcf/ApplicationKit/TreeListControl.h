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


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2005/09/12 03:47:04  ddiego
*more prop editor updates.
*
*Revision 1.4  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/02/21 16:20:02  ddiego
*minor changes to various things, property editors, and tree list control.
*
*Revision 1.3.2.1  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/21 21:06:52  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.30.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.30  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.29.2.5  2003/10/17 21:22:54  ddiego
*added menu item child count function
*fixed a selection glitch in tree list control
*
*Revision 1.29.2.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.29.2.3  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.29.2.2  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.29.2.1  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.29  2003/08/09 02:56:42  ddiego
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
*Revision 1.28.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.28  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.27.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.27.2.1  2003/03/12 03:09:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.27  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.26.14.2  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.26.14.1  2002/12/27 23:04:33  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.26  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.25.4.1  2002/04/27 15:43:07  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.25  2002/03/17 01:16:37  ddiego
*fixes for bug [ 529718 ] treelistcontrol scroll problem
*the virtual height for the scrollbar is now adjusted correctly
*
*Revision 1.24  2002/03/17 00:19:50  ddiego
*added support for selecting multiple items with the shift key
*
*Revision 1.23  2002/03/13 01:26:26  ddiego
*fixes to the TreeListControl
*plus fix for bug [ 529012 ] typecombo crash in the ComboBoxControl. Caused
*by not checking a null pointer in the UIToolkits' methods for getting the
*next and previous control
*
*Revision 1.22  2002/03/09 18:14:24  ddiego
*got rid of the DefaultTreeListItem class - didn't need it anymore.
*Added a setDefaultItemHeight method to the TreeListControl
*
*Revision 1.21  2002/03/04 05:11:42  ddiego
*fixes for bug [ 525232 ] TreeListControl no multi select
*
*Revision 1.20  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.19  2002/03/01 02:58:40  ddiego
*added min/max constraints to the HeaderControl and TreeListControl
*
*Revision 1.18  2002/02/21 00:37:23  ddiego
*added three functions for feature request 520661
*these may become deprecated in the future as they are
*for convenience purposes only. Please see:
*	TreeListControl::getColumnWidth()
*	TreeListControl::setColumnWidth()
*	TreeListControl::getColumnModel()
*
*Revision 1.17  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TREELISTCONTROL_H__


