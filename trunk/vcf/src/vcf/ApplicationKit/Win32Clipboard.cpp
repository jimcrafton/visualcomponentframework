//Win32Clipboard.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32Clipboard.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Clipboard.h"
#include "vcf/ApplicationKit/Win32COMDataObject.h"
#include "vcf/ApplicationKit/Win32COMUtils.h"


using namespace VCF;



Win32Clipboard::Win32Clipboard()
{

}

Win32Clipboard::~Win32Clipboard()
{
	HRESULT hr = OleFlushClipboard();
	if ( !SUCCEEDED(hr) ) {
		//report the error ?
	}
}

void Win32Clipboard::copy( VCF::DataObject* data )
{
	VCFCOM::COMDataObject* dataObj = new VCFCOM::COMDataObject();

	dataObj->setDataObject( data );

	HRESULT hr = ::OleSetClipboard( dataObj );
	if ( !SUCCEEDED(hr) ) {
	}
}




VCF::DataObject* Win32Clipboard::paste( const String& dataType )
{
	VCF::DataObject* result = NULL;

	IDataObject* oleDataObject = NULL;
	HRESULT hr = ::OleGetClipboard( &oleDataObject );
	if ( (SUCCEEDED(hr)) && (NULL != oleDataObject) ) {
		FORMATETC fmtETC = translateDataTypeToWin32( dataType );
		result = VCFCOM::COMUtils::getDataObjectFromOLEDataObject( dataType, oleDataObject, &fmtETC );

		oleDataObject->Release();
	}
	else {
		//throw exception
	}
	return result;
}

bool Win32Clipboard::hasDataType( const String& dataType )
{
	bool result = false;

	IDataObject* oleDataObject = NULL;
	HRESULT hr = ::OleGetClipboard( &oleDataObject );
	if ( (SUCCEEDED(hr)) && (NULL != oleDataObject) ) {
		FORMATETC fmtETC = translateDataTypeToWin32( dataType );

		hr = oleDataObject->QueryGetData( &fmtETC );
		if ( SUCCEEDED(hr) ) {
			result = true;
		}
	}

	return result;
}

FORMATETC Win32Clipboard::translateDataTypeToWin32( const String& dataType )
{

	return VCFCOM::COMUtils::translateDataTypeToWin32( dataType );
}


/**
$Id$
*/
