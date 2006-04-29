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
$Id$
*/
