//ObjectWithEvents.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ObjectWithEvents.h

#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


ObjectWithEvents::ObjectWithEvents()
{

}

ObjectWithEvents::~ObjectWithEvents()
{
	//destroy all the event handlers

	std::map<String,EventHandler*>::iterator it = eventHandlers_.begin();
	while ( it != eventHandlers_.end() ){
		EventHandler* ev = it->second;

		ev->free();
		//delete it->second;

		it++;
	}
	eventHandlers_.clear();
/*
	std::vector<EventHandler::Vector*>::iterator handlerIt = masterHandlerList_.begin();
	while ( handlerIt != masterHandlerList_.end() ) {
		EventHandler::Vector* list = *handlerIt;
		delete list;
		list = NULL;
		handlerIt ++;
	}
	masterHandlerList_.clear();
	*/

}

void ObjectWithEvents::addEventHandler( const String& handlerName, EventHandler* handler )
{
	eventHandlers_[handlerName] = handler;
}

EventHandler* ObjectWithEvents::getEventHandler( const String& handlerName )
{
	EventHandler* result = NULL;

	std::map<String,EventHandler*>::iterator found = eventHandlers_.find( handlerName );
	if ( found != eventHandlers_.end() ){
		result = found->second;
	}
	return result;
}

String ObjectWithEvents::getEventHandlerName( EventHandler* handler )
{
	String result;

	std::map<String,EventHandler*>::iterator found = eventHandlers_.begin();
	while ( found != eventHandlers_.end() ){
		if ( found->second == handler ) {
			result = found->first;
			break;
		}
		found ++;
	}

	return result;
}

/*
void ObjectWithEvents::addEventHandlerList( EventHandler::Vector* eventHandlerList )
{
	masterHandlerList_.push_back( eventHandlerList );
}
*/


/**
$Id$
*/
