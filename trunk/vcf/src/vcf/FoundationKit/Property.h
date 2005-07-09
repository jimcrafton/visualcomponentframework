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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/07/01 15:34:36  marcelloptr
*added assignment operator
*
*Revision 1.2.4.1  2005/01/07 23:21:48  marcelloptr
*fixed forgotten initialization
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.3  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
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
*Revision 1.28  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.27.4.5  2003/10/24 04:03:36  ddiego
*More header musical chairs
*
*Revision 1.27.4.4  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.27.4.3  2003/09/15 02:52:52  ddiego
*miscellaneous changes
*
*Revision 1.27.4.2  2003/09/12 16:46:33  ddiego
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
*Revision 1.27.4.1  2003/09/11 03:54:53  ddiego
*fixed a bug in the ClassRegistry when adding a new Class. Previously
*it was not properly copying methods from super class. This is now fixed
*Made the EventProperty class exported
*
*Revision 1.27  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.26.2.2  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.26.2.1  2003/03/12 03:09:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.26  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.25.8.4  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.25.8.3  2002/12/27 23:04:32  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.25.8.2  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.25.8.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.25  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.24.6.2  2002/09/03 05:05:13  ddiego
*fixed some more bugs in getting form building to work again. It now works
*but of course there are new issues, namely reading in nested properties
*in a form file where the properties are objects like:
*font.color.red, so this needs to be fixed in hte VFFInputStream file
*also need to have hte form saved properly
*still miscellaneous crashes but getting closer to an alpha tes state
*
*Revision 1.24.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.24  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.23.4.3  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.23.4.2  2002/03/25 04:19:45  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.23.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.23  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PROPERTY_H__


