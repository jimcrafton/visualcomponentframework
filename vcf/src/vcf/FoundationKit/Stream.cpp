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

void InputStream::read( long& val )
{
	read( (unsigned char*)&val, sizeof(val) );
}

void InputStream::read( int& val )
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
	const ulong32 BUFFER_SIZE = 4096;
	AnsiString tmpStr;

	val = "";
	ulong32 size = getSize();

	ulong32 seekPos = getCurrentSeekPos();

	ulong32 totalBytesRead = 0;
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
	unsigned long bufferRead = minVal<ulong32>( BUFFER_SIZE * sizeof(char), size-seekPos );

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
					tmpStr.append( start, sz );
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

					val.append( (UnicodeString::UniChar*)start, (tmp - start) / sizeof(UnicodeString::UniChar) );

				}
				break;

				case UnicodeString::UTF32BigEndianBOM : //case UnicodeString::UTF16BigEndianBOM :
				case UnicodeString::UTF32LittleEndianBOM :  {
					//barf!!!
					throw RuntimeException( MAKE_ERROR_MSG_2("Unable to handle this kind of Unicode BOM marked text!") );
				}
				break;

				default : {
					tmpStr.append( start, sz );
				}
				break;
			}
		}
		else {

			if ( BOM16Str ) {				
				val.append( (UnicodeString::UniChar*)start, tmp - start );
			}
			else {
				tmpStr.append( start, tmp - start );
			}
		}

		if ( !done ) {
			bufferRead = VCF::minVal<ulong32>( BUFFER_SIZE * sizeof(char), size );
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
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const long& val )
{
	write( (const unsigned char*)&val, sizeof(val) );
}

void OutputStream::write( const int& val )
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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.6  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.2.6.5  2005/11/10 00:04:23  obirsoy
*changes required for gcc under Linux.
*
*Revision 1.2.6.4  2005/11/02 04:38:23  obirsoy
*changes required for vc80 support.
*
*Revision 1.2.6.3  2005/10/07 19:31:53  ddiego
*merged patch 1315995 and 1315991 into dev repos.
*
*Revision 1.2.6.2  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2.6.1  2005/09/08 03:16:58  ddiego
*fix for BOM marker in input stream handling and xml parser.
*
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


