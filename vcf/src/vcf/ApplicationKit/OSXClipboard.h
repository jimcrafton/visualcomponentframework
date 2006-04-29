#ifndef _VCF_OSXCLIPBOARD_H__
#define _VCF_OSXCLIPBOARD_H__
//OSXClipboard.h

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
*Class OSXClipboard documentation
*/
class OSXClipboard : public ClipboardPeer {
public:
	OSXClipboard();

	virtual ~OSXClipboard();

	virtual void copy( DataObject* data );

	virtual DataObject* paste( const String& dataType );

	virtual bool hasDataType( const String& dataType );

	static DataObject* createDataObjectFromPasteBoard( PasteboardRef pasteBoard );
	static void initDataObjectFromPasteBoard( PasteboardRef pasteBoard, DataObject* dataObject );
protected:
	CFRefObject<PasteboardRef> globalPasteBoard_;

};


}; //end of namespace VCF


#endif // _VCF_OSXCLIPBOARD_H__

/**
$Id$
*/
