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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2  2004/04/03 15:48:49  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 04:00:48  ddiego
*added some missing files for locales
*
*/


