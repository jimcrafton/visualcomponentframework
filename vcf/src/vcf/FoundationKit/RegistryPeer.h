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


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2.6.1  2005/09/05 18:17:17  ddiego
*adjusted reg class methods for reading data so that they now throw
*exceptions for bad reads.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.26.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_REGISTRYPEER_H__


