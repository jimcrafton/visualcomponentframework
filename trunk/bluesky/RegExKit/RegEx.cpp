////RegEx.cpp

#include "vcf/FoundationKit/FoundationKit.h"

#define regex_t   onig_regex_t
#include "oniguruma.h"
#undef regex_t
#include "onigposix.h"


#pragma comment (lib,"msvc6prj_d/Onig_dll.lib")

namespace VCF {
	class RegExKit {
	public:
		static void init( int argc, char** argv ) {

		}

		static void terminate() {
			onig_end();
		}

	};

	class PosixRegExpression {
	public:
		operator const regex_t* () const {
			return &reg_;
		}

		operator regex_t* () {
			return &reg_;
		}

		void compile( const String& pattern ) {
			pattern_ = pattern;
			int err = regcomp( &reg_, pattern_.ansi_c_str(), REG_EXTENDED );

			if ( err ) {
				throw RuntimeException( getErrorString(err) );
			}			
		}


		String getErrorString( int errorCode ) const {
			char tmp[256];
			::regerror( errorCode, &reg_, tmp, sizeof(tmp));
			return String(tmp);
		}
	protected:
		String pattern_;
		regex_t reg_;
	};


};



using namespace VCF;



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	RegExKit::init( argc, argv );
	

	RegExKit::terminate();

	FoundationKit::terminate();
	return 0;
}


