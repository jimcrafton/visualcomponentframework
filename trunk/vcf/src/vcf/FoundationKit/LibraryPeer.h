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
*The LibraryPeer represents a generic wrapper
*around using DLL/SOs on systems. Implemented
*by a specific LibraryPeer derived OS class.
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

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.26.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LIBRARYPEER_H__


