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


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/04/05 03:35:59  ddiego
*post cvs crash updates.
*
*Revision 1.3.2.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.3  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/05/16 02:39:09  ddiego
*OSX code updates
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.5.2.1  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.3  2004/01/21 19:06:26  ddiego
*fix for bug [ 776440 ] ClassReg doesn't call addImplementedInterface
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
*Revision 1.24  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.23.4.7  2003/11/03 04:48:54  ddiego
*minor mods
*
*Revision 1.23.4.6  2003/11/02 02:54:34  ddiego
*made some small changes to the method RTTI registration code.
*
*Revision 1.23.4.5  2003/10/24 04:03:36  ddiego
*More header musical chairs
*
*Revision 1.23.4.4  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.23.4.3  2003/10/04 20:14:59  ddiego
*aaddec changes to support compiling on GCC 3.3.1, which is much more
*picky than some of the previous versions.
*
*Revision 1.23.4.2  2003/09/12 16:46:33  ddiego
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
*Revision 1.23.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.23  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
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
*Revision 1.21.14.2  2002/12/27 23:04:30  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21.14.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.21  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.20.4.2  2002/03/25 04:19:45  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.20.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.20  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CLASSINFO_H__


