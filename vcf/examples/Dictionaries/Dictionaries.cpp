////Dictionaries.cpp

#include "FoundationKit.h"
#include "utils/Dictionary.h"


using namespace VCF;


typedef std::map<String,VariantData> map_t;


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	map_t m;
	m["sdfsd"] = 23455;


	//create a dictionary

	Dictionary dict;

	//add 2 elements to the dictionary.
	dict.insert( "size", 200 );
	dict["Name"] = "Bob";

	/*
	//print out the items of the dictionary
	Dictionary::iterator it = dict.begin();	
	
	while ( it != dict.end() ) {
		Dictionary::pair& item = *it;

		System::println( "dict[\"%s\"] = %s", item.first.c_str(), item.second.toString().c_str() );
		
		it ++;
	}
	*/
	


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
		tis >> &dict;
	}


	/*
	it = dict.begin();	
	
	while ( it != dict.end() ) {
		Dictionary::pair& item = *it;

		System::println( "dict[\"%s\"] = %s", item.first.c_str(), item.second.toString().c_str() );
		
		it ++;
	}
	*/


	FoundationKit::terminate();
	return 0;
}


