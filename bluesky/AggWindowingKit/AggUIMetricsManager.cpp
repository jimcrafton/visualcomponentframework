
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "AggUIMetricsManager.h"

using namespace VCF;


VCF::Font AggUIMetricsManager::getDefaultFontFor( const FontType& type )
{

	return Font();
}

double AggUIMetricsManager::getValue( const MetricType& type, const String& text, Font* alternateFont )
{

	return 0.0;
}

Size AggUIMetricsManager::getSize( const MetricType& type, const String& text, Font* alternateFont )
{

	return Size();
}

Rect AggUIMetricsManager::getRect( const MetricType& type, Rect* rect, Font* alternateFont )
{

	return Rect();
}

/**
$Id$
*/

