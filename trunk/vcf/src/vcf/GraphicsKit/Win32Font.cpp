//Win32Font.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

Win32Font::Win32Font( const String& fontName ):
	font_(NULL),
	pointSize_(-1.0),
	fontName_(fontName),
	logFont_(NULL),
	tm_(NULL)
{
	init();
}

Win32Font::Win32Font( const String& fontName, const double& pointSize ):
	font_(NULL),
	pointSize_(pointSize),
	fontName_(fontName),
	logFont_(NULL),
	tm_(NULL)
{
	init();
}

Win32Font::~Win32Font()
{
	Win32FontManager::removeFont( this );
	//fontName_ = "";

	if ( System::isUnicodeEnabled() ) {
		delete (LOGFONTW*)logFont_;
		delete (TEXTMETRICW*)tm_;
	}
	else {
		delete (LOGFONTA*)logFont_;
		delete (TEXTMETRICA*)tm_;
	}
}

void Win32Font::init()
{


	if ( System::isUnicodeEnabled() ) {
		logFont_ = new LOGFONTW;
		memset( logFont_, 0, sizeof(LOGFONTW) );

		tm_ = new TEXTMETRICW;
		memset( tm_, 0, sizeof(TEXTMETRICW) );
	}
	else {
		logFont_ = new LOGFONTA;
		memset( logFont_, 0, sizeof(LOGFONTA) );

		tm_ = new TEXTMETRICA;
		memset( tm_, 0, sizeof(TEXTMETRICA) );
	}

	int fontHeight = 0;

	HFONT defFont = (HFONT)GetStockObject( ANSI_VAR_FONT );//DEFAULT_GUI_FONT );
	//defFont = NULL;
	if ( NULL != defFont ){
		if ( System::isUnicodeEnabled() ) {

			LOGFONTW tmpLogFont = {0};
			GetObjectW( defFont, sizeof(LOGFONTW), &tmpLogFont );
			memcpy( logFont_, &tmpLogFont, sizeof(LOGFONTW));
		}
		else {
			LOGFONTA tmpLogFont = {0};
			GetObjectA( defFont, sizeof(LOGFONTA), &tmpLogFont );
			memcpy( logFont_, &tmpLogFont, sizeof(LOGFONTA));
		}
	}
	else {
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW& tmpLF = *((LOGFONTW*)logFont_);
			tmpLF.lfCharSet = ANSI_CHARSET;//DEFAULT_CHARSET might be better ?
			tmpLF.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			tmpLF.lfEscapement = 0;
			tmpLF.lfItalic = FALSE;
			tmpLF.lfOrientation = 0;
			tmpLF.lfOutPrecision = OUT_DEFAULT_PRECIS;
			tmpLF.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
			tmpLF.lfQuality = DEFAULT_QUALITY;
			tmpLF.lfStrikeOut = FALSE;
			tmpLF.lfUnderline = FALSE;
			tmpLF.lfWeight = FW_NORMAL;
			tmpLF.lfWidth = 0;//let font mapper choose closest match
			fontHeight = tmpLF.lfHeight;
		}
		else{
			LOGFONTA& tmpLF = *((LOGFONTA*)logFont_);
			tmpLF.lfCharSet = ANSI_CHARSET;//DEFAULT_CHARSET might be better ?
			tmpLF.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			tmpLF.lfEscapement = 0;
			tmpLF.lfItalic = FALSE;
			tmpLF.lfOrientation = 0;
			tmpLF.lfOutPrecision = OUT_DEFAULT_PRECIS;
			tmpLF.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
			tmpLF.lfQuality = DEFAULT_QUALITY;
			tmpLF.lfStrikeOut = FALSE;
			tmpLF.lfUnderline = FALSE;
			tmpLF.lfWeight = FW_NORMAL;
			tmpLF.lfWidth = 0;//let font mapper choose closest match
			fontHeight = tmpLF.lfHeight;
		}
	}

	if ( System::isUnicodeEnabled() ) {
		fontHeight = ((LOGFONTW*)logFont_)->lfHeight;
	}
	else{
		fontHeight = ((LOGFONTA*)logFont_)->lfHeight;
	}

	HDC dc = GetDC( ::GetDesktopWindow() );//gets screen DC

	if ( pointSize_ > 0.0 ) {
		fontHeight = -MulDiv( pointSize_, GetDeviceCaps( dc, LOGPIXELSY), 72 );
	}


	ReleaseDC( ::GetDesktopWindow(), dc );

	if ( System::isUnicodeEnabled() ) {
		LOGFONTW& tmpLF = *((LOGFONTW*)logFont_);

		tmpLF.lfHeight = fontHeight;

		if ( fontName_.empty() ) {
			fontName_.append( tmpLF.lfFaceName, LF_FACESIZE );
		}
		else {
			memset( ((LOGFONTW*)logFont_)->lfFaceName, 0, LF_FACESIZE*sizeof(VCFChar) );
			fontName_.copy( tmpLF.lfFaceName, minVal<int>( fontName_.size(), LF_FACESIZE) );
		}
	}
	else {
		LOGFONTA& tmpLF = *((LOGFONTA*)logFont_);

		tmpLF.lfHeight = fontHeight;

		if ( fontName_.empty() ) {
			fontName_.append( tmpLF.lfFaceName, LF_FACESIZE );
		}
		else {
			AnsiString tmpFntName = fontName_;
			memset( ((LOGFONTA*)logFont_)->lfFaceName, 0, LF_FACESIZE*sizeof(char) );
			tmpFntName.copy( tmpLF.lfFaceName, minVal<int>( tmpFntName.size(), LF_FACESIZE) );
		}
	}


	updateTextMetrics();

	Win32FontManager::initializeFont( this );
}

ulong32 Win32Font::getFontHandleID()
{
	return (ulong32)logFont_;
}

void Win32Font::updateTextMetrics()
{
	HDC dc = GetDC( ::GetDesktopWindow() );//gets screen DC

	int dcs = ::SaveDC( dc );



	HFONT tmpFont = NULL;
	HFONT oldFont = NULL;

	if ( System::isUnicodeEnabled() ) {
		tmpFont = CreateFontIndirectW( (LOGFONTW*)logFont_ );
		oldFont = (HFONT)SelectObject( dc, tmpFont );

		memset( tm_, 0, sizeof(TEXTMETRICW) );
		GetTextMetricsW( dc, (TEXTMETRICW*)tm_ );
	}
	else {
		tmpFont = CreateFontIndirectA( (LOGFONTA*)logFont_ );
		oldFont = (HFONT)SelectObject( dc, tmpFont );

		memset( tm_, 0, sizeof(TEXTMETRICA) );
		GetTextMetricsA( dc, (TEXTMETRICA*)tm_ );
	}


	::RestoreDC( dc, dcs );

	SelectObject( dc, oldFont );
	DeleteObject( tmpFont );

	ReleaseDC( ::GetDesktopWindow(), dc );
}

bool Win32Font::isTrueType()
{
	bool result = false;
	if ( System::isUnicodeEnabled() ) {
		if ( (((TEXTMETRICW*)tm_)->tmPitchAndFamily & TMPF_TRUETYPE) != 0 ){
			result = true;
		}
	}
	else {
		if ( (((TEXTMETRICA*)tm_)->tmPitchAndFamily & TMPF_TRUETYPE) != 0 ){
			result = true;
		}
	}

	return result;
}

double Win32Font::getPointSize()
{
	HDC dc = GetDC( ::GetDesktopWindow() );
	double ppi = (double)GetDeviceCaps( dc, LOGPIXELSY);
	double result = 0.0;

	if ( System::isUnicodeEnabled() ) {
		result = ((double)((LOGFONTW*)logFont_)->lfHeight / ppi) * 72.0;
	}
	else {
		result = ((double)((LOGFONTA*)logFont_)->lfHeight / ppi) * 72.0;
	}
	ReleaseDC( ::GetDesktopWindow(), dc );

	return result;
}

void Win32Font::setPointSize( const double pointSize )
{
	HDC dc = GetDC( ::GetDesktopWindow() );
	double ppi = (double)GetDeviceCaps( dc, LOGPIXELSY);
	long lfHeight = (pointSize / 72) * ppi;

	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (lfHeight != ((LOGFONTW*)logFont_)->lfHeight);
	}
	else {
		needsUpdate = (lfHeight != ((LOGFONTA*)logFont_)->lfHeight);
	}


	ReleaseDC( ::GetDesktopWindow(), dc );

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	if ( System::isUnicodeEnabled() ) {
		((LOGFONTW*)logFont_)->lfHeight = lfHeight;
		((LOGFONTW*)logFont_)->lfWidth = 0; //let font mapper choose closest match
	}
	else {
		((LOGFONTA*)logFont_)->lfHeight = lfHeight;
		((LOGFONTA*)logFont_)->lfWidth = 0; //let font mapper choose closest match
	}

	if ( true == needsUpdate ) {

		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}

double Win32Font::getPixelSize()
{
	double result = 0.0;

	if ( System::isUnicodeEnabled() ) {
		result = abs( ((LOGFONTW*)logFont_)->lfHeight );
	}
	else {
		result = abs( ((LOGFONTA*)logFont_)->lfHeight );
	}

	return result;
}

void Win32Font::setPixelSize( const double pixelSize )
{
	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (pixelSize != ((LOGFONTW*)logFont_)->lfHeight);
	}
	else {
		needsUpdate = (pixelSize != ((LOGFONTA*)logFont_)->lfHeight);
	}

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	if ( System::isUnicodeEnabled() ) {
		((LOGFONTW*)logFont_)->lfHeight = pixelSize;
		((LOGFONTW*)logFont_)->lfWidth = 0; //let font mapper choose closest match
	}
	else {
		((LOGFONTA*)logFont_)->lfHeight = pixelSize;
		((LOGFONTA*)logFont_)->lfWidth = 0; //let font mapper choose closest match
	}



	if ( true == needsUpdate ) {
		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}

void Win32Font::setBold( const bool& bold )
{
	DWORD style = bold ? FW_BOLD : FW_NORMAL;


	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (style != ((LOGFONTW*)logFont_)->lfWeight);
	}
	else {
		needsUpdate = (style != ((LOGFONTA*)logFont_)->lfWeight);
	}

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	if ( System::isUnicodeEnabled() ) {
		((LOGFONTW*)logFont_)->lfWeight = style;
	}
	else {
		((LOGFONTA*)logFont_)->lfWeight = style;
	}

	if ( true == needsUpdate ) {
		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}

bool Win32Font::getBold()
{
	bool result = false;

	if ( System::isUnicodeEnabled() ) {
		result = (((LOGFONTW*)logFont_)->lfWeight == FW_NORMAL) ? false : true;
	}
	else {
		result = (((LOGFONTA*)logFont_)->lfWeight == FW_NORMAL) ? false : true;
	}

	return result;
}

bool Win32Font::getItalic()
{
	bool result = false;

	if ( System::isUnicodeEnabled() ) {
		result = (((LOGFONTW*)logFont_)->lfItalic ) ? true : false;
	}
	else {
		result = (((LOGFONTA*)logFont_)->lfItalic ) ? true : false;
	}

	return result;
}

void Win32Font::setItalic( const bool& italic )
{
	BYTE lfItalic = italic ? TRUE : FALSE;

	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (lfItalic != ((LOGFONTW*)logFont_)->lfItalic);
	}
	else {
		needsUpdate = (lfItalic != ((LOGFONTA*)logFont_)->lfItalic);
	}

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	if ( System::isUnicodeEnabled() ) {
		((LOGFONTW*)logFont_)->lfItalic = italic ? TRUE : FALSE;
	}
	else {
		((LOGFONTA*)logFont_)->lfItalic = italic ? TRUE : FALSE;
	}


	if ( true == needsUpdate ) {
		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}

bool Win32Font::getUnderlined()
{
	bool result = false;

	if ( System::isUnicodeEnabled() ) {
		result = (((LOGFONTW*)logFont_)->lfUnderline ) ? true : false;
	}
	else {
		result = (((LOGFONTA*)logFont_)->lfUnderline ) ? true : false;
	}

	return result;
}

void Win32Font::setUnderlined( const bool& underlined )
{
	BYTE lfUnderlined = underlined ? TRUE : FALSE;


	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (lfUnderlined != ((LOGFONTW*)logFont_)->lfUnderline);
	}
	else {
		needsUpdate = (lfUnderlined != ((LOGFONTA*)logFont_)->lfUnderline);
	}

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	if ( System::isUnicodeEnabled() ) {
		((LOGFONTW*)logFont_)->lfUnderline = underlined ? TRUE : FALSE;
	}
	else {
		((LOGFONTA*)logFont_)->lfUnderline = underlined ? TRUE : FALSE;
	}


	if ( true == needsUpdate ) {
		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}

bool Win32Font::getStrikeOut()
{
	bool result = false;

	if ( System::isUnicodeEnabled() ) {
		result = (((LOGFONTW*)logFont_)->lfStrikeOut ) ? true : false;
	}
	else {
		result = (((LOGFONTA*)logFont_)->lfStrikeOut ) ? true : false;
	}

	return result;
}

void Win32Font::setStrikeOut( const bool& strikeout )
{
	BYTE lfStrikeOut = strikeout ? TRUE : FALSE;

	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (lfStrikeOut != ((LOGFONTW*)logFont_)->lfStrikeOut);
	}
	else {
		needsUpdate = (lfStrikeOut != ((LOGFONTA*)logFont_)->lfStrikeOut);
	}

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}


	if ( System::isUnicodeEnabled() ) {
		((LOGFONTW*)logFont_)->lfStrikeOut = strikeout ? TRUE : FALSE;
	}
	else {
		((LOGFONTA*)logFont_)->lfStrikeOut = strikeout ? TRUE : FALSE;
	}

	if ( true == needsUpdate ) {
		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}


String Win32Font::getName()
{
	String result;
	if ( System::isUnicodeEnabled() ) {
		result = ((LOGFONTW*)logFont_)->lfFaceName;
	}
	else {
		result = ((LOGFONTA*)logFont_)->lfFaceName;
	}

	return result;
}

void Win32Font::setName( const String& name )
{
	bool needsUpdating = ( fontName_ != name );

	if ( true == needsUpdating ) {
		Win32FontManager::removeFont( this );
	}

	fontName_ = name;

	if ( System::isUnicodeEnabled() ) {
		memset( ((LOGFONTW*)logFont_)->lfFaceName, 0, LF_FACESIZE*sizeof(VCFChar) );
		fontName_.copy( ((LOGFONTW*)logFont_)->lfFaceName, minVal<int>( fontName_.size(), LF_FACESIZE) );
	}
	else {
		AnsiString tmpName = fontName_;

		memset( ((LOGFONTA*)logFont_)->lfFaceName, 0, LF_FACESIZE*sizeof(char) );
		tmpName.copy( ((LOGFONTA*)logFont_)->lfFaceName, minVal<int>( tmpName.size(), LF_FACESIZE) );
	}

	if ( true == needsUpdating ) {
		updateTextMetrics();

		Win32FontManager::initializeFont( this );
	}
}

GlyphCollection* Win32Font::getGlyphCollection( const String& text )
{
	return NULL;
}

bool Win32Font::isEqual( Object* object )
{
	bool result = false;
	Win32Font* fntObj = dynamic_cast<Win32Font*>(object);
	if ( NULL != fntObj ){

		if ( (fontName_ == fntObj->fontName_) &&
			(font_->getColor()->isEqual( fntObj->font_->getColor() )) &&
			 (pointSize_ == fntObj->pointSize_) ) {
			result = true;
		}
	}

	return result;
}


double Win32Font::getAscent()
{
	double result = 0.0;
	if ( System::isUnicodeEnabled() ) {
		result = ((TEXTMETRICW*)tm_)->tmAscent;
	}
	else {
		result = ((TEXTMETRICA*)tm_)->tmAscent;
	}
	return result;
}

double Win32Font::getDescent()
{
	double result = 0.0;
	if ( System::isUnicodeEnabled() ) {
		result = ((TEXTMETRICW*)tm_)->tmDescent;
	}
	else {
		result = ((TEXTMETRICA*)tm_)->tmDescent;
	}
	return result;
}


void Win32Font::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name )
{

	Win32FontManager::removeFont( this );

	fontName_ = name;

	HDC dc = GetDC( ::GetDesktopWindow() );
	double ppi = (double)GetDeviceCaps( dc, LOGPIXELSY);
	long lfHeight = (pointSize / 72.0) * ppi;

	ReleaseDC( ::GetDesktopWindow(), dc );


	if ( System::isUnicodeEnabled() ) {
		LOGFONTW& lfw = *((LOGFONTW*)logFont_);
		lfw.lfHeight = lfHeight;
		lfw.lfWidth = 0; //let font mapper choose closest match
		lfw.lfItalic = italic ? TRUE : FALSE;
		lfw.lfWeight = bold ? FW_BOLD : FW_NORMAL;
		lfw.lfStrikeOut = struckOut ? TRUE : FALSE;
		lfw.lfUnderline = underlined ? TRUE : FALSE;
		lfw.lfEscapement = 0;
		lfw.lfOrientation = 0;

		memset( lfw.lfFaceName, 0, LF_FACESIZE*sizeof(VCFChar) );
		fontName_.copy( lfw.lfFaceName, minVal<int>( fontName_.size(), LF_FACESIZE) );
	}
	else {
		LOGFONTA& lfa = *((LOGFONTA*)logFont_);
		lfa.lfHeight = lfHeight;
		lfa.lfWidth = 0; //let font mapper choose closest match
		lfa.lfItalic = italic ? TRUE : FALSE;
		lfa.lfWeight = bold ? FW_BOLD : FW_NORMAL;
		lfa.lfStrikeOut = struckOut ? TRUE : FALSE;
		lfa.lfUnderline = underlined ? TRUE : FALSE;
		lfa.lfEscapement = 0;
		lfa.lfOrientation = 0;

		AnsiString tmpName = fontName_;

		memset( lfa.lfFaceName, 0, LF_FACESIZE*sizeof(char) );
		tmpName.copy( lfa.lfFaceName, minVal<int>( tmpName.size(), LF_FACESIZE) );
	}


	updateTextMetrics();

	Win32FontManager::initializeFont( this );
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/30 19:17:11  ddiego
*fixed some font issues. got rid of methods that are not implementable on other platforms
*
*Revision 1.1.2.2  2004/04/29 04:10:28  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.15.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.15  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.2  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.13.2.1  2004/01/19 23:32:06  ddiego
**** empty log message ***
*
*Revision 1.13  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.3  2003/10/06 23:57:01  marcelloptr
*fix: selecting oldFont in the device context before deleting the resource
*
*Revision 1.12.4.2  2003/09/06 19:45:44  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.12.4.1  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.12  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:12:37  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10.2.1  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.9.10.5  2002/11/01 05:26:42  ddiego
*finishing touches to the MessageDialog - ready for use now
*Resource editing is now feature complete and ready for bug fixing
*
*Revision 1.9.10.4  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.9.10.3  2002/09/30 02:16:52  ddiego
*misc piddling
*
*Revision 1.9.10.2  2002/09/28 22:22:46  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.9.10.1  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.9  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.8  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


