#include "onig_cpp.h"

using namespace VCF;

int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

    String target="This is a test. Do not panic. I repeat: DO NOT PANIC!";
    String exp="is";

    Regex::Host engine(exp, target);
    System::println(Format("Test string: %s") % target);
    Regex::Iterator it=engine.begin();
    Regex::Iterator* info=&it;
    while(it!=(engine.end())){
        System::println(Format("Match found for '%s' at position %d") % it->getText() % it->getPos());
        ++it;
    }
    System::println("Now going the other way...");
    do {
        --it;
       System::println(Format("Match found for '%s' at position %d") % it->getText() % it->getPos());
    } while(it!=(engine.begin()));

    System::println("How about reverse iterators?...");
    Regex::ReverseIterator rit=engine.rbegin();
    while(rit!=(engine.rend())){
        System::println(Format("Match found for '%s' at position %d") % rit->getText() % rit->getPos());
        ++rit;
    }
    System::println("and back again...");
    do {
        --rit;
        System::println(Format("Match found for '%s' at position %d") % rit->getText() % rit->getPos());
    }
    while(rit!=(engine.rbegin()));

	FoundationKit::terminate();

	return 0;
}
