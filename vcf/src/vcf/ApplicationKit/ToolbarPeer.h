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

};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.1  2003/11/04 02:20:29  ddiego
*added toolbar peer
*
*/


#endif // _VCF_TOOLBARPEER_H__


