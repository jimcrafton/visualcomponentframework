//X11Font.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

X11Font::X11Font( const String& fontName ):
	imFont_(NULL),
	fontInfo_(NULL)
{
	pointSize_ = DEFAULT_FONT_PT_SIZE;
	fontName_ = fontName;

	if ( fontName_.empty() ) {
		//hack here - need a better way
		fontName_ = "ARIAL";
	}

	init();
}

X11Font::X11Font( const String& fontName, const double& pointSize ):
	imFont_(NULL),
	fontInfo_(NULL)
{
	pointSize_ = pointSize;
	fontName_ = fontName;
	init();
}

X11Font::~X11Font()
{
	if ( NULL != imFont_ ) {
		imlib_context_set_font( imFont_ );
		imlib_free_font();
	}
	//X11FontManager::removeFont( this );
}

void X11Font::init()
{
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	double dpi = toolkit->getDPI();
	int pixelSize = (int)((pointSize_ / 72.0) * dpi);

	fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

	updateFont();

	//X11FontManager::initializeFont( this );
}

void X11Font::updateFont()
{
	if ( NULL != imFont_ ) {
		imlib_context_set_font( imFont_ );
		imlib_free_font();
	}


	imFont_ = imlib_load_font( fontString_.c_str() );
	//printf( "%p = imlib_load_font( \"%s\" )\n", imFont_, fontString_.c_str() );
	fontInfo_ = (ImlibFontHdr*)imFont_;
	if ( NULL == imFont_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("imlib_load_font() failed to return a valid font handle!") );
	}
}

ulong32 X11Font::getFontHandleID()
{
	return (ulong32)imFont_;
}

bool X11Font::isTrueType()
{
	bool result = true;

	return result;
}



double X11Font::getPointSize()
{

	return pointSize_;
}

void X11Font::setPointSize( const double pointSize )
{
	bool needsUpdate = pointSize_ != pointSize;
	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}

	pointSize_ = pointSize;

	if ( true == needsUpdate ) {
		X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
		double dpi = toolkit->getDPI();
		int pixelSize = (int)((pointSize_ / 72.0) * dpi);

		fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

		updateFont();

		//X11FontManager::initializeFont( this );
	}
}

double X11Font::getPixelSize()
{
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	return (pointSize_ / 72.0) * toolkit->getDPI();
}

void X11Font::setPixelSize( const double pixelSize )
{


	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	double dpi = toolkit->getDPI();
	double tmp = (pixelSize * 72.0)/ dpi;

	bool needsUpdate = tmp != pointSize_;

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}

	pointSize_ = tmp;

	if ( true == needsUpdate ) {
		int pixelSize = (int)((pointSize_ / 72.0) * dpi);

		fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

		updateFont();
		//X11FontManager::initializeFont( this );
	}
}

void X11Font::setBold( const bool& bold )
{

	bool needsUpdate = false;//(style != logFont_.lfWeight);

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}


	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

bool X11Font::getBold()
{
	return false;//
}

bool X11Font::getItalic()
{
	return false ;//
}

void X11Font::setItalic( const bool& italic )
{

	bool needsUpdate = false;
	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}



	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

bool X11Font::getUnderlined()
{
	return false;
}

void X11Font::setUnderlined( const bool& underlined )
{

	bool needsUpdate = false;//(lfUnderlined != logFont_.lfUnderline);
	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}



	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

bool X11Font::getStrikeOut()
{
	return false;
}

void X11Font::setStrikeOut( const bool& strikeout )
{


	bool needsUpdate = false;//(lfStrikeOut != logFont_.lfStrikeOut);

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}



	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

double X11Font::getShear()
{
	return this->shear_;
}

void X11Font::setShear(const double& shear )
{
	this->shear_ = shear;
}

double X11Font::getAngle()
{
	double tmp = (double)0.0;
	return tmp;
}

void X11Font::setAngle( const double& angle )
{
	bool needsUpdate = false;

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}


	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

String X11Font::getName()
{
	String result = "";

	return fontName_;
}

void X11Font::setName( const String& name )
{
	bool needsUpdating = name != fontName_;
	if ( true == needsUpdating ) {
		//X11FontManager::removeFont( this );
	}

	fontName_ = name;

	if ( true == needsUpdating ) {
		X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
		double dpi = toolkit->getDPI();
		int pixelSize = (int)((pointSize_ / 72.0) * dpi);

		fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

		updateFont();
		//X11FontManager::initializeFont( this );
	}
}

GlyphCollection* X11Font::getGlyphCollection( const String& text )
{
	return NULL;
}

bool X11Font::isEqual( Object* object )
{
	bool result = false;
	X11Font* fntObj = dynamic_cast<X11Font*>(object);
	if ( NULL != fntObj ){

		if ( (this->fontName_ == fntObj->fontName_) &&
			 (this->pointSize_ == fntObj->pointSize_) ) {
			result = true;
		}
	}

	return result;
}

void X11Font::updateTextMetrics()
{

}

double X11Font::getAscent()
{
	double result = 0.0;

	if ( NULL != imFont_ ) {
		Imlib_Font current = imlib_context_get_font();

		imlib_context_set_font( imFont_ );

		result = (double)imlib_get_font_ascent();

		imlib_context_set_font( current );
	}
	return result;
}

double X11Font::getDescent()
{
	double result = 0.0;

	if ( NULL != imFont_ ) {
		Imlib_Font current = imlib_context_get_font();

		imlib_context_set_font( imFont_ );

		result = (double)imlib_get_font_descent();

		imlib_context_set_font( current );
	}
	return result;
}

double X11Font::getExternalLeading()
{
	return 0.0;
}

double X11Font::getInternalLeading()
{
	return 0.0;
}

double X11Font::getHeight()
{
	double result = 0.0;

	if ( NULL != imFont_ ) {
		Imlib_Font current = imlib_context_get_font();

		imlib_context_set_font( imFont_ );

		result = (double)imlib_get_font_descent() + (double)imlib_get_font_ascent();

		imlib_context_set_font( current );
	}
	return result;
}

VCFChar X11Font::getWordBreakCharacter()
{
	return ' ';
}

VCFChar X11Font::getFirstCharacter()
{
	return 0;
}

VCFChar X11Font::getLastCharacter()
{
	return 0;
}

void X11Font::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const double& shear,
								const double& angle, const String& name )
{
	pointSize_ = pointSize;
	fontName_ = name;
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	double dpi = toolkit->getDPI();
	int pixelSize = (int)((pointSize_ / 72.0) * dpi);

	fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

	updateFont();

	updateTextMetrics();
}


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
*Revision 1.5  2003/05/17 20:37:40  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.1  2003/03/12 03:12:45  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.2.8  2003/01/23 04:38:25  ddiego
*fixes to x port - issues with lightweight controls not quite drawing right. - a
*bug in the line drawing code when the origin is not 0,0
*
*Revision 1.3.2.7  2003/01/19 03:11:59  ddiego
*misc coding fixes, added x11 error handler
*
*Revision 1.3.2.6  2003/01/08 03:49:18  ddiego
*fixes to ensure that move and size events get sent properly. Not sure
*I am happy with how it is currently working. Fix to X11Cursor so that the cursorID
*has a valid initial value.
*
*Revision 1.3.2.5  2003/01/08 00:19:54  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.3.2.4  2003/01/02 04:07:46  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.3.2.3  2002/12/27 23:04:56  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.3.2.2  2002/12/23 04:36:32  ddiego
*finished very basic support for fonts - so we can at least draw simple
*text now. Woohoo! and they are anti aliased at that!
*
*Revision 1.3.2.1  2002/12/22 04:48:23  ddiego
*basic integration of imlib2 is done for X11Context and X11Image, now
*starting on adding font support
*
*Revision 1.3  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.2.4.1  2002/09/28 22:22:46  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.2  2002/09/12 03:26:05  ddiego
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


