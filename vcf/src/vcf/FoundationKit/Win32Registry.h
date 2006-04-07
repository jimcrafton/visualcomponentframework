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
	std::vector<RegistryValueInfo*> values_;
	std::vector<String> keys_;
	EnumeratorContainer<std::vector<RegistryValueInfo*>,RegistryValueInfo*> valuesContainer_;
	EnumeratorContainer<std::vector<String>,String> keysContainer_;
	RegistryKeyType rootKeyType_;
	String currentRegKey_;

	HKEY currentKeyHandle_;
	HKEY rootKeyHandle_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/09/05 18:17:17  ddiego
*adjusted reg class methods for reading data so that they now throw
*exceptions for bad reads.
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
*Revision 1.8.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.7  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.16.1  2003/03/12 03:11:27  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32REGISTRY_H__


