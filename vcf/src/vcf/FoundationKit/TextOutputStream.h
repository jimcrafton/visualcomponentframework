#ifndef _VCF_TEXTOUTPUTSTREAM_H__
#define _VCF_TEXTOUTPUTSTREAM_H__
//TextOutputStream.h

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
*The TextOutputStream is used for writing data from another stream as text.

*/
class FOUNDATIONKIT_API TextOutputStream : public OutputStream
{
public:

	TextOutputStream( OutputStream* outStream );

	TextOutputStream();

	virtual ~TextOutputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	virtual unsigned long getSize();

	virtual char* getBuffer();

	virtual ulong32 getCurrentSeekPos() ;

	virtual void write( const char* bytesToRead, unsigned long sizeOfBytes );

	/**
	*all numbers are written out as the number converted to text, followed by a
	*space character ( ' ' ), so the value 2 becomes "2 "
	*/

	virtual void write( const short& val );

	virtual void write( const long& val );

	virtual void write( const int& val );

	virtual void write( const bool& val );

	virtual void write( const float& val );

	virtual void write( const double& val );

	virtual void write( const String& val );

	void init();

	void writeLine( const String& line );

	String getTextBuffer();

	virtual String toString();
private:
	String textBuffer_;
	unsigned long size_;
	OutputStream* outStream_;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.8  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.1  2003/03/12 03:11:46  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2002/02/28 01:07:09  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TEXTOUTPUTSTREAM_H__


