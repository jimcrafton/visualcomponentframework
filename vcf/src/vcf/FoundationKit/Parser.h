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
*A parsing utility class, at this moment (8/25/2001) meant
*for internal use only
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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/09 17:21:32  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.6  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.22.1  2003/03/12 03:11:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PARSER_H__


