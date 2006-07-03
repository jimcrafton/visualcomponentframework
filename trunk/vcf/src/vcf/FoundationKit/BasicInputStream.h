#ifndef _VCF_BASICINPUTSTREAM_H__
#define _VCF_BASICINPUTSTREAM_H__
//BasicInputStream.h

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
\class BasicInputStream BasicInputStream.h "vcf/FoundationKit/BasicInputStream.h"
*/
class FOUNDATIONKIT_API BasicInputStream : public InputStream
{
public:
	BasicInputStream();

	BasicInputStream( const String& textBuffer );

	BasicInputStream( const char* dataBuffer, const uint32& dataBufferSize );

	/**
	*This constructor is used in stream chaining.
	*The flow goes from the BasicInputStream to the inStream.
	*So if a read is called on the BasicInputStream, it simply
	*passes it to the inStream's read() method
	*/
	BasicInputStream( InputStream* inStream );

	virtual ~BasicInputStream();

	virtual void seek(const uint64& offset, const SeekType& offsetFrom);

	virtual uint64 getSize();

	virtual char* getBuffer();

	virtual uint64 getCurrentSeekPos() ;

	virtual uint32 read( unsigned char* bytesToRead, uint32 sizeOfBytes );

	virtual bool isEOS();

	void init();
private:
	CharMemStream inStream_;
	InputStream* inputStream_;
	uint64 totalStreamSize_;
};

};


#endif // _VCF_BASICINPUTSTREAM_H__

/**
$Id$
*/
