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

	virtual void seek( const unsigned long& offset, const SeekType& offsetFrom );

	virtual unsigned long getSize();

	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes );

	virtual unsigned long write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes );

	virtual char* getBuffer();
private:
	int fileHandle_;
	VCF::String filename_;
	VCF::File* file_;
	int translateSeekTypeToMoveType( const SeekType& offsetFrom );
};


};


/**
*CVS Log info
 *$Log$
 *Revision 1.3  2006/04/07 02:35:34  ddiego
 *initial checkin of merge from 0.6.9 dev branch.
 *
 *Revision 1.2.6.1  2005/11/10 02:02:38  ddiego
 *updated the osx build so that it
 *compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
 *
 *Revision 1.2  2004/08/07 02:49:13  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.7  2004/08/01 23:40:16  ddiego
 *fixed a few osx bugs
 *
 *Revision 1.1.2.6  2004/07/29 03:55:21  ddiego
 *osx updates
 *
 *Revision 1.1.2.5  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.3.2.1  2004/04/26 21:58:42  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.3  2004/04/03 15:48:41  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.2.6.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.2  2003/05/17 20:37:12  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:01  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


#endif // _VCF_OSXFILESTREAM_H__


