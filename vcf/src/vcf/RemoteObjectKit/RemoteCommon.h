#ifndef _VCF_REMOTECOMMON_H__
#define _VCF_REMOTECOMMON_H__
//RemoteCommon.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/RemoteObjectKit/RemoteConfig.h"

//default ClassServer port
#define CLASS_SERVER_PORT			0x278C

#define LOCAL_CLASS_SERVER			"localhost"

#define REMOTE_MSG						1000
#define CLASS_SVR_MSG_NEW_INST					REMOTE_MSG + 1

//server located - it is a in-process lib, so load it
#define CLASS_SVR_MSG_LOAD_VPL					REMOTE_MSG + 2

//a Distributed Application started up
#define CLASS_SVR_DISTRIB_APP_STARTED				REMOTE_MSG + 3

//a Distributed Application shut down
#define CLASS_SVR_DISTRIB_APP_EXITED				REMOTE_MSG + 4

/**
*sent by the CLassServer to the appropriate Distributed App
*to go ahead and attempt to create a new instance
*/
#define DISTRIB_APP_MSG_NEW_INST				REMOTE_MSG + 5

/**
*sent by the Distributed App to the ClassServer
*to indicate a successful instance was created
*a the proxy is being sent back to the ClassServer
*/
#define CLASS_SVR_MSG_NEW_PROXY					REMOTE_MSG + 6

/**
*sent to the ClassServer when the Proxy::invoke()
*is called on an out of process or remote object
*/
#define CLASS_SVR_MSG_PROXY_INVOKE				REMOTE_MSG + 7

#define CLASS_SVR_MSG_PROXY_INVOKE_RETURNED		REMOTE_MSG + 8

namespace VCFRemote {


};


#endif // _VCF_REMOTECOMMON_H__

/**
$Id$
*/
