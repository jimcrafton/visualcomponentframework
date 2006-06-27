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

	virtual void seek( const uint32& offset, const SeekType& offsetFrom );

	virtual uint32 getSize();

    virtual uint32 read( unsigned char* bytesToRead, uint32 sizeOfBytes );

    virtual uint32 write( const unsigned char* bytesToWrite, uint32 sizeOfBytes );

	virtual char* getBuffer();

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
