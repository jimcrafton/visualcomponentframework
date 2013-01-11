#ifndef _VCF_TOOLBARPEER_H__
#define _VCF_TOOLBARPEER_H__
//ToolbarPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class APPLICATIONKIT_API ToolbarPeer {
public:
	virtual ~ToolbarPeer(){}

	virtual void setImageList( ImageList* imageList ) = 0;

	virtual void showButtonCaptions( const bool& val ) = 0;

	virtual void setButtonCaptionPlacementHorizontal( const bool& val ) = 0;

	virtual void setButtonSize( const Size& buttonSize ) = 0;

	virtual void setEnableAutoResize( const bool& val ) = 0;
	virtual bool isAutoResizeEnabled() = 0;

	virtual void setVertical( const bool& val ) = 0; 
	virtual bool isVertical() = 0;

	virtual void setWrapButtons( const bool& val ) = 0; 
	virtual bool isWrapButtons() = 0;

};


};


#endif // _VCF_TOOLBARPEER_H__

/**
$Id$
*/
