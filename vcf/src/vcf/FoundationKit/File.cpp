//File.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


File::File( const String& fileName ):
	filePeer_(NULL),
	openAccess_(File::ofNone)
{	
	setName( fileName );
}

File::File( const String& fileName, ulong32 openFlags, ShareFlags shareFlags ):
	filePeer_(NULL),
	openAccess_(File::ofNone)
{
	setName( fileName );
	openWithRights( fileName, openFlags, shareFlags );	
}


File::~File()
{
	if ( NULL != filePeer_ ){
		delete filePeer_;
	}
	filePeer_ = NULL;
}

void File::setName( const String& fileName )
{
	// should we do this check ? maybe better not.
	//if ( fileName_ != fileName ) {
	//	return;
	//}

  // or just: fileName_ = fileName ?
	fileName_ = FilePath::transformToOSSpecific( fileName );

	if ( NULL == filePeer_ ) {
		filePeer_ = SystemToolkit::createFilePeer( this );
		if ( NULL == filePeer_ ) {
			throw NoPeerFoundException();
		}
	} 
	else {
		filePeer_->setFile( this );
	}

	resetStats();
}


String File::getOwner()
{
	// gets the owner of the file
	return owner_;
}

void File::updateStat( StatMask statMask/*=File::smStatNone*/ )
{
	filePeer_->updateStat( statMask );
}

void File::setFileAttributes( const File::FileAttributes fileAttributes )
{
	filePeer_->setFileAttributes( fileAttributes );
}



void File::setDateModified( const DateTime& dateModified )
{
	filePeer_->setDateModified( dateModified );
}

bool File::exists( const String& filename )
{
	return System::doesFileExist( filename );
}

void File::create( const String& newFileName, ulong32 openFlags )
{
	try {
		fileName_ = newFileName;
		filePeer_->create(openFlags);
	}
	catch ( ... ) {
		fileName_ = "";
		throw;
	}
}

DateTime File::getDateModified() 
{
	return filePeer_->getDateModified();
}

DateTime File::getDateCreation() 
{
	return filePeer_->getDateCreated();
}

DateTime File::getDateAccess() 
{
	return filePeer_->getDateAccessed();
}

VCF::ulong64 File::getSize()
{
	return filePeer_->getSize();
}

bool File::isExecutable()
{
	return filePeer_->isExecutable();
}

void File::remove()
{
	filePeer_->remove();
}

void File::copyTo( const String& copyFileName )
{
	filePeer_->copyTo( copyFileName );
}


void File::open()
{
	VCF_ASSERT( !fileName_.empty() );

	filePeer_->open(fileName_); 
}

void File::openWithFileName( const String& fileName )
{
	fileName_ = fileName;
	filePeer_->open( fileName );
	openAccess_ = File::ofStat;
}

void File::openWithRights( const String& fileName, ulong32 openFlags, ShareFlags shareFlags )
{
	fileName_ = fileName;
	filePeer_->open( fileName, openFlags, shareFlags );
	openAccess_ = openFlags;
}

void File::close()
{
	filePeer_->close();
}

FileInputStream* File::getInputStream()
{
	FileInputStream* result = NULL;

	if ( isReadable() ) {
		result = new FileInputStream( this );
		result->seek( 0, stSeekFromStart );
	}

	return result;
}

FileOutputStream* File::getOutputStream()
{
	FileOutputStream* result = NULL;

	if ( isWriteable() ) {
		result = new FileOutputStream( this );
		result->seek( 0, stSeekFromStart );
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/11 04:39:59  marcelloptr
*function inlined
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.10  2004/08/06 01:45:04  ddiego
*updated and added Marcellos DateTime changes.
*
*Revision 1.1.2.9  2004/08/03 23:04:38  marcelloptr
*completed implementation of updateTime
*
*Revision 1.1.2.8  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.7  2004/07/26 03:40:31  ddiego
*minor changes
*
*Revision 1.1.2.6  2004/07/24 01:40:42  ddiego
*committed changes requested by Marcello. Got rid of the remaining
*date time members on the File class - now the dat time function call the
*FilePeer directly each time. Also added 2 functions to DateTime to convert
*directly to UTC or Local time.
*
*Revision 1.1.2.5  2004/07/23 00:56:37  ddiego
*added the latest changes to the File and Directory finder classes.
*
*Revision 1.1.2.4  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.3  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.15  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.2.1  2003/08/13 19:01:43  marcelloptr
*made File::getName() const
*
*Revision 1.14  2003/08/09 02:56:46  ddiego
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
*Revision 1.13.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.13  2003/05/17 20:37:24  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.16.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.12.16.1  2003/03/12 03:12:09  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.11  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.10  2002/01/28 02:09:03  cesarmello
*Linux file peer
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


