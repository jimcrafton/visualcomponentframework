
#ifndef _WIN32GRAPHICSRESOURCEBUNDLE_H__
#define _WIN32GRAPHICSRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/Win32ResourceBundle.h"


namespace VCF  {

class GRAPHICSKIT_API Win32GraphicsResourceBundle : public Win32ResourceBundle, public GraphicsResourceBundlePeer {
public:
	Win32GraphicsResourceBundle();

	virtual ~Win32GraphicsResourceBundle();

	
	/**
	*returns an Image based on a given resource name
	*/
	virtual Image* getImage( const String& resourceName );

	
protected:
	
	
};

};


#endif //_WIN32GRAPHICSRESOURCEBUNDLE_H__

/**
$Id$
*/
