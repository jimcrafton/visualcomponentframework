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


#endif // _VCF_LIBRARY_H__

/**
$Id$
*/
