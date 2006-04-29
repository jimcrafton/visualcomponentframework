#ifndef _VCF_GTKTOOLBAR_H__
#define _VCF_GTKTOOLBAR_H__ 
//GTKToolbar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#ifndef _VCF_TOOLBARPEER_H__
#	include "vcf/ApplicationKit/ToolbarPeer.h"
#endif // _VCF_TOOLBARPEER_H__

namespace VCF
{

class ToolbarItem;
class ImageList;

class GTKToolbar : public AbstractGTKControl, public ToolbarPeer
{
public:

	GTKToolbar( Control* control );

	virtual void create( Control* control );

	virtual gboolean handleEvent( GdkEvent* gtkEvent );

	void insertToolbarButton( const ulong32& index,
	                          ToolbarItem* item,
	                          bool showCaption = false );

	void removeToolbarButton( ToolbarItem* item );

	virtual void setImageList( ImageList* imageList );

	virtual void showButtonCaptions( const bool& val );

	virtual void setButtonCaptionPlacementHorizontal( const bool& val );

	virtual void setButtonSize( const Size& buttonSize );

	virtual void setBorder( Border* border );

	virtual bool isAutoResizeEnabled();

	virtual void setEnableAutoResize( const bool& val );

protected:
	void onModelChanged( ModelEvent* e );
	bool currentlyModifyingItem_;
	void onImageListImageChanged( ImageListEvent* e );
};

}


#endif // _VCF_GTKTOOLBAR_H__

/**
$Id$
*/
