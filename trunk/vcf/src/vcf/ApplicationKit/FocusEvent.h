#ifndef _VCF_FOCUSEVENT_H__
#define _VCF_FOCUSEVENT_H__
//FocusEvent.h

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
\class FocusEvent FocusEvent.h "vcf/ApplicationKit/FocusEvent.h"
* the event class for events specific of any change of focus.
*/
class APPLICATIONKIT_API FocusEvent : public Event {
public:
	FocusEvent( Object* source ): Event(source){}

	FocusEvent( Object* source, const uint32& eventType ): Event(source,eventType){}

	virtual ~FocusEvent(){}

	virtual Object* clone( bool deep=false ) {
		return new FocusEvent(*this);
	}
};





/**
 The Delegate class for a FocusEvent.
 
 handles the following:
 
 	\li FocusGained
 	\li FocusLost
 
*/
typedef Delegate1<FocusEvent*> FocusDelegate; 
typedef FocusDelegate::ProcedureType FocusHandler;

};


#endif // _VCF_FOCUSEVENT_H__

/**
$Id$
*/
