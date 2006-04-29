//TextCodec.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/TextCodec.h"

using namespace VCF;


std::map<String,TextCodec*> TextCodec::registeredCodecsMap;



void TextCodec::registerCodec( TextCodec* codec )
{
	TextCodec::registeredCodecsMap[codec->getName()] = codec;
}

TextCodec* TextCodec::getCodec( const String& codecName )
{
	TextCodec* result = NULL;
	std::map<String,TextCodec*>::iterator found = TextCodec::registeredCodecsMap.find( codecName );
	if ( found != TextCodec::registeredCodecsMap.end() ) {
		result = found->second;
	}

	return result;
}

void TextCodec::internal_freeAllRegisteredCodecs()
{
	std::map<String,TextCodec*>::iterator it = TextCodec::registeredCodecsMap.begin();
	while ( it != TextCodec::registeredCodecsMap.end() ) {
		delete it->second;
		it++;
	}
}


/**
$Id$
*/
