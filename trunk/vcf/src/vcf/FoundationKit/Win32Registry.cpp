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

	if ( System::isUnicodeEnabled() ) {
		const unsigned char* val = (const unsigned char*)value.c_str();
		resVal = RegSetValueExW( currentKeyHandle_, valuename.c_str(), 0, REG_DWORD, (BYTE*)&value, sizeof(VCFChar)*value.size() );
	}
	else {
		AnsiString tmp = value;
		const unsigned char* val = (const unsigned char*)tmp.c_str();
		resVal = RegSetValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, REG_DWORD, (BYTE*)&val, tmp.size() );
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
		RegSetValueExW( currentKeyHandle_, valuename.c_str(), 0, REG_BINARY, (BYTE*)dataBuffer, dataBufferSize );
	}
	else {
		RegSetValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, REG_BINARY, (BYTE*)dataBuffer, dataBufferSize );
	}
	return (resVal == ERROR_SUCCESS);
}

String Win32Registry::getStringValue( const String& valuename )
{

	DWORD type = 0;
	BYTE* buf = NULL;
	DWORD size = 0;
	String result;
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
			memset( buf, 0, size );
			if ( System::isUnicodeEnabled() ) {
				resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, buf, &size );
				if ( resVal == ERROR_SUCCESS ){

					result = (VCFChar*)buf;
				}
				else {
					//throw exception
				}
			}
			else {

				resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, buf, &size );
				if ( resVal == ERROR_SUCCESS ){

					result = (char*)buf;
				}
				else {
					//throw exception
				}
			}

			delete [] buf;
		}
	}
	else {
		//throw exception
	}

	return result;
}

uint32 Win32Registry::getIntValue( const String& valuename )
{
	uint32 result = 0;

	DWORD type = 0;
	DWORD size = sizeof(result);
	LONG resVal = 0;

	if ( System::isUnicodeEnabled() ) {
		resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, (BYTE*)&result, &size );
	}
	else {
		resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, (BYTE*)&result, &size );
	}
	if ( resVal == ERROR_SUCCESS ){
		if ( (type != REG_DWORD) && (size <= 0) ){
			//throw exception
		}
	}
	else {

		//throw exception
	}

	return result;
}

bool Win32Registry::getBoolValue( const String& valuename )
{
	DWORD result = 0;
	DWORD type = 0;
	DWORD size = sizeof(DWORD);
	LONG resVal = 0;
	if ( System::isUnicodeEnabled() ) {
		resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, (BYTE*)&result, &size );
	}
	else {
		resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, (BYTE*)&result, &size );
	}
	if ( resVal == ERROR_SUCCESS ){
		if ( (type != REG_DWORD) && (size <= 0) ){
			//throw exception
		}
	}
	else {
		//throw exception
	}

	return result ? true : false;
}

void Win32Registry::getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer )
{
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
			memset( buf, 0, size );
			if ( System::isUnicodeEnabled() ) {
				resVal = RegQueryValueExW( currentKeyHandle_, valuename.c_str(), 0, &type, buf, &size );
			}
			else {
				resVal = RegQueryValueExA( currentKeyHandle_, valuename.ansi_c_str(), 0, &type, buf, &size );
			}

			if ( resVal == ERROR_SUCCESS ){
				*dataBuffer = (void*)buf;
				dataBufferSize = (uint32)size;
			}
			else {
				//throw exception
			}
		}
	}
	else {
		//throw exception
	}
}

Enumerator<String>* Win32Registry::getKeyNames()
{
	DWORD index = 0;
	DWORD size = MAX_PATH + 1;
	TCHAR* keyName = new TCHAR[size];
	memset( keyName, 0, size );
	keys_.clear();
	while ( ERROR_SUCCESS == RegEnumKey( currentKeyHandle_, index, keyName, size ) ){
		this->keys_.push_back( String(keyName) );
		memset( keyName, 0, size );
		index ++;
	}
	keysContainer_.initContainer( keys_ );
	delete [] keyName;

	return keysContainer_.getEnumerator();
}

Enumerator<RegistryValueInfo*>* Win32Registry::getValues()
{
	DWORD index = 0;
	CHAR valName[256];
	DWORD type = 0;
	DWORD valNameSize = 256;
	BYTE buffer[256];
	DWORD bufferSize = 256;

	std::vector<RegistryValueInfo*>::iterator it = values_.begin();
	while ( it != values_.end() ){
		RegistryValueInfo* regVal = *it;
		delete regVal;
		regVal = NULL;
		it++;
	}

	values_.clear();
	memset( valName, 0, 256 );

	while ( ERROR_NO_MORE_ITEMS != RegEnumValue( currentKeyHandle_, index, valName, &valNameSize, NULL, &type, (BYTE*)&buffer, &bufferSize ) ){
		String tmp = String(valName);
		RegistryValueInfo* regVal = NULL;
		VariantData data;

		switch ( type ){
			case REG_SZ:{
				String strVal( (VCFChar*)buffer );
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
		bufferSize=256;
		valNameSize = 256;
		memset( valName, 0, 256 );
		index ++;
	}
	valuesContainer_.initContainer( values_ );

	return valuesContainer_.getEnumerator();
}

String Win32Registry::getCurrentKey()
{
	return currentRegKey_;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.11  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.2.1  2003/08/12 15:48:47  ddiego
*fixed bug in read vals from reg
*
*Revision 1.10  2003/08/09 02:56:46  ddiego
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
*Revision 1.9.2.1  2003/08/07 21:44:08  ddiego
*minor change to the Win32 reg peer (allows "/" instead of "\")
*added a getViews() method to Model class
*
*Revision 1.9  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:12:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.6  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


