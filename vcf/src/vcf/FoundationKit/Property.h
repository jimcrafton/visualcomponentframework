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
		}
		
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
	*They can be int, long, uint32, short, float, double, char, bool,
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
	Some properties may be a collection of some sort.
	The following functions are designed to provide
	indexed access to the collection and to allow 
	for adding/removing entries to the collection
	*/

	/**
	Indicates whether or not the property is a collection.
	Most properties will obviously return false. If the 
	property supports a collection, then it should return true.
	*/
	bool isCollection(){
		return isCollection_;
	};


	/**
	Returns the number of elements in the property's collection
	*/
	virtual uint32 getCollectionCount() {
		return getCollectionCount( source_ );
	}

	virtual uint32 getCollectionCount( Object* source ) {
		return 0;
	}

	/**
	Returns the element at the specified key. Typically this is an
	index into some array like container, but it's possibly it could be
	a key into a container like a map or Dictionary.
	*/
	virtual VariantData* getAtKey( const VariantData& key ){
		if ( NULL != source_ ){
			return getAtKey( key, source_ );
		}
		else {
			return NULL;
		}
	};

	/**
	Returns the element of the collection at the specified index. If the
	index is out of bounds (greater than or equal to the total number of 
	elements in the collection) then an exception is thrown.
	*/
	virtual VariantData* getAtKey( const VariantData& key, Object* source ){
		
		return NULL;
	};

	/**
	Sets the value of the element at the specified index. If the
	index is out of bounds (greater than or equal to the total number of 
	elements in the collection) then an exception is thrown. 
	@param VariantData the key, frequently just an index
	@param VariantData the value
	@param bool whether or not the collection should add any entries if 
	necessary. For example, if the key is 0, and the collection is empty,
	if addMissingValues is true, then a new entry will be created first
	before assign it the new value passed in.
	*/
	virtual void setAtKey( const VariantData& key, VariantData* value, bool addMissingValues=false ){
		if ( NULL != source_ ){
			setAtKey( key, value, source_, addMissingValues );
		}
	};

	virtual void setAtKey( const VariantData& key, const String& value, bool addMissingValues=false ){
		if ( NULL != source_ ){
			setAtKey( key, value, source_, addMissingValues );
		}
	};

	virtual void setAtKey( const VariantData& key, VariantData* value, Object* source, bool addMissingValues=false ){
		//no-op
	};

	virtual void setAtKey( const VariantData& key, const String& value, Object* source, bool addMissingValues=false ){
		value_.setFromString( value );

		setAtKey( key, &value_, source_, addMissingValues );
	};

	/**
	Adds an element to the property collection
	*/
	void add( VariantData* value ){
		if ( NULL != source_ ){
			add( source_, value );
		}
	};

	/**
	Adds an element to the property collection. Note that the
	default implementation is to do nothing. Implementers
	will need to reimplement this function to provide
	for correct behavior.
	*/
	virtual void add( Object* source, VariantData* value ) {
		//no-op
	};

	/**
	Inserts an element into the property collection. Note that the
	default implementation is to do nothing. Implementers
	will need to reimplement this function to provide
	for correct behavior.
	*/
	virtual void insert( const VariantData& key, VariantData* value, Object* source ){
		//no-op
	};

	/**
	Inserts an element into the property collection. Note that the
	default implementation is to do nothing. Implementers
	will need to reimplement this function to provide
	for correct behavior.
	*/
	void insert( const VariantData& key, VariantData* value ){
		if ( NULL != source_ ){
			insert( key, value, source_ );
		}
	};

	/**
	Removes an element from the property collection at the
	specified index. Note that the default implementation 
	is to do nothing. Implementers will need to reimplement 
	this function to provide for correct behavior.
	*/
	virtual void remove( const VariantData& key, Object* source ){
		//no-op
	}

	/**
	Removes an element from the property collection at the
	specified index. Note that the default implementation 
	is to do nothing. Implementers will need to reimplement 
	this function to provide for correct behavior.
	*/
	void remove( const VariantData& key ){
		if ( NULL != source_ ){
			remove( key, source_ );
		}
	};

	/**
	This indicates whether or not the property for the collection
	will allow any modifications (add/insert/remove) to
	take place. The default behavior is to disallow these functions.
	*/
	virtual bool collectionSupportsEditing(){
		return false;
	}

	bool isReadOnly(){
		return isReadOnly_;
	}

	DELEGATE( PropertyChangeDelegate, PropertyChanged )

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
\class DelegateProperty Property.h "vcf/FoundationKit/Property.h"
*/
class FOUNDATIONKIT_API DelegateProperty  {
public :
	/**
	Typedef for a getter function for returning a delegate
	*/
	typedef Delegate& (Object::*DelegateMethod)(void);


	DelegateProperty( const String& delegateClassName,
					const String& delegateName, DelegateMethod delegateMethod ){		
		delegateClassName_ = delegateClassName;
		delegateName_ = delegateName;
		source_ = NULL;
		delegateMethod_ = delegateMethod;
	};


	virtual ~DelegateProperty(){};

	String getDelegateClassName(){
		return delegateClassName_;
	};

	String getDelegateName() {
		return delegateName_;
	}

	virtual bool isAbstract()  = 0;

	virtual DelegateProperty* clone() = 0;

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
	//virtual CallBack* createEventHandler( Object* source, EventHandlerMethod method, const String& name ) = 0;

	/**
	Get the delegate for the source
	*/
	Delegate* getDelegateInstance( Object* source=NULL ) {
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
	String delegateClassName_;
	String delegateName_;
	Object* source_;
	DelegateMethod delegateMethod_;
};

/**
\class AbstractDelegateProperty Property.h "vcf/FoundationKit/Property.h"
*/
class FOUNDATIONKIT_API AbstractDelegateProperty : public DelegateProperty {
public:
	AbstractDelegateProperty( const String& delegateClassName,
			const String& delegateName ):
			DelegateProperty(delegateClassName,delegateName,NULL)	{}

/*	virtual EventHandler* createEventHandler( Object* source, EventHandlerMethod method, const String& name ) {
		return NULL;
	}
	*/

	virtual DelegateProperty* clone() {
		return new AbstractDelegateProperty(*this);
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
