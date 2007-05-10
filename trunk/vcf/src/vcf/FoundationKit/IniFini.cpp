//IniFini.cpp

#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


Initialization::Initialization( InitializationFunc funcPtr )
{
	FoundationKit::internal_addInitializer( funcPtr );
}




Finalization::Finalization( FinalizationFunc funcPtr )
{
	FoundationKit::internal_addFinalizer( funcPtr );
}