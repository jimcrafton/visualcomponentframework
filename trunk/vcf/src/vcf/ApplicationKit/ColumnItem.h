#ifndef _VCF_COLUMNITEM_H__
#define _VCF_COLUMNITEM_H__
//ColumnItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define COLUMNITEM_CLASSID		"0788b0bd-d9da-4a05-ae77-5d536269598f"

namespace VCF  {

/**
*A ColumnItem item is used to represent a single header column.
*ColumnItems can be found in the HeaderControl, and ListViewControl,
*and are used to display a series of rectangular shapes that each represent
*a column vertical column.
*/
class APPLICATIONKIT_API ColumnItem : public Item{
public:

	virtual ~ColumnItem(){};

	/**
	*returns the width of the coumn. The width should always be greater
	*than or equal to 0
	*/
	virtual double getWidth() = 0;

	/**
	*sets the width of the column
	*@param double width - the new column width
	*/
	virtual void setWidth( const double& width ) = 0;

	/**
	*sets the caption of the column.
	*If the text is wider than the current width of the
	*column it will be truncated to fit and drawn with an
	*ellipsis ("...")
	*@param String the new column caption
	*/
	virtual void setCaption( const String& caption ) = 0;

	/**
	*returns the caption for the column item
	*@return String the column's caption
	*/
	virtual String getCaption() = 0;

	/**
	*sets the alignment of the caption.
	*Setting the caption alignment determines how the caption is
	*drawn and to which side the text is aligned. You can align
	*it to the left, right, or center.
	*@param TextAlignmentType teh alignment type for the column
	*when it is drawn
	*/
	virtual void setCaptionAlignment( const TextAlignmentType& alignment ) = 0;

	/**
	*gets the current alignment type fopr the column.
	*@return TextAlignmentType the alignment type of the column
	@see setCaptionAlignment()
	*/
	virtual TextAlignmentType getCaptionAlignment() = 0;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.26.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.4  2002/02/17 01:07:14  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.3  2002/02/15 03:49:11  ddiego
*documentation
*
*Revision 1.2  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COLUMNITEM_H__


