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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/02/19 19:38:12  ddiego
*adjusted some comet code to make it compile again. renamed some of the COM utility files to have a Win32 prefix.
*
*Revision 1.2.6.1  2005/08/12 03:13:44  ddiego
*minor changes
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.12  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.2.1  2003/08/27 20:11:49  ddiego
*adjustments to how hte DataObject class work and copy/paste
*
*Revision 1.11  2003/08/09 02:56:46  ddiego
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
*Revision 1.10.2.4  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10.2.3  2003/06/27 03:10:59  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.10.2.2  2003/05/25 20:01:08  ddiego
*oops - missed some #include changes from moving the files from one directory to
*the other! This fixes that (related to the drag-drop bug fixing and clean up)
*
*Revision 1.10.2.1  2003/05/25 19:07:13  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.10  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.8.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.8  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/04/27 15:52:25  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.7  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.6  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


