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
	*@param uint64 the size
	*/
	virtual uint64 getSize() = 0;

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
	virtual void open( const String& fileName, uint32 openFlags = File::ofRead, File::ShareFlags shareFlags = File::shMaskAny ) = 0;

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
	virtual void create( uint32 openFlags ) = 0;

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


#endif // _VCF_FILEPEER_H__

/**
$Id$
*/
