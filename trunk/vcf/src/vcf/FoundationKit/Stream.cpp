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
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( long& val )
{
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( int& val )
{
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( bool& val )
{
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( char& val )
{
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( float& val )
{
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( double& val )
{
	read( (char*)&val, sizeof(val) );
}

void InputStream::read( String& val )
{
	const unsigned long BUFFER_SIZE = 4096;
	AnsiString tmpStr;

	val = "";
	unsigned long size = getSize();

	ulong32 seekPos = getCurrentSeekPos();

	/*
	JC
	WARNING!!!
	We are treating the stream as if it just had ASCII bytes - this may not be right
	*/

	char buffer[BUFFER_SIZE];
	unsigned long bufferRead = minVal<ulong32>( BUFFER_SIZE * sizeof(char), size-seekPos );

	read( (char*) buffer, bufferRead );

	char* tmp = buffer;
	char* start = tmp;
	size -= bufferRead;
	bool done = false;
	while ( false == done ){
		while ( bufferRead > 0 ) {
			if ( *tmp == '\0' ) {
				done = true;
				break;
			}
			tmp ++;
			bufferRead --;
		}

		done = (done || (size == 0));

		tmpStr.append( start, tmp - start );

		if ( false == done ) {
			bufferRead = VCF::minVal<ulong32>( BUFFER_SIZE * sizeof(char), size );
			read( buffer, bufferRead );
			tmp = buffer;
			start = tmp;
			size -= bufferRead;
		}
	}


	val = tmpStr;

	//the +1 is to take the null char (0) into account
	seek( seekPos + val.size() + 1, stSeekFromStart );
}


InputStream& InputStream::operator>>( short& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( long& val ){
	read( val );
	return *this;
}

InputStream& InputStream::operator>>( int& val ){
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

OutputStream& OutputStream::operator<<( const long& val ){
	write( val );
	return *this;
}

OutputStream& OutputStream::operator<<( const int& val ){
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
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const long& val )
{
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const int& val )
{
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const bool& val )
{
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const char& val )
{
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const float& val )
{
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const double& val )
{
	write( (char*)&val, sizeof(val) );
}

void OutputStream::write( const String& val )
{
	write( val.ansi_c_str(), val.size() );
	/**
	JC
	WARNING - we are treating writes to the stream as if it were Ascii - this
	will lose precision!!!
	*/
	char c = 0;
	write( &c, sizeof(c) );
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.20.8.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.20  2003/05/17 20:37:25  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.19.16.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.19.16.1  2003/03/12 03:12:15  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.19  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.18.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.18  2002/02/28 01:07:23  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.17  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.16  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


