#ifndef _VCF_SKETCHWINDOW_H__
#define _VCF_SKETCHWINDOW_H__
//SketchWindow.h

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


#define SKETCHWINDOW_CLASSID		"e035e1bd-f375-4b97-9736-710c17e672c8"

/**
class SketchWindow documentation
*/
class SketchWindow : public VCF::Window {
public:
	_class_rtti_( SketchWindow, "VCF::Window", SKETCHWINDOW_CLASSID )
	_class_rtti_end_


	SketchWindow();
	virtual ~SketchWindow();


protected:

	void onDocInitialized( VCF::Event* e ) ;
};


#endif // _VCF_SKETCHWINDOW_H__


/**
$Id$
*/
