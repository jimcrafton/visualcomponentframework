//#include "oniguruma.h"
#include "onig_cpp.h"

namespace VCF {

// Regex::Iterator

    Regex::Iterator& Regex::Iterator::operator++() {
        return *this=data_->getEnv()->find(data_->getPos());
    }

    Regex::Iterator Regex::Iterator::operator++(int) {
        Iterator result=*this;
        ++(*this);
        return result;
    }

    Regex::Iterator& Regex::Iterator::operator--() {
        return *this=data_->getEnv()->rfind(data_->getPos());
    }

    Regex::Iterator Regex::Iterator::operator--(int) {
        Iterator result=*this;
        --(*this);
        return result;
    }

// Regex::Host

    Regex::Host::Host(const String& exp, unsigned char* f, unsigned char* l): expression_(exp), first_(f), last_(l) {
        if (init()!=ONIG_NORMAL) System::println("Some sort of error");
    }

    Regex::Host::Host(const String& expression, const String& source): expression_(expression) {
        first_=(unsigned char*)source.ansi_c_str();
        last_=(unsigned char*)(source.ansi_c_str()+source.length()-1);
        if (init()!=ONIG_NORMAL) System::println("Some sort of error");
    }

    int Regex::Host::init() {
        return onig_new(&reg_, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length() - 1,
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, ONIG_SYNTAX_PERL, &error_);
    }

    Regex::Iterator Regex::Host::find(ptrdiff_t pos) {
        OnigRegion* region;
        String matchtext;
        ptrdiff_t status;

        region = onig_region_new();
        status = onig_search(reg_, first_, last_, first_+pos, last_, region, ONIG_OPTION_NONE);
        if (status>=0) {
            matchtext=String((char*)region->beg,(region->end-region->beg)/sizeof(char));
            onig_region_free(region,1);
            return Iterator(new Match(status, matchtext, this));
        } else {
            onig_region_free(region,1);
            return Iterator(new Match(-1, "No match found", this));
        }
    }

    Regex::Iterator Regex::Host::rfind(ptrdiff_t pos){
        OnigRegion* region;
        String matchtext;
        ptrdiff_t status;

        region = onig_region_new();
        status = onig_search(reg_, first_, last_, first_+pos, first_, region, ONIG_OPTION_NONE);
        if (status>=0) {
            matchtext=String((WideChar*)region->beg, (region->end-region->beg)/sizeof(WideChar));
            onig_region_free(region,1);
            return Iterator(new Match(status, matchtext, this));
        } else {
            onig_region_free(region,1);
            return Iterator(new Match(-1, "No match found", this));
        }
    }

    Regex::MatchList Regex::Host::findAll() {
        MatchList result;
        Iterator it=begin();
        while (it->getPos() != -1) {
            result.push_back(*it);
            ++it;
        }
        return result;
    }
}
