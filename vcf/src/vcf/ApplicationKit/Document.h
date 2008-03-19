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
\class ModelEvent Model.h "vcf/ApplicationKit/Model.h"
*/
class APPLICATIONKIT_API DocumentEvent : public Event {
public:
	DocumentEvent( Object* source, const uint32& type ) :
	  Event( source, type ) {

	  }

	DocumentEvent( Object* source ) : Event(source){}

	virtual ~DocumentEvent(){};

	virtual Object* clone( bool deep=false ) {
		return new DocumentEvent(*this);
	}
};


typedef Delegate1<DocumentEvent*> DocumentDelegate; 


/**
\class Document Document.h "vcf/ApplicationKit/Document.h"
A document is a component that interacts with a valid model
instance and has many extra features like saving, loading, cutting 
no implemented within the scope of a model.
*/
class APPLICATIONKIT_API Document : public Component {

public:
	enum DocumentEvents{
		deSaved = Model::MODEL_LAST_EVENT + 100,
		deOpened
	};

public:

	DELEGATE(DocumentDelegate,DocumentChanged)

	/**
	* the document's constructor
	*/
	Document():docWindow_(NULL),
				docModel_(NULL),
				fileName_(""),
				modified_(false),
				keepBackUpFile_(false) {
	}

	virtual ~Document(){}

	/**
	* empties the model
	*/
	
	virtual void empty() {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return;
		}

		setModified( true );

		docModel->empty();
	}

	void addView( View* view ) {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return;
		}

		docModel->addView( view );
	}

	void updateAllViews() {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return;
		}

		docModel->updateAllViews();
	}

	void modelChanged( ModelEvent* e ) {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return;
		}
		
		docModel->ModelChanged( e );
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

	Model* getModel() {
		return docModel_;//dynamic_cast<Model*>(this);
	}

	void setModel( Model* val ) {
		docModel_ = val;
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
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return false;
		}

		FileOutputStream fs( fileName );

		bool result = saveAsType( fileType, fs );
		if ( result ) {
			setModified( false );
			DocumentEvent e( this, Document::deSaved );
			DocumentChanged(&e);
		}
		return result;
	};

	/**
	* saves the document as a specified type of file. The output stream is also specified.
	*@param const String& fileType, the type of file to be saved as.
	*@param OutputStream& stream, the output stream to be saved into.
	*@return bool, true if the file has been succesfully saved.
	*/
	virtual bool saveAsType( const MIMEType& fileType, OutputStream& stream ) {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL != docModel ) {
			Persistable* persistable = dynamic_cast<Persistable*>( docModel );

			if ( NULL != persistable ) {
				try {
					persistable->saveToStream( &stream, fileType );
				}
				catch ( std::exception& ) {
					return false;
				}
				
				return true;
			}
		}

		
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
	virtual bool openFromType( const String& fileName, const MIMEType& fileType ){
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return false;
		}

		bool result = false;
		try {
			FileInputStream fs( fileName );

			result = openFromType( fileType, fs );

			// releases the lock as soon as possible
			fs.close();

			if ( result ) {
				setModified( false );
				updateAllViews();

				DocumentEvent e( this, Document::deOpened );
				DocumentChanged(&e);
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
	virtual bool openFromType( const MIMEType& fileType, InputStream& stream ){
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );

		if ( NULL != docModel ) {
			Persistable* persistable = dynamic_cast<Persistable*>( docModel );

			if ( NULL != persistable ) {
				try {
					persistable->loadFromStream( &stream, fileType );
				}
				catch ( std::exception& ) {
					return false;
				}
				
				return true;
			}
		}

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
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return false;
		}

		return docModel->isEmpty();
	}

	/**
	* tells if we can perform a copy operation on the document.
	* By default a document has not thisoperation enabled.
	*@return bool returns true if it does, false if it doesn't
	*/
	virtual bool canCopyFromDocument() {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return false;
		}


		return docModel->isEmpty();
	}

	/**
	* tells if we can perform a paste operation on the document.
	* By default a document has not thisoperation enabled.
	*@return bool returns true if it does, false if it doesn't
	*/
	virtual bool canPasteToDocument() {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return false;
		}


		Clipboard* clipboard = UIToolkit::getSystemClipboard();
		
		for ( size_t i=0;i<clipFormats_.size();i++ ) {
			if ( clipboard->hasDataType( clipFormats_[i] ) ) {
				return true;
			}
		}

		return false;
	}

	/**
	* performs a cut operation on the document and returns the cut object.
	*@return DataObject*, a pointer to the data that has been cut.
	*/
	virtual DataObject* cut() {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return NULL;
		}

		return NULL;
	}

	/**
	* performs a copy operation on the document and returns the copied object.
	*@return DataObject*, a pointer to the data that has been copied.
	*/
	virtual DataObject* copy() {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return NULL;
		}

		return NULL;
	}

	/**
	* performs a past operation on the document.
	*@param DataObject*, a pointer to the data to paste.
	*@return bool, true if the operation has been performed successfully.
	*/
	virtual bool paste( DataObject* data ) {
		Model* docModel = getModel();
		VCF_ASSERT( NULL != docModel );
		
		if ( NULL == docModel ) {
			return NULL;
		}

		return false;
	}

	/**
	* gets the enumerator of the clip formats supported by the document.
	* This document will be able to cut & paste data from the clipboard
	* of the OS only for these specified formats.
	*@return Enumerator<String>*, the enumerator.
	*/
	Enumerator<MIMEType>* getSupportedClipboardFormats() {
		return clipFormats_.getEnumerator();
	}

	/**
	* adds a clip format to the list of supported formats.
	*@param String, the string identifying the clip format to be added.
	*/
	void addSupportedClipboardFormat( const MIMEType& type ) {
		clipFormats_.push_back( type );
	}

protected:
	/* the window associated to the document */
	Window* docWindow_;
	Model* docModel_;

	FilePath fileName_;

	bool modified_;
	bool keepBackUpFile_;

	/* the clipboard formats */
	Array<MIMEType> clipFormats_;
};



};


#endif // _VCF_DOCUMENT_H__

/**
$Id$
*/
