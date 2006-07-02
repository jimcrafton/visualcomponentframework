#ifndef _VCF_LINUXDEBUGUTILS_HPP__
#define _VCF_LINUXDEBUGUTILS_HPP__ 



/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#define VCF_DEBUG_CODE(statement) \
{ \
	statement \
} 

namespace VCF
{
	namespace LinuxDebugUtils
	{
		void FunctionNotImplemented(const String& funcName);
	};
};

#endif  // _VCF_LINUXDEBUGUTILS_HPP__

/**
$Id$
*/


