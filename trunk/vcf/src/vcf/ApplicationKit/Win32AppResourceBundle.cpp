//Win32AppResourceBundle
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/Win32AppResourceBundle.h"

using namespace VCF;

Win32AppResourceBundle::Win32AppResourceBundle( AbstractApplication* app ): 
	app_(app)
{
	VCF_ASSERT( NULL != app_ );
}

HINSTANCE Win32AppResourceBundle::getResourceInstance()
{
	VCF_ASSERT( NULL != app_ );

	HINSTANCE result = NULL;	
	
	result = (HINSTANCE)app_->getPeer()->getHandleID();
	
	return result;
}