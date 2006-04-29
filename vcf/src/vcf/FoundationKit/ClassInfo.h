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
\class ClassInfo ClassInfo.h "vcf/FoundationKit/ClassInfo.h"
ClassInfo is used to simplify registering
classes with the FoundationKit's runtime ClassRegistry.
The class is derived from by using the macros below. It is
created on the stack, and the constructor will automatically
register the class, as well as any of the classes properties,
methods, and events that have been specified through the macros.
*/
template <class CLASS_TYPE> class ClassInfo  {
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
\class AbstractClassInfo ClassInfo.h "vcf/FoundationKit/ClassInfo.h"
*The AbstractClassInfo is used to simplify registering
*classes with the FoundationKit's runtime ClassRegistry.
*It is uses specifically with classes that are abstract,
*in other words are not supposed to be created, only derived from.
*The class is derived from by using the macros below. It is
*created on the stack, and the constructor will automatically
*register the class, as well as any of the classes properties,
*methods, and events that have been specified through the macros.
*/
template <class CLASS_TYPE> class AbstractClassInfo  {
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
\class InterfaceInfo ClassInfo.h "vcf/FoundationKit/ClassInfo.h"
The InterfaceInfo class serves bascially
the same purpose as the ClassInfo class.
It is used to register interfaces and their
methods with the
*/
template <class INTERFACE_TYPE> class InterfaceInfo  {
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




#ifdef VCF_RTTI


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


#define REGISTER_CLASSINFO( ClassType )

#define REGISTER_INTERFACEINFO(InterfaceType)

#define REGISTER_CLASSINFO_EXTERNAL( ClassType ) 

#define REGISTER_INTERFACEINFO_EXTERNAL( InterfaceType ) 


#endif //VCF_RTTI


#endif // _VCF_CLASSINFO_H__

/**
$Id$
*/
