
#ifndef _XMAKE_UTILS_H__
#define _XMAKE_UTILS_H__

#include "xmake.h"

namespace xmake {

		

	class XMakeUtils {
	public:
		String generateMakefile( const String& project, const String& makefileName, XMLMake& xmakeObj );		
	};

};



#endif //_XMAKE_UTILS_H__


