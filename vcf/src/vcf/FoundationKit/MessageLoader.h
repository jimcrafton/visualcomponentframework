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


#endif // _VCF_MESSAGELOADER_H__

/**
$Id$
*/
