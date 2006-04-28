//RemoteObjectKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;
using namespace VCFRemote;

void initRemoteObjectKit()
{
	DistributedClassRegistry::create();
}

void terminateRemoteObjectKit()
{
	DistributedClassRegistry::getDistributedClassRegistry()->release();
}


/**
$Id$
*/
