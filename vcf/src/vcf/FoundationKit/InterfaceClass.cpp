//InterfaceClass.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//InterfaceClass.h
#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


InterfaceClass::InterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName )
{
	interfaceName_ = interfaceName;
	interfaceID_ = interfaceID;

	superInterfaceClassName_ = superInterfaceName;

	methodContainer_.initContainer( methods_ );
}

InterfaceClass::~InterfaceClass()
{
	std::map<String,Method*>::iterator it = methods_.begin();
	while ( it != methods_.end() ) {
		Method* m = it->second;
		delete m;
		m = NULL;
		it ++;
	}
	methods_.clear();
}

void InterfaceClass::addMethod( Method* method )
{
	methods_[ method->getName() ] = method;
}

bool InterfaceClass::hasMethod( const String& methodName )
{
	std::map<String,Method*>::iterator found = methods_.find( methodName );
	return found != methods_.end();
}

unsigned long InterfaceClass::getMethodCount()
{
	return methods_.size();
}

Method* InterfaceClass::getMethod( const String& methodName )
{
	Method* result = NULL;
	std::map<String,Method*>::iterator found = methods_.find( methodName );
	if ( found != methods_.end() ) {
		result = found->second;
	}
	return result;
}

bool InterfaceClass::isEqual( Object* object ) const
{
	return compareObject( object );
}

void InterfaceClass::setSource( Object* source )
{
	std::map<String,Method*>::iterator it = methods_.begin();
	while ( it != methods_.end() ) {
		Method* m = it->second;
		m->setSource( source );
		it ++;
	}
}

InterfaceClass* InterfaceClass::getSuperInterfaceClass()
{
	InterfaceClass* result = NULL;

	return result;
}


/**
*ImplementedInterfaceClass
*/

ImplementedInterfaceClass::ImplementedInterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName ):
	InterfaceClass( interfaceName, interfaceID, superInterfaceName )
{

}

ImplementedInterfaceClass::~ImplementedInterfaceClass()
{

}


/**
$Id$
*/
