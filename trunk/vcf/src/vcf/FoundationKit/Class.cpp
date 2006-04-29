//Class.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;



Class::Class( const String& className, const String& classID, const String& superClass )
{
	className_ = className;
	classID_ = classID;
	superClass_ = NULL;
	superClassName_ = superClass;
	propertyContainer_.initContainer( properties_ );
	eventContainer_.initContainer( events_ );
	interfaceContainer_.initContainer( interfaces_ );
	methodContainer_.initContainer(methods_);
	fieldContainer_.initContainer(fields_);

}

Class::~Class()
{
	std::map<String,Property*>::iterator props = properties_.begin();

	while ( props != properties_.end() ){
		Property* prop = props->second;
		delete prop;
		props++;
	}

	properties_.clear();


	std::map<String,Field*>::iterator fields = fields_.begin();

	while ( fields != fields_.end() ){
		Field* field = fields->second;
		delete field;
		fields++;
	}

	fields_.clear();

	std::map<String,EventProperty*>::iterator events = events_.begin();
	while ( events != events_.end() ){
		delete events->second;
		events ++;
	}
	events_.clear();

	std::map<String,Method*>::iterator methods = methods_.begin();
	while ( methods != methods_.end() ){
		Method* method = methods->second;
		delete method;
		method = NULL;
		methods++;
	}
	methods_.clear();

	std::map<String,InterfaceClass*>::iterator interfaces = interfaces_.begin();
	while ( interfaces != interfaces_.end() ){
		InterfaceClass* ic = interfaces->second;
		delete ic;
		ic = NULL;
		interfaces++;
	}
	interfaces_.clear();
}

String Class::getClassName()
{
	return className_;
}

bool Class::hasProperty( const String& propertyName )
{
	bool result = false;
    std::map<String,Property*>::iterator found = properties_.find( propertyName );
	result = (found != properties_.end());
	return result;
}

Property* Class::getProperty( const String& propertyName )
{
	Property* result = NULL;

	std::map<String,Property*>::iterator found = properties_.find( propertyName );
	if ( found != properties_.end() ){
		result = found->second;
	}

	return result;
}

void Class::addEvent( EventProperty* event )
{
	if ( NULL != event ) {
		String delegateName = event->getDelegateName();
		events_[delegateName] = event;
	}
}

EventProperty* Class::getEvent( const String& delegateName )
{
	EventProperty* result = NULL;
	std::map<String,EventProperty*>::iterator found = events_.find( delegateName );
	if ( found != events_.end() ) {
		result = found->second;
	}
	return result;
}

bool Class::hasEventHandler( const String& delegateName )
{
	bool result = false;
	std::map<String,EventProperty*>::iterator found = events_.find( delegateName );
	result = (found != events_.end());
	return result;
}

void Class::addProperty( Property* property )
{
	if ( NULL != property ){

		String name = property->getName();

		properties_[name] = property;
	}
}

void Class::addMethod( Method* method )
{
	if ( NULL != method ){
		String name = method->getName();
		if ( false == hasMethod( name ) ){
			methods_[name] = method;
		}
	}
}

bool Class::hasMethod( const String& methodName ){
	bool result = false;
    std::map<String,Method*>::iterator found = methods_.find( methodName );
	result = (found != methods_.end());
	return result;
}

unsigned long Class::getMethodCount(){
	return methods_.size();
}

Method* Class::getMethod( const String& methodName ){
	Method* result = NULL;

	std::map<String,Method*>::iterator found = methods_.find( methodName );
	if ( found != methods_.end() ){
		result = found->second;
	}

	return result;
}


void Class::addField( Field* field )
{
	if ( NULL != field ){
		String name = field->getName();
		if ( false == hasField( name ) ){
			fields_[name] = field;
		}
	}
}

bool Class::hasField( const String& fieldName ){
	bool result = false;
    std::map<String,Field*>::iterator found = fields_.find( fieldName );
	result = (found != fields_.end());
	return result;
}

unsigned long Class::getFieldCount(){
	return fields_.size();
}

Field* Class::getField( const String& fieldName ){
	Field* result = NULL;

	std::map<String,Field*>::iterator found = fields_.find( fieldName );
	if ( found != fields_.end() ){
		result = found->second;
	}

	return result;
}



void Class::setSource( Object* source )
{
	std::map<String,Property*>::iterator props = properties_.begin();
	while ( props != properties_.end() ){
		props->second->setSource( source );
		props++;
	}

	std::map<String,Field*>::iterator fields = fields_.begin();
	while ( fields != fields_.end() ){
		fields->second->setSource( source );
		fields++;
	}

	std::map<String,Method*>::iterator methods = methods_.begin();
	while ( methods != methods_.end() ){
		Method* method = methods->second;
		method->setSource( source );
		methods++;
	}

	std::map<String,InterfaceClass*>::iterator interfaces = interfaces_.begin();
	while ( interfaces != interfaces_.end() ){
		InterfaceClass* interfaceClass = interfaces->second;
		interfaceClass->setSource( source );
		interfaces++;
	}
}

unsigned long Class::getPropertyCount()
{
	return properties_.size();
}

String Class::getID()
{
	return classID_;
}

Class* Class::getSuperClass()
{
	if ( NULL == superClass_ ){

		superClass_ = ClassRegistry::getClass( superClassName_ );

	}
	return superClass_;
}

String Class::getClassNameForProperty( Property* property )
{
	String result = "";

	if ( NULL != property ){
		VariantData* val = property->get();
		if ( NULL != val ){
			switch ( val->type ){
				case pdInt: {
					result = CLASS_INTEGER;
				}
				break;

				case pdUInt: {
					result = CLASS_UINT;
				}
				break;

				case pdLong: {
					result = CLASS_LONG;
				}
				break;

				case pdShort: {
					result = CLASS_SHORT;
				}
				break;

				case pdUShort: {
					result = CLASS_USHORT;
				}
				break;

				case pdULong: {
					result = CLASS_ULONG;
				}
				break;

				case pdFloat: {
					result = CLASS_FLOAT;
				}
				break;

				case pdChar: {
					result = CLASS_CHAR;
				}
				break;

				case pdDouble: {
					result = CLASS_DOUBLE;
				}
				break;

				case pdObject: {
					result = property->getTypeClassName();
				}
				break;

				case pdBool: {
					result = CLASS_BOOL;
				}
				break;

				case pdString: {
					result = CLASS_STRING;
				}
				break;

				case pdEnum: {
					result = CLASS_ENUM;
				}
				break;

				case pdUndefined: {
					//no-op
				}
				break;

				case pdInterface: {
					//no-op
				}
				break;

                default: {
                    //no-op
                }
                break;
			}
		}
	}

	return result;
}

unsigned long Class::getInterfaceCount()
{
	return interfaces_.size();
}

bool Class::hasInterface( const String& interfaceName )
{
	bool result = false;
	std::map<String, InterfaceClass*>::iterator it = interfaces_.begin();
	while ( (false == result) && (it != interfaces_.end()) )  {
		InterfaceClass* ic = it->second;
		if ( interfaceName == ic->getInterfaceName() ) {
			result = true;
		}
		it ++;
	}

	return result;
}

bool Class::hasInterfaceID( const String& interfaceID )
{
	std::map<String, InterfaceClass*>::iterator found = interfaces_.find( interfaceID );
	return found != interfaces_.end();
}

InterfaceClass* Class::getInterfaceByName( const String& interfaceName )
{
	InterfaceClass* result = NULL;

	std::map<String, InterfaceClass*>::iterator it = interfaces_.begin();
	while ( (NULL == result) && (it != interfaces_.end()) )  {
		InterfaceClass* ic = it->second;
		if ( interfaceName == ic->getInterfaceName() ) {
			result = ic;
		}
		it ++;
	}

	return result;
}

InterfaceClass* Class::getInterfaceByID( const String& interfaceID )
{
	InterfaceClass* result = NULL;

	std::map<String, InterfaceClass*>::iterator found = interfaces_.find( interfaceID );
	if ( found != interfaces_.end() ) {
		result = found->second;
	}

	return result;
}

void Class::addInterface( InterfaceClass* newInterface )
{
	interfaces_[ newInterface->getID() ] = newInterface;
	//copy over method from existing interface in classregistry
	//if any exist

	ClassRegistry::getInterfaceFromInterfaceID( newInterface->getID() );

	InterfaceClass* existingInterface = ClassRegistry::getInterfaceFromInterfaceID( newInterface->getID() );
	if ( NULL != existingInterface ) {
		Enumerator<Method*>* methods = existingInterface->getMethods();
		while ( true == methods->hasMoreElements() ) {
			Method* method = methods->nextElement();

			if ( false == newInterface->hasMethod( method->getName() ) ) {
				newInterface->addMethod( (Method*)method->clone() );
			}
		}
	}
}


/**
$Id$
*/
