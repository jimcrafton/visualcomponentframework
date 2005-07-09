#ifndef _VCF_COMMONDIALOGPEER_H__
#define _VCF_COMMONDIALOGPEER_H__
//CommonDialogPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Color;

class Font;

/**
*
*/
class APPLICATIONKIT_API CommonDialogPeer : public Interface{
public:
	virtual ~CommonDialogPeer(){};

	virtual void setTitle( const String& title ) = 0;

	virtual bool execute() = 0;
};


/**
*
*/
class APPLICATIONKIT_API CommonFileDialogPeer : public CommonDialogPeer{
public:
	virtual ~CommonFileDialogPeer(){};

	virtual void addFilter( const String & description, const String & extension ) = 0;

	virtual void setDirectory( const String & directory ) = 0;

	virtual void setFileName( const String & filename ) = 0;

	virtual String getFileName() = 0;

	virtual String getDirectory() = 0;

	virtual String getFileExtension() = 0;

	virtual uint32 getSelectedFileCount() = 0;

	virtual Enumerator<String>* getSelectedFiles() = 0;

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect ) = 0;

	virtual String getSelectedFilter() = 0;

	virtual void setSelectedFilter( const String& selectedFilter ) = 0;

	virtual void setFileMustExist( const bool& fileMustExist ) = 0;
};

/**
*
*/
class APPLICATIONKIT_API CommonFolderBrowseDialogPeer : public CommonDialogPeer{
public:
	virtual ~CommonFolderBrowseDialogPeer(){};

	virtual void setDirectory( const String & directory ) = 0;

	virtual String getDirectory() = 0;

};

/**
*
*/
class APPLICATIONKIT_API CommonColorDialogPeer : public CommonDialogPeer {
public:
	virtual ~CommonColorDialogPeer(){};

	virtual Color* getSelectedColor() = 0;

	virtual void setSelectedColor( Color* selectedColor ) = 0;

};


/**
*
*/
class APPLICATIONKIT_API CommonPrintDialogPeer : public CommonDialogPeer {
public:
	virtual ~CommonPrintDialogPeer(){};
	
	virtual void setPrintInfo( PrintInfoHandle info ) = 0;
	
	virtual PrintInfoHandle getPrintInfo() = 0;

	virtual void setNumberOfCopies( const ulong32& val ) = 0;
	virtual ulong32 getNumberOfCopies() = 0;
	
	virtual void setStartPage( const ulong32& val ) = 0;
	virtual ulong32 getStartPage() = 0;

	virtual void setEndPage( const ulong32& val ) = 0;
	virtual ulong32 getEndPage() = 0;

	virtual void setPrintJobType( PrintSession::PrintJob val ) = 0;
	virtual PrintSession::PrintJob getPrintJobType() = 0;
};


/**
*
*/
class APPLICATIONKIT_API CommonFontDialogPeer : public CommonDialogPeer {
public:
	virtual ~CommonFontDialogPeer(){};

	virtual Font* getSelectedFont() = 0;

	virtual void setSelectedFont( Font* selectedFont ) = 0;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/04/09 17:20:35  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.2.4  2003/09/17 03:27:56  ddiego
*added a fix for bug [ 807416 ] CommonFileDialog needs setFileExtension
*added methods for getting data from the open and save dialogs in the
*DocumentManager
*
*Revision 1.9.2.3  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9.2.2  2003/08/23 02:01:28  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.9.2.1  2003/08/17 18:18:06  ddiego
*added some of Marcellos fixes, notably the one to fix CRLF problems in teh
*edit control
*
*Revision 1.9  2003/08/09 02:56:44  ddiego
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
*Revision 1.8.2.1  2003/06/30 02:53:15  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.8  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2002/12/25 22:06:28  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMMONDIALOGPEER_H__


