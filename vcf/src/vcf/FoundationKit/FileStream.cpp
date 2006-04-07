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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2005/11/27 23:55:45  ddiego
*more osx updates.
*
*Revision 1.2.6.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.21.4.1  2004/04/12 19:33:13  ddiego
*fixed throw exception bug
*
*Revision 1.21  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.20.2.3  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.20.2.2  2003/08/11 19:41:15  marcelloptr
*bugfix [786946] FileOutputStream always erases the file when it opens it
*
*Revision 1.20.2.1  2003/08/11 19:07:05  marcelloptr
*bug 786924 - FileInputStream access fixed
*
*Revision 1.20  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.19.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.19  2003/05/17 20:37:24  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.18.2.2  2003/03/23 04:06:34  marcelloptr
*minor fixes
*
*Revision 1.18.2.1  2003/03/12 03:12:10  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.18  2003/02/26 04:30:47  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.17.2.1  2002/12/27 23:04:47  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.17  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.16.8.1  2002/10/04 05:02:54  ddiego
*added beggining support for add new classes. Basic GUI is now in place.
*Also preliminary support for class templates and class wizards
*some documentation done on the format for the XML based class template
*
*Revision 1.16  2002/05/28 03:03:15  ddiego
*added another test: FileStreaming to test out the FileStream class in
*linux. Added some changes to the LinuxFileStream class. Also added the
*LinuxLibraryPeer so the Library class now works in linux.
*
*Revision 1.15  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.14  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.13  2002/02/28 01:07:23  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.12  2002/01/28 02:09:03  cesarmello
*Linux file peer
*
*Revision 1.11  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


