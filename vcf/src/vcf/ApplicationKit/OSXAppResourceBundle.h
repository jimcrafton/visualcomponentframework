#ifndef _VCF_OSXAPPRESOURCEBUNDLE_H__
#define _VCF_OSXAPPRESOURCEBUNDLE_H__

#include "vcf/GraphicsKit/OSXGraphicsResourceBundle.h"

namespace VCF {

	class OSXAppResourceBundle : public OSXGraphicsResourceBundle {
	public:
		OSXAppResourceBundle( AbstractApplication* app );
	protected:
		AbstractApplication* app_;
		
	};

};




#endif //_VCF_OSXAPPRESOURCEBUNDLE_H__

/**
$Id$
*/
