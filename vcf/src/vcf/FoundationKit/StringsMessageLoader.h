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

/**
\class StringsMessageLoader StringsMessageLoader.h "vcf/FoundationKit/StringsMessageLoader.h"
*/
class FOUNDATIONKIT_API StringsMessageLoader : public MessageLoader {
public:

	class FOUNDATIONKIT_API Exception : public BasicException {
	public:
		Exception( const String& message, int line, int col ):
		  BasicException( message + StringUtils::format( Format("\nError occurred on line %d, column %d.") % line % col ) ) {	}
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
*Revision 1.4  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/12 22:01:41  ddiego
*doc updates.
*
*Revision 1.3  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/03/15 01:51:52  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
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


