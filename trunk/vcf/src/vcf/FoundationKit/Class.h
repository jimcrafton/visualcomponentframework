#ifndef _VCF_CLASS_H__
#define _VCF_CLASS_H__
//Class.h

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

class Property;
class Method;
class EventProperty;
class InterfaceClass;
class Field;

/**
*common class names for native types, like int, long, char, bool, etc.
*/
#define CLASS_INTEGER		"integer"
#define CLASS_INT			"integer"
#define CLASS_UINT			"uint"
#define CLASS_LONG			"long"
#define CLASS_ULONG			"ulong"
#define CLASS_FLOAT			"float"
#define CLASS_DOUBLE		"double"
#define CLASS_CHAR			"char"
#define CLASS_BOOL			"bool"
#define CLASS_SHORT			"short"
#define CLASS_USHORT		"ushort"
#define CLASS_ENUM			"enum"
#define CLASS_STRING		"string"

/**
\class Class Class.h "vcf/FoundationKit/Class.h"
Class is the base class for all RTTI in the Framework. Class was written
because C++ RTTI is shockingly primitive, and many of these features are
found in other OO languages (i.e. ObjectPascal, ObjectiveC, SmallTalk, 
Java, et. al) and are immensely useful and powerful.

Class is an abstract base class that template class's derive from. Classes 
provide the following information:
	\li
	the name of the Class - this is stored in a member variable rather
	than relying on typeid().name() to retreive the class name. Not all
	compiler's support the typeid().name() function (i.e. MSVC 6.0 does, Borland
	probably does, but GCC does not)
	

	\li
	the Class ID - this represents a UUID for the class. This will prove useful
	when distributed features creep in.
	

	\li
	the ability to discover all the properties of a Class at runtime. A property
	is defined as some class attribute that is provided access to via getter and
	setter methods. Properties can be primitive types (int, long double, etc) or
	Object derived types, or enums. Properties can also be collections of other
	properties.
	

	\li
	retreiving the super class of the class.
	

	\li
	the ability to create a new instance of the class the Class object represents.
	This of course assumes a default constructor is available.
	

In order for the RTTI to work in the Framework developers of derived classes 
must do three things for their classes to participate in the Framework. Failure 
to implement these steps will mean their classes will not have correct RTTI. A 
series of macros (defined in ClassInfo.h) have been written to make this easier.

The first step is (obviously) making sure that your class is derived from a Framework object.
For example:
\code
	class Foo : public VCF::Object {  //this is OK
	...
	};

	class Foo {  //this is bad - there is no way to hook the RTTI up without at
	...					//least deriving from VCF::Object
	};
\endcode


Next you should define a class id (as a string) for your class. If you are on winblows use
guidgen.exe to create UUID's for you. The define should look something like this:
\code
#define FOO_CLASSID			"1E8CBE21-2915-11d4-8E88-00207811CFAB"
\endcode
The next step is to add to macros to your class defintion (.h/.hpp file). These are required
for the basic RTTI info (class-super class relation ships) and to make sure you'll inherit
any properties of your super class. For example:
\code
	class Foo : public VCF::Object {
		_class_rtti_(Foo, "VCF::Object", FOO_CLASSID)
		_class_rtti_end_
	...
	};
\endcode
The macros create a public nested class used to register your class that you're writing.
The above macros generate the following inline code for the developer of the Foo class.
\code
	class Foo : public VCF::Object {
		class Foo_rtti_ClassInfo : public VCF::ClassInfo<Foo> { 
		public: 
			typedef Foo RttiClassType;
			Foo_rtti_ClassInfo (): 
			VCF::ClassInfo<RttiClassType>( VCF::StringUtils::getClassNameFromTypeInfo(typeid(Foo)), 
											"VCF::Object", 
											"1E8CBE21-2915-11d4-8E88-00207811CFAB" ){ 

				VCF::String tmpClassName = VCF::StringUtils::getClassNameFromTypeInfo(typeid(Foo)); 
				if ( isClassRegistered()  ){ 
				
				}
			}
		};//end of FooInfo
		...
	};
\endcode

The next step is to add any properties to the class. This is optional and is only neccessary if
the you want to expose the properties of the class you're writing. Adding properties is also
done through macros and looks like this:
\code
	class Foo : public VCF::Object {
		_class_rtti_(Foo, "VCF::Object", FOO_CLASSID)
		_property_( double, "fooVal", getFooVal, setFooVal, "The foo value property" )
		_class_rtti_end_
	...
	double getFooVal();
	void setFooVal( const double& val );
	...
	};
\endcode
If the properties are Object derived properties then the following can be done:
\code
	class Foo : public VCF::Object {
		_class_rtti_(Foo, "VCF::Object", FOO_CLASSID)
		_property_object_( Foo, "fooObj", getFoo, setFoo, "The Foo object property" )
		_class_rtti_end_(Foo)
	...
	Foo* getFoo();
	void setFoo( Foo* val );
	...
	};
\endcode
@author Jim Crafton
@version 1.0
*/
class FOUNDATIONKIT_API Class {
public:
	/**
	the constructor for a new Class.
	@param String the class name of the class
	@param String the class id for the class. This MUST be a string
	that represents unique ID as returned by a UUID function/algorithm
	the format is this:
	96B6A350-2873-11d4-8E88-00207811CFAB
	
	@param String the name of the class's super class
	*/
	Class( const String& className, const String& classID, const String& superClass );

	virtual ~Class();

	/**
	returns the super class for the class. If the Rect::getClass() was called
	and then getSuperClass() was called on the return value of Rect::getClass(),
	the return would be a Class* for Object.
	*/
	Class* getSuperClass();

	/**
	returns the class id for the class. Class's may have the same name
	so to prevent this, an ID is provided. This is ID MUST be generated using
	some algorithm that guarantees a valid UUID
	*/
	String getID();

	/**
	returns the class name for the Class
	*/
	String getClassName();

	/**
	returns an enumerator containing the Property values
	the enumerator does not reflect the order in which the properties were added.
	*/
	Enumerator<Property*>* getProperties(){
		return propertyContainer_.getEnumerator();
	};

	/**
	returns an enumerator containing the Field values
	the enumerator does not reflect the order in which the fields were added.
	*/
	Enumerator<Field*>* getFields(){
		return fieldContainer_.getEnumerator();
	};

	/**
	returns an enumerator containing the Methods of the Class
	the enumerator does not reflect the order in which the properties were added.
	*/
	Enumerator<Method*>* getMethods(){
		return methodContainer_.getEnumerator();
	};


	/**
	adds a new property to the Class's property map.
	*/
	void addProperty( Property* property );

	/**
	does the Class have a have a particular property ?
	@param String the name of the property to find
	@return bool true if the class has the specified property, otherwise false
	*/
	bool hasProperty( const String& propertyName );

	/**
	the number of properties the Class has
	*/
	unsigned long getPropertyCount();

	/**
	gets the property specified by propertyName, if the class
	has that property.
	@param String the name of the property to try and retrieve
	@return Property a pointer to a property of the class.
	*/
	Property* getProperty( const String& propertyName );




	/**
	adds a new property to the Class's property map.
	*/
	void addField( Field* field );

	/**
	does the Class have a have a particular property ?
	@param String the name of the property to find
	@return bool true if the class has the specified property, otherwise false
	*/
	bool hasField( const String& fieldName );

	/**
	the number of fields the Class has
	*/
	unsigned long getFieldCount();

	/**
	gets the field (or member variable) specified by fieldName, if the class
	has that field.
	@param String the name of the field to try and retrieve
	@return Field a pointer to a field of the class.
	*/
	Field* getField( const String& fieldName );


	/**
	adds a new property to the Class's property map.
	*/
	void addMethod( Method* method );

	/**
	does the Class have a have a particular property ?
	@param String the name of the property to find
	@return bool true if the class has the specified property, otherwise false
	*/
	bool hasMethod( const String& methodName );

	/**
	the number of methods the Class has
	*/
	unsigned long getMethodCount();

	/**
	gets the method specified by methodName, if the class
	has that method.
	@param String the name of the method to try and retrieve
	@return Method a pointer to a method of the class.
	*/
	Method* getMethod( const String& methodName );

	/**
	Adds an event to the Class
	@param EventProperty* the event to add - see EventProperty for more info.
	*/
	void addEvent( EventProperty* event );

	/**
	does the Class have this particular event handler ?
	@return bool returns true if the Class has an event handler by this name
	*/
	bool hasEventHandler( const String& delegateName );

	/**
	returns an enumerator containing the EventProperty values.
	the enumerator does not reflect the order in which the events were added.
	*/
	Enumerator<EventProperty*>* getEvents(){
		return eventContainer_.getEnumerator();
	};

	/**
	Returns an EventProperty by name
	@param String the event delegate to return
	*/
	EventProperty* getEvent( const String& delegateName );

	/**
	Returns an enumeration of interfaces implemented by this class
	*/
	Enumerator<InterfaceClass*>* getInterfaces() {
		return interfaceContainer_.getEnumerator();
	}

	unsigned long getInterfaceCount();

	bool hasInterface( const String& interfaceName );

	bool hasInterfaceID( const String& interfaceID );

	InterfaceClass* getInterfaceByName( const String& interfaceName );

	InterfaceClass* getInterfaceByID( const String& interfaceID );

	void addInterface( InterfaceClass* newInterface );

	/**
	compares an object to the stored object instance. This uses
	typeid which is OK in GCC. The actual compare is made in compareObject()
	which is implemented in the derived Template classes
	@param Object another Class instance to compare this Class instance to
	@return bool true if the object's typeid is equal to this' typeid
	*/
	virtual bool isEqual( Object* object )const{
		return compareObject( object );
	};

	/**
	creates a new instance of an Object based on the Class Type.
	Actual implementation is performed by the template instance of the
	class.
	*/
	virtual Object* createInstance() const = 0;

	/**
	Used to compare the object instance passed in with the class type.
	Implemented in the template derived class so a type safe compare is
	made.
	*/
	virtual bool compareObject( Object* object )const = 0;

	/**
	sets the source of all properties in the Class to source.
	@param Object the source to which the properties are set
	*/
	void setSource( Object* source );

	/**
	returns the class name of a Property. This will also
	return the correct type for C++ basic pritives (i.e. int,
	bool, etc)
	*/
	static String getClassNameForProperty( Property* property );
private:
	String className_;
	String classID_;
	String superClassName_;
	Class* superClass_;
	std::map<String,Property*> properties_;
	EnumeratorMapContainer<std::map<String,Property*>,Property*> propertyContainer_;

	std::map<String,Field*> fields_;
	EnumeratorMapContainer<std::map<String,Field*>,Field*> fieldContainer_;

	std::map<String,Method*> methods_;
	EnumeratorMapContainer<std::map<String,Method*>,Method*> methodContainer_;

	std::map<String, EventProperty*> events_;
	EnumeratorMapContainer<std::map<String,EventProperty*>,EventProperty*> eventContainer_;

	std::map<String, InterfaceClass*> interfaces_;
	EnumeratorMapContainer<std::map<String,InterfaceClass*>,InterfaceClass*> interfaceContainer_;

};



};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.4  2006/04/05 03:35:59  ddiego
*post cvs crash updates.
*
*Revision 1.3.2.3  2006/03/26 22:37:34  ddiego
*minor update to source docs.
*
*Revision 1.3.2.2  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.3.2.1  2006/02/23 01:41:57  ddiego
*some minor changes to teh variantdata class, added support for specific char* and WideChar* cosntructor and for unsigned short types.
*
*Revision 1.3  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
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
*Revision 1.15  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.14  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:09:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.14.1  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.12  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.11  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CLASS_H__


