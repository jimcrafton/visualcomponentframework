#ifndef _VCF_X11GRAPHICSTOOLKIT_H__
#define _VCF_X11GRAPHICSTOOLKIT_H__
//X11GraphicsToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
*Class X11GraphicsToolkit documentation
*/
class X11GraphicsToolkit : public GraphicsToolkit {
public:
	X11GraphicsToolkit();

	virtual ~X11GraphicsToolkit();

	virtual ContextPeer* createContextPeer( const unsigned long& width, const unsigned long& height );

	virtual ContextPeer* createContextPeer( const long& contextID );

	virtual FontPeer* createFontPeer( const String& fontName );

	virtual FontPeer* createFontPeer( const String& fontName, const double& pointSize );

	virtual OpenGLPeer* createOpenGLPeer( GraphicsContext* glContext );

	virtual Image* createImage( const unsigned long& width, const unsigned long& height );

	virtual Image* createImage( GraphicsContext* context, Rect* rect );

	virtual Font* getDefaultSystemFont() {
		return systemFont_;
	}

	//X11 specific functions

	double getDPI();

	Display* getX11Display() {
		return X11Display_;
	}

	int getX11ScreenID() {
		return X11ScreenID_;
	}

	ulong32 getPixelForColor( Color* color );

	/**
	this should return a path that represents the common font directory available to
	all users. By default this will be in /usr/local/share/fonts unless changed by the
	X11GraphicsToolkit implementation
	*/
	String getSharedFontsPath();

	/**
	this will return a path to the users font directory. Typically this is
	$HOME/fonts
	*/
	String getUserFontsPath();
protected:

	void initSystemFont();
	void loadSystemColors();
	virtual void initSystemFontNames();

	Font* systemFont_;
	Display* X11Display_;
	int X11ScreenID_;

	std::map<ulong32,ulong32> colorLookupMap_;
private:
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
*Revision 1.4.2.1  2003/03/12 03:11:40  ddiego
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
*Revision 1.3.2.6  2002/12/27 23:04:43  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.3.2.5  2002/12/23 04:35:27  ddiego
*finished very basic support for fonts - so we can at least draw simple
*text now. Woohoo! and they are anti aliased at that!
*
*Revision 1.3.2.4  2002/12/22 04:47:59  ddiego
*basic integration of imlib2 is done for X11Context and X11Image, now
*starting on adding font support
*
*Revision 1.3.2.3  2002/12/15 05:14:41  ddiego
*color allocation now more efficient
*
*Revision 1.3.2.2  2002/12/10 05:33:56  ddiego
*more drawing support, now partial support for copying contexts, and more
*drawXXX methods implemented
*
*Revision 1.3.2.1  2002/12/08 04:48:29  ddiego
*more code to X11Context - uses a Drawable handle directly now
*fleshing out more functions
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
*Revision 1.1.2.3  2002/09/05 21:49:44  ddiego
*added support for kevboard events in deleting a component and
*setting a property value
*some miscellaneous fixes
*some merges in the xmake makefiles for FK and GK
*
*Revision 1.1.2.2  2002/08/08 05:02:59  ddiego
*added a test for X11 GraphicsKit testing
*fixed bug in initializing the graphicsKit, actually I just
*realized this will cause another but - take out automatice initialization of
*FoundationKit from GraphicsKit
*
*Revision 1.1.2.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_X11GRAPHICSTOOLKIT_H__


