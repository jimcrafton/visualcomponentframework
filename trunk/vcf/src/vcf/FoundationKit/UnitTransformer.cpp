//UnitTransformer.cpp

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/UnitTransformer.h"

using namespace VCF;

UnitTransformer* UnitTransformer::currentTransformer_ = NULL;

UnitTransformer* UnitTransformer::getCurrentTransformer()
{
	return UnitTransformer::currentTransformer_;
}

void UnitTransformer::setCurrentTransformer(UnitTransformer* val) 
{
	UnitTransformer::currentTransformer_ = val;
}

String UnitTransformer::xfrmString( const String& value, Object* context )
{
	if ( NULL != UnitTransformer::currentTransformer_ ) {
		return UnitTransformer::currentTransformer_->transform(value,context);
	}

	return value;
}