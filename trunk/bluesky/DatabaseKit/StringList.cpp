#include "DatabaseKit.h"
#include "vcf/FoundationKit/StringTokenizer.h"


using namespace VCF;

StringList::StringList()
{
}

StringList::~StringList()
{
}

void StringList::add( String str )
{
    strings_.push_back( str );
}

void StringList::erase( int index )
{
    strings_.erase( strings_.begin() + index );
}

void StringList::clear()
{
    strings_.clear();
}

void StringList::setCommaText( String commaText )
{
    StringTokenizer strTok( commaText, ",\r\n" );

    while ( strTok.hasMoreElements() ) {
        strings_.push_back( strTok.nextElement() );
    }
}

String StringList::getCommaText()
{
    String result = "";

    typedef std::vector<String>::iterator strIt;

    for ( strIt it=strings_.begin();it!=strings_.end();++it ) {
        result+=*it + ", ";
    }

    if (!result.empty()) {
        result.erase(result.size()-2, 2);
    }

    return result;
}

void StringList::setText( String text )
{
    StringTokenizer strTok( text, "\r\n" );

    while ( strTok.hasMoreElements() ) {
        strings_.push_back( strTok.nextElement() );
    }
}

String StringList::getText()
{
    String result = "";

    typedef std::vector<String>::iterator strIt;

    for ( strIt it=strings_.begin();it!=strings_.end();++it ) {
        result+=*it + "\r\n";
    }

    if (!result.empty()) {
        result.erase(result.size()-2, 2);
    }

    return result;
}

String StringList::operator []( int index )
{
    return strings_[index];
}

int StringList::getCount()
{
    return strings_.size();
}
