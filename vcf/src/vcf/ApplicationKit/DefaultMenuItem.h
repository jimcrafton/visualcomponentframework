#ifndef _VCF_DEFAULTMENUITEM_H__
#define _VCF_DEFAULTMENUITEM_H__
//DefaultMenuItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class MenuItemPeer;

#define DEFAULTMENUITEM_CLASSID		"15307228-7207-44c8-8b22-4d5575648ae8"

/**
\class DefaultMenuItem DefaultMenuItem.h "vcf/ApplicationKit/DefaultMenuItem.h"
*/
class APPLICATIONKIT_API DefaultMenuItem : public MenuItem {

public:
	DefaultMenuItem();

	DefaultMenuItem( const String& caption, MenuItem* parent=NULL, Menu* menuOwner=NULL );

	virtual ~DefaultMenuItem();

	void init();	


	virtual bool containsPoint( Point * pt );

    virtual uint32 getIndex() const;

	virtual void setIndex( const uint32& index );
    
	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual bool isSelected() const ;

	virtual void setSelected( const bool& selected );

	virtual Enumerator<MenuItem*>* getChildren();

	virtual void addChild( MenuItem* child );

	virtual void insertChild( const uint32& index, MenuItem* child );

	virtual void deleteChild( MenuItem* child );

	virtual void deleteChild( const uint32& index );

	virtual void clearChildren();

	virtual bool isChecked() const;

	virtual void setChecked( const bool& checked );

	virtual bool hasParent() const;

	virtual bool hasChildren() const;

	virtual uint32 getChildCount() const;

	virtual Menu* getMenuOwner() const;

	virtual void setMenuOwner( Menu* menuOwner );

	virtual MenuItem* getParent() const;

	virtual void setParent( MenuItem* parent );

	virtual MenuItem* getChildAt( const uint32& index );

	virtual MenuItem* findChildNamed( const String& name, const bool& exactMatch=true );

	virtual bool isEnabled() const;

	virtual void setEnabled( const bool& enabled );

	virtual bool isVisible() const;

	virtual void setVisible( const bool& visible );

	virtual bool getRadioItem() const;

	virtual void setRadioItem( const bool& value );

	virtual void setCaption( const String& caption );

	virtual String getCaption() const;

	virtual MenuItemPeer* getPeer() const;

	virtual bool isSeparator() const;

	virtual void setSeparator( const bool& separator );

	virtual bool isHighlighted() const;

	virtual void setHighlighted( const bool& val );

	virtual void click();

	virtual void update();

	virtual void setImageIndex( const int32& imageIndex );

	virtual bool canPaint() const ;
	
	virtual void setCanPaint( const bool& val );
	
	virtual void setAcceleratorKeyInfo( const VirtualKeyCode& keyCode, const uint32& modifierMask );

	virtual void setAcceleratorKey( AcceleratorKey* accelerator );

	virtual AcceleratorKey* getAccelerator() const;

	virtual uint32 getChildIndex( MenuItem* child ) const;
	
	virtual Object* clone(bool deep=false) const;

	virtual void handleEvent( Event* event );
protected:
	void onAccelerator( KeyboardEvent* e );

protected:
	Array<MenuItem*> menuItems_;
	String caption_;
	Menu* menuOwner_;
	MenuItem* parent_;
	mutable AcceleratorKey* currentAccelerator_;
};



/**
\class SeparatorMenuItem DefaultMenuItem.h "vcf/ApplicationKit/DefaultMenuItem.h"
* a class to help creating a separator menu item
*/
class APPLICATIONKIT_API SeparatorMenuItem : public DefaultMenuItem {
public:
	SeparatorMenuItem( MenuItem* parent, Menu* menuOwner=NULL ) :
		DefaultMenuItem( "", parent, menuOwner) {
		setSeparator( true );
	}
};


}; // namespace VCF


#endif // _VCF_DEFAULTMENUITEM_H__

/**
$Id$
*/
