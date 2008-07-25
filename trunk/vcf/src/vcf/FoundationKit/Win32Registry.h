#ifndef _VCF_WIN32REGISTRY_H__
#define _VCF_WIN32REGISTRY_H__
//Win32Registry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Win32Registry : public Object, public RegistryPeer{

public:
	Win32Registry();

	virtual ~Win32Registry();

	virtual void setRoot( const RegistryKeyType& rootKey );

	virtual RegistryKeyType getRoot();

	virtual bool openKey( const String& keyname, const bool& createIfNonExistant );

	virtual bool removeKey( const String& keyname );

	virtual bool setValue( const String& value, const String& valuename );

	virtual bool setValue( const uint32& value, const String& valuename );

	virtual bool setValue( const bool& value, const String& valuename );

	virtual bool setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename );

	virtual bool getStringValue( const String& valuename, String& value );

	virtual bool getIntValue( const String& valuename, uint32& value );

	virtual bool getBoolValue( const String& valuename, bool& value );

	virtual bool getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer );

	virtual Enumerator<String>* getKeyNames();

	virtual Enumerator<RegistryValueInfo*>* getValues();

	virtual String getCurrentKey();
private:
	Array<RegistryValueInfo*> values_;
	Array<String> keys_;	
	RegistryKeyType rootKeyType_;
	String currentRegKey_;

	HKEY currentKeyHandle_;
	HKEY rootKeyHandle_;
};

}; //end of namespace VCF


#endif // _VCF_WIN32REGISTRY_H__

/**
$Id$
*/
