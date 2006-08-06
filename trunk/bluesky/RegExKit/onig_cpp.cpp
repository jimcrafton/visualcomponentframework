//#include "oniguruma.h"
#include "onig_cpp.h"

namespace VCF {

// Regex::Iterator

    Regex::Iterator& Regex::Iterator::operator++() {
        return *this=data_->getEnv()->find(*this);
    }

    Regex::Iterator Regex::Iterator::operator++(int) {
        Iterator result(*this);
        ++(*this);
        return result;
    }

    Regex::Iterator& Regex::Iterator::operator--() {
        return *this=data_->getEnv()->rfind(*this);
    }

    Regex::Iterator Regex::Iterator::operator--(int) {
        Iterator result(*this);
        --(*this);
        return result;
    }

// Regex::Host

    Regex::Host::Host(const String& exp, unsigned char* f, unsigned char* l, OnigSyntaxType* syntax):
        expression_(exp), first_(f), last_(l), syntax_(syntax) {
        if (init()!=ONIG_NORMAL) System::println("Some sort of error");
    }

    Regex::Host::Host(const String& expression, const String& source, OnigSyntaxType* syntax):
        expression_(expression), syntax_(syntax) {
        first_=(unsigned char*)source.ansi_c_str();
        last_=(unsigned char*)(source.ansi_c_str()+source.length());
        if (init()!=ONIG_NORMAL) System::println("Some sort of error");
    }

    int Regex::Host::init() {
        return onig_new(&reg_, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, syntax_, &error_);
    }

/*    int Regex::Host::init() {
        return onig_new(&reg_, (unsigned char*)expression_.c_str(), (unsigned char*)expression_.c_str() + expression_.size_in_bytes() - 2,
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF16_LE, syntax_, &error_);
    }*/

    Regex::Iterator Regex::Host::find(ptrdiff_t pos) {
        if (pos<0){
            pos=0;
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, first_+pos, last_, NULL, ONIG_OPTION_NONE);
        if (status>=0) {
            return Iterator(new Match(status, String((char*)(first_+status), onig_match(reg_,
                first_, last_, first_+status, NULL, ONIG_OPTION_NONE)), this));
        } else {
            return Iterator(new Match(-1, "", this));
        }
    }

    Regex::Iterator Regex::Host::rfind(ptrdiff_t pos){
        if (pos<0){
            pos=last_-first_-1;
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, first_+pos, first_, NULL, ONIG_OPTION_NONE);
        if (status>=0) {
            return Iterator(new Match(status, String((char*)(first_+status), onig_match(reg_,
                first_, last_, first_+status, NULL, ONIG_OPTION_NONE)), this));
        } else {
            return Iterator(new Match(-1, "", this));
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
