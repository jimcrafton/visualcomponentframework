#ifndef _VCF_ABSTRACTTREEMODEL_H__
#define _VCF_ABSTRACTTREEMODEL_H__
//AbstractTreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

#ifndef _VCF_TREEMODELEVENT_H__
#	include "vcf/ApplicationKit/TreeModelEvent.h"
#endif // _VCF_TREEMODELEVENT_H__

#ifndef _VCF_TREEITEM_H__
#	include "vcf/ApplicationKit/TreeItem.h"
#endif // _VCF_TREEITEM_H__

namespace VCF{

#define ABSTRACTTREEMODEL_CLASSID		"3126B227-2819-11d4-B53A-00C04F0196DA"


/**
*AbstractTreeModel is a basic implementation of Treemodel. It used for
*deriving classes to have a starting point for implementing
*a concrete TreeModel class.
*For more information on the methods implemented here please see TreeModel.
*
*@see TreeModel
*@see DefaultTreeModel
*@version 1.0
*@author Jim Crafton
@delegates
	@del AbstractTreeModel::ModelEmptied
	@del AbstractTreeModel::ModelValidate
*/
class APPLICATIONKIT_API AbstractTreeModel : public TreeModel {
public:


    AbstractTreeModel();

	virtual ~AbstractTreeModel();

	void init();

	/**
	@delegate ModelEmptied fired when the model's empty() method is
	called.
	@event ModelEvent
	@see empty()
	*/
	DELEGATE(ModelEmptied)

	/**
	@delegate ModelValidate fired when the model's validate() method is called
	@event ValidationEvent
	@see validate()
	*/
	DELEGATE(ModelValidate)


    virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate += handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate -= handler;
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelEmptied += handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelEmptied -= handler;
	}

	/**
	@delegate RootNodeChanged
	@event
	*/
	DELEGATE(RootNodeChanged)

	/**
	@delegate NodeAdded
	@event
	*/
	DELEGATE(NodeAdded)

	/**
	@delegate NodeDeleted
	@event
	*/
	DELEGATE(NodeDeleted)

	virtual void addTreeRootNodeChangedHandler( EventHandler* handler ) {
		RootNodeChanged += handler;
	}

	virtual void removeTreeRootNodeChangedHandler( EventHandler* handler ) {
		RootNodeChanged -= handler;
	}

	virtual void addTreeNodeAddedHandler( EventHandler* handler ) {
		NodeAdded += handler;
	}

	virtual void removeTreeNodeAddedHandler( EventHandler* handler ) {
		NodeAdded -= handler;
	}

	virtual void addTreeNodeDeletedHandler( EventHandler* handler ) {
		NodeDeleted += handler;
	}

	virtual void removeTreeNodeDeletedHandler( EventHandler* handler ) {
		NodeDeleted -= handler;
	}

	/**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not
	 *require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate();

    /**
     * clears out the model's data
     */
    virtual void empty();

	virtual Enumerator<TreeItem*>* getRootItems();

    virtual void insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter);

    virtual void deleteNodeItem(TreeItem * nodeToDelete);

    virtual void addNodeItem( TreeItem * node, TreeItem * nodeParent=NULL );

    virtual void sort();

	virtual void onItemPaint( ItemEvent* event );

    virtual void onItemChanged( ItemEvent* event );

    virtual void onItemSelected( ItemEvent* event );

	virtual void onItemAdded( ItemEvent* event );

	virtual void onItemDeleted( ItemEvent* event );
protected:
	std::vector<TreeItem*> rootNodes_;
	EnumeratorContainer<std::vector<TreeItem*>,TreeItem*> treeItemContainer_;
private:

};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.14.4.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.4.2  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.13.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.13  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.1  2003/03/12 03:09:13  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.14.2  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.11.14.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.11  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.10.4.2  2002/04/27 15:41:46  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.10.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.10  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTTREEMODEL_H__


