#ifndef _VCF_TREEMODEL_H__
#define _VCF_TREEMODEL_H__
//TreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class TreeItem;



/**
*
*/
class APPLICATIONKIT_API TreeModel  {
public:


	TreeModel(){

	};

	virtual ~TreeModel(){};


	enum TreeModelEvents {
		TREEITEM_ADDED = Model::MODEL_LAST_EVENT + 2000,
		TREEITEM_DELETED
	};


	virtual Enumerator<TreeItem*>* getRootItems() = 0;

	virtual void addTreeRootNodeChangedHandler( EventHandler* handler ) = 0;

	virtual void removeTreeRootNodeChangedHandler( EventHandler* handler ) = 0;

	virtual void addTreeNodeAddedHandler( EventHandler* handler ) = 0;

	virtual void removeTreeNodeAddedHandler( EventHandler* handler ) = 0;

	virtual void addTreeNodeDeletedHandler( EventHandler* handler ) = 0;

	virtual void removeTreeNodeDeletedHandler( EventHandler* handler ) = 0;

	virtual void insertNodeItem( TreeItem * node, TreeItem * nodeToInsertAfter ) = 0;


	virtual void deleteNodeItem( TreeItem * nodeToDelete ) = 0;

	virtual void addNodeItem( TreeItem * node, TreeItem * nodeParent=NULL ) = 0;

	virtual void sort() = 0;
};


}; //namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/22 03:27:36  marcelloptr
*just reformatting
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
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
*Revision 1.12.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.6.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.11  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.10  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/04/27 15:43:07  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.9  2002/03/01 01:02:37  ddiego
*fixes bug [ 524006 ] TreeListControl crash
*makes some changes to model classes to utilize event types better
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TREEMODEL_H__


