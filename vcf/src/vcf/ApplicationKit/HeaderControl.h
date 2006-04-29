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


#endif // _VCF_HEADERCONTROL_H__

/**
$Id$
*/
