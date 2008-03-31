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

	std::map<String,DelegateProperty*>::iterator events = delegates_.begin();
	while ( events != delegates_.end() ){
		delete events->second;
		events ++;
	}
	delegates_.clear();

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

String Class::getClassName() const 
{
	return className_;
}

bool Class::hasProperty( const String& propertyName ) const 
{
	bool result = false;
    std::map<String,Property*>::const_iterator found = properties_.find( propertyName );
	result = (found != properties_.end());
	return result;
}

Property* Class::getProperty( const String& propertyName ) const
{
	Property* result = NULL;

	std::map<String,Property*>::const_iterator found = properties_.find( propertyName );
	if ( found != properties_.end() ){
		result = found->second;
	}

	return result;
}

void Class::addDelegate( DelegateProperty* event )
{
	if ( NULL != event ) {
		String delegateName = event->getDelegateName();
		delegates_[delegateName] = event;
	}
}

DelegateProperty* Class::getDelegate( const String& delegateName ) const 
{
	DelegateProperty* result = NULL;
	std::map<String,DelegateProperty*>::const_iterator found = delegates_.find( delegateName );
	if ( found != delegates_.end() ) {
		result = found->second;
	}
	return result;
}

bool Class::hasDelegate( const String& delegateName ) const 
{
	bool result = false;
	std::map<String,DelegateProperty*>::const_iterator found = delegates_.find( delegateName );
	result = (found != delegates_.end());
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

bool Class::hasMethod( const String& methodName ) const 
{
	bool result = false;
    std::map<String,Method*>::const_iterator found = methods_.find( methodName );
	result = (found != methods_.end());
	return result;
}

uint32 Class::getMethodCount() const 
{
	return methods_.size();
}

Method* Class::getMethod( const String& methodName ) const 
{
	Method* result = NULL;

	std::map<String,Method*>::const_iterator found = methods_.find( methodName );
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

bool Class::hasField( const String& fieldName ) const 
{
	bool result = false;
    std::map<String,Field*>::const_iterator found = fields_.find( fieldName );
	result = (found != fields_.end());
	return result;
}

uint32 Class::getFieldCount() const 
{
	return fields_.size();
}

Field* Class::getField( const String& fieldName ) const 
{
	Field* result = NULL;

	std::map<String,Field*>::const_iterator found = fields_.find( fieldName );
	if ( found != fields_.end() ){
		result = found->second;
	}

	return result;
}

void Class::setSource( const Object* source )
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

	std::map<String, DelegateProperty*>::iterator delegates = delegates_.begin();
	while ( delegates != delegates_.end() ){
		DelegateProperty* delegateProp = delegates->second;
		delegateProp->setSource( source );
		delegates++;
	}

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

uint32 Class::getPropertyCount() const 
{
	return properties_.size();
}

String Class::getID() const 
{
	return classID_;
}

Class* Class::getSuperClass() const 
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

uint32 Class::getInterfaceCount() const 
{
	return interfaces_.size();
}

bool Class::hasInterface( const String& interfaceName ) const 
{
	bool result = false;
	std::map<String, InterfaceClass*>::const_iterator it = interfaces_.begin();
	while ( (false == result) && (it != interfaces_.end()) )  {
		InterfaceClass* ic = it->second;
		if ( interfaceName == ic->getInterfaceName() ) {
			result = true;
		}
		it ++;
	}

	return result;
}

bool Class::hasInterfaceID( const String& interfaceID ) const 
{
	std::map<String, InterfaceClass*>::const_iterator found = interfaces_.find( interfaceID );
	return found != interfaces_.end();
}

InterfaceClass* Class::getInterfaceByName( const String& interfaceName ) const 
{
	InterfaceClass* result = NULL;

	std::map<String, InterfaceClass*>::const_iterator it = interfaces_.begin();
	while ( (NULL == result) && (it != interfaces_.end()) )  {
		InterfaceClass* ic = it->second;
		if ( interfaceName == ic->getInterfaceName() ) {
			result = ic;
		}
		it ++;
	}

	return result;
}

InterfaceClass* Class::getInterfaceByID( const String& interfaceID ) const 
{
	InterfaceClass* result = NULL;

	std::map<String, InterfaceClass*>::const_iterator found = interfaces_.find( interfaceID );
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
