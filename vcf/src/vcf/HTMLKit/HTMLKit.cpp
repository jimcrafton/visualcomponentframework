//HTMLKit.cpp

#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"


#include "vcf/FoundationKit/RTTIMacros.h"


using namespace VCF;


_class_rtti_(HTMLBrowserControl, "VCF::Control", HTMLBROWSERCONTROL_CLASSID)
_property_( String, "currentURL", getCurrentURL, setCurrentURL, "" );
_class_rtti_end_




		








void HTMLKit::init( int argc, char** argv )
{
	HTMLToolkit::create();

	REGISTER_CLASSINFO_EXTERNAL( HTMLBrowserControl );

	Component::registerComponent( "VCF::HTMLBrowserControl", ADDITIONAL_CATEGORY );
}


void HTMLKit::terminate()
{
	HTMLToolkit::destroy();
}