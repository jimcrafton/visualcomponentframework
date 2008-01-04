#ifndef _VCF_VFFPARSER_H__
#define _VCF_VFFPARSER_H__
//VFFParser.h

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



/**
\class VFFParser VFFParser.h "vcf/FoundationKit/VFFParser.h"
A class used for parsing VFF files, at this moment (8/25/2001) meant
for internal use only.

The Visual Form File (VFF) is a text based format used to store
components. The syntax can be represented in Backus-Naur format:

<pre>
component-decl ::= "object" component-id component-properties 
    *(component-decl) component-delegates  "end"
component-id ::= component-name component-class ["," component-classid]

component-name ::= id
id ::= ALPHA *(ALPHA | DIGIT | '_' )
component-class ::= ALPHA *(ALPHA | DIGIT | '_' | "::" )
component-classid ::= ''' 1*(ALPHA | DIGIT | '-' ) '''

component-properties ::= 1*component-property
component-property ::= property-name '=' property-value
property-name ::= id | property-object-name
property-object-name ::= property-name '.' property-name
property-value ::= property-string | property-number | 
    property-component-ref | property-enum |
    property-enum-mask | property-binary | property-bool


property-string ::= ''' *(ALPHA | DIGIT | 'any printable unicode char' )  '''
property-number ::= 1*DIGIT ['.' 1*(DIGIT) ]
property-component-ref ::= ('@' component-name) | "null"
property-enum ::= id
property-enum-mask ::= '[' property-enum *[',' property-enum]  ']'
property-binary ::= '{'  binary-data  '}'
binary-data ::=  1*(binary-byte)
binary-byte ::= (DIGIT | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' ) 
    (DIGIT | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' )
property-bool ::=  "true" | "false"

component-delegates ::= "delegates"  *(component-delegate-decl) "end"
component-delegate-decl ::= delegate-name '=' delegate-array
delegate-name ::= id
delegate-array ::= '[' 1*(event-handler-ref)  ']'
event-handler-ref ::= component-instance '@' component-callback-method
component-instance ::= id
component-callback-method ::= component-classname "::" component-methodname
component-classname ::= id
component-methodname ::= id
</pre>

*/
class FOUNDATIONKIT_API VFFParser : public Object {
public:

	enum {		
		PARSE_BUF_SIZE = 4096,
		TO_EOF = 0,
		TO_SYMBOL,
		TO_STRING,
		TO_INTEGER,
		TO_FLOAT,
		TO_COMMENT
	};

	VFFParser( InputStream* is );

	virtual ~VFFParser();

	void resetStream();

	void checkToken( const VCFChar& T );

	void checkTokenSymbol( const String& s );

	void error( const String& Ident );

	void errorStr( const String& Message);

	VCFChar nextToken();

	int32 sourcePos();

	String tokenComponentIdent();

	double tokenFloat();

	int32 tokenInt();

	String tokenString();

	bool tokenSymbolIs(const String& s);

    int32 getSourceLine() {
		return sourceLine_;
	}

    VCFChar getToken(){
		return token_;
	}

	String binHexToString();

protected:
	InputStream* stream_;
	int32 origin_;
	VCFChar* buffer_;
	VCFChar* bufPtr_;
	VCFChar* bufEnd_;
	VCFChar* sourcePtr_;
	VCFChar* sourceEnd_;
	VCFChar* tokenPtr_;
	VCFChar* stringPtr_;
	int32 sourceLine_;
	VCFChar saveChar_;
	VCFChar token_;

	void skipBlanks();
};


}; // namespace VCF


#endif // _VCF_PARSER_H__

/**
$Id$
*/
