#ifndef _VCF_OSXMENUITEM_H__
#define _VCF_OSXMENUITEM_H__
//OSXMenuItem.h

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



namespace VCF  {

class OSXMenuItem : public MenuItemPeer {
public:
	enum {
		propertyTag = 'VCmn'
	};
	
	OSXMenuItem();

	OSXMenuItem( MenuItem* item );

	virtual ~OSXMenuItem();

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

	bool isMenuItemRoot();
	
	bool isParentMenuItemRoot();
	
	static bool isMenuItemRoot( MenuItem* item );
	
	static bool isParentMenuItemRoot( MenuItem* item );
	
	void fixChildren( MenuItem* child );
	
	
protected:
	uint32 itemID_;
	MenuItem* menuItem_;
	MenuRef itemHandle_;
	bool itemAdded_;
	static uint32 globalMenuItemID;
};

};


#endif //_VCF_OSXMENUITEM_H__

/**
$Id$
*/
