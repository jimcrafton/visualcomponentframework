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

	sourcePtr_ = buffer_;
	sourceEnd_ = buffer_;
	tokenPtr_ = buffer_;
	sourceLine_ = 1;
	token_ = '\0';
	this->nextToken();
}

void VFFParser::skipBlanks()
{
	while (true) {
		if ( *sourcePtr_ == 10 ) {
			sourceLine_ ++;
		}
		else if ( (*sourcePtr_ >= 33) && (*sourcePtr_ <= 255) ) {
			return;
		}
		sourcePtr_++;
	}
}

void VFFParser::checkToken( const VCFChar& T )
{
	if ( token_ != T ) {
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
				error( StringUtils::format( Format("Char Expected, instead: %c") % T ) );
			}
			break;
		}
	}
}

String VFFParser::binHexToString()
{
	String result;

	skipBlanks();
	VCFChar* tmpBufPtr = sourcePtr_;
	VCFChar* tmpSourcePtr = sourcePtr_;
	while ( *tmpSourcePtr != '}' ) {
		if ( ((*tmpSourcePtr >= '0') && (*tmpSourcePtr <= '9')) || ((*tmpSourcePtr >= 'A') && (*tmpSourcePtr <= 'F'))
				|| ((*tmpSourcePtr >= 'a') && (*tmpSourcePtr <= 'f')) ) {
			sourcePtr_ ++;
		}
		tmpSourcePtr++;
	}
	result.append( tmpBufPtr, sourcePtr_-tmpBufPtr);
	sourcePtr_ = tmpSourcePtr;

	return result;
}

void VFFParser::checkTokenSymbol( const String& s )
{
	bool tki = tokenSymbolIs( s );
	if ( false == tki ) {
		error( StringUtils::format( Format("Symbol Expected, instead: %s") % s.c_str() ) );
	}
}

void VFFParser::error( const String& Ident )
{
	errorStr(Ident);
}

void VFFParser::errorStr( const String& Message)
{
	throw RuntimeException( MAKE_ERROR_MSG_2(StringUtils::format( Format("Parse Error, message: %s") % Message )) );
}

VCFChar VFFParser::nextToken()
{
	VCFChar result = '\0';
	int32 I = 0;
	VCFChar* P = NULL;
	VCFChar* S = NULL;

	skipBlanks();

	P = sourcePtr_;
	tokenPtr_ = P;
	if ( ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ( *P == '_' ) ) {
		P++;
		while ( ((*P == ':')) || ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ((*P >= '0') && (*P <= '9')) || ( *P == '_' )
			     || ( *P == '@' ) ) {
			P++;
		}
		result = TO_SYMBOL;
	}
	else if ( *P == '@' ) {
		P++;
		if ( ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ( *P == '_' ) ) {
			P++;
			while ( ((*P == ':')) || ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ((*P >= '0') && (*P <= '9')) || ( *P == '_' )
				    || ( *P == '@' ) ) {
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
					while ( (*P >= '0') && (*P <= '9') ) {
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
		this->stringPtr_ = S;
		result = TO_STRING;
	}
	else if ( *P == '$' ) {
		P++;
		while ( ((*P >= '0') && (*P <= '9')) || ((*P >= 'A') && (*P <= 'F')) || ((*P >= 'a') && (*P <= 'f')) ) {
			P++;
		}
		result = TO_INTEGER;
	}
    else if ( (*P == '-') ||  ((*P >= '0') && (*P <= '9')) ) {
		P++;
		while ( ((*P >= '0') && (*P <= '9')) ) {
			P++;
		}
		result = TO_INTEGER;
		while ( ((*P >= '0') && (*P <= '9')) || (*P == '.') || (*P == 'e') || (*P == '+') || (*P == '-') ) {
			P++;
			result = TO_FLOAT;
		}
	}
	else {
		result = *P;
		if ( result != TO_EOF ) {
			P++;
		}
	}
	sourcePtr_ = P;
	token_ = result;

	return result;
}

int32 VFFParser::sourcePos()
{
	return origin_ + (tokenPtr_ - buffer_);
}

String VFFParser::tokenComponentIdent()
{

	checkToken( TO_SYMBOL );
	VCFChar* P = sourcePtr_;

	while ( (*P == '.') ) {
		P++;
		bool alpha = ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ( *P == '_' );
		if ( !alpha ) {
			error( "Identifier Expected" );
		}

		do {
			alpha = ((*P >= 'A') && (*P <= 'Z')) || ((*P >= 'a') && (*P <= 'z')) || ((*P >= '0') && (*P <= '9')) || ( *P == '_' );
			P++;
		}while ( !alpha );
	}

	sourcePtr_ = P;

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
	int32 length = 0;
	if ( token_ == TO_STRING) {
		length = (stringPtr_ - tokenPtr_) - 1;
	}
	else {
		length = sourcePtr_ - tokenPtr_;
	}
	result.append( tokenPtr_, length );

	return result;
}

bool VFFParser::tokenSymbolIs(const String& s)
{
	return (token_ == TO_SYMBOL) && (StringUtils::noCaseCompare( s, tokenString() ) == 0);
}


/**
$Id$
*/
