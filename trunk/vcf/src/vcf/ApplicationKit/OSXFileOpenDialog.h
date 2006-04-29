#ifndef _VCF_OSXFILEOPENDIALOG_H__
#define _VCF_OSXFILEOPENDIALOG_H__
//OSXFileOpenDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



namespace VCF {

typedef std::pair<String,String> FilterPair;

class OSXFileOpenDialog : public CommonFileDialogPeer, public Object {
public:
	OSXFileOpenDialog( Control* owner=NULL );

	virtual ~OSXFileOpenDialog();

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
	std::vector<String> selectedFiles_;
	String directory_;
	String selectedFileExt_;
	String fileName_;
	EnumeratorContainer<std::vector<String>,String> container_;
	bool allowsMultiSelect_;
	bool fileMustExist_;
	Control* owner_;
	String selectedFilter_;
	NavDialogCreationOptions openDlgOptions_;
	int selectedFileTypeIndex_;
	
	void buildFileTypesMap();
	
	bool matchFileType( NavFileOrFolderInfo* info, FSRef* fileRef );
	
	static pascal void openNavEventProc( NavEventCallbackMessage inSelector, NavCBRecPtr ioParams, 
										NavCallBackUserData	ioUserData);
										
	static pascal Boolean openFileFilterProc( AEDesc* theItem, void* info, NavCallBackUserData callBackUD, NavFilterModes filterMode );
};


};


#endif // _VCF_OSXFILEOPENDIALOG_H__

/**
$Id$
*/
