
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "AggApplicationPeer.h"

using namespace VCF;

AggApplicationPeer::AggApplicationPeer():
    app_(NULL)
{

}

AggApplicationPeer::~AggApplicationPeer()
{

}

bool AggApplicationPeer::initApp()
{

	return true;
}

void AggApplicationPeer::terminateApp()
{

}

AbstractApplication* AggApplicationPeer::getApplication()
{
	return app_;
}

void AggApplicationPeer::setApplication( AbstractApplication* application )
{
	app_ = application;
}

String AggApplicationPeer::getFileName()
{
	const CommandLine& cmdLine = FoundationKit::getCommandLine();

	return cmdLine.getArgument(0);
}

OSHandleID AggApplicationPeer::getHandleID()
{
	return 0;
}

void AggApplicationPeer::setHandleID( OSHandleID handleID )
{

}

/**
$Id$
*/

