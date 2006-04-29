#ifndef _VCF_PARSER_H__
#define _VCF_PARSER_H__
//Parser.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class InputStream;

#define PARSE_BUF_SIZE		4096

#define TO_EOF				0
#define TO_SYMBOL			1
#define TO_STRING			2
#define TO_INTEGER			3
#define TO_FLOAT			4


/**
\class Parser Parser.h "vcf/FoundationKit/Parser.h"
A parsing utility class, at this moment (8/25/2001) meant
for internal use only
*/
class FOUNDATIONKIT_API Parser : public Object {
public:

	Parser( InputStream* is );

	virtual ~Parser();

	void resetStream();

	void checkToken( const VCFChar& T );

	void checkTokenSymbol( const String& s );

	void error( const String& Ident );

	void errorStr( const String& Message);

	VCFChar nextToken();

	long sourcePos();

	String tokenComponentIdent();

	double tokenFloat();

	long tokenInt();

	String tokenString();

	bool tokenSymbolIs(const String& s);

    long getSourceLine() {
		return sourceLine_;
	}

    VCFChar getToken(){
		return token_;
	}

	String binHexToString();

protected:
	InputStream* stream_;
	long origin_;
	VCFChar* buffer_;
	VCFChar* bufPtr_;
	VCFChar* bufEnd_;
	VCFChar* sourcePtr_;
	VCFChar* sourceEnd_;
	VCFChar* tokenPtr_;
	VCFChar* stringPtr_;
	long sourceLine_;
	VCFChar saveChar_;
	VCFChar token_;

	void skipBlanks();
};


}; // namespace VCF


#endif // _VCF_PARSER_H__

/**
$Id$
*/
