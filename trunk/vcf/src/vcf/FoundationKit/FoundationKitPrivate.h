#ifndef _VCF_FOUNDATIONKITPRIVATE_H__
#define _VCF_FOUNDATIONKITPRIVATE_H__
//FoundationKitPrivate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#if defined(VCF_WIN) && !defined(VCF_DOTNET)
#	include "vcf/FoundationKit/Win32SystemToolkit.h"
#	include "vcf/FoundationKit/Win32SemaphorePeer.h"
#	include "vcf/FoundationKit/Win32LibraryPeer.h"
#	include "vcf/FoundationKit/Win32Peer.h"
#	include "vcf/FoundationKit/Win32FilePeer.h"
#	include "vcf/FoundationKit/Win32FileStream.h"
#	include "vcf/FoundationKit/Win32ProcessPeer.h"
#	include "vcf/FoundationKit/Win32SystemPeer.h"
#	include "vcf/FoundationKit/Win32Thread.h"
#	include "vcf/FoundationKit/Win32Registry.h"
#	include "vcf/FoundationKit/Win32Mutex.h"
#elif defined(VCF_DOTNET)
#	include "vcf/FoundationKit/DotNetSystemToolkit.h"
#	include "vcf/FoundationKit/DotNetSemaphorePeer.h"
#	include "vcf/FoundationKit/DotNetLibraryPeer.h"
#	include "vcf/FoundationKit/DotNetPeer.h"
#	include "vcf/FoundationKit/DotNetFilePeer.h"
#	include "vcf/FoundationKit/DotNetFileStream.h"
#	include "vcf/FoundationKit/DotNetProcessPeer.h"
#	include "vcf/FoundationKit/DotNetSystemPeer.h"
#	include "vcf/FoundationKit/DotNetThread.h"
#	include "vcf/FoundationKit/DotNetRegistry.h"
#	include "vcf/FoundationKit/DotNetMutex.h"
#elif defined (VCF_POSIX)
	//pull in the linux headers here
	#include <sys/stat.h>
	#include <signal.h>
	#include <semaphore.h>
#	include "vcf/FoundationKit/LinuxSystemToolkit.h"
#	include "vcf/FoundationKit/LinuxPeer.h"
#	include "vcf/FoundationKit/LinuxFilePeer.h"
#	include "vcf/FoundationKit/LinuxFileStream.h"
#	include "vcf/FoundationKit/LinuxSemaphorePeer.h"
#	include "vcf/FoundationKit/LinuxLibraryPeer.h"
#	include "vcf/FoundationKit/LinuxProcessPeer.h"
#	include "vcf/FoundationKit/LinuxSystemPeer.h"
#	include "vcf/FoundationKit/LinuxDebugUtils.h"
#	include "vcf/FoundationKit/PosixThread.h"
#	include "vcf/FoundationKit/LinuxRegistry.h"
#	include "vcf/FoundationKit/PosixMutex.h"
#	include "vcf/FoundationKit/PosixCondition.h"
#elif defined (VCF_OSX)
//pull in the OSX Foundation headers here
#include <Carbon/Carbon.h>
#include "vcf/FoundationKit/OSXSystemToolkit.h"
#include "vcf/FoundationKit/OSXPeer.h"
#include "vcf/FoundationKit/OSXFilePeer.h"
#include "vcf/FoundationKit/OSXFileStream.h"
#include "vcf/FoundationKit/OSXSemaphorePeer.h"
#include "vcf/FoundationKit/OSXLibraryPeer.h"
#include "vcf/FoundationKit/OSXProcessPeer.h"
#include "vcf/FoundationKit/OSXSystemPeer.h"
#include "vcf/FoundationKit/OSXThread.h"
#include "vcf/FoundationKit/OSXRegistry.h"
#include "vcf/FoundationKit/OSXMutexPeer.h"
#include "vcf/FoundationKit/OSXConditionPeer.h"
#endif


#endif // _VCF_FOUNDATIONKITPRIVATE_H__

/**
$Id$
*/
