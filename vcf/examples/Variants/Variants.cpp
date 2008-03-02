////Variants.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"
using namespace VCF;



class AnyVal {
public:

	union{
			int IntVal;
			long LongVal;
			short ShortVal;
			ushort UShortVal;
			unsigned int UIntVal;
			unsigned long ULongVal;
			float FloatVal;
			char CharVal;
			double DblVal;
			bool BoolVal;
			Object* ObjVal;
			EnumValue EnumVal;
			Interface* InterfaceVal;			
			int64 Int64Val;
			uint64 UInt64Val;
			void* VoidPtrVal;
	};

	AnyVal():VoidPtrVal(NULL){}

	AnyVal( Object* v ): ObjVal(v){}

	AnyVal( int v ): IntVal(v){}
	AnyVal( double v ): DblVal(v){}
	AnyVal( float v ): FloatVal(v){}
	AnyVal( Interface* v ): InterfaceVal(v){}
	AnyVal( void* v ): VoidPtrVal(v){}

	AnyVal& operator=( Object* v ) {
		ObjVal = v;
		return *this;
	}

	AnyVal& operator=( int v ) {
		IntVal = v;
		return *this;
	}
	AnyVal& operator=( double v ) {
		DblVal = v;
		return *this;
	}

	AnyVal& operator=( float v ) {
		FloatVal = v;
		return *this;
	}

	AnyVal& operator=( Interface* v ) {
		InterfaceVal = v;
		return *this;
	}

	AnyVal& operator=( void* v ) {
		VoidPtrVal = v;
		return *this;
	}

	operator Object* () const {
		return ObjVal;
	}

	operator int () const {
		return IntVal;
	}

	operator double () const {
		return DblVal;
	}

	operator float () const {
		return FloatVal;
	}

	operator Interface* () const {
		return InterfaceVal;
	}

	operator void* () const {
		return VoidPtrVal;
	}


};


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

	VariantData v12 = (int64)8797852412;
	VCF_ASSERT( v12.type == pdInt64 );
	printVariant(v12);

	VariantData v13 = (uint64)8797852413;
	VCF_ASSERT( v13.type == pdUInt64 );
	printVariant(v13);

	VariantData v14 = DateTime::now();
	VCF_ASSERT( v14.type == pdDateTime );
	printVariant(v14);

	DateTime dt( 1998, 8, 1, 16, 30, 0 );
	VariantData v15 = DateTime::now() - dt;
	VCF_ASSERT( v15.type == pdDateTimeSpan );
	printVariant(v15);

	dt.setMilliseconds( 0 );
	VariantData v16 = dt;
	VCF_ASSERT( v16.type == pdDateTime );
	printVariant(v16);



	char tmp[256];
	void* tmpPtr = tmp;

	VariantData v17 = tmpPtr;
	VCF_ASSERT( v17.type == pdVoidPointer );
	
	String sp = v17.toString();
	v17.setFromString(sp);


	printVariant(v17);

	Dictionary d;

	
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


