#ifndef _VCF_DEFAULTTABLECELLITEM_H__
#define _VCF_DEFAULTTABLECELLITEM_H__
//DefaultTableCellItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABLECELLITEM_H__
#	include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__


namespace VCF {

class BasicTableItemEditor;
class TableModel;

#define DEFAULTTABLECELLITEM_CLASSID	"53EA0BA6-7068-11d4-8F12-00207811CFAB"

/**
\class DefaultTableCellItem DefaultTableCellItem.h "vcf/ApplicationKit/DefaultTableCellItem.h"
*/
class APPLICATIONKIT_API DefaultTableCellItem : public TableCellItem {
public:

	DefaultTableCellItem();

	virtual ~DefaultTableCellItem();

	virtual bool containsPoint( Point * pt );

    virtual uint32 getIndex() {
		return -1;
	}

	virtual void setIndex( const uint32& index ) {}
    
	virtual bool canPaint() const {
		return true;
	}


	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual TableItemEditor* createItemEditor();

	
	virtual bool isReadonly() {
		return (displayState_ & TableCellItem::tisReadonly) ? true : false;
	}

	virtual bool isFixed();

	virtual bool isFocused() {
		return (displayState_ & TableCellItem::tcsFocused) ? true : false;
	}

	virtual bool isDropHighlighted() {
		return (displayState_ & TableCellItem::tcsDropHighlighted) ? true : false;
	}

	virtual bool isEditable() {
		return !isReadonly();
	}	

	virtual void setReadonly( const bool& val );

	virtual void setFocused( const bool& val );

	virtual void setDropHighlighted( const bool& val );


	virtual String getCaption() ;

	virtual void setCaption( const String& caption );

	virtual double getTextCellWidth();

	virtual double getTextCellHeight();

	virtual const Color& getColor();

	virtual void setColor( Color* color );	

	virtual CellID getID() {
		return id_;
	}

	virtual void setID( const CellID& val ) {
		id_ = val;
	}
protected:
	Color* color_;
	CellID id_;
	typedef std::map<uint32,Color> ColorMap;
	static  ColorMap tableCellsColorMap;

	
	typedef std::map<String,Font> FontMap;
	static FontMap tableCellsFontMap;

	void onFontChanged( Event* e );
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABLECELLITEM_H__

/**
$Id$
*/
