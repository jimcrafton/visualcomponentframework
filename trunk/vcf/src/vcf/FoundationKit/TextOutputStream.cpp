//TextOutputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

#define NUMBER_TXT_SIZE		25


TextOutputStream::TextOutputStream( OutputStream* outStream )
{
	this->init();
	outStream_ = outStream;
}

TextOutputStream::TextOutputStream()
{
	this->init();
}

TextOutputStream::~TextOutputStream()
{

}

void TextOutputStream::init()
{
	size_ = 0;
	outStream_ = NULL;
}

void TextOutputStream::seek(const uint32& offset, const SeekType& offsetFrom )
{
	if ( NULL != outStream_ ){
		outStream_->seek( offset, offsetFrom );
	}
}

uint32 TextOutputStream::getSize()
{
	uint32 result = 0;
	if ( NULL != outStream_ ){
		result = outStream_->getSize();
	}
	else {
		result = this->textBuffer_.size();
	}
	return result;
}

char* TextOutputStream::getBuffer()
{
	char* buffer = NULL;
	if ( NULL != outStream_ ){
		buffer = outStream_->getBuffer();
	}
	return buffer;
}

uint32 TextOutputStream::write( const unsigned char* bytesToRead, uint32 sizeOfBytes )
{
	uint32 result = 0;

	textBuffer_.append( (const char*)bytesToRead, sizeOfBytes );

	if ( NULL != this->outStream_ ){
		result = outStream_->write( bytesToRead, sizeOfBytes );
	}

	return result;
}

void TextOutputStream::write( const short& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, SHORT_STR_CONVERSION, val );
	this->write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const long& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, LONG_STR_CONVERSION, (int)val );
	this->write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const int& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, INT_STR_CONVERSION, val );
	this->write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const bool& val )
{
	char* tmpText = (char*)(val ? BOOL_STR_CONVERSION_TRUE : BOOL_STR_CONVERSION_FALSE);
	this->write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const float& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, FLOAT_STR_CONVERSION, val );
	this->write( (const unsigned char*)tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const double& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, sizeof(tmpText) );
	sprintf( tmpText, DOUBLE_STR_CONVERSION, val );
	this->write( (const unsigned char*)tmpText, strlen(tmpText) );
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
	return this->textBuffer_;
}

String TextOutputStream::toString()
{
	return textBuffer_;
}

uint32 TextOutputStream::getCurrentSeekPos()
{
	if ( NULL != outStream_ ) {
		return outStream_->getCurrentSeekPos();
	}
	return 0;
}


/**
$Id$
*/
