//Class.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;



Class::Class( const String& className, const String& classID, const String& superClass )
{
	className_ = className;
	classID_ = classID;
	superClass_ = NULL;
	superClassName_ = superClass;
	propertyContainer_.initContainer( properties_ );
	eventContainer_.initContainer( events_ );
	interfaceContainer_.initContainer( interfaces_ );
	methodContainer_.initContainer(methods_);
	fieldContainer_.initContainer(fields_);

}

Class::~Class()
{
	std::map<String,Property*>::iterator props = properties_.begin();

	while ( props != properties_.end() ){
		Property* prop = props->second;
		delete prop;
		props++;
	}

	properties_.clear();


	std::map<String,Field*>::iterator fields = fields_.begin();

	while ( fields != fields_.end() ){
		Field* field = fields->second;
		delete field;
		fields++;
	}

	fields_.clear();

	std::map<String,EventProperty*>::iterator events = events_.begin();
	while ( events != events_.end() ){
		delete events->second;
		events ++;
	}
	events_.clear();

	std::map<String,Method*>::iterator methods = methods_.begin();
	while ( methods != methods_.end() ){
		Method* method = methods->second;
		delete method;
		method = NULL;
		methods++;
	}
	methods_.clear();

	std::map<String,InterfaceClass*>::iterator interfaces = interfaces_.begin();
	while ( interfaces != interfaces_.end() ){
		InterfaceClass* ic = interfaces->second;
		delete ic;
		ic = NULL;
		interfaces++;
	}
	interfaces_.clear();
}

String Class::getClassName()
{
	return className_;
}

bool Class::hasProperty( const String& propertyName )
{
	bool result = false;
    std::map<String,Property*>::iterator found = properties_.find( propertyName );
	result = (found != properties_.end());
	return result;
}

Property* Class::getProperty( const String& propertyName )
{
	Property* result = NULL;

	std::map<String,Property*>::iterator found = properties_.find( propertyName );
	if ( found != properties_.end() ){
		result = found->second;
	}

	return result;
}

void Class::addEvent( EventProperty* event )
{
	if ( NULL != event ) {
		String delegateName = event->getDelegateName();
		events_[delegateName] = event;
	}
}

EventProperty* Class::getEvent( const String& delegateName )
{
	EventProperty* result = NULL;
	std::map<String,EventProperty*>::iterator found = events_.find( delegateName );
	if ( found != events_.end() ) {
		result = found->second;
	}
	return result;
}

bool Class::hasEventHandler( const String& delegateName )
{
	bool result = false;
	std::map<String,EventProperty*>::iterator found = events_.find( delegateName );
	result = (found != events_.end());
	return result;
}

void Class::addProperty( Property* property )
{
	if ( NULL != property ){

		String name = property->getName();

		properties_[name] = property;
	}
}

void Class::addMethod( Method* method )
{
	if ( NULL != method ){
		String name = method->getName();
		if ( false == hasMethod( name ) ){
			methods_[name] = method;
		}
	}
}

bool Class::hasMethod( const String& methodName ){
	bool result = false;
    std::map<String,Method*>::iterator found = methods_.find( methodName );
	result = (found != methods_.end());
	return result;
}

unsigned long Class::getMethodCount(){
	return methods_.size();
}

Method* Class::getMethod( const String& methodName ){
	Method* result = NULL;

	std::map<String,Method*>::iterator found = methods_.find( methodName );
	if ( found != methods_.end() ){
		result = found->second;
	}

	return result;
}


void Class::addField( Field* field )
{
	if ( NULL != field ){
		String name = field->getName();
		if ( false == hasField( name ) ){
			fields_[name] = field;
		}
	}
}

bool Class::hasField( const String& fieldName ){
	bool result = false;
    std::map<String,Field*>::iterator found = fields_.find( fieldName );
	result = (found != fields_.end());
	return result;
}

unsigned long Class::getFieldCount(){
	return fields_.size();
}

Field* Class::getField( const String& fieldName ){
	Field* result = NULL;

	std::map<String,Field*>::iterator found = fields_.find( fieldName );
	if ( found != fields_.end() ){
		result = found->second;
	}

	return result;
}



void Class::setSource( Object* source )
{
	std::map<String,Property*>::iterator props = properties_.begin();
	while ( props != properties_.end() ){
		props->second->setSource( source );
		props++;
	}

	std::map<String,Field*>::iterator fields = fields_.begin();
	while ( fields != fields_.end() ){
		fields->second->setSource( source );
		fields++;
	}

	std::map<String,Method*>::iterator methods = methods_.begin();
	while ( methods != methods_.end() ){
		Method* method = methods->second;
		method->setSource( source );
		methods++;
	}

	std::map<String,InterfaceClass*>::iterator interfaces = interfaces_.begin();
	while ( interfaces != interfaces_.end() ){
		InterfaceClass* interfaceClass = interfaces->second;
		interfaceClass->setSource( source );
		interfaces++;
	}
}

unsigned long Class::getPropertyCount()
{
	return properties_.size();
}

String Class::getID()
{
	return classID_;
}

Class* Class::getSuperClass()
{
	if ( NULL == superClass_ ){

		superClass_ = ClassRegistry::getClass( superClassName_ );

	}
	return superClass_;
}

String Class::getClassNameForProperty( Property* property )
{
	String result = "";

	if ( NULL != property ){
		VariantData* val = property->get();
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

				case pdObject: {
					result = property->getTypeClassName();
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

				case pdUndefined: {
					//no-op
				}
				break;

				case pdInterface: {
					//no-op
				}
				break;
			}
		}
	}

	return result;
}

unsigned long Class::getInterfaceCount()
{
	return interfaces_.size();
}

bool Class::hasInterface( const String& interfaceName )
{
	bool result = false;
	std::map<String, InterfaceClass*>::iterator it = interfaces_.begin();
	while ( (false == result) && (it != interfaces_.end()) )  {
		InterfaceClass* ic = it->second;
		if ( interfaceName == ic->getInterfaceName() ) {
			result = true;
		}
		it ++;
	}

	return result;
}

bool Class::hasInterfaceID( const String& interfaceID )
{
	std::map<String, InterfaceClass*>::iterator found = interfaces_.find( interfaceID );
	return found != interfaces_.end();
}

InterfaceClass* Class::getInterfaceByName( const String& interfaceName )
{
	InterfaceClass* result = NULL;

	std::map<String, InterfaceClass*>::iterator it = interfaces_.begin();
	while ( (NULL == result) && (it != interfaces_.end()) )  {
		InterfaceClass* ic = it->second;
		if ( interfaceName == ic->getInterfaceName() ) {
			result = ic;
		}
		it ++;
	}

	return result;
}

InterfaceClass* Class::getInterfaceByID( const String& interfaceID )
{
	InterfaceClass* result = NULL;

	std::map<String, InterfaceClass*>::iterator found = interfaces_.find( interfaceID );
	if ( found != interfaces_.end() ) {
		result = found->second;
	}

	return result;
}

void Class::addInterface( InterfaceClass* newInterface )
{
	interfaces_[ newInterface->getID() ] = newInterface;
	//copy over method from existing interface in classregistry
	//if any exist

	ClassRegistry::getInterfaceFromInterfaceID( newInterface->getID() );

	InterfaceClass* existingInterface = ClassRegistry::getInterfaceFromInterfaceID( newInterface->getID() );
	if ( NULL != existingInterface ) {
		Enumerator<Method*>* methods = existingInterface->getMethods();
		while ( true == methods->hasMoreElements() ) {
			Method* method = methods->nextElement();

			if ( false == newInterface->hasMethod( method->getName() ) ) {
				newInterface->addMethod( (Method*)method->clone() );
			}
		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.4  2004/04/03 17:57:51  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.2  2004/01/21 19:06:43  ddiego
*fix for bug [ 776440 ] ClassReg doesn't call addImplementedInterface
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
*Revision 1.20  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.19.2.3  2003/11/02 02:54:44  ddiego
*made some small changes to the method RTTI registration code.
*
*Revision 1.19.2.2  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.19.2.1  2003/09/15 02:52:36  ddiego
*miscellaneous changes
*
*Revision 1.19  2003/08/09 02:56:44  ddiego
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
*Revision 1.18.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.18  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.17.2.3  2003/05/15 03:01:03  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.17.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.17.2.1  2003/03/12 03:13:00  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.17  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.16.14.1  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.16  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.15.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.15  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


