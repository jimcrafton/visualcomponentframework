#ifndef _VCF_VCFRTTIIMPL_H__
#define _VCF_VCFRTTIIMPL_H__
//VCFRTTIImpl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
This header contains all the concrete template classes used for support the
VCF's RTTI API's
*/



namespace VCF   {





#ifdef VCF_RTTI

/**
\class EnumSetProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
This is a special class for handing a enum mask value that is the combination
of one or more other values.
*/
class FOUNDATIONKIT_API EnumSetProperty : public Property {
public:

	typedef uint32 (Object::*GetFunction)(void);
	typedef void (Object::*SetFunction)(const uint32& );

	EnumSetProperty( const String& typeName, GetFunction propGetFunction, int count, uint32* setArray, String* names ){
		init();

		typeName_ = typeName;
		getFunction_ = propGetFunction;
		setType( pdEnumMask );
		isReadOnly_ = true;

		for (int i=0;i<count;i++ ) {
			nameVals_[names[i]] = setArray[i];
		}
	};

	EnumSetProperty( const String& typeName, GetFunction propGetFunction, SetFunction propSetFunction,
					int count, uint32* setArray, String* names ){
		init();

		typeName_ = typeName;
		getFunction_ = propGetFunction;
		setFunction_ = propSetFunction;
		setType( pdEnumMask );

		for (int i=0;i<count;i++ ) {
			nameVals_[names[i]] = setArray[i];
		}
	};

	EnumSetProperty( const EnumSetProperty& prop ):
		Property( prop ){

		init();
		typeName_ = prop.typeName_;
		getFunction_ = prop.getFunction_;
		setFunction_ = prop.setFunction_;
		nameVals_ = prop.nameVals_;
	};

	virtual ~EnumSetProperty(){};

	virtual String getTypeClassName() {
		return typeName_;
	}


	void addAsString( const String& val ) {
		std::map<String,uint32>::iterator found = nameVals_.find( val );
		if ( found != nameVals_.end() ) {
			add( found->second );
		}
	}

	void removeAsString( const String& val ) {
		std::map<String,uint32>::iterator found = nameVals_.find( val );
		if ( found != nameVals_.end() ) {
			remove( found->second );
		}
	}

	void add( const uint32& val ) {
		uint32 tmp = value_;
		tmp |= val;
		value_ = tmp;
	}

	void remove( const uint32& val ) {
		uint32 tmp = value_;
		tmp &= ~val;
		value_ = tmp;
	}

	bool contains( const uint32& val )  {
		return (((uint32)value_) & val) ? true : false;
	}

	bool hasNames()  {
		return !nameVals_.empty();
	}

	virtual Property* clone(){
		return new EnumSetProperty(*this);
	};

	void init(){
		getFunction_ = NULL;
		setFunction_ = NULL;
	};

	virtual VariantData* get( Object* source ){
		if ( (NULL != getFunction_) && (NULL != source) ){
			value_ = (source->*getFunction_)();
			value_.type = getType();
			return &value_;
		}
		else {
			return NULL;
		}
	};

	virtual void set( Object* source, VariantData* value ){
		if ( (NULL != setFunction_) && (NULL != source) ){
			if ( true == isBound() ){
				VariantData* originalValue = get( source );
				PropertyChangeEvent changeEvent( source, originalValue, value );
				try {
					PropertyChanged.fireEvent( &changeEvent );

					(source->*setFunction_)( *value );
				}
				catch ( PropertyChangeException ){
					//do not call the set method
					//re-throw the exception ?

				}
			}
			else {
				(source->*setFunction_)( *value );
			}
		}
	};

	virtual void set( Object* source, const String& value ){

		String tmp = value;
		size_t pos = tmp.find( "," );

		while ( pos != VCF::String::npos ) {
			addAsString( tmp.substr( 0, pos ) );
			tmp.erase( 0, pos+1 );
			pos = tmp.find( "," );
		}
		if ( !tmp.empty() ) {
			addAsString( tmp );
		}
		VariantData newVal = value_;
		set( source, &newVal );
	};

	virtual String toString() {
		String result;

		VariantData* data = Property::get();
		if ( NULL != data ) {
			uint32 maskVal = *data;
			std::map<String,uint32>::iterator it = nameVals_.begin();
			while ( it != nameVals_.end() ) {
				if ( it->second & maskVal ) {
					if ( !result.empty() ) {
						result += ",";
					}
					result += it->first;
				}
				it ++;
			}
		}

		return result;
	}

	bool getNameValuesAsSet( std::vector<String>& names, std::vector<uint32>& values ) {
		std::map<String,uint32>::iterator it = nameVals_.begin();
		while ( it != nameVals_.end() ) {
			names.push_back( it->first );
			values.push_back( it->second );
			it ++;
		}

		return (!names.empty()) && (!values.empty());
	}

protected:
	String typeName_;
	GetFunction getFunction_;
	SetFunction setFunction_;
	std::map<String,uint32> nameVals_;
};




/**
*This is specific template class used to wrap the
*C++ enum type (ENUM_TYPE) to the Enum class.
*/
template <class ENUM_TYPE>
class TypedEnum : public Enum {
public:

	TypedEnum( const ENUM_TYPE& lower, const ENUM_TYPE& upper ){
		enum_ = lower;
		lower_ = (int)lower;
		upper_ = (int)upper;
		enumNames_.clear();
		namesAvailable_ = false;
	};

	TypedEnum( const ENUM_TYPE& lower, const ENUM_TYPE& upper, const uint32& enumNameCount, String* enumNames ){
		enum_ = lower;
		lower_ = (int)lower;
		upper_ = (int)upper;
		enumNames_.clear();
		if ( enumNameCount > 0 ){
			for ( uint32 i=0;i<enumNameCount;i++ ){
				enumNames_.push_back( enumNames[i] );
			}
		}
		namesAvailable_ = enumNames_.size() > 0 ? true : false;
	};

	virtual ~TypedEnum() {};

	virtual int next(){
		int i = (int)enum_;
		i++;
		if ( i > upper_ ){
			i = lower_;
		}
		enum_ = (ENUM_TYPE)i;
		return i;
	};

	virtual int begin(){
		enum_ = (ENUM_TYPE)lower_;
		return (int)enum_;
	};

	virtual int end(){
		enum_ = (ENUM_TYPE)upper_;
		return (int)enum_;
	};

	virtual int get(){
		return (int)enum_;
	};

	void set( const ENUM_TYPE& val ){
		enum_ = val;
	};

	virtual void set( const int& intVal ){
		enum_ = (ENUM_TYPE)intVal;
	}

	ENUM_TYPE getValAsEnum(){
		return enum_;
	};

	operator ENUM_TYPE (){
		return getValAsEnum();
	};

	TypedEnum<ENUM_TYPE>& operator=( const ENUM_TYPE& val ){
		set( val );
		return *this;
	};

	virtual void setFromString( const String& textVal ){
		if ( true == namesAvailable_ ){
			std::vector<String>::iterator it = enumNames_.begin();
			int i = 0;
			bool found = false;
			while ( it != enumNames_.end() ){
				if ( (*it) == textVal ){
					found = true;
					break;
				}
				i++;
				it++;
			}
			if ( true == found ){
				set( i );
			}
			else {
				Enum::setFromString( textVal );
			}
		}
		else {
			Enum::setFromString( textVal );
		}
	};

	virtual String toString(){
		String result = "";

		if ( true == namesAvailable_ ){
			int index = get();
			if ( (index >= lower_) && (index <= upper_) ) {
				result = enumNames_[index];
			}
		}
		else {
			result += get();
		}
		return result;
	};

private:
	ENUM_TYPE enum_;
	int lower_;
	int upper_;
	std::vector<String> enumNames_;
	bool namesAvailable_;
};












/**
\class TypedEventProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
Concrete template class for supporting event RTTI.
*/
template <typename SourceType, typename EventType>
class TypedEventProperty : public EventProperty {
public:

	TypedEventProperty( const String& eventClassName, const String& handlerClassName,
			const String& delegateName, DelegateMethod delegateMethod ):
			EventProperty(eventClassName,handlerClassName,delegateName,delegateMethod)	{}



	typedef void (Object::*HandlerMethod)(EventType*);


	virtual EventHandler* createEventHandler( Object* source, EventHandlerMethod method, const String& name ) {

		return new EventHandlerInstance<Object,EventType>( source, (HandlerMethod)method, name );
	}

	virtual EventProperty* clone() {
		return new TypedEventProperty<SourceType,EventType>(*this);
	}

	virtual bool isAbstract() {
		return false;
	}
};







/**
\class TypedProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Typed properties are designed to only work with Object derived classes.
*Many thanks go to Mario Motta (author VDK, mmotta@guest.net) for inspiring this from his
*VDKReadWriteValueProp class.
*
*@version 1.0
*@author Jim Crafton
*/
template <class PROPERTY>
class TypedProperty : public Property {
public:
	typedef PROPERTY (Object::*GetFunction)(void);
	typedef void (Object::*SetFunction)(const PROPERTY& );

	TypedProperty( GetFunction propGetFunction, const PropertyDescriptorType& propertyType ){
		init();

		getFunction_ = propGetFunction;
		setType( propertyType );
		isReadOnly_ = true;
	};

	TypedProperty( GetFunction propGetFunction, SetFunction propSetFunction,
		               const PropertyDescriptorType& propertyType ){
		init();

		getFunction_ = propGetFunction;
		setFunction_ = propSetFunction;
		setType( propertyType );
	};

	TypedProperty( const TypedProperty<PROPERTY>& prop ):
		Property( prop ){

		init();
		getFunction_ = prop.getFunction_;
		setFunction_ = prop.setFunction_;
	};

	virtual ~TypedProperty(){};

	virtual String getTypeClassName() {
		String result;
		VariantData* val = Property::get();
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

				default : {
					result = StringUtils::getClassNameFromTypeInfo( typeid(PROPERTY) );
				}
				break;

			}
		}
		return result;
	}

	virtual Property* clone(){
		return new TypedProperty<PROPERTY>(*this);
	};

	void init(){
		getFunction_ = NULL;
		setFunction_ = NULL;
	};

	virtual VariantData* get( Object* source ){
		if ( (NULL != getFunction_) && (NULL != source) ){
			value_ = (source->*getFunction_)();
			value_.type = getType();
			return &value_;
		}
		else {
			return NULL;
		}
	};

	virtual void set( Object* source, VariantData* value ){
		if ( (NULL != setFunction_) && (NULL != source) ){
			if ( true == isBound() ){
				VariantData* originalValue = get( source );
				PropertyChangeEvent changeEvent( source, originalValue, value );
				try {
					PropertyChanged.fireEvent( &changeEvent );

					(source->*setFunction_)( *value );
				}
				catch ( PropertyChangeException ){
					//do not call the set method
					//re-throw the exception ?

				}
			}
			else {
				(source->*setFunction_)( *value );
			}
		}
	};

protected:
	GetFunction getFunction_;
	SetFunction setFunction_;
};


/**
\class TypeDefProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*/
template <class PROPERTY>
class TypeDefProperty : public TypedProperty<PROPERTY> {
public:
	TypeDefProperty( _typename_ TypedProperty<PROPERTY>::GetFunction propGetFunction,
						const PropertyDescriptorType& propertyType,
						const String& typeDefClassName ): TypedProperty<PROPERTY>( propGetFunction, propertyType ) {

		typeDefClassName_ = typeDefClassName;
	}

	TypeDefProperty( _typename_ TypedProperty<PROPERTY>::GetFunction propGetFunction,
					_typename_ TypedProperty<PROPERTY>::SetFunction propSetFunction,
						const PropertyDescriptorType& propertyType, const String& typeDefClassName ):
							TypedProperty<PROPERTY>( propGetFunction, propSetFunction, propertyType )	{

		typeDefClassName_ = typeDefClassName;
	}

	TypeDefProperty( const TypeDefProperty<PROPERTY>& prop ):
		TypedProperty<PROPERTY>( prop ){
		typeDefClassName_ = prop.typeDefClassName_;
	};

	virtual ~TypeDefProperty(){};

	virtual String getTypeClassName() {
		return typeDefClassName_;
	}

	virtual Property* clone(){
		return new TypeDefProperty<PROPERTY>(*this);
	};

protected:
	String typeDefClassName_;
};

template <class PROPERTY>
class TypedObjectProperty : public Property {
public:
	typedef PROPERTY* (Object::*GetFunction)(void);
	typedef void (Object::*SetFunction)( PROPERTY* );

	TypedObjectProperty( GetFunction propGetFunction ){
		init();
		getFunction_ = propGetFunction;
		setType( pdObject );
		isReadOnly_ = true;
	};

	TypedObjectProperty( GetFunction propGetFunction, SetFunction propSetFunction ){
		init();

		getFunction_ = propGetFunction;
		setFunction_ = propSetFunction;
		setType( pdObject );
	};

	TypedObjectProperty( const TypedObjectProperty<PROPERTY>& prop ):
		Property( prop ){

		init();
		getFunction_ = prop.getFunction_;
		setFunction_ = prop.setFunction_;
	};

	virtual ~TypedObjectProperty(){};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(PROPERTY) );
	}

	virtual Property* clone(){
		return new TypedObjectProperty<PROPERTY>(*this);
	};

	void init(){
		getFunction_ = NULL;
		setFunction_ = NULL;
		setType( pdObject );
	};

	virtual VariantData* get( Object* source ){
		if ( (NULL != getFunction_) && (NULL != source) ){
			PROPERTY* propVal = (source->*getFunction_)();
			if ( NULL != propVal ) {
				value_ = dynamic_cast<Object*>( propVal );
			}
			else {
				value_ = (Object*)NULL;
			}
			value_.type = getType();
			return &value_;
		}
		else {
			return NULL;
		}
	};

	void set( Object* source, VariantData* value ){
		if ( (NULL != setFunction_) && (NULL != source) ){
			Object* object = *value;

			PROPERTY* propVal = NULL;
			if ( NULL != object ) {
				propVal = dynamic_cast<PROPERTY*>(object);
			}
			if ( true == isBound() ){
				VariantData* originalValue = get( source );
				PropertyChangeEvent changeEvent( source, originalValue, value );
				try {
					PropertyChanged.fireEvent( &changeEvent );
					(source->*setFunction_)( propVal );
				}
				catch ( PropertyChangeException ){
					//do not call the set method
					//re-throw the exception ?
				}
			}
			else {
				(source->*setFunction_)( propVal );
			}
		}
	};

protected:
	GetFunction getFunction_;
	SetFunction setFunction_;
};

/**
\class TypedObjectRefProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*/
template <class PROPERTY>
class TypedObjectRefProperty : public Property {
public:
	typedef PROPERTY& (Object::*GetFunction)(void);
	typedef void (Object::*SetFunction)( const PROPERTY& );

	TypedObjectRefProperty( GetFunction propGetFunction ){
		init();
		getFunction_ = propGetFunction;
		setType( pdObject );
		isReadOnly_ = true;
	};

	TypedObjectRefProperty( GetFunction propGetFunction, SetFunction propSetFunction ){
		init();

		getFunction_ = propGetFunction;
		setFunction_ = propSetFunction;
		setType( pdObject );
	};

	TypedObjectRefProperty( const TypedObjectProperty<PROPERTY>& prop ):
		Property( prop ){

		init();
		getFunction_ = prop.getFunction_;
		setFunction_ = prop.setFunction_;
	};

	virtual ~TypedObjectRefProperty(){};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(PROPERTY) );
	}

	virtual Property* clone(){
		return new TypedObjectRefProperty<PROPERTY>(*this);
	};

	void init(){
		getFunction_ = NULL;
		setFunction_ = NULL;
		setType( pdObject );
	};

	virtual VariantData* get( Object* source ){
		if ( (NULL != getFunction_) && (NULL != source) ){

			value_ = (source->*getFunction_)();
			value_.type = getType();
			return &value_;
		}
		else {
			return NULL;
		}
	};

	void set( Object* source, VariantData* value ){
		if ( (NULL != setFunction_)  ){
			Object* object = *value;
			if ( true == isBound() ){
				VariantData* originalValue = get( source );
				PropertyChangeEvent changeEvent( source, originalValue, value );
				try {
					PropertyChanged.fireEvent( &changeEvent );
					(source->*setFunction_)( (PROPERTY&)*object );
				}
				catch ( PropertyChangeException ){
					//do not call the set method
					//re-throw the exception ?
				}
			}
			else {
				(source->*setFunction_)( (PROPERTY&)*object );
			}
		}
	};

protected:
	GetFunction getFunction_;
	SetFunction setFunction_;
};

/**
\class TypedEnumProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*/
template <class ENUM_PROPERTY>
class TypedEnumProperty : public Property {
public:
	typedef ENUM_PROPERTY (Object::*GetFunction)(void);
	typedef void (Object::*SetFunction)( const ENUM_PROPERTY& );

	TypedEnumProperty( GetFunction propGetFunction, const ENUM_PROPERTY& lower, const ENUM_PROPERTY& upper ){
		init();
		getFunction_ = propGetFunction;
		enum_ = new TypedEnum<ENUM_PROPERTY>(lower,upper);
		lower_ = lower;
		upper_ = upper;
		setType( pdEnum );
		isReadOnly_ = true;
	};

	TypedEnumProperty( GetFunction propGetFunction, SetFunction propSetFunction, const ENUM_PROPERTY& lower, const ENUM_PROPERTY& upper ){
		init();
		lower_ = lower;
		upper_ = upper;
		getFunction_ = propGetFunction;
		setFunction_ = propSetFunction;
		enum_ = new TypedEnum<ENUM_PROPERTY>(lower,upper);
		setType( pdEnum );
	};

	TypedEnumProperty( GetFunction propGetFunction, SetFunction propSetFunction,
		               const ENUM_PROPERTY& lower, const ENUM_PROPERTY& upper,
					   const uint32& enumNameCount,
					   String* enumNames ){
		init();
		lower_ = lower;
		upper_ = upper;
		getFunction_ = propGetFunction;
		setFunction_ = propSetFunction;
		enumNameCount_ = enumNameCount;
		enumNames_ = enumNames;
		enum_ = new TypedEnum<ENUM_PROPERTY>(lower,upper, enumNameCount, enumNames );
		setType( pdEnum );
	};

	TypedEnumProperty( const TypedEnumProperty<ENUM_PROPERTY>& prop ):
		Property( prop ){

		init();
		getFunction_ = prop.getFunction_;
		setFunction_ = prop.setFunction_;
		enumNameCount_ = prop.enumNameCount_;
		enumNames_ = prop.enumNames_;
		lower_ = prop.lower_;
		upper_ = prop.upper_;
		if ( 0 < enumNameCount_ ){
			enum_ = new TypedEnum<ENUM_PROPERTY>( lower_,upper_, enumNameCount_, enumNames_ );
		}
		else{
			enum_ = new TypedEnum<ENUM_PROPERTY>( lower_,upper_ );
		}
		setType( pdEnum );
		setName( prop.getName() );
		setDisplayName( prop.getDisplayName() );
		setDescription( prop.getDescription() );
	};

	virtual ~TypedEnumProperty(){
		delete enum_;
	};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(ENUM_PROPERTY) );
	}

	virtual Property* clone(){
		return new TypedEnumProperty<ENUM_PROPERTY>(*this);
	};

	void init(){
		getFunction_ = NULL;
		setFunction_ = NULL;
		setType( pdEnum );
		enumNameCount_ = 0;
	};

	virtual VariantData* get( Object* source ){
		if ( (NULL != getFunction_) && (NULL != source) ){
			enum_->set( (source->*getFunction_)() );
			value_ = enum_;
			value_.type = getType();
			return &value_;
		}
		else {
			return NULL;
		}
	};

	virtual void set( Object* source, VariantData* value ){
		if ( (NULL != setFunction_) && (NULL != source) ){
			Enum* e = *value;
			ENUM_PROPERTY enumVal = (ENUM_PROPERTY)e->get();

			if ( true == isBound() ){
				VariantData* originalValue = get( source );
				PropertyChangeEvent changeEvent( source, originalValue, value );
				try {
					PropertyChanged.fireEvent( &changeEvent );
					(source->*setFunction_)( enumVal );
				}
				catch ( PropertyChangeException ){
					//do not call the set method
					//re-throw the exception ?
				}
			}
			else {
				(source->*setFunction_)( enumVal );
			}
		}
	};

protected:
	GetFunction getFunction_;
	SetFunction setFunction_;
	TypedEnum<ENUM_PROPERTY>* enum_;
	ENUM_PROPERTY lower_;
	ENUM_PROPERTY upper_;
	uint32 enumNameCount_;
	String* enumNames_;
};

/**
\class TypedCollectionProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*TypedCollectionProperty represents a type safe wrapper around properties that
*are enumerations of items.
*/
template <typename ValueType,typename KeyType=uint32>
class TypedCollectionProperty : public Property {
public:
	
	typedef void (Object::*AddFunction)( ValueType );
	typedef void (Object::*InsertFunction)( const KeyType&, ValueType );
	typedef void (Object::*DeleteFunction)( const KeyType& );
	typedef uint32 (Object::*GetSizeFunction)();

	typedef ValueType (Object::*GetFunction)( const KeyType& );
	typedef void (Object::*SetFunction)( const KeyType&, ValueType, bool );

	TypedCollectionProperty( GetFunction getFunc, SetFunction setFunc, 
							AddFunction addFunc, InsertFunction insertFunc,
							DeleteFunction deleteFunc, GetSizeFunction getSizeFunc,
							const PropertyDescriptorType& propertyType ){

		init();
		getFunc_ = getFunc;
		setFunc_ = setFunc;
		addFunc_ = addFunc;
		insertFunc_ = insertFunc;
		deleteFunc_ = deleteFunc;
		getSizeFunc_ = getSizeFunc;
		setType( propertyType );
	};

	TypedCollectionProperty( GetFunction getFunc, SetFunction setFunc,
							 const PropertyDescriptorType& propertyType ){

		init();
		getFunc_ = getFunc;
		setFunc_ = setFunc;
		setType( propertyType );
	};


	TypedCollectionProperty( const TypedCollectionProperty<ValueType,KeyType>& prop ):
		Property( prop ){

		init();
		getFunc_ = prop.getFunc_;
		setFunc_ = prop.setFunc_;
		addFunc_ = prop.addFunc_;
		insertFunc_ = prop.insertFunc_;
		deleteFunc_ = prop.deleteFunc_;
		getSizeFunc_ = prop.getSizeFunc_;
	};

	void init(){
		getFunc_ = NULL;
		setFunc_ = NULL;
		isCollection_ = true;
		isReadOnly_ = true;
		addFunc_ = NULL;
		insertFunc_ = NULL;
		deleteFunc_ = NULL;
		getSizeFunc_ = NULL;
	};

	virtual ~TypedCollectionProperty(){};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(ValueType) );
	}

	virtual VariantData* get( Object* source ){
		return NULL;
	};

	virtual void set( Object* source, VariantData* value ){
		//no-op
	};

	virtual Property* clone(){
		return new TypedCollectionProperty<ValueType,KeyType>(*this);
	};

	virtual uint32 getCollectionCount( Object* source ) {
		uint32 result = 0;
		if ( (NULL != source) && (NULL != getSizeFunc_) ){
			
			result = (source->*getSizeFunc_)();
		}

		return result;
	}
	
	virtual VariantData* getAtKey( const VariantData& key, Object* source ){
		VariantData* result = NULL;
		if ( (NULL != source) && (NULL != getFunc_) ){
			try {
				value_.setNull();
				value_ = (source->*getFunc_)( (KeyType)key );

				if ( !value_.isNull() ) {
					result = &value_;
				}
			}
			catch ( BasicException& ) {
				
			}
		}

		return result;
	};

	virtual void setAtKey( const VariantData& key, VariantData* value, Object* source, bool addMissingValues ){
		if ( (NULL != value) && (NULL != source) && (NULL != setFunc_) ){			
			(source->*setFunc_)( (KeyType)key, (ValueType)(*value), addMissingValues );
		}
	};

	virtual void add( Object* source, VariantData* value ){
		if ( (NULL != value) && (NULL != addFunc_) ){
			ValueType valToAdd = (ValueType)(*value);
			(source->*addFunc_)( valToAdd );
		}
	};

	virtual void insert( const VariantData& key, VariantData* value, Object* source ){
		if ( (NULL != value) && (NULL != source) && (NULL != insertFunc_) ){
			ValueType valToInsert = (ValueType)(*value);
			(source->*insertFunc_)( (KeyType)key, valToInsert );
		}
	};
	
	virtual void remove( const VariantData& key, Object* source ){
		if ( (NULL != source) && (NULL != deleteFunc_) ){
			(source->*deleteFunc_)( (KeyType)key );
		}
	};

	virtual bool collectionSupportsEditing() {
		return addFunc_ == NULL;
	}
private:
	GetFunction getFunc_;
	SetFunction setFunc_;
	AddFunction addFunc_;
	InsertFunction insertFunc_;
	DeleteFunction deleteFunc_;
	GetSizeFunction getSizeFunc_;
};

/**
\class TypedObjectCollectionProperty VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*TypedCollectionProperty represents a type safe wrapper around properties that
*are enumerations of Object* derived items.
*/
template <typename ValueType,typename KeyType=uint32>
class TypedObjectCollectionProperty : public Property {
public:
	
	typedef ValueType* ObjectType;
	typedef void (Object::*AddFunction)( ObjectType );
	typedef void (Object::*InsertFunction)( const KeyType&, ObjectType );
	typedef void (Object::*DeleteFunction)( const KeyType& );
	typedef uint32 (Object::*GetSizeFunction)();

	typedef ObjectType (Object::*GetFunction)( const KeyType& );
	typedef void (Object::*SetFunction)( const KeyType&, ObjectType, bool );

	TypedObjectCollectionProperty( GetFunction getFunc, SetFunction setFunc, 
							AddFunction addFunc, InsertFunction insertFunc,
							DeleteFunction deleteFunc, GetSizeFunction getSizeFunc,
							const PropertyDescriptorType& propertyType ){

		init();
		getFunc_ = getFunc;
		setFunc_ = setFunc;
		addFunc_ = addFunc;
		insertFunc_ = insertFunc;
		deleteFunc_ = deleteFunc;
		getSizeFunc_ = getSizeFunc;
		setType( propertyType );
	};

	TypedObjectCollectionProperty( GetFunction getFunc, SetFunction setFunc,
							 const PropertyDescriptorType& propertyType ){

		init();
		getFunc_ = getFunc;
		setFunc_ = setFunc;
		setType( propertyType );
	};


	TypedObjectCollectionProperty( const TypedObjectCollectionProperty<ValueType,KeyType>& prop ):
		Property( prop ){

		init();
		getFunc_ = prop.getFunc_;
		setFunc_ = prop.setFunc_;
		addFunc_ = prop.addFunc_;
		insertFunc_ = prop.insertFunc_;
		deleteFunc_ = prop.deleteFunc_;
		getSizeFunc_ = prop.getSizeFunc_;
	};

	void init(){
		getFunc_ = NULL;
		setFunc_ = NULL;
		isCollection_ = true;
		isReadOnly_ = true;
		addFunc_ = NULL;
		insertFunc_ = NULL;
		deleteFunc_ = NULL;
		getSizeFunc_ = NULL;
	};

	virtual ~TypedObjectCollectionProperty(){};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(ValueType) );
	}

	virtual VariantData* get( Object* source ){
		return NULL;
	};

	virtual void set( Object* source, VariantData* value ){
		//no-op
	};

	virtual Property* clone(){
		return new TypedObjectCollectionProperty<ValueType,KeyType>(*this);
	};

	virtual uint32 getCollectionCount( Object* source ) {
		uint32 result = 0;
		if ( (NULL != source) && (NULL != getSizeFunc_) ){
			
			result = (source->*getSizeFunc_)();
		}

		return result;
	}
	
	virtual VariantData* getAtKey( const VariantData& key, Object* source ){
		VariantData* result = NULL;
		if ( (NULL != source) && (NULL != getFunc_) ){
			try {
				value_.setNull();
				value_ = (source->*getFunc_)( (KeyType)key );

				if ( !value_.isNull() ) {
					result = &value_;
				}
			}
			catch ( BasicException& ) {
				
			}
		}

		return result;
	};

	virtual void setAtKey( const VariantData& key, VariantData* value, Object* source, bool addMissingValues ){
		if ( (NULL != value) && (NULL != source) && (NULL != setFunc_) ){			
			(source->*setFunc_)( (KeyType)key, (ObjectType)(Object*)(*value), addMissingValues );
		}
	};

	virtual void add( Object* source, VariantData* value ){
		if ( (NULL != value) && (NULL != addFunc_) ){
			ObjectType valToAdd = (ObjectType)(Object*)(*value);
			(source->*addFunc_)( valToAdd );
		}
	};

	virtual void insert( const VariantData& key, VariantData* value, Object* source ){
		if ( (NULL != value) && (NULL != source) && (NULL != insertFunc_) ){
			ObjectType valToInsert = (ObjectType)(Object*)(*value);
			(source->*insertFunc_)( (KeyType)key, valToInsert );
		}
	};
	
	virtual void remove( const VariantData& key, Object* source ){
		if ( (NULL != source) && (NULL != deleteFunc_) ){
			(source->*deleteFunc_)( (KeyType)key );
		}
	};

	virtual bool collectionSupportsEditing() {
		return addFunc_ == NULL;
	}
private:
	GetFunction getFunc_;
	SetFunction setFunc_;
	AddFunction addFunc_;
	InsertFunction insertFunc_;
	DeleteFunction deleteFunc_;
	GetSizeFunction getSizeFunc_;
};













/**
\class TypedMethod VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Base template class for methods that do NOT return values
*/
template <typename SOURCE_TYPE>
class TypedMethod : public Method {
public:

	typedef SOURCE_TYPE SrcType;

	TypedMethod( const String& argTypes="", SOURCE_TYPE* source=NULL ){
		source_ = source;
		argTypes_ = argTypes;
		objSource_ = NULL;
	}


	TypedMethod( const TypedMethod<SOURCE_TYPE>& method ) : Method() {
		*this = method;
	}

	TypedMethod<SOURCE_TYPE>& operator=( const TypedMethod<SOURCE_TYPE>& rhs ) {
		source_ = rhs.source_;
		argTypes_ = rhs.argTypes_;
		objSource_ = rhs.objSource_;
		argCount_ = rhs.argCount_;
		name_ = rhs.name_;
		hasReturnValue_ = rhs.hasReturnValue_;
		return *this;
	}

	virtual ~TypedMethod(){	}

	virtual Object* getSource(){
		return objSource_;
	}

	virtual void setSource( Object* source ){
		//does the source actually support this interface/class ?
		source_ = dynamic_cast<SOURCE_TYPE*>( source );
		objSource_ = NULL;
		if ( NULL != source_ ){
			objSource_ = source;
		}
	}

protected:

	SOURCE_TYPE* source_;
	Object* objSource_;
};


/**
\class TypedMethodReturn VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Base template class for methodsthat DO return values
*/

template <typename SOURCE_TYPE, typename RETURN_TYPE>
class TypedMethodReturn : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef RETURN_TYPE ReturnType;

	TypedMethodReturn( const String& argTypes="", SOURCE_TYPE* source=NULL ):
		TypedMethod<SOURCE_TYPE>( argTypes, source ) {
		hasReturnValue_ = true;
	}

	TypedMethodReturn( const TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>& rhs ) {
		hasReturnValue_ = true;
		*this = rhs;
	}

	TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>& operator=( const TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>& rhs ) {
		TypedMethod<SOURCE_TYPE>::operator =(rhs);
		return *this;
	}

	virtual ~TypedMethodReturn(){}

protected:
};


/**
\class TypedMethodArg0 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template class for methods have 0 arguments
*/
template <class SOURCE_TYPE>
class TypedMethodArg0 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef void (SOURCE_TYPE::*MemberFunc)();

	TypedMethodArg0( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 0;
		methodPtr_=methodPtr;
	}

	TypedMethodArg0( const TypedMethodArg0<SOURCE_TYPE>& method ) : TypedMethod<SOURCE_TYPE>( method )  {
		*this = method;
	}

	TypedMethodArg0<SOURCE_TYPE>& operator=( const TypedMethodArg0<SOURCE_TYPE>& rhs ) {
		TypedMethod<SOURCE_TYPE>::operator =(rhs);
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual ~TypedMethodArg0(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 0 == argCount_ ) {
				(source_->*methodPtr_)();
			}
		}

		return VariantData::null();
	}

	virtual Method* clone() {
		return new TypedMethodArg0<SOURCE_TYPE>(*this);
	}

protected:
	MemberFunc methodPtr_;
};

/**
\class TypedMethodArg1 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template class for methods have 1 argument
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE>
class TypedMethodArg1 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef ARG1_TYPE Argument1;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1);


	TypedMethodArg1( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 1;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg1( const TypedMethodArg1<SOURCE_TYPE,ARG1_TYPE>& method ) :
        TypedMethod<SOURCE_TYPE>( method ) {
		*this = method;
	}


	TypedMethodArg1<SOURCE_TYPE,ARG1_TYPE>& operator=( const TypedMethodArg1<SOURCE_TYPE,ARG1_TYPE>& rhs ) {
		TypedMethod<SOURCE_TYPE>::operator =(rhs);
		methodPtr_ = rhs.methodPtr_;
		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg1<SOURCE_TYPE,ARG1_TYPE>(*this);
	}

	virtual ~TypedMethodArg1(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 1 == argCount_ ) {
				(source_->*methodPtr_)( (Argument1) *(arguments[0]) );
			}
		}

		return VariantData::null();
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg2 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Accepts methds with 2 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE >
class TypedMethodArg2 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2);

	TypedMethodArg2( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 2;
		methodPtr_ = methodPtr;

	}

	TypedMethodArg2( const TypedMethodArg2<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE>& method ) : TypedMethod<SOURCE_TYPE>( method )  {
		*this = method;
	}

	TypedMethodArg2<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE>& operator=( const TypedMethodArg2<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE>& rhs ) {
		TypedMethod<SOURCE_TYPE>::operator =(rhs);

		methodPtr_ = rhs.methodPtr_;
		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg2<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE>(*this);
	}

	virtual ~TypedMethodArg2(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 2 == argCount_ ) {
				(source_->*methodPtr_)(	(Argument1)*(arguments[0]),
											(Argument2)*(arguments[1])		);
			}
		}

		return VariantData::null();
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg3 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Accepts methds with 3 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE>
class TypedMethodArg3 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3);

	TypedMethodArg3( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 3;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg3( const TypedMethodArg3<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>& method ):
        TypedMethod<SOURCE_TYPE>( method )  {
		*this = method;
	}

	TypedMethodArg3<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>& operator=( const TypedMethodArg3<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>& rhs ) {

		TypedMethod<SOURCE_TYPE>::operator =(rhs);

		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg3<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>(*this);
	}

	virtual ~TypedMethodArg3(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 3 == argCount_ ) {
				(source_->*methodPtr_)(	(Argument1)*(arguments[0]),
											(Argument2)*(arguments[1]),
											(Argument3)*(arguments[2])		);
			}
		}

		return VariantData::null();
	}
protected:
	MemberFunc methodPtr_;
};



/**
\class TypedMethodArg4 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Accepts methds with 4 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE, typename ARG4_TYPE>
class TypedMethodArg4 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;
	typedef ARG4_TYPE Argument4;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4);

	typedef TypedMethodArg4<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE> TypedMethodArg4Type;

	TypedMethodArg4( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 4;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg4( const TypedMethodArg4Type& method ) :
        TypedMethod<SOURCE_TYPE>( method ){
		*this = method;
	}

	TypedMethodArg4Type& operator=( const TypedMethodArg4Type& rhs ) {

		TypedMethod<SOURCE_TYPE>::operator =(rhs);

		methodPtr_ = rhs.methodPtr_;

		return *this;
	}


	virtual Method* clone() {
		return new TypedMethodArg4Type(*this);
	}


	virtual ~TypedMethodArg4(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 4 == argCount_ ) {
				(source_->*methodPtr_)(	(Argument1)*(arguments[0]),
											(Argument2)*(arguments[1]),
											(Argument3)*(arguments[2]),
											(Argument4)*(arguments[3])		);
			}
		}

		return VariantData::null();
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg5 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Accepts methds with 5 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE>
class TypedMethodArg5 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;
	typedef ARG4_TYPE Argument4;
	typedef ARG5_TYPE Argument5;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5);

	typedef TypedMethodArg5<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE> TypedMethodArg5Type;

	TypedMethodArg5( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 5;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg5( const TypedMethodArg5Type& method ) :
        TypedMethod<SOURCE_TYPE>( method ) {

		*this = method;
	}

	TypedMethodArg5Type& operator=( const TypedMethodArg5Type& rhs ) {

		TypedMethod<SOURCE_TYPE>::operator =( rhs );

		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg5Type( *this );
	}

	virtual ~TypedMethodArg5(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 5 == argCount_ ) {
				(source_->*methodPtr_)(	(Argument1)*(arguments[0]),
											(Argument2)*(arguments[1]),
											(Argument3)*(arguments[2]),
											(Argument4)*(arguments[3]),
											(Argument5)*(arguments[4])		);
			}
		}

		return VariantData::null();
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg6 VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Accepts methds with 6 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE, typename ARG6_TYPE>
class TypedMethodArg6 : public TypedMethod<SOURCE_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;
	typedef ARG4_TYPE Argument4;
	typedef ARG5_TYPE Argument5;
	typedef ARG6_TYPE Argument6;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5, ARG5_TYPE arg6);

	typedef TypedMethodArg6<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE,ARG6_TYPE> TypedMethodArg6Type;


	TypedMethodArg6( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 6;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg6( const TypedMethodArg6Type& method ) :
        TypedMethod<SOURCE_TYPE>( method ) {
		TypedMethod<SOURCE_TYPE>::operator =( method ); /* was rhs instead of method (why??) */

		methodPtr_ = method.methodPtr_; /* was rhs instead of method (why??) */
		*this = method;
	}

	virtual Method* clone() {
		return new TypedMethodArg6Type(*this);
	}

	TypedMethodArg6Type& operator=( const TypedMethodArg6Type& rhs ) {

		return *this;
	}

	virtual ~TypedMethodArg6(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 6 == argCount_ ) {
				(source_->*methodPtr_)(	(Argument1)*(arguments[0]),
											(Argument2)*(arguments[1]),
											(Argument3)*(arguments[2]),
											(Argument4)*(arguments[3]),
											(Argument5)*(arguments[4]),
											(Argument6)*(arguments[5])		);
			}
		}

		return VariantData::null();
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg0Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 0 argument and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE>
class TypedMethodArg0Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)();

	typedef TypedMethodArg0Return<SOURCE_TYPE,RETURN_TYPE> TypedMethodArg0ReturnType;


	TypedMethodArg0Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 0;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg0Return( const TypedMethodArg0ReturnType& method ):
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method ) {
		*this = method;
	}

	TypedMethodArg0ReturnType& operator=( const TypedMethodArg0ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;
		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg0ReturnType(*this);
	}

	virtual ~TypedMethodArg0Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;
		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 0 == argCount_ ) {
				returnVal = (source_->*methodPtr_)();
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg1Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 1 argument and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE>
class TypedMethodArg1Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef ARG1_TYPE Argument1;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1);

	typedef TypedMethodArg1Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE> TypedMethodArg1ReturnType;


	TypedMethodArg1Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 1;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg1Return( const TypedMethodArg1ReturnType& method ) :
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method ) {
		*this = method;
	}

	TypedMethodArg1ReturnType& operator=( const TypedMethodArg1ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );

		methodPtr_ = rhs.methodPtr_;
		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg1ReturnType( *this );
	}


	virtual ~TypedMethodArg1Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 1 == argCount_ ) {
				returnVal = (source_->*methodPtr_)((Argument1)*(arguments[0]));
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg2Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 2 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE>
class TypedMethodArg2Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2);

	typedef TypedMethodArg2Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE, ARG2_TYPE> TypedMethodArg2ReturnType;



	TypedMethodArg2Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 2;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg2Return( const TypedMethodArg2ReturnType& method ) :
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method ) {
		*this = method;
	}

	TypedMethodArg2ReturnType& operator=( const TypedMethodArg2ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg2ReturnType( *this );
	}

	virtual ~TypedMethodArg2Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;
		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 2 == argCount_ ) {
				returnVal = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]) );
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg3Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 3 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE>
class TypedMethodArg3Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3);

	typedef TypedMethodArg3Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE, ARG2_TYPE,ARG3_TYPE> TypedMethodArg3ReturnType;

	TypedMethodArg3Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 3;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg3Return( const TypedMethodArg3ReturnType& method )  :
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method ) {
		*this = method;
	}

	TypedMethodArg3ReturnType& operator=( const TypedMethodArg3ReturnType& rhs )  {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg3ReturnType( *this );
	}


	virtual ~TypedMethodArg3Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 3 == argCount_ ) {
				returnVal = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]) );
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg4Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 4 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE>
class TypedMethodArg4Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;
	typedef ARG4_TYPE Argument4;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4);

	typedef TypedMethodArg4Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE, ARG2_TYPE,ARG3_TYPE,ARG4_TYPE> TypedMethodArg4ReturnType;


	TypedMethodArg4Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 4;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg4Return( const TypedMethodArg4ReturnType& method ) :
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method )  {
		*this = method;
	}

	TypedMethodArg4ReturnType& operator=( const TypedMethodArg4ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg4ReturnType( *this );
	}


	virtual ~TypedMethodArg4Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 4 == argCount_ ) {
				returnVal = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]),
														(Argument4)*(arguments[3]) );
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};


/**
\class TypedMethodArg5Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 5 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE>
class TypedMethodArg5Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;
	typedef ARG4_TYPE Argument4;
	typedef ARG5_TYPE Argument5;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5);

	typedef TypedMethodArg5Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE, ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE> TypedMethodArg5ReturnType;



	TypedMethodArg5Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 5;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg5Return( const TypedMethodArg5ReturnType& method ) :
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method )  {
		*this = method;
	}

	TypedMethodArg5ReturnType& operator=( const TypedMethodArg5ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg5ReturnType( *this );
	}


	virtual ~TypedMethodArg5Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 5 == argCount_ ) {
				returnVal = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]),
														(Argument4)*(arguments[3]),
														(Argument5)*(arguments[4]) );
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};



/**
\class TypedMethodArg6Return VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*Method template for methods with 6 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE, typename ARG6_TYPE>
class TypedMethodArg6Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	#if defined(VCF_MINGW) || defined(VCF_GCC)
	using  TypedMethod<SOURCE_TYPE>::hasReturnValue_;
	using  TypedMethod<SOURCE_TYPE>::argCount_;
	using  TypedMethod<SOURCE_TYPE>::objSource_;
	using  TypedMethod<SOURCE_TYPE>::source_;
	using  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::returnVal_;
	#endif

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;
	typedef ARG4_TYPE Argument4;
	typedef ARG5_TYPE Argument5;
	typedef ARG6_TYPE Argument6;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5, ARG6_TYPE arg6);

	typedef TypedMethodArg6Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE, ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE,ARG6_TYPE> TypedMethodArg6ReturnType;


	TypedMethodArg6Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 6;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg6Return( const TypedMethodArg6ReturnType& method ) :
        TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( method )  {
		*this = method;
	}

	TypedMethodArg6ReturnType& operator=( const TypedMethodArg6ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg6ReturnType( *this );
	}

	virtual ~TypedMethodArg6Return(){	}

	virtual VariantData invoke( VariantData** arguments,
								 Object* source=NULL ){

		VariantData returnVal;

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 6 == argCount_ ) {
				returnVal = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]),
														(Argument4)*(arguments[3]),
														(Argument5)*(arguments[4]),
														(Argument6)*(arguments[5]) );
			}
		}

		return returnVal;
	}
protected:
	MemberFunc methodPtr_;
};




template <typename FieldType>
class TypedField : public Field {
public:
	typedef FieldType Type;
	typedef FieldType* TypePtr;


	TypedField():field_(NULL),fieldOffset_(0) {

	}

	TypedField( const String& name, uint32 fieldOffset ):field_(NULL),fieldOffset_(fieldOffset) {
		setName( name );
	}

	TypedField( const TypedField& rhs ):Field(rhs),field_(NULL),fieldOffset_(rhs.fieldOffset_)  {

	}

	virtual Field* clone() {
		return new TypedField( *this );
	}

	virtual uint32 getFieldSize() {
		return sizeof( Type );
	}

	virtual String getFieldTypeName() {
		return typeid( Type ).name();
	}


	virtual VariantData* get( Object* source ) {
		if ( NULL == source ) {
			return NULL;
		}

		field_ = (TypePtr)(((char*)source) + fieldOffset_);

		val_ = *field_;

		return &val_;
	}

	virtual void set( Object* source, VariantData* data )	{
		if ( NULL == source ) {
			return;
		}

		field_ = (TypePtr)(((char*)source) + fieldOffset_);

		val_ = *data;


		*field_ = val_;
	}

	VariantData val_;
	TypePtr field_;
	uint32 fieldOffset_;
};


/**
\class TypedObjectField VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*/
template <typename FieldType>
class TypedObjectField : public Field {
public:
	typedef FieldType Type;
	typedef FieldType* TypePtr;


	TypedObjectField():field_(NULL),fieldOffset_(0) {

	}

	TypedObjectField( const String& name, uint32 fieldOffset ):field_(NULL),fieldOffset_(fieldOffset) {
		setName( name );
	}

	TypedObjectField( const TypedObjectField& rhs ):Field(rhs),field_(NULL),fieldOffset_(rhs.fieldOffset_)  {

	}

	virtual Field* clone() {
		return new TypedObjectField( *this );
	}

	virtual uint32 getFieldSize() {
		return sizeof( Type );
	}

	virtual String getFieldTypeName() {
		return typeid( Type ).name();
	}


	virtual VariantData* get( Object* source ) {
		if ( NULL == source ) {
			return NULL;
		}

		field_ = (TypePtr)(((char*)source) + fieldOffset_);

		val_ = *field_;

		return &val_;
	}

	virtual void set( Object* source, VariantData* data )	{
		if ( NULL == source ) {
			return;
		}

		field_ = (TypePtr)(((char*)source) + fieldOffset_);

		val_ = *data;

		*field_ = (Type)(Object*)val_;
	}

	VariantData val_;
	TypePtr field_;
	uint32 fieldOffset_;
};



/**
\class TypedInterfaceClass VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*TypedInterfaceClass documentation
*/
template<class INTERFACE_TYPE>
class TypedInterfaceClass : public InterfaceClass {
public:
	TypedInterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName ) :
		InterfaceClass( interfaceName, interfaceID, superInterfaceName ) {
	}

	virtual ~TypedInterfaceClass(){};

	virtual bool compareObject( Object* object )const{
		bool result = false;
		try {
			if ( typeid(*object) == typeid(INTERFACE_TYPE) ){
				result = true;
			}
		}
		catch (...){
			throw ClassNotFound();
		}
		return result;
	};

};


/**
\class TypedImplementedInterfaceClass VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*TypedImplementedInterfaceClass documentation
*/
template<class INTERFACE_TYPE, class IMPLEMENTER_TYPE>
class TypedImplementedInterfaceClass : public ImplementedInterfaceClass {
public:
	TypedImplementedInterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName ) :
		ImplementedInterfaceClass( interfaceName, interfaceID, superInterfaceName ) {

	}

	virtual ~TypedImplementedInterfaceClass(){};

	virtual Object* createImplementingInstance() {
		return new IMPLEMENTER_TYPE();
	}

	virtual void* createInterfaceInstance() {
		void* result = NULL;

		IMPLEMENTER_TYPE* implementerInstance = new IMPLEMENTER_TYPE();
		INTERFACE_TYPE* interfaceInstance = dynamic_cast<INTERFACE_TYPE*>( implementerInstance );

		result = (void*)interfaceInstance;
		return result;
	}


	virtual bool compareObject( Object* object )const{
		bool result = false;
		try {
			if ( typeid(*object) == typeid(INTERFACE_TYPE) ){
				result = true;
			}
		}
		catch (...){
			throw ClassNotFound();
		}
		return result;
	};
};












/**
\class TypedClass VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*TypedClass represents a specific instance of a Class. The CLASS_TYPE
is used to specify the Object the Class represents. So TypedClass<Rect> is
*used to represent the Class for a Rect instance.
*
*@author Jim Crafton
*@version 1.0
*/
template <class CLASS_TYPE>
class TypedClass : public Class
{
public:
	TypedClass( const String& className, const String& classID, const String& superClass ):
		Class( className, classID, superClass ){

	};

	virtual ~TypedClass(){

	};

	static TypedClass<CLASS_TYPE>* create(const String& className, const String& classID, const String& superClass) {
		TypedClass<CLASS_TYPE>* result = new TypedClass<CLASS_TYPE>(className, classID, superClass);
		return result;
	}

	/**
	*creates a new instance of type CLASS_TYPE and assigns it to the
	*pointer represented by the objectInstance argument.
	*@param Object the pointer to the newly created instance.
	*/
	virtual Object* createInstance() const {
		return new CLASS_TYPE();
	};


	virtual bool compareObject( Object* object )const{
		bool result = false;
		try {
			if ( typeid(*object) == typeid(CLASS_TYPE) ){
				result = true;
			}
		}
		catch (...){
			throw ClassNotFound();
		}
		return result;
	};

};

/**
\class TypedAbstractClass VCFRTTIImpl.h "vcf/FoundationKit/VCFRTTIImpl.h"
*TypedAbstractClass is used to represent abstract classes that cannot be instantiated
*due to virtual pure methods, but must be represented in the class hierarchy because
*they are derived from by other child classes.
*
*@author Jim Crafton
*@version 1.0
*/
template <class CLASS_TYPE>
class TypedAbstractClass : public Class
{
public:
	TypedAbstractClass( const String& className, const String& classID, const String& superClass ):
		Class( className, classID, superClass ){

	};

	virtual ~TypedAbstractClass(){

	};

	virtual Object* createInstance() const{
		return NULL;
		//this should probably throw an exception !
	};

	virtual bool compareObject( Object* object )const{
		bool result = false;
		if ( typeid(*object) == typeid(CLASS_TYPE) ){
			result = true;
		}
		return result;
	};

};





/*
pdUndefined = 0,
	pdInt,
	pdLong,
	pdShort,
	pdULong,
	pdFloat,
	pdChar,
	pdDouble,
	pdObject,
	pdBool,
	pdString,
	pdEnum,
	pdInterface,
	pdEnumMask
*/
static PropertyDescriptorType getDescriptor( const std::type_info& typeInfo )
{
	PropertyDescriptorType result = pdUndefined;

	String typeName = StringUtils::toString(typeInfo);
/*
#ifdef VCF_WIN //don't know if we really need this here
		//strip out the preceding "class" or "enum" or whatever
		std::string::size_type idx = typeName.find( " " );
		if ( idx != typeName.npos ) {
			typeName = typeName.substr( idx+1 );
		}
#endif
*/

	if ( typeName.find( "basic_string" ) != String::npos ) {
		result = pdString;
	}
	else if ( typeName.find( "UnicodeString" ) != String::npos ) {
		result = pdString;
	}
	else if ( typeName.find( "AnsiString" ) != String::npos ) {
		result = pdString;
	}
	else if ( typeName.find( "int" ) != String::npos ) {
		result = pdInt;
	}
	else if ( typeName.find( "unsigned" ) != String::npos ) {

		if ( typeName.find( "long" ) != String::npos ) {
			result = pdULong;
		}
		else if ( typeName.find( "int" ) != String::npos ) {
			result = pdUInt;
		}
		else if ( typeName.find( "short" ) != String::npos ) {
			result = pdUShort;
		}
		else if ( typeName.find( "char" ) != String::npos ) {
			result = pdChar;
		}
	}
	else if ( typeName.find( "long" ) != String::npos ) {
		result = pdLong;
	}
	else if ( typeName.find( "short" ) != String::npos ) {
		result = pdShort;
	}
	else if ( typeName.find( "char" ) != String::npos ) {
		result = pdChar;
	}
	else if ( typeName.find( "double" ) != String::npos ) {
		result = pdDouble;
	}
	else if ( typeName.find( "float" ) != String::npos ) {
		result = pdFloat;
	}
	else if ( typeName.find( "bool" ) != String::npos ) {
		result = pdBool;
	}
	else if ( !typeName.empty() ) {
		result = pdObject;
	}


	return result;
}





/**
*this function registers a property with a class, where the PROPERTY_TYPE is defined as some
*type like int, double, bool, Object*, etc.
*
*@param PROPERTY_TYPE initialValue is used partly for an initial value for the
*property, but mainly to make sure thr template function is created properly.
*@param String className - the name of the class to associatent the property with
*@param String propertyName - the name of the property
*@param TypedProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the property
*@param TypedProperty<PROPERTY_TYPE>::SetFunction - the property's set function, allows for
*setting values on the property
*@param PropertyDescriptorType the property type
*/

template <typename PROPERTY_TYPE>
void registerPrimitiveProperty( const String& className,
								 const String& propertyName,
								 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
								 _typename_ TypedProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
								 const String& description ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedProperty<PROPERTY_TYPE>* newProperty =
							new TypedProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction,
														 getDescriptor(typeid(PROPERTY_TYPE)) );
			newProperty->setDescription( description );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
}

template <typename PROPERTY_TYPE>
void registerTypeDefProperty( const String& className,
                                 const String& propertyName,
                                 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
                                 _typename_ TypedProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
                                 const String& typeDefName,
								const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypeDefProperty<PROPERTY_TYPE>* newProperty =
							new TypeDefProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction,
														 getDescriptor(typeid(PROPERTY_TYPE)), typeDefName  );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
}

/**
*this function registers a READ-ONLY property with a class, where the PROPERTY_TYPE is defined as some
*basic type like int, double, bool, etc.
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the property
*@param PropertyDescriptorType the property type
*/
template <typename PROPERTY_TYPE>
void registerPrimitiveReadOnlyProperty( const String& className,
										 const String& propertyName,
										 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
										 const String& description ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedProperty<PROPERTY_TYPE>* newProperty =
							new TypedProperty<PROPERTY_TYPE>( propertyGetFunction,
														 getDescriptor(typeid(PROPERTY_TYPE)) );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
}


template <typename PROPERTY_TYPE>
void registerTypeDefReadOnlyProperty( const String& className,
                                                 const String& propertyName,
                                                 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
                                                 const String& typeDefName,
												 const String& description ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypeDefProperty<PROPERTY_TYPE>* newProperty =
							new TypeDefProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             getDescriptor(typeid(PROPERTY_TYPE)), typeDefName  );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
}

/**
*this function registers a READ-ONLY property with a class, where the PROPERTY_TYPE is defined as some
*Oject* derived type
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedObjectProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the property
*/
template <typename PROPERTY_TYPE>
void registerObjectReadOnlyProperty( const String& className,
									 const String& propertyName,
									 _typename_ TypedObjectProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
									 const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectProperty<PROPERTY_TYPE>( propertyGetFunction );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
}

template <typename PROPERTY_TYPE>
void registerObjectReadOnlyPropertyRef( const String& className, const String& propertyName,
										_typename_ TypedObjectRefProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
										const String& description ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectRefProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectRefProperty<PROPERTY_TYPE>( propertyGetFunction );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
}

/**
*this function registers a READ-ONLY property with a class, where the PROPERTY_TYPE is defined as some
*enum type
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the enum property
*@param PROPERTY_TYPE the lower bound of enum
*@param PROPERTY_TYPE the upper bound of enum
*/
template <class PROPERTY_TYPE>
void registerEnumReadOnlyProperty( const String& className, const String& propertyName,
								 _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
								 PROPERTY_TYPE lower, PROPERTY_TYPE upper,
								const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedEnumProperty<PROPERTY_TYPE>* newProperty =
							new TypedEnumProperty<PROPERTY_TYPE>( propertyGetFunction, lower, upper );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};

/**
*this function registers a READ-ONLY property with a class, where the PROPERTY_TYPE is defined as some
*enum type. In addition, this also associates a human readable string with each enum value. These
*value's can then be represented more descriptively in an IDE than just their integer equivalent.
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the enum property
*@param PROPERTY_TYPE the lower bound of enum
*@param PROPERTY_TYPE the upper bound of enum
*@param uint32 the number of string names enumNames points to
*@param String a pointer to an array of Strings that holds a human
*readable value for each enum type.
*/
template <typename PROPERTY_TYPE>
void registerEnumReadOnlyPropertyWithLabels( const String& className, const String& propertyName,
											 _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
											 PROPERTY_TYPE lower, PROPERTY_TYPE upper,
											 const uint32& enumNameCount,
											 String* enumNames,
											 const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedEnumProperty<PROPERTY_TYPE>* newProperty =
							new TypedEnumProperty<PROPERTY_TYPE>( propertyGetFunction,
															 NULL,
															 lower, upper,
															 enumNameCount,
															 enumNames );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};






static void registerEnumSetReadOnlyPropertyWithLabels( const String& typeName, const String& className, const String& propertyName,
												         EnumSetProperty::GetFunction propertyGetFunction,
												         const uint32& enumNameCount,
														 uint32* enumMaskValues,
												         String* enumNames,
														 const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			EnumSetProperty* newProperty =
							new EnumSetProperty( typeName,
												propertyGetFunction,
												enumNameCount,
												enumMaskValues,
												enumNames );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};

static void registerEnumSetPropertyWithLabels( const String& typeName, const String& className, const String& propertyName,
								         EnumSetProperty::GetFunction propertyGetFunction,
										 EnumSetProperty::SetFunction propertySetFunction,
								         const uint32& enumNameCount,
										 uint32* enumMaskValues,
								         String* enumNames,
										 const String& description ){


	Class* clazz = ClassRegistry::getClass( className );

	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			EnumSetProperty* newProperty =
							new EnumSetProperty( typeName,
												propertyGetFunction,
												propertySetFunction,
												enumNameCount,
												enumMaskValues,
												enumNames );

			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};

/**
*this function registers a property with a class, where the PROPERTY_TYPE is defined as some
*Object* derived type
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedObjectProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the property
*@param TypedObjectProperty<PROPERTY_TYPE>::SetFunction - the property's set function, allows for
*setting values on the property
*/
template <typename PROPERTY_TYPE>
void registerObjectProperty( const String& className, const String& propertyName,
							_typename_ TypedObjectProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
							_typename_ TypedObjectProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
							const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};

template <typename PROPERTY_TYPE>
void registerObjectPropertyRef( const String& className, const String& propertyName,
								_typename_ TypedObjectRefProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
								_typename_ TypedObjectRefProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
								const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectRefProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectRefProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};
/**
*this function registers a property with a class, where the PROPERTY_TYPE is defined as some
*enum type
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedEnumProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the property
*@param TypedEnumProperty<PROPERTY_TYPE>::SetFunction - the property's set function, allows for
*setting values on the property
*@param PROPERTY_TYPE the lower bound of enum
*@param PROPERTY_TYPE the upper bound of enum
*/
template <typename PROPERTY_TYPE>
void registerEnumProperty( const String& className, const String& propertyName,
						 _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
						 _typename_ TypedEnumProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
						 PROPERTY_TYPE lower, PROPERTY_TYPE upper,
						 const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedEnumProperty<PROPERTY_TYPE>* newProperty =
							new TypedEnumProperty<PROPERTY_TYPE>( propertyGetFunction,
							                                 propertySetFunction, lower, upper );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};

/**
*this function registers a property with a class, where the PROPERTY_TYPE is defined as some
*enum type. In addition, this also associates a human readable string with each enum value. These
*value's can then be represented more descriptively in an IDE than just their integer equivalent.
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the enum property
*@param TypedEnumProperty<PROPERTY_TYPE>::SetFunction - the property's set function, allows for
*setting values on the property
*@param PROPERTY_TYPE the lower bound of enum
*@param PROPERTY_TYPE the upper bound of enum
*@param uint32 the number of string names enumNames points to
*@param String a pointer to an array of Strings that holds a human
*readable value for each enum type.
*/
template <typename PROPERTY_TYPE>
void registerEnumPropertyWithLabels( const String& className, const String& propertyName,
									 _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
									 _typename_ TypedEnumProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
									 PROPERTY_TYPE lower, PROPERTY_TYPE upper,
									 const uint32& enumNameCount,
									 String* enumNames,
									 const String& description )
{


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedEnumProperty<PROPERTY_TYPE>* newProperty =
							new TypedEnumProperty<PROPERTY_TYPE>( propertyGetFunction,
							                                 propertySetFunction,
															 lower, upper,
															 enumNameCount,
															 enumNames );
			newProperty->setName( propertyName );
			newProperty->setDescription( description );
			clazz->addProperty( newProperty );
		}
	}
};



template <typename FieldType>
void registerFieldType( const String& className, const String& fieldName, uint32 fieldOffset )
{
	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasField( fieldName ) ){
			Field* newField = new TypedField<FieldType>( fieldName, fieldOffset );
			clazz->addField( newField );
		}
	}
}

template <typename FieldType>
void registerObjectFieldType( const String& className, const String& fieldName, uint32 fieldOffset )
{
	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasField( fieldName ) ){
			Field* newField = new TypedObjectField<FieldType>( fieldName, fieldOffset );
			clazz->addField( newField );
		}
	}
}

/**
*registers a class in the global ClassRegistry instance.
*@param T - a dummy param to make the &*$#$% C++ compiler happy and ensure the
*template function is created correctly. It would be nice to remove this because
*it not used at all in the function
*@param String the name of the class to register
*@param String the name of the class's super class
*@param String the classID of the class to register. This MUST be
*a string that represents unique ID as returned by a UUID function/algorithm
*
*@return bool true if the class has been registered, otherwise false
*/
template <class T> bool registerClass( T* fakeParam, const String& className,
									   const String& superClassName, const String& classID ){

	bool result = false;


	//StringUtils::trace( "registerClass for " + String(typeid(T).name()) + "\n" );

	Class* clazz = ClassRegistry::getClass( className );

	if ( NULL == clazz ){
		//StringUtils::trace( "registering new class " + className + " with ClassRegistry\n" );

		TypedClass<T>* objClass = new TypedClass<T>( className, classID, superClassName );

		ClassRegistry::addClass( className, objClass );

		result = true;
	}
	return result;
};

template <class T>  bool registerAbstractClass( T* fakeParam, const String& className,
									           const String& superClassName, const String& classID ){

	bool result = false;
	//StringUtils::trace( "registerAbstractClass for " + String(typeid(T).name()) + "\n" );


	Class* clazz = ClassRegistry::getClass( className );

	if ( NULL == clazz ){
		//StringUtils::trace( "registering new abstract class " + className + " with ClassRegistry\n" );
		TypedAbstractClass<T>* objClass = new TypedAbstractClass<T>( className, classID, superClassName );

		ClassRegistry::addClass( className, objClass );

		result = true;
	}
	return result;
};


/**
*registers an implemented interface with a particular class type.
*/
template <class INTERFACE_TYPE, class IMPLEMENTER_TYPE>
	bool registerImplementedInterface( INTERFACE_TYPE* fakeParam, const String& implementationClassName, const String& interfaceName,
								const String& interfaceID, const String& superInterfaceClassName ) {

	bool result = false;


	InterfaceClass* interfaceClass = ClassRegistry::getImplementedInterface( implementationClassName, interfaceID );
	if ( NULL == interfaceClass ) {

		Class* clazz = ClassRegistry::getClass( implementationClassName );
		result = clazz->hasInterfaceID( interfaceID );
		if ( false == result ) {

			InterfaceClass* interfaceClassInst =
				new TypedImplementedInterfaceClass<INTERFACE_TYPE,IMPLEMENTER_TYPE>( interfaceName, interfaceID, superInterfaceClassName );

			ClassRegistry::addImplementedInterface( (ImplementedInterfaceClass*)interfaceClassInst, clazz->getID() );

			clazz->addInterface( interfaceClassInst );
			result = true;
		}
	}
	return result;
}


/**
*registers an interface in the class registry
*/
template <class INTERFACE_TYPE>
	bool registerInterface( INTERFACE_TYPE* fakeParam, const String& interfaceName,
								const String& interfaceID, const String& superInterfaceClassName ) {

	bool result = false;


	InterfaceClass* interfaceClass = ClassRegistry::getInterfaceFromInterfaceID( interfaceID );
	if ( NULL == interfaceClass ) {

		interfaceClass = new TypedInterfaceClass<INTERFACE_TYPE>( interfaceName, interfaceID, superInterfaceClassName );

		ClassRegistry::addInterface( interfaceName, interfaceClass );

		result = true;
	}
	return result;
}

/**
*registers a new event with a class. Calls the Class::addEvent()
*if a class is found for the given clasName. Internally the class will
*create a new EventSet class if the event set did not previously exist
*and the add the new event.
*MSVC note:
*the inline keyword was added to make the linker happy and stop it bitching
*about linker warning 4006.
*/

template <typename SourceType, typename EventType>
bool registerEvent( SourceType* dummy1, EventType* dummy2,
						const String& className,
						const String& handlerClassName,
						const String& eventClassName,
						const String& eventMethodName,
						EventProperty::DelegateMethod delegateMethod )
{
	bool result = false;



	Class* clazz = ClassRegistry::getClass( className );

	if ( NULL != clazz ){
		if ( NULL == delegateMethod ) {
			if ( ! clazz->hasEventHandler( eventMethodName ) ) {

				EventProperty* ev = new AbstractEventProperty( eventClassName,
																handlerClassName,
																eventMethodName );

				clazz->addEvent( ev );
				result = true;
			}
		}
		else {
			if ( ! clazz->hasEventHandler( eventMethodName ) ) {

				EventProperty* ev = new TypedEventProperty<SourceType,EventType>( eventClassName,
																					handlerClassName,
																					eventMethodName,
																					delegateMethod );

				clazz->addEvent( ev );
				result = true;
			}
			else {
				EventProperty* ev = clazz->getEvent( eventMethodName );
				if ( ev->isAbstract() ) {
					delete ev;

					ev = new TypedEventProperty<SourceType,EventType>( eventClassName,
																		handlerClassName,
																		eventMethodName,
																		delegateMethod );

					clazz->addEvent( ev );
					result = true;
				}
			}
		}
	}
	return result;
}



template <typename ValueType, typename KeyType>
void registerCollectionProperty( const String& className,
								 const String& propertyName,
								 _typename_ TypedCollectionProperty<ValueType,KeyType>::GetFunction getFunc,
								 _typename_ TypedCollectionProperty<ValueType,KeyType>::SetFunction setFunc,
								 _typename_ TypedCollectionProperty<ValueType,KeyType>::AddFunction addFunc,
								 _typename_ TypedCollectionProperty<ValueType,KeyType>::InsertFunction insertFunc,
								 _typename_ TypedCollectionProperty<ValueType,KeyType>::DeleteFunction deleteFunc,
								 _typename_ TypedCollectionProperty<ValueType,KeyType>::GetSizeFunction getSizeFunc,
								 const String& description ){

	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( !clazz->hasProperty( propertyName ) ){
			Property* newProperty = 
				new TypedCollectionProperty<ValueType,KeyType>( getFunc,setFunc,
														addFunc, insertFunc,
														deleteFunc, getSizeFunc,
														getDescriptor(typeid(ValueType)) );

			newProperty->setDescription( description );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
}



template <typename ValueType, typename KeyType>
void registerObjectCollectionProperty( const String& className,
								 const String& propertyName,
								 _typename_ TypedObjectCollectionProperty<ValueType,KeyType>::GetFunction getFunc,
								 _typename_ TypedObjectCollectionProperty<ValueType,KeyType>::SetFunction setFunc,
								 _typename_ TypedObjectCollectionProperty<ValueType,KeyType>::AddFunction addFunc,
								 _typename_ TypedObjectCollectionProperty<ValueType,KeyType>::InsertFunction insertFunc,
								 _typename_ TypedObjectCollectionProperty<ValueType,KeyType>::DeleteFunction deleteFunc,
								 _typename_ TypedObjectCollectionProperty<ValueType,KeyType>::GetSizeFunction getSizeFunc,
								 const String& description ){

	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( !clazz->hasProperty( propertyName ) ){
			Property* newProperty = 
				new TypedObjectCollectionProperty<ValueType,KeyType>( getFunc,setFunc,
														addFunc, insertFunc,
														deleteFunc, getSizeFunc,
														getDescriptor(typeid(ValueType)) );

			newProperty->setDescription( description );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
}

/**
*registers a new method with a Class
*@param T - a dummy param to make the &*$#$% C++ compiler happy and ensure the
*template function is created correctly. It would be nice to remove this because
*it not used at all in the function
*@param String the name of the class to register
*@param String the name of the class's method to register
*@param METHOD_TYPE the method pointer of the class
*@param String the arg types of the method
*@param bool doe the method have a return value
*@param uint32 the number of arguments of the method
*
*@return bool true if the method has been registered, otherwise false
*/
template<typename SOURCE_TYPE, typename METH_TYPE, typename RETURN_TYPE>
void registerMethod0Return( SOURCE_TYPE* fakeParam, const String& className, const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){



	Method* newMethod = new TypedMethodArg0Return<SOURCE_TYPE,RETURN_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}

};


template<typename SOURCE_TYPE, typename METH_TYPE,typename RETURN_TYPE, typename ARG1_TYPE>
void registerMethod1Return( SOURCE_TYPE* fakeParam,
						   const String& className, const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg1Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}

};

template<typename SOURCE_TYPE, typename METH_TYPE,typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE>
void registerMethod2Return( SOURCE_TYPE* fakeParam,
						   const String& className,
						   const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg2Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE,ARG2_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};

template<typename SOURCE_TYPE, typename METH_TYPE,typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE>
void registerMethod3Return( SOURCE_TYPE* fakeParam, const String& className, const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg3Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};

template<typename SOURCE_TYPE, typename METH_TYPE,typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE, typename ARG4_TYPE>
void registerMethod4Return( SOURCE_TYPE* fakeParam,
						   const String& className,
						   const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg4Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}

};

template<typename SOURCE_TYPE, typename METH_TYPE,typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE>
void registerMethod5Return( SOURCE_TYPE* fakeParam,
						   const String& className,
						   const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg5Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};


template<typename SOURCE_TYPE, typename METH_TYPE,typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE, typename ARG6_TYPE>
void registerMethod6Return( SOURCE_TYPE* fakeParam,
						   const String& className,
						   const String& methodName,
						   METH_TYPE methodPtr,
						   const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg6Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE,ARG6_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};

/**
*registers a new method with a Class
*@param T - a dummy param to make the &*$#$% C++ compiler happy and ensure the
*template function is created correctly. It would be nice to remove this because
*it not used at all in the function
*@param String the name of the class to register
*@param String the name of the class's method to register
*@param METHOD_TYPE the method pointer of the class
*@param String the arg types of the method
*@param bool doe the method have a return value
*@param uint32 the number of arguments of the method
*
*@return bool true if the method has been registered, otherwise false
*/
template<typename SOURCE_TYPE, typename METH_TYPE>
void registerVoidMethodArg0( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg0<SOURCE_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};


template<typename SOURCE_TYPE, typename METH_TYPE, typename ARG1_TYPE>
void registerVoidMethodArg1( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false ){


	Method* newMethod = new TypedMethodArg1<SOURCE_TYPE,ARG1_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};

template<typename SOURCE_TYPE, typename METH_TYPE, typename ARG1_TYPE, typename ARG2_TYPE>
void registerVoidMethodArg2( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg2<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};

template<typename SOURCE_TYPE, typename METH_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,typename ARG3_TYPE>
void registerVoidMethodArg3( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg3<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};

template<typename SOURCE_TYPE, typename METH_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,typename ARG3_TYPE,typename ARG4_TYPE>
void registerVoidMethodArg4( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg4<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};


template<typename SOURCE_TYPE, typename METH_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,typename ARG3_TYPE,typename ARG4_TYPE,typename ARG5_TYPE>
void registerVoidMethodArg5( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg5<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};


template<typename SOURCE_TYPE, typename METH_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,typename ARG3_TYPE,typename ARG4_TYPE,typename ARG5_TYPE,typename ARG6_TYPE>
void registerVoidMethodArg6( SOURCE_TYPE* fakeParam,
							const String& className,
							const String& methodName,
							METH_TYPE methodPtr,
							const String& argTypes, const bool& isInterfaceMethod=false  ){


	Method* newMethod = new TypedMethodArg6<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE,ARG4_TYPE,ARG5_TYPE,ARG6_TYPE>( methodPtr, argTypes );
	newMethod->setName( methodName );
	if ( false == ClassRegistry::registerMethod( newMethod, className, isInterfaceMethod ) ) {
		delete newMethod;
		newMethod = NULL;
	}
};


#endif // VCF_RTTI


};


#endif // _VCF_VCFRTTIIMPL_H__

/**
$Id$
*/
