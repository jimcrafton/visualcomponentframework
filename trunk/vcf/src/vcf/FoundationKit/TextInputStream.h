#ifndef _VCF_TEXTINPUTSTREAM_H__
#define _VCF_TEXTINPUTSTREAM_H__
//TextInputStream.h

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
*TextInputStream is used for interpreting data from another stream as text.
*This assumes the data in the stream was originally written as text. For example,
*a FileStream that has been used to write a binary file, and is then passed into
*a new instance of TextInputStream to read the same file, will cause unpredicatable
*results in the decoding of the stream, since the TextInputStream is taking advantage of
*certain layout assumptions in how the source stream is organized.
*So consider yourself warned !
*/
class FOUNDATIONKIT_API TextInputStream : public InputStream
{
public:
	TextInputStream( InputStream* inStream );

	virtual ~TextInputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	virtual unsigned long getSize();

	virtual char* getBuffer();

	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes );

	/**
	*all numbers are written out as the number converted to text, followed by a
	*space character ( ' ' ), so the value 2 becomes "2 "
	*/

	virtual void read( short& val );

	virtual void read( long& val );

	virtual void read( int& val );

	virtual void read( bool& val );

	virtual void read( float& val );

	virtual void read( double& val );

	virtual void read( String& val );

	void init();

	void readLine( String& line );

	virtual bool isEOS()
	{
		return totCharRead_ >= size_? true:false;
	}

	virtual ulong32 getCurrentSeekPos() ;
private:
	InputStream* inStream_;
	unsigned long size_;
	unsigned long totCharRead_;
	String readTillWhiteSpace();

	/**
	*reads to the starting point of the token and then accumalates anything in the buffer
	*till the next occurence of the token
	*@return String the accumalted text
	*/
	String readTillTokenPair( const char& token );
};


};


#endif // _VCF_TEXTINPUTSTREAM_H__

/**
$Id$
*/
