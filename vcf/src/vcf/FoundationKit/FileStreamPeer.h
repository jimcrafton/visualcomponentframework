#ifndef _VCF_FILESTREAMPEER_H__
#define _VCF_FILESTREAMPEER_H__
//FileStreamPeer.h

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

/**
\class FileStreamPeer FileStreamPeer.h "vcf/FoundationKit/FileStreamPeer.h"
*FileStreamPeer is a basic file stream interface to wrap native file IO OS calls.
*Under Win32 this will involve calls to ReadFile() and WriteFile,
*among others.
*
*@author Jim Crafton
*@version 1.0
*/
class FOUNDATIONKIT_API FileStreamPeer {
public:
	virtual ~FileStreamPeer(){};

	/**
	*moves the seek pointer offset number of bytes in the
	*direction specified by the offsetFrom argument.
	*@param uint32 the number of bytes of offset the
	*seek pointer
	*@param SeekType the direction to offset the seek pointer, which
	*may be one of the following values <br>
	*SEEK_FROM_START - offsets from the beginning of the file <br>
	*SEEK_FROM_RELATIVE - offsets relative to the current seek position <br>
	*SEEK_FROM_END - offsets backwards, starting at the end of the file <br>
	*/
	virtual void seek(const uint64& offset, const SeekType& offsetFrom) = 0;

	/**
	*returns the size of the file stream in bytes
	*/
	virtual uint64 getSize() = 0;

	/**
	*reads sizeOfBytes bytes from the stream into the buffer bytesToRead
	*@param char* a buffer of at least sizeOfBytes long. This must be
	*allocated by the caller.
	*@param uint32 the number of bytes to read from the file, starting
	*at the current seek position.
	*/
	virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes ) = 0;

	/**
	*writes sizeOfBytes bytes to the file stream from the buffer bytesToWrite.
	*@param char* a buffer that must be at least sizeOfBytes long, that contains
	*the data that will written out to the file stream
	*@param @ uint32 the number of bytes to write
	*/
	virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes ) = 0;

	/**
	*returns a pointer to the buffer that represents the file contents
	*/
	virtual char* getBuffer() = 0;
};


};


#endif // _VCF_FILESTREAMPEER_H__

/**
$Id$
*/
