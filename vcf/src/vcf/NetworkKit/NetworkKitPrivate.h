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


#ifdef WIN32
#include "vcf/NetworkKit/Win32SocketPeer.h"
#include "vcf/NetworkKit/Win32DatagramSocketPeer.h"
#endif


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:48  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.16.1  2003/03/23 03:23:43  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.4  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.1.2.3  2002/04/03 19:37:16  zzack
*include style changed
*
*Revision 1.1.2.2  2002/03/25 04:25:42  ddiego
*added some of the BSD license header plus the cvs log stamp to the
*new foundation kit and network global headers
*
*
*/


#endif // _VCF_NETWORKKITPRIVATE_H__


