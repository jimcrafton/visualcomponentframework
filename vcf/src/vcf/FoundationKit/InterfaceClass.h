#ifndef _VCF_INTERFACECLASS_H__
#define _VCF_INTERFACECLASS_H__
//InterfaceClass.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
*The InterfaceClass does much the same for interface classes that the
*VCF::Class does for classes. It is a base class for RTTI for interfaces
*/
class FOUNDATIONKIT_API InterfaceClass  {
public:
	InterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName );

	virtual ~InterfaceClass();

	/**
	*returns the interface id for the interface class. InterfaceClass's may have the same name
	*so to prevent this, an ID is provided. This is ID MUST be generated using
	*some algorithm that guarantees a valid UUID
	*/
	String getID() {
		return interfaceID_;
	}

	/**
	*returns the interface name of the InterfaceClass
	*/
	String getInterfaceName() {
		return interfaceName_;
	}

	/**
	*returns an enumerator containing the Methods of the Class
	*the enumerator does not reflect the order in which the properties were added.
	*/
	Enumerator<Method*>* getMethods(){
		return methodContainer_.getEnumerator();
	}

	/**
	*adds a new method to the InterfaceClass's method map.
	*/
	void addMethod( Method* method );

	/**
	*does the InterfaceClass have a have a particular method ?
	*@param String the name of the method to find
	*@return bool true if the interface has the specified method, otherwise false
	*/
	bool hasMethod( const String& methodName );

	/**
	*the number of methods the Class has
	*/
	unsigned long getMethodCount();

	/**
	*gets the method specified by methodName, if the class
	*has that method.
	*@param String the name of the method to try and retrieve
	*@return Method a pointer to a method of the interface.
	*/
	Method* getMethod( const String& methodName );

	virtual bool isEqual( Object* object ) const;

	virtual bool compareObject( Object* object )const = 0;


	/**
	*sets the source for all methods in the InterfaceClass to source.
	*@param Object the source to which the methods are set
	*/
	void setSource( Object* source );

	/**
	*returns the InterfaceClass that this interface is derived
	*from, if any.
	*@return InterfaceClass the super interface this interface is derived
	*from. May return NULL if the interface is not derived from any thing
	*/
	InterfaceClass* getSuperInterfaceClass();
protected:
	String superInterfaceClassName_;
	String interfaceName_;
	String interfaceID_;
	std::map<String,Method*> methods_;
	EnumeratorMapContainer<std::map<String,Method*>,Method*> methodContainer_;
private:
};



/**
\class ImplementedInterfaceClass InterfaceClass.h "vcf/FoundationKit/InterfaceClass.h"
*ImplementedInterfaceClass documentation
*/
class FOUNDATIONKIT_API ImplementedInterfaceClass : public InterfaceClass {
public:
	ImplementedInterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName );

	virtual ~ImplementedInterfaceClass();

	/**
	*creates a new instance of an Object that implements the interface
	*represented by this InterfaceClass. Since multiple interfaces may
	*be implemented by a given Object, more than one InterfaceClass may
	*end up creating the same Object instance.
	*/
	virtual Object* createImplementingInstance() = 0;

	/**
	*creates an instance of the interface. Sadly this requires the use of a void*
	*since we can't possibly know the correct interface base type.
	*Perhaps this may be replaced the use of the Interface base class, though it
	*will still require a type cast by the caller into the appropriate type
	*/
	virtual void* createInterfaceInstance() = 0;
protected:
};




}; //end of namespace VCF


#endif // _VCF_INTERFACECLASS_H__

/**
$Id$
*/
