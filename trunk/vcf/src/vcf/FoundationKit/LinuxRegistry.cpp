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
		: values_()
		, keys_()
		, valuesContainer_()
		, keysContainer_()
		, rootKeyType_()
		, currentRegKey_()
{}

LinuxRegistry::~LinuxRegistry()
{}

void LinuxRegistry::setRoot( const RegistryKeyType& rootKey )
{}

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

bool LinuxRegistry::setValue( void* dataBuffer,
                              const uint32& dataBufferSize,
                              const String& valuename )
{
	return false;
}

bool LinuxRegistry::getStringValue( const String& valuename, String& value )
{
    return false;
}

bool LinuxRegistry::getIntValue( const String& valuename, uint32& value )
{
	return false;
}

bool LinuxRegistry::getBoolValue( const String& valuename, bool& value )
{
    return false;
}

bool LinuxRegistry::getDataBufValue( const String& valuename,
                                     uint32& dataBufferSize,
                                     void** dataBuffer )
{
    bool result = false;
    return result;
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
$Id$
*/
