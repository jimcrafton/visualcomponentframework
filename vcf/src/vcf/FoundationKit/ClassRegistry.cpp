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
	classContainer_.initContainer( classMap_ );

	interfaceContainer_.initContainer( interfaceMap_ );

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

		std::map<String,Class*>::iterator found =
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

		std::map<String,InterfaceClass*>::iterator found =
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

			std::map<String,ImplementedInterfaceClass*>::iterator found2 =
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
	Class* clazz = NULL;
	Object* result = NULL;
	std::map<String,Class*>::iterator found =
		classMap_.find( className );

	if ( found != classMap_.end() ){
		clazz = found->second;
		result = clazz->createInstance();
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
	if  ( classID != "" ) {
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
			Enumerator<EventProperty*>* events = superClass->getEvents();
			if ( NULL != events ){
				while ( events->hasMoreElements() ){
					EventProperty* event = events->nextElement();
					if ( NULL != event ){
						if ( false == classToRegister->hasEventHandler( event->getDelegateName() ) ) {
							classToRegister->addEvent( event->clone() );
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
	return classContainer_.getEnumerator();
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
				Method* inheritedMethod = method->clone();
				interfaceToRegister->addMethod( method );
			}


			tmp = superInterfaceClass;
			superInterfaceClass = tmp->getSuperInterfaceClass();
		}
	}
}

Enumerator<InterfaceClass*>* ClassRegistry::internal_getInterfaces()
{
	return interfaceContainer_.getEnumerator();
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
			int pos = key.find("::");
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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/03/14 19:07:28  marcelloptr
*comments and added an error message to avoid an infinite loop
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/10 04:37:19  ddiego
*added a MIMType class that parses mime types.
*
*Revision 1.4  2004/04/03 17:57:51  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.2  2004/01/21 19:06:43  ddiego
*fix for bug [ 776440 ] ClassReg doesn't call addImplementedInterface
*
*Revision 1.1.2.1  2004/01/11 19:57:55  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.23  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.22.2.6  2003/11/02 02:54:44  ddiego
*made some small changes to the method RTTI registration code.
*
*Revision 1.22.2.5  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.22.2.4  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.22.2.3  2003/09/11 03:54:40  ddiego
*fixed a bug in the ClassRegistry when adding a new Class. Previously
*it was not properly copying methods from super class. This is now fixed
*Made the EventProperty class exported
*
*Revision 1.22.2.2  2003/09/10 04:23:42  ddiego
*minor cahnge to class registry to allow you to remove registered classes
*
*Revision 1.22.2.1  2003/08/28 21:46:56  ddiego
*added escape reponse...
*
*Revision 1.22  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.21.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.21  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.20.2.3  2003/04/07 03:39:34  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.20.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.20.2.1  2003/03/12 03:13:00  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.20  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.19.14.1  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.19  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.18.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.18  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


