#ifndef _VCF_NETWORKKITPRIVATE_H__
#define _VCF_NETWORKKITPRIVATE_H__
//NetworkKitPrivate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifdef VCF_WIN
//this makes sence to be here since all files include this header
//and we make chaneg only in one place
#include <winsock2.h>
#include "vcf/NetworkKit/Win32SocketPeer.h"
#include "vcf/NetworkKit/Win32DatagramSocketPeer.h"
#endif


#endif // _VCF_NETWORKKITPRIVATE_H__

/**
$Id$
*/
