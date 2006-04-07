

#ifndef _RESOURCEBUNDLEPEER_H__
#define _RESOURCEBUNDLEPEER_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {


class Resource;
/**
\class ResourceBundlePeer ResourceBundlePeer.h "vcf/FoundationKit/ResourceBundlePeer.h"
class ResourceBundlePeer documentation
*/
class FOUNDATIONKIT_API ResourceBundlePeer {
public: 	
	virtual ~ResourceBundlePeer(){};

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
	* returns a Resource object given the resource's name.
	*/
	virtual Resource* getResource( const String& resourceName ) = 0;

	virtual ProgramInfo* getProgramInfo() = 0;

	/**
	Returns a native handle (if available) for dealing with 
	resources. On Win32 this would be the HINSTANCE passed in
	through a WinMain() like function or a DLMain() function.
	On OSX this will be a CFBundle instance.
	*/
	virtual OSHandleID getHandleID() = 0;
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
*Revision 1.2.2.1  2004/12/19 04:05:01  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/09/15 21:14:28  ddiego
*added support for getting program info from resource bundle.
*
*Revision 1.1.2.1  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*/


#endif //_RESOURCEBUNDLEPEER_H__





