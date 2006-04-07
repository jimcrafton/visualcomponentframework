//OSXPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <errno.h>

using namespace VCF;


String OSXStringUtils::getErrnoString( int errCode )
{
	String result;
	switch ( errCode ) {
		case EFAULT: {
				result = "Bad address.";
			}
			break;

		case EACCES: {
				result = "Permission denied.";
			}
			break;

		case EPERM: {
				result = "Operation not permitted";

			}
			break;


		case ENAMETOOLONG: {
				result = "File name too long.";
			}
			break;

		case ENOENT: {
				result = "No such file or directory.";
			}
			break;

		case ENOTDIR: {
				result = "Not a directory.";
			}
			break;

		case ENOMEM: {
				result = "Cannot allocate memory.";
			}
			break;

		case EROFS: {
				result = "Read-only file system.";
			}
			break;

		case EEXIST: {
				result = "File exists.";
			}
			break;

		case EISDIR: {
				result = "Is a directory.";
			}
			break;

		case ENXIO: {
				result = "Device not configured.";
			}
			break;

		case ENODEV: {
				result = "Operation not supported by device.";
			}
			break;

		case ELOOP: {
				result = "Too many levels of symbolic links.";
			}
			break;

		case ENFILE: {
				result = "Too many open files in system.";
			}
			break;

		case EMFILE: {
				result = "Too many open files.";
			}
			break;
			
		case EINVAL: {
			result = "Invalid argument.";
		}
		break;
	}
	return result;
}



/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2005/12/04 20:58:32  ddiego
*more osx impl work. foundationkit is mostly complete now.
*
*Revision 1.4.2.1  2005/11/21 04:00:51  ddiego
*more osx updates.
*
*Revision 1.4  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/06/15 15:41:14  ddiego
*minor osx stuff
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/10 20:42:08  ddiego
*osx updates
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


