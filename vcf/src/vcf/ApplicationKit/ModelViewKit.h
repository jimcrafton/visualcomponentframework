#ifndef _VCF_MODELVIEWKIT_H__
#define _VCF_MODELVIEWKIT_H__
//ModelViewKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//ModelViewKit.h




/**
*Use this header to add support for the various model/item/view implementation classes
*/

#ifndef _VCF_ABSTRACTMODEL_H__
#	include "vcf/ApplicationKit/AbstractModel.h"
#endif // _VCF_ABSTRACTMODEL_H__

#ifndef _VCF_DOCUMENT_H__
#	include "vcf/ApplicationKit/Document.h"
#endif // _VCF_DOCUMENT_H__



#ifndef _VCF_DOCUMENTMANAGER_H__
#	include "vcf/ApplicationKit/DocumentManager.h"
#endif // _VCF_DOCUMENTMANAGER_H__

#ifndef _VCF_DOCMANAGERPOLICY_H__
#	include "vcf/ApplicationKit/DocManagerPolicy.h"
#endif // _VCF_DOCMANAGERPOLICY_H__


#ifndef _VCF_DOCUMENTBASEDAPPLICATION_H__
#	include "vcf/ApplicationKit/DocumentBasedApplication.h"
#endif // _VCF_DOCUMENTBASEDAPPLICATION_H__



/**
*core list model classes
*/
#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__

#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__


/**
*core text model classes
*/
#ifndef _VCF_TEXTEVENT_H__
#	include "vcf/ApplicationKit/TextEvent.h"
#endif // _VCF_TEXTEVENT_H__

#ifndef _VCF_TEXTMODEL_H__
#	include "vcf/ApplicationKit/TextModel.h"
#endif // _VCF_TEXTMODEL_H__



/**
*core tree model classes
*/
#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

#ifndef _VCF_TREEITEM_H__
#	include "vcf/ApplicationKit/TreeItem.h"
#endif // _VCF_TREEITEM_H__

#ifndef _VCF_TREEMODELEVENT_H__
#	include "vcf/ApplicationKit/TreeModelEvent.h"
#endif // _VCF_TREEMODELEVENT_H__



/**
*core tab model classes
*/
#ifndef _VCF_TABMODEL_H__
#	include "vcf/ApplicationKit/TabModel.h"
#endif // _VCF_TABMODEL_H__

#ifndef _VCF_TABPAGE_H__
#	include "vcf/ApplicationKit/TabPage.h"
#endif // _VCF_TABPAGE_H__

#ifndef _VCF_TABMODELEVENT_H__
#	include "vcf/ApplicationKit/TabModelEvent.h"
#endif // _VCF_TABMODELEVENT_H__



/**
*core table model classes
*/
#ifndef _VCF_TABLEMODEL_H__
#	include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__

#ifndef _VCF_TABLEMODELEVENT_H__
#	include "vcf/ApplicationKit/TableModelEvent.h"
#endif // _VCF_TABLEMODELEVENT_H__


#ifndef _VCF_TABLECELLITEM_H__
#	include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__

#ifndef _VCF_TABLEITEMEDITOR_H__
#	include "vcf/ApplicationKit/TableItemEditor.h"
#endif // _VCF_TABLEITEMEDITOR_H__


/**
*Column model classes
*/
#ifndef _VCF_COLUMNITEMEVENT_H__
#	include "vcf/ApplicationKit/ColumnItemEvent.h"
#endif // _VCF_COLUMNITEMEVENT_H__

#ifndef _VCF_COLUMNMODELEVENT_H__
#	include "vcf/ApplicationKit/ColumnModelEvent.h"
#endif // _VCF_COLUMNMODELEVENT_H__

#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__



/**
*implementations
*/
#ifndef _VCF_ABSTRACTLISTMODEL_H__
#	include "vcf/ApplicationKit/AbstractListModel.h"
#endif // _VCF_ABSTRACTLISTMODEL_H__

#ifndef _VCF_DEFAULTLISTITEM_H__
#	include "vcf/ApplicationKit/DefaultListItem.h"
#endif // _VCF_DEFAULTLISTITEM_H__

#ifndef _VCF_DEFAULTLISTMODEL_H__
#	include "vcf/ApplicationKit/DefaultListModel.h"
#endif // _VCF_DEFAULTLISTMODEL_H__

#ifndef _VCF_DEFAULTTEXTMODEL_H__
#	include "vcf/ApplicationKit/DefaultTextModel.h"
#endif // _VCF_DEFAULTTEXTMODEL_H__

#ifndef _VCF_ABSTRACTTREEMODEL_H__
#	include "vcf/ApplicationKit/AbstractTreeModel.h"
#endif // _VCF_ABSTRACTTREEMODEL_H__

#ifndef _VCF_DEFAULTTREEITEM_H__
#	include "vcf/ApplicationKit/DefaultTreeItem.h"
#endif // _VCF_DEFAULTTREEITEM_H__

#ifndef _VCF_DEFAULTTREEMODEL_H__
#	include "vcf/ApplicationKit/DefaultTreeModel.h"
#endif // _VCF_DEFAULTTREEMODEL_H__

#ifndef _VCF_DEFAULTCOLUMNMODEL_H__
#	include "vcf/ApplicationKit/DefaultColumnModel.h"
#endif // _VCF_DEFAULTCOLUMNMODEL_H__

#ifndef _VCF_DEFAULTCOLUMNITEM_H__
#	include "vcf/ApplicationKit/DefaultColumnItem.h"
#endif // _VCF_DEFAULTCOLUMNITEM_H__

#ifndef _VCF_DEFAULTTABPAGE_H__
#	include "vcf/ApplicationKit/DefaultTabPage.h"
#endif // _VCF_DEFAULTTABPAGE_H__

#ifndef _VCF_DEFAULTTABMODEL_H__
#	include "vcf/ApplicationKit/DefaultTabModel.h"
#endif // _VCF_DEFAULTTABMODEL_H__


#ifndef _VCF_DEFAULTTABLECELLITEM_H__
#	include "vcf/ApplicationKit/DefaultTableCellItem.h"
#endif // _VCF_DEFAULTTABLECELLITEM_H__

#ifndef _VCF_DEFAULTTABLEMODEL_H__
#	include "vcf/ApplicationKit/DefaultTableModel.h"
#endif // _VCF_DEFAULTTABLEMODEL_H__


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.2  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.6.2.1  2004/01/29 22:26:47  ddiego
*table fixes, this still needs some more work
*
*Revision 1.6  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.1  2003/09/12 00:09:31  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.5  2003/08/09 02:56:42  ddiego
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
*Revision 1.4.2.2  2003/07/06 01:20:29  ddiego
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
*Revision 1.4.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.4  2003/05/17 20:36:58  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:42  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.1  2002/05/01 01:19:50  ddiego
*added remaining new files from switching stuff around
*like the peer classes and some of the drag drop stuff
*
*/


#endif // _VCF_MODELVIEWKIT_H__


