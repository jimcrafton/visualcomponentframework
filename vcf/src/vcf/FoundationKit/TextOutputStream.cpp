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

void TextOutputStream::seek(const unsigned long& offset, const SeekType& offsetFrom )
{
	if ( NULL != outStream_ ){
		outStream_->seek( offset, offsetFrom );
	}
}

unsigned long TextOutputStream::getSize()
{
	unsigned long result = 0;
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

void TextOutputStream::write( const char* bytesToRead, unsigned long sizeOfBytes )
{
	textBuffer_.append( bytesToRead, sizeOfBytes );

	if ( NULL != this->outStream_ ){
		outStream_->write( bytesToRead, sizeOfBytes );
	}
}

void TextOutputStream::write( const short& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, NUMBER_TXT_SIZE );
	sprintf( tmpText, SHORT_STR_CONVERSION, val );
	this->write( tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const long& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, NUMBER_TXT_SIZE );
	sprintf( tmpText, LONG_STR_CONVERSION, (int)val );
	this->write( tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const int& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, NUMBER_TXT_SIZE );
	sprintf( tmpText, INT_STR_CONVERSION, val );
	this->write( tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const bool& val )
{
	char* tmpText = (char*)(val ? BOOL_STR_CONVERSION_TRUE : BOOL_STR_CONVERSION_FALSE);
	this->write( tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const float& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, NUMBER_TXT_SIZE );
	sprintf( tmpText, FLOAT_STR_CONVERSION, val );
	this->write( tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const double& val )
{
	char tmpText[NUMBER_TXT_SIZE];
	memset( tmpText, 0, NUMBER_TXT_SIZE );
	sprintf( tmpText, DOUBLE_STR_CONVERSION, val );
	this->write( tmpText, strlen(tmpText) );
}

void TextOutputStream::write( const String& val )
{
	String tmp = val + "\n";
	//int size = tmp.size();
	//char* buf = new char[size];
	//memset(buf, 0, size );
	//val.copy( buf, size-1 );
	/**
	WARNING!!!!!
	We are converting down to a ascii here. Is this the right thing to do????
	*/

	AnsiString tmp2 = tmp;
	write( tmp2.c_str(), tmp2.size() );

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

ulong32 TextOutputStream::getCurrentSeekPos()
{
	if ( NULL != outStream_ ) {
		return outStream_->getCurrentSeekPos();
	}
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.13.4.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.13  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.1  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.12  2003/05/17 20:37:25  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.14.3  2003/05/15 03:01:02  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.11.14.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.14.1  2003/03/12 03:12:16  ddiego
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
*Revision 1.9  2002/02/28 01:07:23  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


