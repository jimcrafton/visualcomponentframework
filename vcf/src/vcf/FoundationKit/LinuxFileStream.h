#ifndef _VCF_LINUXFILESTREAM_H__
#define _VCF_LINUXFILESTREAM_H__ 
//LinuxFileStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//#include "FileStreamPeer.h"


namespace VCF
{
/**
* This is going to based on the C runtime's fopen/fread/fwrite stream
*API for now.
*/
class FOUNDATIONKIT_API LinuxFileStream : public FileStreamPeer
{
public:
	LinuxFileStream( const String& filename,
	                 const FileStreamAccessType& accessType );

	LinuxFileStream( File* file );

	virtual ~LinuxFileStream();

	virtual void seek( const uint64& offset, const SeekType& offsetFrom );

	virtual uint64 getSize();

    virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

    virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes );

	virtual uchar* getBuffer();

private:
	int fileHandle_;
	VCF::File* file_;
	VCF::String filename_;
	
	int translateSeekTypeToMoveType( const SeekType& offsetFrom );
};


}


#endif // _VCF_LINUXFILESTREAM_H__

/**
$Id$
*/
