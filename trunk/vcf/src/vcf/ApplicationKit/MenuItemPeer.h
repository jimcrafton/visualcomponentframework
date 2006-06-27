#ifndef _VCF_MENUITEMPEER_H__
#define _VCF_MENUITEMPEER_H__
//MenuItemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class MenuItem;
/**
\class MenuItemPeer MenuItemPeer.h "vcf/ApplicationKit/MenuItemPeer.h"
*/
class APPLICATIONKIT_API MenuItemPeer {
public:
	virtual ~MenuItemPeer(){};

	virtual OSHandleID getMenuID() = 0;

	virtual void addChild( MenuItem* child ) = 0;

	virtual void insertChild( const uint32& index, MenuItem* child ) = 0;

	virtual void deleteChild( MenuItem* child ) = 0;

	virtual void deleteChild( const uint32& index ) = 0;

	virtual void clearChildren() = 0;

	virtual bool isChecked() = 0;

	virtual void setChecked( const bool& checked ) = 0;

	virtual MenuItem* getParent() = 0;

	virtual bool hasParent() = 0;

	virtual MenuItem* getChildAt( const uint32& index ) = 0;

	virtual bool isEnabled() = 0;

	virtual void setEnabled( const bool& enabled ) = 0;

	virtual bool isVisible() = 0;

	virtual void setVisible( const bool& visible ) = 0;

	virtual bool getRadioItem() = 0;

	virtual void setRadioItem( const bool& value ) = 0;

	virtual void setMenuItem( MenuItem* item ) = 0;

	virtual void setCaption( const String& caption ) = 0;

	virtual void setAsSeparator( const bool& isSeperator ) = 0;

	virtual void setAcceleratorKey( AcceleratorKey* accelerator ) = 0;
};

};


#endif // _VCF_MENUITEMPEER_H__

/**
$Id$
*/
