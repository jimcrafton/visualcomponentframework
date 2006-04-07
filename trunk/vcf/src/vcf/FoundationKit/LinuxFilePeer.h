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
	*@param ulong64 the size
	*/
	virtual ulong64 getSize();

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
	virtual void open( const String& fileName, ulong32 openFlags = File::ofRead,
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
	virtual void create( ulong32 openFlags );

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

    ulong32 convertAttributesFromSystemSpecific( const struct stat& st, const String& fileName );

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


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.4  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
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
*Revision 1.1.2.5  2004/08/02 00:48:23  ddiego
*fixed build errors in linux for FoundationKit
*
*Revision 1.1.2.4  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.16.1  2003/03/12 03:10:55  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.4.1  2002/03/26 04:46:10  cesarmello
*Linux headers
*
*Revision 1.1  2002/01/28 02:04:54  cesarmello
*Linux file peer implementation
*
*/


#endif // _VCF_LINUXFILEPEER_H__


