#ifndef _VCF_XCBAPPLICATIONRESOURCEBUNDLEPEER_H__
#define _VCF_XCBAPPLICATIONRESOURCEBUNDLEPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/XCBGraphicsResourceBundlePeer.h"

namespace VCF
{

class XCBApplicationResourceBundlePeer : public XCBGraphicsResourceBundlePeer {
public:
	 XCBApplicationResourceBundlePeer( AbstractApplication* app );
};

};

#endif // _VCF_XCBAPPLICATIONRESOURCEBUNDLEPEER_H__

/**
$Id$
*/

