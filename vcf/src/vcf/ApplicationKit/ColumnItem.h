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

	/* autoresizing added by Marcello */
	enum ColumnAutosizeType {
		casAutoSizeNone = -1,
		casAutoSizeColumns = -2,
		casAutoSizeHeaders = -3,
		casAutoSizeColumnsAndHeaders = -4,
	};


	static String ColumnAutosizeTypeNames[] = { "casAutoSizeNone",
                                         "casAutoSizeColumns",
										 "casAutoSizeHeaders",
										 "casAutoSizeColumnsAndHeaders" };


class ColumnItem;
class ColumnModel;
	
class ColumnController {
public:
	virtual ~ColumnController(){}
	
	virtual double getItemWidth( ColumnItem* item ) = 0;
	virtual void setItemWidth( ColumnItem* item, const double& val ) = 0;

	virtual TextAlignmentType getItemTextAlignment( ColumnItem* item ) = 0;
	virtual void setItemTextAlignment( ColumnItem* item, const TextAlignmentType& val ) = 0;
	
};




/**
\class ColumnItem ColumnItem.h "vcf/ApplicationKit/ColumnItem.h"
*A ColumnItem item is used to represent a single header column.
*ColumnItems can be found in the HeaderControl, and ListViewControl,
*and are used to display a series of rectangular shapes that each represent
*a column vertical column.
*/
class APPLICATIONKIT_API ColumnItem : public Item {
public:

	ColumnItem(): Item(), index_(0)/*,width_(100.0), textAlignment_(taTextLeft)*/{}

	virtual ~ColumnItem(){};

	ColumnModel* getColumnModel() {
		return (ColumnModel*) getModel();
	}

	ColumnController* getController() {
		return dynamic_cast<ColumnController*>( getControl() );
	}

	/**
	*returns the width of the coumn. The width should always be greater
	*than or equal to 0
	*/
	double getWidth();

	/**
	*sets the width of the column
	*@param double width - the new column width
	*/
	void setWidth( const double& width );

	

	/**
	*sets the alignment of the caption.
	*Setting the caption alignment determines how the caption is
	*drawn and to which side the text is aligned. You can align
	*it to the left, right, or center.
	*@param TextAlignmentType teh alignment type for the column
	*when it is drawn
	*/
	void setCaptionAlignment( const TextAlignmentType& alignment );

	/**
	*gets the current alignment type fopr the column.
	*@return TextAlignmentType the alignment type of the column
	@see setCaptionAlignment()
	*/
	TextAlignmentType getCaptionAlignment();

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
	void setCaption( const String& caption );

	/**
	*returns the caption for the column item
	*@return String the column's caption
	*/
	String getCaption();


	virtual void paint( GraphicsContext* context, Rect* paintRect ) {
		bounds_ = *paintRect;
	}

protected:		
	uint32 index_;
};


}; //end of namespace VCF


#endif // _VCF_COLUMNITEM_H__

/**
$Id$
*/
