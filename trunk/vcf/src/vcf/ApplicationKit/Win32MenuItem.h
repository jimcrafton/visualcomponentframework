#ifndef _VCF_WIN32MENUITEM_H__
#define _VCF_WIN32MENUITEM_H__
//Win32MenuItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_MENUITEMPEER_H__
#	include "vcf/ApplicationKit/MenuItemPeer.h"
#endif // _VCF_MENUITEMPEER_H__



namespace VCF
{

class Win32MenuItem : public MenuItemPeer
{
public:
	Win32MenuItem();

	Win32MenuItem( MenuItem* item );

	virtual ~Win32MenuItem();

	void init();

	virtual OSHandleID getMenuID();

	virtual void addChild( MenuItem* child );

	virtual void insertChild( const uint32& index, MenuItem* child );

	virtual void deleteChild( MenuItem* child );

	virtual void deleteChild( const uint32& index );

	virtual void clearChildren();

	virtual bool isChecked();

	virtual void setChecked( const bool& checked );

	virtual MenuItem* getParent();

	virtual bool hasParent();

	virtual MenuItem* getChildAt( const uint32& index );

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual bool isVisible();

	virtual void setVisible( const bool& visible );

	virtual bool getRadioItem();

	virtual void setRadioItem( const bool& value );

	virtual void setMenuItem( MenuItem* item );

	virtual void setCaption( const String& caption );

	virtual void setAsSeparator( const bool& isSeperator );

	virtual void setAcceleratorKey( AcceleratorKey* accelerator );

	void changePaintState();

	static MenuItem* getMenuItemFromID( const uint32 id );
	static MenuItem* getMenuItemFromHandle( HMENU handle );

	void fillInMeasureItemInfo( MEASUREITEMSTRUCT& measureItemInfo );	
protected:

	HMENU itemHandle_;
	uint32 itemId_;
	MenuItem* menuItem_;
	bool itemAdded_; //true if the item is added, false otherwise, in which case
					//fixChildren() should take care of it

	void insertSimpleMenuItem( MenuItem* child, HMENU menu );
	
	static std::map<uint32,MenuItem*> menuItemMap;
	static std::map<HMENU,MenuItem*> menuItemHandleMap;

	void fixChildren( MenuItem* child );

	String generateCaption( MenuItem* item, String caption );
};

};


#endif // _VCF_WIN32MENUITEM_H__

/**
$Id$
*/
