//MemoryStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;



MemoryStream::MemoryStream()
{
	this->init();
}

MemoryStream::MemoryStream( OutputStream* outStream )
{
	if ( NULL != outStream ){
		this->init();
		this->outputStream_ = outStream;
	}
	//else throw exception ?
}

MemoryStream::MemoryStream( InputStream* inStream )
{
	if ( NULL != inStream ){
		this->init();
		this->inputStream_ = inStream;
	}
}

MemoryStream::~MemoryStream()
{

}

void MemoryStream::init()
{
	this->inputStream_ = NULL;
	this->outputStream_ = NULL;
	this->size_ = 0;
	currentSeekPos_ = 0;
}

void MemoryStream::seek(const unsigned long& offset, const SeekType& offsetFrom)
{
	switch ( offsetFrom ) {
		case stSeekFromStart: {
			stream_.setSeekPos( offset );
		}
		break;

		case stSeekFromEnd: {
			stream_.setSeekPos( stream_.getSize() - offset );
		}
		break;

		case stSeekFromRelative: {
			stream_.setSeekPos( stream_.getSeekPos() + offset );
		}
		break;
	}
}

unsigned long MemoryStream::getSize()
{
	return size_;
}

void MemoryStream::write( Persistable* persistableObject )
{
	if ( NULL != this->outputStream_ ){
		outputStream_->write( persistableObject );
	}
	else {
		persistableObject->saveToStream( this );
	}
}

unsigned long MemoryStream::write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes )
{
	unsigned long result = 0;

	if ( NULL != this->outputStream_ ){
		result = outputStream_->write( bytesToWrite, sizeOfBytes );
	}
	else {
		result = this->stream_.write( bytesToWrite, sizeOfBytes );
	}
	size_ += result;

	currentSeekPos_ += result;

	return result;
}

unsigned long MemoryStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	unsigned long result = 0;
	if ( NULL != this->inputStream_ ){
		result = inputStream_->read( bytesToRead, sizeOfBytes );
	}
	else {
		result = this->stream_.read( bytesToRead, sizeOfBytes );// currentSeekPos_ );
	}
	currentSeekPos_ += result;

	return result;
}

ulong32 MemoryStream::getCurrentSeekPos()
{
	if ( NULL != inputStream_ ) {
		return inputStream_->getCurrentSeekPos();
	}
	else if ( NULL != outputStream_ ) {
		return outputStream_->getCurrentSeekPos();
	}
	return currentSeekPos_;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.13  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.2  2003/08/27 20:11:49  ddiego
*adjustments to how hte DataObject class work and copy/paste
*
*Revision 1.12.4.1  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.12  2003/05/17 20:37:24  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.14.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.14.1  2003/03/12 03:12:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.10  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.9  2002/02/28 05:08:34  ddiego
*added tests for remote objects, plus another subtle fix for BasicInputStream
*for seek positioning
*
*Revision 1.8  2002/02/28 01:07:23  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


