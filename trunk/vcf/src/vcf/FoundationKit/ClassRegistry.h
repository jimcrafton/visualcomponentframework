#ifndef _VCF_CLASSREGISTRY_H__
#define _VCF_CLASSREGISTRY_H__
//ClassRegistry.h

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
*ClassRegistry contains all Class's in the Framework Runtime.
*The ClassRegistry is used by the Framework Runtime to register Classes
*and properties for Classes. The ClassRegistry is also used to dynamically
*create new instances of a class from a class name.
*
*@author Jim Crafton
*@version 1.0
*/
class FOUNDATIONKIT_API ClassRegistry {
public:
	static ClassRegistry* create();

	static void terminate();

	ClassRegistry();

	virtual ~ClassRegistry();

	/**
	*returns a Class object from a string. If no matching
	*Class exists the function returns NULL.
	*In terms of efficiency, this function is faster than
	*getClass( Object*)
	*@param String the name of the class to find
	*@return Class the class associated with the className
	*/
	static Class* getClass( const String& className );

	/**
	*returns a Class object from a string representing a ClassID/UUID.
	*If no matching Class exists the function returns NULL.
	*In terms of efficiency, this function is faster than
	*getClass( Object*)
	*@param String the UUID or ClassID of the class to find
	*@return Class the class associated with the ClassID
	*/
	static Class* getClassFromClassID( const String& classID );

	/**
	*returns a Class object for the object passed in.
	*@param Object the object instance to get a class for
	*@return Class the class associated with the object
	*/
	static Class* getClass( Object* object ) ;

	/**
	*creates a new instance of an object based on the class name.
	*@param String the class name of the object to create
	*@param Object a pointer to the newly created object
	*/
	static Object* createNewInstance( const String& className ) ;

	/**
	*creates a new instance of an object based on the classID.
	*@param String the classID of the object to create
	*@param Object a pointer to the newly created object
	*/
	static Object* createNewInstanceFromClassID( const String& classID ) ;

	/**
	*see ImplementedInterfaceClass::createInterfaceInstance()
	*/
	static void* createNewInterfaceInstanceFromInterfaceName( const String& interfaceName, const String& implementerClassName );

	/**
	*see ImplementedInterfaceClass::createInterfaceInstance()
	*/
	static void* createNewInterfaceInstanceFromInterfaceID( const String& interfaceID, const String& implementerClassID );

	/**
	*adds a new Class object to the ClassRegistry
	*@param String the name of the class
	*@param Class the Class object to register
	*/
	static void addClass( const String& className, Class* classToRegister );

	static void removeClass( const String& className );
	static void removeClassByID( const String& classID );

	/**
	*adds a new InterfaceClass object to the ClassRegistry that represents
	*a particular interface
	*@param String the name of the interface
	*@param InterfaceClass the InterfaceClass object to register
	*/
	static void addInterface( const String& interfaceName, InterfaceClass* interfaceToRegister );
	static void removeInterface( const String& interfaceName );
	static void removeInterfaceByID( const String& interfaceID );

	/**
	*returns an enumeration of all the classes in the system at the time
	*of the call
	*/
	static Enumerator<Class*>* getClasses() ;

	static Enumerator<InterfaceClass*>* getInterfaces() ;

	/**
	*returns a ImplementedInterfaceClass object from a string. If no matching
	*ImplementedInterfaceClass exists the function returns NULL.
	*@param String the name of the implementing class to find
	*@paramString the interface UUID to find
	*@return ImplementedInterfaceClass the implemented interface associated with the implementingClassName
	*/
	static ImplementedInterfaceClass* getImplementedInterface( const String& implementingClassName, const String& interfaceID );

	/**
	*returns a InterfaceClass object from a string. If no matching
	*InterfaceClass exists the function returns NULL.
	*@param String the name of the interface to find
	*@return InterfaceClass the interface associated with the interfaceName
	*/
	static InterfaceClass* getInterface( const String& interfaceName ) ;

	/**
	*returns a InterfaceClass object from a string ID. If no matching
	*InterfaceClass exists the function returns NULL.
	*@param String the UUID of the interface to find
	*@return InterfaceClass the interface associated with the interfaceName
	*/
	static InterfaceClass* getInterfaceFromInterfaceID( const String& interfaceID );

	/**
	*Adds an implemented interface class to the registry
	*/
	static void addImplementedInterface( ImplementedInterfaceClass* interfaceToRegister, const String& implementerClassID );

	/**
	*attempts to register the method with the class or interface
	*@return bool represents whether or not the registration attempt
	*was successful. If the method returns false then the caller must
	*free the Method object that was passed in
	*/
	static bool registerMethod( Method* method, const String& className, const bool& isInterfaceMethod );


	/**
	*attempts to register the method with the class or interface
	*@param Method the Method object that represents the method to registered
	*@param String the UUID of the class or interface to register the Method
	*with
	*@param bool whether or not the Method is associated with an Interface
	*or a Class.
	*@return bool represents whether or not the registration attempt
	*was successful. If the method returns false then the caller must
	*free the Method object that was passed in
	*/
	static bool registerMethodByUUID( Method* method, const String& UUID, const bool& isInterfaceMethod );

	/**
	*Dumps out the classes in registery to stdout
	*/
	static void dump();

	/**
	Removes a class from teh ClassRegistry.
	Dynamically loaded libraries should call this prior to termination to
	prevent bad memory from being deleted
	*/

	static void removeClass( Class* clazz );

	static void removeInterface( InterfaceClass* interfaceClass );
protected:
	Class* internal_getClass( const String& className );

	Class* internal_getClassFromClassID( const String& classID );

	Class* internal_getClass( Object* object ) ;

	Object* internal_createNewInstance( const String& className ) ;

	Object* internal_createNewInstanceFromClassID( const String& classID ) ;

	void* internal_createNewInterfaceInstanceFromInterfaceName( const String& interfaceName, const String& implementerClassName );

	void* internal_createNewInterfaceInstanceFromInterfaceID( const String& interfaceID, const String& implementerClassID );

	void internal_addClass( const String& className, Class* classToRegister );

	void internal_addInterface( const String& interfaceName, InterfaceClass* interfaceToRegister );

	Enumerator<Class*>* internal_getClasses() ;

	Enumerator<InterfaceClass*>* internal_getInterfaces() ;

	ImplementedInterfaceClass* internal_getImplementedInterface( const String& implementingClassName, const String& interfaceID );

	InterfaceClass* internal_getInterface( const String& interfaceName ) ;

	InterfaceClass* internal_getInterfaceFromInterfaceID( const String& interfaceID );

	void internal_addImplementedInterface( ImplementedInterfaceClass* interfaceToRegister, const String& implementerClassID );

	bool internal_registerMethod( Method* method, const String& className, const bool& isInterfaceMethod );


	bool internal_registerMethodByUUID( Method* method, const String& UUID, const bool& isInterfaceMethod );

	void internal_dump();

	static ClassRegistry* registryInstance_;

	/**
	*a static function that returns the global instance of the ClassRegistry.
	*/
	static ClassRegistry* getClassRegistry();

	EnumeratorMapContainer<std::map<String,Class*>,Class*> classContainer_;
	EnumeratorMapContainer<std::map<String,InterfaceClass*>,InterfaceClass*> interfaceContainer_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the class name
	*/
	std::map<String,Class*> classMap_;

	/**
	*a map of all the interfaces in the ClassRegistry. keyed by the interface name
	*/
	std::map<String,InterfaceClass*> interfaceMap_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the classID
	*/
	std::map<String,InterfaceClass*> interfaceIDMap_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the classID
	*/
	std::map<String,ImplementedInterfaceClass*> implementedInterfacesIDMap_;

	/**
	*a map of all the classes in the ClassRegistry. keyed by the classID
	*/
	std::map<String,Class*> classIDMap_;

};




};


/**
*CVS Log info
*$Log$
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
*Revision 1.4.2.2  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4.2.1  2004/04/10 04:37:19  ddiego
*added a MIMType class that parses mime types.
*
*Revision 1.4  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.2  2004/01/21 19:06:26  ddiego
*fix for bug [ 776440 ] ClassReg doesn't call addImplementedInterface
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
*Revision 1.25  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.24.2.3  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.24.2.2  2003/09/12 16:46:33  ddiego
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
*Revision 1.24.2.1  2003/09/10 04:23:48  ddiego
*minor cahnge to class registry to allow you to remove registered classes
*
*Revision 1.24  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.23.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.23  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.3  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
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
*Revision 1.21.8.2  2002/12/27 23:04:30  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21.8.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.21  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.20.12.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.20  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CLASSREGISTRY_H__


