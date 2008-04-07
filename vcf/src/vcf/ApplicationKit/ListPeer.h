#ifndef _VCF_LISTPEER_H__
#define _VCF_LISTPEER_H__
//ListPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class ListItem;




/**
\class ListPeer ListPeer.h "vcf/ApplicationKit/ListPeer.h"
*/

class APPLICATIONKIT_API ListPeer  {
public:
	virtual ~ListPeer(){};	

	virtual void selectItem( const uint32& index ) = 0;

	virtual uint32 getSelectedItem() = 0;

	virtual void setFocusedItem( const uint32& index ) = 0;

	virtual uint32 getFocusedItem() = 0;

	virtual bool isItemSelected( const uint32& index ) = 0;

	virtual Rect getItemRect( const uint32& index ) = 0;	

	virtual Rect getItemImageRect( const uint32& index ) = 0;

	virtual uint32 hitTest( const Point& point ) = 0;	

	virtual Enumerator<uint32>* getSelectedItems() = 0;

	virtual void rangeSelect( const Rect& selectionRect ) = 0;	

	virtual bool allowsMultiSelect() = 0;

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect ) = 0;	

	virtual void setLargeImageList( ImageList* imageList ) = 0;

	virtual void setSmallImageList( ImageList* imageList ) = 0;		
};

}


#endif // _VCF_LISTPEER_H__

/**
$Id$
*/
