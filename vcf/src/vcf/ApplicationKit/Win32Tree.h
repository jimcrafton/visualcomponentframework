#ifndef _VCF_WIN32TREE_H__
#define _VCF_WIN32TREE_H__
//Win32Tree.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/TreePeer.h"

#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

namespace VCF {

class TreeModelEvent;
class ImageListEvent;

class Win32Tree : public AbstractWin32Component, public TreePeer  {
public:
	Win32Tree( TreeControl* tree );

	virtual ~Win32Tree();

	virtual void create( Control* owningControl );

	virtual TreeModel* getTreeModel();

	virtual void setTreeModel( TreeModel* model );

    virtual double getItemIndent();

    virtual void setItemIndent( const double& indent );

    virtual ImageList* getImageList();

	virtual void setStateImageList( ImageList* imageList );

    virtual void setImageList( ImageList* imageList );

	virtual void addItem( TreeItem* item );

	virtual void clear();

	void init();

	virtual Win32Object::CreateParams createParams();

	virtual Rect getItemImageRect( TreeItem* item );

	virtual Rect getItemRect( TreeItem* item );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);
/*
	void onItemPaint( ItemEvent* event );

    void onItemChanged( ItemEvent* event );

    void onItemSelected( ItemEvent* event );

	void onItemAdded( ItemEvent* event );

	void onItemDeleted( ItemEvent* event );
*/
private:
	//ItemHandler* itemAddedHandler_;
	//ItemHandler* itemDeletedHandler_;
	//ItemHandler* itemChangedHandler_;
	//ItemHandler* itemSelectedHandler_;
	//ItemHandler* itemPaintedHandler_;

	TreeControl* treeControl_;
	//WNDPROC oldTreeWndProc_;
	std::map<TreeItem*,HTREEITEM> treeItems_;
	//Color backColor_;
	HIMAGELIST imageListCtrl_;
	HIMAGELIST stateImageListCtrl_;
	bool internalTreeItemExpanded_;
	void onImageListImageChanged( ImageListEvent* event );

	void onStateImageListImageChanged( ImageListEvent* event );

	void onControlModelChanged( Event* e );
	void onTreeModelChanged( ModelEvent* event );

	void addTreeItem( TreeModel::Key key, HTREEITEM parent );

	//void onTreeNodeDeleted( TreeModelEvent* event );
};

};


#endif // _VCF_WIN32TREE_H__

/**
$Id$
*/
