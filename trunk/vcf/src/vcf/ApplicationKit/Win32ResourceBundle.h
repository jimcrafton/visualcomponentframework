#ifndef _VCF_WIN32RESOURCEBUNDLE_H__
#define _VCF_WIN32RESOURCEBUNDLE_H__
//Win32ResourceBundle.h

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

class Win32ResourceBundle : public Object, public ResourceBundle
{
public:
	Win32ResourceBundle();

	virtual ~Win32ResourceBundle();

	/**
	*returns a resource string given a resource name
	*/
	virtual String getString( const String& resourceName );

	/**
	*returns the text that represents an VFF file (where VFF stands
	*for "Visual Form File" ). This text is standard XML and contains
	*the component hierarchy and properties for creating a frame.
	*/
	virtual String getVFF( const String& resourceName );

	/**
	*returns an Image based on a given resource name
	*/
	virtual Image* getImage( const String& resourceName );

	/**
	*returns a Resource object given the resource's name.
	*this function walks through all the app's resources, by type
	*and then by name. The first match is the resource returned.
	*/
	virtual Resource* getResource( const String& resourceName );

	void setApplicationPeer( ApplicationPeer* appPeer ) {
		appPeer_ = appPeer;
	}
protected:
	HINSTANCE getResourceInstance();
	ApplicationPeer* appPeer_;
};

};


#endif // _VCF_WIN32RESOURCEBUNDLE_H__

/**
$Id$
*/
