//TextInputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

TextInputStream::TextInputStream( InputStream* inStream )
{
	this->init();
	this->inStream_ = inStream;
	if ( NULL != inStream_ ){
		this->size_ = this->inStream_->getSize();
	}
}

TextInputStream::~TextInputStream()
{

}

void TextInputStream::seek(const unsigned long& offset, const SeekType& offsetFrom )
{
	if ( NULL != inStream_ ){
		inStream_->seek( offset, offsetFrom );
	}
}

unsigned long TextInputStream::getSize()
{
	return size_;
}

char* TextInputStream::getBuffer()
{
	return NULL;
}

unsigned long TextInputStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	unsigned long result = 0;
	if ( NULL != inStream_ ){
		result = inStream_->read( bytesToRead, sizeOfBytes );
	}

	return result;
}

void TextInputStream::read( short& val )
{
	if ( NULL != this->inStream_ ){
		String tmp = readTillWhiteSpace();
		val = StringUtils::fromStringAsShort( tmp );
	}
}

void TextInputStream::read( long& val )
{
	if ( NULL != this->inStream_ ){
		String tmp = readTillWhiteSpace();
		val = (long) StringUtils::fromStringAsInt( tmp );
	}
}

void TextInputStream::read( int& val )
{
	if ( NULL != this->inStream_ ){
		String tmp = readTillWhiteSpace();
		val = StringUtils::fromStringAsInt( tmp );
	}
}

void TextInputStream::read( bool& val )
{
	if ( NULL != this->inStream_ ){
		String tmp = readTillWhiteSpace();
		val = StringUtils::fromStringAsBool( tmp );
	}
}

void TextInputStream::read( float& val )
{
	if ( NULL != this->inStream_ ){
		String tmp = readTillWhiteSpace();
		val = StringUtils::fromStringAsFloat( tmp );
	}
}

void TextInputStream::read( double& val )
{
	if ( NULL != this->inStream_ ){
		String tmp = readTillWhiteSpace();
		val = StringUtils::fromStringAsDouble( tmp );
	}
}

void TextInputStream::read( String& val )
{
	readLine( val );
}


void TextInputStream::init()
{
	this->inStream_ = NULL;
	this->size_ = 0;
	totCharRead_ = 0;
}

void TextInputStream::readLine( String& line )
{
	if ( NULL != this->inStream_ )
	{
		char c = '\0';
		inStream_->read( (unsigned char*)&c, sizeof(c) );
		totCharRead_++;

		while ( (c != '\n' && c!= '\r') && (totCharRead_ <= size_) )
		{
			line += c;
			inStream_->read( (unsigned char*)&c, sizeof(c) );
			totCharRead_++;
		}

		// commented: we don't want the cr/lf in the string
		// line += c;

		//last character!
		if ( c == '\r' && (totCharRead_ <= size_) ) {
			inStream_->read( (unsigned char*)&c, sizeof(c) );
			totCharRead_++;
			if ( c != '\n' ) {
				//back up 1
				totCharRead_--;
				inStream_->seek( inStream_->getCurrentSeekPos() - sizeof(c), stSeekFromStart );
			}
		}
	}
}

String TextInputStream::readTillWhiteSpace()
{
	String result = "";
	if ( NULL != this->inStream_ ){
		char c = '\0';
		inStream_->read( (unsigned char*)&c, sizeof(c) );
		totCharRead_++;

		while ( ((c == ' ') || (c == '\0')) && (totCharRead_ < size_) ){
			inStream_->read( (unsigned char*)&c, sizeof(c) );
			totCharRead_++;
		}
		//get all the nonwhitespace characters
		while ( (c != ' ') && (c != '\0')  && (totCharRead_ < size_) ){
			result += c;
			inStream_->read( (unsigned char*)&c, sizeof(c) );
			totCharRead_++;
		}
	}
	return result;
}

String TextInputStream::readTillTokenPair( const char& token )
{
	String result = "";
	if ( NULL != this->inStream_ ){
		char c = '\0';
		inStream_->read( (unsigned char*)&c, sizeof(c) );
		totCharRead_++;

		while ( (c != token) && (c != ' ') && (totCharRead_ < size_) ){
			inStream_->read( (unsigned char*)&c, sizeof(c) );
			totCharRead_++;
		}

		while ( (c != token) && (totCharRead_ < size_) ){
			result += c;
			inStream_->read( (unsigned char*)&c, sizeof(c) );
			totCharRead_++;
		}
	}
	return result;
}

ulong32 TextInputStream::getCurrentSeekPos()
{
	if ( NULL != inStream_ ) {
		return inStream_->getCurrentSeekPos();
	}
	return 0;
}


/**
$Id$
*/
