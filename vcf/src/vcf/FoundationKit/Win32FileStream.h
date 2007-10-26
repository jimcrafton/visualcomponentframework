#ifndef _VCF_WIN32FILESTREAM_H__
#define _VCF_WIN32FILESTREAM_H__
//Win32FileStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Win32FileStream : public FileStreamPeer
{
public:
	Win32FileStream( const String& filename, const FileStreamAccessType& accessType );

	Win32FileStream( File* file );

	virtual ~Win32FileStream();

	virtual void seek( const uint64& offset, const SeekType& offsetFrom );

	virtual uint64 getSize();

	virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

	virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes );

	virtual uchar* getBuffer();
private:
	HANDLE fileHandle_;
	VCF::String filename_;
	File* file_;
	DWORD translateAccessType( const FileStreamAccessType& accessType );
	DWORD translateAccessTypeToCreationType( const FileStreamAccessType& accessType );
	DWORD translateSeekTypeToMoveType( const SeekType& offsetFrom );
};


};


#endif // _VCF_WIN32FILESTREAM_H__

/**
$Id$
*/
