#ifndef _VCF_WIN32FONTMANAGER_H__
#define _VCF_WIN32FONTMANAGER_H__
//Win32FontManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Win32Font;

#define DEFAULT_VCF_FONT_NAME		"Arial"


/**
*used to hold a HFONT and a refcount
*/
class GRAPHICSKIT_API Win32FontHandle : public Object {
public:
	Win32FontHandle( HFONT font );

	virtual ~Win32FontHandle();

	void incRef();

	/**
	*decrement the ref count. If the count goes to 0 then
	*delete the HFONT object
	*/
	void decRef();

	HFONT getFontHandle();

	bool isRefCountZero();
private:
	int refCount_;
	HFONT fontHandle_;
};


/**
*Uses to manage fonts for controls
*/
class GRAPHICSKIT_API Win32FontManager : public Object{

public:
	static Win32FontManager* create();

	Win32FontManager();

	virtual ~Win32FontManager();

	virtual void init();

	/**
	*this is called by the Win32Font class to add the
	*the font peer to the font manager.
	*/
	static void initializeFont( Win32Font* font );

	static void removeFont( Win32Font* font );

	static HFONT getFontHandleFromFontPeer( Win32Font* font );

	static Win32FontManager* getFontManager() {
		return Win32FontManager::win32FontMgr;
	}
private:
	/**
	*adds the font to the manager called internally
	*/
	void addFont( Win32Font* font );

	std::map<String, Win32FontHandle*> fontMap_;
	Win32Font* defaultFont_;

	/**
	*makes a string id (like a hash code - there probably is a better way to do this.....
	*of the Win32Font.
	*the ID is the Name + Color +
	*/
	String makeStringID( Win32Font* font );

	static Win32FontManager* win32FontMgr;
};

}; //end of namespace VCF


#endif // _VCF_WIN32FONTMANAGER_H__

/**
$Id$
*/
