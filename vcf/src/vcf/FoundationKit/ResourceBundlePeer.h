

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



#endif //_RESOURCEBUNDLEPEER_H__

/**
$Id$
*/
