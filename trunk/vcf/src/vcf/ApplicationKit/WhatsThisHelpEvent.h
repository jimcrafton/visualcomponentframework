#ifndef _VCF_WHATSTHISHELPEVENT_H__
#define _VCF_WHATSTHISHELPEVENT_H__
//WhatsThisHelpEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

#define WHAT_THIS_EVENT_TYPE	CUSTOM_EVENT_TYPES + 12


/**
\class WhatsThisHelpEvent WhatsThisHelpEvent.h "vcf/ApplicationKit/WhatsThisHelpEvent.h"  
*/
class WhatsThisHelpEvent : public Event {
public:
	WhatsThisHelpEvent( Object* source ):
	  Event( source, WHAT_THIS_EVENT_TYPE ) {

	}

	WhatsThisHelpEvent( const WhatsThisHelpEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~WhatsThisHelpEvent(){};

	WhatsThisHelpEvent& operator= ( const WhatsThisHelpEvent& rhs ) {
		Event::operator =( rhs );

		helpString = rhs.helpString;

		return *this;
	}


	String helpString;

	
	virtual Object* clone( bool deep=false ) {
		return new WhatsThisHelpEvent(*this);
	}


};





/**
WhatsThisHelpDelegate
handles the following:
\li onControlHelpRequested
*/
typedef Delegate1<WhatsThisHelpEvent*> WhatsThisHelpDelegate; 
typedef WhatsThisHelpDelegate::ProcedureType WhatsThisHelpHandler;

}; //end of namespace VCF


#endif // _VCF_WHATSTHISHELPEVENT_H__

/**
$Id$
*/
