#ifndef _VCF_CLASSREGISTRY_H__
#define _VCF_CLASSREGISTRY_H__
//ClassRegistry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

/**

This macro is used in a way similar to the C++ typeid operator.
Where typeid() returns a const type_info reference, the classid()
"operator" returns a Class pointer or NULL if no class can be found
in the ClassRegistry. For example:
\code
Class* clazz = classid(Window);
\endcode
The clazz variable will now point to a Class instance associated with
the Window class.

*/
#define classid(classType) \
	VCF::ClassRegistry::getClass( #classType )\
	\


namespace VCF
{


/**
\class ClassRegistry ClassRegistry.h "vcf/FoundationKit/ClassRegistry.h"
*ClassRegistry contains all Class's in the Framework Runtime.
*The ClassRegistry is used by the Framework Runtime to register Classes
*and properties for Classes. The ClassRegistry is also used to dynamically
*create new instances of a class from a class name.
*
*@author Jim Crafton
*@version 1.0
*/
class FOUNDATIONKIT_API ClassRegistry {
public:
	static ClassRegistry* create();

	static void terminate();

	ClassRegistry();

	virtual ~ClassRegistry();

	/**
	*returns a Class object from a string. If no matching
	*Class exists the function returns NULL.
	*In terms of efficiency, this function is faster than
	*getClass( Object*)
	*@param String the name of the class to find
	*@return Class the class associated with the className
	*/
	static Class* getClass( const String& className );

	/**
	*returns a Class object from a string representing a ClassID/UUID.
	*If no matching Class exists the function returns NULL.
	*In terms of efficiency, this function is faster than
	*getClass( Object*)
	*@param String the UUID or ClassID of the class to find
	*@return Class the class associated with the ClassID
	*/
	static Class* getClassFromClassID( const String& classID );

	/**
	*returns a Class object for the object passed in.
	*@param Object the object instance to get a class for
	*@return Class the class associated with the object
	*/
	static Class* getClass( const Object* object ) ;

	static Class* getClass( Object* object ) ;

	/**
	*creates a new instance of an object based on the class name.
	*@param String the class name of the object to create
	*@param Object a pointer to the newly created object
	*/
	static Object* createNewInstance( const String& className ) ;

	/**
	*creates a new instance of an object based on the classID.
	*@param String the classID of the object to create
	*@param Object a pointer to the newly created object
	*/
	static Object* createNewInstanceFromClassID( const String& classID ) ;

	/**
	*see ImplementedInterfaceClass::createInterfaceInstance()
	*/
	static void* createNewInterfaceInstanceFromInterfaceName( const String& interfaceName, const String& implementerClassName );

	/**
	*see ImplementedInterfaceClass::createInterfaceInstance()
	*/
	static void* createNewInterfaceInstanceFromInterfaceID( const String& interfaceID, const String& implementerClassID );

	/**
	*adds a new Class object to the ClassRegistry
	*@param String the name of the class
	*@param Class the Class object to register
	*/
	static void addClass( const String& className, Class* classToRegister );

	static void removeClass( const String& className );
	static void removeClassByID( const String& classID );

	/**
	*adds a new InterfaceClass object to the ClassRegistry that represents
	*a particular interface
	*@param String the name of the interface
	*@param InterfaceClass the InterfaceClass object to register
	*/
	static void addInterface( const String& interfaceName, InterfaceClass* interfaceToRegister );
	static void removeInterface( const String& interfaceName );
	static void removeInterfaceByID( const String& interfaceID );

	/**
	*returns an enumeration of all the classes in the system at the time
	*of the call
	*/
	static Enumerator<Class*>* getClasses() ;

	static Enumerator<InterfaceClass*>* getInterfaces() ;

	/**
	*returns a ImplementedInterfaceClass object from a string. If no matching
	*ImplementedInterfaceClass exists the function returns NULL.
	*@param String the name of the implementing class to find
	*@paramString the interface UUID to find
	*@return ImplementedInterfaceClass the implemented interface associated with the implementingClassName
	*/
	static ImplementedInterfaceClass* getImplementedInterface( const String& implementingClassName, const String& interfaceID );

	/**
	*returns a InterfaceClass object from a string. If no matching
	*InterfaceClass exists the function returns NULL.
	*@param String the name of the interface to find
	*@return InterfaceClass the interface associated with the interfaceName
	*/
	static InterfaceClass* getInterface( const String& interfaceName ) ;

	/**
	*returns a InterfaceClass object from a string ID. If no matching
	*InterfaceClass exists the function returns NULL.
	*@param String the UUID of the interface to find
	*@return InterfaceClass the interface associated with the interfaceName
	*/
	static InterfaceClass* getInterfaceFromInterfaceID( const String& interfaceID );

	/**
	*Adds an implemented interface class to the registry
	*/
	static void addImplementedInterface( ImplementedInterfaceClass* interfaceToRegister, const String& implementerClassID );

	/**
	*attempts to register the method with the class or interface
	*@return bool represents whether or not the registration attempt
	*was successful. If the method returns false then the caller must
	*free the Method object that was passed in
	*/
	static bool registerMethod( Method* method, const String& className, const bool& isInterfaceMethod );


	/**
	*attempts to register the method with the class or interface
	*@param Method the Method object that represents the method to registered
	*@param String the UUID of the class or interface to register the Method
	*with
	*@param bool whether or not the Method is associated with an Interface
	*or a Class.
	*@return bool represents whether or not the registration attempt
	*was successful. If the method returns false then the caller must
	*free the Method object that was passed in
	*/
	static bool registerMethodByUUID( Method* method, const String& UUID, const bool& isInterfaceMethod );

	/**
	*Dumps out the classes in registery to stdout
	*/
	static void dump();

	/**
	Removes a class from teh ClassRegistry.
	Dynamically loaded libraries should call this prior to termination to
	prevent bad memory from being deleted
	*/

	static void removeClass( Class* clazz );

	static void removeInterface( InterfaceClass* interfaceClass );
protected:
	Class* internal_getClass( const String& className );

	Class* internal_getClassFromClassID( const String& classID );

	Class* internal_getClass( Object* object ) ;

	Class* internal_getClass( const Object* object ) ;

	Object* internal_createNewInstance( const String& className ) ;

	Object* internal_createNewInstanceFromClassID( const String& classID ) ;

	void* internal_createNewInterfaceInstanceFromInterfaceName( const String& interfaceName, const String& implementerClassName );

	void* internal_createNewInterfaceInstanceFromInterfaceID( const String& interfaceID, const String& implementerClassID );

	void internal_addClass( const String& className, Class* classToRegister );

	void internal_addInterface( const String& interfaceName, InterfaceClass* interfaceToRegister );

	Enumerator<Class*>* internal_getClasses() ;

	Enumerator<InterfaceClass*>* internal_getInterfaces() ;

	ImplementedInterfaceClass* internal_getImplementedInterface( const String& implementingClassName, const String& interfaceID );

	InterfaceClass* internal_getInterface( const String& interfaceName ) ;

	InterfaceClass* internal_getInterfaceFromInterfaceID( const String& interfaceID );

	void internal_addImplementedInterface( ImplementedInterfaceClass* interfaceToRegister, const String& implementerClassID );

	bool internal_registerMethod( Method* method, const String& className, const bool& isInterfaceMethod );


	bool internal_registerMethodByUUID( Method* method, const String& UUID, const bool& isInterfaceMethod );

	void internal_dump();

	static ClassRegistry* registryInstance_;

	/**
	*a static function that returns the global instance of the ClassRegistry.
	*/
	static ClassRegistry* getClassRegistry();

	/**
	*a map of all the classes in the ClassRegistry. keyed by the class name
	*/
	Map<String,Class*> classMap_;

	/**
	*a map of all the interfaces in the ClassRegistry. keyed by the interface name
	*/
	Map<String,InterfaceClass*> interfaceMap_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the classID
	*/
	std::map<String,InterfaceClass*> interfaceIDMap_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the classID
	*/
	std::map<String,ImplementedInterfaceClass*> implementedInterfacesIDMap_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the classID
	*/
	std::map<String,Class*> classIDMap_;

};







};


#endif // _VCF_CLASSREGISTRY_H__

/**
$Id$
*/
