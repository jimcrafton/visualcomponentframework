#ifndef _VCF_HELPEVENT_H__
#define _VCF_HELPEVENT_H__
//HelpEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

#define HELP_EVENT_TYPE		CUSTOM_EVENT_TYPES + 900


/**
\class HelpEvent HelpEvent.h "vcf/ApplicationKit/HelpEvent.h"
*/
class APPLICATIONKIT_API HelpEvent : public Event {
public:
	HelpEvent( Object* source ): Event(source,HELP_EVENT_TYPE){}

	virtual ~HelpEvent() {}

	virtual Object* clone( bool deep=false ) {
		return new HelpEvent(*this);
	}

	String helpSection;
	String helpBook;
	String helpDirectory;

};


/**
*/
typedef Delegate1<HelpEvent*> HelpDelegate; 
typedef HelpDelegate::ProcedureType HelpHandler;


}; //end of namespace VCF


#endif // _VCF_HELPEVENT_H__

/**
$Id$
*/
