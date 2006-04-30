#ifndef _VCF_STRINGTOKENIZER_H__
#define _VCF_STRINGTOKENIZER_H__
//StringTokenizer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {



/**
\class StringTokenizer StringTokenizer.h "vcf/FoundationKit/StringTokenizer.h"
Class for breaking a string into a series of one or more tokens

Usage:
\code

StringTokenizer stk("Diddly piddly, dock, a big fat piece of apple nut cake!", " \n\r\f\t" );

while ( stk.hasMoreElements(true) ) {
	String s1 = stk.nextElement();
	String s2 = stk.prevElement();
	printf( "s1 = %s, s2 = %s\n", s1.c_str(), s2.c_str() );
}

\endcode

*/
class StringTokenizer : public Object, public Enumerator<String> {
public:
	StringTokenizer( const String& data ) :
		backward_(false), dataSize_(0), start_(NULL), ptr_(NULL), backPtr_(NULL), data_(data), delimiter_(" \n\r\t\f") {
		reset();
	}

	StringTokenizer( const String& data, const String& delimiter ) :
		backward_(false), dataSize_(0), start_(NULL), ptr_(NULL), backPtr_(NULL), data_(data), delimiter_(delimiter) {
		reset();
	}

	virtual bool hasMoreElements(const bool& backward=false) {
		if ( (NULL == start_) || (NULL == ptr_) ) {
			reset(backward);
		}
		backward_ = backward;
		return backward_ ? ((ptr_-start_) > 0) && ((backPtr_-start_) < dataSize_)
							: ((ptr_-start_) < dataSize_) && ((backPtr_-start_) > 0);
	}

	virtual String nextElement() {
		String result;

		if ( !backward_ ) {
			size_t pos = data_.find_first_of( delimiter_, ptr_-start_ );
			if ( pos != String::npos ) {
				result.append( ptr_,  (start_ + pos)-ptr_ );
				ptr_ = start_ + pos+1;
				pos = delimiter_.find( *ptr_ );
				while ( (pos != String::npos) && ((ptr_-start_) < dataSize_) ) {
					ptr_ ++;
					pos = delimiter_.find( *ptr_ );
				}
			}
			else {
				if ( (ptr_-start_) < dataSize_ ) {
					result.append( ptr_, dataSize_ - (ptr_-start_) );
				}
				ptr_ = start_ + dataSize_;
			}
		}
		else {
			size_t pos = data_.find_last_of( delimiter_, ptr_-start_ );
			if ( pos != String::npos ) {
				//pos ++;
				if ( (ptr_-start_) == dataSize_ ) {
					result.append( start_ + pos+1, ptr_ - (start_ + pos) );
				}
				else {
					result.append( start_ + pos+1, ptr_ - (start_ + pos)+1 );
				}
				//pos --;
				ptr_ = (start_ + pos) - 1;

				pos = delimiter_.find( *ptr_ );
				while ( (pos != String::npos) && ((ptr_-start_) > 0) ) {
					ptr_ --;
					pos = delimiter_.find( *ptr_ );
				}
			}
			else {
				if ( (ptr_-start_) > 0 ) {
					result.append( start_, ptr_-start_ +1 );
				}
				ptr_ = start_;
			}
		}

		return result;
	}

	virtual String prevElement() {
		String result;
		if ( backward_ ) {
			size_t pos = data_.find_first_of( delimiter_, backPtr_-start_ );
			if ( pos != String::npos ) {
				result.append( backPtr_,  (start_ + pos)-backPtr_ );
				backPtr_ = start_ + pos+1;
				pos = delimiter_.find( *backPtr_ );
				while ( (pos != String::npos) && ((backPtr_-start_) < dataSize_) ) {
					ptr_ ++;
					pos = delimiter_.find( *backPtr_ );
				}
			}
			else {
				if ( (backPtr_-start_) < dataSize_ ) {
					result.append( backPtr_, dataSize_ - (backPtr_-start_) );
				}
				backPtr_ = start_ + dataSize_;
			}
		}
		else {
			size_t pos = data_.find_last_of( delimiter_, backPtr_-start_ );
			if ( pos != String::npos ) {
				//pos ++;
				if ( (backPtr_-start_) == dataSize_ ) {
					result.append( start_ + pos+1, backPtr_ - (start_ + pos) );
				}
				else {
					result.append( start_ + pos+1, backPtr_ - (start_ + pos)+1 );
				}
				//pos --;
				backPtr_ = (start_ + pos) - 1;

				pos = delimiter_.find( *backPtr_ );
				while ( (pos != String::npos) && ((backPtr_-start_) > 0) ) {
					backPtr_ --;
					pos = delimiter_.find( *backPtr_ );
				}
			}
			else {
				if ( (backPtr_-start_) > 0 ) {
					result.append( start_, backPtr_-start_ +1 );
				}
				backPtr_ = start_;
			}
		}
		return result;
	}

	virtual void reset(const bool& backward=false) {
		backward_ = backward;
		dataSize_ = data_.size();
		start_ = data_.c_str();
		ptr_ = start_;
		backPtr_ = start_ + dataSize_ ;
		if ( backward_ ) {
			backPtr_ = start_ ;
			ptr_ = start_ + dataSize_ ;
		}
	}

	StringTokenizer& operator=( const String& data ) {
		data_ = data;
		ptr_ = NULL;
		start_ = NULL;
		backPtr_ = NULL;
		return *this;
	}

protected:

	//don't allow copy constructorys
	StringTokenizer( const StringTokenizer& ) {};

	StringTokenizer& operator=( const StringTokenizer& rhs ) {
		return *this;
	}

	bool backward_;
	size_t dataSize_;
	const VCFChar* start_;
	const VCFChar* ptr_;
	const VCFChar* backPtr_;

	String data_;
	String delimiter_;
};




};



#endif // _VCF_STRINGTOKENIZER_H__

/**
$Id$
*/