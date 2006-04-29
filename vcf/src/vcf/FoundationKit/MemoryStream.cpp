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
$Id$
*/
