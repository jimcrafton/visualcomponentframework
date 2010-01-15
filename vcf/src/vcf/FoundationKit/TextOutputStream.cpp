//TextOutputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

namespace VCF {

#define NUMBER_TXT_SIZE		25


TextOutputStream::TextOutputStream( OutputStream* outStream )
{
	init();
	outStream_ = outStream;
}

TextOutputStream::TextOutputStream()
{
	init();
}

TextOutputStream::~TextOutputStream()
{

}

void TextOutputStream::init()
{
	size_ = 0;
	outStream_ = NULL;
	seekPos_ = 0;
}

void TextOutputStream::seek(const uint64& offset, const SeekType& offsetFrom )
{
	if ( NULL != outStream_ ){
		outStream_->seek( offset, offsetFrom );
	}
	else {
		switch ( offsetFrom ) {
			case stSeekFromStart : {
				seekPos_ = offset;
			}
			break;

			case stSeekFromEnd : {
				seekPos_ = (size_ > offset) ? size_ - offset : 0;
			}
			break;

			case stSeekForwards : {
				seekPos_ += offset;
			}
			break;

			case stSeekBackwards : {
				seekPos_ -= offset;
			}
			break;
		}		
	}
}

uint64 TextOutputStream::getSize()
{
	uint64 result = 0;
	if ( NULL != outStream_ ){
		result = outStream_->getSize();
	}
	else {
		result = size_;
	}
	return result;
}

uchar* TextOutputStream::getBuffer()
{
	uchar* buffer = NULL;
	if ( NULL != outStream_ ){
		buffer = outStream_->getBuffer();
	}
	return buffer;
}

uint64 TextOutputStream::write( const unsigned char* bytesToWrite, uint64 sizeOfBytes )
{
	uint64 result = 0;	

	if ( NULL != outStream_ ){
		result = outStream_->write( bytesToWrite, sizeOfBytes );
	}
	else {		
		if ( textBuffer_.size() < seekPos_ ) {
//			textBuffer_.reserve( seekPos_ );
		}
		textBuffer_.insert( seekPos_, (const char*)bytesToWrite, sizeOfBytes );

		result = sizeOfBytes;		
		seekPos_ += result;
		if ( seekPos_ > size_ ) {
			size_ += result;
		}
	}	

	return result;
}

void TextOutputStream::write( const short& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, SHORT_STR_CONVERSION, val );
	write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const long& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, LONG_STR_CONVERSION, val );
	write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const int& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, INT_STR_CONVERSION, val );
	write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const bool& val )
{
	char* tmpText = (char*)(val ? BOOL_STR_CONVERSION_TRUE : BOOL_STR_CONVERSION_FALSE);
	write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const float& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, FLOAT_STR_CONVERSION, val );
	write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const double& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, DOUBLE_STR_CONVERSION, val );
	write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const String& val )
{
	String tmp = val + "\n";
	//int size = tmp.size();
	//char* buf = new char[size];
	//memset(buf, 0, size*sizeof(char) );
	//val.copy( buf, size-1 );
	/**
	WARNING!!!!!
	We are converting down to a ascii here. Is this the right thing to do????
	*/

	AnsiString tmp2 = tmp;
	write( (const unsigned char*)tmp2.c_str(), tmp2.size() );

	//delete [] buf;
}


void TextOutputStream::writeLine( const String& line )
{
	*((OutputStream*)this) << line;
	*this << '\n';
}

String TextOutputStream::getTextBuffer()
{
	return textBuffer_;
}

String TextOutputStream::toString() const 
{
	return textBuffer_;
}

uint64 TextOutputStream::getCurrentSeekPos()
{
	if ( NULL != outStream_ ) {
		return outStream_->getCurrentSeekPos();
	}
	return 0;
}


};


/**
$Id$
*/
