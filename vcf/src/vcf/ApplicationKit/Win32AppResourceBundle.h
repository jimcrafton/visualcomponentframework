#ifndef _VCF_WIN32APPRESOURCEBUNDLE_H__
#define _VCF_WIN32APPRESOURCEBUNDLE_H__

#include "vcf/GraphicsKit/Win32GraphicsResourceBundle.h"

namespace VCF {

	class Win32AppResourceBundle : public Win32GraphicsResourceBundle {
	public:
		Win32AppResourceBundle( AbstractApplication* app );
	protected:
		AbstractApplication* app_;
		virtual HINSTANCE getResourceInstance();
	};

};




#endif //_VCF_WIN32APPRESOURCEBUNDLE_H__



