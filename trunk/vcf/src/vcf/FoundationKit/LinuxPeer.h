#ifndef _VCF_LINUXPEER_H__
#define _VCF_LINUXPEER_H__ 
//LinuxPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

/**
*Main header for implementation object that Linux headers
*/

namespace VCFLinux
{
/**
*General purpose utility class
*/
class LinuxUtils
{
public:
	/**
	*returns a string that represents the error code.
	*this functions expects to have the represent the current
	*value of errno
	*/
	static VCF::String getErrorString( const int& errorCode );
};

}

#endif // _VCF_LINUXPEER_H__

/**
$Id$
*/
