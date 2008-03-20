//Dictionaries.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/StringTokenizer.h"
#include "vcf/FoundationKit/Base64Codec.h"
#include "vcf/FoundationKit/XMLDictOutputStream.h"
#include "vcf/FoundationKit/XMLDictInputStream.h"


#include "vcf/FoundationKit/PropertyListing.h"


using namespace VCF;







int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	const unsigned char tmp[] = "Hello World\0";
	AnsiString b64;
	Base64Codec::encode( tmp, sizeof(tmp), b64, false );

	//create a dictionary

	Dictionary dict;

	//add 2 elements to the dictionary.

	dict.insert( "size", 200 );

	dict["width"] = 150;

	dict["Name"] = "Bob";

	Dictionary moreStuff;
	moreStuff["tempature"] = "Inferno";
	moreStuff["Current"] = 1000;

	dict["moreStuff"] = &moreStuff;

	DateTime dt;
	dt.set( 1998, 12, 13 );
	TimeZone tz = TimeZone::local(dt);

	moreStuff["someTime"] = dt.toUTC();


	Dictionary::Enumerator* items = dict.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair item = items->nextElement();

		System::println( Format("dict[\"%s\"] = %s") % item.first % item.second.toString() );
	}



	System::println( "Saving dictionary..." );

	{
		//store the dictionary
		FileOutputStream fs("test.dict.xml");

		XMLDictOutputStream xos(&fs);

		//xos.writeDict( dict );
		//dump the dictionary to the stream
		xos << &dict;

	}

	System::println( "Loading dictionary..." );

	{
		//read in the dictionary from a file
		FileInputStream fs("test.dict.xml");

		XMLDictInputStream xis(&fs);

		//clear the dictionary - this will remove all elements in the dictionary
		dict.clear();

		//read in the dictionary from the stream
		xis >> &dict;
	}


	
	items = dict.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair item = items->nextElement();

		System::println( Format("dict[\"%s\"] = %s") % item.first % item.second.toString() );
	}


	{
		FileInputStream fs("test.dict.xml");
		PropertyListing pl;
		fs >> &pl;

		items = pl.getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair item = items->nextElement();
			
			System::println( Format("dict[\"%s\"] = %s") % item.first % item.second.toString() );
		}


		System::println( pl.toString() );
	}


	FoundationKit::terminate();
	return 0;
}


/**
$Id$
*/
