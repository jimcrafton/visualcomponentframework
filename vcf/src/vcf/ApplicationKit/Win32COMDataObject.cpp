//COMDataObject.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/VCFCOM.h"
#include "vcf/ApplicationKit/Win32ComUtils.h"
#include "vcf/ApplicationKit/Win32COMDataObject.h"


using namespace VCFCOM;
using namespace VCF;


DataRendering::DataRendering()
{
	memset( &formatETC_, 0, sizeof(formatETC_) );
	memset( &storage_, 0, sizeof(storage_) );
	owner_ = NULL;

}

DataRendering::DataRendering( FORMATETC * formatETC, STGMEDIUM * stgMedium, IUnknown* newStorageOwner ):
	Object()
{
	memset( &formatETC_, 0, sizeof(formatETC_) );
	memset( &storage_, 0, sizeof(storage_) );
	owner_ = NULL;

	formatETC_ = *formatETC;
	storage_ = *stgMedium;
	owner_ = stgMedium->pUnkForRelease;
	storage_.pUnkForRelease = newStorageOwner;
}

DataRendering::~DataRendering()
{
	if ( NULL != owner_ ){
		owner_->Release();
		owner_ = NULL;
	}
}

VCF::String DataRendering::toString()
{
	VCF::String result;
	//result = format( "DataRendering @ %p \n", this );
	switch ( formatETC_.cfFormat ){
	case CF_BITMAP:{
		result += "formatETC_.cfFormat = CF_BITMAP";
				   }
		break;

	case CF_DIB:{
		result += "formatETC_.cfFormat = CF_DIB";
				}
		break;

	case CF_DIF:{
		result += "formatETC_.cfFormat = CF_DIF";
				}
		break;

	case CF_HDROP:{
		result += "formatETC_.cfFormat = CF_HDROP";
				  }
		break;

	case CF_METAFILEPICT:{
		result += "formatETC_.cfFormat = CF_METAFILEPICT";
						 }
		break;

	case CF_OEMTEXT:{
		result += "formatETC_.cfFormat = CF_OEMTEXT";
					}
		break;

	case CF_TEXT:{
		result += "formatETC_.cfFormat = CF_TEXT";
				 }
		break;

	case CF_WAVE:{
		result += "formatETC_.cfFormat = CF_WAVE";
				 }
		break;

	case CF_TIFF:{
		result += "formatETC_.cfFormat = CF_TIFF";
				 }
		break;
	};
	return result;
}

/**
*COMDataObject
*/

COMDataObject::COMDataObject( IDataObject* outerDataObject ):
	ref_(0),
	dataObj_(NULL),
	outerDataObject_(outerDataObject)
{

}

COMDataObject::~COMDataObject()
{
	
}


STDMETHODIMP COMDataObject::GetData( FORMATETC * formatETC, STGMEDIUM * stgMedium )
{
	HRESULT result = E_FAIL;

	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->GetData( formatETC, stgMedium );
	}
	else {
		if ( (NULL == formatETC) || (NULL == stgMedium) ){
			result = DATA_E_FORMATETC;
		}
		else{
			result = DATA_E_FORMATETC;

			DataRendering dataRender = findDataRenderingForType( formatETC );

			if ( !dataRender.isEmpty() ){
				if ( TYMED_ISTORAGE == dataRender.formatETC_.tymed ){
					dataRender.storage_.pstg->AddRef();
				}
				if ( TYMED_ISTREAM == dataRender.formatETC_.tymed){
					dataRender.storage_.pstm->AddRef();
				}

				*stgMedium = dataRender.storage_;
				
				AddRef();

				result = S_OK;
			}
		}
	}
	return result;
}

STDMETHODIMP COMDataObject::GetDataHere( FORMATETC * formatETC, STGMEDIUM * stgMedium )
{
	HRESULT result = E_NOTIMPL;

	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->GetDataHere( formatETC, stgMedium );
	}
	return result;
}

STDMETHODIMP COMDataObject::QueryGetData( FORMATETC * formatETC )
{

	HRESULT result = E_FAIL;


	if ( NULL==formatETC ){
        return DATA_E_FORMATETC;
	}

	if ( !findDataRenderingForType( formatETC ).isEmpty() ){
		result = S_OK;//NOERROR;
	}
	else {
		result = DATA_E_FORMATETC;
	}

	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->QueryGetData( formatETC );
	}
	return result;
}

STDMETHODIMP COMDataObject::GetCanonicalFormatEtc( FORMATETC * formatETCIn, FORMATETC * formatETCOut )
{
	HRESULT result = DATA_S_SAMEFORMATETC;

	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->GetCanonicalFormatEtc( formatETCIn, formatETCOut );
	}

	return result;
}

/**
* if the releaseData is false we cannot go on - Our data objects need to release the data.
*This may change in future releases.
*if the FormatETC or stgMedium passed in are NULL we should also quit - can't do anything
*otherwise we do the following:
*	1.) Create a data Rendering and add it to the vector renderings_.
*	2.)
*/
STDMETHODIMP COMDataObject::SetData( FORMATETC * formatETC, STGMEDIUM * stgMedium, BOOL releaseData )
{
	HRESULT result = E_NOTIMPL;
	//ClipboardDataObject_
	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->SetData( formatETC, stgMedium, releaseData );
	}
	else {
		if ( false  == releaseData ){
			result = E_FAIL;
		}
		else if ( (NULL==formatETC) || (NULL==stgMedium) ){
			//clean out the clipboard data
			result = E_FAIL;
		}
		else {
			renderings_.push_back( DataRendering( formatETC,  stgMedium, (IUnknown*)(this) ) );
			result = S_OK;
		}
	}
	return result;
}

STDMETHODIMP COMDataObject::EnumFormatEtc( DWORD dwDirection, IEnumFORMATETC ** ppenumFormatetc )
{

	HRESULT result = E_FAIL;

	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->EnumFormatEtc( dwDirection, ppenumFormatetc );
	}
	else {
		*ppenumFormatetc = NULL;
		EnumFormatETC* enumObj = NULL;
		switch ( dwDirection ){
			case DATADIR_GET:{
				enumObj = new EnumFormatETC();
			}
			break;

			case DATADIR_SET: default:{
				enumObj = NULL;
			}
			break;
		}

		if ( NULL == enumObj ){
			result = E_FAIL;
		}
		else{
			//Let the enumerator copy our format list.
			for ( std::vector<DataRendering>::iterator it = renderings_.begin(); it != renderings_.end(); it++ ){
				DataRendering& render = *it;
				enumObj->add( render.formatETC_ );
			}
			enumObj->Reset();
			enumObj->AddRef();

			result  = S_OK;
		}

		*ppenumFormatetc = dynamic_cast<IEnumFORMATETC*>(enumObj);
	}
	return result;
}

STDMETHODIMP COMDataObject::DAdvise( FORMATETC * formatETC, DWORD advf, IAdviseSink * pAdvSink,  DWORD * pdwConnection )
{
	HRESULT result = OLE_E_ADVISENOTSUPPORTED;
	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->DAdvise( formatETC, advf, pAdvSink, pdwConnection );
	}
	return result;
}

STDMETHODIMP COMDataObject::DUnadvise( DWORD dwConnection )
{
	HRESULT result = OLE_E_ADVISENOTSUPPORTED;
	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->DUnadvise( dwConnection );
	}
	return result ;
}

STDMETHODIMP COMDataObject::EnumDAdvise( IEnumSTATDATA ** ppenumAdvise )
{
	HRESULT result = OLE_E_ADVISENOTSUPPORTED;
	if ( NULL != outerDataObject_ ){
		result = outerDataObject_->EnumDAdvise( ppenumAdvise );
	}
	return result;
}

bool COMDataObject::isTypeSupported(const String& dataType)
{
	if ( NULL == dataObj_ ) {
		return false;
	}
	return dataObj_->isTypeSupported(dataType);
}

void COMDataObject::setDataObject( VCF::DataObject* data )
{
	dataObj_ = data;
	dataObj_->addRef();

	Enumerator<String>* types = dataObj_->getSupportedDataTypes();
	while ( types->hasMoreElements() ) {
		String type = types->nextElement();

		VCF::MemoryStream memStream;
		//Write the data to the mem stream

		if ( dataObj_->saveToStream( type, &memStream ) ) {
			memStream.seek( 0, stSeekFromStart );
			STGMEDIUM stgMedium;
			memset( &stgMedium, 0, sizeof(STGMEDIUM) );
			FORMATETC fmtETC = translateFrameworkFormatToFormatETC( type );
			stgMedium.tymed = fmtETC.tymed;
			//stgMedium.pUnkForRelease = AS_IUNKNOWN(this);
			stgMedium.hGlobal =
				::GlobalAlloc( GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, memStream.getSize() );


			if ( 0 != stgMedium.hGlobal ){
				unsigned char* globalMemPtr = (unsigned char*)::GlobalLock( stgMedium.hGlobal );
				if ( NULL != globalMemPtr ){
					memStream.read( globalMemPtr, memStream.getSize() );
				}
				GlobalUnlock( stgMedium.hGlobal );

				if ( S_OK != SetData( &fmtETC, &stgMedium, true ) ){
					//throw exception ?
				}
			}
		}
	}
}



DataRendering COMDataObject::findDataRenderingForType( FORMATETC* formatETC )
{
	DataRendering result;
	bool found = false;

	if ( NULL != formatETC ){

		for ( std::vector<DataRendering>::iterator it = renderings_.begin(); it != renderings_.end(); it++ ){
			DataRendering& dataRender = *it;

			found = (dataRender.formatETC_.cfFormat == formatETC->cfFormat);

			if ( true == found ){
				result = dataRender;
				break;
			}
		}
	}
	return result;
}

UINT COMDataObject::translateFrameworkFormat( const String& dataType )
{
	FORMATETC result = COMUtils::translateDataTypeToWin32( dataType );

	return result.cfFormat;
}

FORMATETC COMDataObject::translateFrameworkFormatToFormatETC( const String& dataType )
{
	return COMUtils::translateDataTypeToWin32( dataType );
}

String COMDataObject::translateClipboardFmt( const UINT& fmtType )
{
	String result = "";
	switch ( fmtType ){
		case CF_BITMAP:{
			result += "CF_BITMAP";
		}
		break;

		case CF_DIB:{
			result += "CF_DIB";
		}
		break;

		case CF_DIF:{
			result += "CF_DIF";
		}
		break;

		case CF_HDROP:{
			result += "CF_HDROP";
		}
		break;

		case CF_METAFILEPICT:{
			result += "CF_METAFILEPICT";
		}
		break;

		case CF_OEMTEXT:{
			result += "CF_OEMTEXT";
		}
		break;

		case CF_TEXT:{
			result += "CF_TEXT";
		}
		break;

		case CF_WAVE:{
			result += "CF_WAVE";
		}
		break;

		case CF_TIFF:{
			result += "CF_TIFF";
		}
		break;

		default:{
			char s[256];
			sprintf( s, " %d", fmtType );
			result = s;
		};
		break;
	};
	return result;
};


/**
$Id$
*/