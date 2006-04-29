#ifndef _VCF_PROPERTYCHANGEEXCEPTION_H__
#define _VCF_PROPERTYCHANGEEXCEPTION_H__
//PropertyChangeException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class PropertyChangeEvent;
/**
\class PropertyChangeException PropertyChangeException.h "vcf/FoundationKit/PropertyChangeException.h"
*/
class FOUNDATIONKIT_API PropertyChangeException : public BasicException {
public:
	PropertyChangeException( PropertyChangeEvent* event ):
		BasicException( PROPERTY_CHANGE_BAD ){
		changeEvent_ = event;
	};

	virtual ~PropertyChangeException() throw() {};

	PropertyChangeEvent* getChangeEvent(){
		return changeEvent_;
	};

private:
	PropertyChangeEvent* changeEvent_;
};

};


#endif // _VCF_PROPERTYCHANGEEXCEPTION_H__

/**
$Id$
*/
