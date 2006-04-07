

#ifndef _GRAPHICSRESOURCEBUNDLE_H__
#define _GRAPHICSRESOURCEBUNDLE_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {


class Image;
class GraphicsResourceBundlePeer;

/**
\class GraphicsResourceBundle GraphicsResourceBundle.h "vcf/GraphicsKit/GraphicsResourceBundle.h"
*A GraphicsResourceBundle is used to represent a collection of resources
that happen to be images. 
*/
class GRAPHICSKIT_API GraphicsResourceBundle : public ResourceBundle {
public:

	GraphicsResourceBundle();
	virtual ~GraphicsResourceBundle();

	Image* getImage( const ulong32& resourceID );

	/**
	*returns an Image based on a given resource name
	*/
	Image* getImage( const String& resourceName );
protected:
	
	GraphicsResourceBundlePeer* graphicsResPeer_;
};


};


#endif //_GRAPHICSRESOURCEBUNDLE_H__






