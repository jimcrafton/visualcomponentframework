#ifndef _VCF_MEMSTREAMUTILS_H__
#define _VCF_MEMSTREAMUTILS_H__
//MemStreamUtils.h

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
\class GenericMemoryBuffer MemStreamUtils.h "vcf/FoundationKit/MemStreamUtils.h"
GenericMemoryBuffer
@author  Jim Crafton
@date 3/7/2000
@version 1.0
*/

template <typename DATA_TYPE, int allocationSize = 65536>
class GenericMemoryBuffer {
public:
	enum {
		AllocationSize = allocationSize
	};

	GenericMemoryBuffer() :
			currentBuffer_(NULL),
			currentAllocationSize_(0),
			seekPos_(0),
			currentSize_(0)
			{}



	~GenericMemoryBuffer(){
		delete [] currentBuffer_;
		currentBuffer_ = NULL;
	}

	inline DATA_TYPE* getBuffer()	{
		return currentBuffer_;
	}

	inline uint64 getSize()  {
		return currentSize_;
	}

	inline uint64 write( const unsigned char* buffer, const uint64& sizeOfBuffer ) {
		if ( currentAllocationSize_ < (seekPos_ + sizeOfBuffer) ) {
			allocate( (seekPos_ + sizeOfBuffer) - currentAllocationSize_ );
		}

		char* tmp = (char*)currentBuffer_;
		tmp += seekPos_;

		memcpy( tmp, buffer, sizeOfBuffer );

		seekPos_ += sizeOfBuffer;

		if ( seekPos_ > currentSize_ ) {
			currentSize_ += sizeOfBuffer;
		}

		return sizeOfBuffer;
	}

	inline uint64 read( unsigned char* buffer, const uint64& sizeOfBuffer ) {
		if ( seekPos_ >= currentAllocationSize_ ) {
			throw NoFreeMemException("No longer have enough memory in this buffer to read from.");
		}

		unsigned char* tmp = currentBuffer_;
		tmp += seekPos_;

		uint64 sz = minVal<uint64>( sizeOfBuffer, currentSize_ - seekPos_ );
		memcpy( buffer, tmp, (size_t)sz );

		seekPos_ += sz;

		return sz;
	}

	inline void setSeekPos( uint64 pos ) {
		seekPos_ = pos;
	}

	inline uint64 getSeekPos() {
		return seekPos_;
	}


	inline void clear() {

		currentAllocationSize_ = 0;
		delete [] currentBuffer_;
		currentBuffer_ = NULL;
		allocate(AllocationSize);
	}
protected:
	inline void allocate( uint64 sizeToAllocate ) {
		uint64 oldSize = currentAllocationSize_;

		//sizeToAllocate = (sizeToAllocate - oldSize);

		currentAllocationSize_ += ((sizeToAllocate/AllocationSize) * AllocationSize) +
			( (sizeToAllocate % AllocationSize) ? AllocationSize : 0 );

		DATA_TYPE* tmp = new DATA_TYPE[currentAllocationSize_];

		if ( NULL == tmp ) {
			throw NoFreeMemException();
		}

		if ( NULL != currentBuffer_ ) {
			//copy over the old bits
			memcpy( tmp, currentBuffer_, oldSize );
			delete [] currentBuffer_;
		}

		currentBuffer_ = tmp;
	}
private:
	DATA_TYPE* currentBuffer_;
	uint64 currentAllocationSize_;
	uint64 seekPos_;
	uint64 currentSize_;
};




/**
\class CharMemStream MemStreamUtils.h "vcf/FoundationKit/MemStreamUtils.h"
*/
template <int allocationSize = 65536>
class FOUNDATIONKIT_API CharMemStream : public GenericMemoryBuffer<uchar,allocationSize> {
public:
	CharMemStream() :
		GenericMemoryBuffer<uchar,allocationSize> () {}

	~CharMemStream(){};

};

}; //end of namespace VCF


#endif // _VCF_MEMSTREAMUTILS_H__

/**
$Id$
*/
