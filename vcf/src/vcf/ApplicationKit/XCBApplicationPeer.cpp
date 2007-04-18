
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBApplicationPeer.h"

using namespace VCF;

XCBApplicationPeer::XCBApplicationPeer():
    app_(NULL)
{

}

XCBApplicationPeer::~XCBApplicationPeer()
{

}

bool XCBApplicationPeer::initApp()
{

	return true;
}

void XCBApplicationPeer::terminateApp()
{

}

AbstractApplication* XCBApplicationPeer::getApplication()
{
	return app_;
}

void XCBApplicationPeer::setApplication( AbstractApplication* application )
{
	app_ = application;
}

String XCBApplicationPeer::getFileName()
{
	const CommandLine& cmdLine = FoundationKit::getCommandLine();

	return cmdLine.getArgument(0);
}

OSHandleID XCBApplicationPeer::getHandleID()
{
	return 0;
}

void XCBApplicationPeer::setHandleID( OSHandleID handleID )
{

}

/**
$Id$
*/

