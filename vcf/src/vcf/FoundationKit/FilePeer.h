#ifndef _VCF_FILEPEER_H__
#define _VCF_FILEPEER_H__
//FilePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class File;


/**
*The FilePeer interface is used to describe basic
*file operations that are then implemented for the
*specific OS platform. The File class uses an internal
*instance of this class to perform the actual work
*of dealing with files.
*/
class FOUNDATIONKIT_API FilePeer {
public:

	virtual ~FilePeer(){};


	/**
	* close any open handles, reset all internal data,
	*and it associates itself to a given file instance.
	*@param File* pointer to a File instance
	*/
	virtual void setFile( File* file ) = 0;

	//virtual String getName() = 0; // we don't need anymore

	/**
	* gets the size of the file in bytes
	*@param ulong64 the size
	*/
	virtual ulong64 getSize() = 0;

	/**
	* updates the informations about the file from the file system
	*@param statMask the mask indicating the infos we want to update
	*/
	virtual void updateStat( File::StatMask statMask = File::smMaskDateAll ) = 0;

	/**
	* set the fileAttributes of the file
	*@param fileAttributes the desired attributes
	*/
	virtual void setFileAttributes( const File::FileAttributes fileAttributes ) = 0;


	/**
	* tells if the file can be run by the OS.
	*@return bool, true if it does.
	*/
	virtual bool isExecutable() = 0;

	/**
	* set the modification date of the file
	*@param date the desired modification date
	*/
	virtual void setDateModified( const DateTime& dateModified ) = 0;


	/**
	* get the modification date of the file
	*@return DateTime, the modification date.
	*/
	virtual DateTime getDateModified()  = 0;

	/**
	* get the creation date of the file
	*@return DateTime, the creation date.
	*/
	virtual DateTime getDateCreated()  = 0;

	/**
	* get the latest date the file has been accessed.
	*@return DateTime, the access date.
	*/
	virtual DateTime getDateAccessed()  = 0;

	/**
	* opens a file with read/write access
	* Closes the old one if previously opened
	*@param fileName the desired new filename
	*@param openFlags
	*@param shareFlags
	*/
	virtual void open( const String& fileName, ulong32 openFlags = File::ofRead, File::ShareFlags shareFlags = File::shMaskAny ) = 0;

	/**
	* closes the file if open
	* it can be called even if it was not opened
	*/
	virtual void close() = 0;

	/**
	creates a new file
	if the last character in the filename is a
	directory character, then a directory is created
	instead of a file. The file name is omitted here as this is stored in the 
	File instance kept by the peer.
	*/
	virtual void create( ulong32 openFlags ) = 0;

	/**
	*deletes the file from the file system
	*/
	virtual void remove() = 0;

	/**
	* renames/moves a file
	*@param newFileName the filename
	*/
	//void rename( const String& newFileName );
	//virtual void rename( const String& newFileName ); //renames the file
	virtual void move( const String& newFileName ) = 0;   //renames/moves the file

	/**
	* copies the file into another one
	*@param fileNameToCopyTo the filename to create/overwrite.
	*/
	virtual void copyTo( const String& copyFileName ) = 0;



	/* Directory::Finder support functions */

	virtual void initFileSearch( Directory::Finder* finder ) = 0;

	virtual File* findNextFileInSearch( Directory::Finder* finder ) = 0;

	virtual void endFileSearch( Directory::Finder* finder ) = 0;

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/10 19:09:46  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/08/02 00:48:23  ddiego
*fixed build errors in linux for FoundationKit
*
*Revision 1.1.2.7  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.6  2004/07/24 01:40:42  ddiego
*committed changes requested by Marcello. Got rid of the remaining
*date time members on the File class - now the dat time function call the
*FilePeer directly each time. Also added 2 functions to DateTime to convert
*directly to UTC or Local time.
*
*Revision 1.1.2.5  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.4  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
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
*Revision 1.9.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:58  ddiego
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
*Revision 1.8  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.1  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FILEPEER_H__


