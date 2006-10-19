#ifndef _VCF_OSXFILESTREAM_H__
#define _VCF_OSXFILESTREAM_H__
//OSXFileStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF
{
/**
This is going to based on the C runtime's fopen/fread/fwrite stream
API for now.
*/
class OSXFileStream : public FileStreamPeer
{
public:
	OSXFileStream( const String& filename, const FileStreamAccessType& accessType );
	
	OSXFileStream( File* file );

	virtual ~OSXFileStream();

	virtual void seek( const uint64& offset, const SeekType& offsetFrom );

	virtual uint64 getSize();

	virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

	virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes );

	virtual char* getBuffer();
private:
	int fileHandle_;
	VCF::String filename_;
	VCF::File* file_;
	int translateSeekTypeToMoveType( const SeekType& offsetFrom );
};


};


#endif // _VCF_OSXFILESTREAM_H__

/**
$Id$
*/
