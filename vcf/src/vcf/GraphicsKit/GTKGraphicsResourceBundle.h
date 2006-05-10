
#ifndef _GTKGRAPHICSRESOURCEBUNDLE_H__
#define _GTKGRAPHICSRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/FoundationKit/LinuxResourceBundle.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"


namespace VCF  {

class GTKGraphicsResourceBundle : public LinuxResourceBundle, public GraphicsResourceBundlePeer {
public:
	GTKGraphicsResourceBundle();

	virtual ~GTKGraphicsResourceBundle();

	
	/**
	*returns an Image based on a given resource name
	*/
	virtual Image* getImage( const String& resourceName );

	
protected:
	
	
};

};


/**
$Id$
*/




#endif //_GTKGRAPHICSRESOURCEBUNDLE_H__



