#ifndef _VCF_GTKFILEOPENDIALOG_H__
#define _VCF_GTKFILEOPENDIALOG_H__
//GTKFileOpenDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
class GTKFileOpenDialog documentation
*/
class GTKFileOpenDialog : public CommonFileDialogPeer, public Object {
public:
	GTKFileOpenDialog( Control* owner=NULL );

	virtual ~GTKFileOpenDialog();

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

	virtual void setFileMustExist( const bool& fileMustExist ) {
		fileMustExist_ = fileMustExist;
	}
protected:
	String title_;
	std::vector<String> filter_;
	std::vector<String> selectedFiles_;
	String directory_;
	String selectedFileExt_;
	String fileName_;
	EnumeratorContainer<std::vector<String>,String> container_;
	bool allowsMultiSelect_;
	Control* owner_;
	String selectedFilter_;
	bool fileMustExist_;

	static gboolean onDestroyGtkFileSelector( GtkWidget *widget );
};



};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.2  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.5.2.1  2003/08/25 03:13:44  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.5  2003/08/09 02:56:44  ddiego
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
*Revision 1.4.2.1  2003/07/14 22:52:40  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*/


#endif // _VCF_GTKFILEOPENDIALOG_H__


