//InterfaceClass.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//InterfaceClass.h
#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


InterfaceClass::InterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName )
{
	interfaceName_ = interfaceName;
	interfaceID_ = interfaceID;

	superInterfaceClassName_ = superInterfaceName;

	methodContainer_.initContainer( methods_ );
}

InterfaceClass::~InterfaceClass()
{
	std::map<String,Method*>::iterator it = methods_.begin();
	while ( it != methods_.end() ) {
		Method* m = it->second;
		delete m;
		m = NULL;
		it ++;
	}
	methods_.clear();
}

void InterfaceClass::addMethod( Method* method )
{
	methods_[ method->getName() ] = method;
}

bool InterfaceClass::hasMethod( const String& methodName )
{
	std::map<String,Method*>::iterator found = methods_.find( methodName );
	return found != methods_.end();
}

unsigned long InterfaceClass::getMethodCount()
{
	return methods_.size();
}

Method* InterfaceClass::getMethod( const String& methodName )
{
	Method* result = NULL;
	std::map<String,Method*>::iterator found = methods_.find( methodName );
	if ( found != methods_.end() ) {
		result = found->second;
	}
	return result;
}

bool InterfaceClass::isEqual( Object* object ) const
{
	return compareObject( object );
}

void InterfaceClass::setSource( Object* source )
{
	std::map<String,Method*>::iterator it = methods_.begin();
	while ( it != methods_.end() ) {
		Method* m = it->second;
		m->setSource( source );
		it ++;
	}
}

InterfaceClass* InterfaceClass::getSuperInterfaceClass()
{
	InterfaceClass* result = NULL;

	return result;
}


/**
*ImplementedInterfaceClass
*/

ImplementedInterfaceClass::ImplementedInterfaceClass( const String& interfaceName, const String& interfaceID, const String& superInterfaceName ):
	InterfaceClass( interfaceName, interfaceID, superInterfaceName )
{

}

ImplementedInterfaceClass::~ImplementedInterfaceClass()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.4  2004/04/03 17:57:51  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.1  2004/01/11 19:57:55  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.7  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.16.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.16.1  2003/03/12 03:13:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


