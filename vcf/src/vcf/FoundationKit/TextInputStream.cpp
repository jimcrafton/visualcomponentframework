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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2.6.1  2005/09/08 03:16:58  ddiego
*fix for BOM marker in input stream handling and xml parser.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.9  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.8  2004/06/28 20:04:11  marcelloptr
*fixed readLine so it reads cr/lf but it doesn't include it in the string
*
*Revision 1.1.2.6  2004/06/27 17:59:52  ddiego
*fixed an off-by-one style error in the textInputStream::readLine() method
*

*Revision 1.1.2.5.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.5  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.11  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.1  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.10  2003/05/17 20:37:25  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.14.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.14.1  2003/03/12 03:12:16  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.8  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/02/28 01:07:23  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


