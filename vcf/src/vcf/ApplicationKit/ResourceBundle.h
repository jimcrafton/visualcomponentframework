#ifndef _VCF_RESOURCEBUNDLE_H__
#define _VCF_RESOURCEBUNDLE_H__
//ResourceBundle.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Resource;
class Image;
/**
*A ResourceBundle is used to represent a collection of resources. ResourceBundle's can
*be attached to external files or applications.
*/
class APPLICATIONKIT_API ResourceBundle : public Interface
{
public:

	virtual ~ResourceBundle(){};

	/**
	*returns a resource string given a resource name
	*/
	virtual String getString( const String& resourceName ) = 0;

	/**
	*returns the text that represents a Form. This text is standard XML and contains
	*the component hierarchy and properties for creating a frame.
	*/
	virtual String getVFF( const String& resourceName ) = 0;

	/**
	*returns an Image based on a given resource name
	*/
	virtual Image* getImage( const String& resourceName ) = 0;

	/**
	* returns a Resource object given the resource's name.
	*/
	virtual Resource* getResource( const String& resourceName ) = 0;

};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.8.4.1  2003/09/12 00:09:34  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.1  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_RESOURCEBUNDLE_H__


