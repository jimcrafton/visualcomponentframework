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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.6.10.1  2004/04/26 21:58:46  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2003/01/08 00:19:48  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_REMOTECOMMON_H__


