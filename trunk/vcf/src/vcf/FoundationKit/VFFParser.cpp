//VFFParser.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VFFParser.h"

using namespace VCF;


VFFParser::VFFParser( InputStream* is )
{
	stream_ = is;

	buffer_ =  NULL;

	resetStream();
}

VFFParser::~VFFParser()
{
	delete [] buffer_;
}

void VFFParser::resetStream()
{
	if ( NULL != buffer_ ) {
		delete [] buffer_;
	}

	uint32 strSize = stream_->getSize();
	buffer_ =  new VCFChar[ strSize+1 ];
	memset( buffer_, 0, (strSize+1) * sizeof(VCFChar) );

	char* tmp = new char[ strSize+1 ];
	memset( tmp, 0, (strSize+1) * sizeof(char) );

	stream_->seek( 0, stSeekFromStart );

	stream_->read( (unsigned char*)tmp, stream_->getSize() );

	String tmpStr = tmp;
	delete [] tmp;

	tmpStr.copy( buffer_, tmpStr.size() );

	bufPtr_ = buffer_;
	bufEnd_ = bufPtr_ + stream_->getSize();

	VCF_ASSERT( bufEnd_ > bufPtr_ );

	current_.sourcePtr = buffer_;
	current_.sourceEnd = buffer_;
	current_.tokenPtr = buffer_;
	current_.sourceLine = 1;
	current_.token = '\0';

	VCFChar token = nextToken();
	while ( TO_COMMENT == token ) {
		token = nextToken();
	}
}

void VFFParser::skipBlanks()
{
	while (current_.sourcePtr < bufEnd_) {
		if ( *current_.sourcePtr == 10 ) {
			current_.sourceLine ++;
		}
		else if ( (*current_.sourcePtr >= 33) && (*current_.sourcePtr <= 255) ) {
			return;
		}
		current_.sourcePtr++;
	}
}

void VFFParser::checkToken( const VCFChar& T )
{
	if ( current_.token != T ) {
		switch ( T ) {
			case TO_SYMBOL: {
				error("Identifier Expected");
			}
			break;

			case TO_STRING: {
				error("String Expected" );
			}
			break;

			case TO_INTEGER: case TO_FLOAT: {
				error("Number Expected");
			}
			break;

			default: {
				error( Format("Char Expected, instead: %c") % T );
			}
			break;
		}
	}
}

String VFFParser::binHexToString()
{
	String result;

	skipBlanks();
	VCFChar* tmpBufPtr = current_.sourcePtr;
	VCFChar* tmpSourcePtr = current_.sourcePtr;
	while ( *tmpSourcePtr != '}' && (tmpSourcePtr < bufEnd_) ) {
		if ( ((*tmpSourcePtr >= '0') && (*tmpSourcePtr <= '9')) || ((*tmpSourcePtr >= 'A') && (*tmpSourcePtr <= 'F'))
				|| ((*tmpSourcePtr >= 'a') && (*tmpSourcePtr <= 'f')) ) {
			current_.sourcePtr ++;
		}
		tmpSourcePtr++;
	}
	result.append( tmpBufPtr, current_.sourcePtr-tmpBufPtr);
	current_.sourcePtr = tmpSourcePtr;

	return result;
}

void VFFParser::checkTokenSymbol( const String& s )
{
	bool tki = tokenSymbolIs( s );
	if ( false == tki ) {
		error( Format("Symbol Expected, instead: %s") % s.c_str() );
	}
}

void VFFParser::error( const String& Ident )
{
	errorStr(Ident);
}

void VFFParser::errorStr( const String& Message)
{
	throw RuntimeException( MAKE_ERROR_MSG_2(Format("Parse Error, message: %s") % Message ) );
}

VCFChar VFFParser::nextToken()
{
	VCFChar result = '\0';
	int32 I = 0;
	VCFChar* P = NULL;
	VCFChar* S = NULL;

	skipBlanks();

	P = current_.sourcePtr;
	current_.tokenPtr = P;
	if ( ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ( *P == '_' ) ) {
		P++;
		while ( ((*P == ':')) || ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ((*P >= '0') && (*P <= '9')) || ( *P == '_' )
			     || ( *P == '@' ) && (P < bufEnd_) ) {
			P++;
		}
		result = TO_SYMBOL;
	}
	else if ( *P == '@' ) {
		P++;
		if ( ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ( *P == '_' ) && (P < bufEnd_) ) {
			P++;
			while ( ((*P == ':') || (*P == '.')) || ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ((*P >= '0') && (*P <= '9')) || ( *P == '_' )
				    || ( *P == '@' ) && (P < bufEnd_) ) {
				P++;
			}
			result = TO_SYMBOL;
		}
	}
	else if ( (*P == '#') || (*P == '\'') ) {
		S = P;
		bool finished = false;
		while ( !finished ) {
			switch ( *P ) {
				case '#' :
				{
					P++;
					I = 0;
					while ( (*P >= '0') && (*P <= '9') && (P < bufEnd_) ) {
						I = I * 10 + (((int)(*P)) - ((int)('0')));
						P++;
					}
					*S = (VCFChar)I;
					S++;
				}
				break;

				case '\'' :
				{
					P++;
					bool finished2 = false;
					while ( !finished2 ) {
						switch ( *P ) {
							case '\0': case 10: case 13 : {
								error( "Invalid String" );
							}
							break;

							case '\'' : {
								P++;
								if ( *P != '\'' ) {
									finished2 = true;
								}
							}
							break;
						}
						

						if ( (*P != '\n') && (*P != '\r') ) {
							*S = *P;
						}
						else {
							*S = '\0';
						}

						if ( finished2 ) {
							S++;
							break;//out of while loop
						}

						P++;
						S++;
					}
				}
				break;

				default : {
					finished = true;
				}
				break;
			}
		}
		current_.stringPtr = S;
		result = TO_STRING;
	}
	else if ( *P == '/' ) {
		P++;
		if ( *P == '/'  && (P < bufEnd_) ) {
			while ( ((*P != '\r') && (*P != '\n'))  && (P < bufEnd_) ) {
				P++;
			}
			result = TO_COMMENT;
		}
		else{
			P--;
		}
	}
	else if ( *P == '$' ) {
		P++;
		while ( ((*P >= '0') && (*P <= '9')) || ((*P >= 'A') && (*P <= 'F')) || ((*P >= 'a') && (*P <= 'f')) && (P < bufEnd_) ) {
			P++;
		}

		//skip over any unit type
		while ( ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) && (P < bufEnd_) ) {
			P++;
		}

		result = TO_INTEGER;
	}
    else if ( (*P == '-') ||  ((*P >= '0') && (*P <= '9')) ) {
		P++;
		while ( ((*P >= '0') && (*P <= '9')) && (P < bufEnd_) ) {
			P++;
		}
		result = TO_INTEGER;
		while ( ((*P >= '0') && (*P <= '9')) || (*P == '.') || (*P == 'e') || (*P == '+') || (*P == '-') && (P < bufEnd_) ) {
			P++;
			result = TO_FLOAT;
		}

		//skip over any unit type
		while ( ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) && (P < bufEnd_) ) {
			P++;
		}
	}
	else {
		result = *P;
		if ( result != TO_EOF ) {
			P++;
		}
	}
	current_.sourcePtr = P;
	current_.token = result;

	return result;
}

int32 VFFParser::sourcePos()
{
	return origin_ + (current_.tokenPtr - buffer_);
}

String VFFParser::tokenComponentIdent()
{

	checkToken( TO_SYMBOL );
	VCFChar* P = current_.sourcePtr;

	while ( (*P == '.') && (P < bufEnd_) ) {
		P++;
		bool alpha = ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ( *P == '_' );
		if ( !alpha ) {
			error( "Identifier Expected" );
		}

		do {
			alpha = ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ((*P >= '0') && (*P <= '9')) || ( *P == '_' );
			P++;
		}while ( !alpha && (P < bufEnd_) );
	}

	current_.sourcePtr = P;

	return tokenString();
}

double VFFParser::tokenFloat()
{
	String s = tokenString();
	double result = StringUtils::fromStringAsFloat( s );
	return result;
}

int32 VFFParser::tokenInt()
{
	String s = tokenString();
	int32 result = StringUtils::fromStringAsInt( s );
	return result;
}

String VFFParser::tokenString()
{
	String result;

	uint32 length = 0;

	if ( current_.token == TO_STRING) {
		if ( current_.stringPtr > current_.tokenPtr ) {
			length = (current_.stringPtr - current_.tokenPtr) - 1;
		}
	}
	else {
		if ( current_.sourcePtr > current_.tokenPtr ) {
			length = current_.sourcePtr - current_.tokenPtr;
		}
	}

	if ( length > 0 ) {
		result.assign( current_.tokenPtr, length );
	}

	return result;
}

bool VFFParser::tokenSymbolIs(const String& s)
{
	return (current_.token == TO_SYMBOL) && (StringUtils::noCaseCompare( s, tokenString() ) == 0);
}

void VFFParser::savePosition()
{
	saved_ = current_;
}

void VFFParser::restorePosition()
{
	current_ = saved_;
}

/**
$Id$
*/
