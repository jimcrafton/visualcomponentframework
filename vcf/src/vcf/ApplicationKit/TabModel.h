#ifndef _VCF_TABMODEL_H__
#define _VCF_TABMODEL_H__
//TabModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define TABMODEL_CLASSID	"4A9D66D7-3B26-11d4-B54C-00C04F0196DA"

class TabPage;

/**
\par
The Tab model is a interface for describing what a model that implements
a series of tabs should do. It does not \emnot inherit from the Model class
directly. This is to allow different implementations different base classes.
For example, you might have a simple list model that inherits/implements the 
Model class, and the TabModel class. This would be suitable for most controls.
However you might want a fancier implementation, perhaps that is based 
off of the Document and TabModel classes. This would still allow you to 
use the same control with either style.
*/

class APPLICATIONKIT_API TabModel  {
public:

	TabModel(){

	};

	virtual ~TabModel(){};

	virtual void addTabPageAddedHandler( EventHandler* handler ) = 0;

	virtual void removeTabPageAddedHandler( EventHandler* handler ) = 0;

	virtual void addTabPageRemovedHandler( EventHandler* handler ) = 0;

	virtual void removeTabPageRemovedHandler( EventHandler* handler ) = 0;

	virtual void addTabPageSelectedHandler( EventHandler* handler ) = 0;

	virtual void removeTabPageSelectedHandler( EventHandler* handler ) = 0;

	virtual void addTabPage( TabPage* page ) = 0;

	virtual void insertTabPage( const ulong32& index, TabPage* page ) = 0;

	virtual void deleteTabPage( TabPage* page ) = 0;

	virtual void deleteTabPage( const ulong32& index ) = 0;

	virtual void clearTabPages() = 0;

	virtual TabPage* getPageFromPageName( const String& pageName ) = 0;

	virtual TabPage* getPageAt( const ulong32& index ) = 0;

	virtual ulong32 getItemIndex( TabPage* item ) = 0;

	virtual TabPage* getSelectedPage() = 0;

	virtual void setSelectedPage( TabPage* page ) = 0;

	virtual void setSelectedPage( const ulong32& index ) = 0;

	virtual Enumerator<TabPage*>* getPages() = 0;

	virtual uint32 getPageCount() = 0;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/19 04:08:52  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.4  2004/07/17 17:56:24  ddiego
*minor mods to the TableControl and the TabbedPages control
*so that drawing updates get drawn better, and we don't have weird missing
*artifacts.
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.9.2.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.8.2.2  2004/02/12 14:39:01  marcelloptr
*added member function getItemIndex
*
*Revision 1.8  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.6.2  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.7.6.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TABMODEL_H__


