//BasicInputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

BasicInputStream::BasicInputStream()
{
	init();
}

BasicInputStream::BasicInputStream( const String& textBuffer )
{
	init();
	/**
	JC
	WARNING !!!!
	We are treating this like ascii strings!!!
	*/
	inStream_.write( (const unsigned char*)textBuffer.ansi_c_str(), textBuffer.size() );
	inStream_.setSeekPos( 0 );
	totalStreamSize_ = textBuffer.size();
}

BasicInputStream::BasicInputStream( const char* dataBuffer, const unsigned long& dataBufferSize )
{
	init();
	inStream_.write( (const unsigned char*)dataBuffer, dataBufferSize );
	inStream_.setSeekPos( 0 );
	totalStreamSize_ = dataBufferSize;
}

BasicInputStream::BasicInputStream( InputStream* inStream )
{
	init();
	inputStream_ = inStream;
}


void BasicInputStream::init()
{
	inputStream_ = NULL;
	totalStreamSize_ = 0;
}

BasicInputStream::~BasicInputStream()
{

}

void BasicInputStream::seek(const unsigned long& offset, const SeekType& offsetFrom)
{
	if ( NULL != inputStream_ ) {
		inputStream_->seek( offset, offsetFrom );
	}

	switch ( offsetFrom ) {
		case stSeekFromStart: {
			inStream_.setSeekPos( offset );
		}
		break;

		case stSeekFromEnd: {
			inStream_.setSeekPos( inStream_.getSize() - offset );
		}
		break;

		case stSeekFromRelative: {
			inStream_.setSeekPos( inStream_.getSeekPos() + offset );
		}
		break;
	}
}

unsigned long BasicInputStream::getSize()
{
	return inStream_.getSize();
}

char* BasicInputStream::getBuffer()
{
	return inStream_.getBuffer();
}

unsigned long BasicInputStream::read( unsigned char* bytesToRead, unsigned long sizeOfBytes )
{
	unsigned long result = 0;
	if ( NULL != inputStream_ ){
		result = inputStream_->read( bytesToRead, sizeOfBytes );
		inStream_.write( bytesToRead, sizeOfBytes );
	}
	else {
		result = inStream_.read( bytesToRead, sizeOfBytes );
	}

	return result;
}

ulong32 BasicInputStream::getCurrentSeekPos()
{
	if ( NULL != inputStream_ ) {
		return inputStream_->getCurrentSeekPos();
	}
	return inStream_.getSeekPos();
}

bool BasicInputStream::isEOS()
{
	if ( NULL != inputStream_ ) {
		return inputStream_->getCurrentSeekPos() == (inputStream_->getSize()-1);
	}
	return inStream_.getSeekPos() == (totalStreamSize_-1);
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.10  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.2  2003/08/27 20:11:49  ddiego
*adjustments to how hte DataObject class work and copy/paste
*
*Revision 1.9.4.1  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.9  2003/05/17 20:37:23  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.16.1  2003/03/12 03:12:08  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/02/28 05:08:34  ddiego
*added tests for remote objects, plus another subtle fix for BasicInputStream
*for seek positioning
*
*Revision 1.6  2002/02/28 01:07:23  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


