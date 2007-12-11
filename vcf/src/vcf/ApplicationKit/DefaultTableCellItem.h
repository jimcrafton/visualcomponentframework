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

    virtual void* getData();

	virtual void setData( void* data );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual TableItemEditor* createItemEditor();

	virtual bool isSelected() {
		return (itemState_ & TableCellItem::tisSelected) ? true : false;
	}

	virtual bool isReadonly() {
		return (itemState_ & TableCellItem::tisReadonly) ? true : false;
	}

	virtual bool isFixed() {
		return (itemState_ & TableCellItem::tcsFixed) ? true : false;
	}

	virtual bool isFocused() {
		return (itemState_ & TableCellItem::tcsFocused) ? true : false;
	}

	virtual bool isDropHighlighted() {
		return (itemState_ & TableCellItem::tcsDropHighlighted) ? true : false;
	}

	virtual bool isEditable() {
		return !isReadonly();
	}

	virtual void setSelected( const bool& val );

	virtual void setReadonly( const bool& val );

	virtual void setFocused( const bool& val );

	virtual void setDropHighlighted( const bool& val );

	virtual void setFixed( const bool& val );


	virtual String getCaption() ;

	virtual void setCaption( const String& caption );

	virtual void setImageIndex( const int32& imageIndex );

	virtual bool canPaint() {
		return true;
	}

	virtual void setBounds( Rect* bounds );

	virtual void setModel( Model* model );

	virtual double getTextCellWidth( GraphicsContext* context );

	virtual double getTextCellHeight( GraphicsContext* context );

	virtual const Color& getColor();

	virtual void setColor( Color* color );

	virtual const Font& getFont();

	virtual void setFont( Font* font );
private:
	void init();	
	String caption_;
	TableModel* tableModel_;
	Color* color_;
	typedef std::map<uint32,Color> ColorMap;
	static  ColorMap tableCellsColorMap;

	Font* font_;
	typedef std::map<String,Font> FontMap;
	static FontMap tableCellsFontMap;

	void onFontChanged( Event* e );
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABLECELLITEM_H__

/**
$Id$
*/
