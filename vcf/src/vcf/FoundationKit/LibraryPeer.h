#ifndef _VCF_LIBRARYPEER_H__
#define _VCF_LIBRARYPEER_H__
//LibraryPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class LibraryPeer LibraryPeer.h "vcf/FoundationKit/LibraryPeer.h"
The LibraryPeer represents a generic wrapper
around using DLL/SOs on systems. Implemented
by a specific LibraryPeer derived OS class.
*/
class FOUNDATIONKIT_API LibraryPeer {
public:

	virtual ~LibraryPeer(){};

	/**
	*loads a dynamic library
	*/
	virtual void load( const String& libraryFilename ) = 0;

	/**
	*returns a pointer to the function named functionName.
	*@param String the name of the function to get a pointer to
	*@return void* a pointer to the function. Must be typcasted into
	*a valid function pointer on the caller's side.
	*Throws RuntimeException if a failure to load the library occurs
	*/
	virtual void* getFunction( const String& functionName ) = 0;

	virtual void unload() = 0;

	/**
	Returns an OS handle to the loaded library.
	*/
	virtual OSHandleID getHandleID() = 0;

};

}; //end of namespace VCF


#endif // _VCF_LIBRARYPEER_H__

/**
$Id$
*/
