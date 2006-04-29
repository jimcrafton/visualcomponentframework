#ifndef _VCF_LINUXREGISTRY_H__
#define _VCF_LINUXREGISTRY_H__ 
//LinuxRegistry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF
{

class LinuxRegistry : public Object, public RegistryPeer
{
public:
	LinuxRegistry();

	virtual ~LinuxRegistry();

	virtual void setRoot( const RegistryKeyType& rootKey );

	virtual RegistryKeyType getRoot();

	virtual bool openKey( const String& keyname, const bool& createIfNonExistant );

	virtual bool setValue( const String& value, const String& valuename );

	virtual bool setValue( const uint32& value, const String& valuename );

	virtual bool setValue( const bool& value, const String& valuename );

	virtual bool setValue( void* dataBuffer,
	                       const uint32& dataBufferSize,
	                       const String& valuename );

    virtual bool getStringValue( const String& valuename, String& value );

    virtual bool getIntValue( const String& valuename, uint32& value );

    virtual bool getBoolValue( const String& valuename, bool& value );

    virtual bool getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer );

	virtual Enumerator<String>* getKeyNames();

	virtual Enumerator<RegistryValueInfo*>* getValues();

	virtual String getCurrentKey();

private:
	std::vector<RegistryValueInfo*> values_;
	std::vector<String> keys_;
	EnumeratorContainer<std::vector<RegistryValueInfo*>,
	                    RegistryValueInfo* > valuesContainer_;
	EnumeratorContainer<std::vector<String>, String> keysContainer_;
	RegistryKeyType rootKeyType_;
	String currentRegKey_;
};

} //end of namespace VCF


#endif // _VCF_LINUXREGISTRY_H__

/**
$Id$
*/
