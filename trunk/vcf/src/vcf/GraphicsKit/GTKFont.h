#ifndef _VCF_GTKFONT_H__
#define _VCF_GTKFONT_H__ 
//GTKFont.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

/**
 
*/
class GTKFont : public Object, public FontPeer
{
public:
	GTKFont( const String& fontName );

	GTKFont( const String& fontName, const double& pointSize );

	virtual ~GTKFont();

	void init();

	virtual OSHandleID getFontHandleID();

	virtual String getName();

	virtual void setName( const String& name );

	virtual bool isTrueType();

	virtual double getPointSize();

	virtual void setPointSize( const double pointSize );

	virtual double getPixelSize();

	virtual void setPixelSize( const double pixelSize );

	virtual void setBold( const bool& bold );

	virtual bool getBold();

	virtual bool getItalic();

	virtual void setItalic( const bool& italic );

	virtual bool getUnderlined();

	virtual void setUnderlined( const bool& underlined );

	virtual bool getStrikeOut();

	virtual void setStrikeOut( const bool& strikeout );

	//virtual double getShear();

	//virtual void setShear( const double& shear );

	//virtual double getAngle();

	//virtual void setAngle( const double& angle );
	
	virtual void setAttributes( const double& pointSize,
	                            const bool& bold,
	                            const bool& italic,
	                            const bool& underlined,
	                            const bool& struckOut,
	                            //const double& shear,
	                            //const double& angle,
	                            const String& name );

	virtual double getAscent();

	virtual double getDescent();

	//virtual double getExternalLeading();

	//virtual double getInternalLeading();

	//virtual double getHeight();

	//virtual VCFChar getWordBreakCharacter();

	//virtual VCFChar getFirstCharacter();

	//virtual VCFChar getLastCharacter();

	virtual GlyphCollection* getGlyphCollection( const String& text );

	virtual void setFont( Font* font );

	//virtual bool isEqual( Object* object );

	PangoFontDescription* getPangoFontDescription()
	{
		return fontDescriptor_;
	}
protected:
	PangoFontDescription* fontDescriptor_;
};

}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:23  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/04/14 19:10:30  ddiego
*mods to better support fonts and text using Pango - not finished, and
*may not compile
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/20 02:46:02  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Auto generated header for class GTKFont
*/


#endif // _VCF_GTKFONT_H__


