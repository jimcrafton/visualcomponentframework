//Dictionaries.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"


using namespace VCF;



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	
	
	//create a dictionary

	Dictionary dict;

	//add 2 elements to the dictionary.

	dict.insert( "size", 200 );
	dict["width"] = 150;

	dict["Name"] = "Bob";


	Dictionary::Enumerator* items = dict.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair item = items->nextElement();

		System::println( "dict[\"%ls\"] = %ls", item.first.c_str(), item.second.toString().c_str() );
	}



	System::println( "Saving dictionary..." );

	{
		//store the dictionary
		FileOutputStream fs("test.dict.txt");

		//note: The use of the TextOutputStream is not neccessary, it's
		//just for demonstration purposes.
		TextOutputStream tos(&fs);

		//dump the dictionary to the stream
		tos << &dict;

	}

	System::println( "Loading dictionary..." );

	{
		//read in the dictionary from a file
		FileInputStream fs("test.dict.txt");

		//note: The use of the TextInputStream is not neccessary, it's
		//just for demonstration purposes.
		TextInputStream tis(&fs);

		//clear the dictionary - this will remove all elements in the dictionary
		dict.clear();

		//read in the dictionary from the stream
		tis >> static_cast<VCF::Persistable*>(&dict);
	}


	items = dict.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair item = items->nextElement();

		System::println( "dict[\"%ls\"] = %ls", item.first.c_str(), item.second.toString().c_str() );
	}



	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.7  2004/12/01 04:15:01  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.6.2.1  2004/10/07 15:03:24  kiklop74
*Fixed building issues with bcb
*
*Revision 1.6  2004/08/07 02:46:58  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.5.2.5  2004/08/02 04:11:52  ddiego
*added more examples to xcode project
*
*Revision 1.5.2.4  2004/04/29 03:40:52  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


