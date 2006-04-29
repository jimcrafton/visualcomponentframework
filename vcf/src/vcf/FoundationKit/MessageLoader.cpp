//MessageLoader.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/MessageLoader.h"


using namespace VCF;



std::map<String,MessageLoader*> MessageLoader::registeredMessageLoaders;


void MessageLoader::registerMessageLoader( const String& mimeType, MessageLoader* loader )
{
	MessageLoader::registeredMessageLoaders[mimeType] = loader;
}

MessageLoader* MessageLoader::getMessageLoader( const String& mimeType )
{
	std::map<String,MessageLoader*>::iterator found = MessageLoader::registeredMessageLoaders.find( mimeType );
	if ( found != MessageLoader::registeredMessageLoaders.end() ) {
		return found->second;
	}

	return NULL;
}

void MessageLoader::internal_freeAllRegisteredMessageLoaders()
{
	std::map<String,MessageLoader*>::iterator it = MessageLoader::registeredMessageLoaders.begin();
	if ( it != MessageLoader::registeredMessageLoaders.end() ) {
		delete it->second;
		it ++;
	}
}


/**
$Id$
*/
