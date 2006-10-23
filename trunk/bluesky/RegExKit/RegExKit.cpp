//#include "oniguruma.h"
#include "RegExKit.h"

namespace VCF {

//RegExKit

	void RegExKit::init( int argc, char** argv )
	{

	}


	void RegExKit::terminate()
	{
		onig_end();
	}




// Regex:: Match

	ptrdiff_t Regex::Match::getPosAsOffset() const {
		return pos_-(env_->first_);
	}
	
// Regex::Iterator

    const Regex::Iterator& Regex::Iterator::operator++() {
		if (data_==&(data_->env_->pastTheEnd_)) {
			return *this;
		}
		if (data_->linkedNext_==true) {
			return *this=data_->env_->next(*this);
		}
		unsigned int offset=data_->env_->characterWidth(data_->getPosAsOffset());
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

    const Regex::Iterator& Regex::Iterator::operator--() {
		if (data_->env_->pastTheEnd_.linkedNext_) {
			return *this;
		}
		if (data_->linkedPrev_==true) {
			return *this=data_->env_->prev(*this);
		}
		Iterator temp;
		if (data_==&(data_->env_->pastTheEnd_)) {
			temp=data_->env_->rfind(data_->env_->last_);
		}
		else {
			temp=data_->env_->rfind(data_->pos_-1);
		}
        data_->linkedPrev_=true;
		temp->linkedNext_=true;
		return *this=temp;
    }

    Regex::Iterator Regex::Iterator::operator--(int){
        Iterator result(*this);
        --(*this);
        return result;
    }

// Regex::Host

	Regex::Host::Host(const String& exp, unsigned char* f, unsigned char* l, OnigSyntaxType* syntax):
        expression_(exp), first_(f), last_(l), syntax_(syntax), reg_(NULL), enumerator(Iterator(&pastTheEnd_)) {
		pastTheEnd_=Match(NULL, "", this);
	}

	Regex::Host::Host(const String &exp, OnigSyntaxType *syntax): expression_(exp),
		syntax_(syntax), reg_(NULL), enumerator(Iterator(&pastTheEnd_)) {
		pastTheEnd_=Match(NULL, "", this);
	}

	Regex::Host::~Host() {
		onig_free(reg_);
	}

	void Regex::Host::compile() {
		if (this->init()!=ONIG_NORMAL) {
			// Need some sort of error handling code here
			StringUtils::trace("Some sort of Onig-based error");
		}
	}

    Regex::Iterator Regex::Host::find(unsigned char* pos) {
		OnigRegion* region = onig_region_new();
		Match temp;
		InternalIterator it;
        if (pos<first_ || pos>last_){
            return Iterator(&pastTheEnd_);
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, pos, last_, region, ONIG_OPTION_NONE);
        if (status>=0) {
			temp=Match(first_+status, String((char*)(first_+status), (*region->end)-status), this);
			onig_region_free(region, 1);
			if (pos==first_) { // No possible results before this one
				temp.linkedPrev_=true;
			}
			if (status==last_-first_) {
				temp.linkedNext_=true;
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
			}
			else if (*it==temp){
				return Iterator(&*it);
			}
			else {
				if (it!=cache_.begin()) {
					if ((--it)->pos_>=pos) {
					temp.linkedPrev_=true;
					}
				}
				return Iterator(&*(cache_.insert(it, temp)));
			}
        }
		else {
			onig_region_free(region, 1);
			if (status!=ONIG_MISMATCH) {
				// some error handling here
			}
			else if (pos==first_) { // There are no matches
				pastTheEnd_.linkedNext_=true;
			}
            return Iterator(&pastTheEnd_);
        }
    }

    Regex::Iterator Regex::Host::rfind(unsigned char* pos){
		OnigRegion* region=onig_region_new();
		Match temp;
		InternalIterator it;
        if (pos<first_ || pos>last_){
            return Iterator(&pastTheEnd_);
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, pos, first_, region, ONIG_OPTION_NONE);
        if (status>=0) {
			temp=Match(first_+status, String((char*)(first_+status), (*region->end)-status), this);
			onig_region_free(region, 1);
			if (pos==last_) {
				temp.linkedNext_=true;
			}
			if (status==0) {
				temp.linkedPrev_=true;
			}
			it=cache_.lower_bound(temp);
/* Search result is further forward than all others found so far */
			if (it==cache_.end()) {
				return Iterator(&*(cache_.insert(it, temp)));
/* Search result has been found before */
			}
			else if (*it==temp){
				return Iterator(&*it);
			}
			else {
				if (it->pos_<=pos) {
					temp.linkedNext_=true;
				}
				return Iterator(&*(cache_.insert(it, temp)));
			}
        }
		else {
			if (status !=ONIG_MISMATCH) {
				// some error handling here
			}
			else if (pos==last_) { // There are no matches
				pastTheEnd_.linkedNext_=true;
			}
            return Iterator(&pastTheEnd_);
        }
    }

    Regex::MatchList Regex::Host::findAll() {
        Iterator it=begin();
        while (&*it != &pastTheEnd_) {
            ++it;
        }
        return cache_;
    }

	Regex::Iterator Regex::Host::begin() {
		InternalIterator it=cache_.begin();
		if (it!=cache_.end() && it->linkedPrev_) {
			return Iterator(&*it);
		}
		else {
			return find(0);
		}
	}

	unsigned char* Regex::Host::changeRangeBeginning(unsigned char* newBeginning) {
		unsigned char* old = first_;
		first_ = newBeginning;
		InternalIterator it = cache_.begin();
		if (old > first_) {
			pastTheEnd_.linkedNext_=false;
			if (it!=cache_.end()) {
				it->linkedPrev_=false;
			}
		}
		else {
			while (it!=cache_.end() && it->pos_<first_) {
				cache_.erase(it++);
			}
			if (it!=cache_.end()) {
				it->linkedPrev_=true;
			}
		}
		return old;
	}

	unsigned char* Regex::Host::changeRangeEnd(unsigned char* newEnd) {
		unsigned char* old = last_;
		last_ = newEnd;
		InternalIterator it = cache_.end();
		if (old < last_) {
			pastTheEnd_.linkedNext_=false;
			pastTheEnd_.linkedPrev_=false;
			if (!cache_.empty()) {
				(--it)->linkedNext_=false;
			}
		}
		else {
			if (!cache_.empty()) {
				--it;
				while (it!=cache_.begin()) {
					if (it->pos_>last_) {
						cache_.erase(it--);
					}
					else {
						break;
					}
				}
			}
		}
		return old;
	}

	String Regex::Host::changeSearchExpression(const VCF::String& newExpression) {
		String old = expression_;
		expression_ = newExpression;
		compile();
		clearCache();
		return old;
	}

	bool Regex::Host::hasMoreElements(const bool &backward) {
		return backward ? (!(enumerator==begin())) : (!(enumerator==end() || enumerator==--end()));
	}

	Regex::Match Regex::Host::nextElement() {
		return *++enumerator;
	}

	Regex::Match Regex::Host::prevElement() {
		return *--enumerator;
	}

	void Regex::Host::reset(const bool &backward) {
		backward ? enumerator=end() : enumerator=begin();
	}

	Regex::Iterator Regex::Host::next(Regex::Iterator current) const {
/* ConstIterator used here as passing a const Match to lower_bound returns a const_iterator *
* which then can't be cast to an normal iterator in those compilers which do not make       *
* set::iterator and set::const_iterator synonymous. - ACH                                   */
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
		}
		else {
			it=cache_.lower_bound(*current);
		}
		if (it != cache_.begin()) {
			return Iterator(&*(--it));
		}
		return Iterator(&pastTheEnd_);
	}

// Regex::Ascii

	Regex::Ascii::Ascii(const String &exp, unsigned char *first, unsigned char *last, OnigSyntaxType *syntax):
			Host(exp, first, last, syntax) {}

	Regex::Ascii::Ascii(const String &exp, const String &source, OnigSyntaxType *syntax): Host(exp, syntax) {
		first_=(unsigned char*)source.ansi_c_str();
		last_=(unsigned char*)(source.ansi_c_str()+source.length());
	}

	int Regex::Ascii::init() {
        return onig_new(&reg_, (unsigned char*)expression_.ansi_c_str(), (unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, syntax_, &error_);
	}

// Regex::UTF_16LE

	Regex::UTF_16LE::UTF_16LE(const String &exp, unsigned char *first, unsigned char *last, OnigSyntaxType *syntax):
		Host(exp, first, last, syntax) {}

	Regex::UTF_16LE::UTF_16LE(const String &exp, const String &source, OnigSyntaxType *syntax): Host(exp, syntax) {
        first_=(unsigned char*)(source.data());        
		last_=first_+(source.size_in_bytes());
	}

	int Regex::UTF_16LE::init() {
        return onig_new(&reg_, (unsigned char*)expression_.c_str(), (unsigned char*)expression_.c_str() + expression_.size_in_bytes(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF16_LE, syntax_, &error_);
	}

	unsigned int Regex::UTF_16LE::characterWidth(const ptrdiff_t &pos) const {
		return isSurrogate(*reinterpret_cast<VCFChar*>(first_+pos)) ? 4 : 2;
	}

	bool Regex::UTF_16LE::isSurrogate(VCFChar octet) const {
		return (0xD800 <= octet && octet <= 0xDBFF);
	}
}
