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
$Id$
*/
