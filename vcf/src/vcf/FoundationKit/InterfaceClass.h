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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
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
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.8  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/12 03:09:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2002/12/27 23:04:31  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_INTERFACECLASS_H__


