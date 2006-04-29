#ifndef _VCF_WIN32CLIPBOARD_H__
#define _VCF_WIN32CLIPBOARD_H__
//Win32Clipboard.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class DataType;
/**
*Class Win32Clipboard documentation
*/
class Win32Clipboard : public ClipboardPeer {
public:
	Win32Clipboard();

	virtual ~Win32Clipboard();

	virtual void copy( DataObject* data );

	virtual DataObject* paste( const String& dataType );

	virtual bool hasDataType( const String& dataType );


protected:
	FORMATETC translateDataTypeToWin32( const String& dataType );

};


}; //end of namespace VCF


#endif // _VCF_WIN32CLIPBOARD_H__

/**
$Id$
*/
