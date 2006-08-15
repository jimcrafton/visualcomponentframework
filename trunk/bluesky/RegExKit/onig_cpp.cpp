//#include "oniguruma.h"
#include "onig_cpp.h"

namespace VCF {

// Regex::Match

/*	const char* Regex::Match::getPosAsPointer() const {
		return (env_->getFirst())+pos_;
	}*/

// Regex::Iterator

    Regex::Iterator& Regex::Iterator::operator++() {
		if (data_==&(data_->env_->pastTheEnd_)) {
			return *this;
		}
		if (data_->linkedNext_==true) {
			return *this=data_->env_->next(*this);
		}
		unsigned int offset=data_->env_->fixedCharacterWidth_;
		if (!offset) {
//			need to do something here to determine where the next character starts
		}
		Iterator temp=data_->env_->find(data_->pos_+offset);
		data_->linkedNext_=true;
		temp->linkedPrev_=true;
        return *this=temp;
    }

    Regex::Iterator Regex::Iterator::operator++(int) {
        Iterator result(*this);
        ++(*this);
        return result;
    }

    Regex::Iterator& Regex::Iterator::operator--() {
		if (data_->linkedPrev_==true) {
			return *this=data_->env_->prev(*this);
		}
		Iterator temp=data_->env_->rfind(data_->pos_-1);
        data_->linkedPrev_=true;
		temp->linkedNext_=true;
		return *this=temp;
    }

    Regex::Iterator Regex::Iterator::operator--(int) {
        Iterator result(*this);
        --(*this);
        return result;
    }

// Regex::Host


	Regex::Host::Host(const String& exp, unsigned char* f, unsigned char* l, unsigned int width, OnigSyntaxType* syntax):
        expression_(exp), first_(f), last_(l), syntax_(syntax), fixedCharacterWidth_(width) {
        if (init()!=ONIG_NORMAL) System::println("Some sort of error");
    }

	Regex::Host::Host(const String &exp, unsigned int width, OnigSyntaxType *syntax): expression_(exp), 
		syntax_(syntax), fixedCharacterWidth_(width) {}

	int Regex::Host::init() {
		pastTheEnd_=Match(-1, "", this);
		return 0;
	}

/*    int Regex::Host::init() {
		pastTheEnd_=Match(-1, "", this);
        return onig_new(&reg_, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, syntax_, &error_);
    }*/

/*  int Regex::Host::init() {
		pastTheEnd_=Match(-1, "", this);
        return onig_new(&reg_, (unsigned char*)expression_.c_str(), (unsigned char*)expression_.c_str() + expression_.size_in_bytes(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF16_LE, syntax_, &error_);
    }*/

    Regex::Iterator Regex::Host::find(ptrdiff_t pos) {
		Match temp;
		InternalIterator it;
        if (pos<0){
            pos=0;
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, first_+pos, last_, NULL, ONIG_OPTION_NONE);
        if (status>=0) {
			temp=Match(status, String((char*)(first_+status), onig_match(reg_,
                first_, last_, first_+status, NULL, ONIG_OPTION_NONE)), this);
			if (pos==0) { // No possible results before this one
				temp.linkedPrev_=true;
			}
			it=cache_.lower_bound(temp);
/* Search result is further forward than all others found so far */
			if (it==cache_.end()) {
				if (!cache_.empty()){
					if ((--it)->pos_>=pos) {
						temp.linkedPrev_=true;
					}
				}
				return Iterator(&*(cache_.insert(it, temp)));
/* Search result has been found before */
			} else if (*it==temp){
				return Iterator(&*it);
			} else {
				if (it!=cache_.begin()) {
					if ((--it)->pos_>=pos) {
					temp.linkedPrev_=true;
					}
				}
				return Iterator(&*(cache_.insert(it, temp)));
			}
        } else {
            return Iterator(&pastTheEnd_);
        }
    }

    Regex::Iterator Regex::Host::rfind(ptrdiff_t pos){
		Match temp;
		InternalIterator it;
        if (pos<0){
            pos=last_-first_;
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, first_+pos, first_, NULL, ONIG_OPTION_NONE);
        if (status>=0) {
			temp=Match(status, String((char*)(first_+status), onig_match(reg_,
                first_, last_, first_+status, NULL, ONIG_OPTION_NONE)), this);
			if (pos==(last_-first_)) {
				temp.linkedNext_=true;
			}
			it=cache_.lower_bound(temp);
/* Search result is further forward than all others found so far */
			if (it==cache_.end()) {
				return Iterator(&*(cache_.insert(it, temp)));
/* Search result has been found before */
			} else if (*it==temp){
				return Iterator(&*it);
			} else {
				if (it->pos_<=pos) {
					temp.linkedNext_=true;
				}
				return Iterator(&*(cache_.insert(it, temp)));
			}
        } else {
            return Iterator(&pastTheEnd_);
        }
    }

	Regex::Iterator Regex::Host::next(Regex::Iterator current) const {
/* ConstIterator used here as passing a const Match to lower_bound returns a const_iterator *
* which then can't be cast to an normal iterator in those compilers which do not make       *
* set::iterator and set::const_iterator synonymous.                                        */
		InternalConstIterator it=++cache_.lower_bound(*current);
		if (it != cache_.end()) {
				return Iterator(&*it);
		}
		return Iterator(&pastTheEnd_);
	}

	Regex::Iterator Regex::Host::prev(Regex::Iterator current) const {
		InternalConstIterator it;
		if (&*current==&pastTheEnd_) {
			it=cache_.end();
		} else {
			it=cache_.lower_bound(*current);
		}
		if (it != cache_.begin()) {
			return Iterator(&*(--it));
		}
		return Iterator(&pastTheEnd_);
	}

    Regex::MatchList Regex::Host::findAll() {
        Iterator it=begin();
        while (&*it != &pastTheEnd_) {
            ++it;
        }
        return cache_;
    }

	Regex::Ascii::Ascii(const String &exp, unsigned char *first, unsigned char *last, OnigSyntaxType *syntax):
			Host(exp, first, last, 1, syntax) {
		if (this->init()!=ONIG_NORMAL) {
			StringUtils::trace("Regex compile error");
		}
	}

	Regex::Ascii::Ascii(const String &exp, const String &source, OnigSyntaxType *syntax): Host(exp, 1, syntax) {
		first_=(unsigned char*)source.ansi_c_str();
		last_=(unsigned char*)(source.ansi_c_str()+source.length());
		if (this->init()!=ONIG_NORMAL) {
			StringUtils::trace("Regex compile error");
		}
	}

	int Regex::Ascii::init() {
		Host::init();
        return onig_new(&reg_, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, syntax_, &error_);
	}

	Regex::UTF_16LE::UTF_16LE(const String &exp, unsigned char *first, unsigned char *last, OnigSyntaxType *syntax):
			Host(exp, first, last, 2, syntax) {
		if (this->init()!=ONIG_NORMAL) {
			StringUtils::trace("Regex compile error");
		}
	}

	Regex::UTF_16LE::UTF_16LE(const String &exp, const String &source, OnigSyntaxType *syntax): Host(exp, 2, syntax) {
        first_=(unsigned char*)source.c_str();
        last_=(unsigned char*)(source.c_str()+source.size_in_bytes());
		if (this->init()!=ONIG_NORMAL) {
			StringUtils::trace("Regex compile error");
		}		
	}

	int Regex::UTF_16LE::init() {
		Host::init();
        return onig_new(&reg_, (unsigned char*)expression_.c_str(), (unsigned char*)expression_.c_str() + expression_.size_in_bytes(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF16_LE, syntax_, &error_);
	}
}
