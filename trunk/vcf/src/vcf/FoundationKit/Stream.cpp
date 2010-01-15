//Stream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


void InputStream::read( Persistable* persistableObject ){
	if ( NULL != persistableObject ){
		persistableObject->loadFromStream( this );
	}
}

void InputStream::read( short& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( unsigned short& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( long& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( unsigned long& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( int& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( unsigned int& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( bool& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( char& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( unsigned char& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( int64& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( uint64& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( float& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( double& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( String& val )
{
	const uint32 BUFFER_SIZE = 4096;
	AnsiString tmpStr;

	val = "";
	uint64 size = getSize();

	uint64 seekPos = getCurrentSeekPos();

	uint64 totalBytesRead = 0;
	/*
	JC
	WARNING!!!
	We are treating the stream as if it just had ASCII bytes - this may not be right
	*/

	/*
	Current STATUS:
	We are now picking up the BOM marker.
	We *only* handle the case where it's UTF16 little endian - 
	the others we punt!
	If this get's called repeatedly, we will no longer be treating the
	string as a unicode string which will cause a problem
	because we will intepret the 2 byte code points incorrectly.
	We need a way to know if the stream we are reading is actually 
	a UTF16 stream
	*/

	char buffer[BUFFER_SIZE];
	uint64 bufferRead = minVal<uint64>( BUFFER_SIZE * sizeof(char), size-seekPos );

	read( (unsigned char*) buffer, bufferRead );

	totalBytesRead += bufferRead;

	bool BOM16Str = false;


	char* tmp = buffer;
	char* start = tmp;
	size -= bufferRead;
	bool done = false;
	while ( !done ){

		while ( bufferRead > 0 ) {
			if ( BOM16Str ) {
				if ( (tmp[0] == '\0') && (tmp[1] == '\0') ) {
					done = true;
					break;
				}
				tmp += sizeof(UnicodeString::UniChar);
				bufferRead --;
				if ( bufferRead != 0 ) {
					bufferRead --;
				}
			}
			else {
				if ( *tmp == '\0' ) {
					done = true;
					break;
				}
				tmp ++;
				bufferRead --;
			}
		}

		done = (done || (size == 0));

		if ( 0 == seekPos ) {		
			uint32 sz = tmp - start;

			//JC Nov 10, 2005
			//I removed the old ifdef here because I simply got rid of 
			//teh weird const char*& syntax, and made it simply
			//char*& this should fine now.
			int bom = UnicodeString::adjustForBOMMarker( start, sz );			
			
			switch ( bom ) {
				case UnicodeString::UTF8BOM : {
					tmpStr = tmpStr.append( start, sz );
				}
				break;

				case UnicodeString::UTF16LittleEndianBOM : {
					
					BOM16Str = true;
					if ( done && (sz < bufferRead) ) {
						done = false;
						while ( bufferRead > 0 ) {
							if ( (tmp[0] == '\0') && (tmp[1] == '\0') ) {
								done = true;
								break;
							}
							tmp += sizeof(UnicodeString::UniChar);
							bufferRead --;
							if ( bufferRead != 0 ) {
								bufferRead --;
							}
						}
						done = (done || (size == 0));
					}

					val = val.append( (UnicodeString::UniChar*)start, (tmp - start) / sizeof(UnicodeString::UniChar) );

				}
				break;

				case UnicodeString::UTF32BigEndianBOM : //case UnicodeString::UTF16BigEndianBOM :
				case UnicodeString::UTF32LittleEndianBOM :  {
					//barf!!!
					throw RuntimeException( MAKE_ERROR_MSG_2("Unable to handle this kind of Unicode BOM marked text!") );
				}
				break;

				default : {
					tmpStr = tmpStr.append( start, sz );
				}
				break;
			}
		}
		else {

			if ( BOM16Str ) {				
				val = val.append( (UnicodeString::UniChar*)start, tmp - start );
			}
			else {
				tmpStr = tmpStr.append( start, tmp - start );
			}
		}

		if ( !done ) {
			bufferRead = VCF::minVal<uint64>( BUFFER_SIZE * sizeof(char), size );
			read( (unsigned char*)buffer, bufferRead );
			tmp = buffer;
			start = tmp;
			size -= bufferRead;
			totalBytesRead += bufferRead;
		}
	}


	if ( !BOM16Str ) {
		val = tmpStr;
		seek( val.size() + 1, stSeekFromStart );	
	}
	else {
		//the +1 is to take the null char (0) into account
		seek( totalBytesRead + 1, stSeekFromStart );	
	}	
}


InputStream& InputStream::operator>>( short& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( unsigned short& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( long& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( unsigned long& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( int& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( unsigned int& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( bool& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( char& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( unsigned char& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( int64& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( uint64& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( float& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( double& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( String& val )
{
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( Persistable* val ){
	read( val );
	return *this;
}


void OutputStream::write( Persistable* persistableObject ){
	if ( NULL != persistableObject ){
		persistableObject->saveToStream( this );
	}
}

OutputStream& OutputStream::operator<<( const short& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const unsigned short& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const long& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const unsigned long& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const int& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const unsigned int& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const bool& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const char& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const unsigned char& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const int64& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const uint64& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const float& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const double& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const String& val )
{
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( Persistable* val ){
	write( val );
	return *this;
}

void OutputStream::write( const short& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const unsigned short& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const long& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const unsigned long& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const int& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const unsigned int& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const bool& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const char& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const unsigned char& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const int64& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const uint64& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const float& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const double& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const String& val )
{
	write( (const unsigned char*)val.ansi_c_str(), val.size() );
	/**
	JC
	WARNING - we are treating writes to the stream as if it were Ascii - this
	will lose precision!!!
	*/
	unsigned char c = 0;
	write( &c, sizeof(c) );
}


/**
$Id$
*/
