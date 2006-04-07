//HTMLToolkit.cpp

#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLToolkit.h"

#ifdef VCF_WIN32
#include "vcf/HTMLKit/Win32HTMLToolkit.h"
#endif



using namespace VCF;

HTMLToolkit* HTMLToolkit::toolkitInstance = NULL;


void HTMLToolkit::create()
{
#ifdef VCF_WIN32
	HTMLToolkit::toolkitInstance = new Win32HTMLToolkit();
#endif 	

}

void HTMLToolkit::destroy()
{
	delete HTMLToolkit::toolkitInstance;
}

HTMLBrowserPeer* HTMLToolkit::createHTMLBrowserPeer( Control* control )
{
	return HTMLToolkit::toolkitInstance->internal_createHTMLBrowserPeer( control );
}