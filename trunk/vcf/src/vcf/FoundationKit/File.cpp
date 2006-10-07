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

File::File( const String& fileName, uint32 openFlags, ShareFlags shareFlags ):
	filePeer_(NULL),
	openAccess_(File::ofNone)
{
	setName( fileName );
	openWithRights( fileName, openFlags, shareFlags );	
}

File::File():
	filePeer_(NULL),
	openAccess_(File::ofNone)	
{
	/*filePeer_ = SystemToolkit::createFilePeer( this );
	if ( NULL == filePeer_ ) {
		throw NoPeerFoundException();
	}

	resetStats();
	*/
	setName( "" );
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

void File::create( const String& newFileName, uint32 openFlags )
{
	try {
		fileName_ = newFileName;
		filePeer_->create(openFlags);
		openAccess_ = openFlags;
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

VCF::uint64 File::getSize()
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

void File::openWithRights( const String& fileName, uint32 openFlags, ShareFlags shareFlags )
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
$Id$
*/
