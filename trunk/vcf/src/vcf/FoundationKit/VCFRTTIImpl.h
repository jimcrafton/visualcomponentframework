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
This is a special class for handing a enum mask value that is the combination
of one or more other values.
*/
class FOUNDATIONKIT_API EnumSetProperty : public Property {
public:

	typedef unsigned long (Object::*GetFunction)(void);
	typedef void (Object::*SetFunction)(const unsigned long& );

	EnumSetProperty( GetFunction propGetFunction, int count, unsigned long* setArray, String* names ){
		init();

		getFunction_ = propGetFunction;
		setType( pdEnumMask );
		isReadOnly_ = true;

		for (int i=0;i<count;i++ ) {
			nameVals_[names[i]] = setArray[i];
		}
	};

	EnumSetProperty( GetFunction propGetFunction, SetFunction propSetFunction,
					int count, unsigned long* setArray, String* names ){
		init();

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
		getFunction_ = prop.getFunction_;
		setFunction_ = prop.setFunction_;
		nameVals_ = prop.nameVals_;
	};

	virtual ~EnumSetProperty(){};


	void addAsString( const String& val ) {
		std::map<String,unsigned long>::iterator found = nameVals_.find( val );
		if ( found != nameVals_.end() ) {
			add( found->second );
		}
	}

	void removeAsString( const String& val ) {
		std::map<String,unsigned long>::iterator found = nameVals_.find( val );
		if ( found != nameVals_.end() ) {
			remove( found->second );
		}
	}

	void add( const unsigned long& val ) {
		unsigned long tmp = value_;
		tmp |= val;
		value_ = tmp;
	}

	void remove( const unsigned long& val ) {
		unsigned long tmp = value_;
		tmp &= ~val;
		value_ = tmp;
	}

	bool contains( const unsigned long& val )  {
		return (((unsigned long)value_) & val) ? true : false;
	}

	bool hasNames()  {
		return !nameVals_.empty();
	}

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(unsigned long) );
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
			value_.type = getType();
			value_ = (source->*getFunction_)();
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
		ulong32 pos = tmp.find( "," );

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
			unsigned long maskVal = *data;
			std::map<String,unsigned long>::iterator it = nameVals_.begin();
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
protected:
	GetFunction getFunction_;
	SetFunction setFunction_;
	std::map<String,unsigned long> nameVals_;
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

	TypedEnum( const ENUM_TYPE& lower, const ENUM_TYPE& upper, const unsigned long& enumNameCount, String* enumNames ){
		enum_ = lower;
		lower_ = (int)lower;
		upper_ = (int)upper;
		enumNames_.clear();
		if ( enumNameCount > 0 ){
			for ( unsigned long i=0;i<enumNameCount;i++ ){
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
			result = enumNames_[get()];
		}
		else {
			char tmp[25];
			memset( tmp, 0, 25 );
			sprintf( tmp, "%d", get() );
			result += tmp;
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

				case pdLong: {
					result = CLASS_LONG;
				}
				break;

				case pdShort: {
					result = CLASS_SHORT;
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
			value_.type = getType();
			value_ = (source->*getFunction_)();
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
			value_.type = getType();
			value_ = (Object*)(source->*getFunction_)();
			return &value_;
		}
		else {
			return NULL;
		}
	};

	void set( Object* source, VariantData* value ){
		if ( (NULL != setFunction_) && (NULL != source) ){
			Object* object = *value;
			if ( true == isBound() ){
				VariantData* originalValue = get( source );
				PropertyChangeEvent changeEvent( source, originalValue, value );
				try {
					PropertyChanged.fireEvent( &changeEvent );
					(source->*setFunction_)( (PROPERTY*)(object) );
				}
				catch ( PropertyChangeException ){
					//do not call the set method
					//re-throw the exception ?
				}
			}
			else {
				(source->*setFunction_)( (PROPERTY*)(object) );
			}
		}
	};

protected:
	GetFunction getFunction_;
	SetFunction setFunction_;
};

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
			value_.type = getType();
			//value_ = (Object&)(source->*getFunction_)();
			value_ = (source->*getFunction_)();
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
					   const unsigned long& enumNameCount,
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
			value_.type = getType();
			enum_->set( (source->*getFunction_)() );
			value_ = enum_;
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
	unsigned long enumNameCount_;
	String* enumNames_;
};

/**
*TypedCollectionProperty represents a type safe wrapper around properties that
*are enumerations of items.
*/
template <class ITEM_TYPE>
class TypedCollectionProperty : public Property {
public:
	typedef Enumerator<ITEM_TYPE>* (Object::*GetFunction)(void);
	typedef void (Object::*AddFunction)( ITEM_TYPE );
	typedef void (Object::*InsertFunction)( const unsigned long&, ITEM_TYPE );
	typedef void (Object::*DeleteFunction1)( ITEM_TYPE );
	typedef void (Object::*DeleteFunction2)( const unsigned long& );

	TypedCollectionProperty( GetFunction getFunc, AddFunction addFunc, InsertFunction insertFunc,
		                     DeleteFunction1 deleteFunc1, DeleteFunction2 deleteFunc2,
							 const PropertyDescriptorType& propertyType ){

		init();
		getFunction_ = getFunc;
		addFunc_ = addFunc;
		insertFunc_ = insertFunc;
		deleteFunc1_ = deleteFunc1;
		deleteFunc2_ = deleteFunc2;
		setType( propertyType );
	};


	TypedCollectionProperty( const TypedCollectionProperty<ITEM_TYPE>& prop ):
		Property( prop ){

		init();
		getFunction_ = prop.getFunction_;
		enumeration_ = prop.enumeration_;
		addFunc_ = prop.addFunc_;
		insertFunc_ = prop.insertFunc_;
		deleteFunc1_ = prop.deleteFunc1_;
		deleteFunc2_ = prop.deleteFunc2_;
	};

	void init(){
		getFunction_ = NULL;
		isCollection_ = true;
		enumeration_ = NULL;
		isReadOnly_ = true;
		addFunc_ = NULL;
		insertFunc_ = NULL;
		deleteFunc1_ = NULL;
		deleteFunc2_ = NULL;
	};

	virtual ~TypedCollectionProperty(){};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(ITEM_TYPE) );
	}

	virtual VariantData* get( Object* source ){
		return NULL;
	};

	virtual void set( Object* source, VariantData* value ){
		//no-op
	};

	virtual bool hasMoreElements( Object* source ){
		if ( NULL != enumeration_ ){
			return enumeration_->hasMoreElements();
		}
		else {
			return false;
		}
	};

	virtual VariantData* nextElement( Object* source ){
		VariantData* element = NULL;
		if ( NULL != enumeration_ ){
			if ( true == enumeration_->hasMoreElements() ){
				value_ = enumeration_->nextElement();
				element = &value_;
			}
		}
		return element;
	};

	virtual void startCollection( Object* source ){
		enumeration_ = NULL;
		if ( NULL != source ){
			enumeration_ = (source->*getFunction_)();
		}
	};

	virtual Property* clone(){
		return new TypedCollectionProperty<ITEM_TYPE>(*this);
	};

	virtual void add( Object* source, VariantData* value ){
		if ( (NULL != value) && (NULL != addFunc_) ){
			ITEM_TYPE valToAdd = (ITEM_TYPE)(*value);
			(source->*addFunc_)( valToAdd );
		}
	};

	virtual void insert( Object* source, const unsigned long& index, VariantData* value ){
		if ( (NULL != value) && (NULL != source) && (NULL != insertFunc_) ){
			ITEM_TYPE valToInsert = (ITEM_TYPE)(*value);
			(source->*insertFunc_)( index, valToInsert );
		}
	};

	virtual void remove( Object* source, VariantData* value ){
		if ( (NULL != value) && (NULL != source) && (NULL != deleteFunc1_) ){
			ITEM_TYPE valToRemove = (ITEM_TYPE)(*value);
			(source->*deleteFunc1_)( valToRemove );
		}
	};

	virtual void remove( Object* source, const unsigned long& index ){
		if ( (NULL != source) && (NULL != deleteFunc2_) ){
			(source->*deleteFunc2_)( index );
		}
	};

	virtual bool collectionSupportsEditing(){
		if ( NULL != enumeration_ ){
			return enumeration_->supportsEditing();
		}
		else{
			return false;
		}
	};
private:
	GetFunction getFunction_;
	Enumerator<ITEM_TYPE>* enumeration_;
	AddFunction addFunc_;
	InsertFunction insertFunc_;
	DeleteFunction1 deleteFunc1_;
	DeleteFunction2 deleteFunc2_;
};

/**
*TypedCollectionProperty represents a type safe wrapper around properties that
*are enumerations of Object* derived items.
*/
template <class ITEM_TYPE>
class TypedObjectCollectionProperty : public Property {
public:
	typedef Enumerator<ITEM_TYPE>* (Object::*GetFunction)(void);
	typedef void (Object::*AddFunction)( ITEM_TYPE );
	typedef void (Object::*InsertFunction)( const unsigned long&, ITEM_TYPE );
	typedef void (Object::*DeleteFunction1)( ITEM_TYPE );
	typedef void (Object::*DeleteFunction2)( const unsigned long& );

	TypedObjectCollectionProperty( GetFunction getFunc, AddFunction addFunc, InsertFunction insertFunc,
		                           DeleteFunction1 deleteFunc1, DeleteFunction2 deleteFunc2 ){
		init();
		getFunction_ = getFunc;
		addFunc_ = addFunc;
		insertFunc_ = insertFunc;
		deleteFunc1_ = deleteFunc1;
		deleteFunc2_ = deleteFunc2;
	};


	TypedObjectCollectionProperty( const TypedObjectCollectionProperty& prop ):
		Property( prop ){

		init();
		getFunction_ = prop.getFunction_;
		enumeration_ = prop.enumeration_;
		addFunc_ = prop.addFunc_;
		insertFunc_ = prop.insertFunc_;
		deleteFunc1_ = prop.deleteFunc1_;
		deleteFunc2_ = prop.deleteFunc2_;
	};

	virtual ~TypedObjectCollectionProperty(){};

	void init(){
		getFunction_ = NULL;
		isCollection_ = true;
		enumeration_ = NULL;
		isReadOnly_ = true;
		addFunc_ = NULL;
		insertFunc_ = NULL;
		deleteFunc1_ = NULL;
		deleteFunc2_ = NULL;
		setType( pdObject );
	};

	virtual String getTypeClassName() {
		return StringUtils::getClassNameFromTypeInfo( typeid(ITEM_TYPE) );
	}

	virtual VariantData* get( Object* source ){
		return NULL;
	};

	virtual void set( Object* source, VariantData* value ){
		//no-op
	};

	virtual bool hasMoreElements( Object* source ){
		_typename_ std::map<Object*,Enumerator<ITEM_TYPE>*>::iterator it = enumerationMap_.find( source );
		if ( it != enumerationMap_.end() ){
			Enumerator<ITEM_TYPE>* enumeration = it->second;
			bool result = false;
			if ( NULL != enumeration ){
				result = enumeration->hasMoreElements();
				if ( false == result ){
					enumerationMap_.erase( source );
				}
			}
			return result;
		}
		else {
			return false;
		}
	};

	virtual VariantData* nextElement( Object* source ){
		VariantData* element = NULL;
		_typename_ std::map<Object*,Enumerator<ITEM_TYPE>*>::iterator it = enumerationMap_.find( source );
		if ( it != enumerationMap_.end() ){
			Enumerator<ITEM_TYPE>* enumeration = it->second;
			if ( NULL != enumeration ){
				if ( true == enumeration->hasMoreElements() ){
					value_ = enumeration->nextElement();
					element = &value_;
				}
			}
		}
		return element;
	};

	virtual void startCollection( Object* source ){
		enumeration_ = NULL;
		if ( NULL != source ) {
			enumeration_ = (source->*getFunction_)();
			enumerationMap_[ source ] = enumeration_;
		}
	};

	virtual Property* clone(){
		return new TypedObjectCollectionProperty<ITEM_TYPE>(*this);
	};

	virtual void add( Object* source, VariantData* value ){
		if ( (NULL != value) && (NULL != addFunc_) ){
			if ( pdObject == value->type ){
				ITEM_TYPE valToAdd = (ITEM_TYPE)(Object*)(*value);
				(source->*addFunc_)( valToAdd );
			}
		}
	};

	virtual void insert( Object* source, const unsigned long& index, VariantData* value ){
		if ( (NULL != value) && (NULL != insertFunc_) ){
			if ( pdObject == value->type ){
				ITEM_TYPE valToInsert = (ITEM_TYPE)(Object*)(*value);
				(source->*insertFunc_)( index, valToInsert );
			}
		}
	};

	virtual void remove( Object* source, VariantData* value ){
		if ( (NULL != value) && (NULL != deleteFunc1_) ){
			ITEM_TYPE valToRemove = (ITEM_TYPE)(Object*)(*value);
			(source->*deleteFunc1_)( valToRemove );
		}
	};

	virtual void remove( Object* source, const unsigned long& index ){
		if ( NULL != deleteFunc2_ ){
			(source->*deleteFunc2_)( index );
		}
	};

	virtual bool collectionSupportsEditing(){
		if ( NULL != enumeration_ ){
			return enumeration_->supportsEditing();
		}
		else{
			return false;
		}
	};
private:
	GetFunction getFunction_;
	AddFunction addFunc_;
	InsertFunction insertFunc_;
	DeleteFunction1 deleteFunc1_;
	DeleteFunction2 deleteFunc2_;

	Enumerator<ITEM_TYPE>* enumeration_;
	std::map<Object*, Enumerator<ITEM_TYPE>*> enumerationMap_;
};















/**
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


	TypedMethod( const TypedMethod<SOURCE_TYPE>& method ) {
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
*Base template class for methodsthat DO return values
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE>
class TypedMethodReturn : public TypedMethod<SOURCE_TYPE> {
public:
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
		returnVal_ = rhs.returnVal_;
		return *this;
	}

	virtual ~TypedMethodReturn(){}

protected:
	VariantData returnVal_;
};


/**
*Method template class for methods have 0 arguments
*/
template <class SOURCE_TYPE>
class TypedMethodArg0 : public TypedMethod<SOURCE_TYPE> {
public:
	typedef void (SOURCE_TYPE::*MemberFunc)();

	TypedMethodArg0( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 0;
		methodPtr_=methodPtr;
	}

	TypedMethodArg0( const TypedMethodArg0<SOURCE_TYPE>& method )  {
		*this = method;
	}

	TypedMethodArg0<SOURCE_TYPE>& operator=( const TypedMethodArg0<SOURCE_TYPE>& rhs ) {
		TypedMethod<SOURCE_TYPE>::operator =(rhs);
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual ~TypedMethodArg0(){	}

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 0 == argCount_ ) {
				(source_->*methodPtr_)();
			}
		}

		return NULL;
	}

	virtual Method* clone() {
		return new TypedMethodArg0<SOURCE_TYPE>(*this);
	}

protected:
	MemberFunc methodPtr_;
};

/**
*Method template class for methods have 1 argument
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE>
class TypedMethodArg1 : public TypedMethod<SOURCE_TYPE> {
public:
	typedef ARG1_TYPE Argument1;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1);


	TypedMethodArg1( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 1;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg1( const TypedMethodArg1<SOURCE_TYPE,ARG1_TYPE>& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 1 == argCount_ ) {
				(source_->*methodPtr_)( (Argument1) *(arguments[0]) );
			}
		}

		return NULL;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Accepts methds with 2 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE >
class TypedMethodArg2 : public TypedMethod<SOURCE_TYPE> {
public:

	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2);

	TypedMethodArg2( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 2;
		methodPtr_ = methodPtr;

	}

	TypedMethodArg2( const TypedMethodArg2<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE>& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
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

		return NULL;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Accepts methds with 3 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE>
class TypedMethodArg3 : public TypedMethod<SOURCE_TYPE> {
public:
	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;
	typedef ARG3_TYPE Argument3;

	typedef void (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3);

	TypedMethodArg3( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethod<SOURCE_TYPE>( argTypes, source ){
		argCount_ = 3;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg3( const TypedMethodArg3<SOURCE_TYPE,ARG1_TYPE,ARG2_TYPE,ARG3_TYPE>& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
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

		return NULL;
	}
protected:
	MemberFunc methodPtr_;
};



/**
*Accepts methds with 4 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE, typename ARG4_TYPE>
class TypedMethodArg4 : public TypedMethod<SOURCE_TYPE> {
public:
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

	TypedMethodArg4( const TypedMethodArg4Type& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
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

		return NULL;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Accepts methds with 5 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE>
class TypedMethodArg5 : public TypedMethod<SOURCE_TYPE> {
public:

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

	TypedMethodArg5( const TypedMethodArg5Type& method )  {

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

	virtual VariantData* invoke( VariantData** arguments,
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

		return NULL;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Accepts methds with 6 arguments - no return value
*/
template <typename SOURCE_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE, typename ARG6_TYPE>
class TypedMethodArg6 : public TypedMethod<SOURCE_TYPE> {
public:

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

	TypedMethodArg6( const TypedMethodArg6Type& method )  {
		TypedMethod<SOURCE_TYPE>::operator =( rhs );

		methodPtr_ = rhs.methodPtr_;
		*this = method;
	}

	virtual Method* clone() {
		return new TypedMethodArg6Type(*this);
	}

	TypedMethodArg6Type& operator=( const TypedMethodArg6Type& rhs ) {

		return *this;
	}

	virtual ~TypedMethodArg6(){	}

	virtual VariantData* invoke( VariantData** arguments,
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

		return NULL;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Method template for methods with 0 argument and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE>
class TypedMethodArg0Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)();

	typedef TypedMethodArg0Return<SOURCE_TYPE,RETURN_TYPE> TypedMethodArg0ReturnType;


	TypedMethodArg0Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 0;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg0Return( const TypedMethodArg0ReturnType& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 0 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)();
			}
		}

		return &returnVal_;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Method template for methods with 1 argument and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE>
class TypedMethodArg1Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:
	typedef ARG1_TYPE Argument1;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1);

	typedef TypedMethodArg1Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE> TypedMethodArg1ReturnType;


	TypedMethodArg1Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 1;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg1Return( const TypedMethodArg1ReturnType& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 1 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)((Argument1)*(arguments[0]));
			}
		}

		return &returnVal_;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Method template for methods with 2 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE>
class TypedMethodArg2Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:
	typedef ARG1_TYPE Argument1;
	typedef ARG2_TYPE Argument2;

	typedef RETURN_TYPE (SOURCE_TYPE::*MemberFunc)(ARG1_TYPE arg1, ARG2_TYPE arg2);

	typedef TypedMethodArg2Return<SOURCE_TYPE,RETURN_TYPE,ARG1_TYPE, ARG2_TYPE> TypedMethodArg2ReturnType;



	TypedMethodArg2Return( MemberFunc methodPtr=NULL, const String& argTypes="", SOURCE_TYPE* source=NULL ):
	  TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>( argTypes, source ){
		argCount_ = 2;
		methodPtr_ = methodPtr;
	}

	TypedMethodArg2Return( const TypedMethodArg2ReturnType& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 2 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]) );
			}
		}

		return &returnVal_;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Method template for methods with 3 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE>
class TypedMethodArg3Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

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

	TypedMethodArg3Return( const TypedMethodArg3ReturnType& rhs )  {
		*this = rhs;
	}

	TypedMethodArg3ReturnType& operator=( const TypedMethodArg3ReturnType& rhs ) {
		TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE>::operator =( rhs );
		methodPtr_ = rhs.methodPtr_;

		return *this;
	}

	virtual Method* clone() {
		return new TypedMethodArg3ReturnType( *this );
	}


	virtual ~TypedMethodArg3Return(){	}

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 3 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]) );
			}
		}

		return &returnVal_;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Method template for methods with 4 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE>
class TypedMethodArg4Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

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

	TypedMethodArg4Return( const TypedMethodArg4ReturnType& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 4 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]),
														(Argument4)*(arguments[3]) );
			}
		}

		return &returnVal_;
	}
protected:
	MemberFunc methodPtr_;
};


/**
*Method template for methods with 5 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE>
class TypedMethodArg5Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

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

	TypedMethodArg5Return( const TypedMethodArg5ReturnType& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 5 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]),
														(Argument4)*(arguments[3]),
														(Argument5)*(arguments[4]) );
			}
		}

		return &returnVal_;
	}
protected:
	MemberFunc methodPtr_;
};



/**
*Method template for methods with 6 arguments and a return value
*/
template <typename SOURCE_TYPE, typename RETURN_TYPE, typename ARG1_TYPE, typename ARG2_TYPE,
			typename ARG3_TYPE, typename ARG4_TYPE, typename ARG5_TYPE, typename ARG6_TYPE>
class TypedMethodArg6Return : public TypedMethodReturn<SOURCE_TYPE,RETURN_TYPE> {
public:

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

	TypedMethodArg6Return( const TypedMethodArg6ReturnType& method )  {
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

	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ){

		if ( NULL != source ) {
			source_ = dynamic_cast<SOURCE_TYPE*>( source );
		}

		if ( (NULL != source_) && (NULL != methodPtr_) ){
			if  ( 6 == argCount_ ) {
				returnVal_ = (source_->*methodPtr_)(	(Argument1)*(arguments[0]),
														(Argument2)*(arguments[1]),
														(Argument3)*(arguments[2]),
														(Argument4)*(arguments[3]),
														(Argument5)*(arguments[4]),
														(Argument6)*(arguments[5]) );
			}
		}

		return &returnVal_;
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

	TypedField( const String& name, ulong32 fieldOffset ):field_(NULL),fieldOffset_(fieldOffset) {
		setName( name );
	}

	TypedField( const TypedField& rhs ):Field(rhs),field_(NULL),fieldOffset_(rhs.fieldOffset_)  {

	}

	virtual Field* clone() {
		return new TypedField( *this );
	}

	virtual ulong32 getFieldSize() {
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
	ulong32 fieldOffset_;
};



template <typename FieldType>
class TypedObjectField : public Field {
public:
	typedef FieldType Type;
	typedef FieldType* TypePtr;


	TypedObjectField():field_(NULL),fieldOffset_(0) {

	}

	TypedObjectField( const String& name, ulong32 fieldOffset ):field_(NULL),fieldOffset_(fieldOffset) {
		setName( name );
	}

	TypedObjectField( const TypedObjectField& rhs ):Field(rhs),field_(NULL),fieldOffset_(rhs.fieldOffset_)  {

	}

	virtual Field* clone() {
		return new TypedObjectField( *this );
	}

	virtual ulong32 getFieldSize() {
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
	ulong32 fieldOffset_;
};



/**
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
template <class PROPERTY_TYPE>  void registerPrimitiveProperty( const String& className,
                                                 const String& propertyName,
                                                 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
                                                 _typename_ TypedProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
                                                 const PropertyDescriptorType& propertyFieldDescriptor ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedProperty<PROPERTY_TYPE>* newProperty =
							new TypedProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction,
														 propertyFieldDescriptor );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
}

template <class PROPERTY_TYPE>  void registerTypeDefProperty( const String& className,
                                                 const String& propertyName,
                                                 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
                                                 _typename_ TypedProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
                                                 const PropertyDescriptorType& propertyFieldDescriptor,
												 const String& typeDefName ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypeDefProperty<PROPERTY_TYPE>* newProperty =
							new TypeDefProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction,
														 propertyFieldDescriptor, typeDefName  );
			newProperty->setName( propertyName );
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
template <class PROPERTY_TYPE>  void registerPrimitiveReadOnlyProperty(
												 const String& className,
												 const String& propertyName,
												 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												 const PropertyDescriptorType& propertyFieldDescriptor ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedProperty<PROPERTY_TYPE>* newProperty =
							new TypedProperty<PROPERTY_TYPE>( propertyGetFunction,
														 propertyFieldDescriptor );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
}

template <class PROPERTY_TYPE>  void registerTypeDefReadOnlyProperty( const String& className,
                                                 const String& propertyName,
                                                 _typename_ TypedProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
                                                 const PropertyDescriptorType& propertyFieldDescriptor,
												 const String& typeDefName ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypeDefProperty<PROPERTY_TYPE>* newProperty =
							new TypeDefProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction, typeDefName  );
			newProperty->setName( propertyName );
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
template <class PROPERTY_TYPE>  void registerObjectReadOnlyProperty( const String& className,
												         const String& propertyName,
												         _typename_ TypedObjectProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectProperty<PROPERTY_TYPE>( propertyGetFunction );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
}

template <class PROPERTY_TYPE>  void registerObjectReadOnlyPropertyRef( const String& className, const String& propertyName,
												_typename_ TypedObjectRefProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectRefProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectRefProperty<PROPERTY_TYPE>( propertyGetFunction );
			newProperty->setName( propertyName );
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
template <class PROPERTY_TYPE>  void registerEnumReadOnlyProperty( const String& className, const String& propertyName,
												         _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												         PROPERTY_TYPE lower, PROPERTY_TYPE upper ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedEnumProperty<PROPERTY_TYPE>* newProperty =
							new TypedEnumProperty<PROPERTY_TYPE>( propertyGetFunction, lower, upper );
			newProperty->setName( propertyName );
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
*@param unsigned long the number of string names enumNames points to
*@param String a pointer to an array of Strings that holds a human
*readable value for each enum type.
*/
template <class PROPERTY_TYPE>  void registerEnumReadOnlyPropertyWithLabels( const String& className, const String& propertyName,
												         _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												         PROPERTY_TYPE lower, PROPERTY_TYPE upper,
												         const unsigned long& enumNameCount,
												         String* enumNames ){


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
			clazz->addProperty( newProperty );
		}
	}
};






static void registerEnumSetReadOnlyPropertyWithLabels( const String& className, const String& propertyName,
												         EnumSetProperty::GetFunction propertyGetFunction,
												         const unsigned long& enumNameCount,
														 unsigned long* enumMaskValues,
												         String* enumNames ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			EnumSetProperty* newProperty =
							new EnumSetProperty( propertyGetFunction,
												enumNameCount,
												enumMaskValues,
												enumNames );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
};

static void registerEnumSetPropertyWithLabels( const String& className, const String& propertyName,
								         EnumSetProperty::GetFunction propertyGetFunction,
										 EnumSetProperty::SetFunction propertySetFunction,
								         const unsigned long& enumNameCount,
										 unsigned long* enumMaskValues,
								         String* enumNames ){


	Class* clazz = ClassRegistry::getClass( className );

	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			EnumSetProperty* newProperty =
							new EnumSetProperty( propertyGetFunction,
												propertySetFunction,
												enumNameCount,
												enumMaskValues,
												enumNames );

			newProperty->setName( propertyName );
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
template <class PROPERTY_TYPE>  void registerObjectProperty( const String& className, const String& propertyName,
												_typename_ TypedObjectProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												_typename_ TypedObjectProperty<PROPERTY_TYPE>::SetFunction propertySetFunction ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
};

template <class PROPERTY_TYPE>  void registerObjectPropertyRef( const String& className, const String& propertyName,
												_typename_ TypedObjectRefProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												_typename_ TypedObjectRefProperty<PROPERTY_TYPE>::SetFunction propertySetFunction ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectRefProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectRefProperty<PROPERTY_TYPE>( propertyGetFunction,
							                             propertySetFunction );
			newProperty->setName( propertyName );
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
template <class PROPERTY_TYPE>  void registerEnumProperty( const String& className, const String& propertyName,
												 _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												 _typename_ TypedEnumProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
												 PROPERTY_TYPE lower, PROPERTY_TYPE upper ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedEnumProperty<PROPERTY_TYPE>* newProperty =
							new TypedEnumProperty<PROPERTY_TYPE>( propertyGetFunction,
							                                 propertySetFunction, lower, upper );
			newProperty->setName( propertyName );
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
*@param unsigned long the number of string names enumNames points to
*@param String a pointer to an array of Strings that holds a human
*readable value for each enum type.
*/
template <class PROPERTY_TYPE>  void registerEnumPropertyWithLabels( const String& className, const String& propertyName,
												 _typename_ TypedEnumProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												 _typename_ TypedEnumProperty<PROPERTY_TYPE>::SetFunction propertySetFunction,
												 PROPERTY_TYPE lower, PROPERTY_TYPE upper,
												 const unsigned long& enumNameCount,
												 String* enumNames ){


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
			clazz->addProperty( newProperty );
		}
	}
};



template <class PROPERTY_TYPE>
void registerPrimitiveCollectionProperty( const String& className, const String& propertyName,
												           _typename_ TypedCollectionProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
												           const PropertyDescriptorType& propertyFieldDescriptor ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedCollectionProperty<PROPERTY_TYPE>* newProperty =
							new TypedCollectionProperty<PROPERTY_TYPE>( propertyGetFunction,
							                                       propertyFieldDescriptor );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
};

/**
*this function registers a property with a class, where the PROPERTY_TYPE is defined as some
*Object* derived type in a collection. In registering the collection, you must provide ways
*to enumerate, add, insert, and delete from the collection.
*
*class PROPERTY_TYPE is the template type to base the function on
*@param String className - the name of the class to associate the property with
*@param String propertyName - the name of the property
*@param TypedCollectionProperty<PROPERTY_TYPE>::GetFunction - the property's get function, allows for
*retreiving values from the enum property
*@param TypedCollectionProperty<PROPERTY_TYPE>::AddFunction the collection's add function. Takes an
*item of PROPERTY_TYPE type
*@param TypedCollectionProperty<PROPERTY_TYPE>::InsertFunction the collection's insert function. Takes an
*item of PROPERTY_TYPE type and an index
*@param TypedCollectionProperty<PROPERTY_TYPE>::DeleteFunction1 the collection's delete function. Takes an
*item of PROPERTY_TYPE type
*@param TypedCollectionProperty<PROPERTY_TYPE>::DeleteFunction2 the collection's delete function. Takes
*an index
*/
template <class PROPERTY_TYPE>
void registerObjectCollectionProperty( const String& className, const String& propertyName,
												           _typename_ TypedObjectCollectionProperty<PROPERTY_TYPE>::GetFunction propertyGetFunction,
														   _typename_ TypedObjectCollectionProperty<PROPERTY_TYPE>::AddFunction propertyAddFunction,
														   _typename_ TypedObjectCollectionProperty<PROPERTY_TYPE>::InsertFunction propertyInsertFunction,
														   _typename_ TypedObjectCollectionProperty<PROPERTY_TYPE>::DeleteFunction1 propertyDeleteFunction1,
														   _typename_ TypedObjectCollectionProperty<PROPERTY_TYPE>::DeleteFunction2 propertyDeleteFunction2 ){


	Class* clazz = ClassRegistry::getClass( className );
	if ( NULL != clazz ){
		if ( false == clazz->hasProperty( propertyName ) ){
			TypedObjectCollectionProperty<PROPERTY_TYPE>* newProperty =
							new TypedObjectCollectionProperty<PROPERTY_TYPE>( propertyGetFunction,
							                                             propertyAddFunction,
																		 propertyInsertFunction,
																		 propertyDeleteFunction1,
																		 propertyDeleteFunction2 );
			newProperty->setName( propertyName );
			clazz->addProperty( newProperty );
		}
	}
};


template <typename FieldType>
void registerFieldType( const String& className, const String& fieldName, ulong32 fieldOffset )
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
void registerObjectFieldType( const String& className, const String& fieldName, ulong32 fieldOffset )
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
*@param ulong32 the number of arguments of the method
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
*@param ulong32 the number of arguments of the method
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


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/07 15:05:41  kiklop74
*Fixed building issues with bcb
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/29 03:17:41  marcelloptr
*minor fixes on import/export library macros
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.5.2.1  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.7  2004/03/19 21:25:56  ddiego
*just some minor noodlin
*
*Revision 1.1.2.6  2004/02/21 03:27:07  ddiego
*updates for OSX porting
*
*Revision 1.1.2.5  2004/01/21 19:06:27  ddiego
*fix for bug [ 776440 ] ClassReg doesn't call addImplementedInterface
*
*Revision 1.1.2.4  2004/01/20 03:58:14  ddiego
*mods to datetime and ulong64 to make the GCC compiler happy.
*
*Revision 1.1.2.3  2004/01/19 23:40:41  ddiego
**** empty log message ***
*
*Revision 1.1.2.2  2004/01/18 04:52:46  ddiego
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
*Revision 1.2  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.3  2003/11/03 04:48:54  ddiego
*minor mods
*
*Revision 1.1.2.2  2003/11/02 02:54:34  ddiego
*made some small changes to the method RTTI registration code.
*
*Revision 1.1.2.1  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*/


#endif // _VCF_VCFRTTIIMPL_H__


