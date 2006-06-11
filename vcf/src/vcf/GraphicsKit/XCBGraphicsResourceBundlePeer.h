#ifndef _VCF_XCBGRAPHICSRESOURCEBUNDLEPEER_H__
#define _VCF_XCBGRAPHICSRESOURCEBUNDLEPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/LinuxResourceBundle.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"

namespace VCF
{

class XCBGraphicsResourceBundlePeer : public LinuxResourceBundle, public GraphicsResourceBundlePeer {
public:
	~XCBGraphicsResourceBundlePeer();
	virtual Image* getImage( const String& resourceName );
};

};

#endif // _VCF_XCBAPPLICATIONRESOURCEBUNDLEPEER_H__

/**
$Id$
*/

