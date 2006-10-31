#include "DatabaseKit.h"

#include "vcf/FoundationKit/RTTIMacros.h"
#include "DatabaseKitRTTI.inl"


using namespace VCF;

void DatabaseKit::init( int argc, char **argv )
{
    DatabaseToolkit::create();

	REGISTER_CLASSINFO_EXTERNAL(DataField);
}

void DatabaseKit::terminate()
{
    DatabaseToolkit::destroy();
}
