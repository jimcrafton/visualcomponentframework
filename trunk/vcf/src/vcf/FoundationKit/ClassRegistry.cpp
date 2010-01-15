//ClassRegistry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VCFRTTIImpl.h"

using namespace VCF;


ClassRegistry* ClassRegistry::create()
{
	if ( NULL == ClassRegistry::registryInstance_ ) {
		ClassRegistry::registryInstance_ = new ClassRegistry();
	}

	return ClassRegistry::registryInstance_;
}

void ClassRegistry::terminate()
{
	delete ClassRegistry::registryInstance_;
}

ClassRegistry::ClassRegistry()
{
#ifdef VCF_RTTI
	//register "Object" as default class
	TypedClass<Object>* objClass = TypedClass<Object>::create("VCF::Object", OBJECT_CLASSID, "");

		//new TypedClass<Object>( "VCF::Object", OBJECT_CLASSID, "" );

	classMap_["VCF::Object"] = objClass;
	classIDMap_[OBJECT_CLASSID] = objClass;
#endif

	//objClass->init();
}

ClassRegistry::~ClassRegistry()
{
	std::map<String,Class*>::iterator it = classMap_.begin();
	while ( it != classMap_.end() ){
		Class* clazz = it->second;
		delete clazz;
		it ++;
	}

	std::map<String,InterfaceClass*>::iterator it2 = interfaceMap_.begin();
	while ( it2 != interfaceMap_.end() ){
		delete it2->second;
		it2 ++;
	}

	classMap_.clear();

	classIDMap_.clear();

	interfaceMap_.clear();

	interfaceIDMap_.clear();

	implementedInterfacesIDMap_.clear();
}

void ClassRegistry::removeClass( const String& className )
{
	#ifndef VCF_RTTI
	return ;
	#endif

	if ( !className.empty() ) {
		String id ;

		Map<String,Class*>::iterator found =
			registryInstance_->classMap_.find( className );

		if ( found != registryInstance_->classMap_.end() ){
			Class* clazz = found->second;
			id = clazz->getID();
			delete clazz;
			registryInstance_->classMap_.erase( found );

			found = registryInstance_->classIDMap_.find( id );
			if ( found != registryInstance_->classIDMap_.end() ) {
				registryInstance_->classIDMap_.erase( found );
			}
		}
	}

}

void ClassRegistry::removeClassByID( const String& classID )
{
	#ifndef VCF_RTTI
	return ;
	#endif

	if ( !classID.empty() ) {
		String name ;

		std::map<String,Class*>::iterator found =
			registryInstance_->classIDMap_.find( classID );

		if ( found != registryInstance_->classIDMap_.end() ){
			Class* clazz = found->second;
			name = clazz->getClassName();
			delete clazz;
			registryInstance_->classIDMap_.erase( found );

			found = registryInstance_->classMap_.find( name );
			if ( found != registryInstance_->classMap_.end() ) {
				registryInstance_->classMap_.erase( found );
			}
		}
	}
}

void ClassRegistry::removeInterface( const String& interfaceName )
{
	#ifndef VCF_RTTI
	return ;
	#endif

	if ( !interfaceName.empty() ) {
		String id ;

		Map<String,InterfaceClass*>::iterator found =
			registryInstance_->interfaceMap_.find( interfaceName );

		if ( found != registryInstance_->interfaceMap_.end() ){
			InterfaceClass* clazz = found->second;
			id = clazz->getID();
			delete clazz;
			registryInstance_->interfaceMap_.erase( found );

			found = registryInstance_->interfaceIDMap_.find( id );
			if ( found != registryInstance_->interfaceIDMap_.end() ) {
				registryInstance_->interfaceIDMap_.erase( found );
			}

			Map<String,ImplementedInterfaceClass*>::iterator found2 =
				registryInstance_->implementedInterfacesIDMap_.find( id );

			if ( found2 != registryInstance_->implementedInterfacesIDMap_.end() ) {
				registryInstance_->implementedInterfacesIDMap_.erase( found2 );
			}
		}
	}
}

void ClassRegistry::removeInterfaceByID( const String& interfaceID )
{
	#ifndef VCF_RTTI
	return ;
	#endif

	if ( !interfaceID.empty() ) {
		String name ;

		std::map<String,InterfaceClass*>::iterator found =
			registryInstance_->interfaceIDMap_.find( interfaceID );

		if ( found != registryInstance_->interfaceIDMap_.end() ){
			InterfaceClass* clazz = found->second;
			name = clazz->getInterfaceName();
			delete clazz;
			registryInstance_->interfaceIDMap_.erase( found );

			found = registryInstance_->interfaceMap_.find( name );
			if ( found != registryInstance_->interfaceMap_.end() ) {
				registryInstance_->interfaceMap_.erase( found );
			}

			std::map<String,ImplementedInterfaceClass*>::iterator found2 =
				registryInstance_->implementedInterfacesIDMap_.find( interfaceID );

			if ( found2 != registryInstance_->implementedInterfacesIDMap_.end() ) {
				registryInstance_->implementedInterfacesIDMap_.erase( found2 );
			}
		}
	}
}

Class* ClassRegistry::getClass( const String& className )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getClass( className );
}

Class* ClassRegistry::getClassFromClassID( const String& classID )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getClassFromClassID( classID );
}

Class* ClassRegistry::getClass( const Object* object )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getClass( object );
}

Class* ClassRegistry::getClass( Object* object ) 
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getClass( object );
}

Object* ClassRegistry::createNewInstance( const String& className )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_createNewInstance( className );
}

Object* ClassRegistry::createNewInstanceFromClassID( const String& classID )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_createNewInstanceFromClassID( classID );
}

void* ClassRegistry::createNewInterfaceInstanceFromInterfaceName( const String& interfaceName, const String& implementerClassName )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_createNewInterfaceInstanceFromInterfaceName( interfaceName, implementerClassName );
}

void* ClassRegistry::createNewInterfaceInstanceFromInterfaceID( const String& interfaceID, const String& implementerClassID )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_createNewInterfaceInstanceFromInterfaceID( interfaceID, implementerClassID );
}

void ClassRegistry::addClass( const String& className, Class* classToRegister )
{
#ifndef VCF_RTTI
	return ;
#endif
	ClassRegistry::getClassRegistry()->internal_addClass( className, classToRegister );
}

void ClassRegistry::addInterface( const String& interfaceName, InterfaceClass* interfaceToRegister )
{
#ifndef VCF_RTTI
	return ;
#endif
	ClassRegistry::getClassRegistry()->internal_addInterface( interfaceName, interfaceToRegister );
}

Enumerator<Class*>* ClassRegistry::getClasses()
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getClasses();
}

Enumerator<InterfaceClass*>* ClassRegistry::getInterfaces()
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getInterfaces();
}

ImplementedInterfaceClass* ClassRegistry::getImplementedInterface( const String& implementingClassName, const String& interfaceID )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getImplementedInterface( implementingClassName, interfaceID );
}

InterfaceClass* ClassRegistry::getInterface( const String& interfaceName )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getInterface( interfaceName );
}

InterfaceClass* ClassRegistry::getInterfaceFromInterfaceID( const String& interfaceID )
{
#ifndef VCF_RTTI
	return NULL;
#endif
	return ClassRegistry::getClassRegistry()->internal_getInterfaceFromInterfaceID( interfaceID );
}

void ClassRegistry::addImplementedInterface( ImplementedInterfaceClass* interfaceToRegister, const String& implementerClassID )
{
#ifndef VCF_RTTI
	return;
#endif
	ClassRegistry::getClassRegistry()->internal_addImplementedInterface( interfaceToRegister,implementerClassID );
}

bool ClassRegistry::registerMethod( Method* method, const String& className, const bool& isInterfaceMethod )
{
#ifndef VCF_RTTI
	return false;
#endif
	return ClassRegistry::getClassRegistry()->internal_registerMethod( method, className, isInterfaceMethod );
}

bool ClassRegistry::registerMethodByUUID( Method* method, const String& UUID, const bool& isInterfaceMethod )
{
 #ifndef VCF_RTTI
	return false;
#endif
	return ClassRegistry::getClassRegistry()->internal_registerMethodByUUID( method, UUID, isInterfaceMethod );
}

void ClassRegistry::dump()
{
#ifndef VCF_RTTI
	return;
#endif
	ClassRegistry::getClassRegistry()->internal_dump();
}











ClassRegistry* ClassRegistry::getClassRegistry()
{
	return ClassRegistry::registryInstance_;
}

Class* ClassRegistry::internal_getClass( const String& className )
{
	Class* result = NULL;

	if ( !className.empty() ) {
		std::map<String,Class*>::iterator found =
			classMap_.find( className );

		if ( found != classMap_.end() ){
			result = found->second;
		}
	}

	return result;
}


Class* ClassRegistry::internal_getClassFromClassID( const String& classID )
{
	Class* result = NULL;

	if ( !classID.empty() ) {
		std::map<String,Class*>::iterator found =
			classIDMap_.find( classID );

		if ( found != classIDMap_.end() ){
			result = found->second;
		}
	}

	return result;
}


Class* ClassRegistry::internal_getClass( const Object* object ) 
{
	Class* result = NULL;
	std::map<String,Class*>::iterator found =
		classMap_.begin();

	Class* clazz = NULL;
	while ( found != classMap_.end() ){
		clazz = found->second;
		if ( clazz->isEqual( object ) ){
			result = clazz;
			break;
		}
		found++;
	}

	return result;
}

Class* ClassRegistry::internal_getClass( Object* object )
{
	Class* result = NULL;
	std::map<String,Class*>::iterator found =
		classMap_.begin();

	Class* clazz = NULL;
	while ( found != classMap_.end() ){
		clazz = found->second;
		if ( clazz->isEqual( object ) ){
			result = clazz;
			break;
		}
		found++;
	}

	return result;
}

Object* ClassRegistry::internal_createNewInstance( const String& className )
{
	Object* result = NULL;
	if ( !className.empty() ) {		
		Class* clazz = NULL;
		std::map<String,Class*>::iterator found =
			classMap_.find( className );
		
		if ( found != classMap_.end() ){
			clazz = found->second;
			result = clazz->createInstance();
		}
	}
	if ( NULL == result ) {
		throw CantCreateObjectException( "Unable to create an instance of class\"" + className + "\"" );
	}

	return result;
}

Object* ClassRegistry::internal_createNewInstanceFromClassID( const String& classID )
{
	Class* clazz = NULL;
	Object* result = NULL;
	std::map<String,Class*>::iterator found =
		classIDMap_.find( classID );

	if ( found != classIDMap_.end() ){
		clazz = found->second;
		result = clazz->createInstance();
	}
	if ( NULL == result ) {
		throw CantCreateObjectException( "Unable to create an instance of class\"" + classID + "\"" );
	}

	return result;
}

void ClassRegistry::internal_addClass( const String& className, Class* classToRegister )
{
	if ( NULL == classToRegister )
		return; //throw exception ?

	ClassRegistry* classRegistry = ClassRegistry::getClassRegistry();

	String classID = classToRegister->getID();

	std::map<String,Class*>::iterator found;
	bool classNotFound = true;
	if  ( !classID.empty() ) {
		found = classRegistry->classIDMap_.find( classID );
		classNotFound = !( found != classIDMap_.end() );
	}
	else  {
		found = classRegistry->classMap_.find( className );
		classNotFound = !( found != classMap_.end() );
	}

	if ( true == classNotFound ){
		classRegistry->classMap_[className] = classToRegister;

		if  ( classID != "" ) {
			classRegistry->classIDMap_[classID] = classToRegister;
		}

		Class* superClass = classToRegister->getSuperClass();
		Class* tmp = NULL;		

		while ( NULL != superClass ){
			//copy over properties
			Enumerator<Property*>* props = superClass->getProperties();
			if ( NULL != props ){
				while ( props->hasMoreElements() ){
					Property* prop = props->nextElement();
					if ( NULL != prop ){
						if ( false == classToRegister->hasProperty( prop->getName() ) ) {

							classToRegister->addProperty( prop->clone() );
						}
					}
				}
			}

			Enumerator<Field*>* fields = superClass->getFields();
			if ( NULL != fields ){
				while ( fields->hasMoreElements() ){
					Field* field = fields->nextElement();
					if ( NULL != field ){
						if ( false == classToRegister->hasField( field->getName() ) ) {

							classToRegister->addField( field->clone() );
						}
					}
				}
			}

			Enumerator<Method*>* methods = superClass->getMethods();
			if ( NULL != methods ){
				while ( methods->hasMoreElements() ){
					Method* method = methods->nextElement();
					if ( NULL != method ){
						if ( false == classToRegister->hasMethod( method->getName() ) ) {
							Method* newMethod = method->clone();

							classToRegister->addMethod( newMethod );
						}
					}
				}
			}

			//copy over events
			Enumerator<DelegateProperty*>* delegates = superClass->getDelegates();
			if ( NULL != delegates ){
				while ( delegates->hasMoreElements() ){
					DelegateProperty* delegate = delegates->nextElement();
					if ( NULL != delegate ){
						if ( false == classToRegister->hasDelegate( delegate->getDelegateName() ) ) {
							classToRegister->addDelegate( delegate->clone() );
						}
					}
				}
			}
			tmp = superClass;
			superClass = tmp->getSuperClass();

			if ( superClass == tmp ) {
				throw BasicException( MAKE_ERROR_MSG_2( "Error: the class '" + className + "' has been registered with a superclass name that is the same of its own class name." ) );
			}
		}
	}
}

Enumerator<Class*>* ClassRegistry::internal_getClasses()
{
	return classMap_.getEnumerator();
}

void ClassRegistry::internal_dump()
{
	/*
	std::map<String,Class*>::iterator it = classMap_.begin();

	while ( it != classMap_.end() ){
		std::cout << typeid(*(it->second)).name() << std::endl;
		it++;
	}
	*/
}

ImplementedInterfaceClass* ClassRegistry::internal_getImplementedInterface( const String& implementingClassName, const String& interfaceID )
{
	ImplementedInterfaceClass* result = NULL;
	Class* clazz = this->getClass( implementingClassName );
	if ( NULL != clazz ) {
		result = (ImplementedInterfaceClass*)clazz->getInterfaceByID( interfaceID );
	}
	return result;
}


void ClassRegistry::internal_addInterface( const String& interfaceName, InterfaceClass* interfaceToRegister )
{
	if ( NULL == interfaceToRegister )
		return; //throw exception ?

	//ClassRegistry* classRegistry = ClassRegistry::getClassRegistry();

	String interfaceID = interfaceToRegister->getID();

	std::map<String,InterfaceClass*>::iterator found;
	bool interfaceNotFound = true;

	if  ( interfaceID != "" ) {
		found = interfaceIDMap_.find( interfaceID );
		interfaceNotFound = !( found != interfaceIDMap_.end() );
	}
	else  {
		found = interfaceMap_.find( interfaceName );
		interfaceNotFound = !( found != interfaceMap_.end() );
	}

	if ( true == interfaceNotFound ){
		interfaceMap_[interfaceName] = interfaceToRegister;

		if  ( interfaceID != "" ) {
			interfaceIDMap_[interfaceID] = interfaceToRegister;
		}

		InterfaceClass* superInterfaceClass = interfaceToRegister->getSuperInterfaceClass();
		InterfaceClass* tmp = NULL;
		while ( NULL != superInterfaceClass ){
			//copy over the methods
			Enumerator<Method*>* methods = superInterfaceClass->getMethods();
			while ( true == methods->hasMoreElements() ) {
				Method* method = methods->nextElement();
				//Method* inheritedMethod = method->clone();  //not used....
				interfaceToRegister->addMethod( method );
			}


			tmp = superInterfaceClass;
			superInterfaceClass = tmp->getSuperInterfaceClass();
		}
	}
}

Enumerator<InterfaceClass*>* ClassRegistry::internal_getInterfaces()
{
	return interfaceMap_.getEnumerator();
}

InterfaceClass* ClassRegistry::internal_getInterface( const String& interfaceName )
{
	InterfaceClass* result = NULL;

	std::map<String,InterfaceClass*>::iterator found =
		interfaceMap_.find( interfaceName );

	if ( found != interfaceMap_.end() ){
		result = found->second;
	}

	return result;
}

InterfaceClass* ClassRegistry::internal_getInterfaceFromInterfaceID( const String& interfaceID )
{
	InterfaceClass* result = NULL;

	std::map<String,InterfaceClass*>::iterator found =
		interfaceIDMap_.find( interfaceID );

	if ( found != interfaceIDMap_.end() ){
		result = found->second;
	}

	return result;
}

bool ClassRegistry::internal_registerMethod( Method* method, const String& className, const bool& isInterfaceMethod )
{
	bool result = false;

	if ( true == isInterfaceMethod ) {
		InterfaceClass* interfaceClass = this->getInterface( className );
		if ( NULL != interfaceClass ) {
			if ( false == interfaceClass->hasMethod( method->getName() ) ){
				interfaceClass->addMethod( method );
				result = true;
			}
		}
	}
	else {
		Class* clazz = this->getClass( className );
		if ( NULL != clazz ) {
			if ( false == clazz->hasMethod( method->getName() ) ){
				clazz->addMethod( method );
				result = true;
			}
		}
	}
	return result;
}

bool ClassRegistry::internal_registerMethodByUUID( Method* method, const String& UUID, const bool& isInterfaceMethod )
{
	bool result = false;

	if ( true == isInterfaceMethod ) {
		InterfaceClass* interfaceClass = this->getInterfaceFromInterfaceID( UUID );
		if ( NULL != interfaceClass ) {
			if ( false == interfaceClass->hasMethod( method->getName() ) ){
				interfaceClass->addMethod( method );
				result = true;
			}
		}
	}
	else {
		Class* clazz = this->getClassFromClassID( UUID );
		if ( NULL != clazz ) {
			if ( false == clazz->hasMethod( method->getName() ) ){
				clazz->addMethod( method );
				result = true;
			}
		}
	}

	return result;
}


void* ClassRegistry::internal_createNewInterfaceInstanceFromInterfaceName( const String& interfaceName, const String& implementerClassName )
{


	std::map<String,ImplementedInterfaceClass*>::iterator it = implementedInterfacesIDMap_.begin();

	ImplementedInterfaceClass* foundInterface = NULL;

	while ( (it != implementedInterfacesIDMap_.end()) && (NULL == foundInterface) ) {
		ImplementedInterfaceClass* implInterface = it->second;
		if ( implInterface->getInterfaceName() == interfaceName ) {
			String key = it->first;
			size_t pos = key.find("::");
			if ( pos != String::npos ) {

				std::map<String,Class*>::iterator found = classIDMap_.find( key.substr(pos+2, key.size()-(pos+2)) );
				if ( found != classIDMap_.end() ) {
					if ( found->second->getClassName() == implementerClassName ) {
						foundInterface = implInterface;
					}
				}
			}
		}
		it++;
	}

	void* result = NULL;

	if ( NULL != foundInterface ) {
		result = foundInterface->createInterfaceInstance();
	}

	if ( NULL == result ) {
		throw CantCreateObjectException( "Unable to create an instance of interface\"" + interfaceName + "\"" );
	}
	return result;
}

void* ClassRegistry::internal_createNewInterfaceInstanceFromInterfaceID( const String& interfaceID, const String& implementerClassID )
{
	String key = interfaceID + "::" + implementerClassID;
	std::map<String,ImplementedInterfaceClass*>::iterator found = implementedInterfacesIDMap_.find( interfaceID );

	void* result = NULL;

	if ( found != implementedInterfacesIDMap_.end() ) {
		ImplementedInterfaceClass* implInterface = found->second;
		result = implInterface->createInterfaceInstance();
	}

	if ( NULL == result ) {
		throw CantCreateObjectException( "Unable to create an instance of interface\"" + interfaceID + "\"" );
	}

	return result;
}

void ClassRegistry::internal_addImplementedInterface( ImplementedInterfaceClass* interfaceToRegister, const String& implementerClassID )
{
	String key = interfaceToRegister->getID() + "::" + implementerClassID;
	implementedInterfacesIDMap_[key] = interfaceToRegister;
}

void ClassRegistry::removeClass( Class* clazz )
{
	ClassRegistry* reg = ClassRegistry::getClassRegistry();
	String classID = clazz->getID();
	String className = clazz->getClassName();

	std::map<String,Class*>::iterator found;
	found = reg->classIDMap_.find( classID );
	if ( found != reg->classIDMap_.end() ) {
		reg->classIDMap_.erase( found );
	}

	found = reg->classMap_.find( className );
	if ( found != reg->classMap_.end() ) {
		reg->classMap_.erase( found );
	}
}

void ClassRegistry::removeInterface( InterfaceClass* interfaceClass )
{
	ClassRegistry* reg = ClassRegistry::getClassRegistry();
	std::map<String,InterfaceClass*>::iterator found;
	String interfaceID = interfaceClass->getID();
	String interfaceName = interfaceClass->getInterfaceName();

	found = reg->interfaceIDMap_.find( interfaceID );
	if ( found != reg->interfaceIDMap_.end() ) {
		reg->interfaceIDMap_.erase( found );
	}

	found = reg->interfaceMap_.find( interfaceName );
	if ( found != reg->interfaceMap_.end() ) {
		reg->interfaceMap_.erase( found );
	}
}

std::vector<Class*> ClassRegistry::getClassesWithAttribute( const String& attr )
{
	std::vector<String> attrs(1);
	attrs[0] = attr;
	return ClassRegistry::getClassesWithAttributes( attrs );
}

std::vector<Class*> ClassRegistry::getClassesWithAttributes( const std::vector<String>& attrs )
{
	std::vector<Class*> result;

#ifdef VCF_RTTI
	ClassRegistry* reg = ClassRegistry::getClassRegistry();


	std::vector<String>::const_iterator attrIt;

	std::map<String,Class*>::iterator it = reg->classMap_.begin();
	while ( it != reg->classMap_.end() ) {
		Class* clazz = it->second;

		for ( attrIt = attrs.begin();attrIt!=attrs.end();attrIt++ ) {
			if ( clazz->hasAttribute(*attrIt) ) {
				result.push_back( clazz );
				break;
			}
		}

		++it;
	}
#endif

	return result;
}

std::vector<Class*> ClassRegistry::getClassesWithAttribute( const String& className, const String& attr )
{
	std::vector<String> attrs(1);
	attrs[0] = attr;
	return ClassRegistry::getClassesWithAttributes( className, attrs );
}

std::vector<Class*> ClassRegistry::getClassesWithAttributes( const String& className, const std::vector<String>& attrs )
{
	std::vector<Class*> result;
#ifdef VCF_RTTI
	ClassRegistry* reg = ClassRegistry::getClassRegistry();


	std::vector<String>::const_iterator attrIt;

	std::map<String,Class*>::iterator it = reg->classMap_.begin();
	while ( it != reg->classMap_.end() ) {
		Class* clazz = it->second;

		for ( attrIt = attrs.begin();attrIt!=attrs.end();attrIt++ ) {
			if ( clazz->hasAttribute(*attrIt) && clazz->relatedTo( className ) ) {
				result.push_back( clazz );
				break;
			}
		}

		++it;
	}
#endif
	return result;
}

std::vector<VariantData> ClassRegistry::getAttrValuesByClass( const String& className, const String& attr )
{
	std::vector<VariantData> result;
#ifdef VCF_RTTI
	ClassRegistry* reg = ClassRegistry::getClassRegistry();
	std::vector<Class*> classes;
	std::map<String,Class*>::iterator it = reg->classMap_.begin();
	while ( it != reg->classMap_.end() ) {
		Class* clazz = it->second;
		if ( clazz->hasAttribute(attr) ) {
			classes.push_back( clazz );
		}		

		++it;
	}


	std::vector<Class*>::iterator it2 = classes.begin();
	while ( it2 != classes.end() ) {
		Class* clazz = *it2;

		if ( clazz->relatedTo( className ) ) {
			VariantData val = clazz->getAttribute( attr );
			std::vector<VariantData>::iterator found = std::find( result.begin(), result.end(), val );

			if ( found == result.end() ) {
				result.push_back( val );
			}
		}

		++it2;
	}

	

#endif
	return result;
}


Class* ClassRegistry::getClassWithAttrValue( const String& attr, const VariantData& value )
{
	Class* result = NULL;
#ifdef VCF_RTTI
	ClassRegistry* reg = ClassRegistry::getClassRegistry();
	
	std::map<String,Class*>::iterator it = reg->classMap_.begin();
	while ( it != reg->classMap_.end() ) {
		Class* clazz = it->second;
		if ( clazz->hasAttribute(attr) ) {
			if ( clazz->getAttribute( attr ) == value ) {
				result = clazz;
				break;
			}
		}		

		++it;
	}
#endif

	return result;
}

Class* ClassRegistry::getClassWithAttrValue( const String& className, const String& attr, const VariantData& value )
{
	Class* result = NULL;
#ifdef VCF_RTTI
	ClassRegistry* reg = ClassRegistry::getClassRegistry();
	
	std::map<String,Class*>::iterator it = reg->classMap_.begin();
	while ( it != reg->classMap_.end() ) {
		Class* clazz = it->second;
		if ( clazz->relatedTo( className ) ) {
			if ( clazz->hasAttribute(attr) ) {
				if ( clazz->getAttribute( attr ) == value ) {
					result = clazz;
					break;
				}
			}
		}

		++it;
	}
#endif

	return result;
}

/**
$Id$
*/
