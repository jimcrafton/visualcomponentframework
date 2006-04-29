#ifndef _VCF_REGISTRYPEER_H__
#define _VCF_REGISTRYPEER_H__
//RegistryPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
\class RegistryPeer RegistryPeer.h "vcf/FoundationKit/RegistryPeer.h"
*/
class FOUNDATIONKIT_API RegistryPeer {
public:
	virtual ~RegistryPeer(){};

	virtual void setRoot( const RegistryKeyType& rootKey ) = 0;

	virtual RegistryKeyType getRoot() = 0;

	virtual bool openKey( const String& keyname, const bool& createIfNonExistant ) = 0;

	virtual bool setValue( const String& value, const String& valuename ) = 0;

	virtual bool setValue( const uint32& value, const String& valuename ) = 0;

	virtual bool setValue( const bool& value, const String& valuename ) = 0;

	virtual bool setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename ) = 0;

	virtual bool getStringValue( const String& valuename, String& value ) = 0;

	virtual bool getIntValue( const String& valuename, uint32& value ) = 0;

	virtual bool getBoolValue( const String& valuename, bool& value ) = 0;

	virtual bool getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer ) = 0;

	virtual Enumerator<String>* getKeyNames() = 0;

	virtual Enumerator<RegistryValueInfo*>* getValues() = 0;

	virtual String getCurrentKey() = 0;
};

}; //end of namespace VCF


#endif // _VCF_REGISTRYPEER_H__

/**
$Id$
*/
