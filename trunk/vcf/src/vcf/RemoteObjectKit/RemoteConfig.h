#ifndef _VCF_REMOTECONFIG_H__
#define _VCF_REMOTECONFIG_H__
//RemoteConfig.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifdef WIN32
	#ifdef REMOTEKIT_DLL
		#if defined(REMOTEKIT_EXPORTS)
			#define REMOTEKIT_API __declspec(dllexport)
		#else
			#define REMOTEKIT_API __declspec(dllimport)
		#endif
	#else
		#define REMOTEKIT_API
	#endif //REMOTEKIT_DLL
#else
	#define REMOTEKIT_API
#endif

namespace VCFRemote {

}; //end of namespace VCFRemote


#endif // _VCF_REMOTECONFIG_H__

/**
$Id$
*/
