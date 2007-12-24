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

#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__


/**
*core text model classes
*/
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


/**
*core table model classes
*/
#ifndef _VCF_TABLEMODEL_H__
#	include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__



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

#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__



/**
*implementations
*/

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



#ifndef _VCF_DEFAULTTABLECELLITEM_H__
#	include "vcf/ApplicationKit/DefaultTableCellItem.h"
#endif // _VCF_DEFAULTTABLECELLITEM_H__

#ifndef _VCF_DEFAULTTABLEMODEL_H__
#	include "vcf/ApplicationKit/DefaultTableModel.h"
#endif // _VCF_DEFAULTTABLEMODEL_H__


#endif // _VCF_MODELVIEWKIT_H__

/**
$Id$
*/
