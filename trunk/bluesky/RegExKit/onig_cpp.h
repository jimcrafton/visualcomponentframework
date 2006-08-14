//#include <vector>
#include "oniguruma.h"
#include "vcf/FoundationKit/FoundationKit.h"
#include <set>

namespace VCF{
namespace Regex{

    class Host;
	class Iterator;

    class Match {
		friend class Host;
		friend class Iterator;
        public:
            Match(ptrdiff_t pos=-1, String text="", Host* const env=NULL): pos_(pos), matchText_(text), env_(env),
				linkedNext_(false), linkedPrev_(false){}
            Match(const Match& rhs): pos_(rhs.pos_), matchText_(rhs.matchText_), env_(rhs.env_),
				linkedNext_(rhs.linkedNext_), linkedPrev_(rhs.linkedPrev_){}
            Match& operator=(const Match& rhs){
                pos_=rhs.pos_;
                matchText_=rhs.matchText_;
                env_=rhs.env_;
				linkedNext_=rhs.linkedNext_;
				linkedPrev_=rhs.linkedPrev_;
                return *this;
            }

            bool operator==(const Match& rhs) const {
                return (pos_==rhs.pos_ && matchText_==rhs.matchText_ && env_==rhs.env_);
            }

			bool operator<(const Match& rhs) const {
				if (env_==rhs.env_) {
					if (pos_<rhs.pos_) {
						return true;
					} else if (pos_==rhs.pos_) {
						if (matchText_<rhs.matchText_) {
							return true;
						}
					}
				}
				return false;
			}

            const ptrdiff_t& getPos() const {
                return pos_;
            }

//			const char* getPosAsPointer() const;

            const String& getText() const {
                return matchText_;
            }

/*            Host* const getEnv() const {
                return env_;
            }*/
        private:
            ptrdiff_t pos_;
            String matchText_;
            Host* env_;
			mutable bool linkedNext_;
			mutable bool linkedPrev_;
    };

    typedef std::set<Match> MatchList;

    class Iterator: public std::iterator<std::bidirectional_iterator_tag, const Match> {
        public:
            // trivial
            Iterator(const Match* data=NULL): data_(data){}

			Iterator(const Iterator& rhs): data_(rhs.data_){}

            Iterator& operator=(const Iterator& rhs){
                data_=rhs.data_;
                return (*this);
            }

            bool operator==(const Iterator& rhs) const {
                return data_==rhs.data_;
            }

            bool operator!=(const Iterator& rhs) const {
                return !(data_==rhs.data_);
            }

            const Match& operator*() {
                return *data_;
            }

            const Match* operator->() {
                return data_;
            }
            // input/forward
            Iterator& operator++();
            Iterator operator++(int);
            // bidirectional
            Iterator& operator--();
            Iterator operator--(int);
        private:
            const Match* data_;
    };

    typedef std::reverse_iterator<Iterator> ReverseIterator;

    class Host {
		friend class Iterator;
        public:
            Host(const String& expression, unsigned char* first, unsigned char* last, OnigSyntaxType* syntax=ONIG_SYNTAX_DEFAULT);
            Host(const String& expression, const String& source, OnigSyntaxType* syntax=ONIG_SYNTAX_DEFAULT);

            Iterator find(ptrdiff_t pos);
            Iterator find(Iterator& it) {
                return find(it->pos_+1);
            }
            Iterator rfind(ptrdiff_t pos);
            Iterator rfind(Iterator& it) {
                return rfind(it->pos_-1);
            }
            MatchList findAll();
            Iterator begin(){
                return find(0);
            }
            Iterator end(){
                return Iterator(&pastTheEnd_);
            }
            ReverseIterator rbegin(){
                return ReverseIterator(end());
            }
            ReverseIterator rend(){
                return ReverseIterator(begin());
            }
        private:
            int init();
			Iterator next(Iterator current) const;
			Iterator prev(Iterator current) const;

			std::set<Match> cache_;
			typedef std::set<Match>::iterator InternalIterator;
			typedef std::set<Match>::const_iterator InternalConstIterator;
			Match pastTheEnd_;

            const String expression_;
            unsigned char* first_;
            unsigned char* last_;
			regex_t* reg_;
			OnigSyntaxType* syntax_;
            OnigErrorInfo error_;
    };

}
}
