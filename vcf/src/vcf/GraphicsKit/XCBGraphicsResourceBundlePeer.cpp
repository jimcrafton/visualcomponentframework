
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBGraphicsResourceBundlePeer.h"

using namespace VCF;

XCBGraphicsResourceBundlePeer::~XCBGraphicsResourceBundlePeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Image* XCBGraphicsResourceBundlePeer::getImage( const String& resourceName )
{
	//LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	
	/**
	This function will return NULL - this will let the VCF's default, file based
	resource management routines to be used instead.
	*/
	
	return NULL;
}
/**
$Id$
*/

