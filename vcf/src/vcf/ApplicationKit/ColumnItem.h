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
\class ColumnItem ColumnItem.h "vcf/ApplicationKit/ColumnItem.h"
*A ColumnItem item is used to represent a single header column.
*ColumnItems can be found in the HeaderControl, and ListViewControl,
*and are used to display a series of rectangular shapes that each represent
*a column vertical column.
*/
class APPLICATIONKIT_API ColumnItem : public Item{
public:

	ColumnItem(): Item(), index_(0){}

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

	virtual uint32 getIndex() const {
		return index_;
	}

	virtual void setIndex( const uint32& index ) {
		index_ = index;
	}

	/**
	*sets the caption of the column.
	*If the text is wider than the current width of the
	*column it will be truncated to fit and drawn with an
	*ellipsis ("...")
	*@param String the new column caption
	*/
	virtual void setCaption( const String& caption );

	/**
	*returns the caption for the column item
	*@return String the column's caption
	*/
	virtual String getCaption();

protected:
	uint32 index_;
};


}; //end of namespace VCF


#endif // _VCF_COLUMNITEM_H__

/**
$Id$
*/
