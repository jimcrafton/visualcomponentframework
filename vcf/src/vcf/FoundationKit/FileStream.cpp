//FileStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


FileStreamBase::FileStreamBase():	
	fsPeer_(NULL),
	access_(fsDontCare),
	currentSeekPos_(0)
{

}

FileStreamBase::~FileStreamBase()
{

}

void FileStreamBase::init()
{
	fsPeer_ = SystemToolkit::createFileStreamPeer( filename_, access_ );
	if ( NULL == fsPeer_ ) {
		throw NoPeerFoundException();
	}
}

void FileStreamBase::close()
{
	if ( NULL != fsPeer_ ) {
		delete fsPeer_;
		fsPeer_ = NULL;
	}
}

void FileStreamBase::open( const String& filename, FileStreamAccessType accessType )
{
	filename_ = filename;
	access_ = accessType;
	if ( NULL != fsPeer_ ){
		delete fsPeer_;
	}
	fsPeer_ = NULL;

	init();
}


FileInputStream::FileInputStream( const String& filename )
{
	filename_ = filename;
	access_ = fsRead;
	try {
		init();
	}
	catch ( BasicException& ){
		throw;
	}
}


FileInputStream::FileInputStream( File* file )
{
	filename_ = file->getName();
	access_ = fsRead;
	try {
		fsPeer_ = SystemToolkit::createFileStreamPeer( file );
		if ( NULL == fsPeer_ ) {
			throw NoPeerFoundException();
		}
	}
	catch ( BasicException& ){
		throw;
	}
}


FileInputStream::~FileInputStream()
{
	close();
}

void FileInputStream::open( const String& filename )
{
	FileStreamBase::open( filename, fsRead );
}


void FileInputStream::seek(const unsigned long& offset, const SeekType& offsetFrom )
{
	fsPeer_->seek( offset, offsetFrom );

	switch ( offsetFrom ) {
		case stSeekFromStart: {
			currentSeekPos_ = offset;
		}
		break;

		case stSeekFromEnd: {
			currentSeekPos_ = fsPeer_->getSize() - offset;
		}
		break;

		case stSeekFromRelative: {
			currentSeekPos_ += offset;
		}
		break;
	}
}

unsigned long FileInputStream::getSize()
{
	return fsPeer_->getSize();
}

char* FileInputStream::getBuffer()
{
	return fsPeer_->getBuffer();
}

unsigned long FileInputStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	unsigned long result = fsPeer_->read( bytesToRead, sizeOfBytes );

	currentSeekPos_ += result;

	return result;
}


ulong32 FileInputStream::getCurrentSeekPos()
{
	return currentSeekPos_;
}






FileOutputStream::FileOutputStream( const String& filename, const bool & append/*=false*/ )
{
	filename_ = filename;
	if ( append ) {
		access_ = fsReadWrite;
	} else {
		access_ = fsWrite;
	}
	try {
		init();
	}
	catch ( BasicException& e ){
		throw e;
	}

	//else throw exception ?
}


FileOutputStream::FileOutputStream( File* file )
{
	filename_ = file->getName();

	try {
		fsPeer_ = SystemToolkit::createFileStreamPeer( file );
		if ( NULL == fsPeer_ ) {
			throw NoPeerFoundException();
		}
	}
	catch ( BasicException&  ){
		throw ;
	}
}

FileOutputStream::~FileOutputStream()
{
	close();
}



void FileOutputStream::open( const String& filename, const bool & append/*=false*/ )
{
	if ( append ) {
		FileStreamBase::open( filename, fsReadWrite );
	} else {
		FileStreamBase::open( filename, fsWrite );
	}
}


void FileOutputStream::seek(const unsigned long& offset, const SeekType& offsetFrom )
{
	if ( NULL == fsPeer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG_2(NO_PEER) );
	};

	fsPeer_->seek( offset, offsetFrom );

	switch ( offsetFrom ) {
		case stSeekFromStart: {
			currentSeekPos_ = offset;
		}
		break;

		case stSeekFromEnd: {
			currentSeekPos_ = fsPeer_->getSize() - offset;
		}
		break;

		case stSeekFromRelative: {
			currentSeekPos_ += offset;
		}
		break;
	}
}



unsigned long FileOutputStream::getSize()
{
	return fsPeer_->getSize();
}

char* FileOutputStream::getBuffer()
{
	return fsPeer_->getBuffer();
}

unsigned long FileOutputStream::write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes )
{
	unsigned long result = fsPeer_->write( bytesToWrite, sizeOfBytes );

	currentSeekPos_ += result;

	return result;
}


ulong32 FileOutputStream::getCurrentSeekPos()
{
	return currentSeekPos_;
}


/**
$Id$
*/
