
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBApplicationPeer.h"

using namespace VCF;

bool XCBApplicationPeer::initApp()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return true;
}

void XCBApplicationPeer::terminateApp()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

AbstractApplication* XCBApplicationPeer::getApplication()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

void XCBApplicationPeer::setApplication( AbstractApplication* application )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

String XCBApplicationPeer::getFileName()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return "";
}

OSHandleID XCBApplicationPeer::getHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

void XCBApplicationPeer::setHandleID( OSHandleID handleID )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

/**
$Id$
*/

