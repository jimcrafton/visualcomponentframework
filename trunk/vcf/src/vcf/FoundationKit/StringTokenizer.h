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
Class for breaking a string into a series of one or more tokens

<p>
Usage:
<pre>

StringTokenizer stk("Diddly piddly, dock, a big fat tock!", " \n\r\f\t" );

while ( stk.hasMoreElements(true) ) {
	String s1 = stk.nextElement();
	String s2 = stk.prevElement();
	printf( "s1 = %s, s2 = %s\n", s1.c_str(), s2.c_str() );
}

</pre>

*/
class StringTokenizer : public Object, public Enumerator<String> {
public:
	StringTokenizer( const String& data ) :
		data_(data), delimiter_(" \n\r\t\f"), start_(NULL), ptr_(NULL), backPtr_(NULL) {
		reset();
	}

	StringTokenizer( const String& data, const String& delimiter ) :
		data_(data), delimiter_(delimiter), start_(NULL), ptr_(NULL), backPtr_(NULL) {
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
			int pos = data_.find_first_of( delimiter_, ptr_-start_ );
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
			int pos = data_.find_last_of( delimiter_, ptr_-start_ );
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
			int pos = data_.find_first_of( delimiter_, backPtr_-start_ );
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
			int pos = data_.find_last_of( delimiter_, backPtr_-start_ );
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
	unsigned long dataSize_;
	const VCFChar* start_;
	const VCFChar* ptr_;
	const VCFChar* backPtr_;

	String data_;
	String delimiter_;
};




};



/**
CVS Log info
$Log$
Revision 1.2  2004/08/07 02:49:15  ddiego
merged in the devmain-0-6-5 branch to stable

Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
reformatting of source files: macros and csvlog and copyright sections

Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
migration towards new directory structure

Revision 1.3.4.1  2004/04/26 21:58:48  marcelloptr
changes for dir reorganization: _VCF_MACRO_H__

Revision 1.3  2003/12/18 05:15:59  ddiego
merge from devmain-0-6-2 branch into the stable branch

Revision 1.2.4.2  2003/11/10 01:57:43  ddiego
add a fromString methods to StingUtils
added some minor fixes to list box control and added a SelectionChanged
Delegate to it
add some minor fixes ot ComboBoxControl
added an unknownColor() method to ColorNames class

Revision 1.2.4.1  2003/10/23 04:24:51  ddiego
more musical chairs with headers again, in yet another attempt to make
them more efficent to speed up compiles.
Removed all teh template RTTI classes and put them all in one header
called VCFRTTIImpl.h. This should help compile speeds a bit.
The next step is to look at some of the event classes and remove ones
that aren't really neccessary - I'd estimate that 50% of the current
event classes are unneccessary and can be removed.

Revision 1.2  2003/05/17 20:37:17  ddiego
this is the checkin for the 0.6.1 release - represents the merge over from
the devmain-0-6-0 branch plus a few minor bug fixes

Revision 1.1.2.1  2003/04/23 03:44:36  ddiego
added a string tokenizer class, long overdue :)

*/


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_STRINGTOKENIZER_H__


