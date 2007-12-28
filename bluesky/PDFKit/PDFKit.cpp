////PDFKit.cpp
//http://libharu.sourceforge.net/

#include "vcf/FoundationKit/FoundationKit.h"




#include "hpdf.h"





using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );


	{

		FileInputStream is("test2.pdf");

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

		uint64 entryByteOffset = 0;
		uint32 entryGenerationNum = 0;
		AnsiString entryType;

		size_t objEntryIndex = 0;

		
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

							 state = readingXRefEntry;
						}						
					}
					break;

					case readingXRefEntry : {
						
						VCF_ASSERT( val.size() == 18 ); //Adobe spec says 20, we're skipping the \r\n

						size_t pos1 = val.find( " " );
						size_t pos2 = val.find( " ", pos1+1 );

						if ( pos1 != String::npos ) {
							VCF_ASSERT( pos1 == 10 );

							entryByteOffset = 
								atoi( val.substr( 0, 10 ).c_str() );
						}

						if ( pos2 != String::npos ) {
							VCF_ASSERT( pos2 == 16 );

							entryGenerationNum = 
								atoi( val.substr( pos1+1, 5 ).c_str() );


							entryType = val.substr( pos2+1, 1 );
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


