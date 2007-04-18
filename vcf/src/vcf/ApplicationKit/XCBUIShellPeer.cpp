
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBUIShellPeer.h"

using namespace VCF;

XCBUIShellPeer::XCBUIShellPeer( UIShell* shell )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

XCBUIShellPeer::~XCBUIShellPeer()
{

}

void XCBUIShellPeer::shellBeginPainting( Rect* clippingRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIShellPeer::shellEndPainting()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBUIShellPeer::shellSupportsVirtualDirectories()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

bool XCBUIShellPeer::shellHasFileSystemDirectory()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

String XCBUIShellPeer::shellGetDirectory()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return "";
}

OSHandleID XCBUIShellPeer::shellGetHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

OSHandleID XCBUIShellPeer::shellGetGraphicsContextHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

void XCBUIShellPeer::shellSetUIShell( UIShell* shell )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

uint32 XCBUIShellPeer::shellGetWidth()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

uint32 XCBUIShellPeer::shellGetHeight()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

Rect XCBUIShellPeer::shellGetUsableBounds()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Rect();
}

Point XCBUIShellPeer::getCurrentMousePosition()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Point();
}


/**
$Id$
*/

