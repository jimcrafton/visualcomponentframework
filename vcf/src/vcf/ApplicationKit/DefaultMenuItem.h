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

    virtual unsigned long getIndex();

	virtual void setIndex( const unsigned long& index );

    virtual void* getData();

	virtual void setData( void* data );	

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual bool isSelected();

	virtual void setSelected( const bool& selected );

	virtual Enumerator<MenuItem*>* getChildren();

	virtual void addChild( MenuItem* child );

	virtual void insertChild( const unsigned long& index, MenuItem* child );

	virtual void deleteChild( MenuItem* child );

	virtual void deleteChild( const unsigned long& index );

	virtual void clearChildren();

	virtual bool isChecked();

	virtual void setChecked( const bool& checked );

	virtual bool hasParent();

	virtual bool hasChildren();

	virtual unsigned long getChildCount();

	virtual Menu* getMenuOwner();

	virtual void setMenuOwner( Menu* menuOwner );

	virtual MenuItem* getParent();

	virtual void setParent( MenuItem* parent );

	virtual MenuItem* getChildAt( const unsigned long& index );

	virtual MenuItem* findChildNamedSimilarTo( const String& name );

	virtual MenuItem* findChildNamed( const String& name );

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual bool isVisible();

	virtual void setVisible( const bool& visible );

	virtual bool getRadioItem();

	virtual void setRadioItem( const bool& value );

	virtual void setCaption( const String& caption );

	virtual String getCaption();

	virtual MenuItemPeer* getPeer();

	virtual bool isSeparator();

	virtual void setSeparator( const bool& separator );

	virtual void click();

	virtual void update();

	virtual Rect* getBounds() {
		return &bounds_;
	}

	virtual long getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const long& imageIndex );

	virtual bool canPaint();
	
	virtual void setCanPaint( const bool& val );

	virtual void setBounds( Rect* bounds );

	/**
	*not supported
	*/
	virtual long getStateImageIndex(){
		return -1;
	};

	/**
	*not supported
	*/
	virtual void setStateImageIndex( const long& index ){}

	virtual void setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	virtual void setAcceleratorKey( AcceleratorKey* accelerator );

	virtual AcceleratorKey* getAccelerator();

	virtual uint32 getChildIndex( MenuItem* child );
	
	virtual Object* clone(bool deep=false);

	virtual void handleEvent( Event* event );
protected:
	void onAccelerator( KeyboardEvent* e );

protected:
	std::vector<MenuItem*> menuItems_;
	EnumeratorContainer<std::vector<MenuItem*>, MenuItem*> container_;
	String caption_;
	void* data_;
	Menu* menuOwner_;
	MenuItem* parent_;
	long imageIndex_;
	Rect bounds_;
	AcceleratorKey* currentAccelerator_;
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
