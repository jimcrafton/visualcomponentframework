//LinuxPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

using namespace VCF;
using namespace VCFLinux;

namespace
{
    String ErrorStrings[] = 
    {
        "No error.",                            // 0 
        "Operation not permitted.",             // EPERM		 1
        "No such file or directory.",           // ENOENT		 2
        "No such process.",                     // ESRCH		 3
        "Interrupted system call.",             // EINTR		 4
        "I/O error.",                           // EIO		 5
        "No such device or address.",           // ENXIO		 6
        "Argument list too long.",              // E2BIG		 7
        "Exec format error.",                   // ENOEXEC     8
        "Bad file number.",                     // EBADF		 9
        "No child processes.",                  // ECHILD		10
        "Try again.",                           // EAGAIN		11
        "Out of memory.",                       // ENOMEM		12
        "Permission denied.",                   // EACCES		13
        "Bad address.",                         // EFAULT		14
        "Block device required.",               // ENOTBLK	15
        "Device or resource busy.",             // EBUSY		16
        "File exists.",                         // EEXIST		17
        "Cross-device link.",                   // EXDEV		18
        "No such device.",                      // ENODEV		19
        "Not a directory.",                     // ENOTDIR	20
        "Is a directory.",                      // EISDIR		21
        "Invalid argument.",                    // EINVAL		22
        "File table overflow.",                 // ENFILE		23
        "Too many open files.",                 // EMFILE		24
        "Not a typewriter.",                    // ENOTTY		25
        "Text file busy.",                      // ETXTBSY	26
        "File too large.",                      // EFBIG		27
        "No space left on device.",             // ENOSPC		28
        "Illegal seek.",                        // ESPIPE		29
        "Read-only file system.",               // EROFS		30
        "Too many links.",                      // EMLINK		31
        "Broken pipe.",                         // EPIPE		32
        "Math argument out of domain of func.", // EDOM		33
        "Math result not representable."        // ERANGE		34
    };

    const int ErrorStringCount = sizeof(ErrorStrings)/sizeof(String);
}


String LinuxUtils::getErrorString( const int& errorCode )
{
	String result;
	//error string based on linux man page docs
	//assumes
	switch ( errorCode ) {

        case EFAULT: {
				result = "Path points outside your accessible address space.";
			}
			break;

		case EACCES: {
				result = "Write access to the directory containing the pathname "
				         "is not allowed\nfor hte process's effective uid, or one "
				         "of the directories in the pathname\ndid not allow search "
				         "(execute) permission.";
			}
			break;

		case EPERM: {
				result = "The directory that is represented by the path name has "
				         "the sticky bit set\nand the process's effective uid is "
				         "neither the uid of the file to be deleted\nnor that of "
				         "the directory containing it.";
			}
			break;


		case ENAMETOOLONG: {
				result = "The pathname was too long.";
			}
			break;

		case ENOENT: {
				result = "A directory component in the pathname does not exist or "
				         "is a dangling symbolic link.";
			}
			break;

		case ENOTDIR: {
				result = "A component used as a directpy in a path is not, "
				         "in fact, a directory.";
			}
			break;

		case ENOMEM: {
				result = "Insufficient kernel memory.";
			}
			break;

		case EROFS: {
				result = "Path refers to a file that is read-only.";
			}
			break;

		case EEXIST: {
				result = "Path refers to a file that already exists.";
			}
			break;

		case EISDIR: {
				result = "Path refers to a file that is a directory and write "
				         "access was requested.";
			}
			break;

		case ENXIO: {
				result = "O_NONBLOCK or O_WRONLY is set, the named file is a FIFO "
				         "and no\nprocess has the file open for reading. Or, the "
				         "file is a device\nspecial file and no corresponding "
				         "device exists.";
			}
			break;

		case ENODEV: {
				result = "Path refers to a device special file and no "
				         "corresponding device exists.";
			}
			break;

		case ELOOP: {
				result = "Too many symbolic links were were encountered in "
				         "resolving the pathname\nor O_NOFOLLOW was specified "
				         "but the path was a symbolic link.";
			}
			break;

		case ENFILE: {
				result = "The limit on the number of open file handles was "
				         "reached for the OS.";
			}
			break;

		case EMFILE: {
				result = "The limit on the number of open file handles for the "
				         "process was reached.";
			}
			break;

        default: {
                if(errorCode<ErrorStringCount)
                    result = ErrorStrings[errorCode];
                else
                    result = "Unknown.";
            }
            break;
	}
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.5  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.14.1  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4  2002/05/27 22:52:34  ddiego
*added two new tests for testing File and System support in the FoudnationKit
*and verified that they work in Linux. Fixed associated code in getting that to
*work.
*
*Revision 1.3  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*Revision 1.2  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.4.1  2002/03/26 04:46:34  cesarmello
*Linux headers
*
*Revision 1.1  2002/01/28 02:07:59  cesarmello
*Linux file peer
*
*/


