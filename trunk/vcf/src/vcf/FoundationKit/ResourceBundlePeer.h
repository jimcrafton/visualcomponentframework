

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
};



};



/**
*CVS Log info
*$Log$
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





