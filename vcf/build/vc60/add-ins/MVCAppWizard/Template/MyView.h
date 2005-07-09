#ifndef _$$ROOT$$VIEW_H__
#define _$$ROOT$$VIEW_H__



#define $$ROOT$$VIEW_CLASSID		"$$VIEWUUID$$"



/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"

/**
class $$Root$$View documentation
*/
class $$Root$$View : public VCF::Object, public VCF::AbstractView {
public: 
	_class_rtti_( $$Root$$View, "VCF::Object", $$ROOT$$VIEW_CLASSID )
	_class_rtti_end_

	$$Root$$View();

	virtual ~$$Root$$View();


	virtual void paintView( VCF::GraphicsContext* ctx );
protected:

};



#endif //_$$ROOT$$VIEW_H__



