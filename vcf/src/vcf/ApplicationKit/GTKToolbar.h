#ifndef _VCF_GTKTOOLBAR_H__
#define _VCF_GTKTOOLBAR_H__
//GTKToolbar.h

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


class GTKToolbar : public AbstractGTKControl, public ToolbarPeer {
public:

	GTKToolbar(Control* control);


	virtual void create( Control* control );

	virtual gboolean handleEvent( GdkEvent* gtkEvent );


	void insertToolbarButton( const ulong32& index, ToolbarItem* item, bool showCaption=false );
	void removeToolbarButton( ToolbarItem* item );

	virtual void setImageList( ImageList* imageList );

	virtual void showButtonCaptions( const bool& val );

	virtual void setButtonCaptionPlacementHorizontal( const bool& val );

	virtual void setButtonSize( const Size& buttonSize );

protected:
	void onModelChanged( ModelEvent* e );
	bool currentlyModifyingItem_;
	void onImageListImageChanged( ImageListEvent* e );
};





};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.1  2003/11/01 20:39:35  ddiego
*added gtk toolbar - no implementation yet
*
*Revision 1.1.2.1  2003/10/31 05:06:23  ddiego
*added toolbar impl
*
*/


#endif // _VCF_GTKTOOLBAR_H__


