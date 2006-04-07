#ifndef _VCF_HEADERCONTROL_H__
#define _VCF_HEADERCONTROL_H__
//HeaderControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COLUMNMODEL_H__
#include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__

#ifndef _VCF_COLUMNITEM_H__
#include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__

#ifndef _VCF_COLUMNMODELEVENT_H__
#include "vcf/ApplicationKit/ColumnModelEvent.h"
#endif // _VCF_COLUMNMODELEVENT_H__



#define HEADERCONTROL_CLASSID		"79af8c52-62f4-4d42-8c41-c18564e1a2f0"


namespace VCF  {


/*
class APPLICATIONKIT_API HeaderView : public View {
public:

	//virtual void paintColumn( GraphicsContext* context, Rect* paintRect, const ulong32& index );
};
*/


/**
\class HeaderControl HeaderControl.h "vcf/ApplicationKit/HeaderControl.h"
*Class HeaderControl documentation
*/
class APPLICATIONKIT_API HeaderControl : public CustomControl {
public:

	HeaderControl();
	virtual ~HeaderControl();


	enum HeaderControlEvents{
		COLUMN_ITEM_CLICKED = Control::CONTROL_EVENTS_LAST + 300,
		COLUMN_ITEM_WIDTHCHANGED
	};

	DELEGATE(ColumnItemClicked)
	DELEGATE(ColumnWidthChanged)


	inline ColumnModel* getColumnModel() {
		return columnModel_;
	}

	void setColumnModel( ColumnModel* model );

	virtual ColumnItem* addColumn( const String& columnName, const double& width=100.0 );

	void addColumn( ColumnItem* column );

	virtual ColumnItem* insertColumn( const unsigned long& index, const String& columnName, const double& width=100.0 );

	void insertColumn( const unsigned long& index, ColumnItem* column );

	void deleteColumn( const unsigned long& index );

	String getColumnName( const unsigned long& index );

	void setColumnName( const unsigned long& index, const String& columnName );

	double getColumnWidth( const unsigned long& index );

	void setColumnWidth( const unsigned long& index, const double& width );

	inline ImageList* getImageList() {
		return imageList_;
	}

	void setImageList( ImageList* imageList );

	ColumnItem* isPtOverItem(Point* point);

	virtual void paint( GraphicsContext * context );

	virtual double getPreferredHeight();

	virtual double getPreferredWidth();

	TextAlignmentType getTextAlignment() {
		return textAlignment_;
	}

	void setTextAlignment( const TextAlignmentType& textAlignment );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void handleEvent( Event* event );
protected:
	virtual void paintColumn( GraphicsContext* context, Rect* paintRect, const ulong32& index, ColumnItem* item );
	ColumnModel* columnModel_;
	ImageList* imageList_;
	TextAlignmentType textAlignment_;
	ColumnItem* draggingColumnItem_;
	ColumnItem* pressedColumn_;
	double minColumnWidth_;


};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.15.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.14.4.2  2003/09/06 19:45:45  ddiego
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
*Revision 1.14.4.1  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.14  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.1  2003/03/12 03:09:34  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.14.1  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.12  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.1  2002/04/27 15:42:28  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.11  2002/03/03 18:33:44  ddiego
*fixed some display errors in the TreeListControl and added support for ImagLists to
*the HeaderControl
*
*Revision 1.10  2002/03/01 02:58:40  ddiego
*added min/max constraints to the HeaderControl and TreeListControl
*
*Revision 1.9  2002/03/01 02:10:58  ddiego
*added HeaderControl::COLUMN_ITEM_CLICKED event to HeaderControl
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_HEADERCONTROL_H__


