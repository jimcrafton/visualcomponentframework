#ifndef _VCF_MESSAGELOADER_H__
#define _VCF_MESSAGELOADER_H__
//MessageLoader.h

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
\class MessageLoader MessageLoader.h "vcf/FoundationKit/MessageLoader.h"
*/
class FOUNDATIONKIT_API MessageLoader {
public:

	virtual ~MessageLoader(){};

	/**
	Loads the contents of the message file specified by the
	file named fileName into the memory of this MessageLoader
	instance.
	*/
	virtual void loadMessageFile( const UnicodeString& fileName ) = 0;

	/**
	returns the translated string for the given string id.
	*/
	virtual UnicodeString getMessageFromID( const UnicodeString& id ) = 0;

	static void registerMessageLoader( const String& mimeType, MessageLoader* loader );
	static MessageLoader* getMessageLoader( const String& mimeType );
	static void internal_freeAllRegisteredMessageLoaders();
protected:
	static std::map<String,MessageLoader*> registeredMessageLoaders;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.3  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/25 00:11:59  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 04:00:29  ddiego
*added some missing files for locales
*
*/


#endif // _VCF_MESSAGELOADER_H__


