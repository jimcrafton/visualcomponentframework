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

	virtual void insertChild( const unsigned long& index, MenuItem* child );

	virtual void deleteChild( MenuItem* child );

	virtual void deleteChild( const unsigned long& index );

	virtual void clearChildren();

	virtual bool isChecked();

	virtual void setChecked( const bool& checked );

	virtual MenuItem* getParent();

	virtual bool hasParent();

	virtual MenuItem* getChildAt( const unsigned long& index );

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


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.2.2.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
*
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/11/15 05:41:28  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.1.2.1  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*/

#endif //_VCF_OSXMENUITEM_H__