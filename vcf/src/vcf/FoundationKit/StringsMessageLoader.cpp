//StringsMessageLoader.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/StringsMessageLoader.h"


using namespace VCF;


StringsMessageLoader::StringsMessageLoader()
{

}

StringsMessageLoader::~StringsMessageLoader()
{
	TranslationMap::iterator it = translationTable_.begin();
	while ( it != translationTable_.end() ) {
		delete it->second;
		it ++;
	}
}

void StringsMessageLoader::processEscapeSequence( UnicodeString& escapeSeqString, UnicodeString& tokenString )
{
	if ( escapeSeqString.size() == 1 ) {
		switch ( escapeSeqString.at(0) ) {
			case 'n' : {
				tokenString += "\n";
			}
			break;

			case 'r' : {
				tokenString += "\r";
			}
			break;

			case 't' : {
				tokenString += "\t";
			}
			break;

			case '\\' : {
				tokenString += "\\";
			}
			break;

			case '"' : {
				tokenString += "\"";
			}
			break;

			case '\'' : {
				tokenString += "'";
			}
			break;

			case '?' : {
				tokenString += "?";
			}
			break;
		}
	}
	else if ( !escapeSeqString.empty() ) {
		switch ( escapeSeqString.at(0) ) {
			case 'x' : {
				if ( escapeSeqString.size() == 4 ) {
					escapeSeqString = escapeSeqString.erase( 0, 1 );
					int c = 0;
					sscanf( escapeSeqString.ansi_c_str(), "%03x", &c );

					tokenString += (char)c;
				}
			}
			break;

			case 'U' : {
				//unicode character
				if ( escapeSeqString.size() == 5 ) {
					escapeSeqString = escapeSeqString.erase( 0, 1 );

					int c = 0;
					sscanf( escapeSeqString.ansi_c_str(), "%04x", &c );

					tokenString += (UnicodeString::UniChar)c;
				}
			}
			break;

			default : {
				if ( escapeSeqString.size() == 3 ) {

					int c = 0;
					sscanf( escapeSeqString.ansi_c_str(), "%03o", &c );

					tokenString += (char)c;
				}
			}
			break;

		}
	}
}

void StringsMessageLoader::loadMessageFile( const UnicodeString& fileName )
{
	currentTableName_ = fileName;
	if ( translationTable_.find( fileName ) != translationTable_.end() ) {
		return; //already loaded!
	}


	FileInputStream fs( fileName );
	String contents;
	fs >> contents;

	fs.close();

	parseState_ = psToken;

	uint32 length = contents.size();
	const VCFChar* P = contents.c_str();
	const VCFChar* start = P;
	const VCFChar* token;

	int commentLevel = 0;

	UnicodeString key;
	UnicodeString value;

	KeyValMap* keyMap = new KeyValMap();

	KeyValMap& keyMapRef = *keyMap;

	ParseState previousParseState;

	UnicodeString tokenString;
	UnicodeString escapeSeqString;

	int line = 1;
	int col = 1;
	while ( (P-start) < length ) {

		switch ( *P ) {

			case '\n' : case '\r' : {

				//make sure to skip over carriage returns
				//for token string appending

				if ( (psKey == parseState_) || (psValue == parseState_) ){
					tokenString = tokenString.append( token, P-token );
				}

				if ( *P == '\r' ) {
					if ( *(P+1) == '\n' ) {
						P++;
					}
				}

				if ( (psKey == parseState_) || (psValue == parseState_) ){
					token = P+1;
				}

				line ++;
				col = 1;
			}
			break;

			case '/' : {
				//look
				if ( psToken == parseState_ ) {
					if ( *(P+1) == '*' ) {
						//comment!
						P++;
						parseState_ = psComment;

						commentLevel ++;
					}
				}
			}
			break;

			case '*' : {
				//look
				if ( psComment == parseState_ ) {
					if ( *(P+1) == '/' ) {
						//comment!
						P++;

						commentLevel --;
						if ( 0 == commentLevel ) {
							parseState_ = psToken;
						}
					}
				}
			}
			break;

			case '"' : {
				switch ( parseState_ ) {
					case psToken : {
						parseState_ = psKey;
						tokenString = "";

						token = P + 1;
					}
					break;

					case psKey : {
						if ( *(P-1) != '\\' ) {
							parseState_ = psToken;

							tokenString = tokenString.append( token, P-token );

							key = tokenString;
						}
					}
					break;

					case psAssignment : {
						parseState_ = psValue;
						tokenString = "";
						
						token = P + 1;
					}
					break;

					case psValue : {
						if ( *(P-1) != '\\' ) {
							parseState_ = psToken;

							tokenString = tokenString.append( token, P-token );

							value = tokenString;

							if ( !key.empty() && !value.empty() ) {
								keyMapRef[ key ] = value;
							}
						}
					}
					break;

					case psEscapeSequence : {
						parseState_ = previousParseState;

						escapeSeqString = "";

						escapeSeqString = escapeSeqString.append( token, P-token );


						if ( !escapeSeqString.empty() ) {
							processEscapeSequence( escapeSeqString, tokenString );
						}
						else {
							throw Exception( "Invalid escape sequence - no escape code specified.", line, col );
						}

						//reset the token so we skip over the escape sequence characters
						token = P;

						//move the pointer back one so we cycle back through and close the
						//value or key string
						P--;
						col --;


					}
					break;
				}
			}
			break;

			case '=' : {
				switch ( parseState_ ) {
					case psToken : {
						parseState_ = psAssignment;
					}
					break;

					case psEscapeSequence : {
						throw Exception( "Invalid escape sequence - no escape code specified.", line, col );
					}
					break;
				}
			}
			break;


			case '\\' : {
				if ( (psValue == parseState_) || (psKey == parseState_)) {
					previousParseState = parseState_;

					escapeSeqString = "";

					tokenString = tokenString.append( token, P-token );

					parseState_ = psEscapeSequence;

					token = P+1;
				}
			}
			break;

			default : {
				bool doEscSequence = false;
				if ( psEscapeSequence == parseState_ ) {
					switch ( *token ) {
						case 'n' : case 'r' : case 't' : case '\\' :
							case '"' : case '\'' : case '?' : {

							doEscSequence = true;
						}
						break;

						case '0' : { //octal triplet
							if ( (P-token) == 2 ) {
								doEscSequence = true;
							}
						}
						break;

						case 'x' : { //hex triplet
							if ( (P-token) == 3 ) {
								doEscSequence = true;
							}
						}
						break;

						case 'U' : { //Unicode hex quadruplet
							if ( (P-token) == 4 ) {
								doEscSequence = true;
							}
						}
						break;
					}

					if ( doEscSequence ) {
						parseState_ = previousParseState;

						escapeSeqString = "";

						escapeSeqString = escapeSeqString.append( token, (P-token)+1 );

						if ( !escapeSeqString.empty() ) {
							processEscapeSequence( escapeSeqString, tokenString );
						}
						else {
							throw Exception( "Invalid escape sequence - no escape code specified.", line, col );
						}

						token = P+1;
					}
				}
			}
			break;
		}

		col ++;

		P++;
	}



	if ( keyMapRef.empty() ) {
		delete keyMap;
	}
	else {
		translationTable_[fileName] = keyMap;
	}
}

UnicodeString StringsMessageLoader::getMessageFromID( const UnicodeString& id )
{
	TranslationMap::iterator found = translationTable_.find( currentTableName_ );
	if ( found != translationTable_.end() ) {
		KeyValMap& keyMap = *found->second;

		KeyValMap::iterator found2 = keyMap.find( id );
		if ( found2 != keyMap.end() ) {
			return found2->second;
		}
	}


	return "";
}


/**
$Id$
*/
