#include "onig_cpp.h"

using namespace VCF;

int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

    String target="This is a test. Do not panic. I repeat: DO NOT PANIC!";
    String exp="tes";

    Regex engine(exp, target.ansi_c_str(), target.ansi_c_str()+target.length()-1);
    System::println("Test string: %s" % target);
    System::println("Match found at position %d" % *(engine.find(0))->getPos());

	FoundationKit::terminate();

	return 0;
}
