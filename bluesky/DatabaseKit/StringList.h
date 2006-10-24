#ifndef _VCF_STRINGLIST_H__
#define _VCF_STRINGLIST_H__


/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

    class DATABASEKIT_API StringList {
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
		std::vector<String> strings_;
    };

};

#endif
