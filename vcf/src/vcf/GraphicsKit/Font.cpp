//Font.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"


using namespace VCF;

Font::Font():
	peer_(NULL),
	locale_(NULL)
{
	peer_ = GraphicsToolkit::createFontPeer( "" );
	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}
}

Font::Font( const String& fontName ):
	peer_(NULL),
	locale_(NULL)
{
	peer_ = GraphicsToolkit::createFontPeer( fontName );
	if ( NULL == peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->setFont( this );
}

Font::Font( const String& fontName, const double& pointSize ):
	peer_(NULL),
	locale_(NULL)
{

	peer_ = GraphicsToolkit::createFontPeer( fontName, pointSize );
	if ( NULL == peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->setFont( this );
}

Font::Font( const Font& font ):
    Object( font ),
	peer_(NULL),
	locale_(NULL)
{
	peer_ = GraphicsToolkit::createFontPeer( font.getName() );
	if ( NULL == peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->setFont( this );

	*this = font;
}

Font::~Font()
{
	delete peer_;
}


Font& Font::operator= (const Font& rhs )
{
	setAttributes( rhs.getPointSize(), rhs.getBold(), rhs.getItalic(), rhs.getUnderlined(),
					rhs.getStrikeOut(), &rhs.color_, rhs.getName() );

	locale_ = rhs.locale_;
	return *this;
}

void Font::setLocale( Locale* locale )
{
	locale_ = locale;
}

bool Font::isTrueType()  const

{
	return peer_->isTrueType();
}

Color* Font::getColor()
{
	return &color_;
}

void Font::setColor( Color* color )
{
	if ( NULL != color ) {
		color_ = *color;
	}
}

double Font::getPointSize()  const
{
	return peer_->getPointSize();
}

void Font::setPointSize( const double& pointSize )
{
	peer_->setPointSize( pointSize );
}

double Font::getPixelSize()  const
{
	return peer_->getPixelSize();
}

void Font::setPixelSize( const double& pixelSize )
{
	peer_->setPixelSize( pixelSize );
}

void Font::setBold( const bool& bold )
{
	peer_->setBold( bold );
}

bool Font::getBold()  const
{
	return peer_->getBold();
}

bool Font::getItalic()  const
{
	return peer_->getItalic();
}

void Font::setItalic( const bool& italic )
{
	peer_->setItalic( italic );
}

bool Font::getUnderlined()  const
{
	return peer_->getUnderlined();
}

void Font::setUnderlined( const bool& underlined )
{
	peer_->setUnderlined( underlined );
}

bool Font::getStrikeOut()  const
{
	return peer_->getStrikeOut();
}

void Font::setStrikeOut( const bool& strikeout )
{
	peer_->setStrikeOut( strikeout );
}



GlyphCollection* Font::getGlyphCollection( const String& text )
{
	return peer_->getGlyphCollection( text );
}

FontPeer* Font::getFontPeer()
{
	return peer_;
}

String Font::getName()  const
{
	return peer_->getName();
}

void Font::setName( const String& name )
{
	peer_->setName( name );
}

void Font::copy( Object* source )
{
	if ( NULL != source ){
		Font* srcFont = dynamic_cast<Font*>( source );
		if ( NULL != srcFont ){
			setStrikeOut( srcFont->getStrikeOut() );
			setUnderlined( srcFont->getUnderlined() );
			setBold( srcFont->getBold() );
			setItalic( srcFont->getItalic() );
			setPointSize( srcFont->getPointSize() );
			setName( srcFont->getName() );

			Color* srcColor = srcFont->getColor();
			getColor()->copy( srcColor );
		}
	}
}

double Font::getAscent()  const
{
	return peer_->getAscent();
}

double Font::getDescent()  const
{
	return peer_->getDescent();
}

double Font::getHeight()  const
{
	return peer_->getAscent() + peer_->getDescent();
}



void Font::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const Color* color, const String& name )
{

	peer_->setAttributes( pointSize, bold, italic, underlined, struckOut, name );
	if ( NULL != color ) {
		color_ = *color;
	}
}


/**
*CVS Log info
*$Log$
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
*Revision 1.12  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.11.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.11.2.1  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*Revision 1.11  2003/05/17 20:37:21  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:12:00  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.2.2  2002/12/27 23:04:47  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.2.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.9  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.8.4.3  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.8.4.2  2002/09/28 22:22:46  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.8.4.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.8  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.12.2  2002/09/03 05:05:13  ddiego
*fixed some more bugs in getting form building to work again. It now works
*but of course there are new issues, namely reading in nested properties
*in a form file where the properties are objects like:
*font.color.red, so this needs to be fixed in hte VFFInputStream file
*also need to have hte form saved properly
*still miscellaneous crashes but getting closer to an alpha tes state
*
*Revision 1.7.12.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


