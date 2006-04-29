#ifndef _VCF_OSXTOOLBAR_H__
#define _VCF_OSXTOOLBAR_H__
//OSXToolbar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TOOLBARPEER_H__
#	include "vcf/ApplicationKit/ToolbarPeer.h"
#endif // _VCF_TOOLBARPEER_H__



namespace VCF  {

class ToolbarItem;
class ImageList;


class OSXToolbar : public OSXControl, public ToolbarPeer {
public:

	OSXToolbar(Control* control);


	virtual void create( Control* control );	

	virtual void setImageList( ImageList* imageList );

	virtual void showButtonCaptions( const bool& val );

	virtual void setButtonCaptionPlacementHorizontal( const bool& val );

	virtual void setButtonSize( const Size& buttonSize );

	virtual void setEnableAutoResize( const bool& val );

	virtual bool isAutoResizeEnabled();
protected:
	void onModelChanged( ModelEvent* e );
	
	bool currentlyModifyingItem_;

	void onImageListImageChanged( ImageListEvent* e );	
};





};


#endif // _VCF_OSXTOOLBAR_H__

/**
$Id$
*/
