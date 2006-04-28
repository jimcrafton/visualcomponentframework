#ifndef _VCF_SKETCHVIEW_H__
#define _VCF_SKETCHVIEW_H__
//SketchView.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"

#define SKETCHVIEW_CLASSID		"f297d0f2-4ece-4fb7-86ef-bea8b395e4af"
/**
class SketchView documentation
*/
class SketchView : public VCF::Object, public VCF::AbstractView {
public:
	_class_rtti_( SketchView, "VCF::Object", SKETCHVIEW_CLASSID )
	_class_rtti_end_

	SketchView();
	virtual ~SketchView();

	virtual void paintView( VCF::GraphicsContext* ctx );
protected:

};


#endif // _VCF_SKETCHVIEW_H__


/**
$Id$
*/
