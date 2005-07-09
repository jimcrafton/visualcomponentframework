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
	tm_(NULL),
	oldDPI_(0)
{
	HDC dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	oldDPI_ = GetDeviceCaps( dc, LOGPIXELSY);

	ReleaseDC( ::GetDesktopWindow(), dc );

	init();
}

Win32Font::Win32Font( const String& fontName, const double& pointSize ):
	font_(NULL),
	pointSize_(pointSize),
	fontName_(fontName),
	logFont_(NULL),
	tm_(NULL),
	oldDPI_(0)
{
	HDC dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	oldDPI_ = GetDeviceCaps( dc, LOGPIXELSY);

	ReleaseDC( ::GetDesktopWindow(), dc );

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

	//ANSI_VAR_FONT produces bold text on WinME. Changed to DEFAULT_GUI_FONT, which
	//gives same appearrance on WinXP as ANSI_VAR_FONT. dougtinkham
	//Unfortunately DEFAULT_GUI_FONT looks like shit on Win2k :( 
	//we'll check here to see the OS version and then base the decision on that
	//WinMe = DEFAULT_GUI_FONT. But Win98, Win2K, WinXP = ANSI_VAR_FONT. JC (aka ddiego)

	HFONT defFont = NULL;
	
	static OSVERSIONINFO osVersion = {0};
	if ( 0 == osVersion.dwOSVersionInfoSize ) {
		osVersion.dwOSVersionInfoSize = sizeof(osVersion);
		::GetVersionEx( &osVersion );
	}
	


	

	if ( VER_PLATFORM_WIN32_NT == osVersion.dwPlatformId ) {
		if ( (osVersion.dwMinorVersion >= 1) && (osVersion.dwMinorVersion != 51) ) { //Windows XP or better
			defFont = (HFONT)GetStockObject( ANSI_VAR_FONT );
		}
		else { //Windows 2k or worse
			defFont = (HFONT)GetStockObject( ANSI_VAR_FONT );
		}
	}
	else { //Windows 9x
		if ( 90 == osVersion.dwMinorVersion ) { //Windows ME
			defFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		}
		else { //Windows 98
			defFont = (HFONT)GetStockObject( ANSI_VAR_FONT );
		}
	}

	
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

	bool releaseDC = true;
	HDC dc = NULL;
	if ( NULL != font_ ) {
		if ( NULL != font_->getGraphicsContext() ) {
			dc = (HDC) font_->getGraphicsContext()->getPeer()->getContextID();
			if ( NULL != dc ) {
				releaseDC = false;
			}
		}
	}
	if ( NULL == dc ) {
		dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	}
	

	if ( pointSize_ > 0.0 ) {
		fontHeight = -MulDiv( pointSize_, GetDeviceCaps( dc, LOGPIXELSY), 72 );
	}


	if ( releaseDC ) {
		ReleaseDC( ::GetDesktopWindow(), dc );
	}

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

OSHandleID Win32Font::getFontHandleID()
{
	return (OSHandleID)logFont_;
}

void Win32Font::updateTextMetrics()
{
	bool releaseDC = true;
	HDC dc = NULL;
	if ( NULL != font_ ) {
		if ( NULL != font_->getGraphicsContext() ) {
			dc = (HDC) font_->getGraphicsContext()->getPeer()->getContextID();
			if ( NULL != dc ) {
				releaseDC = false;
			}
		}
	}
	if ( NULL == dc ) {
		dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	}

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


	if ( releaseDC ) {
		ReleaseDC( ::GetDesktopWindow(), dc );
	}
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
	bool releaseDC = true;
	HDC dc = NULL;

	//this gets a HDC either from the GraphicsContext that is associated 
	// to this font ( i.e. 'owning' this font as it would always be the 
	// case for printing ), or from the desktop window.
	if ( NULL != font_ ) {
		if ( NULL != font_->getGraphicsContext() ) {
			//look at win32Ctx if we are having problems in the assertions below
			//Win32Context* win32Ctx = (Win32Context*)font_->getGraphicsContext()->getPeer();
			dc = (HDC) font_->getGraphicsContext()->getPeer()->getContextID();
			if ( NULL != dc ) {
				releaseDC = false;
			}
		}
	}
	if ( NULL == dc ) {
	  dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	}

	

	if ( NULL == dc ) {
		//damn! We are well and truly screwed at this point!
		DWORD err = ::GetLastError();

		String msg = "\nNULL dc in Win32Font::getPointSize() - need to fix this!!!!\n\t";
		msg +=  VCFWin32::Win32Utils::getErrorString(err) + "\n";		

		StringUtils::trace( MAKE_ERROR_MSG_2(msg) );		

		//this assert stays in  - we should NEVER, EVER, EVER have a NULL HDC at this point.
		//this would indicate the presence of unspeakable evil, and we should all run for
		//cover if this is the case
		VCF_ASSERT( dc != NULL );  
	}


	double ppi = (double)GetDeviceCaps( dc, LOGPIXELSY);

	if ( ((int)ppi) <= 0 ) {
		DWORD err = ::GetLastError();
		String msg = "\nppi <= 0 in Win32Font::getPointSize() - need to fix this!!!!\n\t";
		msg +=  VCFWin32::Win32Utils::getErrorString(err) + "\n";		

		StringUtils::trace( MAKE_ERROR_MSG_2(msg) );
	
		/**
		The asserts will stay in here for the time being because we should NEVER 
		EVER be getting them, and if we are it's a sympomatic problem of something else
		*/
		VCF_ASSERT( ((int)ppi) > 0 ); 
	}

	int lfHeight = 0;

	if ( System::isUnicodeEnabled() ) {
		lfHeight = ((LOGFONTW*)logFont_)->lfHeight;
	}
	else {
		lfHeight = ((LOGFONTA*)logFont_)->lfHeight;
	}

	if ( lfHeight == 0 ) {
		DWORD err = ::GetLastError();
		String msg = "\nlfHeight == 0 in Win32Font::getPointSize() - need to fix this!!!!\n\t";
		msg +=  VCFWin32::Win32Utils::getErrorString(err) + "\n";		

		StringUtils::trace( MAKE_ERROR_MSG_2(msg) );
		VCF_ASSERT( lfHeight != 0 ); 
	}

	/*
	JC I took these out - while I understand the need for a workaround here
	we don't want to be doing this - ppi of 0 or a lfHeight of 0 is BAD BAD BAD
	and we need to fix the problem(s) that may be causing them.
	if (ppi == 0.0){
		ppi = 96.0;
	}

	if (lfHeight == 0) {
		lfHeight=1;
	}
	*/

	double result = fabs( ((double)lfHeight / ppi) * 72.0 );

	if ( GetDeviceCaps( dc, LOGPIXELSY) != this->oldDPI_ ) {
		result = result * ( ppi / oldDPI_ );
		oldDPI_ = GetDeviceCaps( dc, LOGPIXELSY);
	}

	// releases the device context if it is not the one associated to the font.
	if ( releaseDC ) {
		ReleaseDC( ::GetDesktopWindow(), dc );
	}

	return result;
}

void Win32Font::setPointSize( const double pointSize )
{
	bool releaseDC = true;
	HDC dc = NULL;
	if ( NULL != font_ ) {
		if ( NULL != font_->getGraphicsContext() ) {
			dc = (HDC) font_->getGraphicsContext()->getPeer()->getContextID();
			if ( NULL != dc ) {
				releaseDC = false;
			}
		}
	}
	if ( NULL == dc ) {
		dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	}

	double ppi = (double)GetDeviceCaps( dc, LOGPIXELSY);
	long lfHeight = (pointSize / 72) * ppi;

	if ( releaseDC ) {
		ReleaseDC( ::GetDesktopWindow(), dc );
	}

	
	bool needsUpdate = false;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (lfHeight != ((LOGFONTW*)logFont_)->lfHeight);
	}
	else {
		needsUpdate = (lfHeight != ((LOGFONTA*)logFont_)->lfHeight);
	}


	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	if ( isTrueType() ) {
		lfHeight = -lfHeight;
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

	double pixSize = pixelSize;

	if ( System::isUnicodeEnabled() ) {
		needsUpdate = (pixelSize != ((LOGFONTW*)logFont_)->lfHeight);
	}
	else {
		needsUpdate = (pixelSize != ((LOGFONTA*)logFont_)->lfHeight);
	}

	if ( true == needsUpdate ) {
		Win32FontManager::removeFont( this );
	}

	int lfHeight = pixSize;

	if ( isTrueType() ) {
		if ( !(lfHeight < 0) ) { //if it's NOT negative, then flip it o negative!
			lfHeight = -lfHeight;
		}
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

bool Win32Font::isFixedPitch()
{
	bool result = false;

	if ( System::isUnicodeEnabled() ) {		
		result = ((((TEXTMETRICW*)tm_)->tmPitchAndFamily & TMPF_FIXED_PITCH) != 0) ? true : false;
	}
	else {
		result = ((((TEXTMETRICA*)tm_)->tmPitchAndFamily & TMPF_FIXED_PITCH) != 0) ? true : false;
	}

	return result;
}

void Win32Font::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name )
{

	Win32FontManager::removeFont( this );

	fontName_ = name;

	bool releaseDC = true;
	HDC dc = NULL;
	if ( NULL != font_ ) {
		if ( NULL != font_->getGraphicsContext() ) {
			dc = (HDC) font_->getGraphicsContext()->getPeer()->getContextID();
			if ( NULL != dc ) {
				releaseDC = false;
			}
		}
	}
	if ( NULL == dc ) {
		dc = GetDC( ::GetDesktopWindow() ); // gets screen DC
	}

	double ppi = (double)GetDeviceCaps( dc, LOGPIXELSY);
	long lfHeight = ((pointSize / 72.0) * ppi) + 0.5;


	bool trueTypeFont = false;
	{ //test for true type
		LOGFONT lfTmp = {0};
		lfTmp.lfHeight = 10; //doesn't matter - just testing the name!
		lfTmp.lfWidth = 0; //let font mapper choose closest match				
		lfTmp.lfCharSet = ANSI_CHARSET;//DEFAULT_CHARSET might be better ?
		lfTmp.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lfTmp.lfItalic = FALSE;			
		lfTmp.lfOutPrecision = OUT_DEFAULT_PRECIS;
		lfTmp.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		lfTmp.lfQuality = DEFAULT_QUALITY;
		lfTmp.lfStrikeOut = FALSE;
		lfTmp.lfUnderline = FALSE;
		lfTmp.lfWeight = FW_NORMAL;
#if defined(VCF_CW) && defined(UNICODE)
		memset( lfTmp.lfFaceName, 0, LF_FACESIZE*sizeof(WCHAR) );
		fontName_.copy( lfTmp.lfFaceName, minVal<int>( fontName_.size(), LF_FACESIZE) );
#else		
		AnsiString tmpName = fontName_;
		memset( lfTmp.lfFaceName, 0, LF_FACESIZE*sizeof(char) );
		tmpName.copy( lfTmp.lfFaceName, minVal<int>( tmpName.size(), LF_FACESIZE) );
#endif		
		HFONT testFnt = CreateFontIndirect( &lfTmp );
		if ( testFnt ) {
			HFONT oldFnt = (HFONT)SelectObject( dc, testFnt );		

			TEXTMETRIC tm = {0};
			if ( GetTextMetrics( dc, &tm ) ) {

				trueTypeFont = ((tm.tmPitchAndFamily & TMPF_TRUETYPE) != 0) ? true : false;
			}

			SelectObject( dc, oldFnt );
			DeleteObject( testFnt );
		}

	}

	if ( trueTypeFont ) {
		lfHeight = -lfHeight;
	}

	if ( releaseDC ) {
		ReleaseDC( ::GetDesktopWindow(), dc );
	}


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
*Revision 1.5  2005/07/09 23:06:01  ddiego
*added missing gtk files
*
*Revision 1.4  2005/01/02 03:04:26  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.3  2005/04/13 01:08:49  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.3.2.2  2005/02/16 05:09:34  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.1  2004/12/19 04:05:05  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.16  2004/11/01 19:38:47  marcelloptr
*minor change
*
*Revision 1.2.2.15  2004/10/31 15:32:29  ddiego
*fixed a bug in the way Win32ControlContext::releaseHandle() worked that was causing a problem in Win32Font::getPointSize().
*
*Revision 1.2.2.14  2004/10/25 03:52:02  ddiego
*minor changes to osx checkin for win32
*
*Revision 1.2.2.13  2004/10/11 14:28:47  kiklop74
*First version of patch for BUG 1042623 - Incorect handling of DC in win32font
*
*Revision 1.2.2.12  2004/10/04 15:51:15  kiklop74
*Added explicit cast to avoid ambiquity on BCB6
*
*Revision 1.2.2.11  2004/09/21 23:41:25  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.10  2004/09/01 03:50:39  ddiego
*fixed font drawing bug that tinkham pointed out.
*
*Revision 1.2.2.9  2004/08/31 08:55:58  marcelloptr
*minor change on a comment
*
*Revision 1.2.2.7  2004/08/31 04:12:13  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2.2.6  2004/08/26 04:08:15  marcelloptr
*minor change on a comment
*
*Revision 1.2.2.4  2004/08/26 01:44:40  ddiego
*fixed font pix size bug that handled non true type fonts poorly.
*
*Revision 1.2.2.3  2004/08/26 00:27:49  ddiego
*fixed font pix size bug that handled non true type fonts poorly.
*
*Revision 1.2.2.2  2004/08/24 04:29:58  ddiego
*more printing work, still not yet integrated.
*
*Revision 1.2.2.1  2004/08/20 18:54:21  dougtinkham
*Changed stock font from ANSI_VAR_FONT to DEFAULT_GUI_FONT to fix WinME problem.
*
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


