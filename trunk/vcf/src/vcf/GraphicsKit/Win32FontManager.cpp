//Win32FontManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

Win32FontManager* Win32FontManager::create()
{
	if ( NULL == Win32FontManager::win32FontMgr ) {
		Win32FontManager::win32FontMgr = new Win32FontManager();
		Win32FontManager::win32FontMgr->init();
	}
	return Win32FontManager::win32FontMgr;
}

/**
*Win32FontHandle code
*/
Win32FontHandle::Win32FontHandle( HFONT font )
{


	refCount_ = 0;
	fontHandle_ = NULL;
	fontHandle_ = font;
	incRef();
}

Win32FontHandle::~Win32FontHandle()
{
	if ( fontHandle_ != NULL ){
		DeleteObject( fontHandle_ );
	}
}

void Win32FontHandle::incRef()
{
	refCount_ ++;
}

void Win32FontHandle::decRef()
{
	if ( refCount_ > 0 ){
		refCount_ --;
		if ( (refCount_ == 0) && (fontHandle_ != NULL) ){
			DeleteObject( fontHandle_ );
			fontHandle_ = NULL;
		}
	}
}

HFONT Win32FontHandle::getFontHandle()
{
	return fontHandle_;
}

bool Win32FontHandle::isRefCountZero()
{
	return 0 == refCount_;
}


/**
*Win32FontManager code
*/
Win32FontManager::Win32FontManager()
{
	defaultFont_ = NULL;
}

Win32FontManager::~Win32FontManager()
{
	delete defaultFont_;
	defaultFont_ = NULL;

	std::map<String,Win32FontHandle*>::iterator it = fontMap_.begin();

	while ( it != fontMap_.end() ){
		Win32FontHandle* fh = it->second;
		if ( NULL != fh ){
			delete fh;
		}
		fh = NULL;
		it ++;
	}

	fontMap_.clear();

	Win32FontManager::win32FontMgr = NULL;
}

void Win32FontManager::init()
{
	defaultFont_ = new Win32Font( DEFAULT_VCF_FONT_NAME );
}

void Win32FontManager::addFont( Win32Font* font )
{
	String fontID = makeStringID( font );
	if ( fontID.size() > 0 ){

		std::map<String,Win32FontHandle*>::iterator found = fontMap_.find( fontID );
		if ( found != fontMap_.end() ){
			Win32FontHandle* win32FontHandle = found->second;
			win32FontHandle->incRef();
		}
		else {// only add if no entry
			/**
			*no entry found so go ahead and create a new HFONT object
			*and store the entry
			*/
			HFONT fontHandle = NULL;
			if ( System::isUnicodeEnabled() ) {
				fontHandle = CreateFontIndirectW( (LOGFONTW*)font->getFontHandleID() );
			}
			else {
				fontHandle = CreateFontIndirectA( (LOGFONTA*)font->getFontHandleID() );
			}
			

			if ( NULL != fontHandle ){
				fontMap_[fontID] = new Win32FontHandle( fontHandle );
			}//otherwise throw exception ?????
		}
	}
}

String Win32FontManager::makeStringID(  Win32Font* font )
{
	String result = "";
	if ( NULL != font ){
		result += font->getName();
		result += (int)font->getPixelSize();
		result += font->getBold();
		result += font->getUnderlined();
		result += font->getStrikeOut();
		result += font->getItalic();

		/*
		result = StringUtils::format( Format("%s%d%s%s%s%s") %
										font->getName().c_str() %
										(int)font->getPixelSize() %
										(font->getBold() ? L"true" : L"false") %
										(font->getUnderlined() ? L"true" : L"false") %
										(font->getStrikeOut() ? L"true" : L"false") %
										(font->getItalic() ? L"true" : L"false") );
		*/

	}
	return result;
}

void Win32FontManager::initializeFont( Win32Font* font )
{
	Win32FontManager::win32FontMgr->addFont( font );
}

HFONT Win32FontManager::getFontHandleFromFontPeer( Win32Font* font )
{
	HFONT result = NULL;

	String fontID = Win32FontManager::win32FontMgr->makeStringID( font );

	std::map<String,Win32FontHandle*>::iterator found =
		Win32FontManager::win32FontMgr->fontMap_.find( fontID );

	Win32FontHandle* win32FontHandle = NULL;

	if ( found != Win32FontManager::win32FontMgr->fontMap_.end() ){
		win32FontHandle = found->second;
	}
	else {
	/**
	*this font should have called Win32FontManager::initializeFont()
	*but somehow it didn't get added - let's add it now
	*/
		Win32FontManager::win32FontMgr->addFont( font );
		found = Win32FontManager::win32FontMgr->fontMap_.find( fontID );
		if ( found != Win32FontManager::win32FontMgr->fontMap_.end() ){
			win32FontHandle = found->second;
		}
		//otherwise we're fucked - throw an exception !!!!!
	}

	if ( NULL != win32FontHandle ){
		result = win32FontHandle->getFontHandle();
	}
	return result;
}

void Win32FontManager::removeFont( Win32Font* font )
{
	if ( NULL == Win32FontManager::win32FontMgr ) {
		return;
	}

	String fontID = Win32FontManager::win32FontMgr->makeStringID( font );

	if ( ! Win32FontManager::win32FontMgr->fontMap_.empty() ) {
		std::map<String,Win32FontHandle*>::iterator found =
			Win32FontManager::win32FontMgr->fontMap_.find( fontID );

		if ( found != Win32FontManager::win32FontMgr->fontMap_.end() ){
			Win32FontHandle* fontHandle = found->second;
			fontHandle->decRef();

			if ( true == fontHandle->isRefCountZero() ){
				
				delete fontHandle;
				fontHandle = NULL;
				Win32FontManager::win32FontMgr->fontMap_.erase( found );
			}
		}
	}
}


/**
$Id$
*/
