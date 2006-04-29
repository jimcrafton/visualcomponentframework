#ifndef _VCF_WIN32FILEPEER_H__
#define _VCF_WIN32FILEPEER_H__
//Win32FilePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {



class Win32FilePeer : public FilePeer, public Object {

public:
	class Win32FindData {
	public:
		Win32FindData() {
			searchHandle_ = NULL;
		}

		virtual ~Win32FindData(){}
		HANDLE searchHandle_;
	};

	class Win32FindDataA : public Win32FindData {
	public:
		Win32FindDataA() {
			memset( &findData_, 0, sizeof( WIN32_FIND_DATAA ) );
		}

		WIN32_FIND_DATAA findData_;
	};

	class Win32FindDataW : public Win32FindData {
	public:
		Win32FindDataW() {
			memset( &findData_, 0, sizeof( WIN32_FIND_DATAW ) );
		}

		WIN32_FIND_DATAW findData_;
	};

	//union Win32FindData {
	//	WIN32_FIND_DATAA dataA;
	//	WIN32_FIND_DATAW dataW;
	//};

public:

	Win32FilePeer( File* file );

	virtual ~Win32FilePeer();


	virtual String getName() {
		return file_->getName();
	};

	virtual void setFile( File* file );

	/**
	*returns the size of the file in bytes
	*/
	virtual ulong64 getSize();

	virtual DateTime getDateModified();

	virtual DateTime getDateCreated();
	
	virtual DateTime getDateAccessed();


	virtual void updateStat( File::StatMask statMask = File::smMaskAll );

	virtual void setFileAttributes( const File::FileAttributes fileAttributes );

	virtual bool isExecutable();

	virtual void setDateModified( const DateTime& dateModified );

	virtual void open( const String& fileName, ulong32 openFlags = File::ofRead, File::ShareFlags shareFlags = File::shMaskAny );

	virtual void close();

	/**
	*creates the file
	*if the last character in the filename_ is a
	*'DirectorySeparator' character, then a directory 
	*is created instead of a file.
	*/
	virtual void create( ulong32 openFlags );

	virtual void remove();

	virtual void move( const String& newFileName );

	virtual void copyTo( const String& copyFileName );


	static DateTime convertFileTimeToDateTime( const FILETIME& ft );

	static DateTime convertUtcFileTimeToLocalDateTime( const FILETIME& ftUtc );

	/**
	* Windows specific function: gets the alternate filename of a file
	* This is the the old dos name composed of 8+3 characters
	* @param String the full filename of the file
	* @return String the alternate filename
	*/
	static String getAlternateFileName( const String& fileName );




	/**
	*   Directory::Finder support functions
	*/

	/**
	* initialize the search and allocates meemory if necessary
	*/
	virtual void initFileSearch( Directory::Finder* finder );

	/**
	* the core of the search 'engine'
	*/
	virtual File* findNextFileInSearch( Directory::Finder* finder );

	/**
	* finalize the search closing any handles if necessary
	*/
	virtual void endFileSearch( Directory::Finder* finder );

	/**
	* sets the finder to continue the search in the next subdirectory
	* yet to search and switch displayMode if necessary
	*/
	virtual void continueSearch( Directory::Finder* finder, File* file );

	/**
	* sets the finder for a search one level down in the directory tree
	*/
	virtual void goDirDown( Directory::Finder* finder, File* file );

	/**
	* sets the finder for the first level up in the directory tree in which 
	* the search has not been completed yet
	*/
	virtual void goDirUp( Directory::Finder* finder, File* file );

	/**
	* copies the data contained in our Win32FindData structure into File 
	* Be careful! This function, beside the other informations, it copies the baseName only, not the is full path.
	*/
	static File* updateFindDataInfos( File* file, Win32FindData* findData, File::StatMask statMask = File::smMaskAll );

	/**
	* converts the file attributes from the OS specific format into the vcf format.
	*/
	static ulong32 convertAttributesFromSystemSpecific( const ulong32& dwAttributes );

	/**
	* converts the file attributes from the vcf format into the OS specific format.
	*/
	static ulong32 convertAttributesToSystemSpecific( File::FileAttributes dwAttributes );

	HANDLE getFileHandle() {
		return fileHandle_;
	}

protected:

	void initDataSearch();

	Win32FindData* findData_;

	HANDLE searchHandle_;

	static void copyFromAttributeData( File* file, WIN32_FILE_ATTRIBUTE_DATA& fileAttribData, File::StatMask statMask = File::smMaskAll );


	HANDLE fileHandle_;	// for some operations different than search

	File* file_;
};






}; //end of namespace VCF


#endif // _VCF_WIN32FILEPEER_H__

/**
$Id$
*/
