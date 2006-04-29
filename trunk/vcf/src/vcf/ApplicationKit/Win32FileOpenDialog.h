#ifndef _VCF_WIN32FILEOPENDIALOG_H__
#define _VCF_WIN32FILEOPENDIALOG_H__
//Win32FileOpenDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class Win32FileOpenDialog : public CommonFileDialogPeer, public Object {
public:
	Win32FileOpenDialog( Control* owner=NULL );

	virtual ~Win32FileOpenDialog();

	void init();

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

private:
	bool executeW();
	bool executeA();

private:
	String title_;
	std::vector<String> filter_;
	std::vector<String> selectedFiles_;
	String directory_;
	String selectedFileExt_;
	String fileName_;
	EnumeratorContainer<std::vector<String>,String> container_;
	bool allowsMultiSelect_;
	bool fileMustExist_;
	Control* owner_;
	String selectedFilter_;

};


}; // namespace VCF


#endif // _VCF_WIN32FILEOPENDIALOG_H__

/**
$Id$
*/
