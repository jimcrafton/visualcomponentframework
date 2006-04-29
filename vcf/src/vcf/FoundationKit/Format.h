#ifndef _VCF_FORMAT_H__
#define _VCF_FORMAT_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#if !defined(VCF_CW) && !defined(VCF_DMC)
// In-class member template specializations are non-standard (Section 14.7.3.2)
#  define VCF_NO_OUT_OF_CLASS_TEMPLATE_DEFINITIONS
#endif

//JC Note: apparently VC71 needs to be added to this list as well.
#if defined(VCF_GCC) || defined(VCF_DMC) || defined(VCF_VC60) || defined(VCF_VC70) || defined(VCF_VC71)  || defined (VCF_VC80) || defined(VCF_BCC)

// these compilers do not want 'template <DataType>' specified before the specialization
// JC - it appears GCC 3.3.3 doesn't like this - do we need to have this here at all!?
#  define VCF_NO_TEMPLATE_SPECIFICATION_FOR_MEMBER_TEMPLATE_SPECIALIZATION
#endif

#if defined(_MSC_VER) || defined(VCF_MINGW) || defined(VCF_BCC) || defined(VCF_DMC)
#  define snprintf _snprintf
#  define vsnprintf(b,c,f,a) _vsnprintf(b,c,f,a)
#endif


namespace VCF {

	/**
	\class Format Format.h "vcf/FoundationKit/Format.h"
	The Format class is used to format a string, similar to the
	sprintf/printf family of functions, only made typesafe for
	C++, and less likely to encounter buffer overflow errors
	that are so easy to do with sprintf and friends.
	
	The inspiration for this class comes unashamedly from the
	Boost Format library (http://www.boost.org/libs/format/doc/format.html).
	Any mistakes in the "translation" are mine, not Boost's.

	The basic idea is to pass in a string to the Format instance,
	and then use the "%" operator to separate your arguments.
	Currently the usage is \e exactly the same as you would use
	printf/sprintf, in terms of formatting. For example:
	\code
	//printf
	printf( "Hello World, %d times!", 10 );

	//Encoding the same using a Format object
	String s = Format("Hello World, %d times!") % 10;
	\endcode
	The "s" variable will now contain "Hello World, 10 times!".

	The Format object will throw assert exceptions (in debug mode) if too
	few arguments are passed in, or too many. For example:
	\code
	//BAD - too few arguments!!
	String s = Format("Hello World, %d times!");
	\endcode
	The above example is expecting 1 argument, and didn't receive any, and will
	thus assert.

	\code
	//BAD too many arguments!!
	String s = Format("Hello World, %d times!") % 100 % 0.56564;
	\endcode
	The above example expected 1 argument, but received 2, and will assert.

	@see StringUtils::format(const Format&)
	@see StringUtils::traceWithArgs(const Format&)
	@see System::print(const Format&)
	@see System::println(const Format&)
	*/
	class Format {
	public:

		Format( const String& fmtStr ): expectedFormatArgCount_(0), currentFormatArgCount_(0){

			fmtStr_ = StringUtils::convertFormatString(fmtStr);
			start_ = fmtStr_.c_str();
			end_ = start_ + fmtStr_.size();
			p_ = start_;
			prev_ = p_;

			expectedFormatArgCount_ = countFormatTokens();

			prev_ = p_;
			gobblePercents();

			if ( p_ == end_ ) {
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );
			}
		}

		//should we add virtual here for customizing the class???
		~Format() {

		}


		// operator used to concatenate arguments
		template<typename ValType>
		Format& operator% ( const ValType& val ) {

			currentFormatArgCount_  ++;

			VCF_ASSERT ( currentFormatArgCount_ <= expectedFormatArgCount_ );
			if ( currentFormatArgCount_ > expectedFormatArgCount_ ) {
				return *this;
			}

			if ( p_ < end_ ) {
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );

				const VCFChar* p = getNextFormatTokenEndPos( (p_-start_) );

				String fmt;
				fmt.assign( p_, p - p_ );
				p_ = p;


				size_t size = fmt.size()+256;
				char* tmp = new char[size+1];
				const char* tmpFmt = fmt.ansi_c_str();
				memset( tmp, 0, (size+1)*sizeof(char) );
				int cb = snprintf( tmp, size, tmpFmt, val );
				if ( (static_cast<int>(size) < cb) || (cb < 0) ) {
					String msg = String("Format: [") + cb + "] unable to printout the full formatted string: \"" + tmp + "\"\n";
					StringUtils::trace( msg );
				}
				output_ += tmp;
				delete [] tmp;
			}

			prev_ = p_;

			gobblePercents();

			if ( p_ == end_ ) {
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );
			}

			return *this;
		}

		//template<typename ValType>
		/**
		This hack is here to work around the broken (as far as I can tell)
		unicode support of OSX (yes, this *again*). It would appear that the
		onlu "widechar" support that printf has is for wchar_t types,
		not hte UTF16 16bit type that all the rest of the ^&%$$ OS uses
		(see CFStringRef - it's a 16bit unicode type, like all the other 
		sane Unicode API's use). So using %ls, or %S both fail to print
		anything at all here when a WideChar* (a 16bit unsigned short*)
		and we get errors from snprintf() about this. 
		To workaround this silliness (which of course isn't required on 
		Win32 - yeah Microsoft), I've added this specialization for WideChar* 
		and then converted down to ansi before passing it into sprintf.
		This is incredibly lame, and if someone ever figures out a better 
		solution, PLEASE let me know!!!!!!! 
		*/
		#ifdef VCF_OSX  
		Format& operator% (const WideChar* val) {			
			currentFormatArgCount_  ++;

			VCF_ASSERT ( currentFormatArgCount_ <= expectedFormatArgCount_ );
			if ( currentFormatArgCount_ > expectedFormatArgCount_ ) {
				return *this;
			}

			if ( p_ < end_ ) {
				String tmpVal(val);
			
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );

				const VCFChar* p = getNextFormatTokenEndPos( (p_-start_) );

				String fmt;
				fmt.assign( p_, p - p_ );
				p_ = p;


				size_t size = fmt.size()+256;
				char* tmp = new char[size+1];
				const char* tmpFmt = fmt.ansi_c_str();
				memset( tmp, 0, (size+1)*sizeof(char) );
				size_t cb = snprintf( tmp, size, tmpFmt, tmpVal.ansi_c_str() );
				if ( (size < cb) || (cb < 0) ) {
					String msg = String("Format: [") + cb + "] unable to printout the full formatted string: \"" + tmp + "\"\n";
					StringUtils::trace( msg );
				}
				output_ += tmp;
				delete [] tmp;
			}

			prev_ = p_;

			gobblePercents();

			if ( p_ == end_ ) {
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );
			}

			return *this;
		}
		#endif
		
	#ifdef VCF_NO_OUT_OF_CLASS_TEMPLATE_DEFINITIONS
		// specialization for a String value.
		#ifndef VCF_NO_TEMPLATE_SPECIFICATION_FOR_MEMBER_TEMPLATE_SPECIALIZATION
		template <String>
		#elif defined(VCF_GCC) || defined(VCF_OSX) || defined (VCF_MINGW) //added
		//nothing needed here, GCC on OSX 10.3.x doesn't like anything here
		//mingw too
		#else
		template <>
		#endif
		Format& operator% (const String& val) {

			currentFormatArgCount_  ++;

			VCF_ASSERT ( currentFormatArgCount_ <= expectedFormatArgCount_ );
			if ( currentFormatArgCount_ > expectedFormatArgCount_ ) {
				return *this;
			}

			if ( p_ < end_ ) {
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );

				const VCFChar* p = getNextFormatTokenEndPos( (p_-start_) );

				String fmt;
				fmt.assign( p_, p - p_ );
				p_ = p;


				size_t size = fmt.size()+val.size()+20;
				char* tmp = new char[size+1];
				memset( tmp, 0, (size+1)*sizeof(char) );
				//int cb = 
				snprintf( tmp, size, fmt.ansi_c_str(), val.ansi_c_str() );
				output_ += tmp;
				delete [] tmp;
			}

			prev_ = p_;

			gobblePercents();

			if ( p_ == end_ ) {
				output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );
			}

			return *this;
		}
	#endif //VCF_NO_OUT_OF_CLASS_TEMPLATE_DEFINITIONS


		operator String() const {
			//assert if the % operator wasn't called the correct number of times
			VCF_ASSERT ( currentFormatArgCount_ == expectedFormatArgCount_ );
			return output_;
		}


	protected:
		int countFormatTokens() const {
			int result = 0;
			String searchToken = "%";
			size_t pos = fmtStr_.find( searchToken );

			while ( pos != String::npos ) {
				if ( ((pos+1) <= fmtStr_.size()) && (fmtStr_[pos+1] == '%') ) {
					pos += 1;
				}
				else {
					result ++;
				}
				pos = fmtStr_.find( searchToken, pos+1);
			}

			return result;
		}

		const VCFChar* getNextFormatTokenEndPos( int startPos ) const {

			const VCFChar* p = end_;

			// not necessary anymore
			//if ( fmtStr_[startPos] != '%' ) {
			//	return result;
			//}


			//flags: "-+0 #"

			//width [1..9,0]*

			//precision ".[1..9,0]"

			//precision for int? "hlI64L"

			//type "cCdiouxXeEfgnpsS"


			String search = "-+0 #123456789*.hlI64LcCdiouxXeEfgnpsS";

			size_t pos = fmtStr_.find_first_not_of( search, startPos+1 );
			if ( String::npos != pos ) {
				p = start_ + pos;
			}

			return p;
		}

		void gobblePercents() {
			size_t pos = fmtStr_.find( "%", ( p_ - start_ ) );
			if ( String::npos == pos ) {
				p_ = end_;
			}
			else {
				p_ = start_ + pos;
			}
			while ( p_ < end_ ) {
				if ( ( '%' == *p_ ) && ( ( p_+1 < end_ ) && ( '%' == *(p_+1) ) ) ) {
						p_ ++;
						output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );
						p_ ++;

						prev_ = p_;
						pos = fmtStr_.find( "%", ( p_ - start_ ) );
						if ( String::npos == pos ) {
							p_ = end_;
						}
						else {
							p_ = start_ + pos;
						}
				}
				else {
					break;
				}
			}
		}

	private:
		String fmtStr_;
		String output_;
		size_t expectedFormatArgCount_;
		size_t currentFormatArgCount_;

		const VCFChar* start_;
		const VCFChar* p_;
		const VCFChar* prev_;
		const VCFChar* end_;
	};



#ifndef VCF_NO_OUT_OF_CLASS_TEMPLATE_DEFINITIONS

	// specialization for a String value.
	template <> inline
	Format& Format::operator% (const String& val) {

		currentFormatArgCount_  ++;

		VCF_ASSERT ( currentFormatArgCount_ <= expectedFormatArgCount_ );
		if ( currentFormatArgCount_ > expectedFormatArgCount_ ) {
			return *this;
		}

		if ( p_ < end_ ) {
			output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );

			const VCFChar* p = getNextFormatTokenEndPos( (p_-start_) );

			String fmt;
			fmt.assign( p_, p - p_ );
			p_ = p;


			size_t size = fmt.size()+val.size()+20;
			char* tmp = new char[size+1];
			memset( tmp, 0, (size+1)*sizeof(char) );
			int cb = snprintf( tmp, size, fmt.ansi_c_str(), val.ansi_c_str() );
			output_ += tmp;
			delete [] tmp;
		}

		prev_ = p_;

		gobblePercents();

		if ( p_ == end_ ) {
			output_ += fmtStr_.substr( prev_ - start_, p_ - prev_ );
		}

		return *this;
	}

#endif // VCF_NO_OUT_OF_CLASS_TEMPLATE_DEFINITIONS


}; // namespace VCF


#endif //_VCF_FORMAT_H__

/**
$Id$
*/
