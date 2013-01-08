//ZipInputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ZipInputStream.h"



using namespace VCF;



ZipInputStream::ZipInputStream( InputStream* inStream ):
	inputStream_(inStream),
	seekPos_(0),
	zipBufferSize_(256),
	zipTmpData_(NULL)
{
	memset(&zstream_,0,sizeof(zstream_));
	if ( Z_OK != inflateInit( &zstream_ ) ) {
		//throw exception!!!
	}
}

ZipInputStream::~ZipInputStream()
{
	inflateEnd( &zstream_ );
	if ( NULL != zipTmpData_ ) {
		delete [] zipTmpData_;
	}
}

void ZipInputStream::seek(const uint64& offset, const SeekType& offsetFrom)
{

}

uint64 ZipInputStream::getSize()
{
	 
	return inputStream_->getSize();
}

uchar* ZipInputStream::getBuffer()
{
	return uncompressedData_.getBuffer();
}

uint64 ZipInputStream::getCurrentSeekPos() 
{
	return seekPos_;
}

uint64 ZipInputStream::read( unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	uint64 result = 0;

	if ( sizeOfBytes + seekPos_ <= uncompressedData_.getSeekPos() ) {
		uint64 oldSeek = uncompressedData_.getSeekPos();
		uncompressedData_.setSeekPos( seekPos_ );

		result = uncompressedData_.read( bytesToRead, sizeOfBytes );
		seekPos_ += result;

		uncompressedData_.setSeekPos( oldSeek );
	}
	else {
		
		unsigned char* tmpBuf = new unsigned char[zipBufferSize_];
		memset(tmpBuf,0,zipBufferSize_);


		if ( NULL == zipTmpData_ ) {
			zipTmpData_ = new unsigned char[zipBufferSize_];
			memset(zipTmpData_,0,zipBufferSize_);
		}
		
		inflateInit( &zstream_ ) ;

		int res = 0;

		while ( result < sizeOfBytes ) {
			
			
			uint64 readIn = inputStream_->read( &zipTmpData_[0], zipBufferSize_ );

			if ( readIn == 0 ) {
				break;
			}
			zstream_.next_in = zipTmpData_;
			zstream_.avail_in = readIn;


			do {
				zstream_.avail_out = zipBufferSize_;
				zstream_.next_out = tmpBuf;

				res = inflate( &zstream_, 0 );
				


				VCF_ASSERT(res != Z_STREAM_ERROR);

				switch (res) {
					case Z_NEED_DICT: {
						res = Z_DATA_ERROR;     
					} //and fall through 

					case Z_DATA_ERROR:
					case Z_MEM_ERROR: {
						inflateEnd( &zstream_ );
						throw RuntimeException( "Error with zip stream, either a Z_DATA_ERROR or Z_MEM_ERROR occurred" );
						//out of while loop...
					}

					case Z_STREAM_END : {
						

						uint64 have = zipBufferSize_ - zstream_.avail_out;
						uncompressedData_.write( &tmpBuf[0], have );
						result +=  have;

						inflateEnd( &zstream_ );
						res = inflateInit( &zstream_ ) ;
						zstream_.avail_out = zstream_.avail_in > 0 ? 0:1;
					}
					break;

					default : { 
						uint64 have = zipBufferSize_ - zstream_.avail_out;
						uncompressedData_.write( &tmpBuf[0], have );
						result +=  have;
					} 
					break;
				}
				
			} while ( zstream_.avail_out == 0 );
		}


		inputStream_->seek( zstream_.total_in, stSeekBackwards );


		delete []tmpBuf;

		inflateEnd( &zstream_ );

		result = read( bytesToRead, sizeOfBytes );		
	}


	return result;
}

bool ZipInputStream::isEOS()
{
	bool result = true;
	return result;
}