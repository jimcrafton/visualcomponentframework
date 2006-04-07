//OSXRegistry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/
#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/OSXRegistry.h"

using namespace VCF;

CFStringRef getAppID( RegistryKeyType root )
{
	CFStringRef result = NULL;
	switch ( root ) {
		case RKT_ROOT : {
			result = kCFPreferencesAnyApplication;
		}
		break;
		
		case RKT_CURRENT_USER : {
			result = kCFPreferencesCurrentApplication;
		}
		break;
		
		case RKT_LOCAL_MACHINE : {
			result = kCFPreferencesCurrentApplication;
		}
		break;
	}
	return result;
}

CFStringRef getUserKey( RegistryKeyType root )
{
	CFStringRef result = NULL;
	switch ( root ) {
		case RKT_ROOT : {
			result = kCFPreferencesAnyUser;
		}
		break;
		
		case RKT_CURRENT_USER : {
			result = kCFPreferencesCurrentUser;
		}
		break;
		
		case RKT_LOCAL_MACHINE : {
			result = kCFPreferencesAnyUser;
		}
		break;
	}
	return result;
}

CFStringRef getHostKey( RegistryKeyType root )
{
	CFStringRef result = NULL;
	switch ( root ) {
		case RKT_ROOT : {
			result = kCFPreferencesCurrentHost;
		}
		break;
		
		case RKT_CURRENT_USER : {
			result = kCFPreferencesCurrentHost;
		}
		break;
		
		case RKT_LOCAL_MACHINE : {
			result = kCFPreferencesCurrentHost;
		}
		break;
	}
	return result;
}




OSXRegistry::OSXRegistry()
{
	valuesContainer_.initContainer( values_ );
	keysContainer_.initContainer( keys_ );
}

OSXRegistry::~OSXRegistry()
{

}

void OSXRegistry::setRoot( const RegistryKeyType& rootKey )
{
	rootKeyType_ = rootKey;
}

RegistryKeyType OSXRegistry::getRoot()
{
	return rootKeyType_;
}

bool OSXRegistry::openKey( const String& keyname, const bool& createIfNonExistant )
{
	bool result = true;
	currentRegKey_ = keyname;
	return result;
}

bool OSXRegistry::setValue( const String& value, const String& valuename )
{
	bool result = false;
	
	CFTextString key;
	key = currentRegKey_ + "-" + valuename;
	
	CFTextString val;
	val = value;
	
	CFPreferencesSetValue(key, (CFStringRef)val, 
							getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
				
	return result;
}

bool OSXRegistry::setValue( const uint32& value, const String& valuename )
{
	bool result = false;
	
	CFTextString key;
	key = currentRegKey_ + "-" + valuename;	
		
	CFRefObject<CFNumberRef> val = CFNumberCreate( NULL, kCFNumberSInt64Type, &value );
	
	CFPreferencesSetValue(key, val, 
							getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	
	
	return result;
}

bool OSXRegistry::setValue( const bool& value, const String& valuename )
{
	bool result = false;
	
	CFTextString key;
	key = currentRegKey_ + "-" + valuename;	
		
	CFBooleanRef val = value ? kCFBooleanTrue : kCFBooleanFalse;
	
	CFPreferencesSetValue(key, val, 
							getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	
	
	return result;
}

bool OSXRegistry::OSXRegistry::setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename )
{
	bool result = false;
	
	CFTextString key;
	key = currentRegKey_ + "-" + valuename;	
	
			
	CFRefObject<CFDataRef> val = CFDataCreate( NULL, (const UInt8*)dataBuffer, dataBufferSize );
	
	
	CFPreferencesSetValue(key, val, 
							getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
							
	
	
	return result;
}

bool OSXRegistry::getStringValue( const String& valuename, String& value )
{
	bool result = false;
	
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
	
	if ( result ) {
		CFTextString key;
		key = currentRegKey_ + "-" + valuename;	
	
		CFPropertyListRef propList = CFPreferencesCopyValue( key, getAppID(rootKeyType_),
															getUserKey(rootKeyType_), 
															getHostKey(rootKeyType_) );
		
		if ( NULL != propList ) {
			CFRefObject<CFStringRef> str = (CFStringRef)propList;
			CFTextString tmp;
			tmp = str;
			value = tmp;			 
		}
		else {
			result = false;
		}
	}							
	return result;
}

bool OSXRegistry::getIntValue( const String& valuename, uint32& value )
{
	bool result = false;
	
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
	
	if ( result ) {
		CFTextString key;
		key = currentRegKey_ + "-" + valuename;	
	
		CFPropertyListRef propList = CFPreferencesCopyValue( key, getAppID(rootKeyType_),
															getUserKey(rootKeyType_), 
															getHostKey(rootKeyType_) );
		
		if ( NULL != propList ) {
			CFRefObject<CFNumberRef> num = (CFNumberRef)propList;
			CFNumberGetValue( num,kCFNumberSInt64Type, &value );
		}
		else {
			result = false;
		}
	}
	return result;
}

bool OSXRegistry::getBoolValue( const String& valuename, bool& value )
{
	bool result = false;
	
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
	
	if ( result ) {
		CFTextString key;
		key = currentRegKey_ + "-" + valuename;	
	
		CFPropertyListRef propList = CFPreferencesCopyValue( key, getAppID(rootKeyType_),
															getUserKey(rootKeyType_), 
															getHostKey(rootKeyType_) );
		
		if ( NULL != propList ) {
			CFBooleanRef val = (CFBooleanRef)propList;
			value = CFBooleanGetValue( val );
		}
		else {
			result = false;
		}
	}
	return result;
}

bool OSXRegistry::getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer )
{
	bool result = false;
	
	result = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
	
	if ( result ) {
		CFTextString key;
		key = currentRegKey_ + "-" + valuename;	
	
		CFPropertyListRef propList = CFPreferencesCopyValue( key, getAppID(rootKeyType_),
															getUserKey(rootKeyType_), 
															getHostKey(rootKeyType_) );
		
		if ( NULL != propList ) {
			CFRefObject<CFDataRef> data = (CFDataRef)propList;
			
			CFIndex length = CFDataGetLength( data );
			if ( length > 0 ) {
				unsigned char* buf = new unsigned char[length];
				CFDataGetBytes( data, CFRangeMake(0,length), buf );
				dataBufferSize = length;
				*dataBuffer = buf;
			}
			else {
				result = false;
			}
		}
		else {
			result = false;
		}
	}
	return result;
}

Enumerator<String>* OSXRegistry::getKeyNames()
{
	bool ok = CFPreferencesSynchronize( getAppID(rootKeyType_),
							getUserKey(rootKeyType_), 
							getHostKey(rootKeyType_) );
	
													
	keys_.clear();
	
	if ( ok ) {
		CFRefObject<CFArrayRef> arr = CFPreferencesCopyKeyList( getAppID(rootKeyType_),
												   getUserKey(rootKeyType_), 
												   getHostKey(rootKeyType_) );
		
		if ( arr != NULL ) {
			for (int i=0;i<CFArrayGetCount(arr);i++ ) {
				CFStringRef s = (CFStringRef)CFArrayGetValueAtIndex( arr, i );
			
				keys_.push_back( CFTextString(s) );
			
				CFRelease(s);
			}
		}
	}				
	return keysContainer_.getEnumerator();
}

Enumerator<RegistryValueInfo*>* OSXRegistry::getValues()
{
	std::vector<RegistryValueInfo*>::iterator it = values_.begin();
	while ( it != values_.end() ){
		RegistryValueInfo* regVal = *it;
		delete regVal;
		regVal = NULL;
		it++;
	}
	values_.clear();
	
	bool ok = CFPreferencesSynchronize( getAppID(rootKeyType_),
										getUserKey(rootKeyType_), 
										getHostKey(rootKeyType_) );
	
	if ( ok ) {
		CFRefObject<CFDictionaryRef> dict = CFPreferencesCopyMultiple( NULL, getAppID(rootKeyType_),
																getUserKey(rootKeyType_), 
																getHostKey(rootKeyType_) );
																
		if ( dict != NULL ) {
			CFIndex dictCount = CFDictionaryGetCount( dict );
			CFTypeRef* keys = new CFTypeRef[dictCount];
			CFTypeRef* values = new CFTypeRef[dictCount];
			
			RegistryValueInfo* regVal = NULL;
			VariantData data;
			
			CFDictionaryGetKeysAndValues( dict, keys, values );
			for ( int i = 0;i < dictCount;i++) {
				regVal = NULL;
				String tmp = CFTextString( (CFStringRef) keys[i] );
				
				CFTypeID id = CFGetTypeID( values[i] );
				if ( CFStringGetTypeID() == id ) {
					CFTextString s( (CFStringRef)values[i] );
					data = (String)s;
					regVal = new RegistryValueInfo( &data, RDT_STRING, tmp );
				}
				else if ( CFNumberGetTypeID() == id ) {
					CFNumberRef num = (CFNumberRef)values[i];
					
					switch (CFNumberGetType(num) ) {
						case kCFNumberSInt8Type : 
						case kCFNumberSInt16Type :
						case kCFNumberSInt32Type : {
							int v = 0;
							CFNumberGetValue( num, CFNumberGetType(num), &v );
							data = v;
							regVal = new RegistryValueInfo( &data, RDT_INTEGER, tmp );
						}
						break;
						
						case kCFNumberIntType : 
						case kCFNumberCharType :
						case kCFNumberShortType : 
						case kCFNumberLongType : {
							int v = 0;
							CFNumberGetValue( num, CFNumberGetType(num), &v );
							data = v;
							regVal = new RegistryValueInfo( &data, RDT_INTEGER, tmp );
						}
						break;
						
						case kCFNumberDoubleType : {
							double v = 0;
							CFNumberGetValue( num, CFNumberGetType(num), &v );
							data = (int)v;
							regVal = new RegistryValueInfo( &data, RDT_INTEGER, tmp );
						}
						break;
						
						case kCFNumberFloatType : {
							float v = 0;
							CFNumberGetValue( num, CFNumberGetType(num), &v );
							data = (int)v;
							regVal = new RegistryValueInfo( &data, RDT_INTEGER, tmp );
						}
						break;
					}
				}
				else if ( CFDataGetTypeID() == id ) {
					CFDataRef data = (CFDataRef)values[i];
					CFIndex length = CFDataGetLength( data );
					if ( length > 0 ) {
						unsigned char* buf = new unsigned char[length];
						CFDataGetBytes( data, CFRangeMake(0,length), buf );
						regVal = new RegistryValueInfo( NULL, RDT_BINARY, tmp, (char*)buf, length );
					}
				}
				
				values_.push_back( regVal );
			}
			
			delete [] keys;
			delete [] values;
		}
	}
	
	valuesContainer_.initContainer( values_ );
	
	return valuesContainer_.getEnumerator();
}

String OSXRegistry::getCurrentKey()
{
	return currentRegKey_;
}

/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.3  2005/12/04 20:58:32  ddiego
*more osx impl work. foundationkit is mostly complete now.
*
*Revision 1.2.6.2  2005/11/21 04:00:51  ddiego
*more osx updates.
*
*Revision 1.2.6.1  2005/11/14 22:05:42  ddiego
*osx update.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


