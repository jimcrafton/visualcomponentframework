#ifndef _VCF_LIBRARY_H__
#define _VCF_LIBRARY_H__
//Library.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class LibraryPeer;

/**
\class Library Library.h "vcf/FoundationKit/Library.h"
A Library represents a DLL (Dynamic Linked Library) or SO (Shared Object). 
It can be created by passing in a fully qualified file name to the constructor. 
The specified DLL/SO will then be dynamically loaded (and unloaded when the
Library obejct is destroyed if autoUnloadLib is true).
Alternatively you may call the load() method which will do the same.
*/
class FOUNDATIONKIT_API Library : public Object{

public:
	Library( const String& libraryName = "", const bool& autoUnloadLib=false );

	virtual ~Library();

	/**
	Dynamically loads the DLL/SO specified by the libraryFilename argument.
	
	The default behaviour is to just load the library, assuming the libraryFilename is a
	path to the library. However, we are now going to get a tad fancier!
	If the libraryFilename is a directory, then we will try and locate the 
	Info.plist/Info.xml file, read it, and, based on the info we get, 
	attempt to use this to open the library inside.
	@param String the fully qualified file name of the DLL or SO to
	load, or a directory that includes a Info.plist/Info.xml file in it
	identifying the library's ProgramInfo.
	@see System::getProgramInfoFromFileName()
	@see ProgramInfo
	*/
	void load( const String& libraryFilename );

	/**
	unloads the DLL/SO
	*/
	void unload();

	/**
	returns an exported function of the library
	@param String the name of the function to return
	@return void* a void pointer to the exported function.
	Callers are responsible for actually typecasting this
	to a meaningful function pointer. For example:
	\code
		typedef int (MyFunctionPtr)( int, bool);
		... //more code
		MyFunctionPtr funcPtr = (MyFunctionPtr) lib->getFunction( "DummyFunction" );
		int res = funcPtr( 12, true );
	\endcode
	if the function does not exist then the method returns null
	*/
	void* getFunction( const String& functionName );

	/**
	initializes the library object
	*/
	void init();
private:
	LibraryPeer* libPeer_;
	String currentLibName_;
	bool autoUnloadLib_;
};

}; //end of namespace VCF


/**
CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/03/26 22:37:35  ddiego
*minor update to source docs.
*
*Revision 1.5.2.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.5  2005/07/18 03:54:19  ddiego
*documentation updates.
*
Revision 1.4  2004/12/01 04:31:41  ddiego
merged over devmain-0-6-6 code. Marcello did a kick ass job
of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
that he found. Many, many thanks for this Marcello.
*
Revision 1.3.2.1  2004/09/17 11:38:06  ddiego
added program info support in library and process classes.
*
Revision 1.3  2004/08/08 22:09:33  ddiego
final checkin before the 0-6-5 release
*
Revision 1.2  2004/08/07 02:49:13  ddiego
merged in the devmain-0-6-5 branch to stable
*
Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
changed macros, text reformatting, copyright sections
*
Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
reformatting of source files: macros and csvlog and copyright sections
*
Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
migration towards new directory structure
*
Revision 1.9.4.1  2004/04/26 21:58:48  marcelloptr
changes for dir reorganization: _VCF_MACRO_H__
*
Revision 1.9  2003/12/18 05:15:59  ddiego
merge from devmain-0-6-2 branch into the stable branch
*
Revision 1.8.4.1  2003/10/23 04:24:51  ddiego
more musical chairs with headers again, in yet another attempt to make
them more efficent to speed up compiles.
Removed all teh template RTTI classes and put them all in one header
called VCFRTTIImpl.h. This should help compile speeds a bit.
The next step is to look at some of the event classes and remove ones
that aren't really neccessary - I'd estimate that 50% of the current
event classes are unneccessary and can be removed.
*
Revision 1.8  2003/05/17 20:37:17  ddiego
this is the checkin for the 0.6.1 release - represents the merge over from
the devmain-0-6-0 branch plus a few minor bug fixes
*
Revision 1.7.16.1  2003/03/12 03:11:50  ddiego
switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
Also changed all vcf builder files to accomadate this.
Changes were made to the Stream classes to NOT multiple inheritance and to
be a little more correct. Changes include breaking the FileStream into two
distinct classes, one for input and one for output.
*
Revision 1.7  2002/05/09 03:10:43  ddiego
merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
Revision 1.6.4.1  2002/03/20 21:56:56  zzack
Changed Include Style of FoundationKit
*
Revision 1.6  2002/01/24 01:46:49  ddiego
added a cvs "log" comment to the top of all files in vcf/src and vcf/include
to facilitate change tracking
*
*/


#endif // _VCF_LIBRARY_H__


