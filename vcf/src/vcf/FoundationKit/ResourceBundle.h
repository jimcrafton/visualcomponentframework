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


#endif // _VCF_RESOURCEBUNDLE_H__

/**
$Id$
*/
