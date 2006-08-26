#include "onig_cpp.h"

using namespace VCF;

void report(const Regex::Match& result) {
	System::println(Format("Match found for '%s' at position %d") % result.getText() % result.getPosAsOffset());
}

void report_wide(const Regex::Match& result) {
	System::println(Format("Match found for '%ls' at position %d") % result.getText() % result.getPosAsOffset());
}

int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

    String target=L"This is a test. Do not panic. I repeat: DO NOT PANIC!";
	int pos=8;
	System::println(Format("Character at position %d is '%lc'") % pos % target.at(pos));
    String exp="is";

    Regex::Ascii engine(exp, target);
	engine.compile();
    System::println(Format("Test string: %s") % target);
    Regex::Iterator it=engine.begin();
    while(it!=(engine.end())){
        report(*it++);
    }
    System::println("Now going the other way...");
    do {
        --it;
       report(*it);
    } while(it!=(engine.begin()));

    System::println("How about reverse iterators?...");
	Regex::ReverseIterator rit=engine.rbegin();
    while(rit!=(engine.rend())){
        report(*rit++);
    }
    System::println("and back again...");
    do {
        --rit;
        report(*rit);
    }
    while(rit!=(engine.rbegin()));

	System::println("Starting again, from the back, in Unicode");
	exp="t";
	Regex::UTF_16LE engine2(exp, target);
	engine2.compile();
	it=engine2.end();
	do {
        report_wide(*--it);
	} while (it!=engine2.begin());
	System::println("Starting again, from the beginning, still in Unicode");
	engine2.clearCache();
	it=engine2.begin();
	while (it!=engine2.end()) {
        report_wide(*it++);
	}
	System::println("all done");

	FoundationKit::terminate();

	return 0;
}
