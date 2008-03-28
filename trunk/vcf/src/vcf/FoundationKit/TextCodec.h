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
	@param uint32 the length of the ansiStrBuffer. The codec will put no more than this
	number of characters into the ansiStrBuffer.
	@return uint32 the number of characters in the ansi string. Will be less than or
	equal to ansiStrBufferLength.
	*/
	virtual uint32 convertToAnsiString( const UnicodeString& str, UnicodeString::AnsiChar* ansiStrBuffer,
										const uint32& ansiStrBufferLength,
										const UnicodeString::LanguageEncoding& encoding ) = 0;

	/**
	Transforms a single Unicode character to an ansi character.
	*/
	virtual UnicodeString::AnsiChar convertToAnsiChar( const UnicodeString::UniChar& c, const UnicodeString::LanguageEncoding& encoding ) = 0;

	/**
	Convert one unicode string into the code page type of this codec.
	*/
	virtual UnicodeString convertToUnicodeString( const UnicodeString& str, const UnicodeString::LanguageEncoding& encoding ) = 0;

	/**
	Converts an ansi string to a unicode string
	*/
	virtual UnicodeString convertToUnicodeString( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength, const UnicodeString::LanguageEncoding& encoding ) = 0;

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


#endif // _VCF_TEXTCODEC_H__

/**
$Id$
*/
