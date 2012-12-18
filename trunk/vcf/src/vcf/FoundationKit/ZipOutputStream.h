#ifndef _VCF_ZIPOUTPUTSTREAM_H__
#define _VCF_ZIPOUTPUTSTREAM_H__
//ZipOutputStream.h

/*
Copyright 2000-2321 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif
#include "thirdparty/common/ZLib/zlib.h"


namespace VCF {
	
	class ZipOutputStream : public OutputStream {
	public:

		enum {
			DataSize = 256
		};

		ZipOutputStream();
		ZipOutputStream( OutputStream* outStream );

		virtual ~ZipOutputStream();

		virtual void seek(const uint64& offset, const SeekType& offsetFrom);

		virtual uint64 getSize();

		virtual uchar* getBuffer();

		virtual uint64 getCurrentSeekPos();

		virtual uint64 write( const unsigned char* bytesToRead, uint64 sizeOfBytes );
		
		CharMemStream<DataSize> compressedData_;
		OutputStream* outStream_;

		void setZipeBufferSize( const uint32& val ) {
			zipBufferSize_ = val;
		}

		uint32 getZipeBufferSize() {
			return zipBufferSize_;
		}

	protected:
		uint32 zipBufferSize_;
	};


};

#endif //_VCF_ZIPOUTPUTSTREAM_H__