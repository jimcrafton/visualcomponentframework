//#include <vector>
#include "oniguruma.h"
#include "vcf/FoundationKit/FoundationKit.h"

namespace VCF{
namespace Regex{

    class Host;

    class Match {
        public:
            Match(ptrdiff_t pos, String text, Host* const env): pos_(pos), matchText_(text), env_(env){};
            Match(const Match& rhs): pos_(rhs.pos_), matchText_(rhs.matchText_), env_(rhs.env_){}
            Match operator=(const Match& rhs){
                return Match(rhs);
            }

            const ptrdiff_t& getPos(){
                return pos_;
            }

            const String& getText(){
                return matchText_;
            }

            Host* const getEnv(){
                return env_;
            }
        private:
            ptrdiff_t pos_;
            String matchText_;
            Host* const env_;
    };

    typedef std::vector<Match> MatchList;

    class Iterator: public std::iterator<std::bidirectional_iterator_tag, Match> {
        public:
            // trivial
            Iterator(Match* data): data_(data) {}
            ~Iterator(){
                delete data_;
            }

            Match& operator*(){
                return *data_;
            }

            Match* operator->(){
                return data_;
            }
            // input/forward
            Iterator& operator++();
            Iterator operator++(int);
            // bidirectional
            Iterator& operator--();
            Iterator operator--(int);
        private:
            Match* data_;
    };

    typedef std::reverse_iterator<Iterator> ReverseIterator;


    class Host {
        public:
            Host(const String& expression, unsigned char* first, unsigned char* last);
            Host(const String& expression, const String& source);
            Iterator find(ptrdiff_t pos);
            Iterator find(Iterator it) {
                return find(it->getPos());
            }
            Iterator rfind(ptrdiff_t pos);
            Iterator rfind(Iterator it) {
                return rfind(it->getPos());
            }
            MatchList findAll();
            Iterator begin(){
                return find(0);
            }
            Iterator end(){
                return Iterator(NULL);
            }
            ReverseIterator rbegin(){
                return ReverseIterator(rfind(Iterator(new Match(last_-first_, "", this))));
            }
            ReverseIterator rend(){
                return ReverseIterator(Iterator(NULL));
            }
        private:
            int init();

            const String expression_;
            unsigned char* first_;
            unsigned char* last_;
            regex_t* reg_;
            OnigErrorInfo error_;
    };

}
}
