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



/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:18  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2004/12/21 01:25:17  marcelloptr
*added cvs log section
*
*/



#endif //_XMAKE_UTILS_H__


