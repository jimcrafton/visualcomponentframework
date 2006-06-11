
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include "vcf/GraphicsKit/XCBFontPeer.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"
#include "vcf/GraphicsKit/XCBGraphicsResourceBundlePeer.h"

using namespace VCF;

XCBGraphicsToolkit::XCBGraphicsToolkit() : 
connection_(NULL),
screen_(NULL)
{
	connection_ = XCBConnect (NULL, NULL);
	if(connection_ != NULL)
	{
		screen_ = XCBSetupRootsIter(XCBGetSetup(connection_)).data;
	}
}

XCBGraphicsToolkit::~XCBGraphicsToolkit()
{
    XCBDisconnect(connection_);
}

XCBConnection* XCBGraphicsToolkit::getConnection()
{
	XCBConnection* connection = NULL;
	GraphicsToolkit* graphicsToolkit = GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	XCBGraphicsToolkit* xcbGraphicsToolkit = dynamic_cast<XCBGraphicsToolkit*>(graphicsToolkit);
	if(xcbGraphicsToolkit != NULL)
	{
		connection = xcbGraphicsToolkit->connection_;
	}
	return connection;
}

XCBSCREEN*     XCBGraphicsToolkit::getScreen()
{
	XCBSCREEN* screen = NULL;
	GraphicsToolkit* graphicsToolkit = GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	XCBGraphicsToolkit* xcbGraphicsToolkit = dynamic_cast<XCBGraphicsToolkit*>(graphicsToolkit);
	if(xcbGraphicsToolkit != NULL)
	{
		screen = xcbGraphicsToolkit->screen_;
	}
	return screen;
}

ContextPeer* XCBGraphicsToolkit::internal_createContextPeer( const unsigned long& width, const unsigned long& height )
{
	return new XCBContextPeer( width, height );
}

ContextPeer* XCBGraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	return new XCBContextPeer( contextID );
}

FontPeer* XCBGraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new XCBFontPeer( fontName );
}

FontPeer* XCBGraphicsToolkit::internal_createFontPeer( const String& fontName, const double& pointSize )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

Image* XCBGraphicsToolkit::internal_createImage( const unsigned long& width, const unsigned long& height, const Image::ImageType& imageType )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

Image* XCBGraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

PrintSessionPeer* XCBGraphicsToolkit::internal_createPrintSessionPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

GraphicsResourceBundlePeer* XCBGraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return new XCBGraphicsResourceBundlePeer();
}

double XCBGraphicsToolkit::internal_getDPI( GraphicsContext* context )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

void XCBGraphicsToolkit::internal_systemSettingsChanged()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

/**
$Id$
*/

