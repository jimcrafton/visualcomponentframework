////PDFKit.cpp
//http://libharu.sourceforge.net/

#include "vcf/FoundationKit/FoundationKit.h"
#include <deque>


#include "hpdf.h"





using namespace VCF;


enum XRefEntryType {
	xrefEntryInUse = 1,
	xrefEntryFree,

};

struct XRefEntry {
	XRefEntry(): byteOffset(0), generationNum(0), type(xrefEntryInUse){}
	uint64 byteOffset;
	uint32 generationNum;
	XRefEntryType type;
};

typedef std::vector<XRefEntry> XRefEntryArray;

enum {
	typeObj = 1,
	typeStringLit,
	typeStringHex,
	typeBool,
	typeNumber,
	typeIndirectObjRef,
	typeName
};

struct StackEntry {
	AnsiString value;
	int type;
};

typedef std::vector<StackEntry> StackEntryArray;




class PDFObject {
public:

	enum Type {
		pdfUnknown = 0,
		pdfString,
		pdfBool,
		pdfNumber,
		pdfName,
		pdfArray,
		pdfDictionary,
		pdfStream,
		pdfNull,
		pdfIndirect
	};	

	virtual ~PDFObject() {}

	String keyName;
	
	virtual Type type() const  = 0;

	bool isNull() const {
		return type() == pdfNull;
	}

	virtual void process( const AnsiString& value ) {}

	virtual void process( const StackEntryArray& stack ) {}	

	virtual void process( PDFObject* value ) {}

};


class PDFNull : public PDFObject {
public:

	virtual Type type() const {
		return pdfNull;
	}
};


class PDFValue : public PDFObject {
public:

	const VariantData& value() const {
		return value_;
	}

protected:
	VariantData value_;
};


class PDFBool : public PDFValue {
public:
	
	virtual Type type() const {
		return pdfBool;
	}

	bool boolVal() const {
		return value();
	}

	PDFBool& operator=( const bool& val ) {
		value_ = val;
		return *this;
	}

	virtual void process( const AnsiString& value ) {
		if ( value == "true" ) {
			value_ = true;
		}
		else if ( value == "false" ) {
			value_ = false;
		}
		else {
			throw RuntimeException( "Invalid String assigned to object" );
		}
	}

};


class PDFNumber : public PDFValue {
public:

	virtual Type type() const {
		return pdfNumber;
	}

	int intVal() const {
		return value();
	}

	uint32 uintVal() const {
		return value();
	}

	double realVal() const {
		return value();
	}

	PDFNumber& operator=( const int& val ) {
		value_ = VariantData(val);
		return *this;
	}

	PDFNumber& operator=( const uint32& val ) {
		value_ = VariantData(val);
		return *this;
	}

	PDFNumber& operator=( const double& val ) {
		value_ = VariantData(val);
		return *this;
	}


	virtual void process( const AnsiString& value ) {
		size_t pos = value.find(".");
		if ( pos != String::npos ) {
			value_.type = pdDouble;
		}
		else {
			value_.type = pdInt;
		}

		value_.setFromString( value );
	}
protected:
	
};


class PDFString : public PDFValue {
public:

	virtual Type type() const {
		return pdfString;
	}

	String stringVal() const {
		return value();
	}

	virtual void process( const AnsiString& value ) {		
		value_ = value;		
	}

};





class PDFName : public PDFValue {
public:

	virtual Type type() const {
		return pdfName;
	}

	String stringVal() const {
		return value();
	}

	virtual void process( const AnsiString& value ) {		
		originalName_ = value;
		AnsiString tmp;
		const char* P = originalName_.c_str();
		const char* start = P;
		const char* lastBreak = P;
		while ( P-start < originalName_.size() ) {

			if ( *P == '#' ) {
				P++;
				char hexVal[3] = {0,0,0};

				if ( P-start < originalName_.size() && 
					(*P >= '0' && *P <= '9') ) {

					hexVal[0] = *P;

					P++;
					if ( P-start < originalName_.size() && 
					(*P >= '0' && *P <= '9') ) {
						//hex number replacement
						hexVal[1] = *P;

						tmp.append( lastBreak, (P-lastBreak)-2 );

						int hex = 0;
						sscanf( hexVal, "%x", &hex );

						tmp += (char)hex;


						lastBreak = P+1;
					}
					else {
						P -= 2;
					}
				}
				else {
					P--;
				}
			}

			P++;
		}
		if ( lastBreak < P ) {
			tmp.append( lastBreak, (P-lastBreak) );
		}

		value_ = tmp;
	}

	const AnsiString& originalName() const {
		return originalName_;
	}
protected:
	AnsiString originalName_;
};


class PDFIndirect : public PDFObject {
public:

	enum {
		Invalid = (uint32)-1
	};

	PDFIndirect(): objectNumber_(Invalid), generation_(Invalid){}

	virtual ~PDFIndirect() {
		delete value_;
	}

	virtual Type type() const {
		return pdfIndirect;
	}

	
	virtual void process( const StackEntryArray& stack ) {
		VCF_ASSERT(stack.size() >= 2) ;

		if ( stack.size() >= 2 ) {
			const StackEntry& entry1 = stack[0];
			sscanf( entry1.value.c_str(), "%u", &objectNumber_ );

			const StackEntry& entry2 = stack[1];
			sscanf( entry2.value.c_str(), "%u", &generation_ );
		}
	}

	virtual void process( PDFObject* value ) {
		value_ = value;
	}
	
protected:
	uint32 objectNumber_;
	uint32 generation_;
	PDFObject* value_;
};




class PDFArray : public PDFObject {
public:
	PDFArray(){}

	virtual ~PDFArray() {
		std::vector<PDFObject*>::iterator it = values_.begin();
		while ( it != values_.end() ) {
			delete *it;
			++it;
		}
		values_.clear();
	}

	virtual Type type() const {
		return pdfArray;
	}

	const PDFObject& operator[] ( size_t pos ) const {
		return *values_[pos];
	}

	virtual void process( PDFObject* value ) {
		values_.push_back( value );
	}
	
protected:
	std::vector<PDFObject*> values_;
};


class PDFDictionary : public PDFObject {
public:
	PDFDictionary(){}

	virtual ~PDFDictionary() {
		std::map<String,PDFObject*>::iterator it = values_.begin();
		while ( it != values_.end() ) {
			delete it->second;
			++it;
		}
		values_.clear();
	}

	virtual Type type() const {
		return pdfDictionary;
	}

	const PDFObject* get ( const String& key ) const {
		const PDFObject* result = NULL;
		std::map<String,PDFObject*>::const_iterator found = values_.find( key );
		if ( found != values_.end() ) {
			result = found->second;
		}
		return result;
	}


	const PDFObject& operator[] ( const String& key ) const {
		std::map<String,PDFObject*>::const_iterator found = values_.find( key );
		return *(found->second);
	}

	virtual void process( PDFObject* value ) {
		values_[ value->keyName ] = value;
	}
	
protected:
	std::map<String,PDFObject*> values_;
};


class PDFStream : public PDFDictionary {
public:
	virtual Type type() const {
		return pdfStream;
	}
	
	virtual void process( const AnsiString& value ) {

	}
	
	virtual void process( PDFObject* value ) {
		PDFDictionary::process(value);
	}


	size_t getLength() const {
		size_t result = 0;
		
		const PDFObject& obj = (*this)[ "Length" ];

		VCF_ASSERT( obj.type() == pdfNumber );

		const PDFNumber& length = (const PDFNumber&)obj;
		result = length.uintVal();

		return result;
	}	

	void setLength( const size_t& val ) {
		PDFNumber* length = new PDFNumber();
		*length = val;
		length->keyName = "Length";

		process( length );
	}
protected:
	
};




typedef std::deque<PDFObject*> PDFStack;


enum {
	whitespace = 1,
	delimiter,
	regular
};

enum {
	parsingStringLiteral = 0xff,
	parsingStringLiteralDone,
	parsingStringHex,
	parsingStringHexDone,
	parsingNumber,
	parsingComment,				
	parsingArray,
	parsingArrayDone,
	parsingName,
	parsingDictionary,
	parsingDictionaryDone,
	parsingStream,
	parsingStreamDone,
	parsingObj,
	parsingObjDone,
	parsingIndirectRef,
	parsingBool,
	parsingNull
};

enum {
	objUnk = 0,
	objBool = 1,

};

void parseXRefEntry( const uchar* buf, const size_t& size )
{
	size_t tokenStartOffset = 0;
	int state = 0;
	AnsiString tokenStr;
	int tokenParsingState = 0;
	uchar prevCh, nextCh;
	prevCh = nextCh = 0;
	
	StackEntryArray stack;
	tokenStartOffset = 0;
	PDFStack pdfStack;


	for (size_t i=0;i<size;i++ ) {
					
		nextCh = buf[i+1];

		switch ( buf[i] ) {
			case 0x00 : //null term
			case 0x09 : //tab \t
			case 0x0A : //line feed \r
			case 0x0C : //Form feed 
			case 0x0D : //CR \n
			case 0x20 : //space
			{
				state = whitespace;
			}
			break;

			case '(' :
			case ')': 
			case '<': 
			case '>': 
			case '[':
			case ']':
			case '{':
			case '}':
			case '/':
			case '%':
			{
				state = delimiter;
			}
			break;

			default : {
				state = regular;
			}
			break;
		}



		switch ( state ) {
			case whitespace : {
				if ( tokenParsingState != parsingStringLiteral || 
						tokenParsingState != parsingStringHex ) {
					tokenStr.assign( (const char*)&buf[tokenStartOffset], i-tokenStartOffset );
					tokenStartOffset = i+1;
				}

				if ( tokenStr == "<<" ) {
					tokenParsingState = parsingDictionary;
				}
				else if ( tokenStr == ">>" ) {
					tokenParsingState = parsingDictionaryDone;
				}
				else if ( tokenStr == "stream" ) {
					tokenParsingState = parsingStream;
				}
				else if ( tokenStr == "endstream" ) {
					tokenParsingState = parsingStreamDone;
				}
				else if ( tokenStr == "obj" ) {
					tokenParsingState = parsingObj;
				}
				else if ( tokenStr == "endobj" ) {
					tokenParsingState = parsingObjDone;
				}
				else if ( tokenStr == "R" ) {
					tokenParsingState = parsingIndirectRef;
				}
				else if ( tokenStr == "true" || tokenStr == "false") {
					tokenParsingState = parsingBool;
				}
				
			}
			break;

			case delimiter : {						

				switch ( buf[i] ) {
					case '%':
					{
						tokenStartOffset = i+1;
						tokenParsingState = parsingComment;
					}
					break;

					case '/':
					{
						tokenStartOffset = i+1;
						tokenParsingState = parsingName;
					}
					break;

					case '(':
					{
						tokenStartOffset = i+1;
						tokenParsingState = parsingStringLiteral;
					}
					break;

					case ')':
					{
						tokenStr.assign( (const char*)&buf[tokenStartOffset], i-tokenStartOffset );
						tokenStartOffset = i+1;
						tokenParsingState = parsingStringLiteralDone;
					}
					break;

					case '<':
					{
						if ( nextCh != '<' && prevCh != '<' ) {
							tokenParsingState = parsingStringHex;
							tokenStartOffset = i+1;
						}
					}
					break;

					case '>':
					{
						if ( nextCh != '>' && prevCh != '>' ) {
							tokenStr.assign( (const char*)&buf[tokenStartOffset], i-tokenStartOffset );
							tokenStartOffset = i+1;
							tokenParsingState = parsingStringHexDone;
						}
					}
					break;

					case '[':
					{
						tokenStartOffset = i+1;
						tokenParsingState = parsingArray;
					}
					break;

					case ']':
					{
						tokenStartOffset = i+1;
						tokenParsingState = parsingArrayDone;
					}
					break;
				}
			}
			break;

			case regular : {
				if ( tokenParsingState == 0 ) {
					if ( buf[i] >= '0' && buf[i] <= '9' ) {
						tokenParsingState = parsingNumber;
					}
					else if ( buf[i] == '.' && (nextCh >= '0' && nextCh <= '9') ) {
						tokenParsingState = parsingNumber;
					}
					else if ( buf[i] == '.' && (prevCh >= '0' && prevCh <= '9') ) {
						tokenParsingState = parsingNumber;
					}
					else if ( buf[i] == '.' && (prevCh == '-' || prevCh == '+') ) {
						tokenParsingState = parsingNumber;
					}
					else if ( (buf[i] == '+' || buf[i] == '-') && 
						(nextCh >= '0' && nextCh <= '9' || nextCh == '.') ) {
						tokenParsingState = parsingNumber;
					}
				}
				/*
				else if ( (buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z') ) {
					
				}*/
			}
			break;
		}



		switch ( tokenParsingState ) {
			case parsingStringLiteralDone : {
				System::println( tokenStr );
				tokenParsingState = 0;
			}
			break;

			case parsingStringHexDone : {
				System::println( tokenStr );
				tokenParsingState = 0;
			}
			break;

			case parsingArray : {
				PDFArray* array = new PDFArray();
				pdfStack.push_back( array );							
			}
			break;

			case parsingArrayDone : {							
				tokenParsingState = 0;
				stack.clear();
			}
			break;

			case parsingDictionaryDone : {
				tokenParsingState = 0;
				stack.clear();
			}
			break;

			case parsingObjDone : {
				tokenParsingState = 0;
				stack.clear();
			}
			break;
			
			case parsingStreamDone : {
				tokenParsingState = 0;
				stack.clear();
			}
			break;

			case parsingNumber : {
				if ( state == whitespace ) {

					StackEntry entry;
					entry.type = typeNumber;
					entry.value = tokenStr;
					stack.push_back(entry);

					System::println( tokenStr );
					tokenParsingState = 0;
				}
			}
			break;

			case parsingName : {
				if ( state == whitespace ) {
					StackEntry entry;
					entry.type = typeName;
					entry.value = tokenStr;
					stack.push_back(entry);

					System::println( tokenStr );
					tokenParsingState = 0;
				}
			}
			break;

			case parsingIndirectRef : {
				if ( state == whitespace ) {
					StackEntry entry;
					entry.type = typeIndirectObjRef;
					entry.value = tokenStr;
					stack.push_back(entry);

					System::println( tokenStr );
					tokenParsingState = 0;
				}
			}
			break;

			case parsingBool : {
				if ( state == whitespace ) {
					StackEntry entry;
					entry.type = typeBool;
					entry.value = tokenStr;
					stack.push_back(entry);

					System::println( tokenStr );
					tokenParsingState = 0;
				}
			}
			break;
			

			case parsingComment : {
				if ( buf[i] == '\n' || buf[i] == '\r' ) {
					tokenParsingState = 0;
				}
			}
			break;

		}

		state = 0;
		
		prevCh = buf[i];
		
	}
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );


	PDFName n;
	n.process( "PANTONE#205757#20CV" );
	n.process( "#305757#20CV" );
	n.process( "CV" );
	n.process( "CV#dgg" );

	PDFStream ps;
	ps.setLength( 100 );
	ps.getLength();



	AnsiString pdf = 
"10  0  obj % Page object "\
"<<   /Type  /Page "\
  "/Parent  5 0 R "\
  "/Resources  20 0 R "\
  "/Contents  40 0 R "\
">> "\
"endobj";

	parseXRefEntry( (const uchar*)pdf.c_str(), pdf.length() );



	{
		FilePath fp = "c:\\code\\Direct X.pdf";//"F:/code/vcfdev/dev/bluesky/PDFKit/test2.pdf";
		FilePath fp2 = "E:\\Documents and Settings\\Jim\\My Documents\\CFPreferences.pdf";

		FileInputStream is( fp ); // "test2.pdf");

		const uchar* bytes = NULL;

		uint64 sz = is.getSize();

		uchar header[20];
		is.read( &header[0], sizeof(header) );

		uint64 headerPos = 0;
		
		while ( headerPos < sizeof(header) ) {
			if ( header[headerPos] == '\n' || header[headerPos] == '\r' ) {
				break;
			}
			headerPos++;
		}
		
		String pdfHeader;
		pdfHeader.assign( (const char*)&header[0], headerPos );


		//size_t pdfStart = headerPos;


		uchar endOfFile[1024];
		size_t lastBitSz = minVal<size_t>(1024,sz);


		is.seek( sz - lastBitSz, stSeekFromStart );
		is.read( &endOfFile[0], lastBitSz );

		uint64 trailerPos = lastBitSz;
		bool pdfEOFFound = false;
		uint64 lastEOL = trailerPos-1;

		enum {
			readingEOF = 1,
			readingLastXRefOffset,
			readingStartXRef,
			readingStartXRefBegin,
			readingTrailerEntry,
			readingStartXRefEnd,
			readingTrailer,
			trailerFinished
		};

		int state = 0;

		String eof;
		uint64 lastXRefOffset = 0;

		String trailerEntry;
		typedef std::vector< std::pair<String,String> > EntryVec;
		EntryVec entries;

		do {
			trailerPos --;

			if ( endOfFile[trailerPos] == '\n' ) {
				AnsiString val;
				
				if ( lastEOL > (trailerPos+1) ) {
					val.assign( (const char*)&endOfFile[trailerPos+1], lastEOL - (trailerPos+1) );
				}

				switch ( state ) {
					case 0 : {
						state = readingEOF;
					}
					break;

					case readingEOF : {
						if ( val == "%%EOF" ) {
							state = readingLastXRefOffset;
						}
					}
					break;

					case readingLastXRefOffset : {
						lastXRefOffset = atoi( val.c_str() );

						state = readingStartXRef;
					}
					break;

					case readingStartXRef : {
						if ( val == "startxref" ) {
							state = readingStartXRefEnd;
						}
					}
					break;
					

					case readingStartXRefEnd : {
						if ( val == ">>" ) {
							state = readingTrailerEntry;
						}
					}
					break;

					case readingTrailerEntry : {
						
						
						if ( val == "<<" ) {
							state = readingTrailer;
						}
						else {
							trailerEntry = val;

							size_t pos = trailerEntry.find(" ");
							if ( pos != String::npos ) {
								entries.insert( entries.begin(), std::pair<String,String>( trailerEntry.substr(0,pos), trailerEntry.substr(pos+1, trailerEntry.size()-(pos+1)) ) );
							}							
						}
					}
					break;

					case readingTrailer : {
						if ( val == "trailer" ) {
							state = trailerFinished;
						}
					}
					break;
				}

				lastEOL = trailerPos;
				if ( endOfFile[trailerPos-1] == '\r' ) {
					//trailerPos--;
				}
			}		
			
		} while ( trailerPos > 0 && (state != trailerFinished) );




		EntryVec::iterator it = entries.begin();
		while ( it != entries.end() ) {
			std::pair<String,String>& entry = *it;

			System::println( Format("Key: %s, Val: %s") 
								% entry.first.ansi_c_str()
								% entry.second.ansi_c_str() );
								

			++it;
		}


		uint64 xrefEpos = sz - (lastBitSz - trailerPos);

		if ( lastXRefOffset >= xrefEpos ) {
			throw RuntimeException( "Fucked!" );
		}

		uchar* xrefBuf = new uchar [ xrefEpos - lastXRefOffset ] ;

		is.seek( lastXRefOffset, stSeekFromStart );
		uint64 xrefBufSz = is.read( xrefBuf, xrefEpos - lastXRefOffset );

		const uchar* P = xrefBuf;
		const uchar* line = P;

		enum {
			readingXRef = 1,
			readingXRefHeader,
			readingXRefEntry,
			xrefFinished
		};
		state = readingXRef;

		size_t firstObjectNum = 0;
		size_t objEntryCount = 0;

		size_t objEntryIndex = 0;

		XRefEntryArray xrefTable;
		
		while ( (P - xrefBuf) < xrefBufSz ) {

			if ( *P == '\n' || *P == '\r' || (*P == '\r' && *(P+1) == '\n') ) {

				AnsiString val;
				if ( P > line ) {
					val.assign( (const char*)line, P-line );
				}

				switch ( state ) {
					case readingXRef : {
						if ( val == "xref" ) {
							state = readingXRefHeader;
						}
					}
					break;

					case readingXRefHeader : {
						size_t pos = val.find( " " );
						if ( pos != String::npos ) {
							 firstObjectNum = atoi( val.substr( 0, pos ).c_str() );
							 objEntryCount = atoi( val.substr( pos+1, val.size()-(pos+1) ).c_str() );

							 xrefTable.resize(objEntryCount);

							 state = readingXRefEntry;
						}						
					}
					break;

					case readingXRefEntry : {
						
						//VCF_ASSERT( val.size() == 18 ); //Adobe spec says 20, we're skipping the \r\n

						size_t pos1 = val.find( " " );
						size_t pos2 = val.find( " ", pos1+1 );

						XRefEntry& entry = xrefTable[objEntryIndex];

						if ( pos1 != String::npos ) {
							VCF_ASSERT( pos1 == 10 );

							entry.byteOffset = atoi( val.substr( 0, 10 ).c_str() );
						}

						if ( pos2 != String::npos ) {
							VCF_ASSERT( pos2 == 16 );

							entry.generationNum = atoi( val.substr( pos1+1, 5 ).c_str() );

							AnsiString s = val.substr( pos2+1, 1 );

							if ( s == "n" ) {
								entry.type = xrefEntryInUse;
							}
							else if ( s == "f" ) {
								entry.type = xrefEntryFree;
							}
						}

						objEntryIndex++;					

						state = readingXRefEntry;

						if ( objEntryIndex >= objEntryCount ) {
							state = xrefFinished;
						}
					}
					break;
				}

				if ( *P == '\r' && *(P+1) == '\n' ) {
					P++;
				}

				line = P+1;
			}

			P++;
		}



		delete [] xrefBuf;		

		uint64 entryOffsetEnd = 0;
		uint64 currentOffset = 0;//pdfStart;

		for (size_t i=0;i<xrefTable.size();i++ ) {
			const XRefEntry& entry = xrefTable[i];

			if ( entry.type == xrefEntryFree ) {
				continue;
			}

			if ( i < xrefTable.size()-1 ) {
				entryOffsetEnd = xrefTable[i+1].byteOffset;
			}
			else {
				entryOffsetEnd = lastXRefOffset;
			}


			is.seek( entry.byteOffset, stSeekFromStart );
			

			uchar buf[256];

			

			
			

			do {
				
				size_t bytesRead = is.read( &buf[0], minVal<size_t>( entryOffsetEnd-entry.byteOffset, sizeof(buf) ) );

				parseXRefEntry( &buf[0], bytesRead );

				currentOffset = is.getCurrentSeekPos();
			} while ( currentOffset < entryOffsetEnd );

		}
		
	}

	




/*


	HPDF_Doc  pdf;
	HPDF_Page page;
	HPDF_Point pos;

	AnsiString fname = "test2.pdf";

	pdf = HPDF_New (NULL, NULL);
	HPDF_SetCompressionMode(pdf,HPDF_COMP_ALL);
	
	HPDF_SetInfoAttr( pdf, HPDF_INFO_AUTHOR, "Spazz Jerowski" );
	HPDF_SetInfoAttr( pdf, HPDF_INFO_CREATOR, "Foo Jerowski" );
	HPDF_SetInfoAttr (pdf, HPDF_INFO_PRODUCER, "Dorkmeister Incorporarated." );


	page = HPDF_AddPage (pdf);

	HPDF_Page_SetHeight (page, 220);
    HPDF_Page_SetWidth (page, 200);

	// A 
    HPDF_Page_SetRGBFill (page, 1.0, 0, 0);
    HPDF_Page_MoveTo (page, 100, 100);
    HPDF_Page_LineTo (page, 100, 180);
    HPDF_Page_Arc (page, 100, 100, 80, 0, 360 * 0.45);
    pos = HPDF_Page_GetCurrentPos (page);
    HPDF_Page_LineTo (page, 100, 100);
    HPDF_Page_Fill (page);

    // B
    HPDF_Page_SetRGBFill (page, 0, 0, 1.0);
    HPDF_Page_MoveTo (page, 100, 100);
    HPDF_Page_LineTo (page, pos.x, pos.y);
    HPDF_Page_Arc (page, 100, 100, 80, 360 * 0.45, 360 * 0.7);
    pos = HPDF_Page_GetCurrentPos (page);
    HPDF_Page_LineTo (page, 100, 100);
    HPDF_Page_Fill (page);

    // C
    HPDF_Page_SetRGBFill (page, 0, 1.0, 0);
    HPDF_Page_MoveTo (page, 100, 100);
    HPDF_Page_LineTo (page, pos.x, pos.y);
    HPDF_Page_Arc (page, 100, 100, 80, 360 * 0.7, 360 * 0.85);
    pos = HPDF_Page_GetCurrentPos (page);
    HPDF_Page_LineTo (page, 100, 100);
    HPDF_Page_Fill (page);

    // D 
    HPDF_Page_SetRGBFill (page, 1.0, 1.0, 0);
    HPDF_Page_MoveTo (page, 100, 100);
    HPDF_Page_LineTo (page, pos.x, pos.y);
    HPDF_Page_Arc (page, 100, 100, 80, 360 * 0.85, 360);
    pos = HPDF_Page_GetCurrentPos (page);
    HPDF_Page_LineTo (page, 100, 100);
    HPDF_Page_Fill (page);

    // draw center circle 
    HPDF_Page_SetGrayStroke (page, 0);
    HPDF_Page_SetGrayFill (page, 1);
    HPDF_Page_Circle (page, 100, 100, 30);
    HPDF_Page_Fill (page);


	

	HPDF_SaveToFile (pdf, fname.c_str());

	HPDF_Free (pdf);
*/


	FoundationKit::terminate();
	return 0;
}


