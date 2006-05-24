#ifndef _VCF_STRINGLIST_H__
#define _VCF_STRINGLIST_H__

#include <vector>

namespace VCF {

    class StringList {
    public:
        StringList();

        ~StringList();

        void add( String str );

        void erase( int index );

        void clear();

        void setCommaText( String commaText );

        String getCommaText();

        void setText( String text );

        String getText();

        String operator []( int index );

        int getCount();
    private:
        vector<String> strings_;
    };

};

#endif
