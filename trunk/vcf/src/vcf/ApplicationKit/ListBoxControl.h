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

class APPLICATIONKIT_API ListBoxControl : public CustomControl {

public:
	enum ListBoxControlEvents {
		lbeItemStateChangeRequested = CUSTOM_EVENT_TYPES + ITEM_CONST + 100
	};

	DELEGATE(SelectionChanged);
	DELEGATE(ItemStateChangeRequested);

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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/03/20 04:29:21  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.2.4.2  2005/03/10 00:17:27  marcelloptr
*set discrete scrolling as default behaviour for ListBoxControls
*
*Revision 1.2.4.1  2005/01/17 17:55:06  marcelloptr
*reformatting
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/08 19:45:23  dougtinkham
*implemented multi-selection and extended-selection, modified mouseDown, mouseMove, and paint. Text in list box can be painted using textBoundedBy or textAt, set by making a call to setTextBounded(const bool&). Added double leftGutter_ and double rightGutter_, which control the distance between text and left and right edges of borders, respectively.
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.15.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.2.5  2003/11/10 01:57:03  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.14.2.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.14.2.3  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.14.2.2  2003/09/06 19:45:45  ddiego
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
*Revision 1.14.2.1  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.14  2003/08/09 02:56:42  ddiego
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
*Revision 1.13.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.13  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.1  2003/03/12 03:09:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.11  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.10.4.1  2002/04/27 15:42:39  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.10  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LISTBOXCONTROL_H__


