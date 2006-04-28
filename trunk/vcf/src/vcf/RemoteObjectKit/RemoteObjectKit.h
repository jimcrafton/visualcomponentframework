#ifndef _VCF_REMOTEOBJECTKIT_H__
#define _VCF_REMOTEOBJECTKIT_H__
//RemoteObjectKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/RemoteObjectKit/RemoteObjectKitSelectLib.h"
#include "vcf/RemoteObjectKit/RemoteConfig.h"
#include "vcf/NetworkKit/NetworkKit.h"

#include "vcf/RemoteObjectKit/RemoteCommon.h"
#include "vcf/RemoteObjectKit/ClassRegistryEntry.h"
#include "vcf/RemoteObjectKit/ClassServerInstance.h"
#include "vcf/RemoteObjectKit/DistributedClassRegistry.h"
#include "vcf/RemoteObjectKit/DistributedException.h"
#include "vcf/RemoteObjectKit/InstanceID.h"
#include "vcf/RemoteObjectKit/Proxy.h"
#include "vcf/RemoteObjectKit/AbstractDistributedApplication.h"

REMOTEKIT_API void initRemoteObjectKit();
REMOTEKIT_API void terminateRemoteObjectKit();


#endif // _VCF_REMOTEOBJECTKIT_H__

/**
$Id$
*/
