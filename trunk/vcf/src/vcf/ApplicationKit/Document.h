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
class Document documentation
*/
class APPLICATIONKIT_API Document : public AbstractModel {
public:


	Document():AbstractModel(), docWindow_(NULL),
				modified_(false),
				keepBackUpFile_(false),
				fileName_("") {
		clipFormatContainer_.initContainer(clipFormats_);
	}

	enum DocumentEvents{
		deSaved = Model::MODEL_LAST_EVENT + 100,
		deOpened
	};

	virtual void empty() {
		setModified( true );

		AbstractModel::empty();
	}


	bool isModified() {
		return modified_;
	}

	void setModified( bool val ) {
		modified_ = val;
	}

	String getName() {
		return fileName_.getBaseName(true);
	}

	void setName( const String& name ) {
		FilePath fp = name;

		fileName_ = fileName_.getPathName(true) + fp.getBaseName(true);
		if ( fp.getExtension().empty() ) {
			fileName_ = fileName_.getFileName() + fileName_.getExtension();
		}
	}

	String getFileName() {
		return (String)fileName_;
	}

	void setFileName( const String& fileName ) {
		fileName_ = fileName;
	}

	Window* getWindow() {
		return docWindow_;
	}

	void setWindow( Window* val ) {
		docWindow_ = val;
	}

	virtual void initNew() = 0;


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

	virtual bool saveAsType( const String& fileType, OutputStream& stream ){
		return false;
	};

	virtual bool openFromType( const String& fileName, const String& fileType ){
		bool result = false;
		try {
			FileInputStream fs( fileName );
			result = openFromType( fileType, fs );

			if ( result ) {
				setModified( false );
				updateAllViews();

				ModelEvent e( this, Document::deOpened );
				ModelChanged.fireEvent( &e );
			}
		}
		catch ( BasicException& ) {
			StringUtils::trace( "Document::openFromType() failed to open " + fileName + ", type: " + fileType + "\n" );
		}

		return result;
	};

	virtual bool openFromType( const String& fileType, InputStream& stream ){
		return false;
	};



	bool getKeepsBackUpFile() {
		return keepBackUpFile_;
	}

	void setKeepsBackUpFile( const bool& val ) {
		keepBackUpFile_ = val;
	}

	virtual bool canCutFromDocument() {
		return false;
	}

	virtual bool canCopyFromDocument() {
		return false;
	}

	virtual bool canPasteToDocument() {
		return false;
	}

	virtual DataObject* cut() {
		return NULL;
	}

	virtual DataObject* copy() {
		return NULL;
	}

	virtual bool paste( DataObject* data ) {
		return false;
	}

	Enumerator<String>* getSupportedClipboardFormats() {
		return clipFormatContainer_.getEnumerator();
	}

	void addSupportedClipboardFormat( const String& type ) {
		clipFormats_.push_back( type );
	}
protected:
	Window* docWindow_;

	FilePath fileName_;
	bool modified_;
	bool keepBackUpFile_;
	std::vector<String> clipFormats_;
	EnumeratorContainer<std::vector<String>,String> clipFormatContainer_;
};



};


/**
*CVS Log info
*$Log$
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
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.2.2.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
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
*adjustments to how hte DataObject class work and copy/paste
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


