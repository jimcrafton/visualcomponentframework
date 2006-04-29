#ifndef _VCF_FILESTREAM_H__
#define _VCF_FILESTREAM_H__
//FileStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


namespace VCF  {

class FileStreamPeer;

/**
\class FileStreamBase FileStream.h "vcf/FoundationKit/FileStream.h"
Special file stream that uses native OS calls
for file IO as opposed to the more generic C++ filestream class.
This class uses a FileStreamPeer to do the actual work

@author Jim Crafton
@version 1.0
*/


class FOUNDATIONKIT_API FileStreamBase : public Object {
public:
	FileStreamBase();

	virtual ~FileStreamBase();

	String& getFilename() {
		return filename_;
	};

	/**
	*closes the file stream
	*/
	void close();

	/**
	*opens a file stream
	*/
	void open( const String& filename, FileStreamAccessType accessType );

protected:
	void init();
	FileStreamPeer* fsPeer_;
	String filename_;
	FileStreamAccessType access_;
	ulong32 currentSeekPos_;
};

/**
\class FileInputStream FileStream.h "vcf/FoundationKit/FileStream.h"
*/
class FOUNDATIONKIT_API FileInputStream : public InputStream , public FileStreamBase {
public:
	FileInputStream( File* file );

	FileInputStream( const String& filename );

	virtual ~FileInputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	/**
	returns the size of the stream. The size represents the
	number of bytes that have been <b>read</b> from the stream
	*/
    virtual unsigned long getSize();


	/**
	*returns a pointer to the buffer that holds the stream memory
	*/
	virtual char* getBuffer();

	virtual ulong32 getCurrentSeekPos() ;

	/**
	input
	*/
	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes );

	/**
	end of stream
	*/
	virtual bool isEOS()  {
		// stub impl.
		return false;
	}

	void open( const String& filename );

protected:

};

/**
\class FileOutputStream FileStream.h "vcf/FoundationKit/FileStream.h"
*/
class FOUNDATIONKIT_API FileOutputStream : public OutputStream , public FileStreamBase {
public:
	FileOutputStream( const String& filename, const bool & append = false );

	FileOutputStream( File* file );

	virtual ~FileOutputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	/**
	*returns the size of the stream. The size represents the
	*number of bytes that have been <b>written</b>, or <b>read</b> to/from the stream
	*/
    virtual unsigned long getSize();


	/**
	*returns a pointer to the buffer that holds the stream memory
	*/
	virtual char* getBuffer();

	virtual ulong32 getCurrentSeekPos() ;

	//output
	virtual unsigned long write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes );

	void open( const String& filename, const bool & append = false );

protected:
};



};


#endif // _VCF_FILESTREAM_H__

/**
$Id$
*/
