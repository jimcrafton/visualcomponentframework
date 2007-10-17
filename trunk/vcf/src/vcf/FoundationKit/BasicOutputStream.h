#ifndef _VCF_BASICOUTPUTSTREAM_H__
#define _VCF_BASICOUTPUTSTREAM_H__
//BasicOutputStream.h

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
\class BasicInputStream BasicOutputStream.h "vcf/FoundationKit/BasicOutputStream.h"
*/
class FOUNDATIONKIT_API BasicOutputStream : public OutputStream
{
public:
	BasicOutputStream();

	/**
	*This constructor is used in stream chaining.
	*The flow goes from the BasicOutputStream to the outStream.
	*So if a write is called on the BasicOutputStream, it simply
	*passes it to the outStream's write() method
	*/
	BasicOutputStream( OutputStream* outStream );

	virtual ~BasicOutputStream();

	virtual void seek(const uint64& offset, const SeekType& offsetFrom);

	virtual uint64 getSize();

	virtual char* getBuffer();

	virtual uint64 getCurrentSeekPos();

	virtual uint64 write( const unsigned char* bytesToRead, uint64 sizeOfBytes );

	void init();

	void clear();
private:
	CharMemStream outStream_;
	OutputStream* outputStream_;
};


};


#endif // _VCF_BASICOUTPUTSTREAM_H__

/**
$Id$
*/
