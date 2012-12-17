#ifndef _VCF_ZIPINPUTSTREAM_H__
#define _VCF_ZIPINPUTSTREAM_H__
//ZipInputStream.h

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
	
	class ZipInputStream : public InputStream {
	public:
		ZipInputStream( InputStream* inStream );

		virtual ~ZipInputStream();

		virtual void seek(const uint64& offset, const SeekType& offsetFrom);

		virtual uint64 getSize();

		virtual uchar* getBuffer();

		virtual uint64 getCurrentSeekPos() ;

		virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

		virtual bool isEOS();
		
		InputStream* inputStream_;
		z_stream zstream_;
		CharMemStream<> uncompressedData_;
		unsigned char zipTmpData_[256];
		uint64 seekPos_;

	};
};

#endif //_VCF_ZIPINPUTSTREAM_H__