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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:28  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.8.8.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/12 03:11:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32FONTMANAGER_H__


