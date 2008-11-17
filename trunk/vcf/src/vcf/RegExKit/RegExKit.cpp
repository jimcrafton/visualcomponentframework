//#include "oniguruma.h"
#include "vcf/RegExKit/RegExKit.h"

OnigSyntaxType* onigTranslateSyntax(const VCF::RegExKit::Syntax& syntax) {
	OnigSyntaxType* returned;
	switch (syntax) {
		case VCF::RegExKit::sDefault:
			returned = onigTranslateSyntax(VCF::RegExKit::getDefaultSyntax());
			break;
		case VCF::RegExKit::sASIS:
			returned = ONIG_SYNTAX_ASIS;
			break;
		case VCF::RegExKit::sBasicPosix:
			returned = ONIG_SYNTAX_POSIX_BASIC;
			break;
		case VCF::RegExKit::sExtendedPosix:
			returned = ONIG_SYNTAX_POSIX_EXTENDED;
			break;
		case VCF::RegExKit::sEmacs:
			returned = ONIG_SYNTAX_EMACS;
			break;
		case VCF::RegExKit::sGrep:
			returned = ONIG_SYNTAX_GREP;
			break;
		case VCF::RegExKit::sGnu:
			returned = ONIG_SYNTAX_GNU_REGEX;
			break;
		case VCF::RegExKit::sJava:
			returned = ONIG_SYNTAX_JAVA;
			break;
		case VCF::RegExKit::sPerl:
			returned = ONIG_SYNTAX_PERL;
			break;
		case VCF::RegExKit::sPerlNG:
			returned = ONIG_SYNTAX_PERL_NG;
			break;
		case VCF::RegExKit::sRuby:
			returned = ONIG_SYNTAX_RUBY;
			break;
	}
	return returned;
}

namespace VCF {

//RegExKit

	RegExKit::Syntax RegExKit::default_ = RegExKit::sRuby; // this gets replaced when RegExKit is initialised

	void RegExKit::init( int argc, char** argv )
	{
//		setDefaultSyntax(sRuby); (ACH) Why is this not happening?
	}


	void RegExKit::terminate()
	{
		onig_end();
	}

	RegExKit::Syntax RegExKit::setDefaultSyntax(const RegExKit::Syntax& newDefault) {
		if (newDefault != sDefault) {
			Syntax old = default_;
			default_ = newDefault;

			return old;
		} else {
			return default_;
		}
	}

	RegExKit::Syntax RegExKit::getDefaultSyntax() {
		return default_;
	}

namespace Regex { //Borland compiler requires explicitly namespace declaration
// Regex:: Match

	ptrdiff_t Regex::Match::getPosAsOffset() const {
		return pos_-(env_->first_);
	}

	String::size_type Regex::Match::getPosAsCount() const {
		return env_->countCharacters(env_->first_, pos_);
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

	Regex::Host::Host(const String& exp, const unsigned char* const f, 
		const unsigned char* const l, const RegExKit::Syntax& syntax): 
		expression_(exp), first_(f), last_(l), syntax_(onigTranslateSyntax(syntax)), 
		reg_(NULL), enumerator_(Iterator(&pastTheEnd_)) {
			pastTheEnd_ = Match(NULL, "", this);
	}

	Regex::Host::Host(const String &exp, const RegExKit::Syntax& syntax): expression_(exp),
		syntax_(onigTranslateSyntax(syntax)), reg_(NULL), enumerator_(Iterator(&pastTheEnd_)) {
		pastTheEnd_ = Match(NULL, "", this);
	}

	Regex::Host::~Host() {
		onig_free(reg_);
	}

	void Regex::Host::compile() {
		if (reg_) {
			onig_free(reg_);
		}
		if (this->init()!=ONIG_NORMAL) {
			// Need some sort of error handling code here, but for now...
			StringUtils::trace("Some sort of Onig-based error in compile()");

			throw RuntimeException( "Error in Host::compile() with expression: \n" + expression_ );
		}
	}

    Regex::Iterator Regex::Host::find(const unsigned char* const pos) const {
		OnigRegion* region = onig_region_new();
		Match temp;
		InternalIterator it;
        if (pos<first_ || pos>last_){
            return Iterator(&pastTheEnd_);
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, pos, last_, region, ONIG_OPTION_NONE);
        if (status>=0) {
			temp = createMatch(region, status);
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
				// some error handling here, but for now...
				StringUtils::trace("Some sort of Onig-based error in find()");
				throw RuntimeException( "Error in Host::find() with expression: \n" + expression_ );
			}
			else if (pos==first_) { // There are no matches
				pastTheEnd_.linkedNext_=true;
			}
            return Iterator(&pastTheEnd_);
        }
    }

    Regex::Iterator Regex::Host::rfind(const unsigned char* const pos) const {
		OnigRegion* region=onig_region_new();
		Match temp;
		InternalIterator it;
        if (pos<first_ || pos>last_){
            return Iterator(&pastTheEnd_);
        }
        ptrdiff_t status = onig_search(reg_, first_, last_, pos, first_, region, ONIG_OPTION_NONE);
        if (status>=0) {
			temp = createMatch(region, status);
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
				// some error handling here, but for now...
				StringUtils::trace("Some sort of Onig-based error in rfind()");
				throw RuntimeException( "Error in Host::rfind() with expression: \n" + expression_ );
			}
			else if (pos==last_) { // There are no matches
				pastTheEnd_.linkedNext_=true;
			}
            return Iterator(&pastTheEnd_);
        }
    }

    Regex::MatchList Regex::Host::findAll() const {
        Iterator it=begin();
        while (&*it != &pastTheEnd_) {
            ++it;
        }
        return cache_;
    }

	Regex::Iterator Regex::Host::begin() const {
		InternalConstIterator it=cache_.begin();
		if (it!=cache_.end() && it->linkedPrev_) {
			return Iterator(&*it);
		}
		else {
			return find(0);
		}
	}

	const unsigned char* Regex::Host::changeRangeBeginning(const unsigned char* const newBeginning) {
		const unsigned char* old = first_;
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

	const unsigned char* Regex::Host::changeRangeEnd(const unsigned char* const newEnd) {
		const unsigned char* old = last_;
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

	bool Regex::Host::hasMoreElements(const bool &backward) const {
		return backward ? (!(enumerator_==begin())) : (!(enumerator_==end() || enumerator_==--end()));
	}

	Regex::Match Regex::Host::nextElement() {
		return *++enumerator_;
	}

	Regex::Match Regex::Host::prevElement() {
		return *--enumerator_;
	}

	void Regex::Host::reset(const bool &backward) const {
		backward ? enumerator_=end() : enumerator_=begin();
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

	Regex::Ascii::Ascii(const String &exp, const unsigned char* const first, 
		const unsigned char* const last, const RegExKit::Syntax& syntax): 
		Host(exp, first, last, syntax) {}

	Regex::Ascii::Ascii(const String &exp, const String &source, 
		const RegExKit::Syntax& syntax): Host(exp, syntax) {
			setRangeAsString(source);
	}

	void Regex::Ascii::setRangeAsString(const String& newExpression) {
		first_=(const unsigned char*)newExpression.ansi_c_str();
		last_=(const unsigned char*)(newExpression.ansi_c_str()+newExpression.length());
	}

	int Regex::Ascii::init() {
        return onig_new(&reg_, (const unsigned char*)expression_.ansi_c_str(), (const unsigned char*)expression_.ansi_c_str() + expression_.length(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, syntax_, &error_);
	}

	Regex::Match Regex::Ascii::createMatch(const OnigRegion* region, const ptrdiff_t pos) const {
			return Match(first_+pos, String((char*)(first_+pos), (*region->end)-pos), this);
	}

// Regex::UTF_16LE

	Regex::UTF_16LE::UTF_16LE(const String &exp, const unsigned char* const first, const unsigned char* const last, 
		const RegExKit::Syntax& syntax): Host(exp, first, last, syntax) {}

	Regex::UTF_16LE::UTF_16LE(const String &exp, const String &source, 
		const RegExKit::Syntax& syntax): Host(exp, syntax) {
			setRangeAsString(source);
	}

	void Regex::UTF_16LE::setRangeAsString(const String& newExpression) {
        first_=(const unsigned char*)(newExpression.data());        
		last_=first_+(newExpression.size_in_bytes());
	}

	int Regex::UTF_16LE::init() {
        return onig_new(&reg_, (const unsigned char*)expression_.c_str(), 
			(const unsigned char*)expression_.c_str() + expression_.size_in_bytes(),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF16_LE, syntax_, &error_);
	}

	unsigned int Regex::UTF_16LE::characterWidth(const unsigned char* const location) const {
		return isSurrogate(*reinterpret_cast<const VCFChar* const>(location)) ? 4 : 2;
	}

	Regex::Match Regex::UTF_16LE::createMatch(const OnigRegion* region, const ptrdiff_t pos) const {
		return Match(first_+pos, String((VCFChar*)(first_+pos), 
			countCharacters(first_+pos, first_+(*region->end))), this);
	}

	String::size_type Regex::UTF_16LE::countCharacters(const unsigned char* const start,
		const unsigned char* const end) const {
			String::size_type returned=0;
			unsigned int temp;
			const unsigned char* current = start;
			while (current < end) {
				temp = characterWidth(current);
				++returned;
				current += temp;
				VCF_ASSERT(current <= end);
			}
			return returned;
	}

	bool Regex::UTF_16LE::isSurrogate(const VCFChar octet) const {
		return (0xD800 <= octet && octet <= 0xDBFF);
	}
 } //namespace Regex
} //namespace VCF
