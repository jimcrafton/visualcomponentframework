#ifndef _VCF_FONTPEER_H__
#define _VCF_FONTPEER_H__
//FontPeer.h

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

class GlyphCollection;

class Color;


/**
*Represents the native windowing system's representation of a Font.
*/
class GRAPHICSKIT_API FontPeer {
public:
	virtual ~FontPeer(){};

	/**
	*returns a integer representing some native handle to a font structure.
	*What this actually is depends on the Windowing system implementation.
	*Under Win32 this represents a pointer to a LOGFONT structure.
	*/
	virtual OSHandleID getFontHandleID()  = 0;

	virtual String getName()  = 0;

	virtual void setName( const String& name ) = 0;

	/**
	*is this font a TrueType font ?
	*/
	virtual bool isTrueType()  = 0;

	/**
	*return the point size of the Font. One point is 1/72 of an inch
	*( or 0.0352552 cm for our more civilized friends !), so to figure
	*out the pixels involved, find out the Pixels per Inch and then apply
	*the following formula
	*<code>
	* (PointSize / 72) * PPI
	*</code>
	*where PPI represents the Pixels Per Inch
	*/
	virtual double getPointSize()  = 0;

	/**
	*sets the point size of the FontPeer
	*/
	virtual void setPointSize( const double pointSize ) = 0;

	virtual double getPixelSize()  = 0;


	virtual void setPixelSize( const double pixelSize ) = 0;

	virtual void setBold( const bool& bold ) = 0;

	virtual bool getBold()  = 0;

	virtual bool getItalic()  = 0;

	virtual void setItalic( const bool& italic ) = 0;

	virtual bool getUnderlined()  = 0;

	virtual void setUnderlined( const bool& underlined ) = 0;

	virtual bool getStrikeOut()  = 0;

	virtual void setStrikeOut( const bool& strikeout ) = 0;
	
	/**
	sets ALL the attributes in one fell swoop
	*/
	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name ) = 0;

	virtual double getAscent() = 0;

	virtual double getDescent() = 0;

	virtual bool isFixedPitch() = 0;	

	virtual void setFont( Font* font ) = 0;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:05:58  ddiego
*added missing gtk files
*
*Revision 1.3  2005/01/02 03:04:25  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.3  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.2.4.2  2005/02/16 05:09:34  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2004/12/19 04:05:03  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/30 19:17:11  ddiego
*fixed some font issues. got rid of methods that are not implementable on other platforms
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/26 21:58:39  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.10  2003/05/17 20:37:09  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.2.1  2002/12/27 23:04:38  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.8  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.7.4.3  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.7.4.2  2002/09/28 22:22:35  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.7.4.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.7  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.6.6.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.6  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FONTPEER_H__


