//DistributedException.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DistributedException.h
#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;

using namespace VCFRemote;


DistributedException::DistributedException():
	BasicException("")
{

}

DistributedException::~DistributedException() throw()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:31:56  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/05/17 20:37:51  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.16.1  2003/03/23 03:24:02  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.2.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.2  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


