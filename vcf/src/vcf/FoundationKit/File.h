#ifndef _VCF_FILE_H__
#define _VCF_FILE_H__
//File.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class FilePeer;
class FileInputStream;
class FileOutputStream;

/**
*	The File class represents a single file or directory.
*
*	File functions that fail throw FileIO exceptions.
*/
class FOUNDATIONKIT_API File : public Object{
public:
	enum FileAttributes {
		faNone                 = 0x00000000,
		faReadOnly             = 0x00000001,
		faHidden               = 0x00000002,
		faSystem               = 0x00000004,
		faExecutable           = 0x00000008,
		faDirectory            = 0x00000010,
		faArchive              = 0x00000020,
		faDevice               = 0x00000040,
		faNormal               = 0x00000080,
		
		/* these masks affect the Directory search */
		faMaskFile     = faReadOnly | faHidden | faSystem | faArchive | faNormal,
		faMaskFileExec = faReadOnly | faHidden | faSystem | faArchive | faNormal | faExecutable,
		faMaskDir      = faMaskFile | faDirectory,
		faMaskAll      = faMaskDir  | faDevice | faExecutable
	};

	enum StatMask {
		smStatNone       = 0x0,

		smSize           = 0x1,
		smAttributes     = 0x2,

		smDateCreation   = 0x4,
		smDateModified   = 0x8,
		smDateAccess     = 0x10,

		smMaskDateAll = smDateCreation | smDateModified | smDateAccess,

		smMaskAll = smMaskDateAll | smSize | smAttributes
	};

	enum OpenFlags {
		ofNone           = 0x0,
		ofRead           = 0x1,
		ofWrite          = 0x2,
		ofAppend         = 0x4,

		/* open for stat: if yo know the way to use it, please do it !
		   but I don't think we need of it
		*/
		ofStat           = 0x4

	};

	enum ShareFlags {
		shNone           = 0x0,
		shRead           = 0x1,
		shWrite          = 0x2,

		shMaskAny = shRead | shWrite
	};


public:
	
	File( const String& fileName );
	
	File( const String& fileName, ulong32 openFlags, ShareFlags shareFlags );

	virtual ~File();


	/*
	* gets the file peer
	* returns FilePeer* the file peer
	*/
	FilePeer* getPeer() {
		return filePeer_;
	}

	/*
	* sets the name of the File
	* and creates the peer if it does not exists yet
	*@param fileName the name
	*/
	virtual void setName( const String& fileName );

	String getName() const;

	/*
	* gets the owner of the file
	* returns String the owner of the file
	*/
	String getOwner();

	/*
	* reset infos like the fileAttributes, DateTime stamps

	*/
	void resetStats();

	/*
	* updates the informations about the file from the file system
	*@param statMask the mask indicating the infos we want to update
	*/
	void updateStat( File::StatMask statMask = File::smMaskAll );

	/*
	* tells if the file is a directory file on the file system
	* returns true if it is a directory
	*/
	bool isDirectory();

	/*
	* tells if the file has a read only attribute on the file system
	* returns true if it is read only
	*/
	bool isExecutable();

	/*
	* tells if the file has a read only attribute on the file system
	* returns true if it is read only
	*/
	bool isReadOnly();

	/*
	* tells if the file has a system attribute on the file system
	* returns true if it is a system file
	*/
	bool isSystem();

	/*
	* tells if the file has a hidden attribute on the file system
	* returns true if it is a hidden file
	*/
	bool isHidden();

	/*
	* tells if the file has an archive attribute on the file system
	* returns true if it is archived
	*/
	bool isArchive();

	/*
	* tells if the file has a device attribute on the file system
	* returns true if it is a device
	*/
	bool isDevice();

	/*
	* tells if the file has a normal attribute on the file system
	* returns true if it is a normal file
	*/
	bool isNormal();

	/*
	* tells if a file can be opened for reading
	* returns bool true if can be opened for reading
	*/
	bool isReadable();

	/*
	* tells if a file can be opened for writing
	* returns bool true if can be opened for reading
	*/
	bool isWriteable();

	/*
	* gets the size of the file in bytes
	*@param ulong64 the size
	*/
	VCF::ulong64 getSize();

	/*
	* gets the file attributes of the file
	*@return the file attributes
	*/
	FileAttributes getFileAttributes();

	/*
	* set the fileAttributes of the file
	*@param fileAttributes the desired attributes
	*/
	void setFileAttributes( const File::FileAttributes fileAttributes );

	/*
	* gets the date of creation of the file
	*@param DateTime the creation date
	*/
	DateTime getDateCreation();

	/*
	* gets the modification Date of the file
	*@param DateTime the desired modification date
	*/
	DateTime getDateModified();

	/*
	* gets the date of the last access to the file
	*@param DateTime the last access date
	*/
	DateTime getDateAccess();

	/*
	* set the modification Date of the file <B>given in UTC time</B>
	*@param date the desired modification date
	*/
	void setDateModified( const DateTime& date );

	/*
	* updates the file's modified time to the time when call is made
	* the time is internally converted in UTC time 
	*before being assigned to the file
	*/
	void updateTime();


	/**
	*tells if a filename actually exists in the filesystem
	*@param fileName the filename to check for existence
	*@return true if the filename exists
	*/
	static bool exists( const String& fileName );

	/**
	*tells if a filename actually exists in the filesystem
	*@return true if the file exists
	*/
	bool exists() const;


	/**
	* opens the file using the current file name assigned to it
	*/
	void open();

	/**
	* opens a new file, closes the old one if previously opened
	*@param fileName the desired new filename
	*/
	void openWithFileName( const String& fileName );

	/**
	* opens a file with read/write access
	* Closes the old one if previously opened	
	*@param fileName the desired new filename
	*@param openFlags
	*@param shareFlags
	*/
	void openWithRights( const String& fileName, ulong32 openFlags = File::ofRead, ShareFlags shareFlags = File::shMaskAny );

	/**
	* closes the file if open
	* it can be called even if it was not opened
	*/
	void close();

	/**
	creates a new file, as opposed to open, which simply opens an existing one.
	If the file already exists then create will empty it's contents.
	@param newFileName the filename
	*/
	void create( const String& newFileName, ulong32 openFlags = File::ofRead );

	/**
	* deletes the file from the file system
	*/
	void remove();

	/**
	* renames/moves a file
	*@param newFileName the filename
	*/
	void move( const String& newFileName );


	/**
	* copies the file into another one
	*@param fileNameToCopyTo the filename to create/overwrite.
	*/
	void copyTo( const String& fileNameToCopyTo );

	/**
	This returns a new instance of an InputStream that's attached to this file. Please
	note that it is the caller's responsibility to delete this when finished with it.
	Each call will create an new stream instance.
	@return FileInputStream - an new output stream instance. If the file is opened without
	an ofRead mask set, then this is NULL.
	@see FileInputStream
	@see InputStream
	*/
	FileInputStream* getInputStream();

	/**
	This returns a new instance of an OutputStream that's attached to this file. Please
	note that it is the caller's responsibility to delete this when finished with it.
	Each call will create an new stream instance. If the file is open without write access
	this method will return NULL.
	@return FileOutputStream - an new output stream instance. If the file is opened without
	an ofWrite mask set, then this is NULL.
	@see FileOutputStream
	@see OutputStream
	*/
	FileOutputStream* getOutputStream();


	/**
	functions for modifying the file member values. For internal use only.
	*/

	inline void internal_setStatMask( const StatMask& val ) {
		validStat_ = val;
	}

	inline void internal_addToStatMask( const long& val ) {
		validStat_ = (StatMask)(validStat_ | val);
	}

	inline void internal_removeFromStatMask( const long& val ) {
		validStat_ = (StatMask)(validStat_ & ~val);
	}

	inline void internal_setFileName( const String& val ) {
		fileName_ = val;
	}

	inline void internal_setFileAttributes( const ulong32& val ) {
		fileAttributes_ = val;
	}

	
protected:
	FilePeer* filePeer_;
	
	StatMask validStat_;
	ulong32 openAccess_;
	
	String   fileName_;
	String   owner_; // a string ?
	
	ulong32  fileAttributes_;	
};






///////////////////////////////////////////////////////////////////////////////
// inlines


inline String File::getName() const {
	return fileName_;
}	

inline void File::resetStats() {
    validStat_        = File::smStatNone;

    owner_ = "";

    fileAttributes_   = 0;
}


inline File::FileAttributes File::getFileAttributes()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return (FileAttributes)fileAttributes_;
}

inline bool File::isDirectory()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faDirectory ) );
}

inline bool File::isReadOnly()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faReadOnly ) );
}

inline bool File::isSystem()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faSystem ) );
}

inline bool File::isHidden()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faHidden ) );
}

inline bool File::isArchive()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faArchive ) );
}

inline bool File::isDevice()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faDevice ) );
}

inline bool File::isNormal()
{
	if ( 0 == ( validStat_ & File::smAttributes ) ) {
		updateStat( File::smAttributes );
	}
	return ( 0 != ( fileAttributes_ & File::faNormal ) );
}

inline bool File::exists() const
{
	return File::exists( fileName_ );
}


inline bool File::isReadable()
{
	return (openAccess_ & File::ofRead) ? true : false;;
}

inline bool File::isWriteable() 
{
	return ((openAccess_ & File::ofWrite) || (openAccess_ & File::ofAppend)) ? true : false;
}




}; //end of namespace VCF




/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.11  2004/08/03 23:04:38  marcelloptr
*completed implementation of updateTime
*
*Revision 1.1.2.10  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.9  2004/07/26 03:40:31  ddiego
*minor changes
*
*Revision 1.1.2.8  2004/07/24 01:40:42  ddiego
*committed changes requested by Marcello. Got rid of the remaining
*date time members on the File class - now the dat time function call the
*FilePeer directly each time. Also added 2 functions to DateTime to convert
*directly to UTC or Local time.
*
*Revision 1.1.2.7  2004/07/23 19:51:13  marcelloptr
*minor changes on File / Directory stuff
*
*Revision 1.1.2.6  2004/07/23 00:56:37  ddiego
*added the latest changes to the File and Directory finder classes.
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
*Revision 1.10.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.2  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.9.4.1  2003/08/13 19:01:43  marcelloptr
*made File::getName() const
*
*Revision 1.9  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.22.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.22.1  2003/03/12 03:11:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_FILE_H__


