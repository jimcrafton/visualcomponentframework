#ifndef _VCF_X11FONT_H__
#define _VCF_X11FONT_H__
//X11Font.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
	This is the imlib2 font header (I got this from the test example that comes with the
	code. This probably will change (?), need to find this out, as well as is it possible to get
	the raw handle that freetype uses.
*/
class ImlibFontHdr {
public:
	ImlibFontHdr() :
			type(0),
			next(NULL),
			name(NULL),
			ref(0),
			font_count(0),
			font_struct(NULL),
			font_name(NULL),
			ascent(0),
			descent(0),
			max_ascent(0),
			max_descent(0),
			max_width(0),
			ttf(NULL)	{

		memset( &xfontset, 0, sizeof(XFontSet) );

	};

	int	type;
	ImlibFontHdr  *next;
	char	*name;
	int	ref;
	XFontSet xfontset;
	int font_count;
	XFontStruct **font_struct;
	char **font_name;
	int ascent;
	int descent;
	int max_ascent;
	int max_descent;
	int	max_width;
	ImlibFontHdr  *ttf;
};

class GRAPHICSKIT_API X11Font : public FontPeer , public Object {
public:
	X11Font( const String& fontName );

	X11Font( const String& fontName, const double& pointSize );

	virtual ~X11Font();

	void init();

	/**
	*returns a integer representing some native handle to a font structure.
	*What this actually is depends on the Windowing system implementation.
	*Under Win32 this represents a pointer to a LOGFONT structure.
	*/
	virtual ulong32 getFontHandleID() ;

	virtual String getName() ;

	virtual void setName( const String& name );

	/**
	*is this font a TrueType font ?
	*/
	virtual bool isTrueType() ;

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
	virtual double getPointSize() ;

	/**
	*sets the point size of the FontPeer
	*/
	virtual void setPointSize( const double pointSize );

	virtual double getPixelSize() ;

	virtual void setPixelSize( const double pixelSize );

	virtual void setBold( const bool& bold );

	virtual bool getBold() ;

	virtual bool getItalic() ;

	virtual void setItalic( const bool& italic );

	virtual bool getUnderlined() ;

	virtual void setUnderlined( const bool& underlined );

	virtual bool getStrikeOut() ;

	virtual void setStrikeOut( const bool& strikeout );

	virtual double getShear() ;

	virtual void setShear(const double& shear );

	virtual double getAngle() ;

	virtual void setAngle( const double& angle );

	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
					const bool& underlined, const bool& struckOut, const double& shear,
					const double& angle, const String& name );

	virtual double getAscent() ;

	virtual double getDescent() ;

	virtual double getExternalLeading() ;

	virtual double getInternalLeading() ;

	virtual double getHeight() ;

	virtual VCFChar getWordBreakCharacter() ;

	virtual VCFChar getFirstCharacter() ;

	virtual VCFChar getLastCharacter() ;


	/**
	*returns a GlyphCollection that represents the set of shapes
	*for the specified text string.
	*@param String text - the group of characters to put in the GlyphCollection
	*@return GlyphCollection the collection of Glyphs, or vectorized shapes that
	*represent the text string.
	*/
	virtual GlyphCollection* getGlyphCollection( const String& text ) ;

	virtual bool isEqual( Object* object );
protected:
	double shear_;
	double pointSize_;
	String fontName_;
	void updateTextMetrics();

	Imlib_Font imFont_;
	ImlibFontHdr* fontInfo_;
	String fontString_;
	void updateFont();
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.5.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4.2.1  2003/03/12 03:11:39  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.2.3  2002/12/27 23:04:42  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.3.2.2  2002/12/23 04:35:26  ddiego
*finished very basic support for fonts - so we can at least draw simple
*text now. Woohoo! and they are anti aliased at that!
*
*Revision 1.3.2.1  2002/12/22 04:47:59  ddiego
*basic integration of imlib2 is done for X11Context and X11Image, now
*starting on adding font support
*
*Revision 1.3  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.2.4.1  2002/09/28 22:22:46  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.2  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*
*/


#endif // _VCF_X11FONT_H__


