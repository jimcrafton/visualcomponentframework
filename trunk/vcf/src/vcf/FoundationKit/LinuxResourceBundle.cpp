
#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/LinuxResourceBundle.h"


using namespace VCF;


LinuxResourceBundle::LinuxResourceBundle():
	resourceHandle_(NULL)
{
}


LinuxResourceBundle::~LinuxResourceBundle()
{
}


String LinuxResourceBundle::getString( const String& resourceName )
{
	String result;
		
	return result;
}

String LinuxResourceBundle::getVFF( const String& resourceName )
{
	String result;
	
	return result;
}

Resource* LinuxResourceBundle::getResource( const String& resourceName )
{
	Resource* result = NULL;	
	
	
	return result;
}

ProgramInfo* LinuxResourceBundle::getProgramInfo()
{   
	return NULL;
}
		
		
		