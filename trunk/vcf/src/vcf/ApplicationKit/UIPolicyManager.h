#ifndef _VCF_UIPOLICYMANAGER_H__
#define _VCF_UIPOLICYMANAGER_H__
//UIPolicyManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
class Dialog;
/**
* class UIPolicyManager
*
* helper class for any document interface policy
* it manages things like merging menus, etc.
*/
class APPLICATIONKIT_API UIPolicyManager {
public:
	UIPolicyManager(){};
	virtual ~UIPolicyManager(){};


	/**
	These are a standard set of 
	accelerators types that are common
	to various windowing platforms.
	Use these values to determine the 
	proper accelerator key code and 
	modifier(s) to use rather than
	hard coding them.
	*/
	enum StandardAccelerator{
		saApplicationQuit = 1,
		saApplicationAbout,
		saApplicationPreferences,
		saFileNew,
		saFileOpen,
		saFileSave,		
		saFileSaveAs,		
		saFilePrint,
		saFilePageSetup,		
		saEditUndo,
		saEditRedo,
		saEditCut,
		saEditCopy,
		saEditPaste,
		saEditDelete,
		saEditSelectAll,
		saEditFind,
		saEditFindNext,		
		saHelpContents,
		saFileExit = saApplicationQuit,
		saEditFindAgain = saEditFindNext
	};


	/**
	* merges the appMenu into the windowMenu
	* - the windowMenu is filled with menu items clones of the menu items in appMenu
	* - the 'file' menu is always placed as the leftmost one ( if exists in the windowMenu )
	*   and the 'edit' menu just in the second place from the left ( if exists in the windowMenu )
	* - any other first-level windowMenu item is appended on the right 
	*   of the first-level appMenu items
	* - if two first-level manu itmes have the same caption, its subitems are merged together
	*@param Menu* appMenu, the 'source' menu
	*@param Menu* windowMenu, the 'destination' menu
	*/
	virtual void mergeMenus( Menu* appMenu, Menu* windowMenu ) = 0;

	virtual Frame* getOwnerForDialog() = 0;
	
	virtual Rect adjustInitialDialogBounds( Dialog* dialog ) = 0;

	/**
	\p
	This returns a transformed string that is suitable for passing to text 
	drawing API's when the input string has mnemonic values in it. This is
	platform dependant, so not all platforms will handle this the same way.
	\p
	For example, the string "&OK" is meant to have a mnemonic in front of 
	the "O". In Win32 this would be left alone, and the Win32 drawing API's
	will draw it correctly. On OSX this "&" character would be stripped out.
	*/
	virtual String transformMnemonicValues( const String& input ) = 0;

	/**
	Returns an AcceleratorKey::Value that represents the virtual key code
	and keyboard modifier(s) for the requested standard accelerator.
	Some platforms may not support all the accelerators in the
	StandardAccelerator enum, and if this is the case the returned
	value will be 0 and AcceleratorKey::Value::isEmpty() will return 
	true.
	*/
	virtual AcceleratorKey::Value getStandardAcceleratorFor( const StandardAccelerator& val ) = 0;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/03/27 05:25:13  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.3.2.1  2005/03/14 04:17:24  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/25 03:23:57  ddiego
*and even more dialog updates. Introduced smore docs to the dialog class and added a new showXXX function.
*
*Revision 1.2.2.1  2004/10/24 18:48:56  marcelloptr
*Document Window documentation
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.2.2.1  2003/09/12 00:09:34  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2  2003/08/09 02:56:44  ddiego
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


#endif // _VCF_UIPOLICYMANAGER_H__


