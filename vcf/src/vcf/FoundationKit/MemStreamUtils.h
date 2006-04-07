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

template <class DATA_TYPE>
class GenericMemoryBuffer {
public:
	GenericMemoryBuffer( const ulong32 allocationSize = 65536) :
			allocationSize_(allocationSize),
			currentBuffer_(NULL),
			currentAllocationSize_(0),
			seekPos_(0),
			currentSize_(0)
			{}



	virtual ~GenericMemoryBuffer(){
		delete [] currentBuffer_;
		currentBuffer_ = NULL;
	}

	inline DATA_TYPE* getBuffer()	{
		return currentBuffer_;
	}

	inline ulong32 getSize()  {
		return currentSize_;
	}

	inline unsigned long write( const unsigned char* buffer, const ulong32& sizeOfBuffer ) {
		if ( currentAllocationSize_ < (seekPos_ + sizeOfBuffer) ) {
			allocate( sizeOfBuffer );
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

	inline unsigned long read( unsigned char* buffer, const ulong32& sizeOfBuffer ) {
		if ( currentAllocationSize_ < (seekPos_ + sizeOfBuffer) ) {
			throw NoFreeMemException("No longer have enough memory in this buffer to read from.");
		}

		char* tmp = (char*)currentBuffer_;
		tmp += seekPos_;

		memcpy( buffer, tmp, sizeOfBuffer );

		seekPos_ += sizeOfBuffer;

		return sizeOfBuffer;
	}

	inline void setSeekPos( ulong32 pos ) {
		seekPos_ = pos;
	}

	inline ulong32 getSeekPos() {
		return seekPos_;
	}


	inline void clear() {

		currentAllocationSize_ = 0;
		delete [] currentBuffer_;
		currentBuffer_ = NULL;
		allocate(allocationSize_);
	}
protected:
	inline void allocate( ulong32 sizeToAllocate ) {
		ulong32 oldSize = currentAllocationSize_;

		sizeToAllocate = (sizeToAllocate - oldSize);

		currentAllocationSize_ += ((sizeToAllocate/allocationSize_) * allocationSize_) +
			( (sizeToAllocate % allocationSize_) ? allocationSize_ : 0 );

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
	ulong32 allocationSize_;
	DATA_TYPE* currentBuffer_;
	ulong32 currentAllocationSize_;
	ulong32 seekPos_;
	ulong32 currentSize_;
};




/**
\class CharMemStream MemStreamUtils.h "vcf/FoundationKit/MemStreamUtils.h"
*/
class FOUNDATIONKIT_API CharMemStream : public GenericMemoryBuffer<char> {
public:
	CharMemStream( const ulong32& allocationSize = 65536 ) :
		GenericMemoryBuffer<char> ( allocationSize ) {
	}

	virtual ~CharMemStream(){};

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2.6.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.16.2.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.16  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.15.2.1  2004/02/21 03:27:07  ddiego
*updates for OSX porting
*
*Revision 1.15  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.4  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.14.4.3  2003/08/26 03:16:50  ddiego
*added a syntax fix cause VC6 is too stupid to compile code correctly.
*Thanks to Marcello for pointing it out.
*
*Revision 1.14.4.2  2003/08/26 01:20:23  marcelloptr
*removed inline keyword in Color.cpp in front of some ColorSpace memeber functions definitions
*
*Revision 1.14.4.1  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.14  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.16.1  2003/03/12 03:11:45  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.12  2002/02/28 05:08:34  ddiego
*added tests for remote objects, plus another subtle fix for BasicInputStream
*for seek positioning
*
*Revision 1.11  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_MEMSTREAMUTILS_H__


