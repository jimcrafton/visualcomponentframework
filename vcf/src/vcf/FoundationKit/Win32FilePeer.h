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


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/10 19:09:47  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.5  2004/07/24 01:40:42  ddiego
*committed changes requested by Marcello. Got rid of the remaining
*date time members on the File class - now the dat time function call the
*FilePeer directly each time. Also added 2 functions to DateTime to convert
*directly to UTC or Local time.
*
*Revision 1.1.2.4  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.3  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.2  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10.4.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.9  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.16.1  2003/03/12 03:11:19  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32FILEPEER_H__


