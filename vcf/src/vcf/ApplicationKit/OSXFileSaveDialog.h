#ifndef _VCF_OSXFILESAVEDIALOG_H__
#define _VCF_OSXFILESAVEDIALOG_H__
//OSXFileSaveDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



namespace VCF {

typedef std::pair<String,String> FilterPair;

class OSXFileSaveDialog : public CommonFileDialogPeer, public Object {
public:
	OSXFileSaveDialog( Control* owner=NULL );

	virtual ~OSXFileSaveDialog();

	virtual void setTitle( const String& title );

	virtual bool execute();

	virtual void addFilter( const String & description, const String & extension );

    virtual void setDirectory( const String & directory );

	virtual void setFileName( const String & filename );

    virtual String getFileName();

    virtual String getDirectory();

    virtual String getFileExtension();

	virtual uint32 getSelectedFileCount();

	virtual Enumerator<String>* getSelectedFiles();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	virtual String getSelectedFilter() {
		return selectedFilter_;
	}

	virtual void setSelectedFilter( const String& selectedFilter );

	virtual void setFileMustExist( const bool& fileMustExist );

protected:
	String title_;
	std::vector<FilterPair> filter_;
	std::map<String,OSType> fileTypesFilterMap_;
	String directory_;
	String selectedFileExt_;
	String fileName_;
	bool fileMustExist_;
	Control* owner_;
	String selectedFilter_;
	int selectedFileTypeIndex_;
	
	void buildFileTypesMap();
	
	bool matchFileType( NavFileOrFolderInfo* info, FSRef* fileRef );
	
	static pascal void saveNavEventProc( NavEventCallbackMessage inSelector, NavCBRecPtr ioParams, 
										NavCallBackUserData	ioUserData);
										
	static pascal Boolean saveFileFilterProc( AEDesc* theItem, void* info, NavCallBackUserData callBackUD, NavFilterModes filterMode );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*
*/


#endif // _VCF_OSXFILESAVEDIALOG_H__


