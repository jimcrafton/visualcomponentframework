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


	this->refCount_ = 0;
	this->fontHandle_ = NULL;
	this->fontHandle_ = font;
	this->incRef();
}

Win32FontHandle::~Win32FontHandle()
{
	if ( this->fontHandle_ != NULL ){
		DeleteObject( this->fontHandle_ );
	}
}

void Win32FontHandle::incRef()
{
	this->refCount_ ++;
}

void Win32FontHandle::decRef()
{
	if ( refCount_ > 0 ){
		this->refCount_ --;
		if ( (this->refCount_ == 0) && (this->fontHandle_ != NULL) ){
			DeleteObject( this->fontHandle_ );
			fontHandle_ = NULL;
		}
	}
}

HFONT Win32FontHandle::getFontHandle()
{
	return this->fontHandle_;
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
}

void Win32FontManager::init()
{
	defaultFont_ = new Win32Font( DEFAULT_VCF_FONT_NAME );
}

void Win32FontManager::addFont( Win32Font* font )
{
	String fontID = makeStringID( font );
	if ( fontID.size() > 0 ){

		std::map<String,Win32FontHandle*>::iterator found = this->fontMap_.find( fontID );
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
		result = StringUtils::format( "%s%d%s%s%s%s",
										font->getName().c_str(),
										(int)font->getPixelSize(),
										font->getBold() ? "true" : "false",
										font->getUnderlined() ? "true" : "false",
										font->getStrikeOut() ? "true" : "false",
										font->getItalic() ? "true" : "false" );

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
*Revision 1.15.4.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.15  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.1  2003/09/06 19:45:44  ddiego
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
*Revision 1.14  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.1  2003/03/12 03:12:38  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12.2.1  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.11.10.1  2002/09/30 02:16:52  ddiego
*misc piddling
*
*Revision 1.11  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.10.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.10  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


