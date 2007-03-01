//DatabaseUIKit.cpp

#include "DatabaseUIKit.h"
#include "vcf/ApplicationKit/Label.h"
#include "DataLabel.h"


#include "vcf/FoundationKit/RTTIMacros.h"
#include "DatabaseUIKitRTTI.inl"


using namespace VCF;




void DatabaseUIKit::init( int argc, char **argv )
{
	DatabaseKit::init( argc, argv );

	REGISTER_CLASSINFO_EXTERNAL(DataLabel);
}

void DatabaseUIKit::terminate()
{
	DatabaseKit::terminate();
}

