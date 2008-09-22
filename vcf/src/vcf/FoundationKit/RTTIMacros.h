#ifndef _VCF_RTTIMACROS_H__
#define _VCF_RTTIMACROS_H__
//RTTIMacros.h

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/VCFRTTIImpl.h"
#include "vcf/FoundationKit/ClassInfo.h"


/**
These are the new RTTI macros - don't use the ones defined 
in ClassInfo.h any more.
*/

#ifdef VCF_RTTI


/**
When defining your classes RTTI info in the VCF you will always start
with either this macro or the _class_abstract_rtti_ macro.
This will begin the declaration of a nested class derived from
ClassInfo.
@param  classType the class type to use. If you class is called Foo,
then you will pass in Foo here.
@param superClassName the name of the super class for this class. This 
must be a fully qualified classname (see above). If your class
was called Foo and derived from VCF::Object, then you would pass
in "VCF::Object" here.
@param classID a string that represents a unique id. Preferably a UUID
that has been converted into a string representation.
This macro must be paired with the _class_rtti_end_ macro once
you are finished defining your RTTI.
*/
#define _class_rtti_(classType,superClassName,classID) \
	class classType##_rtti_ClassInfo : public VCF::ClassInfo<classType> { \
	public: \
		typedef classType RttiClassType;\
		classType##_rtti_ClassInfo(): \
		VCF::ClassInfo<RttiClassType>( VCF::StringUtils::getClassNameFromTypeInfo(typeid(classType)), superClassName, classID ){ \
			VCF::String tmpClassName = VCF::StringUtils::getClassNameFromTypeInfo(typeid(classType)); \
			if ( isClassRegistered()  ){ \
			\

#define _class_rtti_end_ \
			}\
		}\
	};\
	\


/**
When defining your classes RTTI info in the VCF you will always start
with either this macro or the _class_rtti_ macro.
This will begin the declaration of a nested class derived from
AbstractClassInfo.
@param  ClassType the class type to use. If you class is called Foo,
then you will pass in Foo here.
@param superClassName the name of the super class for this class. This 
must be a fully qualified classname (see above). If your class
was called Foo and derived from VCF::Object, then you would pass
in "VCF::Object" here.
@param classID a string that represents a unique id. Preferably a UUID
that has been converted into a string representation.
This macro must be paired with the _class_rtti_end_ macro once
you are finished defining your RTTI.
*/
#define _class_abstract_rtti_(classType,superClassName,classID) \
	class classType##_rtti_ClassInfo : public VCF::AbstractClassInfo<classType> { \
	public: \
		typedef classType RttiClassType;\
		classType##_rtti_ClassInfo(): \
		VCF::AbstractClassInfo<RttiClassType>( VCF::StringUtils::getClassNameFromTypeInfo(typeid(classType)), superClassName, classID ){ \
			VCF::String tmpClassName = VCF::StringUtils::getClassNameFromTypeInfo(typeid(classType)); \
			if ( isClassRegistered()  ){ \
			\



/**
When defining your interfaces RTTI info in the VCF you will always start
with this macro. This will begin the declaration of a nested class
derived from InterfaceInfo.
@param  InterfaceType the class type to use for your interface. If your
interface is called FooInterface, then you will pass in FooInterface here.
@param SuperInterfaceName the name of the interface that this interface derives
from. This must be a fully qualified classname. If your class
was called FooInterface and derived from VCF::Interface, then you would pass
in "VCF::Interface" here (this will be the case most of the time).
@param InterfaceID a string that represents a unique id. Preferably a UUID
that has been converted into a string representation.
This macro must be paired with the _interface_rtti_end_ macro once
you are finished defining your RTTI.
*/
#define _interface_rtti_(InterfaceType,SuperInterfaceName,InterfaceID)\
	class InterfaceType##_rtti_InterfaceInfo : public VCF::InterfaceInfo<InterfaceType> {\
	public:\
		typedef InterfaceType RttiClassType;\
		InterfaceType##_rtti_InterfaceInfo():\
		VCF::InterfaceInfo<InterfaceType>( VCF::StringUtils::getClassNameFromTypeInfo(typeid(InterfaceType)),InterfaceID,SuperInterfaceName){\
			VCF::String tmpClassName = VCF::StringUtils::getClassNameFromTypeInfo(typeid(InterfaceType));\
			if ( true == isInterfaceRegistered_ ) {\
			\


#define _interface_rtti_end_ \
			}\
		};\
	};\
	\




/**
*This macro is used within a _class_rtti_/_class_rtti_end_ block
*to indicate that this class fully implements the specified
*interface.
*/
#define _implements_( InterfaceType, interfaceID, superInterfaceClassName ) \
	VCF::registerImplementedInterface<InterfaceType,RttiClassType>( NULL, tmpClassName, VCF::StringUtils::getClassNameFromTypeInfo(typeid(InterfaceType)), VCF::String(interfaceID), VCF::String(superInterfaceClassName) ); \
		\



#define _field_(FieldType,FieldVar)\
	VCF::registerFieldType<FieldType>( tmpClassName, VCF::String(#FieldVar), offsetof(RttiClassType,FieldVar) );\
	\

#define _field_obj_(FieldType,FieldVar)\
	VCF::registerObjectFieldType<FieldType>( tmpClassName, VCF::String(#FieldVar), offsetof(RttiClassType,FieldVar) );\
	\


/**
*Registers that the class fires an event. By declaring this it is expected that
*there are methods for adding event handler of the specified type that fire
*/
#define _event_(DelegateType,DelegateID) \
	\
	VCF::registerEvent<RttiClassType>( tmpClassName, \
							VCF::String(#DelegateType),\
							VCF::String(#DelegateID), \
							(VCF::Delegate& (RttiClassType::*)(void))&RttiClassType::get##DelegateID); \
							\



#define _delegate_(DelegateType,DelegateID)	 _event_(DelegateType,DelegateID) 

#define _abstract_event_(DelegateType,DelegateID) \
		VCF::registerEvent<RttiClassType>( tmpClassName, \
							VCF::String(#DelegateType), \
							VCF::String(#DelegateID), \
							NULL); \
		\


#define _abstract_delegate_(DelegateType,DelegateID)	 _abstract_event_(DelegateType,DelegateID) 

#define _property_( type, propName, getFunc, setFunc, description ) \
	VCF::registerPrimitiveProperty<type>( tmpClassName, VCF::String(propName), \
										(VCF::TypedProperty<type>::GetFunction)&RttiClassType::getFunc, \
									   (VCF::TypedProperty<type>::SetFunction)&RttiClassType::setFunc, \
									    description ); \
										\

#define _property_ro_( type, propName, getFunc, description ) \
	VCF::registerPrimitiveReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
							           (VCF::TypedProperty<type>::GetFunction)&RttiClassType::getFunc, \
									    description ); \
										\

#define _property_typedef_( type, propName, getFunc, setFunc, typeName, description ) \
	VCF::registerTypeDefProperty<type>( tmpClassName, VCF::String(propName), \
							           (VCF::TypedProperty<type>::GetFunction)&RttiClassType::getFunc, \
									   (VCF::TypedProperty<type>::SetFunction)&RttiClassType::setFunc, \
									    VCF::String(typeName),description ); \
										\


#define _property_typef_ro_( type, propName, getFunc, typeName, description ) \
	VCF::registerTypeDefReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
							                    (VCF::TypedProperty<type>::GetFunction)&RttiClassType::getFunc, \
									            VCF::String(typeName),description ); \
										                    \

#define _property_object_( type, propName, getFunc, setFunc, description ) \
	VCF::registerObjectProperty<type>( tmpClassName, VCF::String(propName),  \
                            (VCF::TypedObjectProperty<type>::GetFunction)&RttiClassType::getFunc,  \
							(VCF::TypedObjectProperty<type>::SetFunction)&RttiClassType::setFunc,description );  \
							                                                   \


#define _property_object_ro_( type, propName, getFunc, description ) \
	VCF::registerObjectReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
                            (VCF::TypedObjectProperty<type>::GetFunction)&RttiClassType::getFunc,description ); \
																		       \


#define _property_object_ref_( type, propName, getFunc, setFunc, description ) \
	VCF::registerObjectPropertyRef<type>( tmpClassName, VCF::String(propName),  \
                            (VCF::TypedObjectRefProperty<type>::GetFunction)&RttiClassType::getFunc,  \
							(VCF::TypedObjectRefProperty<type>::SetFunction)&RttiClassType::setFunc,description );  \
							                                                   \

#define _property_object_ref_ro_( type, propName, getFunc, description ) \
	VCF::registerObjectReadOnlyPropertyRef<type>( tmpClassName, VCF::String(propName),  \
                            (VCF::TypedObjectRefProperty<type>::GetFunction)&RttiClassType::getFunc,description );  \
							                                                   \


#define _property_enum_(type,propName,getFunc,setFunc, lower, upper, description) \
	VCF::registerEnumProperty<type>( tmpClassName, VCF::String(propName), \
									    (VCF::TypedEnumProperty<type>::GetFunction)&RttiClassType::getFunc, \
										(VCF::TypedEnumProperty<type>::SetFunction)&RttiClassType::setFunc, \
										lower, \
										upper,description); \
										 \

#define _property_enumset_( type, propName,getFunc,setFunc, count, values, enumNames, description) \
	VCF::registerEnumSetPropertyWithLabels( #type, tmpClassName, VCF::String(propName), \
									    (EnumSetProperty::GetFunction)&RttiClassType::getFunc, \
										(EnumSetProperty::SetFunction)&RttiClassType::setFunc, \
										count, \
										values, \
										enumNames,description ); \
													\

#define _property_enumset_ro_(type, propName,getFunc, count, values, enumNames, description) \
	VCF::registerEnumSetReadOnlyPropertyWithLabels( #type, tmpClassName, VCF::String(propName), \
									    (EnumSetProperty::GetFunction)&RttiClassType::getFunc, \
										count, \
										values, \
										enumNames,description ); \
													\



#define _property_enum_labeled_(type,propName,getFunc,setFunc, lower, upper, count, enumNames, description) \
	VCF::registerEnumPropertyWithLabels<type>( tmpClassName, VCF::String(propName), \
									    (VCF::TypedEnumProperty<type>::GetFunction)&RttiClassType::getFunc, \
										(VCF::TypedEnumProperty<type>::SetFunction)&RttiClassType::setFunc, \
										lower, \
										upper, \
										count, \
										enumNames,description ); \
													\


#define _property_enum_ro_(type,propName,getFunc,lower, upper, description) \
	VCF::registerEnumReadOnlyProperty<type>( tmpClassName, VCF::String(propName), \
												(VCF::TypedEnumProperty<type>::GetFunction)&RttiClassType::getFunc, \
												lower, \
												upper,description); \
												        \


#define _property_enum_labeled_ro_(type,propName,getFunc,lower, upper, count, enumNames, description) \
	VCF::registerEnumReadOnlyPropertyWithLabels<type>( tmpClassName, VCF::String(propName), \
									            (TypedEnumProperty<type>::GetFunction)&RttiClassType::getFunc, \
												lower, \
												upper, \
												count, \
												enumNames,description ); \
												             \


 #define _property_array_( type, propName, getFunc, setFunc, insertFunc, deleteFunc, getSizeFunc, description ) \
	VCF::registerCollectionProperty<type,uint32>( tmpClassName, VCF::String(propName), \
		(VCF::TypedCollectionProperty<type,uint32>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedCollectionProperty<type,uint32>::SetFunction)&RttiClassType::setFunc, \
		(VCF::TypedCollectionProperty<type,uint32>::InsertFunction)&RttiClassType::insertFunc, \
		(VCF::TypedCollectionProperty<type,uint32>::DeleteFunction)&RttiClassType::deleteFunc, \
		(VCF::TypedCollectionProperty<type,uint32>::GetSizeFunction)&RttiClassType::getSizeFunc, \
		NULL,\
		VCF::String(description) ); \
	\



#define _property_collection_( type, key, propName, getFunc, setFunc, insertFunc, deleteFunc, getSizeFunc, description ) \
	VCF::registerCollectionProperty<type,key>( tmpClassName, VCF::String(propName), \
		(VCF::TypedCollectionProperty<type,key>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedCollectionProperty<type,key>::SetFunction)&RttiClassType::setFunc, \
		(VCF::TypedCollectionProperty<type,key>::InsertFunction)&RttiClassType::insertFunc, \
		(VCF::TypedCollectionProperty<type,key>::DeleteFunction)&RttiClassType::deleteFunc, \
		(VCF::TypedCollectionProperty<type,key>::GetSizeFunction)&RttiClassType::getSizeFunc, \
		NULL, \
		VCF::String(description) ); \
	\

#define _property_collection2_( type, key, propName, getFunc, setFunc, insertFunc, deleteFunc, getSizeForKeyFunc, description ) \
	VCF::registerCollectionProperty<type,key>( tmpClassName, VCF::String(propName), \
		(VCF::TypedCollectionProperty<type,key>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedCollectionProperty<type,key>::SetFunction)&RttiClassType::setFunc, \
		(VCF::TypedCollectionProperty<type,key>::InsertFunction)&RttiClassType::insertFunc, \
		(VCF::TypedCollectionProperty<type,key>::DeleteFunction)&RttiClassType::deleteFunc, \
		NULL, \
		(VCF::TypedCollectionProperty<type,key>::GetSizeForKeyFunction)&RttiClassType::getSizeForKeyFunc, \
		VCF::String(description) ); \
	\

#define _property_dictionary_( type, key, propName, getFunc, setFunc, description ) \
	VCF::registerDictionaryProperty<type,key>( tmpClassName, VCF::String(propName), \
		(VCF::TypedDictionaryProperty<type,key>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedDictionaryProperty<type,key>::SetFunction)&RttiClassType::setFunc, \
		VCF::String(description) ); \
	\




 #define _property_obj_array_( type, propName, getFunc, setFunc, insertFunc, deleteFunc, getSizeFunc, description ) \
	VCF::registerObjectCollectionProperty<type,uint32>( tmpClassName, VCF::String(propName), \
		(VCF::TypedObjectCollectionProperty<type,uint32>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedObjectCollectionProperty<type,uint32>::SetFunction)&RttiClassType::setFunc, \
		(VCF::TypedObjectCollectionProperty<type,uint32>::InsertFunction)&RttiClassType::insertFunc, \
		(VCF::TypedObjectCollectionProperty<type,uint32>::DeleteFunction)&RttiClassType::deleteFunc, \
		(VCF::TypedObjectCollectionProperty<type,uint32>::GetSizeFunction)&RttiClassType::getSizeFunc, \
		VCF::String(description) ); \
	\



#define _property_obj_collection_( type, key, propName, getFunc, setFunc, insertFunc, deleteFunc, getSizeFunc, description ) \
	VCF::registerObjectCollectionProperty<type,key>( tmpClassName, VCF::String(propName), \
		(VCF::TypedObjectCollectionProperty<type,key>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedObjectCollectionProperty<type,key>::SetFunction)&RttiClassType::setFunc, \
		(VCF::TypedObjectCollectionProperty<type,key>::InsertFunction)&RttiClassType::insertFunc, \
		(VCF::TypedObjectCollectionProperty<type,key>::DeleteFunction)&RttiClassType::deleteFunc, \
		(VCF::TypedObjectCollectionProperty<type,key>::GetSizeFunction)&RttiClassType::getSizeFunc, \
		VCF::String(description) ); \
	\

#define _property_obj_dictionary_( type, key, propName, getFunc, setFunc, getKeysFunc, description ) \
	VCF::registerObjectDictionaryProperty<type,key>( tmpClassName, VCF::String(propName), \
		(VCF::TypedObjectDictionaryProperty<type,key>::GetFunction)&RttiClassType::getFunc, \
		(VCF::TypedObjectDictionaryProperty<type,key>::SetFunction)&RttiClassType::setFunc, \
		(VCF::TypedObjectDictionaryProperty<type,key>::GetKeys)&RttiClassType::getKeysFunc, \
		VCF::String(description) ); \
	\




#define _procedure_(method) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(void); \
	VCF::registerVoidMethodArg0<RttiClassType,_T_##RttiClassType##method>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, "" );\
	}\
	\

#define _procedure1_(method,argType, argTypeDesc) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(argType); \
	VCF::registerVoidMethodArg1<RttiClassType,_T_##RttiClassType##method, argType>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _procedure2_(method,argType1,argType2,argTypeDesc) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(argType1,argType2); \
	VCF::registerVoidMethodArg2<RttiClassType,_T_##RttiClassType##method,argType1, argType2>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _procedure3_(method,argType1,argType2,argType3,argTypeDesc) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(argType1,argType2,argType3); \
	VCF::registerVoidMethodArg3<RttiClassType,_T_##RttiClassType##method,argType1, argType2, argType3>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _procedure4_(method,argType1,argType2,argType3,argType4,argTypeDesc) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(argType1,argType2,argType3,argType4); \
	VCF::registerVoidMethodArg4<RttiClassType,_T_##RttiClassType##method,argType1, argType2, argType3, argType4>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _procedure5_(method,argType1,argType2,argType3,argType4,argType5,argTypeDesc) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(argType1,argType2,argType3,argType4,argType5); \
	VCF::registerVoidMethodArg5<RttiClassType,_T_##RttiClassType##method,argType1, argType2, argType3, argType4, argType5>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _procedure6_(method,argType1,argType2,argType3,argType4,argType5,argType6,argTypeDesc) \
	{\
	typedef  void ( RttiClassType::* _T_##RttiClassType##method )(argType1,argType2,argType3,argType4,argType5); \
	VCF::registerVoidMethodArg6<RttiClassType,_T_##RttiClassType##method,argType1, argType2, argType3, argType4, argType5, argType6>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \


#define _function_(method,returnType) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(); \
	VCF::registerMethod0Return<RttiClassType,_T_##RttiClassType##method,returnType>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String("") ); \
	}\
	  \

#define _function1_(method,returnType,argType,argTypeDesc) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(argType); \
	VCF::registerMethod1Return<RttiClassType,_T_##RttiClassType##method,returnType,argType>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _function2_(method,returnType,argType1,argType2,argTypeDesc) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(argType1, argType2); \
	VCF::registerMethod2Return<RttiClassType,_T_##RttiClassType##method,returnType, argType1, argType2>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _function3_(method,returnType,argType1,argType2,argType3,argTypeDesc) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(argType1, argType2,argType3); \
	VCF::registerMethod3Return<RttiClassType,_T_##RttiClassType##method,returnType, argType1, argType2, argType3>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _function4_(method,returnType,argType1,argType2,argType3,argType4,argTypeDesc) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(argType1, argType2,argType3,argType4); \
	VCF::registerMethod4Return<RttiClassType,_T_##RttiClassType##method,returnType, argType1, argType2, argType3, argType4>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _function5_(method,returnType,argType1,argType2,argType3,argType4,argType5,argTypeDesc) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(argType1, argType2,argType3,argType4,argType5); \
	VCF::registerMethod5Return<RttiClassType,_T_##RttiClassType##method,returnType, argType1, argType2, argType3, argType4, argType5>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \

#define _function6_(method,returnType,argType1,argType2,argType3,argType4,argType5,argType6,argTypeDesc) \
	{\
	typedef  returnType ( RttiClassType::* _T_##RttiClassType##method )(argType1, argType2,argType3,argType4,argType5,argType6); \
	VCF::registerMethod6Return<RttiClassType,_T_##RttiClassType##method,returnType, argType1, argType2, argType3, argType4, argType5, argType6>( NULL, tmpClassName, VCF::String(#method), &RttiClassType:: method, VCF::String(argTypeDesc) ); \
	}\
	  \



#else

//No RTTI defined!

#define _class_rtti_(classType,superClassName,classID)

#define _class_rtti_end_ 


#define _class_abstract_rtti_(classType,superClassName,classID) 


#define _interface_rtti_(InterfaceType,SuperInterfaceName,InterfaceID) 

#define _interface_rtti_end_ 

#define _implements_( InterfaceType, interfaceID, superInterfaceClassName ) 


#define _field_(FieldType,Field)

#define _field_obj_(FieldType,Field)

#define _event_(handlerClassName,EventType,DelegateID) 

#define _abstract_event_(handlerClassName,EventType,DelegateID) 

#define _property_( type, propName, getFunc, setFunc, description )

#define _property_ro_( type, propName, getFunc, description ) 

#define _property_typef_( type, propName, getFunc, setFunc, typeName, description ) 

#define _property_typef_ro_( type, propName, getFunc, typeName, description )

#define _property_object_( type, propName, getFunc, setFunc, description )

#define _property_object_ro_( type, propName, getFunc, description )

#define _property_object_ref_( type, propName, getFunc, setFunc, description )

#define _property_object_ref_ro_( type, propName, getFunc, description ) 


#define _property_enum_(type,propName,getFunc,setFunc, lower, upper, description) 

#define _property_enumset_(propName,getFunc,setFunc, count, values, enumNames, description) 

#define _property_enumset_ro_(propName,getFunc, count, values, enumNames, description) 

#define _property_enum_labeled_(type,propName,getFunc,setFunc, lower, upper, count, enumNames, description) 

#define _property_enum_ro_(type,propName,getFunc,lower, upper, description) 


#define _property_enum_labeled_ro_(type,propName,getFunc,lower, upper, count, enumNames, description)

#define _procedure_(method)

#define _procedure1_(method,argType, argTypeDesc)

#define _procedure2_(method,argType1,argType2,argTypeDesc)

#define _procedure3_(method,argType1,argType2,argType3,argTypeDesc)

#define _procedure4_(method,argType1,argType2,argType3,argType4,argTypeDesc)

#define _procedure5_(method,argType1,argType2,argType3,argType4,argType5,argTypeDesc) 

#define _procedure6_(method,argType1,argType2,argType3,argType4,argType5,argType6,argTypeDesc) 


#define _function_(method,returnType) 

#define _function1_(method,returnType,argType,argTypeDesc) 

#define _function2_(method,returnType,argType1,argType2,argTypeDesc) 

#define _function3_(method,returnType,argType1,argType2,argType3,argTypeDesc) 

#define _function4_(method,returnType,argType1,argType2,argType3,argType4,argTypeDesc) 

#define _function5_(method,returnType,argType1,argType2,argType3,argType4,argType5,argTypeDesc) 

#define _function6_(method,returnType,argType1,argType2,argType3,argType4,argType5,argType6,argTypeDesc) 

#endif


#endif // _VCF_RTTIMACROS_H__

/**
$Id$
*/
