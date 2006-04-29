//EventHandler.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

EventHandler::~EventHandler()
{
	
}
	

void EventHandler::addHandlerToSource( Object* source, const String& handlerName )
{
	ObjectWithEvents* objEventOwner = dynamic_cast<ObjectWithEvents*>(source);

	if ( NULL != objEventOwner ) {
		if ( !handlerName.empty() ) {
			objEventOwner->addEventHandler( handlerName, this );
		}
	}
	else {
		//StringUtils::traceWithArgs( "this event handler does not have a source object (class Name: %s) that can clean up it's memory. \nExpect memory leaks from this!\n",
		//							source->getClassName().c_str() );
	}
}


String EventHandler::getHandlerName()
{
	return getHandlerNameFromSource( getSource() );
}

String EventHandler::getHandlerNameFromSource( Object* source )
{
	String result;

	ObjectWithEvents* objEventOwner = dynamic_cast<ObjectWithEvents*>(source);
	result = objEventOwner->getEventHandlerName( this );

	return result;
}


/**
$Id$
*/
