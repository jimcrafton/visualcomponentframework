//Document.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//UIShell.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Document.h"
#include "vcf/ApplicationKit/DocumentManager.h"



using namespace VCF;


Document::Document():docWindow_(NULL),
	fileName_(""),
	modified_(false),
	keepBackUpFile_(false) 
{
	addCallback( new ClassProcedure1<Event*,Document>(this, &Document::internalModelChanged), "Document::internalModelChanged" );	
}


Document::~Document()
{
	DocumentManager::getDocumentManager()->unlinkDocumentToModel( this );
}

void Document::empty()
{
	Model* docModel = getModel();
	VCF_ASSERT( NULL != docModel );
	
	if ( NULL == docModel ) {
		return;
	}
	
	setModified( true );
	
	docModel->empty();
}	

void Document::addView( View* view )
{
	Model* docModel = getModel();
	VCF_ASSERT( NULL != docModel );
	
	if ( NULL == docModel ) {
		return;
	}
	
	docModel->addView( view );
}

void Document::updateAllViews()
{
	Model* docModel = getModel();
	VCF_ASSERT( NULL != docModel );
	
	if ( NULL == docModel ) {
		return;
	}
	
	docModel->updateAllViews();
}

void Document::modelChanged( ModelEvent* e )
{
	Model* docModel = getModel();
	VCF_ASSERT( NULL != docModel );
	
	if ( NULL == docModel ) {
		return;
	}
	
	docModel->ModelChanged( e );
}

Model* Document::getModel()
{
	return DocumentManager::getDocumentManager()->getModel( this );
}

void Document::setModel( Model* val )
{
	CallBack* cb = getCallback( "Document::internalModelChanged" );
	Model* model = DocumentManager::getDocumentManager()->getModel( this );
	if ( NULL != model ) {
		model->ModelChanged -= cb;
	}

	DocumentManager::getDocumentManager()->linkDocumentToModel( this, val );
	
	if ( NULL != val ) {
		val->ModelChanged += cb;
	}
}

bool Document::saveAsType( const String& fileName, const String& fileType )
{
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
}

bool Document::saveAsType( const MIMEType& fileType, OutputStream& stream )
{
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
}

bool Document::openFromType( const String& fileName, const MIMEType& fileType )
{
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
}

bool Document::openFromType( const MIMEType& fileType, InputStream& stream )
{
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
}

bool Document::canPasteToDocument()
{
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

DataObject* Document::copy()
{
	Model* docModel = getModel();
	VCF_ASSERT( NULL != docModel );
	
	if ( NULL == docModel ) {
		return NULL;
	}
	
	DataObject* result = NULL;
	
	for ( size_t i=0;i<clipFormats_.size();i++ ) {
		BasicOutputStream bos;
		
		if ( saveAsType( clipFormats_[i], bos ) ) {
			if ( NULL == result ) {
				result = new DataObject();
			}
			BinaryPersistable* persistable = new BinaryPersistable( bos.getBuffer(), bos.getSize() );
			result->addSupportedDataType( clipFormats_[i], persistable );
		}
	}
	
	return result;
}


/**
$Id$
*/
