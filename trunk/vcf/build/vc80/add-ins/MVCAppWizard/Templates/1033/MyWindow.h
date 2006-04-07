#ifndef _[!output UPPER_CASE_PROJECT_NAME]WINDOW_H__
#define _[!output UPPER_CASE_PROJECT_NAME]WINDOW_H__


/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"


#define [!output UPPER_CASE_PROJECT_NAME]WINDOW_CLASSID		"[!output WINDOW_UUID]"


/**
class [!output PROJECT_NAME]Window documentation
*/
class [!output PROJECT_NAME]Window  : public VCF::Window{
public: 
	_class_rtti_( [!output PROJECT_NAME]Window, "VCF::Window", [!output UPPER_CASE_PROJECT_NAME]WINDOW_CLASSID )
	_class_rtti_end_

	[!output PROJECT_NAME]Window();
	virtual ~[!output PROJECT_NAME]Window();


protected:
	void onDocInitialized( VCF::Event* e ) ;
};




#endif //_[!output UPPER_CASE_PROJECT_NAME]WINDOW_H__



