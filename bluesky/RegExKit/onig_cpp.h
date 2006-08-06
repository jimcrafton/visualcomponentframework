//#include <vector>
#include "oniguruma.h"
#include "vcf/FoundationKit/FoundationKit.h"

namespace VCF{
namespace Regex{

    class Host;

    class Match: public VCF::Object {
        public:
            Match(ptrdiff_t pos, String text, Host* const env): pos_(pos), matchText_(text), env_(env){}
            Match(const Match& rhs): Object(rhs), pos_(rhs.pos_), matchText_(rhs.matchText_), env_(rhs.env_){}
            Match& operator=(const Match& rhs){
                pos_=rhs.pos_;
                matchText_=rhs.matchText_;
                env_=rhs.env_;
                return *this;
            }

//            virtual ~Match(){}

            bool operator==(const Match& rhs){
                return (pos_==rhs.pos_ && matchText_==rhs.matchText_ && env_==rhs.env_);
            }

            const ptrdiff_t& getPos() const {
                return pos_;
            }

            const String& getText() const {
                return matchText_;
            }

            Host* const getEnv() const {
                return env_;
            }
        private:
            ptrdiff_t pos_;
            String matchText_;
            Host* env_;
    };

    typedef std::vector<Match> MatchList;

    class Iterator: public std::iterator<std::bidirectional_iterator_tag, Match> {
        public:
            // trivial
            Iterator(Match* data=NULL): data_(data){}
            ~Iterator(){
                data_->release();
            }

            Iterator(const Iterator& rhs): data_(rhs.data_){
                data_->addRef();
            }

            Iterator& operator=(const Iterator& rhs){
                data_->release();
                data_=rhs.data_;
                data_->addRef();
                return (*this);
            }

            bool operator==(const Iterator& rhs) const {
                return *data_==*(rhs.data_);
            }

            bool operator!=(const Iterator& rhs) const {
                return !(*data_==*(rhs.data_));
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
            Host(const String& expression, unsigned char* first, unsigned char* last, OnigSyntaxType* syntax=ONIG_SYNTAX_DEFAULT);
            Host(const String& expression, const String& source, OnigSyntaxType* syntax=ONIG_SYNTAX_DEFAULT);
            Iterator find(ptrdiff_t pos);
            Iterator find(Iterator it) {
                return find(it->getPos()+1);
            }
            Iterator rfind(ptrdiff_t pos);
            Iterator rfind(Iterator it) {
                return rfind(it->getPos()-1);
            }
            MatchList findAll();
            Iterator begin(){
                return find(0);
            }
            Iterator end(){
                return Iterator(new Match(-1,"",this));
            }
            ReverseIterator rbegin(){
                return ReverseIterator(end());
            }
            ReverseIterator rend(){
                return ReverseIterator(begin());
            }
        private:
            int init();

            const String expression_;
            OnigSyntaxType* syntax_;
            unsigned char* first_;
            unsigned char* last_;
            regex_t* reg_;
            OnigErrorInfo error_;
    };

}
}
