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


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.2.1  2005/11/27 23:55:44  ddiego
*more osx updates.
*
*Revision 1.2  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.2  2005/06/27 03:28:54  ddiego
*more osx work.
*
*Revision 1.1.2.1  2005/06/15 15:41:13  ddiego
*minor osx stuff
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
*Revision 1.6.4.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
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
*Revision 1.4.24.2  2003/06/27 03:10:58  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.4.24.1  2003/05/25 19:07:11  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_OSXCLIPBOARD_H__


