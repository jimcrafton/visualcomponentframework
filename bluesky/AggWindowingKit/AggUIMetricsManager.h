#ifndef _VCF_XCBUIMETRICSMANAGER_H__
#define _VCF_XCBUIMETRICSMANAGER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/UIMetricsManager.h"

namespace VCF {

	class AggUIMetricsManager : public UIMetricsManager {
	public:

		virtual Font getDefaultFontFor( const FontType& type );

		virtual double getValue( const MetricType& type, const String& text, Font* alternateFont );

		virtual Size getSize( const MetricType& type, const String& text, Font* alternateFont );

		virtual Rect getRect( const MetricType& type, Rect* rect, Font* alternateFont );
	};
};

#endif //_VCF_XCBUIMETRICSMANAGER_H__

/**
$Id$
*/

