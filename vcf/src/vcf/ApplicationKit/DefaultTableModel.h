#ifndef _VCF_DEFAULTTABLEMODEL_H__
#define _VCF_DEFAULTTABLEMODEL_H__
//DefaultTableModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABLEMODEL_H__
#include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__


#ifndef _VCF_TABLECELLITEM_H__
#include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__

#ifndef _VCF_TABLEMODELEVENT_H__
#	include "vcf/ApplicationKit/TableModelEvent.h"
#endif // _VCF_TABLEMODELEVENT_H__


namespace VCF {

#define DEFAULTTABLEMODEL_CLASSID		"53EA0BA8-7068-11d4-8F12-00207811CFAB"

class TableCellItem;

class APPLICATIONKIT_API DefaultTableModel : public AbstractModel, public TableModel {
public:
	DefaultTableModel();

	virtual ~DefaultTableModel();

	
    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate();

    /**
     * clears out the model's data
     */
    virtual void empty();

	virtual void addRow();

	virtual void insertRow( const uint32& afterRow );

	virtual void addRows( const uint32& count );

	virtual void deleteRow( const uint32& row );

    virtual void addColumn();

	virtual void insertColumn( const uint32& afterColumn );

	virtual void addColumns( const uint32& count );

	virtual void deleteColumn( const uint32& column );

	virtual bool isCellEditable( const uint32& row, const uint32& column );

	virtual TableCellItem* getItem( const uint32& row, const uint32& column );

	virtual uint32 getRowCount();

	virtual uint32 getColumnCount();

	virtual TableRowItemEnumerator* getRowItemEnumerator( const uint32& row );

	virtual TableCellItem* createCell( const uint32& row, const uint32& column );

	virtual TableCellItem* setSelectedCell( const bool& val, const uint32& row, const uint32& column );

	virtual void setSelectedRange( const bool& val, const uint32& startRow, const uint32& startColumn,
									const uint32& endRow, const uint32& endColumn );

	virtual void setFocusedCell( const uint32& row, const uint32& column );

	virtual TableCellItem* getFocusedCell() {
		return focusedCell_;
	}

	virtual void setFixedColumnsCount( const uint32& count );

	virtual void setFixedRowsCount( const uint32& count );

	virtual uint32 getFixedColumnsCount();

	virtual uint32 getFixedRowsCount();

	virtual void clearSelection();

	virtual Enumerator<TableCellItem*>* getSelectedCells();

	virtual CellID getCellIDForItem( TableCellItem* item );
protected:
	/**
	*defines the a vector of TableCellItem's, or one row of data columnCount_ long
	*/
	typedef std::vector<TableCellItem*> TTableColumn;
private:
	void init();
	uint32 rowCount_;
	uint32 columnCount_;

	uint32 fixedRowsCount_;
	uint32 fixedColumnsCount_;
	/*row/column data
	*access is by row column.
	*so tableData_[0] is row 0, and (*tableData_[0])[2] is the item in
	*row 0 at column 3
	*/
	std::vector<TTableColumn*> tableData_;

	EnumeratorContainer<std::vector<TableCellItem*>,TableCellItem*> rowEnumContainer_;

	std::map<ulong32,TableCellItem*> selectionMap_;
	EnumeratorMapContainer<std::map<ulong32,TableCellItem*>,TableCellItem*> selectionContainer_;

	TableCellItem* focusedCell_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/10/10 23:48:21  ddiego
*fixed duplicate delegate in DefaultTableModel class.
*
*Revision 1.2.2.2  2004/10/05 02:48:22  kiklop74
*Added needed changes that will enable Borland compiler to compile RTTI for ApplicationKit
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.14.2.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.7  2004/03/01 05:58:54  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.13.2.6  2004/02/19 04:52:34  ddiego
*more progress made with TableControl
*
*Revision 1.13.2.5  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.13.2.4  2004/02/02 04:38:36  ddiego
*more table codin'
*
*Revision 1.13.2.3  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.13.2.2  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.13.2.1  2004/01/29 22:26:47  ddiego
*table fixes, this still needs some more work
*
*Revision 1.13  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:09:32  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.10  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:42:09  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.9.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTTABLEMODEL_H__


