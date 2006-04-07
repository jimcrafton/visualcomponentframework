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
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.4  2005/11/04 17:56:17  ddiego
*fixed bugs in some win32 code to better handle unicode - ansi functionality.
*
*Revision 1.4.2.3  2005/09/05 18:48:12  ddiego
*adjusted reg class methods for reading data so that they now throw
*exceptions for bad reads.
*
*Revision 1.4.2.2  2005/09/05 18:26:59  ddiego
*adjusted reg class methods for reading data so that they now throw
*exceptions for bad reads.
*
*Revision 1.4.2.1  2005/09/05 18:17:17  ddiego
*adjusted reg class methods for reading data so that they now throw
*exceptions for bad reads.
*
*Revision 1.4  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/04/13 02:50:45  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.3.2.1  2005/04/09 17:21:34  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/15 17:49:14  ddiego
*fixed win32 registry and a bug in the handling of the WM_CLOSE message that was introduced by the change in event handler signature last weekend.
*
*Revision 1.2.2.1  2004/09/15 03:08:40  ddiego
*fixed win32 registry bug that was incorrectly writing out string values.
*
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


