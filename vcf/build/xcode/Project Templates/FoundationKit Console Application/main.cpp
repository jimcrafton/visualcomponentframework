#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


int main (int argc, char * const argv[]) {
   
	FoundationKit::init( argc, argv );
	
	System::println( "Hello World!" );
	
	FoundationKit::terminate();
	
    return 0;
}
