#ifndef _VCF_OSXREGISTRY_H__
#define _VCF_OSXREGISTRY_H__
//OSXRegistry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



namespace VCF {

class OSXRegistry : public Object, public RegistryPeer {
public:
	OSXRegistry();

	virtual ~OSXRegistry();

	virtual void setRoot( const RegistryKeyType& rootKey );

	virtual RegistryKeyType getRoot();

	virtual bool openKey( const String& keyname, const bool& createIfNonExistant );

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
protected:
	std::vector<RegistryValueInfo*> values_;
	std::vector<String> keys_;
	EnumeratorContainer<std::vector<RegistryValueInfo*>,RegistryValueInfo*> valuesContainer_;
	EnumeratorContainer<std::vector<String>,String> keysContainer_;
	RegistryKeyType rootKeyType_;
	String currentRegKey_;	
};

}; //end of namespace VCF



 /**
*CVS Log info
 *$Log$
 *Revision 1.3  2006/04/07 02:35:34  ddiego
 *initial checkin of merge from 0.6.9 dev branch.
 *
 *Revision 1.2.6.1  2005/11/14 22:05:42  ddiego
 *osx update.
 *
 *Revision 1.2  2004/08/07 02:49:14  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.5  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.3.2.1  2004/04/26 21:58:43  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.3  2004/04/03 15:48:42  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.2.6.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.2  2003/05/17 20:37:12  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:01  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


#endif // _VCF_OSXREGISTRY_H__


