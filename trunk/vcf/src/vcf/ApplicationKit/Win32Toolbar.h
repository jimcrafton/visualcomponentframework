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


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.3  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.2  2003/12/01 03:44:13  ddiego
*added some fixes to the Win32Toolbar impl. A few minor changes to the
*toolbar example (which also got added). Some minor changes to docs
*as well.
*
*Revision 1.1.2.1  2003/10/31 05:06:23  ddiego
*added toolbar impl
*
*/


#endif // _VCF_WIN32TOOLBAR_H__


