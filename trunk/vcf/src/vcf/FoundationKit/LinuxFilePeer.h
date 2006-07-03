#ifndef _VCF_LINUXFILEPEER_H__
#define _VCF_LINUXFILEPEER_H__ 


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class LinuxFilePeer : public Object, public FilePeer
{
public:
	class FileSearchData;

	LinuxFilePeer( File* file );

	virtual ~LinuxFilePeer();

	String getName()
	{
		return file_->getName();
	}

	virtual void setFile( File* file );

	/**
	* gets the size of the file in bytes
	*@param uint64 the size
	*/
	virtual uint64 getSize();

	/**
	* updates the informations about the file from the file system
	*@param statMask the mask indicating the infos we want to update
	*/
	virtual void updateStat( File::StatMask statMask );

	/**
	* set the fileAttributes of the file
	*@param fileAttributes the desired attributes
	*/
	virtual void setFileAttributes( const File::FileAttributes fileAttributes );

	virtual bool isExecutable();

	/**
	* set the modification Date of the file
	*@param date the desired modification date
	*/
	virtual void setDateModified( const DateTime& dateModified );

	virtual DateTime getDateModified();
	virtual DateTime getDateCreated();
	virtual DateTime getDateAccessed();

	/**
	* opens a file with read/write access
	* Closes the old one if previously opened
	*@param fileName the desired new filename
	*@param openFlags
	*@param shareFlags
	*/
	virtual void open( const String& fileName, uint32 openFlags = File::ofRead,
	                   File::ShareFlags shareFlags = File::shMaskAny );

	/**
	* closes the file if open
	* it can be called even if it was not opened
	*/
	virtual void close();

	/**
	creates a new file
	if the last character in the filename is a
	directory character, then a directory is created
	instead of a file. The file name is omitted here as this is stored in the
	File instance kept by the peer.
	*/
	virtual void create( uint32 openFlags );

	/**
	*deletes the file from the file system
	*/
	virtual void remove();

	/**
	* renames/moves a file
	*@param newFileName the filename
	*/ 
	//void rename( const String& newFileName );
	//virtual void rename( const String& newFileName ); //renames the file
	virtual void move( const String& newFileName );   //renames/moves the file

	/**
	* copies the file into another one
	*@param fileNameToCopyTo the filename to create/overwrite.
	*/
	virtual void copyTo( const String& copyFileName );

    uint32 convertAttributesFromSystemSpecific( const struct stat& st, const String& fileName );

	/* Directory::Finder support functions */

	virtual void initFileSearch( Directory::Finder* finder );

	virtual File* findNextFileInSearch( Directory::Finder* finder );

	virtual void endFileSearch( Directory::Finder* finder );

	int getFileHandle()
	{
		return ( fileHandle_ > 1 )
		       ? fileHandle_
		       : 0;
	}

private:
	int fileHandle_;
	File* file_;

    bool searchStarted_;
    FileSearchData* fileSearchData_;

	void buildSearchFilters( const String& searchFilter );

};

} //end of namespace VCF


#endif // _VCF_LINUXFILEPEER_H__

/**
$Id$
*/
