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

	virtual ulong32 getMenuID();

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

	static MenuItem* getMenuItemFromID( const uint32 id );
	static MenuItem* getMenuItemFromHandle( HMENU handle );

	void fillInMeasureItemInfo( MEASUREITEMSTRUCT& measureItemInfo );

	void drawDefaultMenuItem( const UINT& idCtl, DRAWITEMSTRUCT& drawItemStruct );
private:
	HMENU itemHandle_;
	uint32 itemId_;
	MenuItem* menuItem_;
	bool itemAdded_; //true if the item is added, false otherwise, in which case
					//fixChildren() should take care of it

	void insertSimpleMenuItem( MenuItem* child, HMENU menu );

	bool draw3DCheckmark( HDC dc, const RECT& rc, const bool& bSelected, HBITMAP hbmCheck );

	void fillMenuItemRect( HDC dc, const RECT& rc, COLORREF color );

	void drawMenuItemText( HDC dc, RECT rc, COLORREF color );

	static std::map<uint32,MenuItem*> menuItemMap;
	static std::map<HMENU,MenuItem*> menuItemHandleMap;

	void fixChildren( MenuItem* child );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.16.2.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.16  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.2  2004/03/21 00:39:22  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.13.2.1  2004/01/15 16:14:19  ddiego
*some minor change to the WIn32MenuItem class to support inserting menus better
*
*Revision 1.13  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.2  2003/10/09 22:06:15  ddiego
*menu item fix
*
*Revision 1.12.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:11:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/04/27 15:52:19  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32MENUITEM_H__


