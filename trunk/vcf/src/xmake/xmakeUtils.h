#ifndef _XMAKE_UTILS_H__
#define _XMAKE_UTILS_H__
//xmakeUtils.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "xmake.h"

namespace xmake {

		

	class XMakeUtils {
	public:
		String generateMakefile( const String& project, const String& makefileName, XMLMake& xmakeObj );		
	};

};



#endif //_XMAKE_UTILS_H__

/**
$Id$
*/
