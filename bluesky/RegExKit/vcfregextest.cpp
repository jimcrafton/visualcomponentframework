#include "onig_cpp.h"

using namespace VCF;

int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

    String target="This is a test. Do not panic. I repeat: DO NOT PANIC!";
    String exp="tes";

    Regex::Host engine(exp, target);//(unsigned char*)(target.ansi_c_str()), (unsigned char*)(target.ansi_c_str())+target.length()-1);
    System::println(Format("Test string: %s") % target);
    System::println(Format("Match found for '%s' at position %d") % exp % engine.begin()->getPos());

	FoundationKit::terminate();

	return 0;
}
