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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2  2004/04/03 15:48:50  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/16 05:34:05  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:00:49  ddiego
*added some missing files for locales
*
*/


