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
*Revision 1.3  2005/01/02 03:04:27  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/21 01:25:17  marcelloptr
*added cvs log section
*
*/



#endif //_XMAKE_UTILS_H__


