#ifndef _VCF_CLASSINFO_H__
#define _VCF_CLASSINFO_H__
//ClassInfo.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{


/**
*RTTI helper classes for properly registering RTTI meta data with the
*class registry
*/

/**
*The ClassInfo is used to simplify registering
*classes with the FoundationKit's runtime ClassRegistry.
*The class is derived from by using the macros below. It is
*created on the stack, and the constructor will automatically
*register the class, as well as any of the classes properties,
*methods, and events that have been specified through the macros.
*/
template <class CLASS_TYPE> class ClassInfo : public Object {
public:
	ClassInfo( const String& className,
		       const String& superClassName, const String& classID ){
		isClassRegistered_ = registerClass<CLASS_TYPE>( NULL, className, superClassName, classID );
	};

	virtual ~ClassInfo(){};

	bool isClassRegistered(){
		return isClassRegistered_;
	}

private:
	bool isClassRegistered_;
};


/**
*The AbstractClassInfo is used to simplify registering
*classes with the FoundationKit's runtime ClassRegistry.
*It is uses specifically with classes that are abstract,
*in other words are not supposed to be created, only derived from.
*The class is derived from by using the macros below. It is
*created on the stack, and the constructor will automatically
*register the class, as well as any of the classes properties,
*methods, and events that have been specified through the macros.
*/
template <class CLASS_TYPE> class AbstractClassInfo : public Object {
public:
	AbstractClassInfo( const String& className,
		       const String& superClassName, const String& classID ){

		isClassRegistered_ = registerAbstractClass<CLASS_TYPE>( NULL, className, superClassName, classID );

	};

	virtual ~AbstractClassInfo(){};

	bool isClassRegistered(){
		return isClassRegistered_;
	}

private:
	bool isClassRegistered_;
};


/**
*The InterfaceInfo class serves bascially
*the same purpose as the ClassInfo class.
*It is used to register interfaces and their
*methods with the
*/
template <class INTERFACE_TYPE> class InterfaceInfo : public Object
{
public:
	InterfaceInfo( const String& interfaceName,
					const String& interfaceID,
					const String& superInterfaceClassName ) {

		isInterfaceRegistered_ = registerInterface<INTERFACE_TYPE>( NULL, interfaceName, interfaceID, superInterfaceClassName );

	}

	virtual ~InterfaceInfo(){};

protected:
	bool isInterfaceRegistered_;
};


}; //end of namespace VCF


/**
*Object creation macros
*/

/**
*makes create with the default constructor pattern, i.e.
*a create() method with no arguments
*/
#define CREATE( ClassType ) \
	static ClassType* create() {\
		ClassType* result = new ClassType();\
		result->init(); \
		return result;\
	};\
	\

/**
*makes a create() method with the copy constructor pattern.
*The create() method takes a pointer to a object instance
*of the same type.
*@param ClassType a pointer an object to copy it's
*initial data from
*/
#define CREATE_COPY( ClassType ) \
	static ClassType* create( ClassType* ClassType##Val ) {\
		ClassType* result = new ClassType( *ClassType##Val );\
		result->init(); \
		return result;\
	};\
	\


/**
*makes a create() method with a single argument. Requires a
*constructor to also be declared that accepts a single argument
*of the same type.
*@param ArgType the type of argument to use in the create() method
*/
#define CREATE_1( ClassType, ArgType ) \
	static ClassType* create( ArgType arg ) {\
		ClassType* result = new ClassType( arg );\
		result->init(); \
		return result;\
	};\
	\

#define CREATE_2( ClassType, ArgType1, ArgType2 ) \
	static ClassType* create( ArgType1 arg1,  ArgType2 arg2 ) {\
		ClassType* result = new ClassType( arg1, arg2 );\
		result->init(); \
		return result;\
	};\
	\

#define CREATE_3( ClassType, ArgType1, ArgType2, ArgType3 ) \
	static ClassType* create( ArgType1 arg1,  ArgType2 arg2, ArgType3 arg3 ) {\
		ClassType* result = new ClassType( arg1, arg2, arg3 );\
		result->init(); \
		return result;\
	};\
	\

#define CREATE_4( ClassType, ArgType1, ArgType2, ArgType3, ArgType4 ) \
	static ClassType* create( ArgType1 arg1,  ArgType2 arg2, ArgType3 arg3, ArgType4 arg4 ) {\
		ClassType* result = new ClassType( arg1, arg2, arg3, arg4 );\
		result->init(); \
		return result;\
	};\
	\

#define CREATE_5( ClassType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5 ) \
	static ClassType* create( ArgType1 arg1,  ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5 ) {\
		ClassType* result = new ClassType( arg1, arg2, arg3, arg4, arg5 );\
		result->init(); \
		return result;\
	};\
	\

#define CREATE_6( ClassType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6 ) \
	static ClassType* create( ArgType1 arg1,  ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6 ) {\
		ClassType* result = new ClassType( arg1, arg2, arg3, arg4, arg5, arg6 );\
		result->init(); \
		return result;\
	};\
	\


#ifdef VCF_RTTI


/**
*RTTI macros
*/
/**
*When defining your classes RTTI info in the VCF you will always start
*with either this macro or the BEGIN_ABSTRACT_CLASSINFO macro.
*This will begin the declaration of a nested class derived from
*ClassInfo.
*@param  ClassType the class type to use. If you class is called Foo,
*then you will pass in Foo here.
*@param ClassName the fully qualified class name to identify your class by.
*Please note that fully qualified means that namespaces need to also be
*in the name. So if your class is called Foo in the namespace Baz, then
*you would use then name "Baz::Foo" here
*@param superClassName the name of the super class for this class. Once
*again this must be a fully qualified classname (see above). If your class
*was called Foo and derived from VCF::Object, then you would pass
*in "VCF::Object" here.
*@param classID a string that represents a unique id. Preferably a UUID
*that has been converted into a string representation.
*This macro must be paired with the END_CLASSINFO macro once
*you are finished defining your RTTI.
*/
#define BEGIN_CLASSINFO( ClassType, ClassName, superClassName, classID ) \
	class ClassType##_rtti_ClassInfo : public VCF::ClassInfo<ClassType> { \
	public: \
		ClassType##_rtti_ClassInfo(): \
			VCF::ClassInfo<ClassType>( ClassName, superClassName, classID ){ \
			VCF::String tmpClassName = ClassName; \
			if ( true == isClassRegistered()  ){ \
			\

/**
*When defining your classes RTTI info in the VCF you will always start
*with either this macro or the BEGIN_ABSTRACT_CLASSINFO macro.
*This will begin the declaration of a nested class derived from
*AbstractClassInfo.
*@param  ClassType the class type to use. If you class is called Foo,
*then you will pass in Foo here.
*@param ClassName the fully qualified class name to identify your class by.
*Please note that fully qualified means that namespaces need to also be
*in the name. So if your class is called Foo in the namespace Baz, then
*you would use then name "Baz::Foo" here
*@param superClassName the name of the super class for this class. Once
*again this must be a fully qualified classname (see above). If your class
*was called Foo and derived from VCF::Object, then you would pass
*in "VCF::Object" here.
*@param classID a string that represents a unique id. Preferably a UUID
*that has been converted into a string representation.
*This macro must be paired with the END_CLASSINFO macro once
*you are finished defining your RTTI.
*/
#define BEGIN_ABSTRACT_CLASSINFO( ClassType, ClassName, superClassName, classID ) \
	class ClassType##_rtti_ClassInfo : public VCF::AbstractClassInfo<ClassType> { \
	public: \
		ClassType##_rtti_ClassInfo(): \
			VCF::AbstractClassInfo<ClassType>( ClassName, superClassName, classID ){ \
			VCF::String tmpClassName = ClassName; \
			if ( true == isClassRegistered()  ){ \
			\

/**
*When defining your interfaces RTTI info in the VCF you will always start
*with this macro. This will begin the declaration of a nested class
*derived from InterfaceInfo.
*@param  InterfaceType the class type to use for your interface. If your
*interface is called FooInterface, then you will pass in FooInterface here.
*@param InterfaceName the fully qualified class name to identify your class by.
*Please note that fully qualified means that namespaces need to also be
*in the name. So if your class is called FooInterface in the namespace Baz, then
*you would use then name "Baz::FooInterface" here
*@param SuperInterfaceName the name of the interface that this interface derives
*from. Once again this must be a fully qualified classname (see above). If your class
*was called FooInterface and derived from VCF::Interface, then you would pass
*in "VCF::Interface" here (this will be the case most of the time).
*@param InterfaceID a string that represents a unique id. Preferably a UUID
*that has been converted into a string representation.
*This macro must be paired with the END_INTERFACEINFO macro once
*you are finished defining your RTTI.
*/
#define BEGIN_INTERFACEINFO(InterfaceType,InterfaceName,SuperInterfaceName,InterfaceID)\
	class InterfaceType##_rtti_InterfaceInfo : public VCF::InterfaceInfo<InterfaceType> {\
	public:\
		InterfaceType##_rtti_InterfaceInfo():\
		VCF::InterfaceInfo<InterfaceType>(InterfaceName,InterfaceID,SuperInterfaceName){\
			VCF::String tmpInterfaceName = InterfaceName;\
			if ( true == isInterfaceRegistered_ ) {\
			\


/**
*This macro is used within a BEGIN_CLASSINFO/END_CLASSINFO block
*to indicate that this class fully implements the specified
*interface.
*/
#define IMPLEMENTS_INTERFACE( ClassType, InterfaceType, implementationClassName, interfaceName, interfaceID, superInterfaceClassName ) \
	VCF::registerImplementedInterface<InterfaceType,ClassType>( NULL, VCF::String(implementationClassName), VCF::String(interfaceName), VCF::String(interfaceID), VCF::String(superInterfaceClassName) ); \
		\



#define FIELD(SourceType,FieldType,Field)\
	VCF::registerFieldType<FieldType>( tmpClassName, VCF::String(#Field), offsetof(SourceType,Field) );\
	\

#define OBJ_FIELD(SourceType,FieldType,Field)\
	VCF::registerObjectFieldType<FieldType>( tmpClassName, VCF::String(#Field), offsetof(SourceType,Field) );\
	\


/**
*Registers that the class fires an event. By declaring this it is expected that
*there are methods for adding event handler of the specified type that fire
*events of the specified event type.
*@param handlerClassName the name of the EventHandler derived class. This class
*will contain a method pointer to some source object that wants to get notified
*for the event.
*@param eventClassName the class name of the Event type that is fired
*by this class.
*@param eventMethod the method name that is used in the supporting
*event methods. So you might pass in "StreamExhausted". You could then
*expect to find methods as follows declared in the class:
*<pre>
*   void addStreamExhaustedHandler( EventHandler* handler ) ;
*   void removeStreamExhaustedHandler( EventHandler* handler ) ;
*   void fireOnStreamExhausted( eventClassName* event ) ;
*</pre>
*/
#define EVENT(handlerClassName,SourceType,EventType,DelegateID) \
		VCF::registerEvent<SourceType,EventType>( NULL, NULL, tmpClassName, \
							VCF::String(handlerClassName), VCF::String(#EventType), \
							VCF::String(#DelegateID), \
							(VCF::EventProperty::DelegateMethod)&SourceType::get##DelegateID); \
		\


#define ABSTRACT_EVENT(handlerClassName,SourceType,EventType,DelegateID) \
		VCF::registerEvent<SourceType,EventType>( NULL, NULL, tmpClassName, \
							VCF::String(handlerClassName), VCF::String(#EventType), \
							VCF::String(#DelegateID), \
							NULL); \
		\



#define PROPERTY( type, propName, getFunc, setFunc, propType ) \
	VCF::registerPrimitiveProperty<type>( tmpClassName, VCF::String(propName), \
							           (VCF::TypedProperty<type>::GetFunction)&getFunc, \
									   (VCF::TypedProperty<type>::SetFunction)&setFunc, \
									    propType ); \
										\

#define PROPERTY_TYPEDEF( type, propName, getFunc, setFunc, propType, typeName ) \
	VCF::registerTypeDefProperty<type>( tmpClassName, VCF::String(propName), \
							           (VCF::TypedProperty<type>::GetFunction)&getFunc, \
									   (VCF::TypedProperty<type>::SetFunction)&setFunc, \
									    propType, VCF::String(typeName) ); \
										\

#define READONLY_PROPERTY( type, propName, getFunc, propType ) \
	            VCF::registerPrimitiveReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
							                    (VCF::TypedProperty<type>::GetFunction)&getFunc, \
									            propType ); \
										                    \


#define READONLY_PROPERTY_TYPEDEF( type, propName, getFunc, propType, typeName ) \
	            VCF::registerTypeDefReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
							                    (VCF::TypedProperty<type>::GetFunction)&getFunc, \
									            propType, VCF::String(typeName) ); \
										                    \

#define OBJECT_PROPERTY( type, propName, getFunc, setFunc ) \
				VCF::registerObjectProperty<type>( tmpClassName, VCF::String(propName),  \
                            (VCF::TypedObjectProperty<type>::GetFunction)&getFunc,  \
							(VCF::TypedObjectProperty<type>::SetFunction)&setFunc );  \
							                                                   \


#define READONLY_OBJECT_PROPERTY( type, propName, getFunc ) \
				VCF::registerObjectReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
                            (VCF::TypedObjectProperty<type>::GetFunction)&getFunc ); \
																		       \


#define OBJECT_PROPERTY_REF( type, propName, getFunc, setFunc ) \
				VCF::registerObjectPropertyRef<type>( tmpClassName, VCF::String(propName),  \
                            (VCF::TypedObjectRefProperty<type>::GetFunction)&getFunc,  \
							(VCF::TypedObjectRefProperty<type>::SetFunction)&setFunc );  \
							                                                   \

#define READONLY_OBJECT_PROPERTY_REF( type, propName, getFunc ) \
				VCF::registerObjectReadOnlyPropertyRef<type>( tmpClassName, VCF::String(propName),  \
                            (VCF::TypedObjectRefProperty<type>::GetFunction)&getFunc );  \
							                                                   \


#define ENUM_PROPERTY(type,propName,getFunc,setFunc, lower, upper) \
				VCF::registerEnumProperty<type>( tmpClassName, VCF::String(propName), \
									    (VCF::TypedEnumProperty<type>::GetFunction)&getFunc, \
										(VCF::TypedEnumProperty<type>::SetFunction)&setFunc, \
										lower, \
										upper); \
										 \

#define ENUM_SET_PROPERTY(propName,getFunc,setFunc, count, values, enumNames) \
				VCF::registerEnumSetPropertyWithLabels( tmpClassName, VCF::String(propName), \
									    (EnumSetProperty::GetFunction)&getFunc, \
										(EnumSetProperty::SetFunction)&setFunc, \
										count, \
										values, \
										enumNames ); \
													\

#define READONLY_ENUM_SET_PROPERTY(propName,getFunc, count, values, enumNames) \
				VCF::registerEnumSetReadOnlyPropertyWithLabels( tmpClassName, VCF::String(propName), \
									    (EnumSetProperty::GetFunction)&getFunc, \
										count, \
										values, \
										enumNames ); \
													\



#define LABELED_ENUM_PROPERTY(type,propName,getFunc,setFunc, lower, upper, count, enumNames) \
				VCF::registerEnumPropertyWithLabels<type>( tmpClassName, VCF::String(propName), \
									    (VCF::TypedEnumProperty<type>::GetFunction)&getFunc, \
										(VCF::TypedEnumProperty<type>::SetFunction)&setFunc, \
										lower, \
										upper, \
										count, \
										enumNames ); \
													\


#define READONLY_ENUM_PROPERTY(type,propName,getFunc,lower, upper) \
				VCF::registerEnumReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
												(VCF::TypedEnumProperty<type>::GetFunction)&getFunc, \
												lower, \
												upper); \
												        \


#define READONLY_LABELED_ENUM_PROPERTY(type,propName,getFunc,lower, upper, count, enumNames) \
				VCF::registerEnumReadOnlyPropertyWithLabels<type>( tmpClassName, VCF::String(propName), \
									            (TypedEnumProperty<type>::GetFunction)&getFunc, \
												lower, \
												upper, \
												count, \
												enumNames ); \
												             \


#define COLLECTION_PROPERTY( type,propName,getFunc, propType ) \
				VCF::registerPrimitiveCollectionProperty<type>( tmpClassName, VCF::String(propName), \
				                                  (VCF::TypedCollectionProperty<type>::GetFunction)&getFunc, \
                                                  propType ); \
										            \

#define OBJECT_COLLECTION_PROPERTY( type,propName,getFunc, addFunc, insertFunc, deleteFunc1, deleteFunc2 ) \
				VCF::registerObjectCollectionProperty<type>( tmpClassName, VCF::String(propName), \
				                                  (VCF::TypedObjectCollectionProperty<type>::GetFunction)&getFunc, \
												  (VCF::TypedObjectCollectionProperty<type>::AddFunction)&addFunc, \
												  (VCF::TypedObjectCollectionProperty<type>::InsertFunction)&insertFunc, \
												  (VCF::TypedObjectCollectionProperty<type>::DeleteFunction1)&deleteFunc1, \
												  (VCF::TypedObjectCollectionProperty<type>::DeleteFunction2)&deleteFunc2 ); \
										            \

#define METHOD_VOID( classType, method ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(void); \
	VCF::registerVoidMethodArg0<classType,_T_##classType##method>( NULL, tmpClassName, VCF::String(#method), &classType:: method, "" );\
	}\
	\

#define METHOD_1VOID( classType, method, argType, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType); \
	VCF::registerVoidMethodArg1<classType,_T_##classType##method, argType>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_2VOID( classType, method, argType1, argType2, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2); \
	VCF::registerVoidMethodArg2<classType,_T_##classType##method,argType1, argType2>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_3VOID( classType, method, argType1, argType2, argType3, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3); \
	VCF::registerVoidMethodArg3<classType,_T_##classType##method,argType1, argType2, argType3>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_4VOID( classType, method, argType1, argType2, argType3, argType4, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3,argType4); \
	VCF::registerVoidMethodArg4<classType,_T_##classType##method,argType1, argType2, argType3, argType4>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_5VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3,argType4,argType5); \
	VCF::registerVoidMethodArg5<classType,_T_##classType##method,argType1, argType2, argType3, argType4, argType5>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_6VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3,argType4,argType5); \
	VCF::registerVoidMethodArg6<classType,_T_##classType##method,argType1, argType2, argType3, argType4, argType5, argType6>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_RETURN( classType, method, returnType ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(); \
	VCF::registerMethod0Return<classType,_T_##classType##method,returnType>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String("") ); \
	}\
	  \

#define METHOD_1RETURN( classType, method, returnType, argType,  argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType); \
	VCF::registerMethod1Return<classType,_T_##classType##method,returnType,argType>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_2RETURN( classType, method, returnType, argType1, argType2, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1, argType2); \
	VCF::registerMethod2Return<classType,_T_##classType##method,returnType, argType1, argType2>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_3RETURN( classType, method, returnType, argType1, argType2, argType3, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1, argType2,argType3); \
	VCF::registerMethod3Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_4RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1, argType2,argType3,argType4); \
	VCF::registerMethod4Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3, argType4>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_5RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1, argType2,argType3,argType4,argType5); \
	VCF::registerMethod5Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3, argType4, argType5>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define METHOD_6RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1, argType2,argType3,argType4,argType5,argType6); \
	VCF::registerMethod6Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3, argType4, argType5, argType6>( NULL, tmpClassName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define INTERFACE_METHOD_VOID( classType, method ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(); \
	VCF::registerVoidMethodArg0<classType,_T_##classType##method>( NULL, tmpInterfaceName, VCF::String(#method), &classType::method, "", true ); \
	}\
	  \

#define INTERFACE_METHOD1_VOID( classType, method, argType, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType); \
	VCF::registerVoidMethodArg1<classType,_T_##classType##method,argType>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD2_VOID( classType, method, argType1, argType2, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2); \
	VCF::registerVoidMethodArg2<classType,_T_##classType##method,argType1, argType2>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD3_VOID( classType, method, argType1, argType2, argType3, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3); \
	VCF::registerVoidMethodArg3<classType,_T_##classType##method,argType1, argType2, argType3>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD4_VOID( classType, method, argType1, argType2, argType3, argType4, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3argType4); \
	VCF::registerVoidMethodArg4<classType,_T_##classType##method,argType1, argType2, argType3, argType4>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD5_VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3argType4,argType5); \
	VCF::registerVoidMethodArg5<classType,_T_##classType##method,argType1, argType2, argType3, argType4, argType5>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD6_VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc ) \
	{\
	typedef  void ( classType::* _T_##classType##method )(argType1,argType2,argType3argType4,argType5,argType6); \
	VCF::registerVoidMethodArg6<classType,_T_##classType##method,argType1, argType2, argType3, argType4, argType5, argType6>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD_RETURN( classType, method, returnType ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(); \
	VCF::registerMethod0Return<classType,_T_##classType##method,returnType>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, "", true ); \
	}\
	  \

#define INTERFACE_METHOD1_RETURN( classType, method, returnType, argType, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType); \
	VCF::registerMethod1Return<classType,_T_##classType##method,returnType, argType>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD2_RETURN( classType, method, returnType, argType1, argType2, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1,argType2); \
	VCF::registerMethod2Return<classType,_T_##classType##method,returnType, argType1, argType2>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD3_RETURN( classType, method, returnType, argType1, argType2, argType3, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1,argType2,argType3); \
	VCF::registerMethod3Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD4_RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1,argType2,argType3,argType4); \
	VCF::registerMethod4Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3, argType4>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD5_RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1,argType2,argType3,argType4,argType5); \
	VCF::registerMethod5Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3, argType4, argType5>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define INTERFACE_METHOD6_RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc ) \
	{\
	typedef  returnType ( classType::* _T_##classType##method )(argType1,argType2,argType3,argType4,argType5,argType6); \
	VCF::registerMethod6Return<classType,_T_##classType##method,returnType, argType1, argType2, argType3, argType4, argType5, argType6>( NULL, tmpInterfaceName, VCF::String(#method), &classType:: method, VCF::String(argTypeDesc), true ); \
	}\
	  \

#define END_CLASSINFO( ClassType ) \
  			} \
		}; \
		 \
		 \
		virtual ~ClassType##_rtti_ClassInfo(){}; \
     \
	}; \
	\



#define END_INTERFACEINFO(InterfaceType)\
			}\
		};\
		virtual ~InterfaceType##_rtti_InterfaceInfo(){};\
	};\
	\


#define REGISTER_CLASSINFO( ClassType ) \
	ClassType::ClassType##_rtti_ClassInfo classInfoFor##ClassType; \
		                                           \

#define REGISTER_INTERFACEINFO(InterfaceType)\
	InterfaceType::InterfaceType##_rtti_InterfaceInfo interfaceInfoFor##InterfaceType;\
	\


#define REGISTER_CLASSINFO_EXTERNAL( ClassType ) \
	ClassType##_rtti_ClassInfo classInfoFor##ClassType; \
		                                           \

#define REGISTER_INTERFACEINFO_EXTERNAL(InterfaceType)\
	InterfaceType##_rtti_InterfaceInfo interfaceInfoFor##InterfaceType;\
	\

#else


#define BEGIN_CLASSINFO( ClassType, ClassName, superClassName, classID )

#define BEGIN_ABSTRACT_CLASSINFO( ClassType, ClassName, superClassName, classID )

#define BEGIN_INTERFACEINFO(InterfaceType,InterfaceName,SuperInterfaceName,InterfaceID)

#define IMPLEMENTS_INTERFACE( ClassType, InterfaceType, implementationClassName, interfaceName, interfaceID, superInterfaceClassName )

#define FIELD(SourceType,FieldType,Field)

#define OBJ_FIELD(SourceType,FieldType,Field)


#define EVENT(handlerClassName,eventClassName,eventMethod)

#define PROPERTY( type, propName, getFunc, setFunc, propType )

#define READONLY_PROPERTY( type, propName, getFunc, propType )

#define OBJECT_PROPERTY( type, propName, getFunc, setFunc )

#define READONLY_OBJECT_PROPERTY( type, propName, getFunc )

#define OBJECT_PROPERTY_REF( type, propName, getFunc, setFunc )

#define READONLY_OBJECT_PROPERTY_REF( type, propName, getFunc )

#define ENUM_PROPERTY(type,propName,getFunc,setFunc, lower, upper)

#define LABELED_ENUM_PROPERTY(type,propName,getFunc,setFunc, lower, upper, count, enumNames)

#define READONLY_ENUM_PROPERTY(type,propName,getFunc,lower, upper)

#define READONLY_LABELED_ENUM_PROPERTY(type,propName,getFunc,lower, upper, count, enumNames)

#define COLLECTION_PROPERTY( type,propName,getFunc, propType )

#define OBJECT_COLLECTION_PROPERTY( type,propName,getFunc, addFunc, insertFunc, deleteFunc1, deleteFunc2 )

#define METHOD_VOID( classType, methType )

#define METHOD_1VOID( classType, method, argType, argTypeDesc )

#define METHOD_2VOID( classType, method, argType1, argType2, argTypeDesc )

#define METHOD_3VOID( classType, method, argType1, argType2, argType3, argTypeDesc )

#define METHOD_4VOID( classType, method, argType1, argType2, argType3, argType4, argTypeDesc )

#define METHOD_5VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argTypeDesc )

#define METHOD_6VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc )

#define METHOD_RETURN( classType, method, returnType )

#define METHOD_1RETURN( classType, method, returnType, argType, argTypeDesc )

#define METHOD_2RETURN( classType, method, returnType, argType1, argType2, argTypeDesc )

#define METHOD_3RETURN( classType, method, returnType, argType1, argType2, argType3, argTypeDesc )

#define METHOD_4RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argTypeDesc )

#define METHOD_5RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argTypeDesc )

#define METHOD_6RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc )

#define INTERFACE_METHOD_VOID( classType, methType )

#define INTERFACE_METHOD1_VOID( classType, method, argType, argTypeDesc )

#define INTERFACE_METHOD2_VOID( classType, method, argType1, argType2, argTypeDesc )

#define INTERFACE_METHOD3_VOID( classType, method, argType1, argType2, argType3, argTypeDesc )

#define INTERFACE_METHOD4_VOID( classType, method, argType1, argType2, argType3, argType4, argTypeDesc )

#define INTERFACE_METHOD5_VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argTypeDesc )

#define INTERFACE_METHOD6_VOID( classType, method, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc )

#define INTERFACE_METHOD_RETURN( classType, method, returnType )

#define INTERFACE_METHOD1_RETURN( classType, method, returnType, argType, argTypeDesc )

#define INTERFACE_METHOD2_RETURN( classType, method, returnType, argType1, argType2, argTypeDesc )

#define INTERFACE_METHOD3_RETURN( classType, method, returnType, argType1, argType2, argType3, argTypeDesc )

#define INTERFACE_METHOD4_RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argTypeDesc )

#define INTERFACE_METHOD5_RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argTypeDesc )

#define INTERFACE_METHOD6_RETURN( classType, method, returnType, argType1, argType2, argType3, argType4, argType5, argType6, argTypeDesc )


#define END_CLASSINFO( ClassType )

#define REGISTER_CLASSINFO( ClassType )

#define REGISTER_INTERFACEINFO(InterfaceType)

#define END_INTERFACEINFO(InterfaceType)

#endif //VCF_RTTI


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/05/16 02:39:09  ddiego
*OSX code updates
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.5.2.1  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.3  2004/01/21 19:06:26  ddiego
*fix for bug [ 776440 ] ClassReg doesn't call addImplementedInterface
*
*Revision 1.1.2.2  2004/01/18 04:52:45  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.1.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.24  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.23.4.7  2003/11/03 04:48:54  ddiego
*minor mods
*
*Revision 1.23.4.6  2003/11/02 02:54:34  ddiego
*made some small changes to the method RTTI registration code.
*
*Revision 1.23.4.5  2003/10/24 04:03:36  ddiego
*More header musical chairs
*
*Revision 1.23.4.4  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.23.4.3  2003/10/04 20:14:59  ddiego
*aaddec changes to support compiling on GCC 3.3.1, which is much more
*picky than some of the previous versions.
*
*Revision 1.23.4.2  2003/09/12 16:46:33  ddiego
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
*Revision 1.23.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.23  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.22.2.1  2003/03/12 03:09:19  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.22  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.21.14.2  2002/12/27 23:04:30  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21.14.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.21  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.20.4.2  2002/03/25 04:19:45  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.20.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.20  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CLASSINFO_H__


