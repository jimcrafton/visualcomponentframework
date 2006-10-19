#ifndef _VCF_TEXTOUTPUTSTREAM_H__
#define _VCF_TEXTOUTPUTSTREAM_H__
//TextOutputStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{


/**
\class TextOutputStream TextOutputStream.h "vcf/FoundationKit/TextOutputStream.h"
*The TextOutputStream is used for writing data from another stream as text.
*/
class FOUNDATIONKIT_API TextOutputStream : public OutputStream
{
public:

	TextOutputStream( OutputStream* outStream );

	TextOutputStream();

	virtual ~TextOutputStream();

	virtual void seek(const uint64& offset, const SeekType& offsetFrom);

	virtual uint64 getSize();

	virtual char* getBuffer();

	virtual uint64 getCurrentSeekPos() ;

	virtual uint64 write( const unsigned char* bytesToRead, uint64 sizeOfBytes );

	/**
	*all numbers are written out as the number converted to text, followed by a
	*space character ( ' ' ), so the value 2 becomes "2 "
	*/

	virtual void write( const short& val );

	virtual void write( const long& val );

	virtual void write( const int& val );

	virtual void write( const bool& val );

	virtual void write( const float& val );

	virtual void write( const double& val );

	virtual void write( const String& val );

	void init();

	void writeLine( const String& line );

	String getTextBuffer();

	virtual String toString();
private:
	String textBuffer_;
	uint64 size_;
	OutputStream* outStream_;
};


};


#endif // _VCF_TEXTOUTPUTSTREAM_H__

/**
$Id$
*/
