#ifndef _VCF_APPLICATIONRESOURCEBUNDLE_H__
#define _VCF_APPLICATIONRESOURCEBUNDLE_H__



/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

	class ApplicationResourceBundle : public GraphicsResourceBundle  {
	public:
		ApplicationResourceBundle( AbstractApplication* app );

		virtual String getResourcesDirectory();

	protected:
		AbstractApplication* app_;
	};
};


#endif //_VCF_APPLICATIONRESOURCEBUNDLE_H__



