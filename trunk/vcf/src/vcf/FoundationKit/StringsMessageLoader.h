#ifndef _VCF_STRINGSMESSAGELOADER_H__
#define _VCF_STRINGSMESSAGELOADER_H__
//StringsMessageLoader.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_MESSAGELOADER_H__
#	include "vcf/FoundationKit/MessageLoader.h"
#endif // _VCF_MESSAGELOADER_H__

namespace VCF {


class FOUNDATIONKIT_API StringsMessageLoader : public MessageLoader {
public:

	class FOUNDATIONKIT_API Exception : public BasicException {
	public:
		Exception( const String& message, int line, int col ):
		  BasicException( message + StringUtils::format( "\nError occurred on line %d, column %d.", line, col ) ) {	}
	};

	StringsMessageLoader();

	virtual ~StringsMessageLoader();

	virtual void loadMessageFile( const UnicodeString& fileName );

	virtual UnicodeString getMessageFromID( const UnicodeString& id );


protected:
	enum ParseState{
		psToken,
		psComment,
		psKey,
		psAssignment,
		psValue,
		psEscapeSequence
	};

	typedef std::pair<UnicodeString,UnicodeString> KeyValPair;
	typedef std::map<UnicodeString,UnicodeString> KeyValMap;

	typedef std::map<UnicodeString,KeyValMap*> TranslationMap;

	TranslationMap translationTable_;
	ParseState parseState_;
	UnicodeString currentTableName_;

	void processEscapeSequence( UnicodeString& escapeSeqString, UnicodeString& tokenString );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_STRINGSMESSAGELOADER_H__


