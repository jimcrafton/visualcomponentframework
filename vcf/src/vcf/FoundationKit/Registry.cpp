//Registry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

Registry::Registry()
{
	peer_ = NULL;
	peer_ =  SystemToolkit::createRegistryPeer( this );

	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Registry::~Registry()
{
	delete peer_;
}

void Registry::setRoot( const RegistryKeyType& rootKey )
{
	peer_->setRoot( rootKey );
}

RegistryKeyType Registry::getRoot()
{
	return peer_->getRoot();
}

bool Registry::openKey( const String& keyname, const bool& createIfNonExistant )
{
	return peer_->openKey( keyname, createIfNonExistant );
}

bool Registry::removeKey( const String& keyname )
{
	return peer_->removeKey( keyname );
}

bool Registry::setValue( const String& value, const String& valuename )
{
	return peer_->setValue( value, valuename );
}

bool Registry::setValue( const uint32& value, const String& valuename )
{
	return peer_->setValue( value, valuename );
}

bool Registry::setValue( const bool& value, const String& valuename )
{
	return peer_->setValue( value, valuename );
}

bool Registry::setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename )
{
	return peer_->setValue( dataBuffer, dataBufferSize, valuename );
}

String Registry::getStringValue( const String& valuename )
{
	String result;
	if ( !peer_->getStringValue( valuename, result ) ) {
		throw RegistryException( "Unable to read value named \"" + valuename + "\" from registry." );
	}
	return result;
}

uint32 Registry::getIntValue( const String& valuename )
{
	uint32 result = 0;
	if ( !peer_->getIntValue( valuename, result ) ) {
		throw RegistryException( "Unable to read value named \"" + valuename + "\" from registry." );
	}
	return result;
}

bool Registry::getBoolValue( const String& valuename )
{
	bool result = false;
	if ( !peer_->getBoolValue( valuename, result ) ) {
		throw RegistryException( "Unable to read value named \"" + valuename + "\" from registry." );
	}
	return result;
}

void Registry::getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer )
{
	if ( !peer_->getDataBufValue( valuename, dataBufferSize, dataBuffer ) ) {
		throw RegistryException( "Unable to read value named \"" + valuename + "\" from registry." );
	}
}

Enumerator<String>* Registry::getKeyNames()
{
	return peer_->getKeyNames();
}

Enumerator<RegistryValueInfo*>* Registry::getValues()
{
	return peer_->getValues();
}

String Registry::getCurrentKey()
{
	return peer_->getCurrentKey();
}


/**
$Id$
*/
