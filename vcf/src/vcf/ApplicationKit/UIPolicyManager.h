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
\class UIPolicyManager UIPolicyManager.h "vcf/ApplicationKit/UIPolicyManager.h"  
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


#endif // _VCF_UIPOLICYMANAGER_H__

/**
$Id$
*/
