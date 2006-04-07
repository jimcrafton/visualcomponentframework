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


namespace VCF  {

class Resource;
class ResourceBundlePeer;

/**
\class ResourceBundle ResourceBundle.h "vcf/FoundationKit/ResourceBundle.h"
*A ResourceBundle is used to represent a collection of resources. ResourceBundle's can
*be attached to external files or applications.
*/
class FOUNDATIONKIT_API ResourceBundle : public Object {
public:

	ResourceBundle();

	virtual ~ResourceBundle();

	String getString( const ulong32& resourceID );

	String getString( const String& resourceName );

	/**
	*returns the text that represents a Form. This text is standard XML and contains
	*the component hierarchy and properties for creating a frame.
	*/
	String getVFF( const String& resourceName );

	/**
	* returns a Resource object given the resource's name.
	*/
	Resource* getResource( const String& resourceName );

	ProgramInfo* getProgramInfo();

	/**
	Returns the resource directory for this bundle if it exists,
	otherwise returns an empty string. 
	*/
	virtual String getResourcesDirectory();
protected:
	ResourceBundlePeer* peer_;

};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.2.1  2004/12/19 07:09:20  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.2  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
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


