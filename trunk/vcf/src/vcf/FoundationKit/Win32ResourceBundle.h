#ifndef _VCF_WIN32RESOURCEBUNDLE_H__
#define _VCF_WIN32RESOURCEBUNDLE_H__
//Win32ResourceBundle.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class FOUNDATIONKIT_API Win32ResourceBundle : public Object, public ResourceBundlePeer {
public:
	Win32ResourceBundle();

	virtual ~Win32ResourceBundle();

	/**
	*returns a resource string given a resource name
	*/
	virtual String getString( const String& resourceName );

	/**
	*returns the text that represents an VFF file (where VFF stands
	*for "Visual Form File" ). This text is standard XML and contains
	*the component hierarchy and properties for creating a frame.
	*/
	virtual String getVFF( const String& resourceName );

	/**
	*returns an Image based on a given resource name
	*/
	//virtual Image* getImage( const String& resourceName );

	/**
	*returns a Resource object given the resource's name.
	*this function walks through all the app's resources, by type
	*and then by name. The first match is the resource returned.
	*/
	virtual Resource* getResource( const String& resourceName );

	/**
	This wil be re-implemented on the version for the AppKit
	void setApplicationPeer( ApplicationPeer* appPeer ) {
		appPeer_ = appPeer;
	}
	*/

	virtual ProgramInfo* getProgramInfo();

	static ProgramInfo* getProgramInfoFromFileName( const String& fileName );
protected:
	virtual HINSTANCE getResourceInstance();
	bool foundResName_;
	const char* foundResType_;
	String searchResName_;

	static BOOL CALLBACK EnumResTypeProcA( HMODULE hModule, char* lpszType, LPARAM lParam );
	static BOOL CALLBACK EnumResNameProcA( HMODULE hModule, const char* lpszType, char* lpszName, LPARAM lParam );

};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.6  2004/11/17 04:52:49  ddiego
*added some minor fixes to win32 resource loading, and added 2 new examples that demonstrate basic resource loading and basic usage of dialogs.
*
*Revision 1.1.2.5  2004/11/10 19:09:48  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.1.2.4  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.1.2.3  2004/09/15 21:14:28  ddiego
*added support for getting program info from resource bundle.
*
*Revision 1.1.2.2  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.1.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.22.1  2003/03/12 03:11:28  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32RESOURCEBUNDLE_H__


