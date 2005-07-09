#ifndef _[!output UPPER_CASE_PROJECT_NAME]VIEW_H__
#define _[!output UPPER_CASE_PROJECT_NAME]VIEW_H__

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"


#define [!output UPPER_CASE_PROJECT_NAME]VIEW_CLASSID		"[!output VIEW_UUID]"


/**
class [!output PROJECT_NAME]View documentation
*/
class [!output PROJECT_NAME]View : public VCF::Object, public VCF::AbstractView {
public: 
	_class_rtti_( [!output PROJECT_NAME]View, "VCF::Object", [!output UPPER_CASE_PROJECT_NAME]VIEW_CLASSID )
	_class_rtti_end_

	[!output PROJECT_NAME]View();

	virtual ~[!output PROJECT_NAME]View();


	virtual void paintView( VCF::GraphicsContext* ctx );
protected:

};



#endif //_[!output UPPER_CASE_PROJECT_NAME]VIEW_H__



