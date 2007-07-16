#ifndef _VCF_MODELEVENT_H__
#define _VCF_MODELEVENT_H__
//ModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class ModelEvent ModelEvent.h "vcf/ApplicationKit/ModelEvent.h"
*/
class APPLICATIONKIT_API ModelEvent : public Event {
public:
	ModelEvent( Object* source, const uint32& type ) :
	  Event( source, type ) {

	  }

	virtual ~ModelEvent(){};

	virtual Object* clone( bool deep=false ) {
		return new ModelEvent(*this);
	}
};


typedef Delegate1<ModelEvent*> ModelDelegate; 
typedef ModelDelegate::ProcedureType ModelHandler;
};


#endif // _VCF_MODELEVENT_H__

/**
$Id$
*/
