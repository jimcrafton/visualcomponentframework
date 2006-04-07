#ifndef _VCF_DOCUMENT_H__
#define _VCF_DOCUMENT_H__
//Document.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define DOCUMENT_CLASSID		"4c5ca064-5a3e-4d0a-bbe9-f37d722af092"

/**
\class Document Document.h "vcf/ApplicationKit/Document.h"
A document is a model has many extra features like saving, loading, cutting 
and all that kind of stuff.
*/
class APPLICATIONKIT_API Document : public AbstractModel {

public:
	enum DocumentEvents{
		deSaved = Model::MODEL_LAST_EVENT + 100,
		deOpened
	};

public:
	/**
	* the document's constructor
	*/
	Document():AbstractModel(), docWindow_(NULL),
				modified_(false),
				keepBackUpFile_(false),
				fileName_("") {
		clipFormatContainer_.initContainer(clipFormats_);
	}

	/**
	* empties the model
	*/
	virtual void empty() {
		setModified( true );

		AbstractModel::empty();
	}

	/**
	* tells is the document has been modified since the last time it has been saved
	*@return bool returns true if it has been modified
	*/
	bool isModified() {
		return modified_;
	}

	/**
	* sets the modification flag for the document.
	*@param bool true, to set the document as modified.
	*/
	void setModified( bool val ) {
		modified_ = val;
	}

	/**
	* gets the basename associated to the document in the file system.
	* This is the name of the file without its path component
	*@return String, the filename.
	*/
	virtual String getName() {
		return fileName_.getBaseName(true);
	}

	/**
	* sets the basename to be associated to the document.
	* This is the name of the file without its path component.
	* The full filename, which is accordingly updated, keeps the same 
	* path component of the previous filename.
	*@param String, the filename.
	*/
	virtual void setName( const String& name ) {
		FilePath fp = name;

		fileName_ = fileName_.getPathName(true) + fp.getBaseName(true);
		if ( fp.getExtension().empty() ) {
			fileName_ = fileName_.getFileName() + fileName_.getExtension();
		}
	}

	/**
	* gets the full filename associated to the document in the file system.
	*@return String, the filename.
	*/
	String getFileName() {
		return (String)fileName_;
	}

	/**
	* sets the full filename associated to the document in the file system.
	*@param const String&, the filename.
	*/
	void setFileName( const String& fileName ) {
		fileName_ = fileName;
	}

	/**
	* gets the window associated to the document.
	*@return Window*, the pointer to the associated window.
	*/
	Window* getWindow() {
		return docWindow_;
	}

	/**
	* sets the window to be associated to the document.
	*@param Window*, the pointer to window to be associated.
	*/
	void setWindow( Window* val ) {
		docWindow_ = val;
	}

	/**
	* callback function called by the document manager framework
	* as soon as a new document has been successfully created.
	* Override this to initializations specific of your document.
	*/
	virtual void initNew() = 0;


	/**
	* saves the document as a specified type of file with a name that could be
	* different than the current name for the document.
	* We may need to save the document as a different type without renaming this
	* document, so it is let to the user to call setFileName() first if he needs.
	*@param const String& fileName, the filename to be saved as.
	*@param const String& fileType, the type of file to be saved as.
	*@return bool, true if the file has been succesfully saved.
	*/
	virtual bool saveAsType( const String& fileName, const String& fileType ){
		FileOutputStream fs( fileName );

		bool result = saveAsType( fileType, fs );
		if ( result ) {
			setModified( false );
			ModelEvent e( this, Document::deSaved );
			ModelChanged.fireEvent( &e );
		}
		return result;
	};

	/**
	* saves the document as a specified type of file. The output stream is also specified.
	*@param const String& fileType, the type of file to be saved as.
	*@param OutputStream& stream, the output stream to be saved into.
	*@return bool, true if the file has been succesfully saved.
	*/
	virtual bool saveAsType( const String& fileType, OutputStream& stream ) {
		return false;
	};

	/**
	* this actually opens/loads the file associated to the document.
	* It calls a custom function specific to the document that appropriately
	* opens and manages the file.
	*@param const String& fileName, the filename to open.
	*@param const String& fileType, the type of file to be open as.
	*@return bool, true if the file has been succesfully opened.
	*@fire ModelChanged.
	*@eventtype Document::deOpened.
	*/
	virtual bool openFromType( const String& fileName, const String& fileType ){
		bool result = false;
		try {
			FileInputStream fs( fileName );

			result = openFromType( fileType, fs );

			// releases the lock as soon as possible
			fs.close();

			if ( result ) {
				setModified( false );
				updateAllViews();

				ModelEvent e( this, Document::deOpened );
				ModelChanged.fireEvent( &e );
			}
		}
		catch ( BasicException& be ) {
			StringUtils::trace( "Document::openFromType() failed to open " + fileName + ", type: " + fileType + "\n" + be.getMessage() );
		}

		return result;
	};

	/**
	* opens the document from an input stream. The type of file has to be specified too, 
	*because this tells how to treat the stream.
	*@param const String& fileType, the type of file to be open as.
	*@param const InputStream& stream, the input stream.
	*@return bool, true if the file has been succesfully opened.
	*/
	virtual bool openFromType( const String& fileType, InputStream& stream ){
		return false;
	};


	/**
	* tells if we keep a backup copy of the file when saving the document.
	*@return bool, true if we keep a backup copy of the document.
	*/
	bool getKeepsBackUpFile() {
		return keepBackUpFile_;
	}

	/**
	* sets the flag stating that we want to keep a backup copy of the file when 
	* saving the document.
	*@param bool, true if we want to keep a backup copy of the document.
	*/
	void setKeepsBackUpFile( const bool& val ) {
		keepBackUpFile_ = val;
	}

	/**
	* tells if we can perform a cut operation on the document.
	* By default a document has not thisoperation enabled.
	*@return bool returns true if it does, false if it doesn't
	*/
	virtual bool canCutFromDocument() {
		return false;
	}

	/**
	* tells if we can perform a copy operation on the document.
	* By default a document has not thisoperation enabled.
	*@return bool returns true if it does, false if it doesn't
	*/
	virtual bool canCopyFromDocument() {
		return false;
	}

	/**
	* tells if we can perform a paste operation on the document.
	* By default a document has not thisoperation enabled.
	*@return bool returns true if it does, false if it doesn't
	*/
	virtual bool canPasteToDocument() {
		return false;
	}

	/**
	* performs a cut operation on the document and returns the cut object.
	*@return DataObject*, a pointer to the data that has been cut.
	*/
	virtual DataObject* cut() {
		return NULL;
	}

	/**
	* performs a copy operation on the document and returns the copied object.
	*@return DataObject*, a pointer to the data that has been copied.
	*/
	virtual DataObject* copy() {
		return NULL;
	}

	/**
	* performs a past operation on the document.
	*@param DataObject*, a pointer to the data to paste.
	*@return bool, true if the operation has been performed successfully.
	*/
	virtual bool paste( DataObject* data ) {
		return false;
	}

	/**
	* gets the enumerator of the clip formats supported by the document.
	* This document will be able to cut & paste data from the clipboard
	* of the OS only for these specified formats.
	*@return Enumerator<String>*, the enumerator.
	*/
	Enumerator<String>* getSupportedClipboardFormats() {
		return clipFormatContainer_.getEnumerator();
	}

	/**
	* adds a clip format to the list of supported formats.
	*@param String, the string identifying the clip format to be added.
	*/
	void addSupportedClipboardFormat( const String& type ) {
		clipFormats_.push_back( type );
	}

protected:
	/* the window associated to the document */
	Window* docWindow_;

	FilePath fileName_;

	bool modified_;
	bool keepBackUpFile_;

	/* the clipboard formats */
	std::vector<String> clipFormats_;
	EnumeratorContainer<std::vector<String>,String> clipFormatContainer_;
};



};


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.5.2.1  2005/07/30 17:01:09  iamfraggle
*get/setName made explicitly virtual
*
*Revision 1.5  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/20 23:23:18  marcelloptr
*openFromType releases the lock asap
*
*Revision 1.3.2.1  2004/12/20 23:23:18  marcelloptr
*openFromType releases the lock asap
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/11/13 22:37:36  marcelloptr
*more documentation
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.2  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3.4.1  2004/04/12 20:23:15  ddiego
*fixed some exception handling in Document and
*DocumentManager when opening a file.
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.4  2003/09/22 01:48:03  ddiego
*some minor additions ot the DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.2.2.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to the bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.2.2.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.2.1  2003/08/27 20:11:49  ddiego
*adjustments to how the DataObject class work and copy/paste
*
*Revision 1.2  2003/08/09 02:56:42  ddiego
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
*Revision 1.1.2.4  2003/08/06 21:26:16  ddiego
*minor changes to doc stuff
*
*Revision 1.1.2.3  2003/08/02 00:41:12  marcelloptr
*fixes for vc6;  improved dependencies
*
*Revision 1.1.2.2  2003/07/16 04:58:47  ddiego
*added some changes to the fil and stroke classes to allow changing whether
*they use anti-aliasing or not. Also implemented Matrix2D::invert(),
*plus properly implemented clone() on the DefaultMenuItem class.
*
*Revision 1.1.2.1  2003/07/06 01:20:29  ddiego
*added basic Document/View classes. These are based on the existing MVC
*architecture already present in the framework already, and exapnd on the
*existing functionality. Many of the ideas were influenced by the NeXT/Cocoa's
*Document/View architecture. Some of the new features are:
*  automatic creation and connection of the various parts including the
*  Document, view and Window.
*  Automatic default menu items, to ensure standard UI conformance. The menu
*  items are merged with an existing ones.
*  Automatic clipboard support in the form of cut/copy/paste and connecting this
*  directly to the current document
*  Support for Undo/Redo item as well, including default menu item validation
*  Default support for opening and saving documents, including presenting the
*  correct Dialogs to the User, and properly filling the default data, based
*  on the documents data.
*  Support for multiple document types
*  Support for differnt Document Interface policies. Currently we support
*  SDI (Single Document Interface) and MDI (Multiple Document Interface)
*
*/


#endif // _VCF_DOCUMENT_H__


