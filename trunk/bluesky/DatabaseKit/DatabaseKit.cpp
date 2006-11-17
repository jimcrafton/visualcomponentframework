#include "DatabaseKit.h"

#include "vcf/FoundationKit/RTTIMacros.h"
#include "DatabaseKitRTTI.inl"


using namespace VCF;

void DatabaseKit::init( int argc, char **argv )
{
    DatabaseToolkit::create();

	REGISTER_CLASSINFO_EXTERNAL(DataField);
	REGISTER_CLASSINFO_EXTERNAL(StringField);
	REGISTER_CLASSINFO_EXTERNAL(BooleanField);
	REGISTER_CLASSINFO_EXTERNAL(DateTimeField);
	REGISTER_CLASSINFO_EXTERNAL(DoubleField);
	REGISTER_CLASSINFO_EXTERNAL(IntegerField);
}

void DatabaseKit::terminate()
{
    DatabaseToolkit::destroy();
}
