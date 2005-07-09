
#ifndef _GTKGRAPHICSRESOURCEBUNDLE_H__
#define _GTKGRAPHICSRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/FoundationKit/LinuxResourceBundle.h"


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
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:05:58  ddiego
*added missing gtk files
*
*Revision 1.1.2.1  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*/







#endif //_GTKGRAPHICSRESOURCEBUNDLE_H__



