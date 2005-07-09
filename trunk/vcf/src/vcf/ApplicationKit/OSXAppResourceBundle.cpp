//OSXAppResourceBundle
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/OSXAppResourceBundle.h"

using namespace VCF;

OSXAppResourceBundle::OSXAppResourceBundle( AbstractApplication* app ): 
	app_(app)
{
	VCF_ASSERT( NULL != app_ );
}
