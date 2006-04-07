////Variants.cpp

#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;

void printVariant( VariantData& v )
{
	System::print( Format("As string: {%s},  type: %d\n") % v.toString() % v.type);
}

void testConstructors()
{
	VariantData v1("Hello");
	VCF_ASSERT( v1.type == pdString );
	printVariant(v1);

	VariantData v2(L"Hello");
	VCF_ASSERT( v2.type == pdString );
	printVariant(v2);

	VariantData v3(String("Hello"));
	VCF_ASSERT( v3.type == pdString );
	printVariant(v3);

	VariantData v4(10);
	VCF_ASSERT( v4.type == pdInt );
	printVariant(v4);

	VariantData v5((long)90005);
	VCF_ASSERT( v5.type == pdLong );
	printVariant(v5);

	VariantData v6(-9859405);
	VCF_ASSERT( v6.type == pdInt );
	printVariant(v6);

	VariantData v7 = (VCF::ushort)123;
	VCF_ASSERT( v7.type == pdUShort );
	printVariant(v7);

	VariantData v8 = (uint32)15997823;
	VCF_ASSERT( v8.type == pdUInt );
	printVariant(v8);


	VariantData v9 = 2332.003893112;
	VCF_ASSERT( v9.type == pdDouble );
	printVariant(v9);

	VariantData v10 = 1.0893112f;
	VCF_ASSERT( v10.type == pdFloat );
	printVariant(v10);

	
	VariantData v11 = true;
	VCF_ASSERT( v11.type == pdBool );
	printVariant(v11);
}


void testConversions() 
{
	VariantData v1;
	VariantData v2;

	v1 = "Stuff";
	printVariant(v1);

	v1 = 1002;
	printVariant(v1);

	v2 = v1;
	printVariant(v2);


	//note we don't support internal conversion from one
	//type to another - v1 is an int, but won't *yet*
	//convert automatically to a double.
	//Should it?
	double d = v1;

	//v2 now sees the gibberish double value
	v2 = d;
	printVariant(v2);

	d = 1001.223211;
	v2 = d;
	printVariant(v2);

	v1 = false;
	printVariant(v1);

	//note what currently happens. 
	//VariantData::setFromString expects the 
	//string value to be in the same existing
	//format as the variant is currently in.
	//v1 is a currently holding a bool value type
	//(pdBool), and the string that is returned
	//from v2's call to toString() is that of 
	//a double (pdDouble). So the boolean string
	//parsing of a double string is nonsensical
	v1.setFromString( v2.toString() );

	printVariant(v1);
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	
	try {
		testConstructors();
		System::println( "testConstructors completed OK." );

		testConversions();
		System::println( "testConversions completed OK." );
	}
	catch ( BasicException& e ) {
		System::println( String("Error: \n") + e.getMessage() );
	}
	catch ( std::exception& e ) {
		System::println( String("Error: \n") + e.what() );
	}

    System::println(System::createTempFileName(System::getCurrentWorkingDirectory()));
	FoundationKit::terminate();
	return 0;
}


