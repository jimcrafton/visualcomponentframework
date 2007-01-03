
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBUIMetricsManager.h"

using namespace VCF;


VCF::Font XCBUIMetricsManager::getDefaultFontFor( const FontType& type )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Font();
}

double XCBUIMetricsManager::getValue( const MetricType& type, const String& text, Font* alternateFont )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

Size XCBUIMetricsManager::getSize( const MetricType& type, const String& text, Font* alternateFont )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Size();
}

Rect XCBUIMetricsManager::getRect( const MetricType& type, Rect* rect, Font* alternateFont )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Rect();
}

/**
$Id$
*/

