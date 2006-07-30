#include "oniguruma.h"
#include "onig_cpp.h"

namespace VCF {

// Regex::Iterator

    Regex::Iterator& Regex::Iterator::operator++() {
        return *this=host_->find(data_->getPos());
    }

    Regex::Iterator Regex::Iterator::operator++(int) {
        Iterator result=*this;
        ++(*this);
        return result;
    }

    Regex::Iterator& Regex::Iterator::operator--() {
        return *this=host_->rfind(data_->getPos());
    }

    Regex::Iterator Regex::Iterator::operator--(int) {
        Iterator result=*this;
        --(*this);
        return result;
    }

// Regex
    Regex::Iterator Regex::find(ptrdiff_t pos) {
        OnigErrorInfo error;
        OnigRegion* region;
        regex_t* reg;
        String matchtext;
        ptrdiff_t status;

        status = onig_new(&reg, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_PERL, &error);
        if (status != ONIG_NORMAL) {
            return Iterator(new Match(-1,"Regex compilation error"), this);
        }
        region = onig_region_new();
        status = onig_search(reg, first_, last_, first_+pos, last_, region, ONIG_OPTION_NONE);
        if (status>=0) {
            matchtext=String((WideChar*)region->beg,(region->end-region->beg)/sizeof(WideChar));
            onig_region_free(region,1);
            return Iterator(new Match(status,matchtext),this);
        } else {
            onig_region_free(region,1);
            return Iterator(new Match(-1,"No match found"), this);
        }
    }

    Regex::Iterator Regex::rfind(ptrdiff_t pos){
        OnigErrorInfo error;
        OnigRegion* region;
        regex_t* reg;
        String matchtext;
        ptrdiff_t status;

        status = onig_new(&reg, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_PERL, &error);
        if (status != ONIG_NORMAL) {
            return Iterator(new Match(-1,"Regex compilation error"), this);
        }
        region = onig_region_new();
        status = onig_search(reg, first_, last_, first_+pos, first_, region, ONIG_OPTION_NONE);
        if (status>=0) {
            matchtext=String((WideChar*)region->beg, (region->end-region->beg)/sizeof(WideChar));
            onig_region_free(region,1);
            return Iterator(new Match(status,matchtext),this);
        } else {
            onig_region_free(region,1);
            return Iterator(new Match(-1,"No match found"), this);
        }
    }

    Regex::MatchList Regex::findAll() {
        MatchList result;
        Iterator it=begin();
        while (it->getPos() != -1) {
            result.push_back(*it);
            ++it;
        }
        return result;
    }
}
