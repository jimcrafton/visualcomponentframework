#ifndef _$$ROOT$$WINDOW_H__
#define _$$ROOT$$WINDOW_H__


#define $$ROOT$$WINDOW_CLASSID		"$$WINDOWUUID$$"


/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"


/**
class $$Root$$Window documentation
*/
class $$Root$$Window  : public VCF::Window{
public: 
	_class_rtti_( $$Root$$Window, "VCF::Window", $$ROOT$$WINDOW_CLASSID )
	_class_rtti_end_

	$$Root$$Window();
	virtual ~$$Root$$Window();


protected:
	void onDocInitialized( VCF::Event* e ) ;
};




#endif //_$$ROOT$$WINDOW_H__



