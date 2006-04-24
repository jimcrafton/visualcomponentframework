
#ifndef _OSXGRAPHICSRESOURCEBUNDLE_H__
#define _OSXGRAPHICSRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/FoundationKit/OSXResourceBundle.h"


namespace VCF  {

class OSXGraphicsResourceBundle : public OSXResourceBundle, public GraphicsResourceBundlePeer {
public:
	OSXGraphicsResourceBundle();

	virtual ~OSXGraphicsResourceBundle();

	
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
*Revision 1.2  2005/07/09 23:06:00  ddiego
*added missing gtk files
*
*Revision 1.1.2.2  2005/06/23 01:26:56  ddiego
*build updates
*
*/







#endif //_OSXGRAPHICSRESOURCEBUNDLE_H__



