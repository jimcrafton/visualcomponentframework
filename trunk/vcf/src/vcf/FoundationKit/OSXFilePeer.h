#ifndef _VCF_OSXFILEPEER_H__
#define _VCF_OSXFILEPEER_H__
//OSXFilePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class OSXFilePeer : public Object, public FilePeer{

public:

	class FileSearchData {
	public:

		FileSearchData() {

		}
	};

	OSXFilePeer( File* file, const String& fileName="" );

	virtual ~OSXFilePeer();

	String getName(){
		return file_->getName();
	};	
	
	virtual void setFile( File* file );

	/*
	* gets the size of the file in bytes
	*@param ulong64 the size
	*/
	virtual ulong64 getSize();

	/*
	* updates the informations about the file from the file system
	*@param statMask the mask indicating the infos we want to update
	*/
	virtual void updateStat( File::StatMask statMask );

	/*
	* set the fileAttributes of the file
	*@param fileAttributes the desired attributes
	*/
	virtual void setFileAttributes( const File::FileAttributes fileAttributes );


	virtual bool isExecutable();

	/*
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
	virtual void open( const String& fileName, ulong32 openFlags = File::ofRead, File::ShareFlags shareFlags = File::shMaskAny );

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



	/* Directory::Finder support functions */

	virtual void initFileSearch( Directory::Finder* finder );

	virtual File* findNextFileInSearch( Directory::Finder* finder );

	virtual void endFileSearch( Directory::Finder* finder );
	
	int getFileHandle() {
		return fileHandle_;
	}
private:
	int fileHandle_;
	File* file_;
	bool searchStarted_;
	std::vector<String> searchFilters_;
	std::vector<String>::iterator searchFilterIterator_;


	std::map<Directory::Finder*,FileSearchData> searchMap_;

	void buildSearchFilters( const String& searchFilter );
};

}; //end of namespace VCF


/**
*CVS Log info
 *$Log$
 *Revision 1.2  2004/08/07 02:49:13  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.10  2004/08/02 04:11:53  ddiego
 *added more examples to xcode project
 *
 *Revision 1.1.2.9  2004/08/01 23:40:16  ddiego
 *fixed a few osx bugs
 *
 *Revision 1.1.2.8  2004/07/29 03:55:21  ddiego
 *osx updates
 *
 *Revision 1.1.2.7  2004/07/27 04:26:04  ddiego
 *updated devmain-0-6-5 branch with osx changes
 *
 *Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
 *This checks in a bunch of changes to the FoundationKit for OSX
 *porting. The thread, mutex, semaphor, condition, and file peers
 *have all been implemented and tested. The file peer could be improved
 *and needs search functionality. The locale peer is only partially
 *complete, but the functions will return values. The unicode transition
 *is also finished and works OK now.
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.4.2.1  2004/04/26 21:58:42  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.4  2004/04/03 15:48:41  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.3.4.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.3  2003/08/09 02:56:44  ddiego
 *merge over from the devmain-0-6-1 branch
 *Changes
 *Features:
 *-Added additional implementation to better support the MVC architecture in
 *the VCF
 *
 *-Added a Document/View architecure that is similar to MFC's or NextSteps's
 *Doc/View architectures
 *
 *-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
 *now basic support for it in terms of drawing vector shapes
 *(fills and strokes). Image support will come in the next release
 *
 *-Added several documented graphics tutorials
 *
 *Bugfixes:
 *
 *[ 775744 ] wrong buttons on a dialog
 *[ 585239 ] Painting weirdness in a modal dialog ?
 *[ 585238 ] Modal dialog which makes a modal Dialog
 *[ 509004 ] Opening a modal Dialog causes flicker
 *[ 524878 ] onDropped not called for MLTcontrol
 *
 *Plus an issue with some focus and getting the right popup window to activate
 *has also been fixed
 *
 *Revision 1.2.2.1  2003/06/23 23:16:55  ddiego
 *added some furtther implementation for the osx port
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


#endif // _VCF_OSXFILEPEER_H__


