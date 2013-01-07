//ZipOutputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ZipOutputStream.h"



using namespace VCF;





ZipOutputStream::ZipOutputStream():
	outStream_(NULL),
		zipBufferSize_(ZipOutputStream::DataSize)
{

}



ZipOutputStream::ZipOutputStream( OutputStream* outStream ):
	outStream_(outStream)
{
	
}

ZipOutputStream::~ZipOutputStream()
{
	
}

void ZipOutputStream::seek(const uint64& offset, const SeekType& offsetFrom)
{

}

uint64 ZipOutputStream::getSize()
{	
	uint64 result = compressedData_.getSize();

	return result;
}


uchar* ZipOutputStream::getBuffer()
{
	return compressedData_.getBuffer();
}

uint64 ZipOutputStream::getCurrentSeekPos()
{	
	uint64 result = 0;

	return result;
}


uint64 ZipOutputStream::write( const unsigned char* bytesToWrite, uint64 sizeOfBytes )
{	
	uint64 result = 0;

	
	const unsigned char* start = bytesToWrite;
	uLongf bytesCompressed = zipBufferSize_ * 2;//compressBound( zipBufferSize_ );
	std::vector<unsigned char> zipBytes;
	zipBytes.resize(bytesCompressed,0);

	int srcLen = zipBufferSize_;
	if ( sizeOfBytes < srcLen ) {
		srcLen = sizeOfBytes;
	}

	while ( (start - bytesToWrite) < sizeOfBytes ) {
		bytesCompressed = zipBytes.size();
		

		int zres = compress( &zipBytes[0], &bytesCompressed, 
							(const Bytef*)start, srcLen );

		if ( Z_OK == zres ) {
			result += compressedData_.write( &zipBytes[0], bytesCompressed );
			if ( NULL != outStream_ ) {
				outStream_->write( &zipBytes[0], bytesCompressed );
			}
		}

		start += srcLen;
		srcLen = minVal<int>( zipBufferSize_, (sizeOfBytes - (start - bytesToWrite)) );
	}

	return result;
}



