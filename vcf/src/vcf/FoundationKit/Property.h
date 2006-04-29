#ifndef _VCF_PROPERTY_H__
#define _VCF_PROPERTY_H__
//Property.h

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
\class Property Property.h "vcf/FoundationKit/Property.h"
*The Property class represents a member attribute of a class. Properties allow a
*programmer to dynamically query a class at runtime for all of it attributes
*with out knowing the exact type of class the object instance is. Property is
*an abstract base class, and only provides an interface to work with.
*
*@author Jim Crafton
*@version 1.0
*/
class FOUNDATIONKIT_API Property  {
public:
	Property(){
		source_ = NULL;
		isCollection_ = false;
		isReadOnly_ = false;
		type_ = pdUndefined;
		bound_ = false;
		//prop_count ++;
		//StringUtils::trace( "Created Property\n\tProperty Count = " + StringUtils::toString(prop_count) + "\n" );
	};

	Property( const Property& prop ):
		value_( prop.value_ )	{

		name_ = prop.name_;
		displayName_ = prop.displayName_;
		description_ = prop.description_;
		type_ = prop.type_;
		source_ = prop.source_;
		isReadOnly_ = prop.isReadOnly_;
		bound_ = prop.bound_;

		//prop_count ++;
		//StringUtils::trace( "Created duplicate Property\n\tProperty Count = " + StringUtils::toString(prop_count) + "\n" );
	};

	virtual ~Property(){
		//prop_count --;
		//StringUtils::trace( "Deleted Property\n\tProperty Count = " + StringUtils::toString(prop_count) + "\n" );
	};

	Property& operator=( const Property& rhs ) {
		value_ = rhs.value_;
		isReadOnly_ = rhs.isReadOnly_;
		isCollection_ = rhs.isCollection_;

		name_ = rhs.name_;
		displayName_ = rhs.displayName_;
		description_ = rhs.description_;
		type_ = rhs.type_;
		source_ = rhs.source_;
		bound_ = rhs.bound_;

		return *this;
	};


	/**
	*makes a copy of the property. Implemented in the templated
	*derived classes.
	*/
	virtual Property* clone() = 0;

	/**
	*gets the name of the property.
	*/
	String getName() const{
		return name_;
	};

	/**
	*returns the display name, usually something longer and more descriptive
	*than the name alone.
	*/
	String getDisplayName() const{
		if ( displayName_.size() > 0 ) {
			return displayName_;
		}else
			return name_;
	};

	/**
	*gets a description of the property,
	*telling what the property does or represents.
	*/
	String getDescription() const{
		return description_;
	};

	/**
	*sets the description of the property
	*/
	void setDescription( const String& description ){
		description_ = description;
	};

	/**
	*sets the display name of the property
	*/
	void setDisplayName( const String& displayName ){
		displayName_ = displayName;
	}

	/**
	*sets the name of the property
	*/
	void setName( const String& name ){
		name_ = name;
	};

	/**
	*This function returns the class name of the property's type.
	*For primitive types it will return the primitive type name, i.e. for
	*a property of type long it will return "long", while a property
	*of type Color will return "VCF::Color".
	*@return String the name of the class that the property represents
	*/
	virtual String getTypeClassName() = 0;
	/**
	*returns the type of the Property. These are the same types as VariantData::type.
	*They can be int, long, unsigned long, short, float, double, char, bool,
	*string, enums or Object*.
	*/
	PropertyDescriptorType getType() const{
		return type_;
	};

	/**
	*sets the type of the Property
	*/
	void setType( const PropertyDescriptorType& type ){
		type_ = type;
		value_.type = type_;
	};

	/**
	*gets the value of the property for the given instance of source.
	*@param Object the object to invoke the get method for that
	*particular property.
	*@return VariantData the value of the given property for that object (source)
	*/
	virtual VariantData* get( Object* source ) = 0;

	/**
	*sets a value on an object.
	*/
	virtual void set( Object* source, VariantData* value ) = 0;

	virtual String toString(){
		String result;
		VariantData* val = get();
		if ( NULL != val ){
			result += val->toString();
		}
		else{
			result += "null";
		}
		return result;
	};

	/**
	*sets the source for the Property instance.
	*@param Object the source object the property instance is
	*associated with. get() and set() calls will be performed
	*on this source object.
	*/
	void setSource( Object* source ){
		source_ = source;
		get();
	};

	/**
	*returns the object source that is associated with this property
	*instance.
	*/
	Object* getSource(){
		return source_;
	}

	/**
	*returns a VariandData object that represents the value of this
	*property on the source object that was specified in the setSource()
	*method.
	*/
	VariantData* get(){
		if ( NULL != source_ ){
			return get( source_ );
		}
		else {
			return NULL;
		}
	};

	/**
	*sets the value specified in the VariantData object passed in
	*on the source obejct that was specified in the setSource()
	*method.
	*/
	void set( VariantData* value ){
		if ( NULL != source_ ){
			set( source_, value );
		}
	};

	/**
	*calls the value_'s setFromString method which converts the
	*string into the right type and then calls set()
	*/
	virtual void set( Object* source, const String& value ){
		value_.setFromString( value );
		set( source, &value_ );
	};

	/**
	*convenience method for calling set on propertys that have their
	*source assigned to a valid pointer.
	*/
	void set( const String& value ){
		if ( NULL != source_ ){
			set( source_, value );
		}
	};

	/**
	*returns whether or not the property represents a collection
	*if the result is true, then it is safe to call the hasMoreElements() and
	*nextElement() methods.
	*/
	bool isCollection(){
		return isCollection_;
	};

	/**
	*returns whether or not the property collection has more elements
	*/
	virtual bool hasMoreElements( Object* source ){
		return false;
	};

	/**
	*returns the next element in the collection, currently only forward
	*iterating. Also no support for getting an item from an index
	*/
	virtual VariantData* nextElement( Object* source ){
		return NULL;
	};

	/**
	*We can't call get() to grab the collection directly, since
	*an Enumerator is a templated class, and this point we
	*don't know the template type. So instead, we call startCollection()
	*to invoke the some getXXX function that returns an enumerator.
	*This will mean that derived classes will now have the enumerator
	*and can start calling methods on it. The base class implementation
	*does nothing.
	*/
	virtual void startCollection( Object* source ){
		//no-op
	};

	void startCollection(){
		if ( NULL != source_ ){
			startCollection( source_ );
		}
	};

	void add( VariantData* value ){
		if ( NULL != source_ ){
			add( source_, value );
		}
	};

	virtual void add( Object* source, VariantData* value ) {
		//no-op
	};

	virtual void insert( Object* source, const unsigned long& index, VariantData* value ){
		//no-op
	};

	void insert( const unsigned long& index, VariantData* value ){
		if ( NULL != source_ ){
			insert( source_, index, value );
		}
	};

	virtual void remove( Object* source, VariantData* value ){
		//no-op
	};

	void remove( VariantData* value ){
		if ( NULL != source_ ){
			remove( source_, value );
		}
	};

	virtual void remove( Object* source, const unsigned long& index ){
		//no-op
	}

	void remove( const unsigned long& index ){
		if ( NULL != source_ ){
			remove( source_, index );
		}
	};

	virtual bool collectionSupportsEditing(){
		return false;
	}

	bool isReadOnly(){
		return isReadOnly_;
	}

	DELEGATE( PropertyChanged )

	/**
	*returns whether or not the property is "bound" to an object.
	*"Bound" properties cause a onPropertyChanged() method to
	*be fired in any listeners whenever the property's set() method
	*is called
	*/
	bool isBound() {
		return bound_;
	};

	void setBound( const bool& bound ){
		bound_ = bound;
	};

protected:
	VariantData value_;
	bool isCollection_;
	bool isReadOnly_;

private:
	String name_;
	String displayName_;
	String description_;
	PropertyDescriptorType type_;
	Object* source_;
	bool bound_;
};


/**
\class EventProperty Property.h "vcf/FoundationKit/Property.h"
*/
class FOUNDATIONKIT_API EventProperty  {
public :
	/**
	Typedef for a getter function for returning a delegate
	*/
	typedef Delegate& (Object::*DelegateMethod)(void);

	typedef void (Object::*EventHandlerMethod)(Event*);


	EventProperty( const String& eventClassName, const String& handlerClassName,
					const String& delegateName, DelegateMethod delegateMethod ){
		eventClassName_ = eventClassName;
		handlerClassName_ = handlerClassName;
		delegateName_ = delegateName;
		source_ = NULL;
		delegateMethod_ = delegateMethod;
	};


	virtual ~EventProperty(){};

	String getEventClassName(){
		return eventClassName_;
	};

	String getHandlerClassName(){
		return handlerClassName_;
	};

	String getDelegateName() {
		return delegateName_;
	}

	virtual bool isAbstract()  = 0;

	virtual EventProperty* clone() = 0;

	/**
	creates a new instance of an EventHandler to use
	@param Object the source for the event handler. If the
	source doesn't derive directly or indirectly from ObjectWithEvents
	then the event handler will not be added to it. If this
	is the case it will be the callers responsibility to clean
	up the memory for the returned EventHandler instance
	@param EventHandlerMethod the method that will be called
	when the EventHandler's invoke() method is called
	@param String the name of the event handler. If this is
	empty then the event handler is not added to source
	@return EventHandler a new event handler that wraps the
	passed in method, and optionally attached to source
	*/
	virtual EventHandler* createEventHandler( Object* source, EventHandlerMethod method, const String& name ) = 0;

	/**
	Get the delegate for the source
	*/
	Delegate* getEventDelegate( Object* source=NULL ) {
		if ( NULL != delegateMethod_ ) {
			if ( NULL != source ) {
				return &(source->*delegateMethod_)();
			}
			else {
				return &(source_->*delegateMethod_)();
			}
		}
		return NULL;
	}

	void setSource( Object* source ) {
		source_ = source;
	}
protected:
	String eventClassName_;
	String handlerClassName_;
	String delegateName_;
	Object* source_;
	DelegateMethod delegateMethod_;
};

/**
\class AbstractEventProperty Property.h "vcf/FoundationKit/Property.h"
*/
class FOUNDATIONKIT_API AbstractEventProperty : public EventProperty {
public:
	AbstractEventProperty( const String& eventClassName, const String& handlerClassName,
			const String& delegateName ):
			EventProperty(eventClassName,handlerClassName,delegateName,NULL)	{}

	virtual EventHandler* createEventHandler( Object* source, EventHandlerMethod method, const String& name ) {
		return NULL;
	}

	virtual EventProperty* clone() {
		return new AbstractEventProperty(*this);
	}

	virtual bool isAbstract() {
		return true;
	}
};


}; //end of namespace VCF


#endif // _VCF_PROPERTY_H__

/**
$Id$
*/
