#ifndef _VCF_WIN32TOOLBAR_H__
#define _VCF_WIN32TOOLBAR_H__
//Win32Toolbar.h

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


class Win32Toolbar : public AbstractWin32Component, public ToolbarPeer {
public:

	Win32Toolbar(Control* control);


	virtual void create( Control* control );

	virtual Win32Object::CreateParams createParams();


	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);


	void insertToolbarButton( const ulong32& index, ToolbarItem* item, bool showCaption=false );
	void removeToolbarButton( ToolbarItem* item );

	virtual void setImageList( ImageList* imageList );

	virtual void showButtonCaptions( const bool& val );

	virtual void setButtonCaptionPlacementHorizontal( const bool& val );

	virtual void setButtonSize( const Size& buttonSize );

	virtual bool acceptsWMCommandMessages(){
		return true;
	}

	virtual void setEnableAutoResize( const bool& val );
	virtual bool isAutoResizeEnabled();
protected:
	void onModelChanged( ModelEvent* e );
	//WNDPROC oldToolbarWndProc_;
	HIMAGELIST imageListCtrl_;

	bool currentlyModifyingItem_;

	void onImageListImageChanged( ImageListEvent* e );

	void resizeToolbarItems( int startAt=-1);
	std::map<VCF::String,int> buttonCaptionsMap_;

	void resetItems( std::vector<ToolbarItem*>& items );
};





};


#endif // _VCF_WIN32TOOLBAR_H__

/**
$Id$
*/
