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
	*@param unsigned long the number of bytes of offset the
	*seek pointer
	*@param SeekType the direction to offset the seek pointer, which
	*may be one of the following values <br>
	*SEEK_FROM_START - offsets from the beginning of the file <br>
	*SEEK_FROM_RELATIVE - offsets relative to the current seek position <br>
	*SEEK_FROM_END - offsets backwards, starting at the end of the file <br>
	*/
	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom) = 0;

	/**
	*returns the size of the file stream in bytes
	*/
	virtual unsigned long getSize() = 0;

	/**
	*reads sizeOfBytes bytes from the stream into the buffer bytesToRead
	*@param char* a buffer of at least sizeOfBytes long. This must be
	*allocated by the caller.
	*@param unsigned long the number of bytes to read from the file, starting
	*at the current seek position.
	*/
	virtual void read( char* bytesToRead, unsigned long sizeOfBytes ) = 0;

	/**
	*writes sizeOfBytes bytes to the file stream from the buffer bytesToWrite.
	*@param char* a buffer that must be at least sizeOfBytes long, that contains
	*the data that will written out to the file stream
	*@param @ unsigned long the number of bytes to write
	*/
	virtual void write( const char* bytesToWrite, unsigned long sizeOfBytes ) = 0;

	/**
	*returns a pointer to the buffer that represents the file contents
	*/
	virtual char* getBuffer() = 0;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.7  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.1  2003/03/12 03:11:44  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FILESTREAMPEER_H__


