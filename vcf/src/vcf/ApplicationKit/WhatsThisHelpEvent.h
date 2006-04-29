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
*WhatsThisHelpEventHandler
*handles the following:
*onControlHelpRequested
*/
template <class SOURCE_TYPE>
class WhatsThisHelpEventHandler : public EventHandlerInstance<SOURCE_TYPE,WhatsThisHelpEvent>  {
public:
	WhatsThisHelpEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,WhatsThisHelpEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,WhatsThisHelpEvent>( source, handlerMethod, handlerName ) {

	}

};

}; //end of namespace VCF


#endif // _VCF_WHATSTHISHELPEVENT_H__

/**
$Id$
*/
