#ifndef _VCF_LISTVIEWPEER_H__
#define _VCF_LISTVIEWPEER_H__
//ListviewPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class ListItem;




/** @interface */

class APPLICATIONKIT_API ListviewPeer : public VCF::Interface {
public:
	virtual ~ListviewPeer(){};

	virtual void addItem( ListItem * item ) = 0;

	virtual void insertItem( const unsigned long& index, ListItem * item ) = 0;

	virtual void clear() = 0;

	virtual void deleteItem( ListItem* item ) = 0;

	virtual bool ensureVisible(ListItem * item, bool partialOK ) = 0;

	virtual void setFocusedItem(ListItem * item) = 0;

	virtual void selectItem(ListItem * item) = 0;

	virtual Rect* getItemRect( ListItem* item ) = 0;

	virtual bool isItemSelected(ListItem* item) = 0;

	virtual ListItem* isPtOverItem(Point* point) = 0;

	virtual ListItem* getFocusedItem() = 0;

	virtual ListItem* getSelectedItem() = 0;

	virtual Enumerator<ListItem*>* getSelectedItems() = 0;

	virtual void rangeSelect( Rect* selectionRect ) = 0;

	virtual void addHeaderColumn( const String& columnName, const double& width ) = 0;

	virtual void insertHeaderColumn( const unsigned long& index, const String& columnName, const double& width ) = 0;

	virtual void deleteHeaderColumn( const unsigned long& index ) = 0;

	virtual void setColumnWidth( const unsigned long& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone ) = 0;

	virtual double getColumnWidth( const unsigned long& index ) = 0;

	virtual void setColumnName( const unsigned long& index, const String& columnName ) = 0;

	virtual String getColumnName( const unsigned long& index ) = 0;

	virtual void sort( ItemSort* itemSortFunctor ) = 0;

	virtual IconStyleType getIconStyle() = 0;

	virtual void setIconStyle( const IconStyleType& iconStyle ) = 0;

	virtual bool getAllowsMultiSelect() = 0;

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect ) = 0;

	virtual IconAlignType getIconAlignment() = 0;

	virtual void setIconAlignment( const IconAlignType& iconAlignType ) = 0;

	virtual bool getAllowLabelEditing() = 0;

	virtual void setAllowLabelEditing( const bool& allowLabelEditing ) = 0;

	virtual void setLargeImageList( ImageList* imageList ) = 0;

	virtual void setSmallImageList( ImageList* imageList ) = 0;

	virtual Rect getItemImageRect( ListItem* item ) = 0;

	virtual long getDisplayOptions() = 0;

	virtual void setDisplayOptions( const long& displayOptions ) = 0;
};

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
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
*Revision 1.12.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.4  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.11.4.3  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.11.4.2  2003/09/09 19:32:01  marcelloptr
*minor changes and autoresizing of listbox columns
*
*Revision 1.11.4.1  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.11  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.1  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.8.1  2002/12/27 23:04:38  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.8.12.1  2002/07/03 07:13:00  marcelloptr
*minor fixes
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LISTVIEWPEER_H__


