//Win32Registry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

Win32Registry::Win32Registry()
{
	rootKeyType_ = RKT_ROOT;
	currentKeyHandle_ = NULL;
	setRoot( rootKeyType_ );
}

Win32Registry::~Win32Registry()
{
	if ( NULL != currentKeyHandle_ ) {
		RegCloseKey( currentKeyHandle_ );
	}
}

void Win32Registry::setRoot( const RegistryKeyType& rootKey )
{
	rootKeyType_ = rootKey;
	switch ( rootKey ){
		case RKT_ROOT: {
			rootKeyHandle_ = HKEY_CLASSES_ROOT;
		}
		break;

		case RKT_CURRENT_USER: {
			rootKeyHandle_ = HKEY_CURRENT_USER;
		}
		break;

		case RKT_LOCAL_MACHINE: {
			rootKeyHandle_ = HKEY_LOCAL_MACHINE;
		}
		break;
	}

	if ( ERROR_SUCCESS != RegOpenKeyEx( rootKeyHandle_, NULL, 0, KEY_ALL_ACCESS, &currentKeyHandle_ ) ){
		//throw exception - operation failed !
	}
}

RegistryKeyType Win32Registry::getRoot()
{
	return rootKeyType_;
}

bool Win32Registry::openKey( const String& keyname, const bool& createIfNonExistant )
{
	bool result = false;

	String tmpKeyname = keyname;

	std::replace_if( tmpKeyname.begin(), tmpKeyname.end(),
					std::bind2nd(std::equal_to<VCFChar>(),'/') , '\\' );

	HKEY tmp = currentKeyHandle_;
	if ( true == createIfNonExistant ){
		if ( true== keyname.empty() ){
			//throw exception !!!
		}
		DWORD disposition = 0;
		if ( System::isUnicodeEnabled() ) {
			result = ( ERROR_SUCCESS == RegCreateKeyExW( tmp, tmpKeyname.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &currentKeyHandle_, &disposition ) );
		}
		else {
			result = ( ERROR_SUCCESS == RegCreateKeyExA( tmp, tmpKeyname.ansi_c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &currentKeyHandle_, &disposition ) );
		}

	}
	else {
		if ( System::isUnicodeEnabled() ) {
			result = ( ERROR_SUCCESS == RegOpenKeyExW( tmp, tmpKeyname.c_str(), 0, KEY_ALL_ACCESS, &currentKeyHandle_ ) );
		}
		else {
			result = ( ERROR_SUCCESS == RegOpenKeyExA( tmp, tmpKeyname.ansi_c_str(), 0, KEY_ALL_ACCESS, &currentKeyHandle_ ) );
		}
	}

	return result;

}

bool Win32Registry::setValue( const String& value, const String& valuename )
{

	LONG resVal = 0;

	const unsigned char* val = NULL;
	if ( System::isUnicodeEnabled() ) {
		val = (const unsigned char*)value.c_str();
		resVal = RegSetValueExW( currentKeyHandle_, valuename.c_str(), 0, REG_SZ, (BYTE*)val, sizeof(VCF::WideChar)*(value.size()+1) );
	}
	else {
		AnsiString tmp = value;
		val = (const unsigned char*)tmp.c_str();
		resVal = RegSetValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, REG_SZ, (BYTE*)val, tmp.size()+1 );
	}

	return (resVal == ERROR_SUCCESS);
}

bool Win32Registry::setValue( const uint32& value, const String& valuename )
{
	LONG resVal = 0;
	if ( System::isUnicodeEnabled() ) {
		resVal = RegSetValueExW( currentKeyHandle_, valuename.c_str(), 0, REG_DWORD, (BYTE*)&value, sizeof(value) );
	}
	else {
		resVal = RegSetValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, REG_DWORD, (BYTE*)&value, sizeof(value) );
	}

	return (resVal == ERROR_SUCCESS);
}

bool Win32Registry::setValue( const bool& value, const String& valuename )
{
	DWORD boolval = (DWORD)value;
	LONG resVal = 0;
	if ( System::isUnicodeEnabled() ) {
		resVal = RegSetValueExW( currentKeyHandle_, valuename.c_str(), 0, REG_DWORD, (BYTE*)&boolval, sizeof(boolval) );
	}
	else {
		resVal = RegSetValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, REG_DWORD, (BYTE*)&boolval, sizeof(boolval) );
	}

	return (resVal == ERROR_SUCCESS);
}

bool Win32Registry::setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename )
{
	LONG resVal = 0;
	if ( System::isUnicodeEnabled() ) {
		resVal = RegSetValueExW( currentKeyHandle_, valuename.c_str(), 0, REG_BINARY, (BYTE*)dataBuffer, dataBufferSize );
	}
	else {
		resVal = RegSetValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, REG_BINARY, (BYTE*)dataBuffer, dataBufferSize );
	}
	return (resVal == ERROR_SUCCESS);
}

bool Win32Registry::getStringValue( const String& valuename, String& value )
{
	
	DWORD type = 0;
	BYTE* buf = NULL;
	DWORD size = 0;
	bool result = false;

	LONG resVal = 0;
	if ( System::isUnicodeEnabled() ) {
		resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, NULL, &size );
	}
	else {
		resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, NULL, &size );
	}

	if ( resVal == ERROR_SUCCESS ){
		if ( (type == REG_SZ) && (size > 0) ){
			buf = new BYTE[size];
			memset( buf, 0, size*sizeof(BYTE) );
			if ( System::isUnicodeEnabled() ) {
				resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, buf, &size );
				if ( resVal == ERROR_SUCCESS ){

					value = (VCFChar*)buf;
					result = true;
				}
			}
			else {

				resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, buf, &size );
				if ( resVal == ERROR_SUCCESS ){

					value = (char*)buf;
					result = true;
				}
			}

			delete [] buf;
		}
	}

	return result;
}

bool Win32Registry::getIntValue( const String& valuename, uint32& value )
{
	bool result = false;

	DWORD type = 0;
	DWORD size = sizeof(value);
	LONG resVal = 0;

	if ( System::isUnicodeEnabled() ) {
		resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, (BYTE*)&value, &size );
	}
	else {
		resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, (BYTE*)&value, &size );
	}
	if ( resVal == ERROR_SUCCESS ){
		result = true;
		if ( (type != REG_DWORD) && (size <= 0) ){
			result = false;
		}
	}

	return result;
}

bool Win32Registry::getBoolValue( const String& valuename, bool& value )
{
	bool result = false;
	DWORD tmp = 0;
	DWORD type = 0;
	DWORD size = sizeof(DWORD);
	LONG resVal = 0;
	if ( System::isUnicodeEnabled() ) {
		resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, (BYTE*)&tmp, &size );
	}
	else {
		resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, (BYTE*)&tmp, &size );
	}
	if ( resVal == ERROR_SUCCESS ){
		result = true;
		if ( (type != REG_DWORD) && (size <= 0) ){
			result = false;
		}

		if ( result ) {
			value = tmp ? true : false;
		}
	}

	return result;
}

bool Win32Registry::getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer )
{
	bool result = false;

	DWORD type = 0;
	BYTE* buf = NULL;
	DWORD size = 0;

	*dataBuffer = NULL;

	LONG resVal = 0;

	if ( System::isUnicodeEnabled() ) {
		resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, NULL, &size );
	}
	else {
		resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, NULL, &size );
	}

	if ( resVal == ERROR_SUCCESS ){
		if ( (type == REG_BINARY) && (size > 0) ){
			buf = new BYTE[size]; //callers responsibility to clean up
			memset( buf, 0, size*sizeof(BYTE) );
			if ( System::isUnicodeEnabled() ) {
				resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, buf, &size );
			}
			else {
				resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, buf, &size );
			}

			if ( resVal == ERROR_SUCCESS ){
				*dataBuffer = (void*)buf;
				dataBufferSize = (uint32)size;
				result = true;
			}
			else {
				dataBufferSize = 0;
				*dataBuffer = NULL;
				delete [] buf;
			}
		}
	}

	return result;
}

Enumerator<String>* Win32Registry::getKeyNames()
{
	DWORD index = 0;
	const DWORD size = MAX_PATH + 1;


	if ( System::isUnicodeEnabled() ) {
		WideChar keyName[size];
		memset( keyName, 0, size*sizeof(WideChar) );

		keys_.clear();
		while ( ERROR_SUCCESS == RegEnumKeyW( currentKeyHandle_, index, keyName, size ) ){
			keys_.push_back( String(keyName) );
			memset( keyName, 0, size*sizeof(WideChar) );
			index ++;
		}
	}
	else {
		char keyName[size];
		memset( keyName, 0, size*sizeof(char) );

		keys_.clear();
		while ( ERROR_SUCCESS == RegEnumKeyA( currentKeyHandle_, index, keyName, size ) ){
			keys_.push_back( String(keyName) );
			memset( keyName, 0, size*sizeof(char) );
			index ++;
		}
	}

	
	keysContainer_.initContainer( keys_ );

	return keysContainer_.getEnumerator();
}

Enumerator<RegistryValueInfo*>* Win32Registry::getValues()
{
	std::vector<RegistryValueInfo*>::iterator it = values_.begin();
	while ( it != values_.end() ){
		RegistryValueInfo* regVal = *it;
		delete regVal;
		regVal = NULL;
		it++;
	}
	values_.clear();


	DWORD index = 0;

	DWORD type = 0;
	DWORD valNameSize = 256;		
	DWORD bufferSize = 256;		

	if ( System::isUnicodeEnabled() ) {
		WideChar valName[256];	
		BYTE buffer[sizeof(valName) * sizeof(WideChar)];

		bufferSize = sizeof(buffer);
		
		memset( valName, 0, sizeof(valName) * sizeof(WideChar) );

		while ( ERROR_NO_MORE_ITEMS != RegEnumValueW( currentKeyHandle_, index, valName, &valNameSize, NULL, &type, (BYTE*)&buffer, &bufferSize ) ){
			String tmp = String(valName);
			RegistryValueInfo* regVal = NULL;
			VariantData data;

			switch ( type ){
				case REG_SZ:{
					String strVal( (WideChar*)buffer );
					data = strVal;
					regVal = new RegistryValueInfo( &data, RDT_STRING, tmp );
				}
				break;

				case REG_DWORD:{
					ulong32* intVal = (ulong32*)buffer;
					data = *intVal;
					regVal = new RegistryValueInfo( &data, RDT_INTEGER, tmp );
				}
				break;

				case REG_BINARY:{
					void* dataBuf = NULL;
					if ( NULL != buffer ){
						dataBuf = (void*)new char[bufferSize];
						memcpy( dataBuf, buffer, bufferSize );
					}
					regVal = new RegistryValueInfo( NULL, RDT_BINARY, tmp, (char*)dataBuf, bufferSize );
				}
				break;
			}

			values_.push_back( regVal );
			bufferSize = sizeof(buffer);

			valNameSize = 256;
			memset( valName, 0, sizeof(valName) * sizeof(WideChar) );
			index ++;
		}
	}
	else {
		char valName[256];	
		BYTE buffer[sizeof(valName) * sizeof(char)];

		bufferSize = sizeof(buffer);
		
		memset( valName, 0, sizeof(valName) * sizeof(char) );

		while ( ERROR_NO_MORE_ITEMS != RegEnumValueA( currentKeyHandle_, index, valName, &valNameSize, NULL, &type, (BYTE*)&buffer, &bufferSize ) ){
			String tmp = String(valName);
			RegistryValueInfo* regVal = NULL;
			VariantData data;

			switch ( type ){
				case REG_SZ:{
					String strVal( (char*)buffer );
					data = strVal;
					regVal = new RegistryValueInfo( &data, RDT_STRING, tmp );
				}
				break;

				case REG_DWORD:{
					ulong32* intVal = (ulong32*)buffer;
					data = *intVal;
					regVal = new RegistryValueInfo( &data, RDT_INTEGER, tmp );
				}
				break;

				case REG_BINARY:{
					void* dataBuf = NULL;
					if ( NULL != buffer ){
						dataBuf = (void*)new char[bufferSize];
						memcpy( dataBuf, buffer, bufferSize );
					}
					regVal = new RegistryValueInfo( NULL, RDT_BINARY, tmp, (char*)dataBuf, bufferSize );
				}
				break;
			}

			values_.push_back( regVal );
			bufferSize = sizeof(buffer);

			valNameSize = 256;
			memset( valName, 0, sizeof(valName) * sizeof(char) );
			index ++;
		}
	}

	valuesContainer_.initContainer( values_ );

	return valuesContainer_.getEnumerator();
}

String Win32Registry::getCurrentKey()
{
	return currentRegKey_;
}


/**
$Id$
*/
