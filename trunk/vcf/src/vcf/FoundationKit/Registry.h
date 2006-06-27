#ifndef _VCF_REGISTRY_H__
#define _VCF_REGISTRY_H__
//Registry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

enum RegistryKeyType{
	RKT_ROOT=0,
	RKT_CURRENT_USER,
	RKT_LOCAL_MACHINE
};

enum RegistryDataType{
	RDT_STRING = 0,
	RDT_INTEGER,
	RDT_BOOL,
	RDT_BINARY
};

/**
\class RegistryValueInfo Registry.h "vcf/FoundationKit/Registry.h"
*/
class FOUNDATIONKIT_API RegistryException : public RuntimeException {
public:
	RegistryException( const VCF::String & message ):
		RuntimeException( message ){

	};
		
	RegistryException( const VCF::String & message, const int lineNumber ):
		VCF::RuntimeException(message, lineNumber){};

	virtual ~RegistryException() throw() {};

};

/**
\class RegistryValueInfo Registry.h "vcf/FoundationKit/Registry.h"
*a class that wraps up a specific registry value that may
*be a string, integer, bool, or stream of binary data
*/
class FOUNDATIONKIT_API RegistryValueInfo : public Object {
public:

	RegistryValueInfo( const VariantData* data, const RegistryDataType& dataType,
		               const String& valueName, char* dataBuffer=NULL, const uint32& dataBufferSize=0  ){

		dataType_ = dataType;

		valueName_ = valueName;

		dataBufferSize_ = dataBufferSize;

		dataBuffer_ = NULL;

		if ( NULL != data ){
			switch ( dataType_ ){
				case RDT_STRING :{
					data_ = (String)*data;
				}
				break;

				case RDT_INTEGER :{
					data_ = (uint32)*data;
				}
				break;

				case RDT_BOOL :{
					data_ = (bool)(*data);
				}
				break;

				case RDT_BINARY :{
					dataBuffer_ = dataBuffer;
				}
				break;
			}
		}
	}


	virtual ~RegistryValueInfo(){
		if ( NULL != dataBuffer_ ){
			delete dataBuffer_;
		}
	}

	RegistryDataType dataType_;

	VariantData data_;

	String valueName_;

	char* dataBuffer_;

	uint32 dataBufferSize_;
};



class RegistryPeer;

/**
\class Registry Registry.h "vcf/FoundationKit/Registry.h"
*The registry represents an external data source that applications
*may store application data in. This may be things like special file names,
*UI positions, application state data etc. The external data may be anything
*depending on the OS. In Win32, this represents a connection to the
*Win32 registry data base.
*/
class FOUNDATIONKIT_API Registry  : public Object{

public:
	Registry();

	virtual ~Registry();

	void setRoot( const RegistryKeyType& rootKey );

	RegistryKeyType getRoot();

	bool openKey( const String& keyname, const bool& createIfNonExistant=false );

	bool setValue( const String& value, const String& valuename );

	bool setValue( const uint32& value, const String& valuename );

	bool setValue( const bool& value, const String& valuename );

	bool setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename );

	/**
	Returns a named string value from the registry and the
	current open key. If no such value name exists, or there 
	is some other problem reading the value, the function throws 
	a RegistryException exception.
	@param String the name of the value under the current open key
	@return String the value returned
	*/
	String getStringValue( const String& valuename );

	/**
	Returns a named int value from the registry and the
	current open key. If no such value name exists, or there 
	is some other problem reading the value, the function throws 
	a RegistryException exception.
	@param String the name of the value under the current open key
	@return uint32 the value returned
	*/
	uint32 getIntValue( const String& valuename );

	/**
	Returns a named bool value from the registry and the
	current open key. If no such value name exists, or there 
	is some other problem reading the value, the function throws 
	a RegistryException exception.
	@param String the name of the value under the current open key
	@return bool the value returned
	*/
	bool getBoolValue( const String& valuename );

	/**
	Returns a named data buffer from the registry and the
	current open key. If no such value name exists, or there 
	is some other problem reading the value, the function throws 
	a RegistryException exception.
	
	Note that the function allocates a data buffer for the caller,
	however it is the caller's responsibility to delete the 
	data buffer when the caller is finished with it.
	Example usage
	\code
	Registry reg; 
	//reg already opened to some key...

	void* buf = NULL;
	uint32 dataBufferSize = 0;
	try {
		reg.getDataBufValue( "MyData", dataBufferSize, &buf );
	}
	catch ( RegistryException& ) {
		System::println( "Oops - an error occured!" );
	}

	//do stuff with buffer ...

	//clean up buffer - delete it!
	delete buf; 
	\endcode
	@param String the name of the value under the current open key
	@param uint32 the size of the newly allocated  data buffer in bytes
	@param void** a pointer to a data buffer pointer.
	*/
	void getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer );

	Enumerator<String>* getKeyNames();

	Enumerator<RegistryValueInfo*>* getValues();

	String getCurrentKey();
private:
	RegistryPeer* peer_;
};

}; //end of namespace VCF


#endif // _VCF_REGISTRY_H__

/**
$Id$
*/
