#ifndef _VCF_ABSTRACTLISTMODEL_H__
#define _VCF_ABSTRACTLISTMODEL_H__
//AbstractListModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__

namespace VCF{

class Stream;

#define ABSTRACTLISTMODEL_CLASSID		"ED88C0A7-26AB-11d4-B539-00C04F0196DA"

/**
\class AbstractListModel AbstractListModel.h "vcf/ApplicationKit/AbstractListModel.h"
*The AbstractListModel is basic implementation of ListModel.
*Deriving classes can use it as starting point in their own
*implementation. See ListModel for more information on the methods
*implemented here.
*
*@see ListModel
*@see DefaultListModel
*@version 1.0
*@author Jim Crafton
@delegates
	@del AbstractListModel::ModelEmptied
	@del AbstractListModel::ModelValidate
	@del AbstractListModel::ContentsChanged
	@del AbstractListModel::ItemAdded
	@del AbstractListModel::ItemDeleted

*/
class APPLICATIONKIT_API AbstractListModel : public ListModel, public Persistable {
public:

	AbstractListModel();

	virtual ~AbstractListModel();

    

    /**
    * clears out the model's data
    */
    void empty();

	/**
	@delegate  ContentsChanged
	@event ListModelEvent
	@eventtype LIST_MODEL_CONTENTS_DELETED
	*/
	DELEGATE(ContentsChanged)

	/**
	@delegate ItemAdded fired when an item is added to the list model
	@event ListModelEvent
	*/
	DELEGATE(ItemAdded)

	/**
	@delegate ItemDeleted fired when an item is removed from the list model
	@event ListModelEvent
	*/
	DELEGATE(ItemDeleted)

	virtual void addContentsChangedHandler(EventHandler * handler) {
		ContentsChanged += handler;
	}

	virtual void removeContentsChangedHandler(EventHandler * handler) {
		ContentsChanged -= handler;
	}

	virtual void addItemAddedHandler(EventHandler * handler) {
		ItemAdded += handler;
	}

	virtual void removeItemAddedHandler(EventHandler * handler) {
		ItemAdded -= handler;
	}

	virtual void addItemDeletedHandler(EventHandler * handler) {
		ItemDeleted += handler;
	}

	virtual void removeItemDeletedHandler(EventHandler * handler) {
		ItemDeleted -= handler;
	}

    virtual void deleteItem(ListItem * item);

    virtual void deleteItemAtIndex(const unsigned long & index);

    virtual void insertItem(const unsigned long & index, ListItem * item);

    virtual void addItem(ListItem * item);

	virtual ListItem* getItemFromIndex( const unsigned long& index );

	virtual ulong32 getItemIndex( ListItem* item );

	virtual Enumerator<ListItem*>* getItems();

	virtual unsigned long getCount();

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );
private:

    /**
    * @supplierCardinality 0..*
   */
	std::vector<ListItem*> listItems_;
	EnumeratorContainer<std::vector<ListItem*>, ListItem*> listContainer_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.1  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
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
*Revision 1.18.2.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.18  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.15.2.5  2004/03/21 00:39:21  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.15.2.4  2004/02/12 14:39:01  marcelloptr
*added member function getItemIndex
*
*Revision 1.15.2.1  2003/12/22 21:55:49  marcelloptr
*minor changes
*
*Revision 1.15  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.2  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.14.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.14  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:09:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.14.4  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.12.14.3  2002/12/28 21:50:46  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.12.14.2  2002/12/27 23:04:29  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12.14.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.12  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.2  2002/04/27 15:41:41  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.11.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.11  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.10  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTLISTMODEL_H__


