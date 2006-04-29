#ifndef _VCF_WIN32FILESAVEDIALOG_H__
#define _VCF_WIN32FILESAVEDIALOG_H__
//Win32FileSaveDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//Win32FileSaveDialog

namespace VCF {


class Win32FileSaveDialog : public CommonFileDialogPeer, public Object {
public:
	Win32FileSaveDialog( Control* owner=NULL );

	virtual ~Win32FileSaveDialog();

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

	/**
	* Returns a pointer to an enumerator listing
	* all the files selected in the dialog.
	* If the multiple selection is not allowed for the dialog, 
	* then this list may be empty, as it happens in the default
	* implementation.
	*@return Enumerator<String>*, the pointer to the enumerator.
	*/
	virtual Enumerator<String>* getSelectedFiles();

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );

	virtual String getSelectedFilter() {
		return selectedFilter_;
	}

	virtual void setSelectedFilter( const String& selectedFilter );

	/**
	* The dialog will accept a filename only if it exists.
	* The default implementation is empty as this is used only
	* with a dialog opening a file.
	*/
	virtual void setFileMustExist( const bool& fileMustExist ){}

private:
	bool executeW();
	bool executeA();

private:
	String title_;
	std::vector<String> filter_;
	std::vector<String> selectedFiles_;
	String directory_;
	String fileName_;
	EnumeratorContainer<std::vector<String>,String> container_;
	bool allowsMultiSelect_;
	Control* owner_;

	String selectedFilter_;
};


}; // namespace VCF


#endif // _VCF_WIN32FILESAVEDIALOG_H__

/**
$Id$
*/
