//OSXAppResourceBundle.cpp
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/OSXAppResourceBundle.h"

using namespace VCF;

OSXAppResourceBundle::OSXAppResourceBundle( AbstractApplication* app ):
	OSXGraphicsResourceBundle(),
	app_(app)
{

}

CFBundleRef OSXAppResourceBundle::getBundle()
{
	return OSXGraphicsResourceBundle::getBundle();
}