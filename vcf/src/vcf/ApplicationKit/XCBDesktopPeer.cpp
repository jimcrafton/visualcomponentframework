
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBDesktopPeer.h"

using namespace VCF;

XCBDesktopPeer::XCBDesktopPeer( Desktop* desktop )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBDesktopPeer::desktopBeginPainting( Rect* clippingRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBDesktopPeer::desktopEndPainting()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBDesktopPeer::desktopSupportsVirtualDirectories()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

bool XCBDesktopPeer::desktopHasFileSystemDirectory()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

String XCBDesktopPeer::desktopGetDirectory()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return "";
}

OSHandleID XCBDesktopPeer::desktopGetHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

OSHandleID XCBDesktopPeer::desktopGetGraphicsContextHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

void XCBDesktopPeer::desktopSetDesktop( Desktop* desktop )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

uint32 XCBDesktopPeer::desktopGetWidth()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

uint32 XCBDesktopPeer::desktopGetHeight()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

Rect XCBDesktopPeer::desktopGetUsableBounds()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Rect();
}

Point XCBDesktopPeer::getCurrentMousePosition()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Point();
}


/**
$Id$
*/

