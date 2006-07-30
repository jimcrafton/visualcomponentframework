//#include <vector>
#include "vcf/FoundationKit/FoundationKit.h"

namespace VCF {



class Regex {

    public:

        class Match {
            public:
                Match(ptrdiff_t pos, String text): pos_(pos), matchText_(text) {};

                const ptrdiff_t& getPos(){
                    return pos_;
                }

                const String& getText(){
                    return matchText_;
                }
            private:
                ptrdiff_t pos_;
                String matchText_;
        };

        typedef std::vector<Match> MatchList;

        class Iterator: public std::iterator<std::bidirectional_iterator_tag, Match> {
            public:
                // trivial
                Iterator(Match* data, Regex* host): data_(data), host_(host) {}
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
                Regex* host_;
        };

        typedef std::reverse_iterator<Iterator> ReverseIterator;

    public:
        Regex(const String& expression, unsigned char* first, unsigned char* last):
            expression_(expression), first_(first), last_(last) {}
/*        Regex(const String& expression, const String& source):
            expression_(expression) {
            first_=source.begin();
            last_=source.end();
        }*/
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
            return Iterator(NULL, this);
        }
        ReverseIterator rbegin(){
            return ReverseIterator(rfind(Iterator(new Match(last_-first_, ""), this)));
        }
        ReverseIterator rend(){
            return ReverseIterator(Iterator(NULL, this));
        }
    private:
        String expression_;
        unsigned char* first_;
        unsigned char* last_;
};

}
