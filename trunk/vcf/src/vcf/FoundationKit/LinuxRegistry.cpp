//LinuxRegistry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

LinuxRegistry::LinuxRegistry()
{


}

LinuxRegistry::~LinuxRegistry()
{

}

void LinuxRegistry::setRoot( const RegistryKeyType& rootKey )
{

}

RegistryKeyType LinuxRegistry::getRoot()
{
	return rootKeyType_;
}

bool LinuxRegistry::openKey( const String& keyname, const bool& createIfNonExistant )
{
	bool result = false;

	return result;

}

bool LinuxRegistry::setValue( const String& value, const String& valuename )
{
	return false;
}

bool LinuxRegistry::setValue( const uint32& value, const String& valuename )
{

	return false;
}

bool LinuxRegistry::setValue( const bool& value, const String& valuename )
{
	return false;
}

bool LinuxRegistry::setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename )
{

	return false;
}

String LinuxRegistry::getStringValue( const String& valuename )
{
	String result;
	return result;
}

uint32 LinuxRegistry::getIntValue( const String& valuename )
{
	return 0;
}

bool LinuxRegistry::getBoolValue( const String& valuename )
{
	bool result = false;

	return result;
}

void LinuxRegistry::getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer )
{

}

Enumerator<String>* LinuxRegistry::getKeyNames()
{

	keys_.clear();
	keysContainer_.initContainer( keys_ );

	return keysContainer_.getEnumerator();
}

Enumerator<RegistryValueInfo*>* LinuxRegistry::getValues()
{
	values_.clear();
	valuesContainer_.initContainer( values_ );

	return valuesContainer_.getEnumerator();
}

String LinuxRegistry::getCurrentKey()
{
	return currentRegKey_;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.12.2  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.1.12.1  2002/12/03 01:15:50  ddiego
*stuff
*
*Revision 1.1  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*
*/


