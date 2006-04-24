#ifndef _VCF_TEXTCODEC_H__
#define _VCF_TEXTCODEC_H__
//TextCodec.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
\class TextCodec TextCodec.h "vcf/FoundationKit/TextCodec.h"
The TextCode class represents a way of transforming an ansi or unicode string
into another form of unicode. It represents the logic required to make this
transformation as specified in a code page, i.e. translating an ansi string
into UTF16.
*/
class FOUNDATIONKIT_API TextCodec {
public:
	virtual ~TextCodec(){}
	/**
	converts a unicode string to an ansi string. The function will transform
	ansiStrBufferLength bytes of ansiStrBuffer to an ansii string. Null termination
	of the buffer passed into this function is <b>not</b> performed.
	@param UnicodeString the string to convert from
	@param UnicodeString::AnsiChar* the caller allocated buffer to put the
	newly transformed ansi string data into. If this is NULL, then
	the ansiStrBufferLength parameter is to be ignored, and the function
	should return the number of characters that would need to be allocated
	by the caller to successfully hold all of the ansi string.
	@param ulong32 the length of the ansiStrBuffer. The codec will put no more than this
	number of characters into the ansiStrBuffer.
	@return ulong32 the number of characters in the ansi string. Will be less than or
	equal to ansiStrBufferLength.
	*/
	virtual ulong32 convertToAnsiString( const UnicodeString& str, UnicodeString::AnsiChar* ansiStrBuffer,
										const ulong32& ansiStrBufferLength ) = 0;

	/**
	Transforms a single Unicode character to an ansi character.
	*/
	virtual UnicodeString::AnsiChar convertToAnsiChar( const UnicodeString::UniChar& c ) = 0;

	/**
	Convert one unicode string into the code page type of this codec.
	*/
	virtual UnicodeString convertToUnicodeString( const UnicodeString& str ) = 0;

	/**
	Converts an ansi string to a unicode string
	*/
	virtual UnicodeString convertToUnicodeString( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength ) = 0;

	virtual String getName() = 0;

	/**
	This is a static function to be called in order to register a custom implementation
	of the TextCodec class with the system's collection of codecs. The collection of codec's
	is a map that is keyed by the name of the codec.
	*/
	static void registerCodec( TextCodec* codec );

	/**
	A static method to retreive a registered codec, by name, from the system's
	collection of codecs.
	@param UnicodeString the name of the code to find
	@return TextCodec a codec that is associated with the codecName argument, or
	NULL if no matching codec by that name can be found.
	*/
	static TextCodec* getCodec( const String& codecName );


	static void internal_freeAllRegisteredCodecs();

protected:
	static std::map<String,TextCodec*> registeredCodecsMap;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/03/12 22:01:41  ddiego
*doc updates.
*
*Revision 1.2.6.1  2005/11/27 23:55:45  ddiego
*more osx updates.
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
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 04:00:30  ddiego
*added some missing files for locales
*
*/


#endif // _VCF_TEXTCODEC_H__


